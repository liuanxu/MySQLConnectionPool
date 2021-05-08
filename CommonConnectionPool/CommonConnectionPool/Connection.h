#pragma once
#include <string>
#include<ctime>
#include "mysql.h"
using namespace std;
/*
实现MySQL数据库的相应操作
*/
class Connection {
public:
	//初始化数据库连接，即构造函数
	Connection();
	//释放数据库连接资源，即析构函数
	~Connection();
	//连接数据库, ip地址，port端口号，用户名，密码， 数据库名称
	bool connect(string ip, unsigned short port, string user, string password, string dbname);
	//更新操作
	bool update(string sql);
	//查询操作,MYSQL_RES为MySQL头文件中的内容
	MYSQL_RES* query(string sql);
	
	//刷新一下连接的起始空闲时间
	void refreshAliveTime() { _alivetime = clock(); }
	//返回存活时间
	clock_t getAliveTime() const { return clock() - _alivetime; }

private:
	MYSQL *_conn;		//表示和MySQL Server的一条连接
	clock_t _alivetime;	//记录进入空闲状态后的起始存活时间
};


