#include "stdafx.h"
#include "LFC.h"

namespace System
{
namespace IO
{

//Writer s(new StringWriter());

// static
//DebugStreamObject* DebugStreamObject::_out = new DebugStreamObject();
DebugStream DebugStream::_out;

bool DebugStream::IsNull() const
{
	/*
	IO::_Ptr<StringWriter> writer;

	writer << "Hello" << 7;

	WriteToStream(writer, String("Hello"));
	*/

	return ! ::IsDebuggerPresent();
}

size_t DebugStream::WriteCStr(const char* str)
{
	size_t len = cstrlen(str);
	OutputDebugStringA(str);
	m_position += len;
	return len;
}

size_t DebugStream::WriteCStr(const wchar_t* str)
{
	size_t len = cstrlen(str);
	OutputDebugStringW(str);
	m_position += len;
	return len;
}

size_t DebugStream::WriteChars(const char* p, size_t len)
{
	char* t = (char*)_alloca(len+1);
	memcpy(t, p, len);
	t[len] = 0;

	OutputDebugStringA(t);
	m_position += len;
	return len;
}

size_t DebugStream::WriteChars(const wchar_t* p, size_t len)
{
	wchar_t* t = (wchar_t*)_alloca((len+1)*sizeof(wchar_t));
	memcpy(t, p, len*sizeof(wchar_t));
	t[len] = 0;

	OutputDebugStringW(t);
	m_position += len;
	return len;
}

}	// IO
}	// System
