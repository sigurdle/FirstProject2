#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosBoolean.h"

namespace System
{
namespace PDF
{

void CPDFCosBoolean::ReadFromStream(std::FILE* fp)
{
	int c = std::fgetc(fp);
	if (c == 't')
	{
		if (std::fgetc(fp) != 'r') throw -1;
		if (std::fgetc(fp) != 'u') throw -1;
		if (std::fgetc(fp) != 'e') throw -1;

		m_value = true;
	}
	else if (c == 'f')
	{
		if (std::fgetc(fp) != 'a') throw -1;
		if (std::fgetc(fp) != 'l') throw -1;
		if (std::fgetc(fp) != 's') throw -1;
		if (std::fgetc(fp) != 'e') throw -1;

		m_value = false;
	}
	else
	{
		ASSERT(0);
		throw -1;
	}
}

void CPDFCosBoolean::WriteToStream(std::FILE* fp)
{
	ASSERT(0);
}

}
}
