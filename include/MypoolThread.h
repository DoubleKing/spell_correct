/*********************************
 *@fileName: MyPoolThread.h
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-05-09 07:44:21
**********************************/

#ifndef WD_MYPOOLTHREAD_H
#define WD_MYPOOLTHREAD_H

#include "Thread.h"
#include "ThreadPool.h"

namespace wd
{

class ThreadPool;

class MypoolThread : public Thread
{
public:
	MypoolThread(ThreadPool &threadpool) 
		: threadpool_(threadpool)
	{}

	void run();

private:
	ThreadPool &threadpool_;
};

}//end namespace wd


#endif
