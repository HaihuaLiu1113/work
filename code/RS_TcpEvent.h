#ifndef RS_TcpEvent_H
#define RS_TcpEvent_H

#include <net/iegad_tcp_event.hpp>
#include <net/iegad_tcp_session.hpp>
#include <memory>
#include <tools/iegad_log.hpp>
#include <string/iegad_string.hpp>
#include "RS_Common.h"
#include "RS_Entry.h"

class RS_TcpEvent:public iegad::net::tcp_event
{
public:
	typedef iegad::net::tcp_session tcp_session;
	typedef boost::shared_ptr<RS_TcpEvent> ptr_t;

	RS_TcpEvent();
	~RS_TcpEvent();

	void openHandler(tcp_session::ptr_t session);
	void closeHandler(tcp_session::ptr_t session);
	void readHandler(tcp_session::ptr_t session, size_t len);
	void writeHandler(tcp_session::ptr_t session, size_t len);

	static ptr_t Create()
	{
		ptr_t p (new RS_TcpEvent);
		assert(p != NULL);
		return p;
	}
	static msg_queue_t& get()
	{
		return msgQueue_; 
	} 
private:
	void _buildMessage(tcp_session::ptr_t session, const std::string msg);

	static msg_queue_t msgQueue_; 
};

#endif //RS_TcpEvent_H