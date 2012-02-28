#ifndef __LSMILTOPLAYOUTELEMENT_H_
#define __LSMILTOPLAYOUTELEMENT_H_

namespace System
{
namespace Web
{

class HTMLEXT SMILTopLayoutElement : 
	public SMILElement,
	public SMILElementLayoutImpl<SMILTopLayoutElement>,
	public SMILAnimationTargetImpl<SMILTopLayoutElement>,

	protected CNotifyGetImpl<SMILTopLayoutElement>,
	protected CNotifySendImpl<SMILTopLayoutElement>
{
public:

	CTOR SMILTopLayoutElement(NamedNodeMap* attributes);

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

#endif //__LSMILTOPLAYOUTELEMENT_H_
