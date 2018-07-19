#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>

// 对fd_set进行一个简单的封装
// 为了能够方便的获取到文件描述符集中的的最大文件描述符
typedef struct FdSet
{
    fd_set fds;
    int max_fd; // 当前文件描述符集中的最大文件描述符
}FdSet;

void InitFdSet(FdSet* set)
{
    if(set == NULL)
    {
        return;
    }
    set->max_fd = -1;
    FD_ZERO(&set->fds);
}

void AddFdSet(FdSet* set,int fd)
{
    FD_SET(fd,&set->fds);
    if(fd > set->max_fd)
    {
        set->max_fd = fd;
    }
}

void DelFdSet(FdSet* set,int fd)
{
    FD_CLR(fd,&set->fds);
    int max_fd = -1;
    int i = 0;
    for(; i <= set->max_fd; ++i)
    {
        if(!FD_ISSET(i,&set->fds))
        {
            continue;
        }
        if(i > max_fd)
        {
            max_fd = i;
        }
    }
    // 循环结束以后,max_fd就是当前最大的文件描述符
    set->max_fd = max_fd;
    return;
}
////////////////////////////////////////////////////  封装完成

int ServerStart(short port)
{
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);
    if(bind(fd,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        perror("bind");
        return -2;
    }
    if(listen(fd,3) < 0)
    {
        perror("listen");
        return -3;
    }
    return fd;
}

int ProcessRequest(int new_sock)
{
    // 完成对客户端的读写操作
    // 这里不可以向以前一样进行循环读写操作
    // 当前是单进程/线程程序,如果死循环就无法执行别的操作了
    
    // 此处只进行一次读写,因为我们要将所有的等待操作都交给select完成
    // 下一次对该 socket 读取的时机,也是由select来进行通知的
    // 也就是select下一次返回该文件描述符就绪的时候就能进行读数据了

    char buf[1024] = {0};
    ssize_t read_size = read(new_sock,buf,sizeof(buf)-1);
    if(read_size < 0)
    {
        perror("read");
        return -1;
    }
    else if(read_size == 0)
    {
        printf("[client %d] : disconnect\n",new_sock);
        return 0;
    }
    buf[read_size] = '\0';
    printf("[client %d] : %s\n",new_sock,buf);
    write(new_sock,buf,strlen(buf));
    return read_size;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: %s [port]\n",argv[0]);
        return 1;
    }
    // 1.对服务器进行初始化
    int listen_sock = ServerStart(atoi(argv[1]));
    if(listen_sock < 0)
    {
        printf("ServerStart faild\n");
        return 1;
    }
    printf("ServerStart OK\n");
    // 2.进入事件循环
    FdSet read_fds; // 输入参数: 要等待的所有文件描述符都要加到这个位图中
    InitFdSet(&read_fds);
    AddFdSet(&read_fds,listen_sock);
    while(1)
    {
        // 3.使用select完成等待
        //   创建 output_fds 的目的是: 防止select返回,把read_fds的内容给破坏掉,导致期中数据丢失
        //   read_fds 始终表示select监控的文件描述符集的内容

        FdSet output_fds = read_fds; // 输出型参数: 用来保存每一次的输出参数
        int ret = select(output_fds.max_fd+1,&output_fds.fds,NULL,NULL,NULL);
        if(ret < 0)
        {
            perror("select");
            continue;
        }
        // 4.select返回以后进行处理
        //   a) listen_sock 读就绪
        //   b) new_sock 读就绪
        if(FD_ISSET(listen_sock,&output_fds.fds)) 
        {// 查看listen_sock在位图中,就证明客户端连接上了,可以accept了 
         // 调用 accept 获取到连接,将new_sock加入到select之中
            struct sockaddr_in peer;
            socklen_t len = sizeof(peer);
            int new_sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
            if(new_sock < 0)
            {
                perror("accept");
                return 1;
            }
            AddFdSet(&read_fds,new_sock);
            printf("[client : %d] connect \n",new_sock);
        }
        else
        {// 当前就是 new_sock 就绪了
            int i = 0;
            for(; i < output_fds.max_fd + 1; ++i)
            { 
                if(!FD_ISSET(i,&output_fds.fds))
                {
                    continue;
                }
                // 到了这里,证明 i 是位图中的一位, 就可以开始读写了
                int ret = ProcessRequest(i);
                if(ret <= 0)
                { 
                    // 到这里正明客户端已经断开连接了
                    // close DelFdSet 两步顺序不影响
                    DelFdSet(&read_fds,i);
                    close(i);
                } // end if(ret<=0)
            } // end for
        } // end else
    } // end while(1)
    return 0;
}
