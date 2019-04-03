#include "EpollPoller.h"
#include "Task.h"
#include "Settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>

extern wd::Logger g_log;
extern long g_ncpus;
extern wd::SettingData g_SettingData;

namespace
{
int createEpollFd()
{
    int epollfd = ::epoll_create1(0);
    if(epollfd == -1)
    {
        perror("create epoll fd error");
        exit(EXIT_FAILURE);
    }

    return epollfd;
}

void addEpollReadFd(int epollfd, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1)
    {
        perror("add epoll fd error");
        exit(EXIT_FAILURE);
    }
}

void delEpollReadFd(int epollfd, int fd)
{
    struct epoll_event ev;
    ev.data.fd = fd;
    //ev.events = EPOLLIN;
    if(epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev) == -1)
    {
        perror("del epoll fd error");
        exit(EXIT_FAILURE);
    }
}

int acceptConnFd(int listenfd)
{
    int peerfd = accept(listenfd, NULL, NULL);
    if(peerfd == -1)
    {
        perror("accept conn fd");
        exit(EXIT_FAILURE);
    }
    return peerfd;
}

//预览数据
ssize_t recvPeek(int sockfd, void *buf, size_t len)
{
    int nread;
    do
    {
        nread = ::recv(sockfd, buf, len, MSG_PEEK);
    }
    while(nread == -1 && errno == EINTR);

    return nread;
}
int anetPeerToString(int fd, char *ip, size_t ip_len, int *port) {
    struct sockaddr_storage sa;
    socklen_t salen = sizeof(sa);

    if (getpeername(fd,(struct sockaddr*)&sa,&salen) == -1) goto error;
    if (ip_len == 0) goto error;

    if (sa.ss_family == AF_INET) {
        struct sockaddr_in *s = (struct sockaddr_in *)&sa;
        if (ip) inet_ntop(AF_INET,(void*)&(s->sin_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin_port);
    } else if (sa.ss_family == AF_INET6) {
        struct sockaddr_in6 *s = (struct sockaddr_in6 *)&sa;
        if (ip) inet_ntop(AF_INET6,(void*)&(s->sin6_addr),ip,ip_len);
        if (port) *port = ntohs(s->sin6_port);
    } else if (sa.ss_family == AF_UNIX) {
        if (ip) strncpy(ip,"/unixsocket",ip_len);
        if (port) *port = 0;
    } else {
        goto error;
    }
    return 0;

error:
    if (ip) {
        if (ip_len >= 2) {
            ip[0] = '?';
            ip[1] = '\0';
        } else if (ip_len == 1) {
            ip[0] = '\0';
        }
    }
    if (port) *port = 0;
    return -1;
}

//通过预览数据 判断conn是否关闭
bool isConnectionClosed(int sockfd)
{
    char buf[1024];
    ssize_t nread = recvPeek(sockfd, buf, sizeof buf);
    if(nread == -1)
    {
        perror("recvPeek");
        exit(EXIT_FAILURE);
    }

    return (nread == 0);
}
}//end anonymous namespace

namespace wd
{
EpollPoller::EpollPoller(int listenfd ,DynamicThreadPool *threadpool)
: epollfd_(createEpollFd()),
  listenfd_(listenfd),
  isLooping_(false),
  events_(1024),
  m_mydic(g_SettingData.m_strDataPath),
  threadpool_(threadpool)
{
    addEpollReadFd(epollfd_, listenfd);
}

EpollPoller::~EpollPoller()
{
    ::close(epollfd_);
}


void EpollPoller::waitEpollFd()
{
    int nready;
    do
    {
        nready = ::epoll_wait(epollfd_, 
                              &*events_.begin(), 
                              static_cast<int>(events_.size()), 
                              5000);
    }while(nready == -1 && errno == EINTR);

    if(nready == -1)
    {
        perror("epoll wait error");
        exit(EXIT_FAILURE);
    }
    else if(nready == 0)
    {
        g_log.addLog(3, "waitEpollFd", "epoll timeout");
    }
    else
    {
        //当vector满时，扩充内存
        if(nready == static_cast<int>(events_.size()))
        {
            events_.resize(events_.size() * 2);
        }


        for(int ix = 0; ix != nready; ++ix)
        {
            if(events_[ix].data.fd == listenfd_)
            {
                if(events_[ix].events & EPOLLIN)
                    handleConnection();
            }
            else
            {
                if(events_[ix].events & EPOLLIN)
				{
                    if(!handleMessage(events_[ix].data.fd))
					{
						delEpollReadFd(epollfd_,events_[ix].data.fd);
						close(events_[ix].data.fd);
					}
				}
            }
        }
		//events_.empty();
    }

}

void EpollPoller::handleConnection()
{
	char ip[32]={0};
	int port;
    int peerfd = acceptConnFd(listenfd_);
	anetPeerToString(peerfd, ip, sizeof(ip), &port);
	g_log.addLog(5, "handleConnection", "new connection: %s/%d", ip, port);
    addEpollReadFd(epollfd_, peerfd);
}

bool EpollPoller::handleMessage(int peerfd)
{
	char buf[512];
	memset(buf,0,512);
	if(recv(peerfd,buf,sizeof(buf),0) > 0)
	{
		std::string expr(buf);
		Task task(expr, peerfd, m_mydic);
		threadpool_->Add([=]()mutable {task.execute();});
		return true;
	}
	else
	{
		return false;
	}

}

void EpollPoller::loop()
{
    isLooping_ = true;
    while(isLooping_)
    {
#if 0
		struct sockaddr_in addr;
		socklen_t len = sizeof addr;
		getsockname(listenfd_,(sockaddr *)&addr,&len);
		int port  = ntohs(addr.sin_port);
		std::cout << inet_ntoa(addr.sin_addr) << std::endl;
		std::cout << port <<std::endl;
		std::cout << listenfd_ <<std::endl;
#endif
        waitEpollFd();
    }

}

void EpollPoller::unloop()
{
    isLooping_ = false;

}

}
