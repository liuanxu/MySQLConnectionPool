#include "CommonConnectionPool.h"
#include "public.h" 

//连接池的构造函数
ConnectionPool::ConnectionPool() {
	//1.加载配置项
	if (!loadConfigFile()) { return; }							//若加载错误，直接返回
	
	//2.创建初始数量的连接
	for (int i = 0; i < _initSize; i++) {
		Connection* p = new Connection();						//创建一个连接对象
		p->connect(_ip, _port, _username, _password, _dbname);	//将此对象连接到数据库
		p->refreshAliveTime();									//更新此连接的空闲存活起始时间				
		_connectionQue.push(p);									//将此连接放入队列
		_connectionCnt++;										//当前连接数量加一，此为原子操作
	}

	//3.启动一个新的线程，作为连接的生产者
	/*线程创建时相关知识：线程也是一种资源，是受系统调度的。因此，你必须要让系统知道你的线程的起始位置，
	即线程函数的指针。Window系统的接口（API）是C标准的，系统在启动线程时，需要直接得到线程的起始位置，
	因此你也必须向系统直接传递这样一个直接的函数指针。
	一、std::thread t();默认构造函数构造了一个thread对象，但是这个对象不代表任何一个线程的执行。也就是只是单纯的
	构造了一个类对象而已。以看到，我们没有调用thread的成员函数join 或者 detach 中的任何一个，是因为，执行上一
	段代码，只是创建一个thread对象，但不会开启一个线程。就是当我们用初始化构造函数创建一个thread对象时，这个对象会
	开启一个可连接（joinable）的线程，那这个线程通过调用传进的函数来执行（将这个函数拷贝并作为入口函数），其中传入的
	参数会被拷贝进去当作参数，当构造完成时，这个函数也会被调用起来，这时也是线程开始执行的时候。
	！！！其实当我们开启一个进程时，一定会有一个主线程得到执行，这个主线程的开启伴随着进程的开启而开启，结束也会随
	着进程的结束而结束，而且主线程的入口函数名字为main，这也是当我们运行一个程序时，不写main函数会报错的原因，因为
	这会使主线程找不到入口函数。那我们通过调用thread的初始化构造来创建一个新的线程也要给其一个入口函数，这个线程
	执行的内容也就是函数的内容。
	std::thread类的构造函数是使用可变参数模板实现的，也就是说，可以传递任意个参数，第一个参数是线程的入口函数，而后面
	的若干个参数是该函数的参数。
	二、！！！重点：普通的C++类成员函数都隐含了一个传递函数作为参数，亦即“this”指针，C++通过传递一个指向自身的指针给其成
	员函数从而实现成员函数可以访问C++的数据成员。这也可以理解为什么C++类的多个实例可以共享成员函数但是确有不同的数据
	成员。由于this指针的作用，使得将一个CALLBACK型的成员函数作为回调函数安装时就会因为隐含的this指针使得函数参数个数
	不匹配，从而导致回调函数安装失败。
	thread t(std::mem_fn(&MyClass::thread_func)（入口函数）, Object（对象）, args（入口函数的参数）..);
	Object参数在main函数中为类实例化的对象名称，在类成员函数中为this指针表示绑定的为当前类的类对象，如下：
	1.main函数中：Server server;	thread t(&Server::loop, &server，args); //使用类成员函数，并传入类指针
	2.类成员函数中，即本项目中的此函数，如主进程所调函数也为该类成员，则传入this指回自己。：
		thread producer(std::bind(&ConnectionPool::producerConnectionTask,this,[args]));//[args]表示args有无取决于入口函数
		可以将bind函数看作是一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数
		列表。调用bind的一般形式：auto newCallable = bind(callable,arg_list);
		或者：thread producer(&ConnectionPool::producerConnectionTask,this,[args]);

	！！！如果不传入this指针或Object类对象地址，则需要：
		1.把成员函数设成静态成员函数，不属于某个对象，属于整个类，没有this指针。但是静态成员函数并不能使用非静态的成员
		变量（因为它没有某个具体对象的this指针）。
		2.把成员函数声明为友元函数，没有this指针，但是能够访问类的成员变量。
	*/
	//thread produce(std::bind(&ConnectionPool::produceConnectionTask, this));
	thread produce(&ConnectionPool::produceConnectionTask, this);			//类成员函数作子线程的入口函数的第二种写法
	produce.detach();	//守护线程，主线程结束，detch的线程即使是死循环，也依旧会被终止。主线程结束，回收分配的资源。
	/*守护线程：一旦detach后，与主线程关联的thread对象就会失去与主线程的关联，此时这个子线程会驻留在后台运行(主线程
	失去对子线程的控制)，子线程与主线程失去联系后，被C++运行时库接管，子线程运行结束时由运行时库负责清理该线程的相关资源（守护线程）*/

	//4.启动一个新的定时线程，扫描超过maxIdleTime时间的空闲连接，回收超时的连接
	thread scanner(std::bind(&ConnectionPool::scannerConnectionTask, this));
	scanner.detach();
}

