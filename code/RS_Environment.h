
#ifndef RS_Environment_H
#define RS_Environment_H

#include <string>
#include <memory>
#include <assert.h>
#include <pugixml.hpp>
#include "RS_Common.h"
#include <iostream>

#define ROOMSERVER_VERSION		("0.1.1")
#define ROOMSERVER_AUTHOR		("liu")
#define ROOMSERVER_LASTDATE		("2017-03-18")

class RS_Environment
{
public:
	typedef std::shared_ptr<RS_Environment> ptr_t;
	RS_Environment(){}
	~RS_Environment(){}
	static ptr_t create()
	{
		ptr_t p = std::make_shared<RS_Environment>();
		assert(p != NULL);
		return p;
	}

	bool init();
	int getRoomServerPort(){	return config_.port;	}
	std::string& getDBUser(){	return config_.DBUser;	}
	std::string& getDBPSW(){	return config_.DBPassword;}

private:
	void writeConfig_();
	bool readConfig_();

	RSConfig config_;
	static const std::string path_;
};

#endif //RS_Environment_H