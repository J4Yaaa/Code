#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <def.h>

void draw_element(int x, int y, int c);
void draw_shape(int x, int y, struct shape p, int c);
void timer_tetris(struct data *p);
void tetris(struct data *p);
void draw_back( void );
void show_next(int );

#endif // __TETRIS_H__

