/////////////////////////////////////////////////////////////////////
// 客户端逻辑:
// 1. 用户输入数据,从标准输入输入一个字符串
// 2. 用户吧这个字符串发送给服务器 (请求Request)
// 3. 从服务器读取返回结果 (响应 Response)
// 4. 把结果打印到标准输出上
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

// 传入服务器的 ip 和 端口号
int main(int argc,char* argv[])
{
    if(argc != 3)
    {
        printf("Usage : ./client [ip] [port]\n");
        return 1;
    }
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd < 0)
    {
        perror("socket");
        return 1;
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));
    char buf[1024] = {0};
    while(1)
    {
        // 1. 从标准输入读取数据
        socklen_t len = sizeof(server);
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
        // 2. 发送数据到服务器
        sendto(fd,buf,strlen(buf),0,(sockaddr*)&server,len);
        // 3. 尝试从服务器读取响应
        char buf_resp[1024] = {0};
        // 这里的后两个参数表示接受服务器的端口哈和ip地址
        // 由于我们已经知道对端的ip和端口号
        // 所以这里不需要输出型参数去返回这两个值,直接忽略就好
        read_size = recvfrom(fd,buf_resp,sizeof(buf_resp),0,NULL,NULL);
        if(read_size < 0)
        {
            perror("recvfrom");
            return 1;
        }
        buf_resp[read_size] = '\0';
        // 4. 把响应写到标准输出
        printf("server resp %s\n",buf_resp);
    }
    close(fd);
    return 0;
}
