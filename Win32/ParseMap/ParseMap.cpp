// ParseMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE* fp = fopen(argv[1], "r");
	if (fp)
	{
		fscanf(fp, "");
		fclose(fp);
	}

	return 0;
}
