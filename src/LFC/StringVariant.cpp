#include "stdafx.h"
#include "LFC.h"

namespace System
{

extern byte* data;
extern byte* enddata;

StringVariant::StringVariant(const StringBuilderBase& builder) : m_cstr(nullptr), m_cstrw(nullptr)
{
	m_stringObject = builder.BuildString();
	if (m_stringObject)
	{
		m_stringObject->IncRef();
		m_len = m_stringObject->GetLength();
	}
	else
	{
		m_len = 0;
	}
}

StringVariant::StringVariant(StringObject* stringObject) : m_stringObject(stringObject), m_cstr(NULL), m_cstrw(NULL)
{
	if (m_stringObject)
	{
		m_stringObject->IncRef();
		m_len = m_stringObject->GetLength();
	}
	else
	{
		m_len = 0;
	}
}

uint32 StringVariant::_SubString::GetLength32() const throw (SystemException*)
{
	if (m_len > UINT_MAX)
	{
		raise(SystemException("String too long"));
	}
	return (uint32)m_len;
}

bool StringVariant::operator == (const wchar_t* cstr) const
{
	if (IsEmpty())
	{
		return cstr == NULL;	// Both are null, return true
	}
	else if (cstr == NULL)
	{
		return false;
	}

	if (m_stringObject)
	{
		return m_stringObject->Compare(cstr) == 0;
	}
	else if (m_cstr)
	{
		ASSERT(0);
		return false;
		//return strcmp(m_cstr, cstr) == 0;
	}
	else
	{
		ASSERT(m_cstrw);
		return wcscmp(m_cstrw, cstr) == 0;
	}
}

StringBuilderTwo StringVariant::_SubString::operator + (StringVariant str) const
{
	return StringBuilderTwo(str, operator String());
}

StringBuilderTwo StringVariant::_SubString::operator + (const char* cstr) const
{
	return StringBuilderTwo(cstr, operator String());
}

StringBuilderTwo StringVariant::operator + (const StringVariant& other) const
{
	return StringBuilderTwo(other, *this);
}

bool StringVariant::operator < (const String& str) const
{
	if (m_stringObject == str.m_stringObject) return false;
	
	if (IsEmpty()) return (str.m_stringObject != NULL);
	else if (str.m_stringObject == NULL) return false;

	if (m_stringObject)
	{
		return m_stringObject->Compare(str.m_stringObject) < 0;
	}
	else if (m_cstr)
	{
		return m_stringObject->Compare(m_cstr) < 0;
	}
	else
	{
		return m_stringObject->Compare(m_cstrw) < 0;
	}
}

size_t StringVariant::find(uint32 ch, size_t startoffset) const
{
	if (startoffset > GetLength())
	{
		raise(ArgumentOutOfRangeException());
	}

	if (m_stringObject)
	{
		return m_stringObject->Find(ch, startoffset);
	}
	else if (m_cstr)
	{
	//	if (startoffset >= m_len) return -1;

		const char* p = strchr(m_cstr + startoffset, ch);
		if (p)
			return p - m_cstr;
		else
			return -1;
	}
	else if (m_cstrw)
	{
	//	if (startoffset >= m_len) return -1;

		const wchar_t* p = wcschr(m_cstrw + startoffset, ch);
		if (p)
			return p - m_cstrw;
		else
			return -1;
	}
	else
		return -1;
}

size_t StringVariant::rfind(uint32 ch, size_t startoffset) const
{
	size_t len = GetLength();
	
	if (len == 0) return npos;

	if (startoffset == npos) startoffset = len-1;
	else if (startoffset >= len) return npos;

	if (m_stringObject)
	{
		if (m_stringObject->GetCharSize() == 1)
		{
			char* data = (char*)m_stringObject->GetData();

			for (size_t i = startoffset; i != (size_t)-1; --i)
			{
				if (data[i] == ch) return i;
			}

			return npos;
		}
		else
		{
			wchar_t* data = (wchar_t*)m_stringObject->GetData();

			for (size_t i = startoffset; i != (size_t)-1; --i)
			{
				if (data[i] == ch) return i;
			}

			return npos;
		}
		//return m_stringObject->Find(ch);
	}
	else if (m_cstr)
	{
		const char* p = m_cstr;

		for (size_t i = startoffset; i != (size_t)-1; --i)
		{
			if (p[i] == ch) return i;
		}

		return npos;
	}
	else if (m_cstrw)
	{
		const wchar_t* p = m_cstrw;

		for (size_t i = startoffset; i != (size_t)-1; --i)
		{
			if (p[i] == ch) return i;
		}

		return npos;
	}
	else
		return npos;
}

ptrdiff_t StringVariant::Find(char* cstr, size_t startoffset) const
{
	if (startoffset > GetLength())
	{
		raise(ArgumentOutOfRangeException());
	}

	if (m_stringObject)
	{
		String c(m_stringObject);
		CString str(c);

		const char* p = strstr(str.c_str() + startoffset, cstr);
		if (p == nullptr)
			return -1;
		else
			return p - str.c_str();
	}
	else if (m_cstr)
	{
		const char* p = strstr(m_cstr + startoffset, cstr);
		if (p == nullptr)
			return -1;
		else
			return p - m_cstr;
	}
	else if (m_cstrw)
	{
		size_t len = strlen(cstr);

		wchar_t* cstr2 = (wchar_t*)_alloca(sizeof(wchar_t)*(len+1));
		for (size_t i = 0; i < len; ++i)
		{
			cstr2[i] = cstr[i];
		}
		cstr2[len] = 0;

		const wchar_t* p = wcsstr(m_cstrw + startoffset, cstr2);
		if (p == nullptr)
			return -1;
		else
			return p - m_cstrw;
	}
	else
		ASSERT(0);

	return -1;
}

ptrdiff_t StringVariant::Find(wchar_t* cstr, size_t startoffset) const
{
	if (startoffset > GetLength())
	{
		raise(ArgumentOutOfRangeException());
	}

	if (m_cstrw)
	{
		const wchar_t* p = wcsstr(m_cstrw + startoffset, cstr);
		if (p == nullptr)
			return -1;
		else
			return p - m_cstrw;
	}
	else
		ASSERT(0);

	return -1;
}

bool StringVariant::_SubString::Equals(const char8* cstr) const
{
	if (m_stringObject)
	{
		return m_stringObject->SubCompare(m_offset, m_len, cstr, strlen(cstr)) == 0;
	}
	else if (m_cstr)
	{
		size_t len = m_len;//strlen(m_cstr) - m_offset;
		const char* p = m_cstr + m_offset;

		while (len--)
		{
			if (*p != *cstr) return false;
			++p;
			++cstr;
		}
		return true;
	}
	else
	{
		size_t len = m_len;//wcslen(m_cstrw) - m_offset;
		const char16* p = m_cstrw + m_offset;

		while (len--)
		{
			if (*p != (wchar_t)*cstr) return false;
			++p;
			++cstr;
		}
		return true;
	}
}

bool StringVariant::_SubString::Equals(const char16* cstr) const
{
	if (m_stringObject)
	{
		return m_stringObject->SubCompare(m_offset, m_len, cstr, wcslen(cstr)) == 0;
	}
	else if (m_cstr)
	{
		size_t len = strlen(m_cstr) - m_offset;
		const char* p = m_cstr + m_offset;

		while (len--)
		{
			if ((char16)*p != *cstr) return false;
			++p;
			++cstr;
		}
		return true;
	}
	else
	{
		size_t len = wcslen(m_cstrw) - m_offset;
		const wchar_t* p = m_cstrw + m_offset;

		while (len--)
		{
			if (*p != *cstr) return false;
			++p;
			++cstr;
		}
		return true;
	}
}

int StringVariant::_SubString::Compare(const char8* cstr) const
{
	if (m_stringObject)
	{
		return m_stringObject->SubCompare(m_offset, m_len, cstr, strlen(cstr));
	}
	else if (m_cstr)
	{
		size_t len = strlen(m_cstr) - m_offset;
		const char* p = m_cstr + m_offset;

		while (len--)
		{
			int diff = *p - *cstr;
			if (diff) return diff;
			++p;
			++cstr;
		}
		return 0;
	}
	else
	{
		ASSERT(0);
		return 0;
	}
}

int StringVariant::_SubString::Compare(const char16* cstr) const
{
	ASSERT(0);
	return 0;
}

StringVariant::operator String ()
{
	if (m_stringObject) return m_stringObject;
	
	if (m_cstr) (m_stringObject = new ImmutableString<char>(string_data<char>(m_cstr)))->IncRef();
	else if (m_cstrw) (m_stringObject = new ImmutableString<wchar_t>(string_data<wchar_t>(m_cstrw)))->IncRef();
	
	return m_stringObject;
}

StringVariant::operator String () const
{
	if (m_stringObject) return String(m_stringObject);
	else if (m_cstr) return String(string_data<char>(m_cstr));
	else if (m_cstrw) return String(string_data<wchar_t>(m_cstrw));
	else return nullptr;
}

const char* StringVariant::c_str()
{
	if (m_cstr)
	{
		return m_cstr;
	}
	else if (m_cstrw)
	{
		raise(SystemException(S("cstrw to cstr")));
	}
	else if (m_stringObject)
	{
		size_t len = m_stringObject->GetLength();
		char* cstr = new char[len+1];
		m_stringObject->CopyTo(cstr, len);
		cstr[len] = 0;
		m_cstr = cstr;
	}

	return m_cstr;
}

const wchar_t* StringVariant::c_strw()
{
	if (m_cstrw)
	{
		return m_cstrw;
	}
	else if (m_cstr)
	{
		size_t len = cstrlen(m_cstr);
		wchar_t* cstrw = new wchar_t[len+1];
		for (size_t i = 0; i < len; ++i)
		{
			cstrw[i] = m_cstr[i];
		}
		cstrw[len] = 0;
		m_cstrw = cstrw;
	}
	else if (m_stringObject)
	{
		size_t len = m_stringObject->GetLength();
		wchar_t* cstrw = new wchar_t[len+1];
		m_stringObject->CopyTo(cstrw, len);
		cstrw[len] = 0;

		m_cstrw = cstrw;
	}

	return m_cstrw;
}

std::string StringVariant::ToStdString() const
{
	if (m_cstr)
	{
		return std::string(m_cstr);
	}
	else
	{
		// TODO
		ASSERT(0);
	}

	return NULL;
}

std::wstring StringVariant::ToStdWString() const
{
	if (m_cstrw)
	{
		return std::wstring(m_cstrw);
	}
	else
	{
		// TODO
		ASSERT(0);
	}

	return NULL;
}

bool StringVariant::operator == (const StringBuilderBase& str) const
{
	return *this == str.BuildString();
}

bool StringVariant::Equals(const String& str) const
{
	// TODO: is not right
	if (m_stringObject == str.m_stringObject) return true;
	else if (IsEmpty()) return (str.m_stringObject == nullptr);	// Return true if both are null
	else if (str.m_stringObject == nullptr) return false;

	if (m_stringObject)
	{
		return m_stringObject->Compare(str.m_stringObject) == 0;
	}
	else if (m_cstr)
	{
		return str.m_stringObject->Compare(m_cstr) == 0;
	}
	else
	{
		return str.m_stringObject->Compare(m_cstrw) == 0;
	}
}

int StringVariant::Compare(const String& str) const
{
	if (m_stringObject == str.m_stringObject) return 0;
	// TODO
//	else if (IsEmpty()) return (str.m_stringObject == NULL);	// Return true if both are null
//	else if (str.m_stringObject == NULL) return false;

	if (m_stringObject)
	{
		return m_stringObject->Compare(str.m_stringObject);
	}
	else if (m_cstr)
	{
		return str.m_stringObject->Compare(m_cstr);
	}
	else
	{
		return str.m_stringObject->Compare(m_cstrw);
	}
}

int StringVariant::Compare(const char16* cstrw) const
{
	if (IsEmpty())
	{
		if (cstrw == NULL)
			return 0;
		else
			return -1;
	}
	else if (cstrw == NULL)
	{
		return 1;
	}

	if (m_stringObject)
	{
		return m_stringObject->Compare(cstrw);
	}
	else if (m_cstr)
	{
		ASSERT(0);
		return 0;//str.m_stringObject->Compare(m_cstr);
	}
	else
	{
		size_t len = __min(cstrlen(m_cstrw), cstrlen(cstrw));
		return wmemcmp(m_cstrw, cstrw, len);
	}
}

int StringVariant::CompareNoCase(const char8* cstr) const
{
	ASSERT(0);
	return 0;
}

int StringVariant::CompareNoCase(const char16* cstr) const
{
	ASSERT(0);
	return 0;
}

int StringVariant::CompareNoCase(StringObject* str) const
{
	ASSERT(0);
	return 0;
}

StringVariant& StringVariant::operator = (const StringVariant& other)
{
	if (other.m_stringObject)
	{
		other.m_stringObject->IncRef();
	}

	if (m_stringObject)
	{
		m_stringObject->DecRef();
	}

	m_stringObject = other.m_stringObject;
	m_cstr = other.m_cstr;
	m_cstrw = other.m_cstrw;

	return *this;
}

Utf32Char StringVariant::operator [] (ptrdiff_t index) const
{
	return At(index);
	/*
	if (index < 0 || (size_t)index >= GetLength())
	{
		raise(ArgumentOutOfRangeException());
	}

	if (m_stringObject)
	{
		ASSERT(0);
		return 0;//String(m_stringObject);
	}
	else if (m_cstr) return m_cstr[index];
	else if (m_cstrw) return m_cstrw[index];
	else
	{
		raise(SystemException(L"referencing null string"));
	}
	*/
}

Utf32Char StringVariant::At(ptrdiff_t index) const
{
	if (IsEmpty()) raise(ArgumentOutOfRangeException());

	if (index < 0) raise(ArgumentOutOfRangeException());
	if (index >= (ptrdiff_t)GetLength()) raise(ArgumentOutOfRangeException());

	if (m_stringObject)
	{
		switch (m_stringObject->GetCharSize())
		{
		case 1: return ((char*)m_stringObject->GetData())[index];
		case 2: return ((char16*)m_stringObject->GetData())[index];
		default: return ((char32_t*)m_stringObject->GetData())[index];
		}
		raise(SystemException("at"));
	}
	else if (m_cstr)
		return m_cstr[index];
	else// if (m_cstrw)
		return m_cstrw[index];
}

StringVariant::_SubString StringVariant::LeftOf(size_t offset) const
{
	return _SubString(m_stringObject, m_cstr, m_cstrw, 0, offset);
}

StringVariant::_SubString StringVariant::RightOf(size_t offset) const
{
	return _SubString(m_stringObject, m_cstr, m_cstrw, offset, GetLength() - offset);
}

StringVariant::_SubString StringVariant::SubString(size_t offset, size_t len) const
{
	if (len == npos) len = GetLength() - offset;
	return _SubString(m_stringObject, m_cstr, m_cstrw, offset, len);
}

size_t StringVariant::CopyTo(char* cstrdst, size_t maxbufferchars, size_t offset) const
{
	if (m_stringObject)
	{
		return m_stringObject->CopyTo(cstrdst, maxbufferchars, offset);
	}
	else if (m_cstr)
	{
		size_t len = strlen(m_cstr) - offset;
		if (len > maxbufferchars) len = maxbufferchars;

		memcpy(cstrdst, m_cstr+offset, len);

		return len;
	}
	else if (m_cstrw)
	{
		raise(Exception("wchar_t -> char"));
		return 0;
	}
	else
		return 0;
}

size_t StringVariant::CopyTo(wchar_t* cstrdst, size_t maxbufferchars, size_t offset) const
{
	if (m_stringObject)
	{
		return m_stringObject->CopyTo(cstrdst, maxbufferchars, offset);
	}
	else if (m_cstr)
	{
		size_t len = strlen(m_cstr) - offset;
		if (len > maxbufferchars) len = maxbufferchars;

		for (size_t i = 0; i < len; ++i)
		{
			cstrdst[i] = m_cstr[offset+i];
		}

		return len;
	}
	else if (m_cstrw)
	{
		size_t len = wcslen(m_cstrw) - offset;
		if (len > maxbufferchars) len = maxbufferchars;

		memcpy(cstrdst, m_cstrw, len*2);

		return len;
	}
	else
		return 0;
}

double StringVariant::ToDouble(bool* ok) const
{
	// TODO, improve

	if (m_stringObject)
	{
		if (ok) *ok = true;
		// TODO, improve
		return _wtof(CStringw(*this).c_str());
	}
	else if (m_cstr)
	{
		// TODO errno

		if (ok) *ok = true;
		return atof(m_cstr);
	}
	else if (m_cstrw)
	{
		// TODO errno

		if (ok) *ok = true;
		return _wtof(m_cstrw);
	}

	if (ok) *ok = false;
	return 0;
}

ptrdiff_t StringVariant::const_iterator_base::operator - (const StringVariant::const_iterator_base& it) const
{
//	if (!m.RefEquals(it.m)) raise(SystemException("Not pointing to same string"));

	return m_offset - it.m_offset;
}

bool StringVariant::const_iterator_base::operator != (const StringVariant::const_iterator_base& it) const
{
	return !(*this == it);
}

// pointer comparison
bool StringVariant::const_iterator_base::operator > (const StringVariant::const_iterator_base& it) const
{
//	if (!m.RefEquals(it.m)) raise(SystemException("Not pointing to same string"));

	return m_offset > it.m_offset;
}

bool StringVariant::const_iterator_base::operator < (const StringVariant::const_iterator_base& it) const
{
	//if (!m.RefEquals(it.m)) raise(SystemException("Not pointing to same string"));

	return m_offset < it.m_offset;
}

bool StringVariant::const_iterator_base::operator >= (const StringVariant::const_iterator_base& it) const
{
//	if (!m.RefEquals(it.m)) raise(SystemException("Not pointing to same string"));

	return m_offset >= it.m_offset;
}

bool StringVariant::const_iterator_base::operator <= (const StringVariant::const_iterator_base& it) const
{
//	if (!m.RefEquals(it.m)) raise(SystemException("Not pointing to same string"));

	return m_offset <= it.m_offset;
}

bool StringVariant::const_iterator_base::atend() const
{
	if (m.IsEmpty())
	{
		if (m_offset != 0) raise(SystemException(L"referencing null pointer"));
		return true;
	}
	else
	{
		//if (m_offset < 0) raise(Exception(L"offset < 0"));
		if ((size_t)m_offset > m.GetLength()) raise(SystemException(L"offset < 0 or >= length"));

		return m_offset == m.GetLength();
	}
}

}	// System
