/*************************************************************************
	> File Name: Conditoin.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Sat 09 May 2015 12:05:13 AM PDT
 ************************************************************************/
#include "Condition.h"
#include "MutexLock.h"
#include <assert.h>
namespace wd
{
Condition::Condition(MutexLock & mutex)
	: mutex_(mutex)
{
	pthread_cond_init(&cond_,NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&cond_);
}
void Condition::wait()
{
	assert(mutex_.isLocked());
	pthread_cond_wait(&cond_, mutex_.getMutexPtr());
}
void Condition::notify()
{
	pthread_cond_signal(&cond_);
}
void Condition::notifyall()
{
	pthread_cond_broadcast(&cond_);
}
}
