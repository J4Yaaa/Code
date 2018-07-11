#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

int ServerInit(short port)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //可以监听本机内任何的ip地址
    addr.sin_port = htons(port);
    int ret = bind(fd,(sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        return -1;
    }
    ret = listen(fd,5);
    if(ret < 0)
    {
        perror("listen");
        return -1;
    }
    return fd;
}

void* Service(void* sock)
{
    int64_t new_sock = (int64_t)sock;
    // 1.读取并解析请求,因为我们是简易版本,所以省略去解析过程
    char buf[1024 * 10] = {0};
    read(new_sock,buf,sizeof(buf)-1);
    printf("[Request] %s\n",buf);
    // 2.构造hello world相应字符串,并写会客户端
    const char* resp = "HTTP/1.0 200 OK\n\n<html><h1>hello world</h1></html>\n"; //HTTP1.0 短连接
    write(new_sock,resp,strlen(resp));
    close(new_sock);
    return NULL;
}

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./http_server [port]\n");
        return 1;
    }
    int listen_sock = ServerInit(atoi(argv[1]));
    if(listen_sock < 0)
    {
        printf("ServerInit faild \n");
        return 1;
    }
    printf("ServerInit OK\n");
    
    while(1)
    {
        sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int64_t new_sock = accept(listen_sock,(sockaddr*)&peer,&len);
        if(new_sock < 0)
        {
            perror("accept");
            continue;
        }
        printf("client: %s\n",inet_ntoa(peer.sin_addr));
//         pid_t id = fork();
//         if(id == 0)
//         {
//             close(listen_sock);
//             if(fork() > 0)
//             {
//                 exit(0);
//             }
//             Service(new_sock);
//             close(new_sock);
//             exit(0);
//         }
//         else if(id > 0)
//         {
//             close(new_sock);
//             waitpid(id,NULL,0);
//         }
        pthread_t tid;
        pthread_create(&tid,NULL,Service,(void*)new_sock);
        pthread_detach(tid);
    }

    return 0;
}
