#ifndef __SVGFEFUNCAELEMENT_H__
#define __SVGFEFUNCAELEMENT_H__

//#include "resource.h"       // main symbols

#include "SVGComponentTransferFunctionElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEFuncAElement : 

	public SVGComponentTransferFunctionElementImpl<SVGFEFuncAElement>,
		public SMILAnimationTargetImpl<SVGFEFuncAElement>,
		public ElementEditVALImpl<SVGFEFuncAElement>,

	//public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEFuncAElement>,
	protected CNotifySendImpl<SVGFEFuncAElement>
{
public:
	CTOR SVGFEFuncAElement()
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

#endif // __SVGFEFUNCAELEMENT_H__
