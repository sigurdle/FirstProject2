#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

BinaryReader::BinaryReader()
{
}

BinaryReader::BinaryReader(Stream* baseStream) : m_baseStream(baseStream)
{
}

size_t BinaryReader::Read(void* pv, size_t len)
{
	return m_baseStream->Read(pv, len);
}

uint64 BinaryReader::GetPosition()
{
	return m_baseStream->GetPosition();
}

bool BinaryReader::ReadBool()
{
	bool value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

char BinaryReader::ReadChar()
{
	char value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

wchar_t BinaryReader::ReadWChar()
{
	wchar_t value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

signed char BinaryReader::ReadSByte()
{
	signed char value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

unsigned char BinaryReader::ReadUByte()
{
	unsigned char value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

short BinaryReader::ReadShort()
{
	short value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

unsigned short BinaryReader::ReadUShort()
{
	unsigned short value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

int BinaryReader::ReadInt()
{
	int value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

unsigned int BinaryReader::ReadUInt()
{
	unsigned int value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

long BinaryReader::ReadLong()
{
	long value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

unsigned long BinaryReader::ReadULong()
{
	unsigned long value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

int64 BinaryReader::ReadInt64()
{
	int64 value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

uint64 BinaryReader::ReadUInt64()
{
	uint64 value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

float BinaryReader::ReadFloat()
{
	float value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

double BinaryReader::ReadDouble()
{
	double value;
	size_t nRead = Read(&value, sizeof(value));
	if (nRead != sizeof(value))
	{
		raise(IOException("IO Read failed in " + m_baseStream->GetFilename()));
	}
	return value;
}

}	// IO
}	// System
