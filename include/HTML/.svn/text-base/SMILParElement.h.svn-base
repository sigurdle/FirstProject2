#ifndef __LSMILPARELEMENT_H_
#define __LSMILPARELEMENT_H_

//#include "resource.h"       // main symbols

#include "SMILElement.h"

namespace System
{
namespace Web
{

class HTMLEXT SMILParElement : 

	public SMILElement,
//	public ElementTimeContainerImpl,//<SMILParElement>,
	public SMILAnimationTargetImpl<SMILParElement>,	// Not really
	public SVGTestsImpl<SMILParElement>,

//	public IElementParallelTimeContainer,

	protected CNotifyGetImpl<SMILParElement>,
	protected CNotifySendImpl<SMILParElement>
{
public:
	typedef ElementTimeContainerImpl/*<SMILParElement>*/ timeBase;

	CTOR SMILParElement(NamedNodeMap* attributes);

	void seekElement(double seekTo);

	ElementTimeContainerImpl* m_timeContainerImpl;

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

#endif //__LSMILPARELEMENT_H_
