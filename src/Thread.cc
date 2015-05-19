
#include "Thread.h"

namespace wd
{
Thread::Thread(ThreadCallback callback)
	: threadId_(0),
	  callback_(callback),
	  isRunning_(false)
{}

Thread::~Thread()
{
	pthread_detach(pthId_);
}

void Thread::start()
{
	pthread_create(&pthId_,NULL, runInThread, this);
	isRunning_ = true;
}

void Thread::join()
{
	pthread_join(pthId_, NULL);
	isRunning_ = false;
}

void *Thread::runInThread(void *arg)
{
	Thread *pThread = static_cast<Thread *>(arg);
	pThread->callback_();

	return NULL;
}

}//end namespace wd
