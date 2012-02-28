#ifndef w3c_SVGFECompositeElement_h
#define w3c_SVGFECompositeElement_h

#include "SVGEnumerationCompositeOperatorValue.h"

#include "PSVGFECompositeElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFECompositeElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFECompositeElement>,
//	public CLElementEditASImpl<SVGFECompositeElement>,
	public ElementEditVALImpl<SVGFECompositeElement>
//	public SMILAnimationTargetImpl<SVGFECompositeElement>,
//	public CLSVGFEElementImpl<SVGFECompositeElement>,
{
public:

	CTOR SVGFECompositeElement(NamedNodeMap* attributes);

	ISVGAnimatedString* get_in1();
	ISVGAnimatedString* get_in2();
	ISVGAnimatedEnumeration* get_operator();
	ISVGAnimatedNumber* get_k1();
	ISVGAnimatedNumber* get_k2();
	ISVGAnimatedNumber* get_k3();
	ISVGAnimatedNumber* get_k4();

public:

	/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in2;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<CSVGEnumerationCompositeOperatorValue> >, CValueTypeWrapper<CSVGEnumerationCompositeOperatorValue> >* m_operator;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_k1;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_k2;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_k3;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_k4;
	*/
};

}	// w3c
}

#endif // w3c_SVGFECompositeElement_h
