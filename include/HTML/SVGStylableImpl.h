#ifndef __SVGStylableImpl_h__
#define __SVGStylableImpl_h__

//#include "SVGAnimatedString.h"

namespace System
{
namespace Web
{

template<class T> class SVGStylableImpl
#ifndef __LERSTAD__
:
	public ElementCSSInlineStyleImpl<T>
#endif
{
public:
#if 0
	SVGStylableImpl()
	{
		m_className = NULL;
	}

	~SVGStylableImpl()
	{
	}

	int FinalConstruct()
	{
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_className, L"", L"class"));

		return 0;
	}

	LCATXMLAttr2T<CComObjectCreateInstance<CLSVGAnimatedString>, CValueTypeWrapper<CStringValue> >* m_className;
#endif

	ISVGAnimatedString* get_className()
	{
		ASSERT(0);
		return NULL;
	//	return m_className->m_animated;
	}

	CSSValue* getPresentationAttribute(StringIn name)
	{
		return static_cast<T*>(this)->m_presentationAttributes->getPropertyCSSValue(name);
	}
};

}	// Web
}

#endif // __SVGStylableImpl_h__
