#ifndef Web_LongValue_h
#define Web_LongValue_h

namespace System
{
namespace Web
{

class LongValue : public CSingleObject
{
public:
	LongValue* operator -> ()
	{
		return this;
	}

	LongValue& operator += (const LongValue& value)
	{
		m_value += value.m_value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		ASSERT(0);
		//m_value = getfnumber(str->c_str());
	}

	String getStringValue()
	{
		WCHAR buf[64];
		swprintf_s(buf, L"%d", (long)m_value);
		return string_copy(buf);
	}

	void InterpolateValue(const LongValue& a, const LongValue& b, double t)
	{
		m_value = a.m_value + (b.m_value - a.m_value)*t;
	}

	double m_value;
};

}	// Web
}	// System

#endif // Web_LongValue_h
