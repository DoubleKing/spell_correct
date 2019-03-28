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
#include "NonCopyable.h"
#include "Settings.h"
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

//using namespace inifile;

namespace wd
{
class TcpServer : NonCopyable
{
public:
	TcpServer(const SettingData &setting_data);
	void start();
private:
	Socket sockfd_;
	MyDic mydic_;
	ThreadPool threadPool_;
	EpollPoller poller_;
};

}
