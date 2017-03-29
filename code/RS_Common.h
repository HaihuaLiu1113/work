#ifndef RS_Common_H
#define RS_Common_H
#include <string>
#include <tools/job_queue.hpp>
#include <memory>
#include <map>
#include <assert.h>

#define HEARTBEAT 			(0x3131)
#define CONN_TIMEOUT_ID 	(1113)
#define CONN_TIMEOUT_TIME	(30)

struct RSConfig
{
	std::string version;
	std::string author;
	std::string lastdate;
	int 		port;
	std::string DBUser;
	std::string DBPassword;
};

struct Msg
{
	typedef std::shared_ptr<Msg> ptr_t;
	static ptr_t create()
	{
		ptr_t p = std::make_shared<Msg>();
		assert(p != NULL);
		return p;
	}


	int16_t msgHead;
	std::string msgBody;
};

// typedef iegad::tools::job_que_t<Msg::ptr_t> gps_queue_t;
 //typedef iegad::tools::job_queue<Msg> g_msgQueue_t;
 typedef iegad::tools::job_que_t<Msg::ptr_t> msg_queue_t;

//static g_msgQueue_t gMsgQueue;


#endif //RS_Common_H