//消费者线程消费连接，给外部提供接口,从连接池中获取一个可用的空闲连接,!!!使用智能指针，定义析构时归还connection返回队列中
/*(1)template< class Rep, class Period > std::cv_status wait_for( std::unique_lock<std::mutex>& lock,const std::chrono::duration<Rep, Period>& rel_time);
若经过 rel_time 所指定的关联时限则为 std::cv_status::timeout ，否则为 std::cv_status::no_timeout 。
(2)bool wait_for( std::unique_lock<std::mutex>& lock,const std::chrono::duration<Rep, Period>& rel_time,[Predicate pred]);
若经过 rel_time 时限后谓词 pred 仍求值为 false 则为 false ，否则为 true 。*/
shared_ptr<Connection> ConnectionPool::getConnection() {
	unique_lock<mutex> lock(_queueMutex);		//从队列中取出一个connection不是线程安全的，如两个线程取队列中的最后一个connection,加锁
	while (_connectionQue.empty()) {
		/*此处wait_for返回的为cv_status,其定义为枚举类型：enum class cv_status { no_timeout,timeout };
		此处会有两种情况：1.超时返回的为timeout，则此时返回获取连接失败，退出。
						  2.是未超时，是被其他消费者线程或生产者线程唤醒，则返回的为no_timeout。若返回的为no_timeout，
						  此时需要判断，因为此时无论是被消费者线程唤醒还是生产者线程唤醒，则必定队列不为空，但此时可能
						  有多个消费者线程在等待消费且被唤醒，也就是说此线程在获取队列中的connection前，队列中的connection
						  可能会被其他消费者线程捷足先登，此时需要判断队列是否为空。不为空则去获取connection，为空则需要继续等待，
						  因此上面需要使用while(_connectionQue.empty())来判断。
		*/
		if (cv.wait_for(lock, chrono::milliseconds(_connectionTimeout)) == cv_status::timeout) {
			if (_connectionQue.empty()) {		//经过timeout未唤醒则连接失败
				LOG("获取空闲连接超时。。。。获取连接失败！");
				return nullptr;
			}
		}
	}
		/*队列不为空，则返回一个指向connection的智能指针sp，获取连接队列中的最前面一个connection
		shared_ptr智能指针析构时，会把connection资源直接delete，相当于调用connection的析构函数，则connection就被close
		这里需要自定义shared_ptr的释放资源的方式，把connection直接归还到queue当中。
		1.shared_ptr的默认释放方法为delete p;,不能delete[] p。但实际上，shared_ptr 的构造函数能够接收两个参数，第一个参数常常
			是需要管理的指针，而第二个参数则可以是自定义的“指针释放方法 deleter”，即可自定义函数为释放方法作为构造函数
			的第二个参数传入。如果自定义的 deleter 方法比较简单，写成 Lambda 表达式（）的形式更加紧凑，如下式：
			shared_ptr<vector<int> > p(new vector<int>[12], [](vector<int> *x){ delete[] x; });
			【所谓的“C++智能指针” shared_ptr 其实并不智能，其实它只能处理一些简单的内存指针而已，至于稍稍复杂一些的
			内存指针，最终真正管理内存的其实还是程序员自身，shared_ptr 本质上只是一个带有“引用计数机制”的秘书，它
			只会调用程序员提供的方法，仅此而已。】
		2.auto_ptr因为auto_ptr的析构函数中删除指针用的是delete,而不是delete [],所以我们不应该用auto_ptr来管理一个数组指针。
			这一点与shared_ptr相同。因为采用的所有权模式，所以一个萝卜一个坑，两个auto_ptr不能同时拥有同一个对象。
			若ps2 = ps1，则ps1失效，当ps2生命周期结束后，系统会调用析构函数。若再次使用或析构ps1，在程序运行
			到此处时会发生未知错误（危险程度高，程序已经运行起来）。
		3.unique_ptr，unique_ptr与auto_ptr相比，前者要求更严格，实现的是独占式拥有或严格拥有概念。即无法使两个unique_ptr
			指向同一个对象。但是可以进行移动构造和移动赋值操作move()函数，ptr2=move(ptr1);将ptr1的所有权转让给ptr2，
			而此时ptr1失效，再次使用会报错;若直接赋值ptr2=ptr1；则在编译器编译阶段报错（危险程度较auto_ptr低，因此unique_ptr基本取代auto_ptr）。
			由于unique_ptr有std::unique_ptr<T[]>的重载函数，所以它可以用来管理数组资源：
			unique_ptr<int[]> pArray(new int[3]{1,3,3});	//不需要自定义Deleter
			对比shared_ptr如下：Connection* c1 = new Connection[2]{string("s1"), string("s2")};
								shared_ptr<Connection> sp(c1, Deleter);	//需要自定义Deleter
			标准库提供了一个可以管理new分配动态数组的unique_ptr版本。为了用用一个unique_ptr管理动态数组，我们必须在对象类型后面跟
			一对空方括号;如此，在unique对象销毁的时候，也可以自动调用delete[]而非delete来完成内存的释放。
			*/
		//使用lamda表达式自定义智能指针的释放方法。因为这里是在服务器应用线程中调用的，归还connection时，涉及到队列安全，需要加锁
		/*二、lamda表达式使用方法：
		与普通函数最大的区别是，除了可以使用参数以外，Lambda函数还可以通过捕获列表访问一些上下文中的数据。具体地，
		捕捉列表描述了上下文中哪些数据可以被Lambda使用，以及使用方式（以值传递的方式或引用传递的方式）。语法上，
		在“[]”包括起来的是捕捉列表，捕捉列表由多个捕捉项组成，并以逗号分隔。捕捉列表有以下几种形式：
			1.[var]表示值传递方式捕捉变量var；
			2.[=]表示值传递方式捕捉所有父作用域的变量（包括this）；也就是包含Lambda函数的语句块，说通俗点就是包含Lambda的“{}”代码块。
			3.[&var]表示引用传递捕捉变量var；
			4.[&]表示引用传递方式捕捉所有父作用域的变量（包括this）；
			5.[this]表示值传递方式捕捉当前的this指针。
		上面的捕捉列表还可以进行组合：
			1.[=,&a,&b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量;
			2.[&,a,this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。
		捕捉列表不允许变量重复传递。下面一些例子就是典型的重复，会导致编译时期的错误：
			1.[=,a]这里已经以值传递方式捕捉了所有变量，但是重复捕捉a了，会报错的;
			2.[&,&this]这里&已经以引用传递方式捕捉了所有变量，再捕捉this也是一种重复。
		*/
	shared_ptr<Connection> sp(_connectionQue.front(),
		[&](Connection* pcon) {
		unique_lock<mutex> lock(_queueMutex);	//归还connection时，可能有多个线程入队，因此需要加锁保证队列安全
		pcon->refreshAliveTime();				//更新此连接的空闲存活起始时间
		_connectionQue.push(pcon);}
	);
	_connectionQue.pop();
	cv.notify_all();							//1是唤醒生产者线程判断是否需要继续生产，2是唤醒其他正在等待获取锁的消费者线程
	return sp;
}

