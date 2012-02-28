#ifndef Web_SMILFitValue_h
#define Web_SMILFitValue_h

namespace System
{
namespace Web
{

enum SMILEnumerationFitType
{
	Fit_fill = 1,
	Fit_hidden = 2,
	Fit_meet = 3,
	Fit_scroll = 4,
	Fit_slice = 5,
};

class SMILFitValue :
	public CSingleObject
{
public:

	CTOR SMILFitValue()
	{
		m_value = Fit_hidden;
	}

	SMILFitValue& operator = (const SMILFitValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	SMILFitValue& operator += (const SMILFitValue& value)
	{
		m_value = value.m_value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"fill")
			m_value = Fit_fill;
		else if (str == L"meet")
			m_value = Fit_meet;
		else if (str == L"scroll")
			m_value = Fit_scroll;
		else if (str == L"slice")
			m_value = Fit_slice;
		else if (str == L"hidden")
			m_value = Fit_hidden;
		else
			m_value = Fit_hidden;
	}

	String getStringValue();

	void InterpolateValue(const SMILFitValue& a, const SMILFitValue& b, double t)
	{
		m_value = a.m_value;
	}

	/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/

	SMILEnumerationFitType m_value;
};

}
}

#endif // Web_SMILFitValue_h
