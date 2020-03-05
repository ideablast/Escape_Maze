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
	int cnt = 0;

	temp = (int**)malloc(size * sizeof(int*));
	for (size_j = 0; size_j < size; size_j++)
		temp[size_j] = (int*)malloc(sizeof(int));

	return temp;
}

void Make_road(int***map)
{
	int size = _msize(map) / sizeof(int*);


}

void clear_buf()//버퍼 비우기
{
	while (getchar() != '\n');
}
char* get_string_return_ptr()//문자열의 길이에 따라서 능동적으로 배열의 할당 메모리를 조절하여 입력받는 함수
{
	//이 방식이 좀더 안정적일것 같은 느낌적인 느낌?
	//받아서 쓰는 방식이 좋을까 
	//내부에서 입력 받은 것을 리턴하는 방식이 좋을까?

	char *temp;
	unsigned int str_len = 2;//문자열의 길이 정보를 저장하고 있는 배열
	char ch = 0;
	unsigned int cnt = 0;


	temp = (char*)malloc(str_len * sizeof(char));

	while (ch != '\n')//입력 받은 문자가 엔터이면 바로 루프 탈출
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
	temp = (char*)realloc(temp, (str_len + 1) * sizeof(char));//엔터를 입력받은 경우에는 1바이트 메모리 할당

	cnt = 0;
	ch = 0;
	//정확하게 문자열의 형태로 저장
	//예를 들어 [123456\0]을 입력했으면 메모리 7바이트가 리턴
	//strlen시 6리턴
	//malloc는 7바이트 해줘야함
	return temp;
}