/*************************************************************************
	> File Name: ThreadPool.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 05:44:25 AM PDT
 ************************************************************************/
#pragma once
#include "Task.h"
#include "MyDic.h"
#include "NonCopyable.h"
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include <vector>
#include <queue>
#include <functional>
namespace wd
{
class MyDic;

class ThreadPool : private NonCopyable
{
public:
	ThreadPool( std::size_t threadsNum /*,Cache &cache */,MyDic &mydic);
	//析构函数，释放资�?TODO
	~ThreadPool();
	void start();

	void addTask(Task task);
	Task * getTask();

	void runInThread(/*Cache &cache*/);
	int get_queue_size()
	{
		return queue_.size();
	}

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
	MyDic &mydic_;
	
};

}//end namespace wd

