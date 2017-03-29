#include "RS_DBServer.h"
#include <functional>
#include <stdexcept>  
#include <exception>  
#include <stdio.h>  

RSDBServer*  RSDBServer::dbserver_ = NULL;
std::once_flag RSDBServer::onceFlag_;

RSDBServer::RSDBServer( int maxSize,std::string userName ,std::string passWord, std::string url)
	:curSize_(0),
	maxSize_(maxSize),
	userName_(userName),
	passWord_(passWord),
	url_(url)
{
	try{
		//driver_ = sql::mysql::get_driver_instance();
		driver_=sql::mysql::get_driver_instance();  
	}
	catch (const sql::SQLException& e)
	{
		iERR<<"Drive connection error"<<std::endl;
	}
	catch (const std::runtime_error& e)
	{
		iERR<<"mysql running wrong"<<std::endl;
	}
	this->initConnect_(maxSize/2);
}

RSDBServer::~RSDBServer()
{	
	destoryConnPool_();
}

void RSDBServer::initConnect_(int initSize)
{
	RSDBServer::Connection* conn;  
	std::lock_guard<std::mutex> lock(mutex_);
	for(int i=0 ; i < initSize; ++i)
	{
		conn = createConnect_();
		if (conn)
		{
			connList_.push_back(conn);
		}
		else
		{
			iERR<<"create conncetion is error"<<std::endl;
		}
	}

}

RSDBServer::Connection* RSDBServer::createConnect_()
{
	 RSDBServer::Connection*conn;  
    try{  
        conn=driver_->connect(this->url_,this->userName_,this->passWord_);//建立连接  
        return conn;  
    }  
    catch(sql::SQLException&e)  
    {  
       iERR<<"create conncetion is error"<<std::endl; 
        return NULL;  
    }  
    catch(std::runtime_error&e)  
    {  
        iERR<<"mysql running wrong"<<std::endl;
        return NULL;  
    }  
}

RSDBServer::Connection* RSDBServer::getConnection()
{
	RSDBServer::Connection*conn;  
	std::lock_guard<std::mutex> lock(mutex_);
	if (connList_.size() > 0)
	{
		conn = connList_.front();
		connList_.pop_front();
		if (conn->isClosed())
		{
			delete conn;
			conn = this->createConnect_();
		}
		if (conn == NULL)
		{
			curSize_--;
		}
		return conn;
	}
	else
	{
		if(curSize_ < maxSize_)
		{
			conn = this->createConnect_();
			if(conn)
			{
				++curSize_;
				return conn;
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;	
		}
	}

}

void RSDBServer::releaseConnection(Connection* conn)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (conn)
	{
		 connList_.push_back(conn);  
	}
}

void RSDBServer::destoryConnPool_()
{
	std::lock_guard<std::mutex> lock(mutex_);
	for(auto iter = connList_.begin();iter != connList_.end(); ++iter)
	{
		destoryConnection_(*iter);
	}
	curSize_ = 0;
	connList_.clear();
}

void RSDBServer::destoryConnection_(Connection* conn)
{
	if(conn)  
    {  
        try{  
            conn->close();  
        }  
        catch(sql::SQLException& e)  
        {  
             iERR<<e.what()<<std::endl;
        }  
        catch(std::exception& e)  
        {  
             iERR<<e.what()<<std::endl; 
        }  
        delete conn;  
    }  
}

RSDBServer* RSDBServer::getInstance()
{
	std::call_once(onceFlag_, RSDBServer::init_);
	return dbserver_;
}

void RSDBServer::init_()
{
	if (!dbserver_ )
	{
		dbserver_ = new RSDBServer( MAX_SIZE, USER_NAME, PASS_WORD,URL);
		assert(dbserver_ != NULL);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
//初始化用户数据
void RSDBServerManager::initData()
{
	RSDBServer::Connection* con;
	sql::Statement* state;
	sql::ResultSet* result;

	con = dbserver_->getConnection();
	state = con->createStatement();  
	state->execute("use mj_arena"); 

	result = state->executeQuery("select * from mj_user");

	while(result->next())
	{
		RSUser::ptr_t p = RSUser::create();

		p->setId(result->getString("u_user_id"));
		p->setName(result->getString("u_user_name"));
		p->setSet(std::atoi(result->getString("u_user_sex").c_str()));
		p->setRoomCardNum(result->getInt("u_roomcard_number"));
		p->setGameStyle(std::atoi(result->getString("u_game_type").c_str()));
		p->setGold(result->getInt("u_recharge_amount"));
		p->setStatus(result->getInt("u_status"));
		p->setlogonTime(result->getString("u_create_time"));
		p->setlastTime(result->getString("u_last_login_time"));

		UserInfo::insert(p->getId(),p);
	}
	delete state;
	dbserver_->releaseConnection(con);

}

void RSDBServerManager::initArena()
{
	
}