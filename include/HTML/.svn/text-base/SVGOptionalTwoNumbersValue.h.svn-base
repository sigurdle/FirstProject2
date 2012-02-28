#ifndef SVGOptionalTwoNumbersValue_h
#define SVGOptionalTwoNumbersValue_h

namespace System
{
namespace Web
{

class SVGOptionalTwoNumbersValue :
	public CSingleObject
{
public:

	SVGOptionalTwoNumbersValue* operator -> ()
	{
		return this;
	}

	SVGOptionalTwoNumbersValue& operator = (SVGOptionalTwoNumbersValue& value)
	{
		m_value[0] = value.m_value[0];
		m_value[1] = value.m_value[1];

		return *this;
	}

	SVGOptionalTwoNumbersValue& operator += (SVGOptionalTwoNumbersValue& value)
	{
		m_value[0] += value.m_value[0];
		m_value[1] += value.m_value[1];

		return *this;
	}

	void setStringValue(StringIn str)
	{
		vector<double> values;
		GetCommaOrSpaceSepNumberArray(str, values);
		if (values.GetSize() > 0)
		{
			if (values.GetSize() == 1)
			{
				m_value[0] = values[0];
				m_value[1] = values[0];
			}
			else
			{
				m_value[0] = values[0];
				m_value[1] = values[1];
			}
		}

		if (m_pListener)
			m_pListener->OnChanged(this);
	}

	String getStringValue()
	{
		WCHAR buf[64];

		if (m_value[1] != m_value[0])
		{
			swprintf_s(buf, L"%g %g", m_value[0], m_value[1]);
		}
		else
		{
			swprintf_s(buf, L"%g", m_value[0]);
		}

		return string_copy(buf);
	}

	void InterpolateValue(SVGOptionalTwoNumbersValue& a, SVGOptionalTwoNumbersValue& b, double t)
	{
		m_value[0] = a.m_value[0] + (b.m_value[0] - a.m_value[0])*t;
		m_value[1] = a.m_value[1] + (b.m_value[1] - a.m_value[1])*t;
	}

	double m_value[2];
};

	/*
class CSVGAnimatedOptionalTwoNumbers
{
public:
	CComObject<CLSVGAnimatedNumber>* m_numbers[2];

	SVGOptionalTwoNumbersValue m_baseVal;
	SVGOptionalTwoNumbersValue m_animVal;

	CSVGAnimatedOptionalTwoNumbers* operator -> ()
	{
		return this;
	}
};
*/

}	// Web
}


#endif // SVGOptionalTwoNumbersValue_h
