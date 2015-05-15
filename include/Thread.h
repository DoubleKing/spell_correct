/*************************************************************************
	> File Name: Thread.h
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 05:41:27 AM PDT
 ************************************************************************/
#pragma once

#include "Noncopyable.h"
#include <pthread.h>

namespace wd
{
class Thread : private Noncopyable //public继承：接口继承；private继承：实现继承
{//实现了它的对象语义
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();
	virtual void run()=0;

	static void *runInThread(void *);

private:
	pthread_t pthId_;
	bool isRunning_;
};

}// end namespace wd



