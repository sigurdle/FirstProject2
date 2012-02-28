#ifndef Web_VIEWCSS_H
#define Web_VIEWCSS_H

namespace System
{
namespace Style
{

//class DocumentView;

/*
class XMLEXT AbstractView : public System::Object
{
public:
	CTOR AbstractView()
	{
		m_document = NULL;
	}

	DocumentView* get_document()
	{
		return m_document;
	}

	DocumentView* m_document;
};
*/

	/*
class StyleDeclarationMatch : public Object
{
public:
	CTOR StyleDeclarationMatch()
	{
		m_selector = NULL;
		m_declaration = NULL;
	}

	uint GetSpecificity();

	Selector* m_selector;
	IStyleDeclaration* m_declaration;
};
*/

enum
{
	Value_Specified,
	Value_Inherited,
	Value_Default,
};

class CSSEXT CSSElementMatches : public Object
{
public:

	CTOR CSSElementMatches()
	{
		m_pseudoElementName = nullptr;
	}

	String m_pseudoElementName;
	ICSSElementResolver* m_elementResolver;
	vector<SingleSelectorRule*> m_rules;

//	void GetStyleSheetMatches(ICSSStyleSheet* styleSheet, ICSSElementResolver* pPElement);

	int GetSpecifiedPropertyValue2(Object* pProperty, bool bIncludeOverride, Variant* value);
};

class CSSEXT ViewCSS// : public AbstractView
{
public:
//	bool m_isXML;	// TODO remove

//	DWORD SelectorMatches(ILDOMElement* element, CSSSelector* selector);
//	ILDOMElement* GetAncestorElement(ILDOMElement* element, CSSSelector* selector, DWORD specificity);
//	DWORD RuleMatches(ILDOMElement* element, CLCSSStyleRule* pRule, BSTR propertyName);
//	void GetStyleSheetDecls(ILCSSStyleSheet* styleSheet, ILDOMElement* element, BSTR propertyName, CArray<CDecl,CDecl&>& decls);

	static CSSElementMatches* GetDeclMatches(IDocumentStyle* documentStyle, ICSSElementResolver* pPElement);

//	int GetSpecifiedPropertyValue(ILDocumentStyle* documentStyle, CPElementBase* pElement, int propertyIndex, CSStyle* cssstyle, ILCSSValue** value, BOOL bIncludeOverride);
	static int GetSpecifiedPropertyValue2(IDocumentStyle* documentStyle, /*ICSSElementResolver* pElement*/ CSSElementMatches* matches, int propertyIndex, bool bIncludeOverride, CSSValue** value);
//	int GetComputedPropertyValue(ILDocumentStyle* documentStyle, CPElementBase* pElement, int propertyIndex, CSStyle* cssstyle, ILCSSValue** value);

//	virtual ICSSStyleDeclaration* getComputedStyle(w3c::Element *elt, System::StringW* pseudoElt);
};

#if 0

class XMLEXT CLViewCSSImplImpl : 
	public ILViewCSS
{
public:
	CLViewCSSImplImpl()
	{
		m_isXML = VARIANT_TRUE;	// TODO remove

		m_pView = NULL;
	}

	CXMLDocumentView* m_pView;


// ILViewCSS
public:
	STDMETHOD(getComputedStyle)(/*[in]*/ ILDOMElement* elt, /*[in]*/ BSTR pseudoElt, /*[out,retval]*/ ILCSSStyleDeclaration** ppResult);
	STDMETHOD(getOverrideStyle)(/*[in]*/ ILDOMElement* elt, /*[in]*/ BSTR pseudoElt, /*[out, retval]*/ ILCSSStyleDeclaration* *pVal);
	STDMETHOD(GetPresentation)(/*[out, retval]*/ ILPresentation* *pVal);
};

class XMLEXT CLViewCSS :
	public CLViewCSSImplImpl
{
public:
// IDOMAbstractView
	STDMETHOD(get_document)(ILDOMDocumentView* *pVal)
	{
		ASSERT(0);
		/*
		CComPtr<ILDOMDocument> document;
		return static_cast<T*>(this)->m_pFrame->m_frameElement->get_contentDocument(&document);

		document->QueryInterface(IID_ILDOMDocumentView, (void**)pVal);
		*/
		return S_OK;
	}
};

template <class T> class CLViewCSSImpl :
	public CLViewCSSImplImpl
{
public:
// IDOMAbstractView
	STDMETHOD(get_document)(ILDOMDocumentView* *pVal)
	{
		ASSERT(0);
		/*
		CComPtr<ILDOMDocument> document;
		return static_cast<T*>(this)->m_pFrame->m_frameElement->get_contentDocument(&document);

		document->QueryInterface(IID_ILDOMDocumentView, (void**)pVal);
		*/
		return S_OK;
	}
};
#endif

}	// Web
}

#endif // Web_VIEWCSS_H
