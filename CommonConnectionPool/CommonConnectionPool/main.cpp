#include<iostream>
#include"Connection.h"
#include"CommonConnectionPool.h"


int main()
{
	/*头文件：#include <stdio.h>, sprintf()函数用于将格式化的数据写入字符串，其原型为：
	int sprintf(char *str, char * format [, argument, ...]);
	sprintf(s, "%8x", 4567);  //小写16进制，宽度占8个位置，右对齐*/
	/*
	Connection conn;
	char sql[1024] = { 0 };											//初始化为空
	sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
	conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
	conn.update(sql);
	*/
	ConnectionPool* cp = ConnectionPool::getConnectionPool();

	clock_t begin = clock();
	
	thread t1([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t2([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t3([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t4([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t5([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t6([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			
		}
	});

	thread t7([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});
	thread t8([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t9([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t10([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});
	
	thread t11([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t12([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t13([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t14([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	thread t15([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//获得单例模式的连接池对象
		for (int i = 0; i < 667; i++) {
			/*
			//不使用连接池
			Connection conn;
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
			conn.update(sql);
			*/

			///*
			//使用连接池
			char sql[1024] = { 0 };											//初始化为空
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
			sp->update(sql);
			//*/
		}
	});

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
	t10.join();
	t11.join();
	t12.join();
	t13.join();
	t14.join();
	t15.join();
	
	cout << clock() - begin << "ms"<<endl;
	/*
	客户量		未使用连接池：单线程，	8线程			使用连接池：单线程，	8线程，  15
	1000，				      8925ms, 1684ms						2749ms,	754ms
	5000,					  44550ms, 8190ms						13558ms,3242ms
	10000,					 86209ms, 16535ms						25755ms,6627ms，5702ms
	//1.单线程比较：相当于整个线程有序循环执行1000次，区别在于：使用连接池的可以直接从队列中直接获取已经存在的连接，
	//				没有连接池的每次循环获得连接都要初始化连接，连接到数据库。每次循环只用到了一个连接，这1000个
					连接都是串行的，不是并行的，不存在竞争。
	//2.多线程比较：使用连接池的则存在多个线程，设置初始连接数4和最大连接数6之后会发生多个线程8之间竞争，也就涉及到
					连接队列的安全性，需要条件变量锁来阻塞线程，等待被唤醒。
	*/


#if 0
	for (int i = 0; i < 10000; i++) {
		/*
		//不使用连接池
		Connection conn;
		char sql[1024] = { 0 };											//初始化为空
		sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
		conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//连接数据库
		conn.update(sql);
		*/

		///*
		//使用连接池
		char sql[1024] = { 0 };											//初始化为空
		sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
		shared_ptr<Connection> sp = cp->getConnection();				//获取Connection的智能指针
		sp->update(sql);
		//*/
	}
#endif

	return 0;


}