//运行在独立的线程中，专门负责生产新的连接,！！！produce生产者线程的入口函数
/*线程的阻塞是通过条件变量的成员函数wait()/wait_for()/wait_until()函数实现的。
一、wait()成员函数：void wait( std::unique_lock<std::mutex>& lock );wait函数在阻塞时，自动释放锁权限，即调用unique_lock
的成员函数unlock（），以便其他线程能有机会获得锁。这就是条件变量只能和unique_lock一起使用的原因，否则当前线程一直占
有锁，线程被阻塞。cv.wait 第一个参数必须是 unique_lock，因为它内部会执行 unlock和lock。
第二种wait函数，template< class Predicate > void wait( std::unique_lock<std::mutex>& lock, Predicate pred );Predicate 
谓词函数，可以普通函数或者lambda表达式！！。（重要）在正常情况下，wait类型函数返回时要不是因为被唤醒，要不是因为超时才
返回，但是在实际中发现，因操作系统的原因，wait类型在不满足条件时，它也会返回，这就导致了虚假唤醒。因此，我们一般
都是使用带有谓词参数的wait函数，因为这种(xxx, Predicate pred )类型的函数等价于：
		while (!pred()) {wait(lock);}		//（重要）while循环，解决了虚假唤醒的问题

1、关于unique_lock与lock_guard：C++多线程编程中通常会对共享的数据进行写保护，以防止多线程在对共享数据成员进行读写时造
成资源争抢导致程序出现未定义的行为。通常的做法是在修改共享数据成员的时候进行加锁--mutex。在使用锁的时候通常是在对共
享数据进行修改之前进行lock操作，在写完之后再进行unlock操作，进场会出现由于疏忽导致由于lock之后在离开共享成员操作区
域时忘记unlock，导致死锁。针对以上的问题，C++11中引入了std::unique_lock与std::lock_guard两种数据结构。通过对lock和
unlock进行一次薄的封装，实现自动unlock的功能。
2、std::unique_lock相对std::lock_guard更灵活的地方在于在等待中的线程如果在等待期间需要解锁mutex，并在唤醒之后重新将其
锁定。而std::lock_guard却不具备这样的功能。！！！！这就是条件变量中为什么使用unique_lock而不使用lock_guard的原因。
二、notify_all/notify_one：notify函数声明如下：
	（1）void notify_one() noexcept;若任何线程在 *this 上等待，则调用 notify_one 会解阻塞(唤醒)等待线程之一。
	（2）void notify_all() noexcept;若任何线程在 *this 上等待，则解阻塞（唤醒)全部等待线程。


*/
void ConnectionPool::produceConnectionTask() {
	while (true) {
		unique_lock<mutex> lock(_queueMutex);	//用mutex _queueMutex;锁变量来初始化unique_lock对象，此时生产者加锁后，消费者就无法获取此锁		
		while (!_connectionQue.empty()) {
			cv.wait(lock);						//队列不空，则生产线程在此处进入阻塞等待状态,会自动释放锁，使得消费者线程可以拿到此把锁去获取连接
		}
		//当前存在的连接数量小于最大连接数量，允许生产
		if (_connectionCnt < _maxSize) {							
			Connection* p = new Connection();						//创建一个连接对象
			p->connect(_ip, _port, _username, _password, _dbname);	//将此对象连接到数据库
			p->refreshAliveTime();									//更新此连接的空闲存活起始时间
			_connectionQue.push(p);									//将此连接放入队列
			_connectionCnt++;										//当前连接数量加一，此为原子操作
		}
		//通知各消费者线程，可以消费连接
		cv.notify_all();
	}	//一次循环结束出}之后，生产者释放此锁，消费者可获得锁
}

