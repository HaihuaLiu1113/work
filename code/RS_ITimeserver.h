#ifndef RSITimeserver_H
#define RSITimeserver_H
#include <boost/function.hpp>
#include <boost/asio.hpp>

class RSITimeserver
{
public:
	typedef boost::function<void()> TimeHandler;
	typedef boost::asio::io_service io_service;
	typedef boost::shared_ptr<io_service> ioPtr;
	RSITimeserver(){}
	virtual~RSITimeserver(){}
	virtual void killAllTimer() = 0;
	virtual void killTimer(int timerId) = 0;
	virtual void setTimer(int timerId, int sec, TimeHandler callback, int reapttimes, io_service& ioserver) = 0;
};

#endif //RSITimeserver_H