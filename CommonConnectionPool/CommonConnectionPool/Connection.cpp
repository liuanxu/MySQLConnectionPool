#include "public.h"
#include "Connection.h"

Connection::Connection() {
	_conn = mysql_init(nullptr);	//初始化数据库连接
}

Connection::~Connection() {
	//释放数据库连接资源
	if (_conn != nullptr)mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port, string username, string password, string dbname) {
	//连接数据库
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;			//p为空则连接失败，不为空则连接成功
}

bool Connection::update(string sql) {
	//更新操作,insert,delete,update
	if (mysql_query(_conn, sql.c_str())) {
		LOG("更新失败:" + sql);		//更新失败，返回错误信息
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(string sql) {
//查询操作,mysql_query()函数执行成功则返回0
	if (mysql_query(_conn, sql.c_str())) {
		LOG("更新失败" + sql);
		return nullptr;
	}
	/*https://blog.csdn.net/daofengliu/article/details/11397327, 对于每个可以产生一个结果集的命令（比如select、show、
	describe, explain, check_table等等），发起mysql_query或者mysql_real_query之后，你都需要调用mysql_store_result或者
	mysql_use_result语句，处理完结果集后需要使用mysql_free_result释放。*/
	return mysql_use_result(_conn);
}
