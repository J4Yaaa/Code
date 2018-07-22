#include <stdio.h>
#include <unistd.h>
#include <poll.h>

int main()
{
    struct pollfd fds;
    fds.fd = 0;
    fds.events = POLLIN;
    while(1)
    {
        int ret = poll(&fds,1,123456);
        if(ret < 0)
        {
            perror("poll");
            continue;
        }
        if(ret == 0)
        {
            printf("timeout...\n");
            continue;
        }
        if(fds.revents == POLLIN)
        {
            char buf[1024] = {0};
            read(0,buf,sizeof(buf)-1);
            printf("stdin: %s\n",buf);
        }
    }
    return 0;
}