//扫描超过maxIdleTime时间的空闲连接，回收超时的连接,！！！scanner扫描线程的入口函数
void ConnectionPool::scannerConnectionTask() {
	while (true) {
		//通过sleep模拟定时效果
		this_thread::sleep_for(chrono::seconds(_maxIdleTime));
		//扫描整个队列，释放多余的连接，在此之前需要加锁，因为需要删除超出maxIdleTime的connection
		unique_lock<mutex> lock(_queueMutex);
		while (_connectionCnt > _initSize) {
			Connection* p = _connectionQue.front();
			if (p->getAliveTime() >= (_maxIdleTime * 1000)) {
				_connectionQue.pop();
				_connectionCnt--;
				delete p;					//调用~Connection()释放连接
			}
			else {
				break;						//第一个不超过，那么后面的都不会超过
			}
		}

	}
}

//从配置文件中加载配置项
bool ConnectionPool::loadConfigFile() {
	FILE* pf = fopen("mysql.ini", "r");				//打开文件
	if (pf == nullptr) {
		LOG("mysql.ini filee is not exist!");		//文件打开失败，返回错误信息
		return false;
	}
	//打开成功，则进一步处理
	while (!feof(pf)) {								//文件未到结尾
		char line[1024] = { 0 };					//定义一个字符数组，初始化为空
		fgets(line, 1024, pf);						//一次读一行
		string str = line;
		int idx = str.find('=', 0);					//默认从起始位置开始查找
		if (idx == -1) {							//无效的配置项
			continue;
		}
		//password=961128\n，每行结尾还有一个换行符
		int endidx = str.find('\n', idx);
		string key = str.substr(0, idx);
		string value = str.substr(idx + 1, endidx - idx - 1);
		
		if (key == "ip") {
			_ip = value;
		}
		else if (key == "port") {
			_port = atoi(value.c_str());
		}
		else if (key == "username") {
			_username = value;
		}
		else if (key == "password") {
			_password = value;
		}
		else if (key == "dbname")
		{
			_dbname = value;
		}
		else if (key == "initSize") 
		{
		_initSize= atoi(value.c_str());
		}
		else if (key == "maxSize")
		{
			_maxSize= atoi(value.c_str());
		}
		else if (key == "maxIdleTime")
		{
			_maxIdleTime= atoi(value.c_str());
		}
		else if (key == "connectionTimeOut")
		{
			_connectionTimeout= atoi(value.c_str());
		}
	}
	return true;
}


//方法一线程安全的懒汉单例函数接口
ConnectionPool* ConnectionPool::getConnectionPool() {
	//静态局部变量的初始化编译器会自动加lock和unlock(),只要对静态数据成员的值更新一次，
	//保证所有对象存取更新后的相同的值,也就是多次调用getConnectPool，pool对象只定义一次！！！
	static ConnectionPool pool;			
	return &pool;
}


#if 0
//方法二、使用互斥锁
ConnectionPool::ConnectionPool() {
	pthread_mutex_init(&mutex);			//锁在使用前要进行初始化
}
ConnectionPool* ConnectionPool::getConnectionPool() {
	if (pool == nullptr) {
		pthread_mutex_lock(&mutex);		//加锁操作
		if (pool == nullptr) {
			pool = new ConnectionPool();
		}
		pthread_mutex_unlock(&mutex);	//对临界区变量操作完之后要对互斥量解锁
	}
	return pool;
}
#endif