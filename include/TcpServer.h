/*************************************************************************
	> File Name: TcpServer.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Sun 17 May 2015 07:32:39 PM PDT
 ************************************************************************/
#pragma once

#include "EpollPoller.h"
#include "ThreadPool.h"
#include "Socket.h"
#include "NonCopyable"
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

namespace wd
{
class TcpServer : NonCopyable
{
public:
	TcpServer(const Myconf &conf);
	void start();
private:
	Socket sockfd_;
	MyDic mydic_;
	ThreadPool threadPool_;
	EpollPoller poller_;
};

}
