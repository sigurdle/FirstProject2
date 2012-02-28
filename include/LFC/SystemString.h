#ifndef String_h
#define String_h

namespace System
{

/** \addtogroup LFC
@{
*/

#ifdef __GNUC__

int wcscmp(const wchar_t* str1, const wchar_t* str2);
wchar_t* wcschr(const wchar_t* str, wchar_t ch);

char* _strdup(const char*);
char* _wcsdup(const wchar_t*);

#endif

enum NormalizationForm
{
	NormalizationOther   = 0,
	NormalizationC       = 0x1,
	NormalizationD       = 0x2,
	NormalizationKC      = 0x5,
	NormalizationKD      = 0x6 
};

class LFCEXT Char8
{
public:

	typedef char8 char_t;

	CTOR Char8(char_t ch) : m_ch(ch)
	{
	}

	Char8& operator = (char_t ch)
	{
		m_ch = ch;
		return *this;
	}

	operator char_t() const
	{
		return m_ch;
	}

	bool IsAlpha() const;
	bool IsDigit() const;
	bool IsLowerCase() const;
	bool IsUpperCase() const;

	Char8 ToUpper() const;
	Char8 ToLower() const;

	char_t m_ch;
};

class LFCEXT Utf16Char
{
public:

	typedef char16 char_t;

	CTOR Utf16Char(char_t ch) : m_ch(ch)
	{
	}

	Utf16Char& operator = (char_t ch)
	{
		m_ch = ch;
		return *this;
	}

	operator char_t() const
	{
		return m_ch;
	}

	bool IsAlpha() const;
	bool IsDigit() const;
	bool IsLowerCase() const;
	bool IsUpperCase() const;

	Utf16Char ToUpper() const;
	Utf16Char ToLower() const;

	char_t m_ch;
};

/*
class Utf32Char
{
public:
	CTOR Utf32Char(uint32 c)
	{
		m_c = c;
	}

	operator uint32 () const
	{
		return m_c;
	}

	uint32 m_c;
};
*/

class LFCEXT Utf32Char
{
public:

	typedef char32_t char_t;

	CTOR Utf32Char(char_t ch) : m_ch(ch)
	{
	}

	Utf32Char& operator = (char_t ch)
	{
		m_ch = ch;
		return *this;
	}

	bool operator == (char ch) const
	{
		return m_ch == ch;
	}

	bool operator == (wchar_t ch) const
	{
		return m_ch == ch;
	}

	bool operator != (char ch) const
	{
		return m_ch != ch;
	}

	bool operator != (wchar_t ch) const
	{
		return m_ch != ch;
	}

	operator wchar_t () const
	{
		return m_ch;
	}

	operator char_t () const
	{
		return m_ch;
	}

	bool IsAlpha() const;
	bool IsDigit() const;
	bool IsLowerCase() const;
	bool IsUpperCase() const;

	Utf32Char ToUpper() const;
	Utf32Char ToLower() const;

	char_t m_ch;
};

template<class char_type> class CharClass {};

#ifndef __LERSTAD__

template<> class CharClass<char8>
{
public:
	typedef Char8 ctype;
};

template<> class CharClass<char16>
{
public:
	typedef Utf16Char ctype;
};

template<> class CharClass<char32_t>
{
public:
	typedef Utf32Char ctype;
};

#endif

class LFCEXT StringObject : public Object
{
public:
	virtual size_t GetLength() throw() = 0;
	virtual size_t GetByteCount() throw() = 0;
	virtual unsigned int GetCharSize() const throw() = 0;
	virtual const void* GetData() = 0;
	virtual uint32 GetAt(ptrdiff_t index) = 0;

	virtual String ToString() override;

	virtual void Write(IO::TextWriter& stream) = 0;

	/// <param name="ch">The character to find</param>
	virtual size_t Find(uint32 ch, size_t startoffset) = 0;
	/// <param name="ch">The character to count</param>
	virtual size_t Count(uint32 ch) = 0;

