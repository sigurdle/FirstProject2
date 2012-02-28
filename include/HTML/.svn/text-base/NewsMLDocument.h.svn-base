#ifndef __NEWSMLDOCUMENT_H_
#define __NEWSMLDOCUMENT_H_

namespace System
{
namespace Web
{

class HTMLEXT NewsMLDocument : 
	public Document,
	public EventTarget,
//	public DocumentViewImpl<NewsMLDocument>,
	public DocumentEvent,
	public DocumentRangeImpl<NewsMLDocument>,
	//public DocumentCSSImpl<NewsMLDocument>,
	public DocumentASImpl<NewsMLDocument>,
	public DocumentEditVALImpl<NewsMLDocument>,

	protected CNotifyGetImpl<NewsMLDocument>,
	protected CNotifySendImpl<NewsMLDocument>
{
public:
	CTOR NewsMLDocument()
	{
	}

public:

	String get_namespaceURI()
	{
		return WSTR(""/*L"http://www.iptc.org/nitf"*/);
	}

	Element* createElementNS(StringIn namespaceURI, StringIn qualifiedName)
	{
		ASSERT(0);
		return NULL;
#if 0
	//	CComQIPtr<ILDOMDocument> document = m_pDocument;
		if (namespaceURI == NULL || wcslen(namespaceURI) == 0)
			return CLDOMDocumentImpl<CLNewsMLDocument>::createElementNS(L""/*L"http://www.iptc.org/nitf"*/, qualifiedName, ppElement);
		else
			return CLDOMDocumentImpl<CLNewsMLDocument>::createElementNS(namespaceURI, qualifiedName, ppElement);
#endif
	}

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
};

}
}

#endif // __NEWSMLDOCUMENT_H_
