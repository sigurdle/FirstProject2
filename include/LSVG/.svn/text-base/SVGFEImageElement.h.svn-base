#ifndef __SVGFEIMAGEELEMENT_H__
#define __SVGFEIMAGEELEMENT_H__

//#include "resource.h"       // main symbols

#include "SVGPreserveAspectRatio.h"
#include "SVGAnimatedPreserveAspectRatio.h"

namespace System
{
namespace Web
{

//class CImage;

class SVGEXT SVGFEImageElement : 
	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEImageElement>,
	public SVGURIReferenceImpl<SVGFEImageElement>,
//	public ElementEditASImpl<SVGFEImageElement>,
	public ElementEditVALImpl<SVGFEImageElement>,
//	public SVGFEElementImpl<SVGFEImageElement>,
	public SMILAnimationTargetImpl<SVGFEImageElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<SVGFEImageElement>,
	public CNotifySendImpl<SVGFEImageElement>
{
public:
	CTOR SVGFEImageElement();

	SVGAnimatedPreserveAspectRatio* get_preserveAspectRatio();
	CImage* GetImage();

public:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedPreserveAspectRatio>, CValueTypeWrapper<CreateInstanceT<SVGPreserveAspectRatio> > >* m_preserveAspectRatio;

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	CImage* m_pImage;
};

}	// w3c
}

#endif // __SVGFEIMAGEELEMENT_H__
