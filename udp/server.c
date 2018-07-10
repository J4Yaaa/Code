/////////////////////////////////////////////////////////////////////
// 服务器逻辑:
// 1. 启动服务器(初始化)
// 2. 进入一个事件循环
//    a) 从 socket 中读取 Request
//    b) 根据 Request 内容计算生成 Response
//    c) 把 Response 响应写到 socket 中(回显服务器,echo_server)
/////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main(int argc,char* argv[])
{
    // 0.校验命令行参数
    if(argc != 3)
    {
        printf("Usage : ./service [ip] [port]\n");
        return 1;
    }
    // 1.服务器初始化
    //   a) 创建socket
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd < 0)
    {
        perror("socket");
        return 1;
    }
    //   b) 绑定IP地址和端口号
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);//点分十进制的字符串ip地址转化为数字(网络字节序)
    addr.sin_port = htons(atoi(argv[2]));
    int ret = bind(fd,(sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return 1;
    }

    // 2.进入事件循环
    char buf[1024] = {0}; 
    while(1)
    {
        //   a) 读取请求
        sockaddr_in peer;
        socklen_t len = sizeof(len);
        ssize_t read_size = recvfrom(fd,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len); //这时peer里的数据为对端的数据
        if(read_size < 0)
        {
            continue;
        }
        buf[read_size] = '\0';
        //   b) 根据请求进行计算(这里是echo_server)
        printf("client[%s : %d] : %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
        //   c) 把响应写回到socket上
        sendto(fd,buf,strlen(buf),0,(sockaddr*)&peer,sizeof(peer));
    }
    close(fd);
    return 0;
}
