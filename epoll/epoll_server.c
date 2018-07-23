#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int startup(short port)
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(3);
    }
    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);
    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        perror("bind");
        exit(4);
    }
    if(listen(sock,5) < 0)
    {
        perror("listen");
        exit(5);
    }
    return sock;
}

void handler_event(int epfd,struct epoll_event revs[],int num,int listen_sock)
{
    struct epoll_event ev;
    int i = 0;
    for(; i < num; ++i)
    {
        int fd = revs[i].data.fd;
        if(fd == listen_sock && (revs[i].events & EPOLLIN))
        {// listen_sock OK
            struct sockaddr_in client;
            socklen_t len = sizeof(client);
            int new_sock = accept(fd,(struct sockaddr*)&client,&len);
            if(new_sock < 0)
            {
                perror("accept");
                continue;
            }
            printf("get new client...\n");
            // 链接建立好以后,不可以直接read,可能会造成阻塞
            ev.events = EPOLLIN;
            ev.data.fd = new_sock;
            epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
            continue;
        }
        // 不是listen_sock, 有可能是读时间就绪,也可能是写时间就绪,也可能是同时就绪
        // 不过我们这里只先关心读事件,再关心写时间
        // 因为HTTP是基于请求应答的,必须先关心读事件
        if(revs[i].events & EPOLLIN)
        {
            char buf[1024*10] = {0};
            ssize_t s = read(fd,buf,sizeof(buf)-1);
            if(s > 0)
            {
                buf[s] = '\0';
                printf("%s\n",buf);
                // 将时间读完成以后,应该讲时事件改为关心写时间
                // 先关心读再关心写是为了控制读写顺序
                ev.events = EPOLLOUT;
                ev.data.fd = fd;
                epoll_ctl(epfd,EPOLL_CTL_MOD,fd,&ev);
            }
            else if(s == 0)
            {
                printf("client quit...\n");
                close(fd);
                epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
            }
            else
            {
                perror("read");
                close(fd);
                epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
            }
            continue;
        }
        if(revs[i].events & EPOLLOUT)
        {
            // 写时间
            const char* echo = "HTTP/1.1 200 OK\r\n\r\n<html>hello epoll server</html>\r\n";
            write(fd,echo,strlen(echo));
            close(fd);
            epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
        }
    }
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [port]\n",argv[0]);
        return 1;
    }
    int epfd = epoll_create(256);
    if(epfd < 0)
    {
        perror("epoll_create");
        return 2;
    }
    int listen_sock = startup(atoi(argv[1]));
    // 1.将listen_sock加入到epoll中
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&ev);

    // 事件循环
    struct epoll_event revs[128];
    int n = sizeof(revs)/sizeof(revs[0]);
    int timeout = 12345;
    int num = 0;
    while(1)
    {
        switch((num = epoll_wait(epfd,revs,n,timeout)))
        {
        case -1:
            perror("epoll_wait");
            break;
        case 0:
            printf("timeout...\n");
            break;
        default:
            handler_event(epfd,revs,num,listen_sock);
            break;
        }
    }

    close(epfd);
    close(listen_sock);
    return 0;
}
