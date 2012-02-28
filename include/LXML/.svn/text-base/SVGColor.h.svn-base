#ifndef Web_SVGColor_h
#define Web_SVGColor_h

//#include "resource.h"       // main symbols

#include "SVGColorImpl.h"

namespace System
{
namespace Web
{

class WEBEXT SVGColor : public SVGColorBase
{
public:
	CTOR SVGColor()
	{
		m_colorType = SVG_COLORTYPE_UNKNOWN;

		m_pListener = NULL;
	}

	~SVGColor()
	{
		//	TODO have this: ASSERT(m_pListener == NULL);
	}

//	int FinalConstruct();
//	void FinalRelease();

	ErrorCode ParseString(StringIn string);

	ISVGColorListener* m_pListener;

	void operator = (const SVGColor& value);
	void operator += (const SVGColor& value);

	/*
	void setString(const StringW& value)
	{
		set_cssText(value);
	}
	*/

#if 0
	operator StringW ()
	{
		return get_cssText();
	}
	#endif

	void InterpolateValue(const SVGColor& a, const SVGColor& b, double t);

	virtual void OnChangedRGBColor(RGBColor* pRGBColor)
	{
		m_bCSSTextUpdated = false;

		if (m_pListener)
		{
			m_pListener->OnCSSValueChanged(this);
		}
	}

	virtual void OnChangedICCColor(SVGICCColor* pRGBColor)
	{
		m_bCSSTextUpdated = false;

		if (m_pListener)
		{
			m_pListener->OnCSSValueChanged(this);
		}
	}

	void set_cssText(StringIn newVal);
};

}	// Web
}

#endif // Web_SVGColor_h
