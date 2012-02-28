#ifndef w3c_SVGFEDistantLightElement_h
#define w3c_SVGFEDistantLightElement_h

//#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEDistantLightElement : 

	public SVGElement,
//	public CLElementEditASImpl<SVGFEDistantLightElement>,
	public ElementEditVALImpl<SVGFEDistantLightElement>,
	public SMILAnimationTargetImpl<SVGFEDistantLightElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEDistantLightElement>,
	protected CNotifySendImpl<SVGFEDistantLightElement>
{
public:
	CTOR SVGFEDistantLightElement(NamedNodeMap* attributes);

	ISVGAnimatedNumber* get_azimuth();
	ISVGAnimatedNumber* get_elevation();

public:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_azimuth;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_elevation;

protected:

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

#endif // w3c_SVGFEDistantLightElement_h
