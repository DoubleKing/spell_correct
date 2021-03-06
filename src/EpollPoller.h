/*************************************************************************
	> File Name: EpollPoller.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Fri 15 May 2015 02:09:12 AM PDT
 ************************************************************************/
#pragma once

#include "dynamic_thread_pool.h"
#include "NonCopyable.h"
#include "log.h"
#include "MyDic.h"
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
namespace wd
{
class ThreadPool;
class EpollPoller : NonCopyable
{
public:
	EpollPoller(int listenfd, DynamicThreadPool *threadpool);
	~EpollPoller();
	void loop();//启动epoll
	void unloop();//关闭epoll
private:

	void waitEpollFd();
	void handleConnection();//处理accept
	bool handleMessage(int peerfd);//处理msg

	const int epollfd_;
	const int listenfd_;
	bool isLooping_;
	typedef std::vector<struct epoll_event> EventList;
	EventList events_;//保存活跃的fd
	MyDic m_mydic;
	
	DynamicThreadPool * threadpool_;
};
}
