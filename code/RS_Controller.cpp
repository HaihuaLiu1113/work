#include "RS_Controller.h"

void RSController::onMessage_(std::string& msg)
{
}

void RSController::run()
{
	t_ = boost::thread(boost::bind(&RSController::getMsg_ ,this));
}

void RSController::getMsg_()
{
	while(!this->stop_)
	{
		Msg::ptr_t msg ;
		msgQueue_.pop(&msg);
		onMessage_(msg->msgBody);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
RSCTRManager::RSCTRManager(RS_Environment::ptr_t evn)
{
	for (int i = 0; i < 4; ++i)
	{
		ptrVec_.push_back(new RSController(RS_TcpEvent::get(), evn));
	}

}
RSCTRManager::~RSCTRManager()
{
}

void RSCTRManager::run()
{
	for (auto& i : this->ptrVec_)
	{
		i.run();
	}
}