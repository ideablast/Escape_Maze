#include"ALL.h"

Stack *top;

int main()
{
	srand((unsigned int)time(NULL));
	int **map;
	//int i, j;
	int cnt = 0;
	int map_size;
	Point Start;
	Point Goal;
	top = Add_new_stack();
	map = Make_map();
	map_size = _msize(map) / sizeof(int*);
	Goal = Pop_stack();
	Start = Pop_stack();

	Maze_Print_out(map);

	

	system("pause");
}

#ifdef NOTYET
for (i = 0; i < size; i++)
{
	for (j = 0; j < size; j++)
	{
		printf("%d\n", map[i][j]);
	}
}
#endif