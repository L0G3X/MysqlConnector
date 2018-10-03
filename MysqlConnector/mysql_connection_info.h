#ifndef MYSQL_CONNECTION_INFO
#define MYSQL_CONNECTION_INFO

struct mysql_connection_info
{
	char* host;
	char* uid;
	char* pwd;
	char* db;
};

#endif