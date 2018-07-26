#include <sys/timerfd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/select.h>
#include <stdint.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <tetris.h>
#include <def.h>
#include <keyboard.h>

int init_socket( void )
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);

	int op = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof op);

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("127.0.0.1", &addr.sin_addr);

	int r = bind(lfd, (struct sockaddr*)&addr, sizeof addr);
	if ( r == -1 ) perror("bind"),exit(1);
	listen(lfd, SOMAXCONN);

	return lfd;
}

int main( void )
{
	int tfd = -1;
	int maxfd;
	int y = 1;
	int x = 1;
	fd_set rset;

	srand(getpid());
	init_keyboard();
	int lfd = init_socket();

	tfd = timerfd_create(CLOCK_MONOTONIC,TFD_CLOEXEC|TFD_NONBLOCK);
	if ( tfd == -1 ) perror("timerfd_create"),exit(EXIT_FAILURE);

	struct itimerspec is;
	memset(&is, 0x00, sizeof is);
	is.it_value.tv_nsec = 1;
	is.it_interval.tv_sec = 1;
	timerfd_settime(tfd, 0, &is, NULL);

	int kfd = fileno(stdin);
	
	maxfd = tfd > kfd ? tfd : kfd;
	maxfd = maxfd > lfd ? maxfd : lfd;

	draw_back();
	next = rand() % 7;
	show_next(next);

	while ( 1 ) {
		FD_ZERO(&rset);
		FD_SET(tfd, &rset);
		FD_SET(kfd, &rset);
		FD_SET(lfd, &rset);
		if ( nfd != -1 ) {
			FD_SET(nfd, &rset);
		}

		int nready = select(maxfd+1, &rset, NULL, NULL, NULL);
		if ( nready <= 0 ) continue;

		if ( FD_ISSET(tfd, &rset)) {
			uint64_t clk;
			read(tfd, &clk, sizeof clk);
			timer_tetris(&t);
		}
		if ( FD_ISSET(kfd, &rset) ) {
			tetris(&t);
		}
		if ( FD_ISSET(lfd, &rset) ) {
			nfd = accept(lfd, NULL, NULL);
			if ( nfd == -1 ) perror("accept"),exit(1);
			maxfd = maxfd > nfd ? maxfd : nfd;
		}
		if ( FD_ISSET(nfd, &rset) ) {
			struct info inf;
			memset(&inf, 0x00, sizeof inf);
			if ( read(nfd, &inf, sizeof inf) <= 0 ) {
				nfd = -1;
			} else if ( ntohl(inf.type) == 3 ) {
				show_next(ntohl(inf.next));
				next = ntohl(inf.next);
			}
		}
	}

	recover_keyboard();
}

