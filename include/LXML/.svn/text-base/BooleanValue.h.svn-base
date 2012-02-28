#ifndef Web_BooleanValue_h
#define Web_BooleanValue_h

namespace System
{
namespace Web
{

class BooleanValue :
	public CSingleObject
{
public:

	/*
	CBooleanValue& operator * ()
	{
		return *this;
	}
	*/

	BooleanValue* operator -> ()
	{
		return this;
	}

	/*
	operator CBooleanValue* ()
	{
		return this;
	}
	*/

	operator bool ()
	{
		return m_value;
	}

	BooleanValue& operator = (const BooleanValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	BooleanValue& operator += (const BooleanValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		m_value = str == L"true"? true: false;
	}

	String getStringValue()
	{
		return m_value? WSTR("true"): WSTR("false");
	}

	void InterpolateValue(const BooleanValue& a, const BooleanValue& b, double t)
	{
		m_value = a.m_value;
	}

public:

	bool m_value;
};

}	// Web
}

#endif // Web_BooleanValue_h
