#ifndef RSTimeServer_H
#define RSTimeServer_H
#include "RS_ITimeserver.h"
//#include "RSTimeItime.h"

#include "RS_TimeItime.h"
#include <map>
#include <mutex>

class RSTimeServer :public RSITimeserver
{
public:

	RSTimeServer(/*ioPtr& ioserver*/);
	~RSTimeServer();
	virtual void killAllTimer();
	virtual void killTimer(int timerId);
	virtual void setTimer(int timerId, int sec, TimeHandler callback, int reapttimes, io_service& ioserver);

private:
	std::mutex mutex_;
	static std::map<int, RSTimeItime::ptr_t> timeList_;
};

#endif //RSTimeServer_H