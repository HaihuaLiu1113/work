#ifndef RS_DBServer_H
#define RS_DBServer_H

#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <cppconn/exception.h>  
#include <cppconn/driver.h>  
#include <cppconn/connection.h>  
#include <cppconn/resultset.h>  
#include <cppconn/prepared_statement.h>  
#include <cppconn/statement.h>  
#include <pthread.h>  
#include <list>  
#include <string>
#include <mutex>
#include <tools/iegad_log.hpp>
#include "RS_User.h"


#define MAX_SIZE 	(10)
#define USER_NAME	("root")
#define PASS_WORD	("123")
#define URL    		("tcp://127.0.0.1")

class RSDBServer
{
public:
	typedef sql::Connection Connection;
	typedef boost::shared_ptr<sql::Driver> DriverPtr_t;

	static RSDBServer* getInstance();
	void releaseConnection(Connection* conn);
	Connection* getConnection();
	
private:

	RSDBServer(int maxSize,std::string userName ,std::string passWord, std::string url);
	~RSDBServer();
	static void init_();
	void initConnect_(int initSize);
	Connection* createConnect_();
 	Connection* getConnection_();
 	void destoryConnection_(Connection* conn);
	void destoryConnPool_();


	static std::once_flag onceFlag_;
	int curSize_;
	int maxSize_;
	std::string userName_;
	std::string passWord_;
	std::string url_;
	std::mutex mutex_;
	std::list<Connection*> connList_;
	static RSDBServer*  dbserver_;
	sql::Driver* driver_;
};



////////////////////////////////////////////////////////////////////
class RSDBServerManager
{
public:
	RSDBServerManager()
	{
		dbserver_ = RSDBServer::getInstance();
		//userList_ = UserInfo::getUserList();
	}
	~RSDBServerManager(){}
	void initData();
	void initArena();

private:
	RSDBServer * dbserver_;
	//UserInfo::UserList& userList_;
};

#endif// RS_DBServer_H