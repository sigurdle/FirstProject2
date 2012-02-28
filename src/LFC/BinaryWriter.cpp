#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

BinaryWriter::BinaryWriter() : m_bufferpos(0)
{
}

BinaryWriter::BinaryWriter(Stream* baseStream) : m_baseStream(baseStream), m_bufferpos(0)
{
}

void BinaryWriter::Flush()
{
	m_baseStream->Write(m_buffer, m_bufferpos);
	m_bufferpos = 0;
}

inline void BinaryWriter::putbyte(ubyte v)
{
	if (m_bufferpos == m_buffersize)
	{
		Flush();
	}

	m_buffer[m_bufferpos++] = v;
}

size_t BinaryWriter::Write(const void* pv, size_t len)
{
	return m_baseStream->Write(pv, len);
}

void BinaryWriter::Write(bool bit)
{
	Write(&bit, sizeof(bit));
}

void BinaryWriter::Write(char ch)
{
	Write(&ch, sizeof(ch));
}

void BinaryWriter::Write(wchar_t ch)
{
	Write(&ch, sizeof(ch));
}

void BinaryWriter::Write(signed char number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(unsigned char number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(short number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(unsigned short number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(int number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(unsigned int number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(long number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(unsigned long number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(int64 number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(uint64 number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(float number)
{
	Write(&number, sizeof(number));
}

void BinaryWriter::Write(double number)
{
	Write(&number, sizeof(number));
}

/*
inline void BinaryWriter::putshort(ubyte v1, ubyte v2)
{
	if (m_bufferpos == m_buffersize)
	{
		Flush();

		m_buffer[m_bufferpos++] = v1;
		m_buffer[m_bufferpos++] = v2;
	}
	else if (m_bufferpos == m_buffersize-1)
	{
		m_buffer[m_bufferpos++] = v1;
		Flush();
		m_buffer[m_bufferpos++] = v2;
	}
	else
	{
		m_buffer[m_bufferpos++] = v1;
		m_buffer[m_bufferpos++] = v2;
	}
}
*/

/*
BinaryWriter& BinaryWriter::operator << (bool bit)
{
	putbyte(bit);
	return *this;
}

BinaryWriter& BinaryWriter::operator << (char ch)
{
	putbyte(ch);
	return *this;
}

BinaryWriter& BinaryWriter::operator << (short value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (unsigned short value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (int value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (unsigned int value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (long value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (unsigned long value)
{
	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (float fvalue)
{
	int value = *(int*)&fvalue;

	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);

	return *this;
}

BinaryWriter& BinaryWriter::operator << (double fvalue)
{
	int64 value = *(int64*)&fvalue;

	putbyte(value & 0xFF);
	putbyte((value>>8) & 0xFF);
	putbyte((value>>16) & 0xFF);
	putbyte((value>>24) & 0xFF);
	putbyte((value>>32) & 0xFF);
	putbyte((value>>40) & 0xFF);
	putbyte((value>>48) & 0xFF);
	putbyte((value>>56) & 0xFF);

	return *this;
}
*/

}	// IO
}	// System
