#ifndef ColorValue_h
#define ColorValue_h

namespace System
{
namespace Web
{

class CColorValue :
	public CSingleObject
{
public:

	uint8 ClampRed()
	{
		return (uint8)MAX(MIN(m_red, 255), 0);
	}

	uint8 ClampGreen()
	{
		return (uint8)MAX(MIN(m_green, 255), 0);
	}

	uint8 ClampBlue()
	{
		return (uint8)MAX(MIN(m_blue, 255), 0);
	}

	CColorValue& operator = (const CColorValue& value)
	{
		m_red = value.m_red;
		m_green = value.m_green;
		m_blue = value.m_blue;

		return *this;
	}

	CColorValue& operator += (const CColorValue& value)
	{
		m_red += value.m_red;
		m_green += value.m_green;
		m_blue += value.m_blue;

		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"transparent")
		{
			m_alpha = 0;
		}
		else
		{
			//COLORREF clrref = ConvertColor(_bstr_t(bstr));

			ASSERT(0);
#if 0
			const WCHAR* p;
			LDraw::Color clr;
			if (ParseRGBColor(str->c_str(), &p, &clr) < 0)
				THROW(-1);//return;// E_INVALIDARG;
			if (*p != 0) THROW(-1);//return;// E_INVALIDARG;

			m_red = clr.GetR();
			m_green = clr.GetG();
			m_blue = clr.GetB();
			m_alpha = clr.GetA();//255;
#endif
		}
	}

	String getStringValue()
	{
		if (m_alpha == 0)
		{
			return WSTR("transparent");
		}
		else
		{
			WCHAR buf[64];
			swprintf_s(buf, L"#%2.2X%2.2X%2.2X", ClampRed(), ClampGreen(), ClampBlue());
			return string_copy(buf);
		}
	}

	void InterpolateValue(const CColorValue& a, const CColorValue& b, double t)
	{
		m_red = a.m_red + (b.m_red - a.m_red)*t;
		m_green = a.m_green + (b.m_green - a.m_green)*t;
		m_blue = a.m_blue + (b.m_blue - a.m_blue)*t;
		m_alpha = a.m_alpha;
	}

public:
	double m_red;
	double m_green;
	double m_blue;
	uint8 m_alpha;
};

}
}

#endif // ColorValue_h
