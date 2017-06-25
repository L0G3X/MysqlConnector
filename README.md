# Mysql Connector (C++)


## How to build
---------------
to build this project, u have to install mysql server (ms windows) 
and link mysql's include dir path and lib dir path to project. 


## Sample code
----------------
```C++
#include <iostream>
#include "MysqlConnector.h"

#pragma comment(lib, "MysqlConnector.lib")

int main() {
  CMysqlConnector connector{};
  try {
    connector.Initialize(host, userid, passwd, db);
    connector.Open();
    auto sql = "select * from table";
    auto result = connector.ExecuteQuery(sql):
    for(auto val : result) {
        std::cout<<val[0]<<std::endl; 
        // val[N] : Nth column's value. If value is NULL, val[N] returns nullptr. 
    }
  }
  catch (std::exception &e){
    std::cout<<e.what()<<std::endl;
  }
  
  connector.Close();
  
  return 0;
}
```

## returned variables from functions
---------------------------------

CMysqlConnector::Initialize : void

CMysqlConnector::Open : void

CMysqlConnector::Close : void

CMysqlConnector::ExecuteQuery : std::vector<MYSQL_ROW> -> MYSQL_ROW is char**

