/*************************************************************************
	> File Name: MutexLock.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Fri 08 May 2015 12:56:10 AM PDT
 ************************************************************************/
#pragma once

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"
namespace wd{

class MutexLock : NonCopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	bool isLocked();
	pthread_mutex_t* getMutexPtr();
private:
	pthread_mutex_t mutex_;
	bool isLocking_;
};

class MutexLockGuard//把MutexLock上锁解锁交给Guard来做
					//防止中断异常
{
public:
	MutexLockGuard(MutexLock &mutex)
		:mutex_(mutex)
	{
		mutex_.lock();
	}

	~MutexLockGuard()
	{
		mutex_.unlock();
	}
private:
	MutexLock &mutex_;
};
}
