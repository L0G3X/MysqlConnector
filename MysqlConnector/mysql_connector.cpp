#include "mysql_connector.h"


void mysql_connector::initialize(char* const& host, char* const& uid, char* const& pwd, char*const& db)
{
	initialize(mysql_connection_info{ host, uid, pwd, db });
}

void mysql_connector::initialize(const mysql_connection_info& connection_info)
{
	if (!mysql_init(&connection))
		throw std::exception(mysql_error(&connection));
	this->connection_info = connection_info;
}

void mysql_connector::open()
{
	if (is_connection_opened)
		return;

	p_connection = mysql_real_connect(&connection, connection_info.host, connection_info.uid, connection_info.pwd, connection_info.db, 3306, nullptr, 0);
	if (!p_connection)
		throw std::exception(mysql_error(&connection));

	if (mysql_select_db(&connection, connection_info.db))
		throw std::exception(mysql_error(&connection));

	is_connection_opened = true;
}

void mysql_connector::close()
{
	if (!is_connection_opened)
		return;

	if (is_res_allocated)
		mysql_free_result(sql_res);

	mysql_close(p_connection);
	is_connection_opened = false;
}

std::vector<mysql_row> mysql_connector::execute_query(const char* const& sql)
{
	std::vector<mysql_row> rows{};

	const auto res = mysql_query(p_connection, sql);

	if (res == 0)
	{
		sql_res = mysql_store_result(p_connection);
		is_res_allocated = true;
		while ((sql_row = mysql_fetch_row(sql_res)))
		{
			rows.emplace_back(sql_row);
		}
		mysql_free_result(sql_res);
		is_res_allocated = false;
	}

	return rows;
}
