#include "RS_TcpEvent.h"
#include "RS_Msg_Processor.h"


msg_queue_t RS_TcpEvent::msgQueue_; 
RS_TcpEvent::RS_TcpEvent()
{
	open_handler = boost::bind(&RS_TcpEvent::openHandler, this, boost::placeholders::_1);
  close_handler= boost::bind(&RS_TcpEvent::closeHandler, this, boost::placeholders::_1);
  read_handler= boost::bind(&RS_TcpEvent::readHandler, this, boost::placeholders::_1, 
  		boost::placeholders::_2);

  write_handler= boost::bind(&RS_TcpEvent::writeHandler, this, boost::placeholders::_1,
  		boost::placeholders::_2);
}

RS_TcpEvent::~RS_TcpEvent()
{

}

void RS_TcpEvent::openHandler(tcp_session::ptr_t session)
{
	static const int keepalive = 1;
	static const int keepidle = 180;
	static const int keepinterval = 5;
	static const int keepcount = 5;
	 try {
            assert(!setsockopt(session->sock().native(), SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(keepalive)));
            assert(!setsockopt(session->sock().native(), IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(keepidle)));
            assert(!setsockopt(session->sock().native(), IPPROTO_TCP, TCP_KEEPINTVL, &keepinterval, sizeof(keepinterval)));
            assert(!setsockopt(session->sock().native(), IPPROTO_TCP, TCP_KEEPCNT, &keepcount, sizeof(keepcount)));
            session->sock().set_option(boost::asio::ip::tcp::no_delay(true));
            //设置超时
            RSEntry::EntryPtr_t entry(new RSEntry(session));
            RSEntry::g_connectionBuckets.back().insert(entry);
            RSEntry::WeakEntryPtr_t weakEntry(entry);
            session->setContext(weakEntry);

            iINFO<<"[TCP SESSION]:CONNECTED:"
                 <<session->sock().remote_endpoint().address()<<'\t'
                 <<session->sock().native()
                 <<std::endl;
        }
        catch (std::exception & ex) {
            iWARN<<"[TCP SESSION]:OPEN:"<<ex.what()<<std::endl;
            session->close();
        }
}

void RS_TcpEvent::closeHandler(tcp_session::ptr_t session)
{
	try {
        iWARN<<"[TCP SESSION]:CLOSE:"<<session->sock().native()<<std::endl;
    }
    catch (std::exception & ex) {
        iWARN<<"[TCP SESSION]:CLOSE:"<<ex.what()<<std::endl;
    }
}

void RS_TcpEvent::readHandler(tcp_session::ptr_t session, size_t len)
{
	try {
          std::string recvdata(session->rbuff().peek(), len);
          assert(!session->getContext().empty());

          iINFO<<"[RECV MSGHEAD]:"
            <<recvdata
            <<std::endl;
          RSEntry::WeakEntryPtr_t weakEntry(boost::any_cast<RSEntry::WeakEntryPtr_t>(session->getContext()));
          RSEntry::EntryPtr_t entry(weakEntry.lock());
          if (entry)
          {
             RSEntry::g_connectionBuckets.back().insert(entry);
          }
          _buildMessage(session, recvdata);
          
    }
    catch (std::exception & ex) {
        iWARN<<"[TCP SESSION]:READ:"<<ex.what()<<std::endl;
    }
}

void RS_TcpEvent::writeHandler(tcp_session::ptr_t session, size_t len)
{
	using boost::asio::buffer_cast;

     try{
		 iINFO<<"[SERVER SEND]:"
            <<iegad::string_ex::bin_tostr(buffer_cast<const char*>(session->wbuff().data()), len)
            <<std::endl;
    }
    catch (std::exception & ex) {
        iWARN<<"[TCP SESSION]:WRITE:"<<ex.what()<<std::endl;
    }

}

void RS_TcpEvent::_buildMessage(tcp_session::ptr_t session, const std::string msg)
{
	 RSMsgPocessor::ptr_t proc = RSMsgPocessor::create(msg, msgQueue_);
   proc->process(session);
}