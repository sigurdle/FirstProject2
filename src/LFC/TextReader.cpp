#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

TextReader::TextReader()
{
}

bool TextReader::ReadBool()
{
	bool value = 0;
	return value;
}

char TextReader::ReadChar()
{
	char value = (char)ReadCharacter();
	return value;
}

wchar_t TextReader::ReadWChar()
{
	wchar_t value = (wchar_t)ReadCharacter();
	return value;
}

signed char TextReader::ReadSByte()
{
	signed char value = 0;
	return value;
}

unsigned char TextReader::ReadUByte()
{
	unsigned char value = 0;
	return value;
}

short TextReader::ReadShort()
{
	short value = 0;
	return value;
}

unsigned short TextReader::ReadUShort()
{
	unsigned short value = 0;
	return value;
}

int TextReader::ReadInt()
{
	int value = 0;
	return value;
}

unsigned int TextReader::ReadUInt()
{
	unsigned int value = 0;
	return value;
}

long TextReader::ReadLong()
{
	long value = 0;
	return value;
}

unsigned long TextReader::ReadULong()
{
	unsigned long value = 0;
	return value;
}

int64 TextReader::ReadInt64()
{
	int64 value = 0;
	return value;
}

uint64 TextReader::ReadUInt64()
{
	uint64 value = 0;
	return value;
}

float TextReader::ReadFloat()
{
	float value = 0;
	return value;
}

double TextReader::ReadDouble()
{
	double value = 0;
	return value;
}

/*
long double TextReader::ReadLongDouble()
{
	long double value = 0;
	return value;
}
*/

String TextReader::ReadLine()
{
	String str;

	while (1)
	{
		int ch;

		if ((ch = ReadCharacter()) == -1)
			break;

		if (ch == '\n')
			break;

		str += (char)ch;
	}

	return str;
}

String TextReader::ReadToEol()
{
	String str;
	return str;
}

String TextReader::ReadToEof()
{
	String str;
	return str;
}

IO::TextReader& ReadFromStream(IO::TextReader& stream, int& number)
{
	number = 0;

	char c;

	stream >> c;

	while (isdigit(c))
	{
	//	char c = m_c;
	//	adv();

		number = number*10 + (c - '0');
		stream >> c;
	}

	return stream;
}

}	// IO
}	// System
