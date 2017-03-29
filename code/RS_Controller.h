#ifndef RSContraller_H
#define RSContraller_H
#include "RS_IController.h"
#include <boost/thread.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include "RS_Common.h"
#include "RS_Environment.h"
#include "RS_TcpEvent.h"
#include <boost/bind.hpp>

class RSController:public RSIController
{
public:
	RSController(msg_queue_t& que,RS_Environment::ptr_t evn)
		:msgQueue_(que),
		evn_(evn),
		stop_(false)
		{}

	~RSController(){}
	
	void run();
	void stop(){ this->stop_ = true; }

private:
	void getMsg_();
	void onMessage_(std::string& msg);
	msg_queue_t& msgQueue_;
	bool stop_;
	boost::thread t_;
	RS_Environment::ptr_t evn_;
};


class RSCTRManager
{
public:
	typedef boost::ptr_vector<RSIController> CtrlVec_t;
	typedef boost::shared_ptr<RSCTRManager> ptr_t;

	static ptr_t create(RS_Environment::ptr_t evn)
	{
		ptr_t p(new RSCTRManager(evn));
		assert(p != NULL);
		return p;
	}

	RSCTRManager(RS_Environment::ptr_t evn);
	~RSCTRManager();
	void run();


private:

	CtrlVec_t ptrVec_;
};

#endif //RSContraller_H