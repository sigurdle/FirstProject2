#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

StringWriter::StringWriter()
{
}

StringWriter::StringWriter(const StringWriter& other) : TextWriter(other), m_str(other.m_str)
{
}

StringWriter::StringWriter(StringIn str) : m_str(str)
{
}

StringWriter& StringWriter::operator << (const StringBuilder& strbuilder)
{
	ASSERT(0);
	//m_str = StringBuilderstrbuilder, m_str);
	return *this;
}

size_t StringWriter::WriteChars(const char8* p, size_t len)
{
	m_str.Append(p, len);
	return len;
}

size_t StringWriter::WriteChars(const char16* p, size_t len)
{
	m_str.Append(p, len);
	return len;
}

size_t StringWriter::WriteChars(const char32_t* p, size_t len)
{
	VERIFY(0);
	//m_str.Append(p, len);
	return len;
}

}	// IO
}	// System
