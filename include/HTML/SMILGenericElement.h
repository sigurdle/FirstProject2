#ifndef __LSMILELEMENT_H_
#define __LSMILELEMENT_H_

#include "SMILElement.h"

namespace System
{
namespace Web
{

class HTMLEXT SMILGenericElement : 
	public SMILElement,

	protected CNotifyGetImpl<SMILGenericElement>,
	protected CNotifySendImpl<SMILGenericElement>
{
public:
	CTOR SMILGenericElement();

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}	// Web
}

#endif //__LSMILELEMENT_H_
