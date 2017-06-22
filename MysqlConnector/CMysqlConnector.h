#pragma once
#pragma comment(lib, "libmysql.lib")

#include "MysqlConnectionInfo.h"
#include <vector>
#include <mysql.h>

class CMysqlConnector
{
public:
	void Initialize(char* host, char* uid, char* pwd, char* db);
	void Initialize(MysqlConnectionInfo connection_info);
	void Open();
	void Close();
	std::vector<MYSQL_ROW> ExecuteQuery(char* sql);

private:
	MYSQL *p_connection;
	MYSQL _connection;
	MYSQL_RES *_sql_res;
	MYSQL_ROW _sql_row;
	MysqlConnectionInfo _connection_info;

	bool is_res_allocated;
	bool is_connection_opened;
};
