#ifndef w3c_RGBColor_h
#define w3c_RGBColor_h

//#include "resource.h"       // main symbols

//#include "CSSPrimitiveValue.h"

namespace System
{
namespace Web
{

class WEBEXT RGBColor : public Object, protected ICSSPrimitiveValueListener
{
public:
	CTOR RGBColor();
	~RGBColor();

	virtual void OnCSSValueChanged(CSSPrimitiveValue* pValue)
	{
		if (m_pListener)
		{
			m_pListener->OnChangedRGBColor(this);
		}
	}

	CSSPrimitiveValue* get_blue();
	CSSPrimitiveValue* get_green();
	CSSPrimitiveValue* get_red();
	double get_alpha();
	void set_alpha(double newVal);

	double m_alpha;
	IRGBColorListener* m_pListener;
	CSSPrimitiveValue* m_red;
	CSSPrimitiveValue* m_green;
	CSSPrimitiveValue* m_blue;
};

}	// w3c
}

#endif // w3c_RGBColor_h
