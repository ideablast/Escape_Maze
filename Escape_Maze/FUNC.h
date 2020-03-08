#pragma once
#include"ALL.h"

#ifndef __FUNC_H__
#define __FUNC_H__

/*BASIC_STACK*/
Stack* Add_new_stack();
void Push_stack(Point P_temp);
Point Pop_stack();
int IsEmpty();
int Count_stack();
/*ESCAPE_MAZE_GAME*/
int** Make_map();
void Maze_Print_out(int **map);
void Move_Point(int ***map, int set, Point temp);
int Boundary_decter(int ***map, Point temp);
int Wall_decter(int ***map, Point temp);
double Distance_calculator(Point temp);
int Path_selecter(int ***map);
int Is_already_passed(int ***map, Point temp);

#endif

