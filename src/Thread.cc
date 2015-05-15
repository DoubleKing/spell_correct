/*********************************
 *@fileName: Thread.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-05-08 11:08:04
**********************************/

#include "Thread.h"

namespace wd
{
Thread::Thread()
	: pthId_(0),
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
	pThread->run();

	return NULL;
}

}//end namespace wd
