#ifndef __LSVGFEFUNCGELEMENT_H_
#define __LSVGFEFUNCGELEMENT_H_

//#include "resource.h"       // main symbols

#include "SVGComponentTransferFunctionElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEFuncGElement : 

	public SVGComponentTransferFunctionElementImpl<SVGFEFuncGElement>,
	public SMILAnimationTargetImpl<SVGFEFuncGElement>,
	public ElementEditVALImpl<SVGFEFuncGElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEFuncGElement>,
	protected CNotifySendImpl<SVGFEFuncGElement>
{
public:
	CTOR SVGFEFuncGElement()
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

#endif //__LSVGFEFUNCGELEMENT_H_
