#include "RS_TimeItime.h"


RSTimeItime::RSTimeItime(int timeId, int sec, TimeHandler callback, int reapteTimes, RSTimeItime::ioPtr_t iosv) :
timeId_(timeId), sec_(sec), timeHandler_(callback), reapteTimes_(reapteTimes),
time_(*iosv, boost::posix_time::seconds(sec)), stop_(false)

{

	time_.async_wait(boost::bind(&RSTimeItime::callback_, this, boost::asio::placeholders::error, &time_));

}

RSTimeItime::~RSTimeItime()
{
}
//重复次数为-1表示无限循环，大于零时表示要执行的次数
 RSTimeItime::ptr_t RSTimeItime::create(int timeId, int sec, TimeHandler callback, int reapteTimes_, RSTimeItime::ioPtr_t time)
{
	RSTimeItime::ptr_t p(new RSTimeItime(timeId, sec, callback, reapteTimes_, time));
	assert(p != NULL);
	return p;
}

void RSTimeItime::callback_(const boost::system::error_code& e, RSTimeItime::deadline_timer* t)
{
	if (isStop_())
	{
		return;
	}
	this->timeHandler_();
	t->expires_at(t->expires_at() + boost::posix_time::seconds(this->sec_));
	t->async_wait(boost::bind(&RSTimeItime::callback_, this, boost::asio::placeholders::error, t));
	reapteTime_();
}

void RSTimeItime::stop()
{
	this->stop_ = true;
}

void RSTimeItime::reapteTime_()
{
	if (reapteTimes_ > 0)
	{
		reapteTimes_--;
	}
}

bool RSTimeItime::isStop_()
{
	return reapteTimes_ == 0 ? this->stop_ = true : this->stop_;
}