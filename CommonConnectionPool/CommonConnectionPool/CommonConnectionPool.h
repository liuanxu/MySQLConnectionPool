#pragma once
//#include <pthread.h>
#include<string>
#include<queue>
#include<mutex>
#include"Connection.h"
#include<atomic>	//ԭ�Ӳ���
#include<memory>	//����ָ��
#include<thread>
#include<condition_variable>	//��������������ͬ������
#include<functional>			//ʹ�����еİ󶨺���bind()


/*
	ʵ�����ӳع���ģ��
*/


//����һ���ڲ���̬����������ʵ��
class ConnectionPool {
public:
	//���ⲿ�ṩ�ӿڣ���ȡ���ӳص�������,����ģʽ�����̰߳�ȫ����������Ϊ��һ�֣�get������ʹ�þ�̬������
	//C++��ĳ�Ա�����У�ʹ��static����ʱ���ñ����Ƿ�����洢���������Ƕ���洢�����������и���Ķ�����þ�̬������
	static ConnectionPool* getConnectionPool();		

	//�������߳��������ӣ����ⲿ�ṩ�ӿ�,�����ӳ��л�ȡһ�����õĿ�������,!!!ʹ������ָ�룬��������ʱ�黹connection���ض�����
	shared_ptr<Connection> getConnection();		//����һ������ָ�룬����ʱ�Զ��������ض�������������

private:
	//����ģʽ�����캯���������������������캯������ֵ���캯��˽�л�
	ConnectionPool();

	//�����ڶ������߳��У�ר�Ÿ��������µ����ӣ����������ڳ�Ա������Ϊ���̵߳���ں���,��������˺����������ڳ�Ա����
	void produceConnectionTask();

	//����һ���µĶ�ʱ�̣߳�ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ճ�ʱ������
	void scannerConnectionTask();

	//�������ļ��м���������
	bool loadConfigFile();

	string _ip;				//mysql��ip��ַ
	unsigned short _port;	//�˿ں�
	string _username;		//�û���
	string _password;		//��¼����
	string _dbname;			//���ӵ����ݿ�����
	int _initSize;			//���ӳصĳ�ʼ������
	int _maxSize;			//���ӳص����������
	int _maxIdleTime;		//���ӳص�������ʱ��s
	int _connectionTimeout;	//���ӳػ�ȡ���ӵĳ�ʱʱ��ms

	queue<Connection*> _connectionQue;	//���ӳص����Ӷ���
	mutex _queueMutex;					//ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt;			//��¼������������connection���ӵ�������
	condition_variable cv;				//�����������������������������̺߳����������̵߳�ͨ��
};


#if 0
//��������������д����ʹ�û�����mutex����
/*�������̣�
�������ʹ���ض����������ͣ�pthread_mutex_t��ʹ�û�����ǰҪ�ȳ�ʼ����ʹ�õĺ������£�
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);	//�������г�ʼ��
int pthread_mutex_destroy(pthread_mutex_t *mutex);													//������
�Ի��������������ĺ������£�
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);	//���ԶԻ���������������û������Ѿ�����ס����������ʧ�ܣ�����EBUSY����������ɹ�����0���̲߳��ᱻ������
int pthread_mutex_unlock(pthread_mutex_t *mutex);
��������:
��������������϶࣬��һ���̶߳Ա���a��������ͼ�Ա���b��������һ���̶߳Ա���b����������ͼ��a��������ʱ�����̶߳����ͷ������Ӳ�������ɹ�����������̴߳�������״̬��
����������б��������ķ�������ʹ�� pthread_mutex_timedlock�������ú��������߳������ض�ʱ�䣬�������ʧ�ܾͻ᷵��ETIMEDOUT��
#include <pthread.h>
#include <time.h>
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timesec *restrict tsptr);
*/
class ConnectionPool {
public:
	static pthread_mutex_t mutex;
	static ConnectionPool * getConnectionPool();
private:
	ConnectionPool();	//���캯����Ҫ�������г�ʼ�����ã�pthread_mutex_init(mutex);
	static ConnectionPool* pool;
};
//��̬���������ʼ��
ConnectionPool* ConnectionPool::pool = nullptr;
pthread_mutex_t ConnectionPool::mutex;

//������������ģʽ����main()��������ǰ���Ѿ���ʼ��һ������
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();
private:
	ConnectionPool();
	static ConnectionPool* pool;
};
ConnectionPool* ConnectionPool::pool = new ConnectionPool;	//Ԥ����׶ξ��Ѿ����ɵ�������
ConnectionPool* ConnectionPool::getConnectionPool() {
	return &pool;
}
#endif

