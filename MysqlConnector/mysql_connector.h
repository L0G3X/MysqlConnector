#pragma once
#pragma comment(lib, "libmysql.lib")

#include "mysql_connection_info.h"
#include <vector>
#include <mysql.h>

using mysql = MYSQL;
using mysql_res = MYSQL_RES;
using mysql_row = MYSQL_ROW;

class mysql_connector
{
public:
	void initialize(char* const&, char* const&, char* const&, char*const&);
	void initialize(const mysql_connection_info&);
	void open();
	void close();
	std::vector<mysql_row> execute_query(const char* const&);

private:
	mysql* p_connection;
	mysql connection;
	mysql_res* sql_res;
	mysql_row sql_row;
	mysql_connection_info connection_info;

	bool is_res_allocated;
	bool is_connection_opened;
};