	virtual int Compare(const char* cstr, size_t len) = 0;
	virtual int Compare(const wchar_t* cstr, size_t len) = 0;
	virtual int Compare(const char32_t* cstr, size_t len) = 0;
	virtual int Compare(StringObject* stringData) = 0;

	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char* cstr, size_t len) = 0;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const wchar_t* cstr, size_t len) = 0;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char32_t* cstr, size_t len) = 0;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, StringObject* stringData) = 0;

	virtual int CompareNoCase(const char* cstr, size_t len) = 0;
	virtual int CompareNoCase(const wchar_t* cstr, size_t len) = 0;
	virtual int CompareNoCase(StringObject* stringData) = 0;

	virtual StringObject* Append(const char8* cstr, size_t len) = 0;
	virtual StringObject* Append(const char16* cstr, size_t len) = 0;
	virtual StringObject* Append(StringObject* stringObject) = 0;

	virtual StringObject* Insert(const char8* cstr, size_t offset, size_t len) = 0;
	virtual StringObject* Insert(const char16* cstr, size_t offset, size_t len) = 0;

	virtual StringObject* Delete(size_t offset, size_t len) = 0;

	StringObject* Insert(StringObject* str, size_t offset);

	virtual StringObject* SubString(size_t offset, size_t len) = 0;

	virtual size_t CopyTo(char* cstrdst, size_t maxbufferchars, size_t offset = 0) = 0;
	virtual size_t CopyTo(wchar_t* cstrdst, size_t maxbufferchars, size_t offset = 0) = 0;

	virtual size_t IncRef() throw() = 0;
	virtual size_t DecRef() throw() = 0;

	/*
	virtual bool IsAllUpperCase() = 0;
	virtual bool IsAllLowerCase() = 0;

	virtual bool HasUpperCase() = 0;
	virtual bool HasLowerCase() = 0;

	virtual unsigned int CountUpperCase() = 0;
	virtual unsigned int CountLowerCase() = 0;

	virtual StringData* ToUpperCase() = 0;
	virtual StringData* ToLowerCase() = 0;
*/

	int GetLength31();
	uint GetLength32();

	int Compare(const char* cstr)
	{
		return Compare(cstr, cstrlen(cstr));
	}

	int Compare(const char16* cstr)
	{
		return Compare(cstr, cstrlen(cstr));
	}

	int Compare(const char32_t* cstr)
	{
		return Compare(cstr, cstrlen(cstr));
	}

	int CompareNoCase(const char* cstr)
	{
		return CompareNoCase(cstr, cstrlen(cstr));
	}

	int CompareNoCase(const wchar_t* cstr)
	{
		return CompareNoCase(cstr, cstrlen(cstr));
	}

	StringObject* Append(const char8* cstr)
	{
		return Append(cstr, cstrlen(cstr));
	}

	StringObject* Append(const char16* cstr)
	{
		return Append(cstr, cstrlen(cstr));
	}

	StringObject* Insert(const char8* cstr, size_t offset)
	{
		return Insert(cstr, offset, cstrlen(cstr));
	}

	StringObject* Insert(const char16* cstr, size_t offset)
	{
		return Insert(cstr, offset, cstrlen(cstr));
	}

	/*
	StringObject* Append(const char32_t* cstr)
	{
		return Append(cstr, cstrlen(cstr));
	}
	*/

	inline bool operator == (StringObject& other)
	{
		return Compare(&other) == 0;
	}

	inline bool operator != (StringObject& other)
	{
		return Compare(&other) != 0;
	}

	inline bool operator < (StringObject& other)
	{
		return Compare(&other) < 0;
	}

	inline bool operator > (StringObject& other)
	{
		return Compare(&other) > 0;
	}

	inline bool operator < (const char* cstr)
	{
		return Compare(cstr) < 0;
	}

	inline bool operator > (const char* cstr)
	{
		return Compare(cstr) > 0;
	}

	inline bool operator < (const wchar_t* cstr)
	{
		return Compare(cstr) < 0;
	}

	inline bool operator > (const wchar_t* cstr)
	{
		return Compare(cstr) > 0;
	}
};

template<class char_type>
class StringObjectT : public StringObject
{
public:

	/*
#ifndef __LERSTAD__
	static_assert(__is_pod(char_type), "char_type must be a simple type");
#endif
	*/

	virtual unsigned int GetCharSize() const throw() override
	{
		return sizeof(char_type);
	}

	virtual int Compare(const char* cstr, size_t len) override
	{
		return SubCompare(0, GetLength(), cstr, len);
	}

	virtual int Compare(const wchar_t* cstr, size_t len) override
	{
		return SubCompare(0, GetLength(), cstr, len);
	}

	virtual int Compare(const char32_t* cstr, size_t len) override
	{
		return SubCompare(0, GetLength(), cstr, len);
	}

	virtual int Compare(StringObject* stringData) override
	{
		return SubCompare(0, GetLength(), stringData);
	}

	virtual const char_type* data() abstract;
};

template<class char_type>
class MutableString : public StringObjectT<char_type>
{
public:

	explicit CTOR MutableString(size_t len, char_type ch = ' ') : m_refcount(0)
	{
		m_data.resize(len);
	}

	CTOR MutableString(const char_type* str, size_t len) : m_refcount(0)
	{
		m_data.insert(m_data.begin(), str, str+len);
	}

	template<class char0_type, class char1_type>
	CTOR MutableString(const char0_type* p0, size_t len0, const char1_type* p1, size_t len1, size_t offset) : m_refcount(0)
	{
		m_data.resize(len0 + len1);
		char_type* p = m_data.begin();

		ASSERT(offset <= len0);

		len0 -= offset;
		while (offset--)
		{
			*p++ = char_type(*p0++);
		}

		while (len1--)
		{
			*p++ = char_type(*p1++);
		}

		while (len0--)
		{
			*p++ = char_type(*p0++);
		}
	}

	template<class char_type>
	CTOR MutableString(const char_type* p0, size_t len0, const char_type* p1, size_t len1) : m_refcount(0)
	{
		m_data.resize(len0 + len1);
		char_type* p = m_data.begin();

		while (len0--)
		{
			*p++ = *p0++;
		}

		while (len1--)
		{
			*p++ = *p1++;
		}
	}

	virtual size_t IncRef() throw() override
	{
		return InterlockedIncrement(&m_refcount);
	}

	virtual size_t DecRef() throw() override
	{
		ASSERT(m_refcount > 0);
		return InterlockedDecrement(&m_refcount);
	}

	virtual size_t GetLength() throw() override
	{
		return m_data.size();
	}

	virtual size_t GetByteCount() throw() override
	{
		return m_data.size() * sizeof(char_type);
	}

	virtual const void* GetData() override
	{
		return m_data.begin();
	}

	virtual const char_type* data() override
	{
		return m_data.begin();
	}

	virtual uint32 GetAt(ptrdiff_t index) override
	{
		if ((size_t)index >= m_data.size()) VERIFY(0);//raise(ArgumentOutOfRangeException());
		return m_data[index];
	}

	virtual StringObject* SubString(size_t offset, size_t len) override;

	virtual void Write(IO::TextWriter& stream) override;

	virtual size_t Find(uint32 ch, size_t startoffset) override;
	virtual size_t Count(uint32 ch) override;

	virtual size_t CopyTo(char* cstrdst, size_t maxbufferchars, size_t offset = 0) override;
	virtual size_t CopyTo(wchar_t* cstrdst, size_t maxbufferchars, size_t offset = 0) override;

