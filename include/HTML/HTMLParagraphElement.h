#ifndef w3c_HTMLParagraphElement_h
#define w3c_HTMLParagraphElement_h

namespace System
{
namespace Web
{

class HTMLEXT HTMLParagraphElement : 

	public HTMLElement,
	public ElementCSSInlineStyleImpl<HTMLParagraphElement>,
//	public CLElementEditASImpl<HTMLParagraphElement>,
	public ElementEditVALImpl<HTMLParagraphElement>,

//	public IElementEditVAL, // INodeEditVAL

	protected CNotifyGetImpl<HTMLParagraphElement>,
	protected CNotifySendImpl<HTMLParagraphElement>
{
public:
	CTOR HTMLParagraphElement(NamedNodeMap* attributes);
	~HTMLParagraphElement();

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, Object* targetObject, Object* immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

};

}	// w3c
}

#endif // w3c_HTMLParagraphElement_h
