#ifndef w3c_SVGFESpecularLightingElement_h
#define w3c_SVGFESpecularLightingElement_h

//#include "PSVGFESpecularLightingElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFESpecularLightingElement : 
	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFESpecularLightingElement>,
//	public ElementEditASImpl<SVGFESpecularLightingElement>,
	public ElementEditVALImpl<SVGFESpecularLightingElement>,
//	public SVGFEElementImpl<SVGFESpecularLightingElement>,
	public SMILAnimationTargetImpl<SVGFESpecularLightingElement>,

	protected CNotifyGetImpl<SVGFESpecularLightingElement>,
	protected CNotifySendImpl<SVGFESpecularLightingElement>
{
public:

	CTOR SVGFESpecularLightingElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();
	ISVGAnimatedNumber* get_surfaceScale();
	ISVGAnimatedNumber* get_specularConstant();
	ISVGAnimatedNumber* get_specularExponent();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<CreateInstanceT<SVGNumberValue> > >* m_surfaceScale;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<CreateInstanceT<SVGNumberValue> > >* m_specularConstant;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<CreateInstanceT<SVGNumberValue> > >* m_specularExponent;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}	// w3c
}

#endif // w3c_SVGFESpecularLightingElement_h
