#ifndef Web_SVGDocument_h
#define Web_SVGDocument_h

namespace System
{
namespace Web
{

class SVGEXT SVGDocument : 
	public Document,
	public EventTarget,
	public DocumentEvent,
	public IDocumentCSS,
//	public DocumentViewImpl<SVGDocument>,
	public DocumentRangeImpl<SVGDocument>,
//	public DocumentCSSImpl<SVGDocument>,
	public XPath::XPathEvaluator,

	public DocumentASImpl<SVGDocument>,
	public DocumentEditVALImpl<SVGDocument>,

	public CNotifyGetImpl<SVGDocument>,
	public CNotifySendImpl<SVGDocument>
{
public:
	CTOR SVGDocument();
	~SVGDocument();

	SVGSVGElement* get_rootElement();

	String get_namespaceURI();
// Document
#if 0
	STDMETHOD(createElementNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR qualifiedName, /*[out,retval]*/ ILDOMElement** ppElement)
	{
		if (namespaceURI == NULL || wcslen(namespaceURI) == 0)
			return CLDOMDocumentImpl<SVGDocument>::createElementNS(L"http://www.w3.org/2000/svg", qualifiedName, ppElement);
		else
			return CLDOMDocumentImpl<SVGDocument>::createElementNS(namespaceURI, qualifiedName, ppElement);
	}
	STDMETHOD(createElementNS)(/*[in]*/ VARIANT namespaceURI, /*[in]*/ BSTR qualifiedName, /*[out,retval]*/ ILDOMElement** ppElement)
	{
		return CLDOMDocumentImpl<T>::createElementNS(namespaceURI, qualifiedName, ppElement);
	}
#endif

	Style::IStyleSheetList* get_styleSheets()	// IDocumentStyle
	{
		return Document::get_styleSheets();
	}

	virtual Style::ICSSStyleDeclaration* getOverrideStyle(Element* elt, StringIn pseudoElt)	// IDocumentCSS
	{
		return Document::getOverrideStyle(elt, pseudoElt);
	}

	static ImmutableString<WCHAR> s_namespaceURI;
};

}	// Web
}

#endif // Web_SVGDocument_h
