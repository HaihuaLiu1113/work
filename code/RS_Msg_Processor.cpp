#include "RS_Msg_Processor.h"
#include <cstdlib>
#include <string/iegad_string.hpp>
#include <tools/iegad_endian.hpp>
#include "RS_Msg_Endecoder.h"

//msg_queue_t RSMsgPocessor::msgQueue_;
RSMsgPocessor::RSMsgPocessor(std::string msg, msg_queue_t& msgQueue):msg_(msg),msgQueue_(msgQueue)
{
}

bool RSMsgPocessor::checkMsg()
{
	return iegad::string_ex::end_with(msg_,"FW");
}

bool RSMsgPocessor::isHeartbeatMsg()
{

}
void RSMsgPocessor::_dispachMsg(Msg::ptr_t& msg, tcp_session::ptr_t session)
{
	switch(msg->msgHead)
	{
		case HEARTBEAT:
		{
			std::string ret = RSMsgEndecoder::endecodeHeartbeatMsg();
			session->write(ret.c_str(), ret.size());
			msgQueue_.push(msg);
		}
		break;
		case 2:
		break;
		default:
		break;
	}
}

void RSMsgPocessor::process(tcp_session::ptr_t session)
{
	Msg::ptr_t p = buildMsg();
	if (!p)
	{
		return;
	}
	_dispachMsg(p, session);

}
Msg::ptr_t RSMsgPocessor::buildMsg()
{
	if (!checkMsg())
	{
		return NULL;
	}
	Msg::ptr_t msg = Msg::create();
	memcpy((char*)&(msg->msgHead), msg_.substr(0,2).c_str(), 2);
	msg->msgHead = iegad::endian::to_little16(msg->msgHead);
	msg->msgBody = msg_.substr(2);
	return msg;
}