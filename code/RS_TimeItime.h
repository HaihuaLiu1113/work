#ifndef RSTimeItime_H
#define RSTimeItime_H
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> 
#include <boost/bind.hpp>
#include <tools/iegad_log.hpp>

class RSTimeItime
{
public:
	typedef boost::asio::io_service io_service;
	typedef boost::shared_ptr<io_service> ioPtr_t;
	typedef boost::asio::deadline_timer deadline_timer;
	typedef boost::function<void()> TimeHandler;
	typedef boost::shared_ptr<RSTimeItime> ptr_t;

	RSTimeItime(int timeId, int sec, TimeHandler callback, int reapteTimes_, io_service& iosv);
	~RSTimeItime();
	static ptr_t create(int timeId, int sec, TimeHandler callback, int reapteTimes_, io_service& io);
	
	void stop();

private:
	void callback_(const boost::system::error_code& e, deadline_timer* t);
	void reapteTime_();
	bool isStop_();

	int timeId_;
	int sec_;
	TimeHandler timeHandler_;
	int reapteTimes_;
	deadline_timer time_;
	bool stop_;

};

#endif //RSTimeItime_H