#include<iostream>
#include"Connection.h"
#include"CommonConnectionPool.h"


int main()
{
	/*ͷ�ļ���#include <stdio.h>, sprintf()�������ڽ���ʽ��������д���ַ�������ԭ��Ϊ��
	int sprintf(char *str, char * format [, argument, ...]);
	sprintf(s, "%8x", 4567);  //Сд16���ƣ����ռ8��λ�ã��Ҷ���*/
	/*
	Connection conn;
	char sql[1024] = { 0 };											//��ʼ��Ϊ��
	sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
	conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
	conn.update(sql);
	*/
	ConnectionPool* cp = ConnectionPool::getConnectionPool();

	clock_t begin = clock();
	
	thread t1([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t2([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t3([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t4([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t5([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t6([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			
		}
	});

	thread t7([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});
	thread t8([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t9([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t10([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});
	
	thread t11([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t12([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t13([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t14([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
			sp->update(sql);
			//*/
		}
	});

	thread t15([&]() {
		//ConnectionPool* cp = ConnectionPool::getConnectionPool();			//��õ���ģʽ�����ӳض���
		for (int i = 0; i < 667; i++) {
			/*
			//��ʹ�����ӳ�
			Connection conn;
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
			conn.update(sql);
			*/

			///*
			//ʹ�����ӳ�
			char sql[1024] = { 0 };											//��ʼ��Ϊ��
			sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
			shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
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
	�ͻ���		δʹ�����ӳأ����̣߳�	8�߳�			ʹ�����ӳأ����̣߳�	8�̣߳�  15
	1000��				      8925ms, 1684ms						2749ms,	754ms
	5000,					  44550ms, 8190ms						13558ms,3242ms
	10000,					 86209ms, 16535ms						25755ms,6627ms��5702ms
	//1.���̱߳Ƚϣ��൱�������߳�����ѭ��ִ��1000�Σ��������ڣ�ʹ�����ӳصĿ���ֱ�ӴӶ�����ֱ�ӻ�ȡ�Ѿ����ڵ����ӣ�
	//				û�����ӳص�ÿ��ѭ��������Ӷ�Ҫ��ʼ�����ӣ����ӵ����ݿ⡣ÿ��ѭ��ֻ�õ���һ�����ӣ���1000��
					���Ӷ��Ǵ��еģ����ǲ��еģ������ھ�����
	//2.���̱߳Ƚϣ�ʹ�����ӳص�����ڶ���̣߳����ó�ʼ������4�����������6֮��ᷢ������߳�8֮�侺����Ҳ���漰��
					���Ӷ��еİ�ȫ�ԣ���Ҫ�����������������̣߳��ȴ������ѡ�
	*/


#if 0
	for (int i = 0; i < 10000; i++) {
		/*
		//��ʹ�����ӳ�
		Connection conn;
		char sql[1024] = { 0 };											//��ʼ��Ϊ��
		sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
		conn.connect("127.0.0.1", 3306, "root", "961128", "chat");		//�������ݿ�
		conn.update(sql);
		*/

		///*
		//ʹ�����ӳ�
		char sql[1024] = { 0 };											//��ʼ��Ϊ��
		sprintf(sql, "insert into user(name, age, sex) values('%s', '%d', '%s')", "Gucci", 12, "female");
		shared_ptr<Connection> sp = cp->getConnection();				//��ȡConnection������ָ��
		sp->update(sql);
		//*/
	}
#endif

	return 0;


}