#ifndef __LNITFDOCUMENT_H_
#define __LNITFDOCUMENT_H_

namespace System
{
namespace Web
{

class NITFDocument : 
	public Document,
	public EventTarget,
//	public DocumentViewImpl<NITFDocument>,
	public DocumentEvent,
	public DocumentRangeImpl<NITFDocument>,
	//public DocumentCSSImpl<NITFDocument>,
	public DocumentASImpl<NITFDocument>,
	public DocumentEditVALImpl<NITFDocument>,

	public CNotifyGetImpl<NITFDocument>,
	public CNotifySendImpl<NITFDocument>
{
public:
	CTOR NITFDocument()
	{
	}

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

public:
	String get_title();
	void set_title(StringIn newVal);
// ILDOMNode
	String get_namespaceURI()
	{
		return WSTR("http://www.iptc.org/nitf");
	}
// ILDOMDocument
	Element* createElementNS(System::StringW* namespaceURI, System::StringW* qualifiedName)
	{
		ASSERT(0);
		return NULL;
#if 0
	//	CComQIPtr<ILDOMDocument> document = m_pDocument;
		if (namespaceURI == NULL || wcslen(namespaceURI) == 0)
			return CLDOMDocumentImpl<CLNITFDocument>::createElementNS(L"http://www.iptc.org/nitf", qualifiedName, ppElement);
		else
			return CLDOMDocumentImpl<CLNITFDocument>::createElementNS(namespaceURI, qualifiedName, ppElement);
#endif
	}
};

}	// Web
}

#endif //__LNITFDOCUMENT_H_
