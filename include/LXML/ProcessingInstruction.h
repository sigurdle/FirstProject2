#ifndef Web_ProcessingInstruction_h
#define Web_ProcessingInstruction_h

//#include "resource.h"       // main symbols

#include "Node.h"
#include "DOMEventTargetImpl.h"

namespace System
{
namespace Web
{

class WEBEXT ProcessingInstruction : 
	public ChildNode,
	public EventTarget

//	protected CNotifyGetImpl<ProcessingInstruction>,
//	protected CNotifySendImpl<ProcessingInstruction>
{
public:
	CTOR ProcessingInstruction();
	CTOR ProcessingInstruction(StringIn target);

	String get_data() const;
	void set_data(StringIn newVal);
	String get_target() const;
	NodeType get_nodeType() const;
	Node* cloneNodeExport(Document* ownerDocument, bool deep) const;

protected:

	String m_target;

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

	String m_data;
};

}	// Web
}

#endif // Web_ProcessingInstruction_h
