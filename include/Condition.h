/*************************************************************************
	> File Name: Condition.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Sat 09 May 2015 12:01:02 AM PDT
 ************************************************************************/
#pragma once
#include <pthread.h>

namespace wd
{
class MutexLock;
class Condition
{
public:
	Condition(MutexLock & mutex);
	~Condition();

	void wait();
	void notify();
	void notifyall();
private:
	MutexLock &mutex_;
	pthread_cond_t cond_;
};
}
