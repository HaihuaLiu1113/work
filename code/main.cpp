#include <iostream>
#include "RS_Environment.h"
#include "RS_TcpServer.h"
#include "RS_User.h"


const std::string RS_Environment::path_ = "./config.xml";

RSEntry::WeakConnectionList_t RSEntry::g_connectionBuckets;
UserInfo::UserList UserInfo::userList_;
 std::mutex UserInfo::mutex_;
int
main(int argc, char *argv[])
{
    std::setlocale(LC_ALL, argc >= 2 ? argv[1] : "zh_CN.UTF-8");
    RS_TcpServer host(argv[0]);
    host.run();
    exit(0);
}