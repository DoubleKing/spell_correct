/*************************************************************************
	> File Name: TcpServer.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Sun 17 May 2015 07:40:46 PM PDT
 ************************************************************************/
#include "TcpServer.h"
namespace wd
{
int createSocketFd()
{
	int fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(fd == -1)
	{
		fprintf(stderr,"create socket fd error\n");
		exit(EXIT_FAILURE);
	}
	return fd;
}
TcpServer::TcpServer(const MyConf& conf)
	:sockfd_(createSocketFd()),
	 mydic_(conf),
	 threadPool_(5,mydic_),
	 poller_(sockfd_.fd(),threadPool_)
{
	std::string ip = conf.conf_.find("myip")->second;
	std::string port0 = conf.conf_.find("myport")->second;
	int port1 = std::stoi(port0);
	uint16_t port =(uint16_t)port1;
	//std::cout << port<< std::endl;
	InetAddress addr(ip,port);

	sockfd_.setTcpNoDelay(false);
	sockfd_.setReusePort(true);
	sockfd_.setReuseAddr(true);
	sockfd_.setKeepAlive(false);

	sockfd_.bindAddress(addr);
	sockfd_.listen();
}

void TcpServer::start()
{
	threadPool_.start();
	poller_.loop();
}
}
