#ifndef RS_TcpServer_H
#define RS_TcpServer_H

#include <tools/iegad_log.hpp>
#include <net/iegad_tcp_server.hpp>
#include "RS_Environment.h"
#include "RS_TcpEvent.h"
#include "RS_TimeServer.h"
#include "RS_Entry.h"
#include "RS_Common.h"
#include "RS_Controller.h"
#include "RS_DBServer.h"

class RS_TcpServer
{
public:
	typedef RS_Environment::ptr_t evnPtr_t;
	typedef boost::shared_ptr<RSITimeserver> TimeServer;
	typedef iegad::net::tcp_server<RS_TcpEvent>::io_service io_service;
	//typedef boost::asio::io_service io_service;
	RS_TcpServer( char* argv0);
	void initTimeServer();
	~RS_TcpServer();
	void run();
	void onTime();

private:
	iegad::tools::_LOG log_;
	evnPtr_t evnptr_;
	iegad::net::tcp_server<RS_TcpEvent>::ptr_t host_;
	TimeServer timeserver_;
	RSCTRManager::ptr_t ctrlmg_;

	RSDBServerManager DBserver_;

};


#endif //RS_TcpServer_H