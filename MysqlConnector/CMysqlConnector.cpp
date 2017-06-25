#include "CMysqlConnector.h"


void CMysqlConnector::Initialize(char* host, char* uid, char* pwd, char* db)
{
	Initialize(MysqlConnectionInfo{ host, uid, pwd, db });
}

void CMysqlConnector::Initialize(MysqlConnectionInfo connection_info)
{
	if (!mysql_init(&_connection))
		throw std::exception(mysql_error(&_connection));
	_connection_info = connection_info;
}

void CMysqlConnector::Open()
{
	if (_is_connection_opened)
		return;
	p_connection = mysql_real_connect(&_connection, _connection_info._host, _connection_info._uid, _connection_info._pwd, _connection_info._db, 3306, nullptr, 0);
	if (!p_connection)
		throw std::exception(mysql_error(&_connection));
	if (mysql_select_db(&_connection, _connection_info._db))
		throw std::exception(mysql_error(&_connection));
	_is_connection_opened = true;
}

void CMysqlConnector::Close()
{
	if (!_is_connection_opened)
		return;

	if (_is_res_allocated)
		mysql_free_result(_sql_res);
	mysql_close(p_connection);
	_is_connection_opened = false;
}

std::vector<MYSQL_ROW> CMysqlConnector::ExecuteQuery(const char* sql)
{
	std::vector<MYSQL_ROW> rows{};

	auto res = mysql_query(p_connection, sql);

	if (res == 0)
	{
		_sql_res = mysql_store_result(p_connection);
		_is_res_allocated = true;
		while ((_sql_row = mysql_fetch_row(_sql_res)))
		{
			rows.push_back(_sql_row);
		}
		mysql_free_result(_sql_res);
		_is_res_allocated = false;
	}

	return rows;
}
