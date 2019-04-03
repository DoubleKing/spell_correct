/*************************************************************************
	> File Name: TcpServer.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Sun 17 May 2015 07:32:39 PM PDT
 ************************************************************************/
#pragma once

#include "EpollPoller.h"
#include "dynamic_thread_pool.h"
#include "Socket.h"
#include "NonCopyable.h"
#include "Settings.h"
#include "MyDic.h"
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
	DynamicThreadPool *m_pThreadPool_;
	EpollPoller poller_;
};

}
