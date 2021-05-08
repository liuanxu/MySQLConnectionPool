#pragma once
#include <string>
#include<ctime>
#include "mysql.h"
using namespace std;
/*
ʵ��MySQL���ݿ����Ӧ����
*/
class Connection {
public:
	//��ʼ�����ݿ����ӣ������캯��
	Connection();
	//�ͷ����ݿ�������Դ������������
	~Connection();
	//�������ݿ�, ip��ַ��port�˿ںţ��û��������룬 ���ݿ�����
	bool connect(string ip, unsigned short port, string user, string password, string dbname);
	//���²���
	bool update(string sql);
	//��ѯ����,MYSQL_RESΪMySQLͷ�ļ��е�����
	MYSQL_RES* query(string sql);
	
	//ˢ��һ�����ӵ���ʼ����ʱ��
	void refreshAliveTime() { _alivetime = clock(); }
	//���ش��ʱ��
	clock_t getAliveTime() const { return clock() - _alivetime; }

private:
	MYSQL *_conn;		//��ʾ��MySQL Server��һ������
	clock_t _alivetime;	//��¼�������״̬�����ʼ���ʱ��
};


