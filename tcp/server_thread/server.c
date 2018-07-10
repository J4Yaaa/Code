#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

typedef struct Peer
{
    int sock;
    sockaddr_in peer;
}Peer;

void* ThreadEntry(void* arg)
{
    Peer* p = (Peer*)arg;

    //需要循环处理客户端发送的数据
    char buf[1024] = {0};
    while(1)
    {
        ssize_t read_size = read(p->sock,buf,sizeof(buf)-1);
        if(read_size < 0)
        {
            continue;
        }
        else if(read_size == 0)
        {
            //客户端关闭连接
            printf("client[%s : %d] quit\n",inet_ntoa(p->peer.sin_addr),ntohs(p->peer.sin_port));
            close(p->sock);
            free(p);
            return NULL;
        }
        else
        {
            buf[read_size] = '\0';
            printf("client[%s : %d] say > %s\n",inet_ntoa(p->peer.sin_addr),ntohs(p->peer.sin_port),buf);
            // 吧响应写回到客户端
            write(p->sock,buf,strlen(buf));
        }
    }
}

void ProcessConnect(int new_sock,sockaddr_in peer)
{
    Peer* p = (Peer*)malloc(sizeof(Peer));
    p->sock = new_sock;
    p->peer = peer;

    pthread_t tid;
    pthread_create(&tid,NULL,ThreadEntry,p);
    pthread_detach(tid);
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./server [ip] [port]\n");
        return 1;
    }
    // 1. 创建 socket
    int listen_sock = socket(AF_INET,SOCK_STREAM,0);
    if(listen_sock < 0)
    {
        perror("socket");
        return 1;
    }
    // 2. 绑定端口号
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));
    if(bind(listen_sock,(sockaddr*)&addr,sizeof(addr)) < 0)
    {
        perror("bind");
        return 2;
    }
    // 3. 转换成被动模式(监听模式)
    //    允许被键立连接
    int ret = listen(listen_sock,2);
    if(ret < 0)
    {
        perror("listen");
        return 3;
    }
    printf("server init ok\n");
    while (1) {
        // 4. 服务器初始化完成,进入事件循环
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int new_sock = accept(listen_sock,(sockaddr*)&peer,&len);
        if(new_sock < 0)
        {
            perror("accpet");
            continue;
        }
        printf("client[%s : %d] Connect\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
        ProcessConnect(new_sock,peer);
    }
    return 0;
}

