#ifndef Web_SVGFEMorphologyElement_h
#define Web_SVGFEMorphologyElement_h

#include "SVGEnumerationMorphologyOperatorValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEMorphologyElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEMorphologyElement>,
//	public CLElementEditASImpl<SVGFEMorphologyElement>,
	public ElementEditVALImpl<SVGFEMorphologyElement>,
	public SMILAnimationTargetImpl<SVGFEMorphologyElement>,
//	public CLSVGFEElementImpl<SVGFEMorphologyElement>,

	public IElementEditVAL	// INodeEditVAL

//	public CNotifyGetImpl<SVGFEMorphologyElement>,
//	public CNotifySendImpl<SVGFEMorphologyElement>
{
public:
	CTOR SVGFEMorphologyElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();
	ISVGAnimatedEnumeration* get__operator();
	ISVGAnimatedNumber* get_radiusX();
	ISVGAnimatedNumber* get_radiusY();

public:

	/*
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<CreateInstanceT<SVGEnumerationMorphologyOperatorValue> > >, CValueTypeWrapper<CreateInstanceT<SVGEnumerationMorphologyOperatorValue> > >* m_operator;
	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<SVGOptionalTwoNumbersValue> > > >, CValueTypeWrapper<CreateInstanceT<SVGOptionalTwoNumbersValue> > >* m_radius;

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/
};

}	// Web
}	// System

#endif // Web_SVGFEMorphologyElement_h
