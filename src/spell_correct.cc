/*************************************************************************
	> File Name: testmain.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:18:34 PM PDT
 ************************************************************************/
#include "TcpServer.h"
#include "MyDic.h"
#include "log.h"
#include "lru_cache.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>



#define 		MAXBUFSIZE 1024
char 			g_szWorkPath[MAXBUFSIZE];
wd::Logger 		g_log;
long 			g_ncpus = 0;
wd::SettingData g_SettingData;
wd::LRUCache<std::string,std::string>	g_LRUCache;

void init_ncpus()
{
  g_ncpus = sysconf(_SC_NPROCESSORS_CONF);
  if (g_ncpus < 1 || g_ncpus > INT32_MAX) {
    g_ncpus = 1;
  }
}



void daemonize(void) 
{
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}
void repeatCheck()
{
	int fd = open(".lock",O_WRONLY|O_CREAT);
	if(fd < 0)
	{
		exit(-1);
	}
	if(0 > flock(fd, LOCK_EX|LOCK_NB))
	{
		std::cout << "is already running" << std::endl;
		exit(-1);
	}
}
void getWorkPath()
{
	int count = readlink("/proc/self/exe", g_szWorkPath, MAXBUFSIZE);
	if(count < 0 || count >= MAXBUFSIZE)
	{
		printf("get path fail\n");
		exit(-1);
	}
	std::cout << g_szWorkPath << std::endl;
	char * tmp = strstr(g_szWorkPath,"bin/spell_correct");
	if(tmp == NULL)
	{
		printf("get work path fail\n");
		exit(-1);
	}
	*tmp = '\0';
}
int main(int argc, char *argv[])
{
	//repeatCheck();
	init_ncpus();
	if(argc > 1 && strcmp(argv[1],"daemon") == 0)
		daemonize();
	getWorkPath();
	
	std::string strSettingPath = std::string(g_szWorkPath) + std::string("/conf/spell_correct.ini"); 
	std::cout << strSettingPath << std::endl;
	//wd::SettingData setting_data(strSettingPath);
	g_SettingData.LoadSetting(strSettingPath);
	g_log.init(g_SettingData.m_intLogLevel,g_SettingData.m_strLogPath);
	g_LRUCache.init(20000);
	wd::TcpServer server(g_SettingData);
	server.start();

	return 0;
}
