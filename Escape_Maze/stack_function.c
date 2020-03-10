#include"ALL.h"

extern Stack *top;
extern Point Start;
extern Point Goal;
extern Point Past_point;
/*BASIC_STACK*/
Stack* Add_new_stack()
{
	Stack *temp = (Stack*)malloc(sizeof(Stack));
	temp->Point.i = 0;
	temp->Point.j = 0;

	temp->Link = NULL;

	return temp;
}

void Push_stack(Point P_temp)
{
	Stack *temp = Add_new_stack();
	temp->Point.i = P_temp.i;
	temp->Point.j = P_temp.j;

	temp->Link = top->Link;
	top->Link = temp;
}

Point Pop_stack()
{
	Stack *Pop_mem = top->Link;
	Point Point;

	Point.i = top->Link->Point.i;
	Point.j = top->Link->Point.j;

	top->Link = Pop_mem->Link;
	free(Pop_mem);

	return Point;
}

int IsEmpty()
{
	return top->Link == NULL;
}

int Count_stack()
{
	int cnt = 0;
	Stack *Count = top->Link;

	while (Count->Link != NULL)
	{
		cnt++;
		Count = Count->Link;
	}
	cnt++;

	return cnt;

}
/*ESCAPE_MAZE_GAME*/
int** Make_map()
{
	int **temp;
	int size = rand() % 4 + 7;
	int size_j;
	int i, j;
	int Wall_Road;

	int cnt = 0;
	int zero_cnt = 0;
	int one_cnt = 0;

	temp = (int**)malloc(size * sizeof(int*));
	for (size_j = 0; size_j < size; size_j++)
		temp[size_j] = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			Wall_Road = rand() % 10;

			if (Wall_Road < 3)
			{
				Wall_Road = 1;
				one_cnt++;
			}
			else
			{
				Wall_Road = 0;
				zero_cnt++;
			}

			temp[i][j] = Wall_Road;
		}
	}

	printf("0비율:%lf\n", zero_cnt / (double)(size*size));
	printf("1비율:%lf\n", one_cnt / (double)(size*size));

	while (1)
	{
		Start.i = rand() % size;
		Start.j = rand() % size;

		if (temp[Start.i][Start.j] == 0)
		{
			temp[Start.i][Start.j] = 2;
			break;
		}
	}

	while (1)
	{
		Goal.i = rand() % size;
		Goal.j = rand() % size;

		if (temp[Goal.i][Goal.j] == 0 && temp[Goal.i][Goal.j] != 2)
		{
			temp[Goal.i][Goal.j] = 3;
			break;
		}

	}

	return temp;
}

//-1:초기화 0□:길 1■:벽 2★:시작 3♥:도착 4:이미 한번 지나간 길
void Maze_Print_out(int **map)
{
	int i, j;
	int map_size = _msize(map) / sizeof(int*);

	for (i = 0; i < map_size; i++)
	{
		for (j = 0; j < map_size; j++)
		{
			switch (map[i][j])
			{
			case 0:
				printf("□");
				break;
			case 1:
				printf("■");
				break;
			case 2:
				printf("★");
				break;
			case 3:
				printf("♥");
				break;
			case 4:
				printf("▩");
				break;
			}
		}
		printf("\n");
	}
}
//갈림길 판단 방법?
//경계값을 잘 확인 할 것
//벽인 값을 잘 확인 할 것
void Move_Point(int ***map, int set, Point temp)
{
	if (set == 4)
	{
		(*map)[Start.i][Start.j] = set;
		(*map)[temp.i][temp.j] = 2;
	}
	else
	{
		Push_stack(Start);
		(*map)[Start.i][Start.j] = set;
		(*map)[temp.i][temp.j] = 2;
	}
	
	Start = temp;
}

int Boundary_decter(int ***map, Point temp)
{
	int Boundary = _msize(*map) / sizeof(int*);
	int result;

	if (!((temp.i) >= 0 && (temp.i) < Boundary))//경계값을 넘어가는 경우
		result = FALSE;
	else//경계값 이내에 있는 값인 경우
	{
		if (!(temp.j >= 0 &&temp.j < Boundary))
			result = FALSE;
		else
			result = TRUE;
	}

	return result;
}

int Wall_decter(int ***map,  Point temp)
{
	int result;

	if (Boundary_decter(map, temp) == TRUE)
	{
		if ((*map)[temp.i][temp.j] != 1)
			result = TRUE;//벽이 아님->갈 수 있는 길
		else
			result = FALSE;
	}
	else//경계값 벗어나는 경우
		result = FALSE;

	return result;
}

int Is_already_passed(int ***map, Point temp)
{
	int result;

	if ((*map)[temp.i][temp.j] != 4)
		result = TRUE;
	else
		result = FALSE;

	return result;
}
int result_false_cnt(int *result_ary)
{
	int cnt = 0;
	int i;

	for (i = 0; i < 4; i++)
	{
		if (result_ary[i] == FALSE)
			cnt++;
	}

	return cnt;
}


