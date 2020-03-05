#include"ALL.h"

Stack *top;

int main()
{
	srand((unsigned int)time(NULL));
	int **map = Make_map();
	
	Make_road(map);

	
	system("pause");
}