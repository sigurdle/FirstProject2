#ifndef SVGFEColorMatrixElement_h
#define SVGFEColorMatrixElement_h

#include "SVGEnumerationColorMatrixTypeValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEColorMatrixElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEColorMatrixElement>,
//	public CLElementEditASImpl<SVGFEColorMatrixElement>,
	public ElementEditVALImpl<SVGFEColorMatrixElement>,
	public SMILAnimationTargetImpl<SVGFEColorMatrixElement>,
//	public CLSVGFEElementImpl<SVGFEColorMatrixElement>,

	//public IElementEditVAL,	// ILNodeEditVAL

	protected AnimatedAttributeT<SVGAnimatedString, 0>,
	protected AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationColorMatrixTypeValue>, 1>,
	protected AnimatedAttributeT<SVGAnimatedNumberList, 2>
{
public:

	CTOR SVGFEColorMatrixElement(NamedNodeMap* attributes);

	AnimatedAttributeT<SVGAnimatedString, 0>& in1_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedString, 0>*>(this);
	}
	AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationColorMatrixTypeValue>, 1>& type_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedEnumerationT<SVGEnumerationColorMatrixTypeValue>, 1>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedNumberList, 2>& values_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedNumberList, 2>*>(this);
	}

	ISVGAnimatedString* get_in1();
	ISVGAnimatedEnumeration* get_type();
	ISVGAnimatedNumberList* get_values();

/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationColorMatrixTypeValue> >, CValueTypeWrapper<CreateInstanceT<SVGEnumerationColorMatrixTypeValue> > >* m_type;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumberList>, CValueTypeWrapper<CreateInstanceT<SVGNumberList> > >* m_values;
	*/
};

}	// Web
}	// System

#endif // SVGFEColorMatrixElement_h
