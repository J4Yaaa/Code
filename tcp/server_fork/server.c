#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;

void ProcessConnect(int sock, sockaddr_in peer)
{
    /*
     *在这个循环中进行创建子进程的请求
     */
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return;
    }
    else if(pid > 0) // parent
    {
        // 会产生的问题:
        // 1.僵尸进程
        //   a) wait(NULL) 不合适!这是一个阻塞等待
        //   b) waitpid(-1,NULL,WNOHANG) 不合适!waitpid只非阻塞等待一次,当子进程没返回就直接退出
        //   c) 忽略SIGCHILD信号 *可用,让操作系统自动回收子进程的退出状态
        // 2.如果不关闭文件描述符,会一直消耗资源
        //   导致文件描述符泄漏
        close(sock);
        return;
    }
    else
    {
        //需要循环处理客户端发送的数据
        char buf[1024] = {0};
        while(1)
        {
            ssize_t read_size = read(sock,buf,sizeof(buf)-1);
            if(read_size < 0)
            {
                continue;
            }
            else if(read_size == 0)
            {
                //客户端关闭连接
                printf("client[%s : %d] quit\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port));
                close(sock); // 因为进程终止了,pcb退出,文件描述符表也就销毁,所以这里的 close 可以不用.
                // 会产生的问题:
                // 1.子进程如果在这里直接return,就会返回回去调用accept, 没必要!!!
                //   子进程只需要和客户端沟通就好,客户端断开,子进程也退出就好
                exit(0);
            }
            else
            {
                buf[read_size] = '\0';
                printf("client[%s : %d] say > %s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
                // 吧响应写回到客户端
                write(sock,buf,strlen(buf));
            }
        }
    }
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./server [ip] [port]\n");
        return 1;
    }
    signal(SIGCHLD,SIG_IGN);
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
        close(new_sock);
    }
    return 0;
}
