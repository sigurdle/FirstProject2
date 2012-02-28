#ifndef __LSMILSEQELEMENT_H_
#define __LSMILSEQELEMENT_H_

//#include "resource.h"       // main symbols

#include "SMILElement.h"

namespace System
{
namespace Web
{

class HTMLEXT SMILSeqElement : 

	public SMILElement,
//	public ElementTimeContainerImpl,//<SMILSeqElement>,
	public SVGTestsImpl<SMILSeqElement>,

//	public IElementSequentialTimeContainer,

	public CNotifyGetImpl<SMILSeqElement>,
	public CNotifySendImpl<SMILSeqElement>
{
public:
	typedef ElementTimeContainerImpl/*<SMILSeqElement>*/ timeBase;

	SMILSeqElement(NamedNodeMap* attributes);

	ElementTimeContainerImpl* m_timeContainerImpl;

	double GetIntrinsicDuration()
	{
		String tagName = get_tagName();

		if (tagName == L"body")
			return INDEFINITE;
		else
			return m_timeContainerImpl->GetIntrinsicDuration();
	}

	virtual void seekElement(double seekTo);

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

#endif //__LSMILSEQELEMENT_H_
