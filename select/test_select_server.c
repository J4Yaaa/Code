#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>   
#include <sys/socket.h>


int fdArray[sizeof(fd_set)*8];

int start_up(short port)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    int opt = 1;
    setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)); // 解决timewait状态
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);
    int ret = bind(fd,(struct sockaddr*)&local,sizeof(local));
    if(ret < 0)
    {
        perror("bind");
        return -2;
    }
    if(listen(fd,5) < 0)
    {
        perror("bind");
        return -3;
    }
    return fd;
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [port]\n",argv[0]);
        return 1;
    }
    int listen_sock = start_up(atoi(argv[1]));
    fdArray[0] = listen_sock;
    int num = sizeof(fdArray)/sizeof(fdArray[0]);
    int i = 1;
    for(; i < num; ++i)
    {// 初始化fdArray
        fdArray[i] = -1;
    }

    while(1)
    {// 进入事件循环
        fd_set fds;
        FD_ZERO(&fds);
        int max_fd = fdArray[0];
        for(i = 0; i < num; ++i)
        {
            if(fdArray[i] >= 0)
            {
                FD_SET(fdArray[i],&fds);
                if(max_fd < fdArray[i])
                {
                    max_fd = fdArray[i];
                }
            }
        }
        struct timeval timeout = {3,0};
        switch(select(max_fd+1,&fds,NULL,NULL,&timeout))
        {
        case 0:
            printf("timeout...\n");
            break;
        case -1:
            perror("select");
            break;
        default:
            {
                for(i = 0; i < num; ++i)
                {
                    if(fdArray[i] == -1)
                        continue;

                    /* if(i == 0 && fdArray[i] == listen_sock && FD_ISSET(fdArray[i],&fds)) */
                    if(i == 0 && FD_ISSET(fdArray[i],&fds))
                    {// accept
                        struct sockaddr_in client;
                        socklen_t len = sizeof(client);
                        int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
                        if(new_sock < 0)
                        {
                            perror("accept");
                            continue;
                        }
                        for(i = 0; i < num; ++i)
                        {
                            if(fdArray[i] == -1)
                            {
                                break;
                            }
                        }
                        if(i < num)
                        {
                            fdArray[i] = new_sock;
                        }
                        else
                        {
                            close(new_sock); // 文件描述符达到上限
                        }
                        continue;
                    }
                    else
                    {// read
                        if(FD_ISSET(fdArray[i],&fds))
                        {
                            char buf[1024] = {0};
                            ssize_t read_size = read(fdArray[i],buf,sizeof(buf)-1);
                            if(read_size > 0)
                            {
                                buf[read_size] = '\0';
                                printf("client: %s\n",buf);
                            }
                            else if(read_size == 0)
                            {
                                printf("client quit\n");
                                close(fdArray[i]);
                                FD_CLR(fdArray[i],&fds);
                            }
                            else
                            {
                                perror("read");
                                close(fdArray[i]);
                                FD_CLR(fdArray[i],&fds);
                            }
                        }

                    }
                } // end for(i = 0; i < num; ++i) 
            } // end default
            break;
        } // end switch

    } // end while(1)
    return 0;
}