	virtual StringObject* Append(const char8* cstr, size_t len);
	virtual StringObject* Append(const char16* cstr, size_t len);
	//virtual StringObject* Append(const char32_t* cstr, unsigned int len);
	virtual StringObject* Append(StringObject* stringData);

	virtual StringObject* Insert(const char8* cstr, size_t offset, size_t len) override;
	virtual StringObject* Insert(const char16* cstr, size_t offset, size_t len) override;
//	virtual StringObject* Insert(StringObject* str, unsigned int offset) override;

	virtual StringObject* Delete(size_t offset, size_t len) override;

	virtual int Compare(const char* cstr, size_t len) override
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(const wchar_t* cstr, size_t len) override
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(const char32_t* cstr, size_t len) override
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(StringObject* stringData) override
	{
		return SubCompare(0, m_data.size(), stringData);
	}

	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char* cstr, size_t len) override;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const wchar_t* cstr, size_t len) override;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char32_t* cstr, size_t len) override;
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, StringObject* stringData) override;

	virtual int CompareNoCase(const char* cstr, size_t len) override;
	virtual int CompareNoCase(const wchar_t* cstr, size_t len) override;
	virtual int CompareNoCase(StringObject* stringData) override;

	virtual uint32 GetHashCode() override
	{
		uint32 hashCode = 0;
		char_type* p = m_data.begin();
		size_t len = m_data.size();
		while (len--)
		{
			hashCode += hashCode*31 + *p++;
		}

		return hashCode;
	}

private:

	vector<char_type> m_data;
	size_t m_refcount;
};

template<class char_type> class ImmutableString : public StringObjectT<char_type>
{
public:

// ctor
	CTOR ImmutableString()
	{
	}

	explicit CTOR ImmutableString(string_data<char_type> str_data) : m_data(str_data.data, str_data.len)//m_str(str_data.data), m_len(str_data.len)
	{
	}

#ifndef __LERSTAD__

	/*
	template<size_t size> ImmutableString(const char_type* str)
	{
		m_data.assign(str, len-1);
	}
*/

#endif

	CTOR ImmutableString(const char_type* str)
	{
		size_t len;
		if (str)
			len = cstrlen(str);
		else
			len = 0;

		m_data.assign(str, len);
	}

	CTOR ImmutableString(const char_type* str, size_t len) : m_data(str, len)
	{
	}

	CTOR ImmutableString(const ImmutableString<char_type>& string) : m_data(string.m_data)
	{
	}

	static ImmutableString<char_type> blank;

public:

	virtual size_t IncRef() throw() override
	{
		return 1;
	}

	virtual size_t DecRef() throw() override
	{
		return 1;
	}

	virtual size_t GetLength() throw() override
	{
		return m_data.size();
	}

	virtual size_t GetByteCount() throw() override
	{
		return m_data.size() * sizeof(char_type);
	}

	virtual const void* GetData() override
	{
		return m_data.begin();
	}

	virtual const char_type* data()
	{
		return m_data.begin();
	}

	virtual uint32 GetAt(ptrdiff_t index) override
	{
		if ((size_t)index >= m_data.size()) VERIFY(0);//throw new ArgumentOutOfRangeException();
		return m_data[index];
	}

	virtual void Write(IO::TextWriter& stream);

	virtual size_t CopyTo(char* cstrdst, size_t maxbufferchars, size_t offset = 0);
	virtual size_t CopyTo(wchar_t* cstrdst, size_t maxbufferchars, size_t offset = 0);

	virtual bool Equals(const Object* other) const
	{
		if (this == other) return true;
		if (other == nullptr) return false;

		if (Object::GetType() != other->GetType())
			return false;

		const ImmutableString<char_type>* otherstr = static_cast<const ImmutableString<char_type>*>(other);

		return equals(*otherstr);
	}

	bool Equals(const ImmutableString<char_type>& str) const
	{
		if (this == &str) return true;
		if (this == nullptr) return false;
		if (&str == nullptr) return false;

		return equals(str);
	}

	bool operator == (const char_type* str)
	{
		if (this == nullptr && str == nullptr) return true;
		if (this == nullptr) return false;

		size_t count = GetByteCount();
		size_t count2 = cstrlen(str) * sizeof(char_type);
		if (count != count2) return false;

		return memcmp(m_data.begin(), str, count) == 0;
	}

	virtual StringObject* SubString(size_t offset, size_t len);

	virtual int Compare(const char* cstr, size_t len)
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(const wchar_t* cstr, size_t len)
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(const char32_t* cstr, size_t len)
	{
		return SubCompare(0, m_data.size(), cstr, len);
	}

	virtual int Compare(StringObject* stringData)
	{
		return SubCompare(0, m_data.size(), stringData);
	}

	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char8* cstr, size_t len);
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char16* cstr, size_t len);
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, const char32_t* cstr, size_t len);
	virtual int SubCompare(ptrdiff_t suboffset, size_t sublen, StringObject* stringObject);

	virtual int CompareNoCase(const char8* cstr, size_t len);
	virtual int CompareNoCase(const char16* cstr, size_t len);
	virtual int CompareNoCase(StringObject* stringObject);

	virtual StringObject* Append(const char8* cstr, size_t len);
	virtual StringObject* Append(const char16* cstr, size_t len);
	virtual StringObject* Append(const char32_t* cstr, size_t len);
	virtual StringObject* Append(StringObject* stringData);

	virtual StringObject* Insert(const char8* cstr, size_t offset, size_t len) override;
	virtual StringObject* Insert(const char16* cstr, size_t offset, size_t len) override;

	virtual StringObject* Delete(size_t offset, size_t len) override;

	virtual uint32 GetHashCode() override;
	virtual size_t Find(uint32 ch, size_t startoffset) override;
	virtual size_t Count(uint32 ch) override;

	template<class T2> int _CompareNoCase(const T2* otherstr, size_t otherlen) const;

	/*

	StringT<T>* TrimLeft()
	{
		unsigned int len = Length();
		unsigned int i = 0;
		while (i < len)
		{
			if (!std::isspace(m_data[i]))
				break;

			i++;
		}

		if (i == 0)
			return this;
		else
			return new StringT<T>(string_copy(m_data.begin() + i, len - i));
	}

	StringT<T>* TrimRight()
	{
		unsigned int len = Length();
		int i = (int)len-1;
		while (i >= 0)
		{
			if (!std::isspace(m_data[i]))
				break;

			--i;
		}

		if (i == len-1)
			return this;
		else
			return new StringT<T>(true, m_data.begin(), i+1);
	}
	*/

