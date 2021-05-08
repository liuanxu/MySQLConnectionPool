#pragma once
//#include <pthread.h>
#include<string>
#include<queue>
#include<mutex>
#include"Connection.h"
#include<atomic>	//原子操作
#include<memory>	//智能指针
#include<thread>
#include<condition_variable>	//条件变量，用来同步操作
#include<functional>			//使用其中的绑定函数bind()


/*
	实现连接池功能模块
*/


//方法一、内部静态变量的懒汉实现
class ConnectionPool {
public:
	//给外部提供接口，获取连接池单例对象,懒汉模式两种线程安全方法，这里为第一种，get函数中使用静态变量，
	//C++类的成员函数中，使用static变量时，该变量是放在类存储区，而不是对象存储区，所以所有该类的对象共享该静态变量。
	static ConnectionPool* getConnectionPool();		

	//消费者线程消费连接，给外部提供接口,从连接池中获取一个可用的空闲连接,!!!使用智能指针，定义析构时归还connection返回队列中
	shared_ptr<Connection> getConnection();		//返回一个智能指针，不用时自动析构，重定义其析构函数

private:
	//单例模式，构造函数，析构函数，拷贝构造函数，赋值构造函数私有化
	ConnectionPool();

	//运行在独立的线程中，专门负责生产新的连接，！！！类内成员函数作为子线程的入口函数,这样方便此函数访问类内成员变量
	void produceConnectionTask();

	//启动一个新的定时线程，扫描超过maxIdleTime时间的空闲连接，回收超时的连接
	void scannerConnectionTask();

	//从配置文件中加载配置项
	bool loadConfigFile();

	string _ip;				//mysql的ip地址
	unsigned short _port;	//端口号
	string _username;		//用户名
	string _password;		//登录密码
	string _dbname;			//连接的数据库名称
	int _initSize;			//连接池的初始连接量
	int _maxSize;			//连接池的最大连接量
	int _maxIdleTime;		//连接池的最大空闲时间s
	int _connectionTimeout;	//连接池获取连接的超时时间ms

	queue<Connection*> _connectionQue;	//连接池的连接队列
	mutex _queueMutex;					//维护连接队列的线程安全互斥锁
	atomic_int _connectionCnt;			//记录连接所创建的connection连接的总数量
	condition_variable cv;				//！设置条件变量，用于连接生产线程和连接消费线程的通信
};


#if 0
//方法二、经典锁写法，使用互斥量mutex加锁
/*加锁过程：
互斥变量使用特定的数据类型：pthread_mutex_t，使用互斥量前要先初始化，使用的函数如下：
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);	//对锁进行初始化
int pthread_mutex_destroy(pthread_mutex_t *mutex);													//销毁锁
对互斥量加锁解锁的函数如下：
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);	//尝试对互斥量加锁，如果该互斥量已经被锁住，函数调用失败，返回EBUSY，否则加锁成功返回0，线程不会被阻塞。
int pthread_mutex_unlock(pthread_mutex_t *mutex);
避免死锁:
产生死锁的情况较多，如一个线程对变量a加锁后，试图对变量b加锁，另一个线程对变量b加了锁，试图对a加锁，这时两个线程都不释放锁，加不会加锁成功，造成两个线程处于死锁状态。
可以在设计中避免死锁的发生。如使用 pthread_mutex_timedlock函数，该函数允许线程阻塞特定时间，如果加锁失败就会返回ETIMEDOUT。
#include <pthread.h>
#include <time.h>
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timesec *restrict tsptr);
*/
class ConnectionPool {
public:
	static pthread_mutex_t mutex;
	static ConnectionPool * getConnectionPool();
private:
	ConnectionPool();	//构造函数中要对锁进行初始化设置：pthread_mutex_init(mutex);
	static ConnectionPool* pool;
};
//静态变量类外初始化
ConnectionPool* ConnectionPool::pool = nullptr;
pthread_mutex_t ConnectionPool::mutex;

//方法三、饿汉模式，在main()函数运行前就已经初始化一个对象
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();
private:
	ConnectionPool();
	static ConnectionPool* pool;
};
ConnectionPool* ConnectionPool::pool = new ConnectionPool;	//预编译阶段就已经生成单例对象
ConnectionPool* ConnectionPool::getConnectionPool() {
	return &pool;
}
#endif

