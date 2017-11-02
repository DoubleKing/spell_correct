#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);
//printf 带缓冲，满一行才输出 
int main(int argc, const char *argv[])
{
    int peerfd = socket(AF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //localhost
    addr.sin_port = htons(8887);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

    do_service(peerfd);


    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};
	int epollfd;
	printf("input a word : ");
	fflush(stdout);
	struct epoll_event ev, events[10];
	epollfd = epoll_create1(0);
	if(epollfd == -1)
	{
		ERR_EXIT("epoll_crearel");
	}
	ev.events = EPOLLIN;
	ev.data.fd = STDIN_FILENO;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &ev) == -1) {
		ERR_EXIT("epoll_ctl: STDIN_FILENO");
	}
	ev.events = EPOLLIN;
	ev.data.fd = sockfd;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
		ERR_EXIT("epoll_ctl: sockfd");
	}
    while(1)
    {
		int nfds = epoll_wait(epollfd, events, 10, -1);	
		for(int n = 0; n < nfds; ++n)
		{
			if(events[n].data.fd == STDIN_FILENO)
			{
				int nread = read(STDIN_FILENO, sendbuf, 1023);
				if(nread > 0)
				{
					send(sockfd,sendbuf,strlen(sendbuf),0);
					
				}
			}
			if(events[n].data.fd == sockfd)
			{
				int nread = read(sockfd, recvbuf, sizeof recvbuf);
    		    if(nread == -1)
    		    {
    		        if(errno == EINTR)
    		            continue;
    		        ERR_EXIT("read");
    		    }
    		    else if(nread == 0)
    		    {
    		        printf("\nserver close!\n");
    		        close(sockfd);
    		        exit(EXIT_SUCCESS);
    		    }
				printf("query result : %s\n", recvbuf);
				printf("input a word : ");
				fflush(stdout);
				
			}
			memset(recvbuf, 0, sizeof recvbuf);
			memset(sendbuf, 0, sizeof sendbuf);
		}
#if 0
        printf("input a word : ");
		//fgets(sendbuf,sizeof sendbuf,stdin);
		//sendbuf[strlen(sendbuf)-1]='\0';
		scanf("%s",sendbuf);
       // write(sockfd, sendbuf, strlen(sendbuf));
		send(sockfd,sendbuf,strlen(sendbuf),0);
        //read
        int nread = read(sockfd, recvbuf, sizeof recvbuf);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0)
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }

        printf("query result : %s\n", recvbuf);

        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
#endif
    }
}