//	ImmutableString* ReplaceChar(T c, T c2);

	/*
#ifndef __LERSTAD__	// TODO
	LFCEXT StringT<char>* ToStringA() const;
	LFCEXT StringT<WCHAR>* ToStringW() const;
#endif
	*/

	/*

   ?? TODO:

int                findOffset16(in int offset32)
                                        raises(StringIndexOutOfBoundsException);
  int                findOffset32(in int offset16)
                                        raises(StringIndexOutOfBoundsException);
*/

	array<const char_type> m_data;

private:

	inline bool equals(const ImmutableString<char_type>& str) const
	{
		ASSERT(0);
		return false;
		/*
		unsigned int count = GetByteCount();
		if (count != str.GetByteCount()) return false;
		return std::memcmp(m_data.begin(), str.m_data.begin(), count) == 0;
		*/
	}
};

class SubStringObject : public StringObject
{
public:

	CTOR SubStringObject(StringObject* stringObject, size_t offset, size_t len) :
		m_stringObject(stringObject),
		m_offset(offset),
		m_len(len)
	{
	}

	virtual int Compare(ptrdiff_t offset, size_t len,  StringObject* stringObject);
	virtual int CompareNoCase(StringObject* stringObject);

	virtual uint32 GetAt(ptrdiff_t index) override
	{
		return m_stringObject->GetAt(m_offset + index);
	}

	virtual StringObject* Append(const char* cstr, size_t len);
	virtual StringObject* Append(const char16* cstr, size_t len);
	virtual StringObject* Append(const char32_t* cstr, size_t len);
	virtual StringObject* Append(StringObject* stringObject);

	int CompareNoCase(const char8* str);
	int CompareNoCase(const char16* str);

	StringObject* m_stringObject;
	size_t m_offset;
	size_t m_len;
};

/*
template<class T, size_t maxsize> class fixed_array
{
public:

	T m_data[maxsize];
	size_t m_size;

public:

	typedef T item_type;

	CTOR fixed_array() : m_size(0)
	{
	}

	void push_back(const T& item)
	{
		if (m_size == maxsize)
		{
			VERIFY(0);
		}

		m_data[m_size] = item;
		++m_size;
	}

	size_t size() const
	{
		return m_size;
	}

	T& operator [] (size_t index)
	{
		return m_data[index];
	}

	const T& operator [] (size_t index) const
	{
		return m_data[index];
	}
};
*/

template<class char_type, unsigned int fixed_len = 127> class CString_
{
public:

	~CString_()
	{
		if (m_p)
		{
			free(m_p);
			m_p = nullptr;
		}
	}

	operator char_type* () throw()
	{
		return m_p? m_p: m_buffer;
	}

	operator const char_type* () const throw()
	{
		return m_p? m_p: m_buffer;
	}

protected:

	CTOR CString_(const String& str)
	{
		size_t len = str.GetLength();
		m_len = len;

		if (len > fixed_len)
		{
			m_p = (char_type*)malloc(sizeof(char_type)*(len+1));
			str.CopyTo(m_p, len);
			m_p[len] = 0;
		}
		else
		{
			m_p = nullptr;
			str.CopyTo(m_buffer, len);
			m_buffer[len] = 0;
		}
	}

#ifndef __LERSTAD__
	CTOR CString_(CString_&& other)
	{
		memcpy(m_buffer, other.m_buffer, sizeof(char_type)*(fixed_len+1));
		m_p = other.m_p;
		other.m_p = nullptr;
	}
#endif

	friend class String;
	friend class StringVariant;

#ifndef __LERSTAD__
	char_type m_buffer[fixed_len+1];
#endif
	char_type* m_p;
	size_t m_len;
};

