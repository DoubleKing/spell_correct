/*************************************************************************
	> File Name: MutexLock.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Fri 08 May 2015 08:44:32 PM PDT
 ************************************************************************/
#include "MutexLock.h"

namespace wd
{
MutexLock::MutexLock()
	:isLocking_(false)
{
	pthread_mutex_init(&mutex_,NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&mutex_);
}

void MutexLock::lock()
{
	pthread_mutex_unlock(&mutex_);
	isLocking_ = true;
}

void  MutexLock::unlock()
{
	pthread_mutex_unlock(&mutex_);
	isLocking_ = false;
}

bool MutexLock::isLocked()
{
	return isLocking_;
}

pthread_mutex_t* MutexLock::getMutexPtr()
{
	return &mutex_;
}
}
