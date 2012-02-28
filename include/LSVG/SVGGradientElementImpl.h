#ifndef w3c_SVGGradientElement_h
#define w3c_SVGGradientElement_h

#include "SVGEnumerationSpreadMethodTypeValue.h"
//#include "SVGTransformList.h"
//#include "SVGAnimatedTransformList.h"

namespace System
{
namespace Web
{

class SVGEXT SVGGradientElement : public SVGElement
{
public:
	CTOR SVGGradientElement(PSVGElement* element, NamedNodeMap* attributes) : SVGElement(element, attributes)
	{
		m_gradientUnits = NULL;
		m_spreadMethod = NULL;
		m_gradientTransform = NULL;
	}

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationSpreadMethodTypeValue> >, CValueTypeWrapper<SVGEnumerationSpreadMethodTypeValue> >* m_spreadMethod;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_gradientUnits;
	SVGAnimatedTransformList* m_gradientTransform;
};

template <class T> class SVGEXT SVGGradientElementImpl :
	public SVGGradientElement,
//	public CLSVGElementImpl<T, IBase>,
	public SVGURIReferenceImpl<T>,
	public SVGStylableImpl<T>,
	public ISingleObjectListener
{
public:
	CTOR SVGGradientElementImpl(PSVGElement* pelement, NamedNodeMap* attributes) : SVGGradientElement(pelement, attributes)
	{
		/*static_cast<T*>(this)->*/AddXMLAttribute(NewXMLAttr(&m_gradientUnits, NULL, WSTR("gradientUnits"), WSTR("objectBoundingBox")));
		/*static_cast<T*>(this)->*/AddXMLAttribute(NewXMLAttr(&m_spreadMethod, NULL, WSTR("spreadMethod"), WSTR("pad")));
	//	/*static_cast<T*>(this)->*/AddXMLAttribute(NewXMLAttr(&m_gradientTransform, NULL, WSTR("gradientTransform")));

#if 0
		m_gradientTransform->m_baseVal->m_pListener = this;
#endif
	}

	~SVGGradientElementImpl()
	{
		//m_gradientTransform->m_baseVal->m_pListener = NULL;
	}

	virtual void OnChanged(CSingleObject* pObject)
	{
		ASSERT(0);
	//	m_gradientTransform->m_animated->m_pAttr->OnBaseValChanged();
	}

	ISVGAnimatedEnumeration* get_gradientUnits()
	{
		return m_gradientUnits->m_animated;
	}

	ISVGAnimatedEnumeration* get_spreadMethod()
	{
		return m_spreadMethod->m_animated;
	}

	SVGAnimatedTransformList* get_gradientTransform()
	{
		return m_gradientTransform;
	}
};

}	// w3c
}

#endif // w3c_SVGGradientElement_h
