#include <iostream>
#include <string>
#include <string/iegad_string.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
//#include "iegad_string.hpp"
#include <vector>
//#include <boost/signal.hpp> 
#include <net/iegad_tcp_event.hpp>
#include <net/iegad_tcp_session.hpp>
#include <net/iegad_tcp_server.hpp>

void helloworld() {  
    std::cout << "Hello, World!(func)" << std::endl;  
} 

//boost::signal<void ()>sig;
class AA
{
public:
	void func()
	{
		std::cout<<"func"<<std::endl;
	}

};

class TSTcpEvent:public iegad::net::tcp_event
{
public:
    typedef boost::shared_ptr<iegad::net::tcp_session> tcp_session;
    typedef boost::shared_ptr<TSTcpEvent> ptr_t;
    TSTcpEvent()
    {
	open_handler=boost::bind(&TSTcpEvent::openhandler, this,boost::placeholders::_1);
        close_handler =boost::bind(&TSTcpEvent::closehandler, this,boost::placeholders::_1);
	read_handler = boost::bind(&TSTcpEvent::readhandler, this,boost::placeholders::_1, boost::placeholders::_2);
	write_handler = boost::bind(&TSTcpEvent::writehandler, this,boost::placeholders::_1, boost::placeholders::_2);
    }
    static ptr_t Create()
    {
	ptr_t p(new TSTcpEvent);
	return p;
    }	

    void readhandler(tcp_session session,size_t len){}
    void writehandler(tcp_session session, size_t len){}
    void openhandler(tcp_session session){}
    void closehandler(tcp_session session){}
};


int main()
{
	std::string str("12345678");

	
	iegad::string_ex::start_with(str, "78");
//	int *p = new int(10);
//	if(p == nullptr)
//	{
//		std::cout<<"p is nullptr"<<std::endl;
//	}
	AA a;
	boost::function<void()> func = boost::bind(&AA::func, &a);
	func();

	


	
	std::vector<int> vec;
	for(int i=0;i<10;i++)
	{
		vec.push_back(i);
	}
//	sig.connect(&helloworld);  
//    	sig(); 
	for(auto i:vec)
	{
		std::cout<<i<<std::endl;
	}
	

	iegad::net::tcp_server<TSTcpEvent>::ptr_t host = iegad::net::tcp_server<TSTcpEvent>::Create(5188, 1);
        host->run();



	return 0;

}

