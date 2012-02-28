namespace System
{

class LFCEXT ComBSTR
{
public:

	CTOR ComBSTR() : m_str(nullptr)
	{
	}

	CTOR ComBSTR(decltype(nullptr)) : m_str(nullptr)
	{
	}

	CTOR ComBSTR(const ComBSTR& other)
	{
		m_str = SysAllocStringLen(other.m_str, other.GetLength());
	}

	CTOR ComBSTR(ComBSTR&& other) : m_str(other.m_str)
	{
		other.m_str = nullptr;
	}

	CTOR ComBSTR(const OLECHAR* cstr)
	{
		m_str = SysAllocString(cstr);
	}

	CTOR ComBSTR(const OLECHAR* cstr, UINT len)
	{
		m_str = SysAllocStringLen(cstr, len);
	}

	CTOR ComBSTR(const String& str)
	{
		if (str != nullptr)
		{
			UINT len = str.GetLength32();
			m_str = SysAllocStringLen(nullptr, len);
			str.CopyTo(m_str, len);
		}
		else
		{
			m_str = nullptr;
		}
	}

	~ComBSTR()
	{
		if (m_str)
		{
			SysFreeString(m_str);
		}
	}

	BSTR* operator & ()
	{
		/*
		if (m_str)
		{
			SysFreeString(m_str);
			m_str = nullptr;

		}
		*/
		ASSERT(m_str == nullptr);
		return &m_str;
	}

	ComBSTR& operator = (decltype(nullptr))
	{
		if (m_str)
		{
			SysFreeString(m_str);
			m_str = nullptr;
		}
		return *this;
	}

	ComBSTR& operator = (const ComBSTR& other)
	{
		if (m_str != other.m_str)
		{
			if (m_str) SysFreeString(m_str);
			m_str = SysAllocStringLen(other.m_str, other.GetLength());
		}
		return *this;
	}

	ComBSTR& operator = (ComBSTR&& other)
	{
		if (m_str != other.m_str)
		{
			if (m_str) SysFreeString(m_str);
			m_str = other.m_str;
			other.m_str = nullptr;
		}
		return *this;
	}

	void Attach(BSTR str)
	{
		if (m_str) SysFreeString(m_str);
		m_str = str;
	}

	BSTR Detach() throw()
	{
		BSTR bstr = m_str;
		m_str = nullptr;
		return bstr;
	}

	BSTR GetData() const throw()
	{
		return m_str;
	}

	operator BSTR () const throw()
	{
		return m_str;
	}

	UINT GetLength() const throw()
	{
		return SysStringLen(m_str);
	}

	bool IsEmpty() const throw()
	{
		return SysStringLen(m_str) == 0;
	}

	bool IsNull() const throw()
	{
		return operator==(nullptr);
	}

	bool operator < (const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_LT;
	}

	bool operator > (const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_GT;
	}

	bool operator <= (const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_LT || hr == VARCMP_EQ;
	}

	bool operator >= (const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_GT || hr == VARCMP_EQ;
	}

	bool operator == (const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_EQ;
	}

	bool operator != (const ComBSTR& bstrSrc) const throw ()
	{
		return !operator==(bstrSrc);
	}

	bool operator ! () const throw ()
	{
		return m_str == nullptr;
	}

	bool operator == (decltype(nullptr)) const throw ()
	{
		return m_str == nullptr;
	}

	bool operator != (decltype(nullptr)) const throw ()
	{
		return !operator==(nullptr);
	}

	int CompareNoCase(const ComBSTR& bstrSrc) const throw ()
	{
		HRESULT hr = VarBstrCmp(m_str, bstrSrc.m_str, LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		return hr - 1;
	}

	HRESULT AppendBSTR(BSTR str) throw ()
	{
		if (SysStringLen(str) == 0) return S_OK;

		BSTR newstr;
		HRESULT hr = VarBstrCat(m_str, str, &newstr);
		if (SUCCEEDED(hr))
		{
			SysFreeString(m_str);
			m_str = newstr;
		}
		return hr;
	}

	ComBSTR operator + (const ComBSTR& bstrSrc) const
	{
		ComBSTR bstrDest;
		ThrowHr(VarBstrCat(m_str, bstrSrc.GetData(), &bstrDest));
		return bstrDest;
	}

	ComBSTR& operator += (const ComBSTR& bstrSrc)
	{
		ThrowHr(AppendBSTR(bstrSrc.GetData()));
		return *this;
	}

	// From

	static ComBSTR FromR4(float value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromR4(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR FromR8(double value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromR8(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR FromDate(DATE value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromDate(value, lcid, dwFlags, &str);
		return str;
	}

#ifndef __LERSTAD__
	static ComBSTR FromDecimal(const DECIMAL* value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromDec(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR FromDecimal(const DECIMAL& value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromDec(&value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR FromCy(CY value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromCy(value, lcid, dwFlags, &str);
		return str;
	}
#endif

	static ComBSTR FromVector(SAFEARRAY *psa)
	{
		ComBSTR str;
		ThrowHr(::BstrFromVector(psa, &str));
		return str;
	}

	static ComBSTR FromDispatch(IDispatch* pdisp, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromDisp(pdisp, lcid, dwFlags, &str);
		return str;
	}

	// overloads

	static ComBSTR From(short value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromI2(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(unsigned short value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromUI2(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(int value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromI4(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(unsigned int value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromUI4(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(long long value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromI8(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(unsigned long long value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromUI8(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(float value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromR4(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(double value, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromR8(value, lcid, dwFlags, &str);
		return str;
	}

	static ComBSTR From(SAFEARRAY *psa)
	{
		ComBSTR str;
		ThrowHr(::BstrFromVector(psa, &str));
		return str;
	}

	static ComBSTR From(IDispatch* pdisp, LCID lcid = LOCALE_USER_DEFAULT, DWORD dwFlags = 0)
	{
		ComBSTR str;
		::VarBstrFromDisp(pdisp, lcid, dwFlags, &str);
		return str;
	}

	/*
	bool LoadString(HINSTANCE hInst, UINT nID) throw()
	{
		::SysFreeString(m_str);
		m_str = NULL;
		return LoadStringResource(hInst, nID, m_str);
	}
	*/

private:

	BSTR m_str;
};

inline Variant::Variant(ComBSTR&& str)
{
	m_pType = typeid(ComBSTR);
	u.bstr_val = str.Detach();
}

LFCEXT IO::TextReader& ReadFromStream(IO::TextReader& reader, ComBSTR& str);

inline IO::TextWriter& WriteToStream(IO::TextWriter& writer, const ComBSTR& bstr)
{
	writer.WriteChars(bstr.GetData(), bstr.GetLength());
	return writer;
}

}	// System