double Distance_calculator(Point temp)
{
	return sqrt(pow((temp.i - Goal.i), 2) + pow((temp.j - Goal.j), 2));
}

int Path_selecter(int ***map)
{
	Point dir_ary[4] = { {Start.i, Start.j -1 } ,{ Start.i -1,Start.j },{ Start.i,Start.j+ 1 },{ Start.i +1, Start.j } };
	int i;
	int result_ary[4];
	int min_idx;
	double distance_result[4];
	Point temp;
	Point Cur_Point;
	int break_signal;
	int false_cnt = 0;
	int true_cnt;
	
	Cur_Point = Start;

	for (i = 0; i < 4; i++)
		result_ary[i] = Wall_decter(map, dir_ary[i]) && Is_already_passed(map, dir_ary[i]);

	for (i = 0; i < 4; i++)
	{
		if (result_ary[i] == TRUE)//결과값이 참인 경우에만 거리를 계산
			distance_result[i] = Distance_calculator(dir_ary[i]);

		else
			distance_result[i] = 20;
	}

	true_cnt = (4 - result_false_cnt(result_ary));
	if(true_cnt == 2)
	if (result_false_cnt(result_ary) == 4)
		break_signal = FALSE;

	min_idx = 0;
	for (i = 0; i < 4; i++)
	{
		if (distance_result[i] < distance_result[min_idx])
			min_idx = i;
	}//거리의 최소값을 가진 인덱스를 탐색

	if (IsEmpty() == FALSE)
	{
		temp = Pop_stack();
		if ((temp.i == dir_ary[min_idx].i) && (temp.j == dir_ary[min_idx].j))
		{
			/*
			if (path_flag == 1)
			{
			path_flag = 0;
			Move_Point(map, 4, temp);
			}
			else
			{
			distance_result[min_idx] = 20;
			min_idx = 0;
			for (i = 0; i < 4; i++)//20인 인덱스의 갯수 세서 규칙 만들기
			{
			if (distance_result[i] < distance_result[min_idx])
			min_idx = i;
			}//거리의 최소값을 가진 인덱스를 탐색
			Move_Point(map, 0, dir_ary[min_idx]);//현재 위치를 지나온 길로 표시하고
			path_flag++;
			}
			*/

			

		}
			
		else
		{
			Push_stack(temp);
			Move_Point(map, 0,dir_ary[min_idx]);
		}
	}
	else
		Move_Point(map, 0, dir_ary[min_idx]);


	return break_signal;
}
void break_already_passed(int ***map)
{
	Point dir_ary[8] = { { Start.i, Start.j - 1 } ,{ Start.i - 1, Start.j - 1 },{ Start.i-1,Start.j },{ Start.i + 1, Start.j } };

}

int Path_selecter_new(int ***map)//Start, Goal은 항상 알고 있는 정보
{
	//앞으로 길을 선택할 기준: 골과의 좌표상 거리
	//특정 좌표가 정해지면 항상 계산해줘야 하는 정보
	int i;
	int false_cnt = 0;
	int true_cnt;
	int min_idx;
	int break_signal = FALSE;

	Point dir_ary[4] = { { Start.i, Start.j - 1 } ,{ Start.i - 1,Start.j },{ Start.i,Start.j + 1 },{ Start.i + 1, Start.j } };
	int result_ary[4];
	double distance_result[4];

	//경계값 및 벽을 고르는 경우를 제외
	for (i = 0; i < 4; i++)
		result_ary[i] = Wall_decter(map, dir_ary[i]) && Is_already_passed(map, dir_ary[i]);

	//거리 계산
	for (i = 0; i < 4; i++)
	{
		if (result_ary[i] == TRUE)//결과값이 참인 경우에만 거리를 계산
			distance_result[i] = Distance_calculator(dir_ary[i]);

		else
			distance_result[i] = 20;//랜덤으로 만들어진 맵의 최대 거리
	}

	false_cnt = result_false_cnt(result_ary);
	true_cnt = (4 - false_cnt);

	//지나온 길을 제외한 선택지가 2가지인 경우에 현재 위치 Push
	if (true_cnt == 2)
		Push_stack(Start);

	if (false_cnt == 4)
	{
		if (IsEmpty() == FALSE)
			Move_Point(map, 4, Pop_stack());
		else
		{

			break_signal = TRUE;
		}
			
	}
	else
	{
		min_idx = 0;
		for (i = 0; i < 4; i++)
		{
			if (distance_result[i] < distance_result[min_idx])
				min_idx = i;
		}//거리의 최소값을 가진 인덱스를 탐색

		Move_Point(map, 4, dir_ary[min_idx]);
	}
	

	return break_signal;
}