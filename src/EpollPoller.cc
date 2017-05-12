#include "EpollPoller.h"
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
	//std::cout <<"accept"<<std::endl;

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
EpollPoller::EpollPoller(int listenfd ,ThreadPool &threadpool)
: epollfd_(createEpollFd()),
  listenfd_(listenfd),
  isLooping_(false),
  events_(1024),
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
	//std::cout<<"accept"<<std::endl;
    int nready;
    do
    {
		//std::cout << "nready" <<nready <<std::endl;
        nready = ::epoll_wait(epollfd_, 
                              &*events_.begin(), 
                              static_cast<int>(events_.size()), 
                              5000);
    }while(nready == -1 && errno == EINTR);
	//std::cout << "nready" <<nready <<std::endl;

    if(nready == -1)
    {
        perror("epoll wait error");
        exit(EXIT_FAILURE);
    }
    else if(nready == 0)
    {
        printf("epoll timeout.\n");
    }
    else
    {
		//std::cout<<"accept"<<std::endl;
        //当vector满时，扩充内存
        if(nready == static_cast<int>(events_.size()))
        {
            events_.resize(events_.size() * 2);
        }


        for(int ix = 0; ix != nready; ++ix)
        {
            if(events_[ix].data.fd == listenfd_)
            {
				std::cout<<"listenfd_"<<std::endl;
                if(events_[ix].events & EPOLLIN)
                    handleConnection();
            }
            else
            {
                if(events_[ix].events & EPOLLIN)
				{
					std::cout<< "recv" <<std::endl;
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
	//std::cout<<"accept"<<std::endl;
    int peerfd = acceptConnFd(listenfd_);
    addEpollReadFd(epollfd_, peerfd);
}

bool EpollPoller::handleMessage(int peerfd)
{
	char buf[512];
	memset(buf,0,512);
	if(recv(peerfd,buf,sizeof(buf),0) > 0)
	{
		std::string expr(buf);
		Task task(expr,peerfd,threadpool_.mydic_);
		threadpool_.addTask(task);
		//std::cout << threadpool_.get_queue_size()<<std::endl;
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
	//std::cout << "EpollPoller loop" << std::endl;
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
