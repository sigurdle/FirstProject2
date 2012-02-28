#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

StreamWriter::StreamWriter()
{
}

StreamWriter::StreamWriter(Stream* baseStream) : m_baseStream(baseStream)
{
}

size_t StreamWriter::WriteChars(const char8* p, size_t len)
{
	return m_baseStream->WriteChars(p, len);
}

size_t StreamWriter::WriteChars(const char16* p, size_t len)
{
	return m_baseStream->WriteChars(p, len);
}

}	// IO
}	// System
