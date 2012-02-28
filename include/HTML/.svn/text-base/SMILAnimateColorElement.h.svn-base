#ifndef w3c_SMILAnimateColorElement_h
#define w3c_SMILAnimateColorElement_h

//#include "resource.h"       // main symbols

//#include "SMILAnimationElementImpl.h"
//#include "AnimationTarget.h"
//#include "../LXML/AnimationElement.h"

namespace System
{
namespace Web
{

class HTMLEXT SMILAnimateColorElement : 

	public SMILAnimationElement,//Impl<SMILAnimateColorElement>,
//	public AnimateElementImpl,//<SMILAnimateColorElement>,

//	public IElementAnimate,	//ILElementAnimate	//ILAnimationElement //ILElementTime

	protected CNotifyGetImpl<SMILAnimateColorElement>,
	protected CNotifySendImpl<SMILAnimateColorElement>
{
public:
	CTOR SMILAnimateColorElement(NamedNodeMap* attributes);

//	ElementAnimateImpl* m_animateImpl;

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

#endif // w3c_SMILAnimateColorElement_h
