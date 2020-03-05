#ifndef __Data_H__
#define __Data_H__

typedef struct _Point {
	int i;
	int j;
}Point;

typedef struct _Stack {
	struct _Point Point;
	struct _Stack *Link;
}Stack;



#endif

#define TRUE 1
#define FALSE 0
#define FAIL -1

