#include "stdafx.h"
#include <stdio.h>

namespace System
{
using namespace std;

CodeCompExt void fput8(FILE* fp, uint8 v)
{
	fwrite(&v, 1, 1, fp);
}

CodeCompExt void fput16(FILE* fp, uint16 v)
{
	uint16 v2 = BigEndian16(v);
	fwrite(&v2, 1, 2, fp);
}

CodeCompExt void fput32(FILE* fp, uint32 v)
{
	uint32 v2 = BigEndian32(v);
	fwrite(&v2, 1, 4, fp);
}

//FILE* fileout;

int m_line = 0;
int m_warnings = 0;
int m_errors = 0;

int m_try = 0;


void __cdecl jwarn(const char* msg, ...)
{
	printf("line: %d : warn : ", m_line+1);
	printf(msg);
	fprintf(stdout, "\n");

	m_warnings++;
}

void __cdecl jerror(const char* msg, ...)
{
	if (m_try == 0)
	{
		printf("line: %d : error : ", m_line+1);
		printf(msg);
		fprintf(stdout, "\n");
		m_errors++;
	//	exit(1);
	}
	else
	{
	//	THROW(-1);
	}
}

void __cdecl jfatalerror(const char* msg, ...)
{
	if (m_try == 0)
	{
		printf("line: %d : fatal error : ", m_line+1);
		printf(msg);
		fprintf(stdout, "\n");
		VERIFY(0);
	}
	else
	{
		THROW(-1);
	}
}

}
