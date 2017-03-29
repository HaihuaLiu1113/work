#include "RS_TcpServer.h"

RS_TcpServer::RS_TcpServer(char* argv0)
	:timeserver_(new RSTimeServer), log_(argv0)//,timeserver_(new RSTimeServer)
{
	RSEntry::g_connectionBuckets.resize(6);

	evnptr_ = RS_Environment::create();
	assert(evnptr_->init());
	int port = evnptr_->getRoomServerPort();
	DBserver_.initData();
	host_ = iegad::net::tcp_server<RS_TcpEvent>::Create(port,1);
	ctrlmg_ = RSCTRManager::create(evnptr_);
	timeserver_->setTimer(CONN_TIMEOUT_ID, CONN_TIMEOUT_TIME/5, boost::bind(&RS_TcpServer::onTime, this), -1, host_->get());
	iINFO<<"[GPS SERVER]:INIT DONE\n";
}

RS_TcpServer::~RS_TcpServer()
{

}

void RS_TcpServer::run()
{
	host_->run();
	ctrlmg_->run();
}

void RS_TcpServer::initTimeServer()
{
	
}

void RS_TcpServer::onTime()
{
	RSEntry::g_connectionBuckets.push_back(RSEntry::Bucket_t());
}