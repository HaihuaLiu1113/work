#include "RS_TimeServer.h"

std::map<int, RSTimeItime::ptr_t> RSTimeServer::timeList_;

RSTimeServer::RSTimeServer()
{

}

RSTimeServer::~RSTimeServer()
{

}

void RSTimeServer::killAllTimer() 
{
	std::unique_lock<std::mutex> lock(mutex_);
	auto iter = timeList_.begin();
	for (; iter != timeList_.end(); ++iter)
	{
		iter->second->stop();
		iter = timeList_.erase(iter);
	}

}
void RSTimeServer::killTimer(int timerId)
{
	std::unique_lock<std::mutex> lock(mutex_);
	auto iter = timeList_.find(timerId);
	if (iter != timeList_.end())
	{
		iter->second->stop();
		timeList_.erase(iter);
	}
}

void RSTimeServer::setTimer(int timerId,int sec, TimeHandler callback, int reapttimes, io_service& ioserver)
{ 
	std::unique_lock<std::mutex> lock(mutex_);
	RSTimeItime::ptr_t item = RSTimeItime::create(timerId, sec, callback, reapttimes, ioserver);
	if (timeList_.find(timerId) == timeList_.end())
	{
		timeList_.insert(std::make_pair(timerId, item));
	}
}

