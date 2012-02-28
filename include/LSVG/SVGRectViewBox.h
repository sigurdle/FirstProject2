#ifndef Web_SVGRectViewBox_h
#define Web_SVGRectViewBox_h

namespace System
{
namespace Web
{

class SVGEXT SVGRectViewBox : 
	public SVGRectImpl
	//public CSingleObject
{
public:
	CTOR SVGRectViewBox()
	{
	}

	SVGRectViewBox& operator = (const SVGRectViewBox& value)
	{
		m_x = value.m_x;
		m_y = value.m_y;
		m_width = value.m_width;
		m_height = value.m_height;

		return *this;
	}

	SVGRectViewBox& operator += (const SVGRectViewBox& value)
	{
		m_x += value.m_x;
		m_y += value.m_y;
		m_width += value.m_width;
		m_height += value.m_height;

		return *this;
	}

	/*
	virtual void setStringValue(System::StringW* str)
	{
		ASSERT(0);
	}
	*/

	void setStringValue(StringIn str)
	{
		m_x = 0;
		m_y = 0;
		m_width = -1;
		m_height = -1;

	//	if (str)
		{
			vector<double> numbers;
			GetCommaOrSpaceSepNumberArray(str, numbers);
			if (numbers.GetSize() == 4)
			{
				m_x = numbers[0];
				m_y = numbers[1];
				m_width = numbers[2];
				m_height = numbers[3];
			}
		}
	}

	String getStringValue()
	{
		WCHAR buf[256];
		swprintf_s(buf, L"%g %g %g %g", m_x, m_y, m_width, m_height);
		return string_copy(buf);
	}

};

}	// w3c
}

#endif // Web_SVGRectViewBox_h
