#include <stdio.h>
#include <tetris.h>
#include <def.h>
#include <keyboard.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void draw_element(int x, int y, int c)
{
	x *= 2;
	x++;
	y++;

	printf("\033[%d;%dH", y, x);
	printf("\033[3%dm\033[4%dm", c, c);
	printf("[]");
	fflush(stdout);
	printf("\033[?25l");
	printf("\033[0m");
}

void draw_shape(int x, int y, struct shape p, int c)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( p.s[i][j] != 0 ) {
				draw_element(x+j, y+i, c);
			}
		}
	}
}

void draw_back( void )
{
	for (int i=0; i<H; i++) {
		for (int j=0; j<W; j++){
			if ( background[i][j] != 0 )
				draw_element(j, i, background[i][j]);
			else
				draw_element(j, i, BC);
		}
	}
}

int can_move(int x, int y, struct shape shpe)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( shpe.s[i][j] == 0 )
				continue;
			if ( x+j >= W )
				return 0;
			if ( x+j < 0 )
				return 0;
			if ( y+i >= H )
				return 0;
			if ( background[y+i][x+j] != 0 )
				return 0;
		}
	}

	return 1;
}

void set_back(int x, int y, struct shape shp)
{
	for (int i=0; i<5; i++){
		for (int j=0; j<5; j++) {
			if ( shp.s[i][j] != 0 )
				background[y+i][x+j] = FC;
		}
	}
}

void mclean( void )
{
	for (int i=0; i<H; i++) {
		int total = 0;
		for (int j=0; j<W; j++) {
			if ( background[i][j] != 0 )
				total ++;
		}
		if ( total == W ) {
			for (int k = i; k>0; k--)
				memcpy(background[k], background[k-1], sizeof background[k-1] );
			memset(background[0], 0x00, sizeof background[0]);
		}
	}
}

void timer_tetris(struct data *p)
{
	if ( can_move(p->x,p->y+1, shape_arr[cur])  ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		p->y++;
		draw_shape(p->x, p->y, shape_arr[cur], FC);
		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(1);
			g_info.s = shape_arr[cur];
			g_info.t = *p;
			g_info.next = next;
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				recover_keyboard(),perror("write"),exit(1);
			}
		}
	} else {
		set_back(p->x, p->y, shape_arr[cur]);
		mclean();
		draw_back();

		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(2);
			g_info.next = next;
			memcpy(g_info.background, (void*)background, sizeof(g_info.background));
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				recover_keyboard(),perror("write"),exit(1);
			}
		}

		p->x = 0;
		p->y = 0;
		cur = next;
		next = rand() % 7;
		show_next(next);
	}
}

void show_next(int nxt)
{
	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			if ( shape_arr[nxt].s[i][j] == 0 )
				draw_element(W+2+j, 2+i, BC);
			else
				draw_element(W+2+j, 2+i, FC);
		}
	}
}

static struct shape turn_90(struct shape p)
{
	struct shape t;

	for (int i=0; i<5; i++) {
		for (int j=0; j<5; j++) {
			t.s[i][j] = p.s[4-j][i];
		}
	}
	
	return t;
}

void tetris(struct data *p)
{
	int c = get_key();

	if ( is_left(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x-1,p->y, shape_arr[cur])  )
			p->x--;
		draw_shape(p->x, p->y, shape_arr[cur], FC);
		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(1);
			g_info.s = shape_arr[cur];
			g_info.t = *p;
			g_info.next = next;
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				perror("write");
			}
		}
	}
	if ( is_right(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x+1,p->y, shape_arr[cur])  )
			p->x++;
		draw_shape(p->x, p->y, shape_arr[cur], FC);
		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(1);
			g_info.s = shape_arr[cur];
			g_info.t = *p;
			g_info.next = next;
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				perror("write");
			}
		}
	}
	if ( is_up(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		shape_arr[cur] = turn_90(shape_arr[cur]);
		if ( 0 == can_move(p->x,p->y, shape_arr[cur]) ) {
			shape_arr[cur] = turn_90(shape_arr[cur]);
			shape_arr[cur] = turn_90(shape_arr[cur]);
			shape_arr[cur] = turn_90(shape_arr[cur]);
		}
		draw_shape(p->x, p->y, shape_arr[cur], FC);
		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(1);
			g_info.next = next;
			g_info.s = shape_arr[cur];
			g_info.t = *p;
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				perror("write");
			}
		}
	}
	if ( is_down(c) ) {
		draw_shape(p->x, p->y, shape_arr[cur], BC);
		if ( can_move(p->x,p->y+1, shape_arr[cur])  )
			p->y++;
		draw_shape(p->x, p->y, shape_arr[cur], FC);
		if ( nfd != -1 ) {
			memset(&g_info, 0x00, sizeof g_info);
			g_info.type = htonl(1);
			g_info.s = shape_arr[cur];
			g_info.t = *p;
			g_info.next = next;
			if ( write(nfd, &g_info, sizeof g_info) == -1 ) {
				perror("write");
			}
		}
	}
	if ( is_esc(c) ) {
		printf("\033[?25h");
		recover_keyboard();
		exit(0);
	}
}

