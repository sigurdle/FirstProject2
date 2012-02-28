#include "stdafx.h"
#include "LXUI2.h"
#include "HttpHeaders.h"

namespace System
{

void HttpHeaders::AddHeaders(StringA* lines)
{
	const char* p = lines->c_str();
	while (*p)
	{
		if (p[0] == '\r' && p[1] == '\n')
			break;

		BufferImp<char> buffer;
		StringBuilder<char> stream(&buffer);

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
			THROW(-1);
		p++;

		StringA* name = buffer.DetachToString();

		while (*p == ' ') p++;

		while (*p)
		{
			if (p[0] == '\r' && p[1] == '\n')
				break;

			stream << *p;
			p++;
		}

		if (p[0] != '\r' || p[1] != '\n')
			THROW(-1);
		p += 2;

		StringA* value = buffer.DetachToString();

		m_headerlines.insert(tyheadermap::value_type(name, value));
	}
}

StringA* HttpHeaders::GetHeaderValue(StringA* name, int index) const
{
	tyheadermap::const_iterator it = m_headerlines.find(name);
	while (it != m_headerlines.end())
	{
		if (index == 0)
		{
			return (*it).second;
			//return value->Length();
		}

		index--;
		++it;
	}

	return NULL;
}

}
