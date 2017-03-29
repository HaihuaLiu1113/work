#ifndef RSEntry_H
#define RSEntry_H
#include "boost/circular_buffer.hpp"
#include "net/iegad_tcp_session.hpp"
#include <boost/unordered_set.hpp>
#include <boost/circular_buffer.hpp>
class RSEntry
{
public:
	typedef iegad::net::tcp_session tcp_session;
	typedef boost::shared_ptr<RSEntry> EntryPtr_t;
	typedef boost::weak_ptr<RSEntry> WeakEntryPtr_t;
	typedef boost::unordered_set<EntryPtr_t> Bucket_t;
	typedef boost::circular_buffer<Bucket_t> WeakConnectionList_t;
	typedef boost::weak_ptr<tcp_session> WeakConnetionPtr_t;

	RSEntry(WeakConnetionPtr_t weakconn):weakconn_(weakconn)
	{

	}
	RSEntry(){}
	~RSEntry()
	{
		auto obj = weakconn_.lock();
		if (obj)
		{
			obj->close();
		}
	}
	static WeakConnectionList_t g_connectionBuckets;
private:
	WeakConnetionPtr_t  weakconn_;
	
};

#endif //RSEntry_H
