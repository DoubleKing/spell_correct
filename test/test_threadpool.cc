#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include "../src/dynamic_thread_pool.h"
// top -H -p 查看线程数
using namespace wd;

int main(int argc, char * argv[])
{
	DynamicThreadPool * pThdPool = new DynamicThreadPool(4);
	for(int i = 0; i < 10; i++)
	{
		pThdPool->Add([i]{
				int temp = rand()%100;
				sleep(temp);
				std::cout << "task: " << i << "; sleep:"<< temp << std::endl;});
	}
	sleep(110);
	for(int i = 10; i < 20; i++)
	{
		pThdPool->Add([i]{
				int temp = rand()%100;
				sleep(temp);
				std::cout << "task: " << i << "; sleep:"<< temp << std::endl;});
	}
	sleep(1);
	for(int i = 20; i < 30; i++)
	{
		pThdPool->Add([i]{
				int temp = rand()%100;
				sleep(temp);
				std::cout << "task: " << i << "; sleep:"<< temp << std::endl;});
	}
	sleep(110);	
	delete pThdPool;
	
	return 0;
}
