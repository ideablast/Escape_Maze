#include"ALL.h"

Stack *top;
Point Start;
Point Goal;
Point Past_point;

int main()
{
	srand((unsigned int)time(NULL));
	int **map;
	//int i, j;
	int cnt = 0;
	int map_size;
	int break_signal;

	top = Add_new_stack();
	map = Make_map();
	map_size = _msize(map) / sizeof(int*);
	puts("게임 시작");
	Maze_Print_out(map);
	system("pause");
	//system("cls");
	puts("");
	while (1)
	{
		
		break_signal = Path_selecter_new(&map);
		Maze_Print_out(map);
		system("pause");
		system("cls");

		if (break_signal == TRUE)
		{
			puts("탈출 실패!");
			break;
		}

		if (Start.i == Goal.i&&Start.j == Goal.j)
		{
			puts("탈출 성공!");
			break;
		}
	}



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