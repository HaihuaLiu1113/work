#ifndef RS_Msg_Processor_H
#define RS_Msg_Processor_H
#include "RS_Common.h"
#include <string>
#include <memory>
#include <assert.h>
#include <net/iegad_tcp_session.hpp>
class RSMsgPocessor
{
public:
	typedef std::shared_ptr<RSMsgPocessor> ptr_t;
	typedef iegad::net::tcp_session tcp_session;

	RSMsgPocessor(std::string msg, msg_queue_t& msgQueue);
	~RSMsgPocessor(){}
	static ptr_t create(std::string msg ,msg_queue_t& msgQueue)
	{
		ptr_t p = std::make_shared<RSMsgPocessor>(msg, msgQueue); 
		assert(p != NULL);
		return p;
	}

	bool checkMsg();
	bool isHeartbeatMsg();
	Msg::ptr_t buildMsg();
	void process(tcp_session::ptr_t session);
	msg_queue_t& get()
	{return msgQueue_;}

private:
	void _dispachMsg(Msg::ptr_t& msg, tcp_session::ptr_t session);

	std::string msg_;
  	msg_queue_t& msgQueue_; 

};


#endif //RS_Msg_Processor_H