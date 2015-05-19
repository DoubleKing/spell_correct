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
	typedef std::function<void(/*Cache &*/)> ThreadCallback;

	Thread(ThreadCallback callback/* ,Cache &cache*/);
	 ~Thread();

	void start();
	void join();
	
//	Cache &get_cache();

private:
	static void *runInThread(void *);

	pthread_t threadId_;
	bool isRunning_;
	ThreadCallback callback;
//	Cache cache_;
};

}// end namespace wd



