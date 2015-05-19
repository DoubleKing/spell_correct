/*************************************************************************
	> File Name: ThreadPool.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 05:44:25 AM PDT
 ************************************************************************/
#pragma once

#include "MyDic.h"
#include "Noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "MyConf.h"
#include <vector>
#include <queue>

namespace wd
{
class Thread;
class MyDic;

class ThreadPool : private Noncopyable
{
public:
	ThreadPool( std::size_t threadsNum /*,Cache &cache */,MyDic &mydic);

	void start();

	void addTask(Task task);
	Task  getTask();

	void runInThread(/*Cache &cache*/);

//	void update();
private:
	MutexLock mutex_;
	Condition cond_;

	std::queue<Task> queue_;

	std::size_t threadsNum_;
	std::vector<Thread * > threads_;
	bool isStarted_;

//	Cache cache_;

public:
	MyDic &mydict_;
	
};

}//end namespace wd

