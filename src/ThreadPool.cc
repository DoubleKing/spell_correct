
#include "ThreadPool.h"
namespace wd
{
ThreadPool::ThreadPool(
		std::size_t threadsNum,
		MyDic &mydic
		)
	: threadsNum_(threadsNum),
	  mydic_(mydic),
	  isStarting_(false)
{
	for(std::size_t idx = 0; idx != threadsNum_; ++idx)
	{
		Thread *pThread = new Thread(std::bind(&Threadpool::runInThread,this));
		threads_.push_back(pThread);
	}
}

void ThreadPool::start()
{
	std::vector<Thread *>::iterator it = threads_.begin();
	for(; it != threads_.end(); ++it)
	{
		(*it)->start();
	}
	isStarting_ = true;
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
	queue_.pop();
	return tmp ;
}

void ThreadPool::runInThread()
{
	while(1){
		Task task = getTask();
		task.execute();
	}
}
}//end namespace wd