/// The String class provides a Unicode character string class.
/**
A String class internally stores only a pointer to a StringObject that contains the actual string.

<h2> Initializing a String</h2>
@code
   String str("Hello");
@endcode

A better way to initialize a String with a constant string literal is to wrap
the string literal in a S() macro. The S() macro wraps a string literal in a static ImmutableStringObject<T>
thus avoiding an allocation of this object
@code
   String str("Hello");       // a new ImmutableStringObject<char> is allocated
   String str(S("Hello"));    // no allocation takes place
@endcode

<h2>Distinction Between Null and Empty Strings</h2>

String distinguishes between a zero-length string <code>"" and a nullptr</code> string. If you
want to test for either a nullptr string or a zero-length string. You can use the IsEmpty() method.
@code
// Different ways to set a nullptr String
   String str;	// Default constructor
   String str(nullptr);
   String str = nullptr;

   // Note str = NULL cannot be used, you must use nullptr

   str == nullptr;     // returns true
   str == "";          // returns false
   str.GetLength();    // returns 0
   !str;               // returns true
   str.IsEmpty();      // returns true

   str = "";           // A zero-length string
   str == nullptr;     // returns false
   str == "";          // returns true
   str.GetLength();    // returns 0
   !str;               // returns false
   str.IsEmpty();      // returns true
@endcode

<h2>String is NOT nullterminated</h2>
Unlike a conventional C string, (char*), String data is not not nullterminated, and on
The rationale behind this decision: It is cleaner, and although one saves a byte or two per
string, this is not the main reason, but it is cleaner.
Most new APIs take an additional length parameter instead of relying on null-terminated C strings.
To convert to a null-terminated C string, one can use
c_str()
c_strw()

c_str_flen<size>()
c_strw_flen<size>()
ToStdString()
ToStdWString()

@code
String str("Some message");
printf("%s\n", (char*)str.c_str_flen<64>());
@endcode

<h2>Efficient String Construction</h2>

Using the String '+' operator, you can concatenate several strings together effieciently. The
concatenation will be postponed until the memory needed is known, and will allocate this once
instead of.
@code
String str1(S("How"));
String str2(S("are"));
String str3(S("you?"));

String result = str1 + " " + str2 + " " + str3;	// result is "How are you?"
@endcode

Without expression templates, this line of code would be allocating 4 times instead of one,
conceptually it would have done the following:
@code
temp1 = str1 + " " // (allocation #1)
temp2 = temp1 + str2 // (allocation #2)
temp3 = temp2 + " " // (allocation #3)
temp4 = temp3 + str3 // (allocation #4)
@endcode

<h2>Manipulating String Data</h2>

To extract a substring from the beginning or end of the string, you can use LeftOf() and
RightOf() respectively. To extract a substring, you can use substr()

<h2>Querying String Data</h2>

If you want to check if a string begins or ends with a given string, you can use BeginsWith() and
EndsWith(). If you want to check if a string contains a certain character or substring, you can use
Contains. If you want to find the index location of a certain character or substring, you can use
find() or rfind(). To 

*/
class LFCEXT String
{
public:

	typedef size_t size_type;

	static const size_type npos = (size_t)-1;

	static String get_Empty()
	{
		return &ImmutableString<char>::blank;
	}

	template<class char_type> class const_reverse_iterator
	{
	public:
	};

	class LFCEXT _SubString
	{
	public:

		CTOR _SubString(StringObject* stringObject, size_t offset, size_t len) :
			m_stringObject(stringObject),
			m_offset(offset),
			m_len(len)
		{
			if (stringObject)
			{
				stringObject->IncRef();

				if (len == ~0)
				{
					m_len = stringObject->GetLength() - offset;
				}
			}
		}

		~_SubString()
		{
			if (m_stringObject)
			{
				m_stringObject->DecRef();
			}
		}

		/*
		operator String () const
		{
			return m_stringObject->SubString(m_offset, m_len);
		}
		*/

		// char
		inline bool operator == (const char* cstr) const
		{
			return Compare(cstr) == 0;
		}

		inline bool operator != (const char* cstr) const
		{
			return Compare(cstr) != 0;
		}

		inline bool operator < (const char* cstr) const
		{
			return Compare(cstr) < 0;
		}

		inline bool operator > (const char* cstr) const
		{
			return Compare(cstr) > 0;
		}

		// char16
		inline bool operator == (const char16* cstr) const
		{
			return Compare(cstr) == 0;
		}

		inline bool operator != (const char16* cstr) const
		{
			return Compare(cstr) != 0;
		}

		inline bool operator < (const char16* cstr) const
		{
			return Compare(cstr) < 0;
		}

		inline bool operator > (const char16* cstr) const
		{
			return Compare(cstr) > 0;
		}

