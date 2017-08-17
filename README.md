# Mysql Connector (C++)


## How to build
To build this project, u have to install mysql server (ms windows) 
and link mysql's include dir path and lib dir path to project. 
<br/><br/>
프로젝트를 빌드하기위해서는, Mysql server를 설치하여 폴더안에있는 include폴더와 lib폴더를
프로젝트에 링크시킨 후 빌드하면 됩니다. (Lib파일로 빌드후 다른 프로젝트에 이식하십시오.)

## Sample code
```C++
#include <iostream>
#include <MysqlConnector.h>

#pragma comment(lib, "MysqlConnector.lib")

int main() {
  CMysqlConnector connector{};
  try {
    connector.Initialize(host, userid, passwd, db);
    connector.Open();
    auto sql = "select * from table";
    auto result = connector.ExecuteQuery(sql):
    for(auto row : rows) {
        std::cout<<row[0]<<std::endl; 
        // row[N] : Nth column's value. If value is NULL, row[N] returns nullptr. 
    }
  }
  catch (std::exception &e){
    std::cout<<e.what()<<std::endl;
  }
  
  connector.Close();
  
  return 0;
}
```

## Return type of functions
CMysqlConnector::Initialize : void

CMysqlConnector::Open : void

CMysqlConnector::Close : void

CMysqlConnector::ExecuteQuery : std::vector<MYSQL_ROW> -> MYSQL_ROW is char**

