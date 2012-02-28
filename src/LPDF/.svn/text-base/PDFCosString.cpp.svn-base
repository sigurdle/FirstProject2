#include "stdafx.h"
#include "LPDF.h"
#include "PDFCosString.h"

namespace System
{
namespace PDF
{

int Hex2Number(char c)
{
	if (c >= '0' && c <= '9')
	{
		return c - '0';
	}
	else
	{
		c = std::tolower(c);
		ASSERT(c >= 'a' && c <= 'f');

		return 10 + c - 'a';
	}
}

CPDFCosString::CPDFCosString()
{
	m_value = NULL;
}

void CPDFCosString::WriteToStream(std::FILE* fp)
{
	ASSERT(0);
}

void CPDFCosString::ReadFromStream(std::FILE* fp)
{
	BufferImp<char> buffer;
	StringBuilderA stream(&buffer);

	//m_value = StringA();

	int delim = std::fgetc(fp);

	if (delim == '<')	// hexadecimal string
	{
		while (1)
		{
			int c;
			
			char ch;

		////////////
			do
			{
				c = std::fgetc(fp);
			}
			while (std::isspace(c));	// ignore white space

			if (c == '>')
				break;

			ch = Hex2Number(c)<<4;

		////////////
			do
			{
				c = std::fgetc(fp);
			}
			while (std::isspace(c));	// ignore white space

			if (c == '>')
			{
				stream << (char)ch;
				break;
			}

			ch |= Hex2Number(c);

			stream << (char)ch;
		}
	}
	else if (delim == '(')
	{
		while (1)
		{
			int c = std::fgetc(fp);
			if (c == ')')
				break;

			if (c == '\\')
			{
				int c2 = std::fgetc(fp);
				if (c2 == 'n') stream << '\n';
				if (c2 == 'r') stream << '\r';
				if (c2 == 't') stream << '\t';
				if (c2 == 'b') stream << '\b';
				if (c2 == 'f') stream << '\f';
				if (c2 == '(') stream << '(';
				if (c2 == ')') stream << ')';
				if (c2 == '\\') stream << '\\';
			}
			else
			{
				stream << (char)c;
			}
		}
	}

	m_value = buffer.DetachToString();
}

StringA* CPDFCosString::GetValue()
{
	return m_value;
}

}	// PDF
}
