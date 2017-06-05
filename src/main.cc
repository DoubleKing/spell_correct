/*************************************************************************
	> File Name: testmain.cc
	> Author: DoubleKing
	> Mail:971774262@qq.com 
	> Created Time: Thu 14 May 2015 07:18:34 PM PDT
 ************************************************************************/
#include "TcpServer.h"
#include "MyConf.h"
#include "MyDic.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
void daemonize(void) {
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
     * the 'logfile' is set to 'stdout' in the configuration file
     * it will not log at all. */
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
int main(int argc, char *argv[])
{
	repeatCheck();
	if(argc > 1 && strcmp(argv[1],"daemon") == 0)
		daemonize();
	wd::MyConf conf("./conf/conf.txt");
	conf.conf_show();
	//wd::MyDic dic(conf);
	//dic.show_dic();
	//dic.show_index();
	wd::TcpServer server(conf);
	server.start();

	return 0;
}
