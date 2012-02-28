#ifndef Web_SVGICCColor_h
#define Web_SVGICCColor_h

//#include "resource.h"       // main symbols

namespace System
{
	/*
namespace Web
{
class SVGNumberList;
}
*/

namespace Web
{

class WEBEXT SVGICCColor : 
//	public ILSVGICCColor
	public System::Object

//	public CSSPrimitiveValueListener
{
public:
	CTOR SVGICCColor()
	{
		m_colors = NULL;

		m_pListener = NULL;
	}

	~SVGICCColor()
	{
		ASSERT(m_pListener == NULL);
	}

	String get_colorProfile() const;
	void set_colorProfile(StringIn newVal);
	Web::SVGNumberList* get_colors();

	/*
	virtual void OnCSSValueChanged(CSSPrimitiveValue* pValue)
	{
		if (m_pListener)
		{
			m_pListener->OnChangedRGBColor(this);
		}
	}
	*/

	ErrorCode ParseICCColor(const WCHAR* s, const WCHAR* *pp);

	ISVGICCColorListener* m_pListener;

	Web::SVGNumberList* m_colors;

protected:

	String m_colorProfile;
};

}	// Web
}

#endif // Web_SVGICCColor_h
