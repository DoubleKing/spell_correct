
#include "ThreadPool.h"
#include "Thread.h"
#include "MypoolThread.h"
#include "Task.h"
#include "MyConf.h"
#include "MutexLock.h"
namespace wd
{
ThreadPool::ThreadPool(
		std::size_t threadsNum,
		MyConf conf
		)
	: threadsNum_(threadsNum),
	  conf_(conf)
	  isStarting_(false)
{
	for(std::size_t idx = 0; idx != threadsNum_; ++idx)
	{
		Thread *pThread = new MypoolThread(*this);
		threadsVec_.push_back(pThread);
	}
}

void ThreadPool::start()
{
	std::vector<Thread *>::iterator it = threadsVec_.begin();
	for(; it != threadsVec_.end(); ++it)
	{
		(*it)->start();
	}
	isStarting_ = true;
}

void ThreadPool::stop()
{
	if(!isStarting_ == false)
		return;

	if(isStarting_)
	{
		while(!buffer_.empty())
			buffer_.deleteElement();//清空队列

		std::vector<Thread *>::iterator it = threadsVec_.begin();
		for(; it != threadsVec_.end(); ++it)
		{
			(*it)->join();
		}
		threadsVec_.clear();
	}
	isStarting_ = false;
}

void ThreadPool::addTask(Task task)
{
	MutexLockGuard mutexGuard(mutex_);
	tasks_.push(task);
	cond_.notify();
}

Task ThreadPool::getTask()
{
	MutexLockGuard mutexGuard(mutex_);
	while(tasks_.empty())
		cond_.wait();
	Task tmp = queue_.front();
	tasks_.pop();
	return tmp ;
}

void ThreadPool::runInThread()
{
	while(1){
		Task task = getTask();
		task->process();
	}
}
	  
ThreadPool::~ThreadPool()
{
	stop();
	
}

}//end namespace wd