		bool operator == (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) == 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) == 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) == 0;
			}
		}

		bool operator != (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) != 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) != 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) != 0;
			}
		}

		bool operator < (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) < 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) < 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) < 0;
			}
		}

		bool operator > (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) > 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) > 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) > 0;
			}
		}

		bool operator >= (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) >= 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) >= 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) >= 0;
			}
		}

		bool operator <= (const String& str) const
		{
			switch (m_stringObject->GetCharSize())
			{
			case 1: return str.m_stringObject->Compare((char8*)m_stringObject->GetData() + m_offset, m_len) <= 0;
			case 2: return str.m_stringObject->Compare((char16*)m_stringObject->GetData() + m_offset, m_len) <= 0;
			default: return str.m_stringObject->Compare((char32_t*)m_stringObject->GetData() + m_offset, m_len) <= 0;
			}
		}

		int Compare(const char8* cstr) const;
		int CompareNoCase(const char8* cstr) const;

		int Compare(const char16* cstr) const;
		int CompareNoCase(const char16* cstr) const;

		int Compare(const char32_t* cstr) const;
		int CompareNoCase(const char32_t* cstr) const;

		// conversion
		operator String () const
		{
			return m_stringObject->SubString(m_offset, m_len); 
		}

		StringObject* m_stringObject;
		size_t m_offset;
		size_t m_len;
	};

	class LFCEXT const_iterator_base
	{
	public:

		CTOR const_iterator_base(StringObject* p, ptrdiff_t offset) : m_p(p), m_offset(offset)
		{
			if (p) p->IncRef();
		}

		// pointer arithmetic

#ifndef __LERSTAD__
		const_iterator_base operator + (ptrdiff_t offset) const
		{
			return const_iterator_base(m_p, m_offset + offset);
		}

		const_iterator_base operator - (ptrdiff_t offset) const
		{
			return const_iterator_base(m_p, m_offset - offset);
		}

		const_iterator_base& operator ++ ()	// preincrement
		{
			++m_offset;
			return *this;
		}

		const_iterator_base& operator -- ()	// predecrement
		{
			--m_offset;
			return *this;
		}

		const_iterator_base operator ++ (int)	// postincrement
		{
			const_iterator_base it(*this);
			++m_offset;
			return it;
		}

		const_iterator_base operator -- (int)	// postdecrement
		{
			const_iterator_base it(*this);
			--m_offset;
			return it;
		}

		const_iterator_base& operator += (ptrdiff_t offset)
		{
			m_offset += offset;
			return *this;
		}

		const_iterator_base& operator -= (ptrdiff_t offset)
		{
			m_offset -= offset;
			return *this;
		}

		bool operator == (const const_iterator_base& it) const
		{
			return m_p == it.m_p && m_offset == it.m_offset;
		}

		bool operator != (const const_iterator_base& it) const
		{
			return m_p != it.m_p || m_offset != it.m_offset;
		}

		_SubString FirstN(size_t len) const
		{
			return _SubString(m_p, m_offset, len);
		}

		/*
		_SubString RightOf(unsigned int len) const
		{
			return _SubString(m_p, m_offset, len);
		}
		*/

		ptrdiff_t operator - (const const_iterator_base& it) const;
#endif

		// pointer comparison
		bool operator > (const const_iterator_base& it) const;
		bool operator < (const const_iterator_base& it) const;
		bool operator >= (const const_iterator_base& it) const;
		bool operator <= (const const_iterator_base& it) const;
		bool atend() const;

		StringObject* m_p;
		ptrdiff_t m_offset;
	};

	template<class char_type> class const_iterator : public const_iterator_base
	{
	public:

		typedef char_type _type;

		CTOR const_iterator(const const_iterator_base& it) : const_iterator_base(it.m_p, it.m_offset)
		{
			if (m_p) m_p->IncRef();
		}

		CTOR const_iterator(StringObjectT<char_type>* p, ptrdiff_t offset) : const_iterator_base(p, offset)
		{
			if (p) p->IncRef();
		}

		~const_iterator()
		{
			if (m_p) m_p->DecRef();
		}

		const_iterator& operator ++ ()	// preincrement
		{
			++m_offset;
			return *this;
		}

		const_iterator& operator -- ()	// predecrement
		{
			--m_offset;
			return *this;
		}

		const_iterator operator ++ (int)	// postincrement
		{
#ifndef __LERSTAD__
			const_iterator it(*this);
#endif
			++m_offset;
			return it;
		}

		const_iterator operator -- (int)	// postdecrement
		{
#ifndef __LERSTAD__
			const_iterator it(*this);
#endif
			--m_offset;
			return it;
		}

		/*
		const_iterator& operator = (StringObjectT<char_type>* p)
		{
			if (p) p->IncRef();
			if (m_p) m_p->DecRef();

			m_p = p;
			m_offset = 0;

			return *this;
		}
		*/

		// access
		char_type operator * () const;
		char_type operator [] (ptrdiff_t index) const;
	};

	CTOR String() : m_stringObject(nullptr)
	{
	}

	CTOR String(decltype(nullptr)) : m_stringObject(nullptr)
	{
	}

	CTOR String(const String& other) : m_stringObject(other.m_stringObject)
	{
		if (m_stringObject)
		{
			m_stringObject->IncRef();
		}
	}

	CTOR String(String&& other) : m_stringObject(other.m_stringObject)
	{
		other.m_stringObject = nullptr;
	}

	CTOR String(StringObject* stringObject) : m_stringObject(stringObject)
	{
		if (m_stringObject)
		{
			m_stringObject->IncRef();
		}
	}

	CTOR String(const char* cstr);
	CTOR String(const wchar_t* cstr);

	CTOR String(const string_data<char8>& strdata) : m_stringObject(new ImmutableString<char8>(strdata))
	{
		m_stringObject->IncRef();
	}

	CTOR String(const string_data<char16>& strdata) : m_stringObject(new ImmutableString<char16>(strdata))
	{
		m_stringObject->IncRef();
	}

	CTOR String(const StringBuilderBase& builder);

	~String()
	{
		if (m_stringObject)
		{
			m_stringObject->DecRef();
		}
	}

	const_iterator_base begin() const
	{
		return const_iterator_base(m_stringObject, 0);
	}

	const_iterator_base end() const
	{
		return const_iterator_base(m_stringObject, GetLength());
	}

	operator StringObject* () const
	{
		return m_stringObject;
	}

	StringObject* Detach()
	{
		StringObject* p = m_stringObject;
		m_stringObject = nullptr;
		return p;
	}

	size_t GetLength() const
	{
		if (m_stringObject == nullptr) return 0;
		return m_stringObject->GetLength();
	}

	uint GetLength32() const
	{
		if (m_stringObject == nullptr) return 0;
		return m_stringObject->GetLength32();
	}

	bool IsEmpty() const throw()
	{
		if (m_stringObject == nullptr) return true;
		return m_stringObject->GetLength() == 0;
	}

	size_t GetByteCount() const
	{
		if (m_stringObject == nullptr) return 0;
		return m_stringObject->GetByteCount();
	}

	char8* GetData8() const
	{
		if (m_stringObject == nullptr) return nullptr;
		ASSERT(m_stringObject->GetCharSize() == 1);
		return (char8*)m_stringObject->GetData();
	}

	char16* GetData16() const
	{
		if (m_stringObject == nullptr) return nullptr;
		ASSERT(m_stringObject->GetCharSize() == 2);
		return (char16*)m_stringObject->GetData();
	}

	int ToInt(bool* ok = nullptr, int base = 10) const;
	unsigned int ToUInt(bool* ok = nullptr, int base = 10) const;

	int64 ToInt64(bool* ok = nullptr, int base = 10) const;
	uint64 ToUInt64(bool* ok = nullptr, int base = 10) const;

	std::string ToStdString() const;
	std::wstring ToStdWString() const;

	String ToNormalized(NormalizationForm form) const;
	bool IsNormalized(NormalizationForm form) const;

	String ToLowerCase() const;
	int ToLowerCase(WCHAR* buffer, size_t buflen) const;

	String ToUpperCase() const;
	int ToUpperCase(WCHAR* buffer, size_t buflen) const;

	bool IsLowerCase() const;
	bool IsUpperCase() const;

	// char
	inline bool operator == (const char8* cstr) const
	{
		return Compare(cstr) == 0;
	}

	inline bool operator != (const char8* cstr) const
	{
		return Compare(cstr) != 0;
	}

	inline bool operator < (const char8* cstr) const
	{
		return Compare(cstr) < 0;
	}

	inline bool operator > (const char8* cstr) const
	{
		return Compare(cstr) > 0;
	}

	inline bool operator <= (const char8* cstr) const
	{
		return Compare(cstr) <= 0;
	}

	inline bool operator >= (const char8* cstr) const
	{
		return Compare(cstr) >= 0;
	}

	int Compare(const char8* cstr) const;
	int CompareNoCase(const char8* cstr) const;

	int CompareNoCase(String str) const;

	// wchar_t
	inline bool operator == (const char16* cstr) const
	{
		return Compare(cstr) == 0;
	}

	inline bool operator != (const char16* cstr) const
	{
		return Compare(cstr) != 0;
	}

	inline bool operator < (const char16* cstr) const
	{
		return Compare(cstr) < 0;
	}

	inline bool operator > (const char16* cstr) const
	{
		return Compare(cstr) > 0;
	}

	inline bool operator <= (const char16* cstr) const
	{
		return Compare(cstr) <= 0;
	}

	inline bool operator >= (const char16* cstr) const
	{
		return Compare(cstr) >= 0;
	}

	int Compare(const char16* cstr) const;
	int CompareNoCase(const char16* cstr) const;

	int Compare(const char32_t* cstr) const;
	int CompareNoCase(const char32_t* cstr) const;

	int Compare(StringObject* str) const;

	// Assignment

	String& operator = (decltype(nullptr))
	{
		if (m_stringObject)
		{
			m_stringObject->DecRef();
			m_stringObject = nullptr;
		}
		return *this;
	}

	String& operator = (const char* cstr);
	String& operator = (const wchar_t* cstr);
	String& operator = (const string_data<char>& str);
	String& operator = (const string_data<wchar_t>& str);
	String& operator = (const String& str);
	String& operator = (String&& str) throw()	// move
	{
		m_stringObject = str.m_stringObject;
		str.m_stringObject = nullptr;
		return *this;
	}

	String& operator = (const StringBuilderBase& builder);

	template<class char_type>
	String& operator = (const CStringT<char_type>& cstr)
	{
		if (m_stringObject) m_stringObject->DecRef();
		m_stringObject = new ImmutableString<char_type>(cstr.c_str());
		m_stringObject->IncRef();
		return *this;
	}

	// Comparison

	bool operator ! () const throw()
	{
		return m_stringObject == nullptr;
	}

	bool operator == (decltype(nullptr)) const throw()
	{
		return m_stringObject == nullptr;
	}

	bool operator != (decltype(nullptr)) const throw()
	{
		return m_stringObject != nullptr;
	}

	bool operator == (StringObject* str) const
	{
		return Compare(str) == 0;
	}

	bool operator != (StringObject* str) const
	{
		return Compare(str) != 0;
	}

	bool operator == (const String& str) const
	{
		return Compare(str.m_stringObject) == 0;
	}

	bool operator != (const String& str) const
	{
		return Compare(str.m_stringObject) != 0;
	}

	bool operator < (const String& str) const
	{
		return Compare(str.m_stringObject) < 0;
	}

	bool operator > (const String& str) const
	{
		return Compare(str.m_stringObject) > 0;
	}

	bool operator == (const _SubString& substr) const;
	bool operator != (const _SubString& substr) const;
	bool operator < (const _SubString& substr) const;
	bool operator > (const _SubString& substr) const;

	// Concatenation

	String& Insert(const char* cstr, size_t offset);
	String& Insert(const wchar_t* cstr, size_t offset);
	String& Insert(const String& str, size_t offset);

	String& Delete(size_t offset, size_t len);

	String& Append(const char* cstr, size_t len);
	String& Append(const wchar_t* cstr, size_t len);

	String& operator += (char8 ch)
	{
		return Append(&ch, 1);
	}

	String& operator += (char16 ch)
	{
		return Append(&ch, 1);
	}

	String& operator += (const char* cstr)
	{
		return Append(cstr, strlen(cstr));
	}

	String& operator += (const wchar_t* cstr)
	{
		return Append(cstr, cstrlen(cstr));
	}

	String& operator += (const String& str);

	String& operator += (const StringBuilderBase& builder);

	StringBuilderTwo operator + (const String& other) const;
	StringBuilderTwo operator + (const char* cstr) const;
	StringBuilderTwo operator + (const wchar_t* cstr) const;
	StringBuilderTwo operator + (char ch) const;
	StringBuilderTwo operator + (wchar_t ch) const;

	// access

	Utf32Char At(ptrdiff_t index) const
	{
		return m_stringObject->GetAt(index);
	}
	
	// extraction
	_SubString LeftOf(size_t offset) const;
	_SubString RightOf(size_t offset) const;
	_SubString SubString(size_t offset, size_t len) const;

	size_type CopyTo(char* cstr, size_type maxbufferchars, size_type offset = 0) const;
	size_type CopyTo(wchar_t* cstr, size_type maxbufferchars, size_type offset = 0) const;

	size_type _Copy_s(char* _Dest, size_type _Dest_size, size_type _Count, size_type _Off = 0) const;
	size_type _Copy_s(wchar_t* _Dest, size_type _Dest_size, size_type _Count, size_type _Off = 0) const;

