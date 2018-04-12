
#include "ThreadPool.h"
namespace wd
{
ThreadPool::ThreadPool(
		std::size_t threadsNum,
		MyDic &mydic
		)
	: cond_(mutex_),
	  threadsNum_(threadsNum),
	  isStarted_(false),
	  mydic_(mydic)
{
	for(std::size_t idx = 0; idx != threadsNum_; ++idx)
	{
		Thread *pThread = new Thread(std::bind(&ThreadPool::runInThread,this));
		threads_.push_back(pThread);
	}
}

ThreadPool::~ThreadPool()
{
	for(;threads_.size() > 0; threads_.pop_back())
	{
		delete threads_.back();
	}
}

void ThreadPool::start()
{
	std::vector<Thread *>::iterator it = threads_.begin();
	for(; it != threads_.end(); ++it)
	{
		(*it)->start();
	}
	isStarted_ = true;
}

void ThreadPool::addTask(Task task)
{
	MutexLockGuard mutexGuard(mutex_);
	queue_.push(task);
	cond_.notify();
}

Task ThreadPool::getTask()
{
	MutexLockGuard mutexGuard(mutex_);
	while(queue_.empty())
		cond_.wait();
	Task tmp = queue_.front();
	queue_.pop();
	return tmp ;
}

void ThreadPool::runInThread()
{
	std::cout <<"Thread  Run "<<std::endl;
	while(1){
		Task task = getTask();
		std::cout <<"get task"<<std::endl;
		task.execute();
	}
}
}//end namespace wd
