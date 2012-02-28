#ifndef w3c_SVGPaint_h
#define w3c_SVGPaint_h

//#include "resource.h"       // main symbols

#include "SVGColorImpl.h"

namespace System
{
namespace Web
{

class WEBEXT SVGPaint : public SVGColorBase
{
public:
	CTOR SVGPaint();
	~SVGPaint();

//	int FinalConstruct();
//	void FinalRelease();

	ErrorCode ParseString(StringIn string);
	void UpdateCSSText();

//	void operator = (const SVGPaint& value);
//	void operator += (const SVGPaint& value);

	/*
	void setString(const StringW& value)
	{
		set_cssText(value);
	}
	*/

	String getStringValue()
	{
		return get_cssText();
	}

	void InterpolateValue(const SVGPaint& a, const SVGPaint& b, double t);

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

	void setPaint(SVGPaintType paintType, StringIn uri, uint8 clr[3]);

// SVGPaint
	void setUri(StringIn uri);
	void setPaint(SVGPaintType paintType, StringIn uri, StringIn rgbColor, StringIn iccColor);
	String get_uri();
	SVGPaintType get_paintType() const;

// SVGColor
	void setRGBColor(StringIn rgbColor)
	{
		SVGColorBase::setRGBColor(rgbColor);
		m_paintType = (SVGPaintType)m_colorType;
	}
	void setRGBColorICCColor(StringIn rgbColor, StringIn iccColor)
	{
		SVGColorBase::setRGBColorICCColor(rgbColor, iccColor);
		m_paintType = (SVGPaintType)m_colorType;
	}
	void setColor(SVGColorType colorType, StringIn rgbColor, StringIn iccColor)
	{
		SVGColorBase::setColor(colorType, rgbColor, iccColor);
		m_paintType = (SVGPaintType)m_colorType;
	}

// CSSValue
	String get_cssText();
	void set_cssText(StringIn newVal);

	ISVGPaintListener* m_pListener;

protected:

	String m_uri;
	SVGPaintType m_paintType;
};

}	// Web
}

#endif // w3c_SVGPaint_h
