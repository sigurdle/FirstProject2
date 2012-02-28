namespace System
{

#if 0
template<class T> class BufferT
{
public:

	CTOR BufferT()
	{
	}

	/*
	T* data()
	{
		return m_str;
	}
	*/

	virtual void Write(const T* buf, int len) = 0;
};
#endif

/*
template<class T, class A = __gc_allocator> class BufferImp : public BufferT<T>
{
public:

	CTOR BufferImp(const A & allocator = A()) : m_allocator(allocator)
	{
		m_len = 0;
		m_alloclen = 0;
		m_str = NULL;
	}

	virtual void Write(const T* buf, int charslen)
	{
		int newlen = m_len+charslen;
		if (newlen > m_alloclen)
		{
			m_alloclen = (newlen + 3) & ~3;
			m_str = (T*)m_allocator.reallocate_buffer(m_str, m_alloclen * sizeof(T));
		}

		std::memcpy(m_str + m_len, buf, charslen * sizeof(T));
		m_len = newlen;
	}

	StringT<T>* DetachToString();

	T* m_str;
	int m_len;
	int m_alloclen;
	A m_allocator;
};

template<class T, class A>
StringT<T>* BufferImp<T, A>::DetachToString()
{
	T* buffer = (T*)m_allocator.reallocate_buffer(m_str, (m_len+1)*sizeof(T));

	StringT<T>* str = new StringT<T>(true, buffer, m_len);
//	str->m_str = buffer;
//	str->m_len = m_len;
	buffer[m_len] = 0;	// null-terminate

	m_len = 0;
	m_alloclen = 0;
	m_str = NULL;

	return str;
}
*/

/*
template<class T, class A>
StringT<T>* BufferImp<T, A>::ToString()
{
	return new StringT<T>(m_str, m_len);
}
*/

class StringBuilder
{
public:
	CTOR StringBuilder()
	{
	}

//	StringBuilder& operator = (const T* chars);

	StringBuilder& operator << (char8 ch)
	{
		Append(ch);
		return *this;
	}

	StringBuilder& operator << (const char* chars)
	{
		Append(chars);
		return *this;
	}

	StringBuilder& operator << (const WCHAR* chars)
	{
		Append(chars);
		return *this;
	}

	StringBuilder& operator << (int num);
	StringBuilder& operator << (unsigned int num);
	StringBuilder& operator << (long num);
	StringBuilder& operator << (unsigned long num);
#ifndef WIN32
	StringBuilder& operator << (short num);
	StringBuilder& operator << (unsigned short num);
#endif
	//template<class T2> StringBuilder& operator << (StringT<T2> & str);

	StringBuilder& operator << (Utf32Char c);

	StringBuilder& operator << (float num);
	StringBuilder& operator << (double num);

	StringBuilder& operator << (const String& str);
#if 0
	{
		/*
		int charslen = str.Length();

		int newlen = m_buffer->m_len+charslen;
		if (newlen > m_buffer->m_alloclen)
		{
			m_alloclen = (newlen + 3) & ~3;
			m_str = (T*)m_allocator.reallocate_buffer(m_str, m_alloclen * sizeof(char));
		}

		memcpy(m_str + m_len, str.begin(), charslen);
		m_len = newlen;
		*/
		if (&str == NULL)
		{
			*this << "(null)";
			return *this;
		}

		size_t len = str.Length();

		for (unsigned int i = 0; i < len; i++)
		{
			T c = T(str.begin()[i]);
			ASSERT(c == str.begin()[i]);
			m_buffer->Write(&c, 1);
		}

		return *this;
	}
#endif
	StringBuilder& operator << (StringBuilder& other);

	void Append(char ch);
	void Append(const char* chars);
	void Append(const WCHAR* chars);

	StringObject* Detach();

//	void clear();

	StringObject* m_stringObject; 
	//BufferT<T>* m_buffer;

	//StringT<T>* ToString();
};

//typedef StringBuilder<char> StringBuilderA;
//typedef StringBuilder<WCHAR> StringBuilderW;

#if 0
template<class T>
void StringBuilder<T>::Append(T c)
{
	/*
	int newlen = m_len+1;
	if (newlen > m_alloclen)
	{
		m_alloclen = (newlen + 3) & ~3;
		m_str = (T*)m_allocator.reallocate_buffer(m_str, m_alloclen * sizeof(T));
	}

	m_str[m_len] = c;
	m_len = newlen;
	*/
	m_buffer->Write(&c, 1);
}

template<class T> StringBuilder<T>& StringBuilder<T>::operator << (Utf32Char c)
{
	if (c & 0xFFFF0000)
	{
		uint32 u = c - 0x10000;

		WCHAR w1 = 0xD800 | (u >> 10);
		WCHAR w2 = 0xDC00 | (u & 1023);

		*this << (WCHAR)w1;
		*this << (WCHAR)w2;
	}
	else
	{
		*this << (WCHAR)c;
	}

	return *this;
}

template<class T>
void StringBuilder<T>::Append(const char* chars)
{
	int charslen = cstrlen(chars);

	/*
	int newlen = m_len+charslen;
	if (newlen > m_alloclen)
	{
		m_alloclen = (newlen + 3) & ~3;
		m_str = (T*)m_allocator.reallocate_buffer(m_str, m_alloclen * sizeof(T));
	}

	memcpy(m_str + m_len, chars, charslen*sizeof(T));
	m_len = newlen;
	*/

	for (int i = 0; i < charslen; i++)
	{
		T c = chars[i];
		m_buffer->Write(&c, 1);
	}

	//m_buffer->Write(chars, charslen);
}

template<class T>
void StringBuilder<T>::Append(const WCHAR* chars)
{
	int charslen = cstrlen(chars);

	/*
	int newlen = m_len+charslen;
	if (newlen > m_alloclen)
	{
		m_alloclen = (newlen + 3) & ~3;
		m_str = (T*)m_allocator.reallocate_buffer(m_str, m_alloclen * sizeof(T));
	}

	memcpy(m_str + m_len, chars, charslen*sizeof(T));
	m_len = newlen;
	*/

	for (int i = 0; i < charslen; i++)
	{
		T c = chars[i];
		m_buffer->Write(&c, 1);
	}

	//m_buffer->Write(chars, charslen);
}

/*
template<class T>
StringBuilder<T>& StringBuilder<T, A>::operator = (const T* chars)
{
	m_len = cstrlen(chars);

	m_alloclen = (m_len + 3) & ~3;
	m_str = (T*)allocate_buffer(m_alloclen * sizeof(T));

	memcpy(m_str, chars, m_len*sizeof(T));

	return *this;
}
*/

/*
template<class T, class A>
void StringBuilder<T, A>::clear()
{
	m_len = 0;
	m_alloclen = 0;
	m_str = NULL;
}
*/

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (long num)
{
	bool bNegative = false;
	if (num < 0)
	{
		bNegative = true;
		num = -num;
	}

	T buffer[32];
	T* p = buffer+31;
	*p = 0;

	do
	{
		int digit = num % 10;
		num /= 10;

		*--p = (char)('0' + digit);
	}
	while (num > 0);

	if (bNegative) *--p = '-';

	*this << p;

	return *this;
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (unsigned long num)
{
	T buffer[32];
	T* p = buffer+31;
	*p = 0;

	do
	{
		int digit = num % 10;
		num /= 10;

		*--p = (char)('0' + digit);
	}
	while (num > 0);

	*this << p;

	return *this;
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (int num)
{
	return operator<<((long)num);
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (unsigned int num)
{
	return operator<<((unsigned long)num);
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (float num)
{
	ASSERT(0);
	return *this;
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (double num)
{
	ASSERT(0);
	return *this;
}

#ifndef WIN32

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (short num)
{
	return operator<<((long)num);
}

template<class T>
StringBuilder<T>& StringBuilder<T>::operator << (unsigned short num)
{
	return operator<<((unsigned long)num);
}

#endif

#endif

}	// System
