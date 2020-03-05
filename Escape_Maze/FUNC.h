#pragma once
#include"ALL.h"

#ifndef __FUNC_H__
#define __FUNC_H__

/*BASIC_STACK*/
Stack* Add_new_stack();
void Push_stack(int i, int j);
Point Pop_stack();
int IsEmpty();
int Count_stack();
/*ESCAPE_MAZE_GAME*/
int** Make_map();
void Make_road(int***map);
/*Simple Function*/
char* get_string_return_ptr();
void clear_buf();
#endif

