#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./client [ip] [port]\n");
        return 1;
    }
    // 1. 创建 socket
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("socket");
        return 1;
    }
    // 2. 建立连接
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));
    int ret = connect(fd,(sockaddr*)&server,sizeof(server));
    if(ret < 0)
    {
        perror("connect");
        return 1;
    }
    // 3. 进入事件循环
    while(1)
    {
        //    a) 从标准输入读数据
        char buf[1024] = {0};
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0)
        {
            perror("read");
            return 1;
        }
        if(read_size == 0)
        {
            printf("read done\n");
            return 0;
        }
        buf[read_size] = '\0';
        //    b) 把读入的数据发送到服务器上
        write(fd,buf,strlen(buf));
        //    c) 从服务器读取相应结果
        char buf_resp[1024] = {0};
        read_size = read(fd,buf_resp,sizeof(buf_resp) - 1);
        if(read_size < 0)
        {
            perror("read");
            return 1;
        }
        else if(read_size == 0)
        {
            //对端先断开连接
            printf("server close socket\n");
            return 0;
        }
        buf_resp[read_size] = '\0';
        //    d) 把结果打印到标准输出上
        printf("server respond > %s\n",buf_resp);
    }
    return 0;
}