#ifndef __LERSTAD__
	template<size_t size>size_type _Copy_s(char (&_Dest)[size], size_type _Count, size_type _Off = 0) const
	{
		return _Copy_s(_Dest, size, _Count, _Off);
	}

	template<size_t size>size_type _Copy_s(wchar_t (&_Dest)[size], size_type _Count, size_type _Off = 0) const
	{
		return _Copy_s(_Dest, size, _Count, _Off);
	}
#endif

	// convert to null-terminated c string

	CString_<char> c_str() const
	{
		return CString_<char>(*this);
	}

	CString_<wchar_t> c_strw() const
	{
		return CString_<wchar_t>(*this);
	}

#ifndef __LERSTAD__
	template<unsigned int fixed_len> CString_<wchar_t, fixed_len> c_str_flen() const
	{
		return CString_<char, fixed_len>(*this);
	}

	template<unsigned int fixed_len> CString_<wchar_t, fixed_len> c_strw_flen() const
	{
		return CString_<wchar_t, fixed_len>(*this);
	}
#endif

	// find
	const_iterator_base Find(uint32 ch, size_t startoffset = 0) const
	{
		if (m_stringObject)
			return const_iterator_base(m_stringObject, m_stringObject->Find(ch, startoffset));
		else
			return const_iterator_base(m_stringObject, GetLength());
	}

	size_t find(uint32 ch, size_t startoffset = 0) const
	{
		if (m_stringObject)
			return m_stringObject->Find(ch, startoffset);
		else
			return npos;
	}

	int ReverseFind(uint32 ch) const
	{
		VERIFY(0);
/*
		if (m_stringObject)
			return m_stringObject->ReverseFind(ch);
		else
		*/
			return -1;
	}

	bool Contains(uint32 ch) const
	{
		return find(ch) != npos;
	}

	bool BeginsWith(StringVariant str) const;
