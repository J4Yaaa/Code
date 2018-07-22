#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

typedef struct pollfd pollfd;

int ServerStart(short port)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    if(bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("bind");
        return -2;
    }
    if(listen(fd,5) < 0)
    {
        perror("listen");
        return -3;
    }
    return fd;
}

void Init(pollfd* fd_list,int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
        fd_list[i].fd = -1;
        fd_list[i].events = 0;
        fd_list[i].revents = 0;
    }
}

void Add(int fd,pollfd* fd_list,int size)
{
    int i = 0;
    for(; i < size; ++i)
    {
        // 找到第一个空位将fd加入进去
        if(fd_list[i].fd == -1)
        {
            fd_list[i].fd = fd;
            fd_list[i].events = POLLIN;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [port]\n",argv[0]);
        return 1;
    }
    int listen_sock = ServerStart(atoi(argv[1]));
    if(listen_sock < 0)
    {
        printf("ServerStart Faild\n");
        return 1;
    }
    pollfd fd_list[1024];
    Init(fd_list,sizeof(fd_list)/sizeof(pollfd));
    Add(listen_sock,fd_list,sizeof(fd_list)/sizeof(pollfd));
    // 进入事件循环
    while(1)
    {
        int ret = poll(fd_list,sizeof(fd_list)/sizeof(pollfd),123456);
        if(ret < 0)
        {
            perror("poll");
            continue;
        }
        else if(ret == 0)
        {
            printf("time out...\n");
            continue;
        }
        size_t i = 0;
        for(; i < sizeof(fd_list)/sizeof(pollfd); ++i)
        {
            if(fd_list[i].fd == -1)
            {
                continue;
            }
            if(!(fd_list[i].revents & POLLIN)) //如果输出参数不是pollin，就跳过
            {
                continue;
            }
            if(fd_list[i].fd == listen_sock)
            {// 处理listen_sock情况
             // 证明客户端已经连接上了，可以进行accept了
                struct sockaddr_in client;
                socklen_t len = sizeof(client);
                int new_sock = accept(fd_list[i].fd,(struct sockaddr*)&client,&len);
                if(new_sock < 0)
                {
                    perror("accept");
                    continue;
                }
                Add(new_sock,fd_list,sizeof(fd_list)/sizeof(pollfd));
                printf("[client: %d] connect\n",new_sock);
            }
            else
            {// new_sock已经就绪
             // 可以进行读写了
                char buf[1024] = {0};
                ssize_t read_size = read(fd_list[i].fd,buf,sizeof(buf)-1);
                if(read_size < 0)
                {
                    perror("read");
                    continue;
                }
                if(read_size == 0)
                {
                    printf("[client: %d] disconnect\n",fd_list[i].fd);
                    fd_list[i].fd = -1;
                    fd_list[i].events = 0;
                    fd_list[i].revents = 0;
                    close(fd_list[i].fd);
                }
                printf("[client: %d] : %s\n",fd_list[i].fd,buf);
                write(fd_list[i].fd,buf,strlen(buf)); // 回显
            } // end else
        } // end for(; i < sizeof(fd_list)/sizeof(pollfd); ++i) 
    } // end while(1)
    return 0;
}
