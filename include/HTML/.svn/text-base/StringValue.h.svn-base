#ifndef w3c_StringValue_h
#define w3c_StringValue_h

namespace System
{
namespace Web
{

class CStringValue :
	public CSingleObject
{
public:
	CStringValue& operator = (const CStringValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	CStringValue& operator += (const CStringValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	void setStringValue(System::StringW* str)
	{
		m_value = str;
	}

	System::StringW* getStringValue()
	{
		return m_value;
	}

	void InterpolateValue(const CStringValue& a, const CStringValue& b, double t)
	{
		m_value = a.m_value;
	}

	/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/

	System::StringW* m_value;
};

}	// Web
}

#endif // w3c_StringValue_h
