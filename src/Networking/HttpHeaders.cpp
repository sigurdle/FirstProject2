#include "stdafx.h"
#include "LFC/LFC.h"
#include "HttpHeaders.h"

namespace System
{
namespace Net
{

void HttpHeaders::AddHeader(StringIn header, StringIn value)
{
	// TODO, check input

	m_headerlines.insert(tyheadermap::value_type(header, value));
}

void HttpHeaders::AddHeaders(StringIn lines)
{
	m_all += lines;

	const char* p = lines.GetData8();
	const char* end = lines.GetData8() + lines.GetLength();
	while (p != end)
	{
		if (p[0] == '\r' && p[1] == '\n')
			break;

		IO::StringWriter stream;

	//	const char* p = line.c_str();
		while (*p)
		{
			if (*p == ':' || *p == ' ')
				break;
			stream << *p;
			p++;
		}
		while (*p == ' ') p++;
		if (*p != ':')
		{
			raise(Exception(L"Not :"));
			ASSERT(0);
		}
		p++;

		String name = stream.str();

		while (*p == ' ') p++;

		while (*p)
		{
			if (p[0] == '\r' && p[1] == '\n')
				break;

			stream << *p;
			p++;
		}

		if (p[0] != '\r' || p[1] != '\n')
		{
			raise(Exception(S("Not \r or \n")));
		}
		p += 2;

		String value = stream.Detach();

		m_headerlines.insert(tyheadermap::value_type(name, value));
	}
}

String HttpHeaders::GetHeaderValue(StringIn name, int index) const
{
	for (auto it = m_headerlines.find(name); it != m_headerlines.end(); ++it)
	{
		if (index == 0)
		{
			return it->second;
			//return value->Length();
		}

		--index;
	}

	return nullptr;
}

}	// Net
}	// System
