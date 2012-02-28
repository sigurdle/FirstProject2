#ifndef w3c_SVGFEDiffuseLightingElement_h
#define w3c_SVGFEDiffuseLightingElement_h

//#include "resource.h"       // main symbols

#include "PSVGFEDiffuseLightingElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEDiffuseLightingElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEDiffuseLightingElement>,
//	public CLElementEditASImpl<SVGFEDiffuseLightingElement>,
	public ElementEditVALImpl<SVGFEDiffuseLightingElement>,
//	public CLSVGFEElementImpl<SVGFEDiffuseLightingElement>,
	public SMILAnimationTargetImpl<SVGFEDiffuseLightingElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEDiffuseLightingElement>,
	protected CNotifySendImpl<SVGFEDiffuseLightingElement>
{
public:

	CTOR SVGFEDiffuseLightingElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();
	ISVGAnimatedNumber* get_surfaceScale();
	ISVGAnimatedNumber* get_diffuseConstant();
	ISVGAnimatedNumber* get_kernelUnitLengthX();
	ISVGAnimatedNumber* get_kernelUnitLengthY();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<SVGNumberValue> >* m_surfaceScale;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<SVGNumberValue> >* m_diffuseConstant;
//	CComObject<CATXMLAttr2T<CreateInstance<CLSVGAnimatedNumber>, CValueTypeWrapper<CSVGNumberValue> > >* m_diffuseConstant;
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

#endif // w3c_SVGFEDiffuseLightingElement_h
