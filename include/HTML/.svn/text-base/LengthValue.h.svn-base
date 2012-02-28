#ifndef __LengthValue_h__
#define __LengthValue_h__

namespace System
{
namespace Web
{

class HTMLEXT CLengthValue :
	public CSingleObject
{
public:
	CTOR CLengthValue()
	{
		m_unitType = (CSSUnitType)-1;	// Defaults to auto (should this be the way ??)
		m_value = 0;
	}

	CLengthValue& operator = (const CLengthValue& value)
	{
		m_value = value.m_value;
		m_unitType = value.m_unitType;
		return *this;
	}

	CLengthValue& operator += (const CLengthValue& value)
	{
		m_value += value.m_value;
		m_unitType = value.m_unitType;
		return *this;
	}

	void setStringValue(System::StringW* str)
	{
		ASSERT(0);
#if 0
		if (bstr == NULL || bstr[0] == 0 || !wcscmp(bstr, L"auto"))
			m_unitType = (CSSUnitType)-1;
		else
			m_value = ParseValueUnitString(bstr, (int*)&m_unitType);
#endif
	// ???
		if (m_pListener)
			m_pListener->OnChanged(this);
	}

	String getStringValue()
	{
		if (m_unitType == (CSSUnitType)-1)
			return WSTR("auto");
		else
			return CreateValueUnitString(m_value, m_unitType);
	}

	void InterpolateValue(const CLengthValue& a, const CLengthValue& b, double t)
	{
		m_unitType = a.m_unitType;	// TODO
		m_value = a.m_value + (b.m_value - a.m_value)*t;
	}

	/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/
	double m_value;
	CSSUnitType m_unitType;
};

}
}

#endif // __LengthValue_h__
