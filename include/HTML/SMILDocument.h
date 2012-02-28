#ifndef Web_SMILDocument_h
#define Web_SMILDocument_h

namespace System
{
namespace Web
{

class HTMLEXT SMILDocument : 
	public Document,
	public EventTarget,
	public DocumentEvent,
//	public DocumentViewImpl<SMILDocument>,
	public DocumentASImpl<SMILDocument>,
	public DocumentEditVALImpl<SMILDocument>,
	//public DocumentCSSImpl<SMILDocument>,
	public XPath::XPathEvaluator,

//	public CLElementTimeContainerImpl<SMILDocument, ILElementSequentialTimeContainer>,
//	public ILSMILDocument,
	public IElementSequentialTimeContainer,
	public IDocumentEditVAL,

	protected CNotifyGetImpl<SMILDocument>,
	protected CNotifySendImpl<SMILDocument>
{
public:
	CTOR SMILDocument();

	String get_namespaceURI();

	void seekElement(double seekTo);

	double get_simpleTime()
	{
		if (m_documentElement)
		{
			Element* body = GetElementByTagName(m_documentElement, WSTR("body"), false);
			if (body)
			{
				ASSERT(0);
				/*
				CComQIPtr<ILElementTime> bodyTime = body;

				return bodyTime->get_simpleTime();
				*/
			}
		}
		return 0;
	}

	double get_activeTime()
	{
		if (m_documentElement)
		{
			Web::Element* body = GetElementByTagName(m_documentElement, WSTR("body"), false);
			if (body)
			{
				ASSERT(0);
				/*
				CComQIPtr<ILElementTime> bodyTime = body;

				return bodyTime->get_activeTime();
				*/
			}
		}
		return 0;
	}

// IElementTimeContainer
	String get_timeContainer()
	{
		return WSTR("seq");
	}

protected:

	Web::NodeList* m_activeChildren;	// TODO, am I using this?

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}	// Web
}

#endif // Web_SMILDocument_h
