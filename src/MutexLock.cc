/*************************************************************************
	> File Name: MutexLock.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Fri 08 May 2015 08:44:32 PM PDT
 ************************************************************************/
#include "MutexLock.h"

extern wd::Logger g_log;
namespace wd
{
MutexLock::MutexLock()
	:isLocking_(false)
{
	if(0 != pthread_mutex_init(&mutex_,NULL))
	{
		g_log.addLog(5, "MutexLock", "pthread_mutex_init failed");
		exit(EXIT_FAILURE);
	}
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&mutex_);
}

int MutexLock::lock()
{
	g_log.addLog(5, "MutexLock:addr", "&mutex_:%x",&mutex_);
	if(0 != pthread_mutex_lock(&mutex_))
	{
		g_log.addLog(5, "MutexLock", "pthread_mutex_lock failed");
		return RET_ERROR;
	}
	g_log.addLog(5, "MutexLock", "pthread_mutex_lock success");
	isLocking_ = true;
	return RET_OK;
}

void  MutexLock::unlock()
{
	pthread_mutex_unlock(&mutex_);
	g_log.addLog(5, "MutexLock", "pthread_mutex_unlock success");
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
