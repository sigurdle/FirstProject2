#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

StreamReader::StreamReader()
{
}

StreamReader::StreamReader(Stream* baseStream) : m_baseStream(baseStream)
{
}

size_t StreamReader::ReadChars(char8* p, size_t len)
{
	return m_baseStream->ReadChars(p, len);
}

size_t StreamReader::ReadChars(char16* p, size_t len)
{
	return m_baseStream->ReadChars(p, len);
}

uint64 StreamReader::GetPosition()
{
	return m_baseStream->GetPosition();
}

}	// IO
}	// System
