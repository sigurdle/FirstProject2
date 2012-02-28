#ifndef __LSVGFEFuncRElement_H_
#define __LSVGFEFuncRElement_H_

//#include "resource.h"       // main symbols

#include "SVGComponentTransferFunctionElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEFuncRElement : 

	public SVGComponentTransferFunctionElementImpl<SVGFEFuncRElement>,
	public SMILAnimationTargetImpl<SVGFEFuncRElement>,
	public ElementEditVALImpl<SVGFEFuncRElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEFuncRElement>,
	protected CNotifySendImpl<SVGFEFuncRElement>
{
public:
	CTOR SVGFEFuncRElement()
	{
		SetAllValues(this);	// ???
	}

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

#endif //__LSVGFEFuncRElement_H_
