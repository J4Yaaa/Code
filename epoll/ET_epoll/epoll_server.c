#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

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

void SetNoBlock(int fd)
{
    int f1 = fcntl(fd,F_GETFL);
    if(f1 < 0)
    {
        perror("fcntl F_GETFL");
        return;
    }
    fcntl(fd,F_SETFL,f1 | O_NONBLOCK);
}

void ProcessConnect(int listen_sock, int epfd)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
    if(new_sock < 0)
    {
        perror("accept");
        return;
    }
    printf("[client %d] connected\n",new_sock);

    SetNoBlock(new_sock);
    struct epoll_event event;
    event.data.fd = new_sock;
    event.events = EPOLLIN | EPOLLET;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&event);
    if(ret < 0)
    {
        perror("epoll_ctl ADD");
        return;
    }
    return;
}

ssize_t NoBlockRead(int fd,char* buf,int maxsize)
{
    ssize_t total_size = 0;
    while(1)
    {
        ssize_t cur_size = read(fd,buf+total_size,maxsize);
        total_size += cur_size;
        if(cur_size < maxsize || errno == EAGAIN)
        {// 如果 cur_size<1024, 证明已经读完了,否则的话一定会将换城区装满的
         // 如果errno为EAGAIN,证明是非阻塞的输入输出,但是当前并没有数据
            break;
        }
    }
    buf[total_size] = '\0';
    return total_size;
}

void ProcessRequest(int new_sock,int epfd)
{
    char buf[1024] = {0};
    ssize_t read_size = NoBlockRead(new_sock,buf,sizeof(buf)-1);
    if(read_size < 0)
    {
        perror("read");
        return;
    }
    else if(read_size == 0)
    {
        // 表示对端已经退出
        int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,new_sock,NULL);
        if(ret < 0)
        {
            perror("epoll_ctl DEL");
            return;
        }
        close(new_sock);
        printf("client disconnected...\n");
    }
    printf("[client %d]> %s\n",new_sock,buf);
    write(new_sock,buf,strlen(buf));
    return;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [port]\n",argv[0]);
    }
    // 1.初始化服务器
    int listen_sock = startup(atoi(argv[1]));
    if(listen_sock < 0)
    {
        printf("Server startup faild\n");
        return 1;
    }
    int epfd = epoll_create(10);
    if(epfd < 0)
    {
        perror("epoll_create");
        return 1;
    }
    // 2.将listen_sock设置为非阻塞,ET模式下要求非阻塞
    SetNoBlock(listen_sock);
    // 3.构建epoll结构体,将listen_sock加入到epfd当中,注意,listen_sock只关心写事件
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET; //加上EPOLLET宏才是边缘触发
    event.data.fd = listen_sock;
    int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&event);
    if(ret < 0)
    {
        perror("epoll_ctr ADD");
        return 1;
    }
    // 4.进行事件循环
    while(1)
    {
        // a) 表示就绪队列
        struct epoll_event events[10];
        int size = epoll_wait(epfd,events,sizeof(events)/sizeof(events[0]),-1);
        if(size < 0)
        {
            perror("epoll_wait");
            return 1;
        }
        if(size == 0)
        {
            printf("timeout...");
            continue;
        }
        // b) 对已就绪的文件描述符进行相应的操作
        int i = 0;
        for(i = 0; i < size; ++i)
        {
            if(!(events[i].events & EPOLLIN))
            {// 当前只关心读事件,如果不是读事件,直接退出
                continue;
            }
            if(events[i].data.fd == listen_sock)
            {// listen_sock 进行accept
                ProcessConnect(listen_sock,epfd);
            }
            else
            {// new_sock 进行读写
                ProcessRequest(events[i].data.fd,epfd);
            }
        }
    }
    return 0;
}