//	bool BeginsWithNoCase(StringIn str) const;
	bool EndsWith(StringVariant str) const;
//	bool BeginsWithNoCase(StringIn str) const;

	// creation
	static String FromInt(int number, int base = 10);
	static String FromUInt(unsigned int number, int base = 10);
	static String FromInt64(int64 number, int base = 10);
	static String FromUInt64(uint64 number, int base = 10);

	static String FromChar(char ch);
	static String FromChar(wchar_t ch);

	static String FromNumber(signed char number, int base = 10);
	static String FromNumber(unsigned char number, int base = 10);
	static String FromNumber(short number, int base = 10);
	static String FromNumber(unsigned short number, int base = 10);
	static String FromNumber(int number, int base = 10);
	static String FromNumber(unsigned int number, int base = 10);
	static String FromNumber(long number, int base = 10);
	static String FromNumber(unsigned long number, int base = 10);
	static String FromNumber(long long number, int base = 10);
	static String FromNumber(unsigned long long number, int base = 10);
	static String FromNumber(float number);
	static String FromNumber(double number);
	static String FromNumber(long double number);

	static String FromRaw(const char* cstr);
	static String FromRaw(const char* cstr, size_t len);
	static String FromRaw(const wchar_t* cstr);
	static String FromRaw(const wchar_t* cstr, size_t len);

	static String From(const std::string& str);
	static String From(const std::wstring& str);

	// IO
	LFCEXT friend IO::TextWriter& operator << (IO::TextWriter& writer, const String& str);
	LFCEXT friend IO::TextReader& operator >> (IO::TextReader& reader, String& str);

public:

	StringObject* m_stringObject;
};

template<class char_type>
class CStringRef
{
public:
	CTOR CStringRef(const char_type* p) : m_p(p)
	{
	}

	const char_type* c_str() const
	{
		return m_p;
	}

	const char_type* m_p;
};

class LFCEXT StringBuilderBase : public Object
{
public:
	virtual char* BuildString(char* pw) const abstract;
	virtual WCHAR* BuildString(WCHAR* pw) const abstract;

	StringObject* BuildString() const;
	StringObject* BuildMutableString() const;

	inline size_t GetLength() const
	{
		return m_totalLen;
	}

	virtual String ToString() override;
	operator String () const;

	size_t m_totalLen;
	bool m_wide;
};

typedef StringObjectT<char> StringA;
typedef StringObjectT<wchar_t> StringW;

LFCEXT char8* strmemcpy(char8* d, const ImmutableString<char8>* str);
LFCEXT char16* wcsmemcpy(char16* d, const ImmutableString<char16>* str);

typedef MutableString<char> MutableStringChar8;
typedef MutableString<wchar_t> MutableStringChar16;

typedef ImmutableString<char> ImmutableStringChar8;
typedef ImmutableString<wchar_t> ImmutableStringChar16;

#ifndef LFC_EXPORTS

#ifndef __LERSTAD__

template class DECLSPEC_DLLIMPORT ImmutableString<char8>;
template class DECLSPEC_DLLIMPORT ImmutableString<char16>;
template class DECLSPEC_DLLIMPORT ImmutableString<char32_t>;

template class DECLSPEC_DLLIMPORT MutableString<char8>;
template class DECLSPEC_DLLIMPORT MutableString<char16>;

#endif

#endif

#ifndef __LERSTAD__

template<class T> struct remove_string
{
	typedef T type;
};

template<class T, unsigned int _Ix> struct remove_string<const T(&)[_Ix]>
{
	typedef T type;
};

#define S(x)	\
[] () -> ImmutableString<remove_string<decltype(x)>::type>*	\
{\
	static ImmutableString<remove_string<decltype(x)>::type> str(x);	\
	return &str;	\
}()
#else
#define S(x)	 x
#endif

/** @} */

}	// System

#endif	// String_h
