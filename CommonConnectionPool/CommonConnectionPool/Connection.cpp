#include "public.h"
#include "Connection.h"

Connection::Connection() {
	_conn = mysql_init(nullptr);	//��ʼ�����ݿ�����
}

Connection::~Connection() {
	//�ͷ����ݿ�������Դ
	if (_conn != nullptr)mysql_close(_conn);
}

bool Connection::connect(string ip, unsigned short port, string username, string password, string dbname) {
	//�������ݿ�
	MYSQL *p = mysql_real_connect(_conn, ip.c_str(), username.c_str(), password.c_str(), dbname.c_str(), port, nullptr, 0);
	return p != nullptr;			//pΪ��������ʧ�ܣ���Ϊ�������ӳɹ�
}

bool Connection::update(string sql) {
	//���²���,insert,delete,update
	if (mysql_query(_conn, sql.c_str())) {
		LOG("����ʧ��:" + sql);		//����ʧ�ܣ����ش�����Ϣ
		return false;
	}
	return true;
}

MYSQL_RES* Connection::query(string sql) {
//��ѯ����,mysql_query()����ִ�гɹ��򷵻�0
	if (mysql_query(_conn, sql.c_str())) {
		LOG("����ʧ��" + sql);
		return nullptr;
	}
	/*https://blog.csdn.net/daofengliu/article/details/11397327, ����ÿ�����Բ���һ����������������select��show��
	describe, explain, check_table�ȵȣ�������mysql_query����mysql_real_query֮���㶼��Ҫ����mysql_store_result����
	mysql_use_result��䣬��������������Ҫʹ��mysql_free_result�ͷš�*/
	return mysql_use_result(_conn);
}
