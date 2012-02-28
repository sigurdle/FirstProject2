#ifndef __SVGComponentTransferFunctionElementImpl_h__
#define __SVGComponentTransferFunctionElementImpl_h__

#include "SVGEnumerationComponentTransferTypeValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGComponentTransferFunctionElementImplImpl : public SVGElement
{
public:
	CTOR SVGComponentTransferFunctionElementImplImpl() : SVGElement(NULL/*TODO*/)
	{
		m_slope = NULL;
		m_tableValues = NULL;
		m_intercept = NULL;
		m_amplitude = NULL;
		m_exponent = NULL;
		m_offset = NULL;
	}

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationComponentTransferTypeValue> >, CValueTypeWrapper<SVGEnumerationComponentTransferTypeValue> >* m_type;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumberList>, CValueTypeWrapper<CreateInstanceT<SVGNumberList> > >* m_tableValues;
	SVGAnimatedNumber* m_slope;
	SVGAnimatedNumber* m_intercept;
	SVGAnimatedNumber* m_amplitude;
	SVGAnimatedNumber* m_exponent;
	SVGAnimatedNumber* m_offset;
};

template<class T, class IBase = SVGComponentTransferFunctionElementImplImpl> class SVGComponentTransferFunctionElementImpl :
	public IBase
{
public:
	CTOR SVGComponentTransferFunctionElementImpl()
	{
		ASSERT(0);
		/*
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_type, NULL, WSTR("type")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_tableValues, NULL, WSTR("tableValues")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_slope, NULL, WSTR("slope")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_intercept, NULL, WSTR("intercept")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_amplitude, NULL, WSTR("amplitude")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_exponent, NULL, WSTR("exponent")));
		static_cast<T*>(this)->AddXMLAttribute(NewXMLAttr(&m_offset, NULL, WSTR("offset")));
		*/
	}

	ISVGAnimatedEnumeration* get_type()
	{
		return m_type->m_animated;
	}

	SVGAnimatedNumberList* get_tableValues()
	{
		return m_tableValues->m_animated;
	}

	ISVGAnimatedNumber* get_slope()
	{
		return m_slope;
	}

	ISVGAnimatedNumber* get_intercept()
	{
		return m_intercept;
	}

	ISVGAnimatedNumber* get_amplitude()
	{
		return m_amplitude;
	}

	ISVGAnimatedNumber* get_exponent()
	{
		return m_exponent;
	}

	ISVGAnimatedNumber* get_offset()
	{
		return m_offset;
	}
};

}	// w3c
}

#endif // __SVGComponentTransferFunctionElementImpl_h__
