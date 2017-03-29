#ifndef RS_User_H
#define RS_User_H
#include <string>
#include <boost/asio.hpp>
#include <assert.h>
#include <map>
#include <mutex>

class RSUser
{
public:
	typedef boost::shared_ptr<RSUser> ptr_t;

	RSUser(){}
	~RSUser(){}
	static ptr_t create()
	{
		ptr_t p(new RSUser);
		assert(p!=NULL);
		return p;
	}

	void setId(std::string id){userId_ = id;}
	void setName(std::string name){userName_ = name;}
	void setSet(int sex){userSex_ = sex;}
	void setRoomCardNum(int n){roomCardNum_ = n;}
	void setGameStyle(int style){gameStyle_ = style ;}
	void setGold(int n){gold_ = n;}
	void setStatus(int status){status_ = status;}
	void setlogonTime(std::string logonTime){logonTime_ = logonTime;}
	void setlastTime(std::string lastTime){lastTime_ = lastTime;}

	std::string getId()const {return userId_;}
	std::string getName()const {return userName_;}
	int8_t getSex()const {return userSex_;}
	int32_t getRoomCardNume()const {return roomCardNum_;}
	int8_t getGameStyle()const {return gameStyle_;}
	int32_t getGold()const {return gold_;}
	int8_t getStatus()const {return status_;}
	std::string getLongonTime()const {return logonTime_;}
	std::string getLastTime()const {return lastTime_;}

private:
	std::string userId_;
	std::string userName_;
	int8_t userSex_;
	int32_t roomCardNum_;
	int8_t gameStyle_;
	int32_t gold_;
	int8_t status_;
	std::string logonTime_;
	std::string lastTime_;

};


class UserInfo
{
public:
	typedef std::map<std::string ,RSUser::ptr_t> UserList;
	UserInfo(){}
	~UserInfo(){}
	static void insert(std::string userid,RSUser::ptr_t p)
	{
		std::lock_guard<std::mutex> lock_(mutex_);
		userList_.insert(std::make_pair(userid, p));
	}

	static RSUser::ptr_t getUser(std::string& userid)
	{
		auto iter = userList_.find(userid);
		return iter == userList_.end() ? NULL:iter->second;
	}

	static UserList& getUserList()
	{
		return userList_;
	}
	
private:
	static std::mutex mutex_;
	static UserList userList_;
};

#endif //RS_User_H