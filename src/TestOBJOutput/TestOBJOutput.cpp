// TestOBJOutput.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

//extern "C" int test();
//extern "C" int test2(int, int);

/*
int test(char*** p, int n1, int n2, int n3)
{
	return p[n1][n2][n3];
}
*/

struct temp
{
	int a;
	int b;
	int c;
};

int xy()
{
	return 4;
}

int test3(temp* p, int n1, int* n2)
{
	return xy();
	//(*p).b = n1;
	//n2 = &(*p).b;
	//return n2;
}

//extern "C" int test2(temp* p, int n1, int* n2);

#include <windows.h>

extern "C" int msgbox(int arg0, int arg1);

int x;
int y;

int main(int argc, char* argv[])
{
//	8 = 6;

	if (x == 1)
	{
		y = 10;
	}
	else
	{
		y = 20;
	}

#if 0
	temp t;
	t.a = 1;
	t.b = 2;
	t.c = 3;

	MessageBox(NULL, "some other text", NULL, MB_OK);

	msgbox(1,2);

	/*
	{
		int x = test2(&t, 3, NULL);
		printf("%d\n", x);
	}
	*/


	{
		int y = 3;
		int x = test3(&t, 3, &y);
	}

	/*
	ar[0] = 5;
	ar[1] = 4;
	ar[2] = 3;
	ar[3] = 2;
	ar[4] = 1;
	ar[5] = 0;
	int x = test2(ar, 2, 4);
	*/

//	int x = test();
//	printf("%d\n", x);
#endif
	return 0;
}
