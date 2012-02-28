#include "StdAfx.h"

char fget8(FILE* fp)
{
	char v;
	fread(&v, 1, 1, fp);
	return v;
}

short fget16(FILE* fp)
{
	long v;
	fread(&v, 2, 1, fp);
	return BigEndian16(v);
}

long fget32(FILE* fp)
{
	long v;
	fread(&v, 4, 1, fp);
	return BigEndian32(v);
}
