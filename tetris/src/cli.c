#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <def.h>
#include <tetris.h>
#include <keyboard.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>

int main( void )
{
	int cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd == -1 ) perror("socket"),exit(1);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	inet_aton("127.0.0.1", &addr.sin_addr);
	int r = connect(cfd, (struct sockaddr*)&addr, sizeof addr);
	if ( r == -1 ) perror("connect"),exit(1);
	
	int kfd = fileno(stdin);
	int maxfd = kfd > cfd ? kfd : cfd;
	fd_set rset;

	while ( 1 ) {
		printf("\033[%d;%dH 0:T 1:Z 2:S 3:L 4:_| 5:I 6:田", H+1,0);
		printf("\033[%d;%dH请输入下一个图案:", H+2,0);
		fflush(stdout);

		FD_ZERO(&rset);
		FD_SET(kfd, &rset);
		FD_SET(cfd, &rset);
		if (select(maxfd+1, &rset, NULL, NULL, NULL) <= 0 )
			perror("select"),exit(1);
		if ( FD_ISSET(cfd, &rset) ) {
			struct info inf;
            memset(&inf, 0x00, sizeof(inf));
			r = read(cfd, &inf, sizeof inf);
			if ( r <= 0 ) break;
			if ( ntohl(inf.type) == 1) {
				draw_back();
				show_next(inf.next);
				draw_shape(inf.t.x, inf.t.y, inf.s, FC);
			} else { // type = 2
				memcpy(background, inf.background, sizeof inf.background);
				show_next(inf.next);
				draw_back();
			}
		}
		if ( FD_ISSET(kfd, &rset) ) {
            int n;
			struct info inf;

            memset(&inf, 0x00, sizeof(inf));

            inf.type = htonl(3);
			scanf("%d", &n);
			fflush(stdout);
			inf.next = htonl(n);
			if ( write(cfd, &inf, sizeof(inf)) == -1 )
                perror("write"),exit(1);
			show_next(n);
		}
	}

	printf("\033[?25h\n");
}

