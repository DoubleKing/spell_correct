/*************************************************************************
	> File Name: ThreadPool.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 05:44:25 AM PDT
 ************************************************************************/
#pragma once

#include "Noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "MyConf.h"
#include <vector>
#include <queue>
namespace wd
{
class Thread;

class ThreadPool : private Noncopyable
{
public:
	ThreadPool( std::size_t threadsNum);
	~ThreadPool();

	void start();
	void stop();
	void addTask(Task * task);
	Task * getTask();
	void runInThread();

private:
	std::vector<Thread *> threadsVec_;
	std::queue<Task> tasks_;
	MutexLock mutex_;
	Condition cond_;
	std::size_t threadsNum_;
	bool isStarting_;

	//MyCacheThread cacheThread_;
	MyConf& conf_;
};

}//end namespace wd

