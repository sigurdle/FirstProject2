#ifndef __LSVGFEFUNCBELEMENT_H_
#define __LSVGFEFUNCBELEMENT_H_

//#include "resource.h"       // main symbols

#include "SVGComponentTransferFunctionElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEFuncBElement : 
	public SVGComponentTransferFunctionElementImpl<SVGFEFuncBElement>,
	public SMILAnimationTargetImpl<SVGFEFuncBElement>,
	public ElementEditVALImpl<SVGFEFuncBElement>,

	//public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEFuncBElement>,
	protected CNotifySendImpl<SVGFEFuncBElement>
{
public:
	CTOR SVGFEFuncBElement()
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

}	// LSVG
}

#endif //__LSVGFEFUNCBELEMENT_H_
