#include"ALL.h"

extern Stack *top;
extern Point Start;
extern Point Goal;
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

	printf("0����:%lf\n", zero_cnt / (double)(size*size));
	printf("1����:%lf\n", one_cnt / (double)(size*size));

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

//-1:�ʱ�ȭ 0��:�� 1��:�� 2��:���� 3��:���� 4:�̹� �ѹ� ������ ��
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
				printf("��");
				break;
			case 1:
				printf("��");
				break;
			case 2:
				printf("��");
				break;
			case 3:
				printf("��");
				break;
			case 4:
				printf("��");
				break;
			}
		}
		printf("\n");
	}
}
//������ �Ǵ� ���?
//��谪�� �� Ȯ�� �� ��
//���� ���� �� Ȯ�� �� ��
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

	if (!((temp.i) >= 0 && (temp.i) < Boundary))//��谪�� �Ѿ�� ���
		result = FALSE;
	else//��谪 �̳��� �ִ� ���� ���
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
			result = TRUE;//���� �ƴ�->�� �� �ִ� ��
		else
			result = FALSE;
	}
	else//��谪 ����� ���
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
	int break_signal;
	int result_false_cnt = 0;
	static int path_flag = 0;
	
	for (i = 0; i < 4; i++)
		result_ary[i] = Wall_decter(map, dir_ary[i])&&Is_already_passed(map, dir_ary[i]);

	for (i = 0; i < 4; i++)
	{
		if (result_ary[i] == TRUE)//������� ���� ��쿡�� �Ÿ��� ���
			distance_result[i] = Distance_calculator(dir_ary[i]);

		else
			distance_result[i] = 20;
	}

	for (i = 0; i < 4; i++)
	{
		if (result_ary[i] == FALSE)
			result_false_cnt++;

		if (result_false_cnt == 4)
			break_signal = FALSE;
	}

	min_idx = 0;
	for (i = 0; i < 4; i++)
	{
		if (distance_result[i] < distance_result[min_idx])
			min_idx = i;
	}//�Ÿ��� �ּҰ��� ���� �ε����� Ž��

	if (IsEmpty() == FALSE)
	{
		temp = Pop_stack();
		if ((temp.i == dir_ary[min_idx].i) && (temp.j == dir_ary[min_idx].j))
		{

			if (path_flag == 1)
			{
				path_flag = 0;
				Move_Point(map, 4, temp);
			}
			else
			{
				distance_result[min_idx] = 20;
				min_idx = 0;
				for (i = 0; i < 4; i++)//20�� �ε����� ���� ���� ��Ģ �����
				{
					if (distance_result[i] < distance_result[min_idx])
						min_idx = i;
				}//�Ÿ��� �ּҰ��� ���� �ε����� Ž��
				Move_Point(map, 0, dir_ary[min_idx]);//���� ��ġ�� ������ ��� ǥ���ϰ� 
				path_flag++;
			}

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
