
#include "Thread.h"

namespace wd
{
Thread::Thread(ThreadCallback callback)
	: threadId_(0),
	  isRunning_(false),
	  callback_(callback)
{}

Thread::~Thread()
{
	pthread_detach(threadId_);
}

void Thread::start()
{
	pthread_create(&threadId_,NULL, runInThread, this);
	isRunning_ = true;
}

void Thread::join()
{
	pthread_join(threadId_, NULL);
	isRunning_ = false;
}

void *Thread::runInThread(void *arg)
{
	Thread *pThread = static_cast<Thread *>(arg);
	pThread->callback_();

	return NULL;
}

}//end namespace wd
