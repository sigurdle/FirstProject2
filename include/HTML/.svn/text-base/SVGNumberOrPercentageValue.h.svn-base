#ifndef SVGNumberOrPercentageValue_h
#define SVGNumberOrPercentageValue_h

namespace System
{
namespace Web
{

class SVGNumberOrPercentageValue :
	public CSingleObject
{
public:

	/*
	SVGNumberOrPercentageValue& operator * ()
	{
		return *this;
	}
	*/

	SVGNumberOrPercentageValue* operator -> ()
	{
		return this;
	}

	/*
	operator SVGNumberOrPercentageValue* ()
	{
		return this;
	}
	*/

	SVGNumberOrPercentageValue& operator = (double value)
	{
		m_value = value;
		return *this;
	}

	SVGNumberOrPercentageValue& operator += (double value)
	{
		m_value += value;
		return *this;
	}

	operator double () const
	{
		return m_value;
	}

	void setStringValue(StringIn str)
	{
	//	System::StringW* str = bstr;//stripspaces(bstr);
		if (str.GetLength() > 0)
		{
			ASSERT(0);
			/*
			if ((str->c_str())[str->Length()-1] == L'%')
				m_value = getfnumber(str->c_str())/100.0;
			else
				m_value = getfnumber(str->c_str());
				*/
		}
		else
			m_value = 0;
	}

	String getStringValue()
	{
		WCHAR buf[64];
		swprintf_s(buf, L"%g", m_value);
		return string_copy(buf);
	}

	void InterpolateValue(const SVGNumberOrPercentageValue& a, const SVGNumberOrPercentageValue& b, double t)
	{
		m_value = a.m_value + (b.m_value - a.m_value)*t;
	}

public:

	double m_value;
};

}	// Web
}

#endif // SVGNumberOrPercentageValue_h
