#include "stdafx.h"
#include "GUI2.h"

namespace System
{

int loadobj(StringIn filename)
{
	FILE* fp;
	fopen_s(&fp, CString(filename), "r");
	if (fp == NULL)
	{
		return -1;
	}

	while (!feof(fp))
	{
		char type[32];
		fscanf_s(fp, "%s", type, _countof(type));
		if (!strcmp(type, "v"))
		{
			double v[3];
			fscanf_s(fp, "%f %f %f", &v[0], &v[1], &v[2]);

		}
	}

	return 0;
}

}
