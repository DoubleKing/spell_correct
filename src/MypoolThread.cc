/*********************************
 *@fileName: MypoolThread.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-05-09 07:47:20
**********************************/

#include "MypoolThread.h"

namespace wd
{

void MypoolThread::run()
{
	threadpool_.runInThread();
}

}//end namespace wd
