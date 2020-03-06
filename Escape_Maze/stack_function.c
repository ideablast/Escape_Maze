#include"ALL.h"

extern Stack *top;
/*BASIC_STACK*/

Stack* Add_new_stack()
{
	Stack *temp = (Stack*)malloc(sizeof(Stack));
	temp->Point.i = 0;
	temp->Point.j = 0;

	temp->Link = NULL;

	return temp;
}

void Push_stack(int i, int j)
{
	Stack *temp = Add_new_stack();
	temp->Point.i = i;
	temp->Point.j = j;

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
	Stack Rand_Start;
	Stack Rand_Goal;

	int cnt = 0;
	int zero_cnt = 0;
	int one_cnt = 0;

	temp = (int**)malloc(size * sizeof(int*));
	for (size_j = 0; size_j < size; size_j++)
		temp[size_j] = (int*)malloc(size*sizeof(int));

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
		Rand_Start.Point.i = rand() % size;
		Rand_Start.Point.j = rand() % size;

		if (temp[Rand_Start.Point.i][Rand_Start.Point.j] == 0)
		{
			temp[Rand_Start.Point.i][Rand_Start.Point.j] = 2;
			break;
		}
	}
	
	while (1)
	{
		Rand_Goal.Point.i = rand() % size;
		Rand_Goal.Point.j = rand() % size;

		if (temp[Rand_Goal.Point.i][Rand_Goal.Point.j]==0 && temp[Rand_Goal.Point.i][Rand_Goal.Point.j] != 2)
		{
			temp[Rand_Goal.Point.i][Rand_Goal.Point.j] = 3;
			break; 
		}

	}

	Push_stack(Rand_Start.Point.i, Rand_Start.Point.j);
	Push_stack(Rand_Goal.Point.i, Rand_Goal.Point.j);

	return temp;
}

//-1:�ʱ�ȭ 0��:�� 1��:�� 2��:���� 3��:����
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
			}
		}
		printf("\n");
	}
}

void clear_buf()//���� ����
{
	while (getchar() != '\n');
}
char* get_string_return_ptr()//���ڿ��� ���̿� ���� �ɵ������� �迭�� �Ҵ� �޸𸮸� �����Ͽ� �Է¹޴� �Լ�
{
	//�� ����� ���� �������ϰ� ���� �������� ����?
	//�޾Ƽ� ���� ����� ������ 
	//���ο��� �Է� ���� ���� �����ϴ� ����� ������?

	char *temp;
	unsigned int str_len = 2;//���ڿ��� ���� ������ �����ϰ� �ִ� �迭
	char ch = 0;
	unsigned int cnt = 0;


	temp = (char*)malloc(str_len * sizeof(char));

	while (ch != '\n')//�Է� ���� ���ڰ� �����̸� �ٷ� ���� Ż��
	{
		if (str_len > cnt)
		{
			ch = getchar();
			temp[cnt] = ch;
			cnt++;
		}

		else
		{
			str_len += 5;
			temp = (char*)realloc(temp, (str_len) * sizeof(char));
		}
	}

	temp[cnt - 1] = '\0';
	str_len = strlen(temp);
	temp = (char*)realloc(temp, (str_len + 1) * sizeof(char));//���͸� �Է¹��� ��쿡�� 1����Ʈ �޸� �Ҵ�

	cnt = 0;
	ch = 0;
	//��Ȯ�ϰ� ���ڿ��� ���·� ����
	//���� ��� [123456\0]�� �Է������� �޸� 7����Ʈ�� ����
	//strlen�� 6����
	//malloc�� 7����Ʈ �������
	return temp;
}

#ifdef NOTYET
Point Stack_to_Point(Stack temp)
{
	Point P_temp;
	P_temp.i = temp.Point.i;
	P_temp.j = temp.Point.j;

	return P_temp;
}
#endif