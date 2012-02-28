// LSVGDocument.h : Declaration of the CLSVGDocument

#ifndef __LSVGDOCUMENT_H_
#define __LSVGDOCUMENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLSVGDocument
class ATL_NO_VTABLE CLSVGDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLSVGDocument, &CLSID_LSVGDocument>,
	public ILSVGDocument
{
public:
	CLSVGDocument()
	{
		m_pDocument = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;
		
		hr = CoCreateInstance (CLSID_LDOMDocument, GetControllingUnknown(), CLSCTX_INPROC_SERVER, IID_IUnknown, (void **) &m_pDocument);
		if (FAILED (hr)) return E_NOINTERFACE;
/*
		m_all.CoCreateInstance(CLSID_MMSXHTMLCollection);
		m_scripts.CoCreateInstance(CLSID_MMSXHTMLCollection);
		m_objects.CoCreateInstance(CLSID_MMSXHTMLCollection);
*/
//		m_viewCSS.CoCreateInstance(L"LCSS.LDOMViewCSS"/*CLSID_DOMViewCSS*/);
//		m_viewCSS->put_document(this);
/*
		m_styleSheets.CoCreateInstance(CLSID_StyleSheetList);

		CComQIPtr<IDOMDocumentView> docview;
		QueryInterface(IID_IDOMDocumentView, (void**)&docview);
		m_viewCSS->put_document(docview);
*/

//		CLDocumentStyleImpl::FinalConstruct();

		return S_OK;
	}

	void FinalRelease()
	{
//		CLDocumentStyleImpl::FinalRelease();

		if (m_pDocument != NULL)
			m_pDocument->Release();
	}

	IUnknown* m_pDocument;

DECLARE_REGISTRY_RESOURCEID(IDR_LSVGDOCUMENT)
DECLARE_GET_CONTROLLING_UNKNOWN()
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSVGDocument)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMDocument)
	COM_INTERFACE_ENTRY(ILSVGDocument)
END_COM_MAP()

// ILSVGDocument
public:
// ILDOMNode
	STDMETHOD(get_nodeType)(LDOMNodeType* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->get_nodeType(pVal);
	}
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->get_textContent(pVal);
	}
	STDMETHOD(put_textContent)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->put_textContent(newVal);
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->get_uniqID(pVal);
	}
	STDMETHOD(put_uniqID)(/*[in]*/ GUID newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->put_uniqID(newVal);
	}
	STDMETHOD(getWhiteSpace)(/*[in]*/ long which, /*[out,retval]*/ BSTR* whitespace)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->getWhiteSpace(which, whitespace);
	}
	STDMETHOD(setWhiteSpace)(/*[in]*/ long which, /*[in]*/ BSTR whitespace)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->setWhiteSpace(which, whitespace);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->get_localName(pVal);
	}
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->put_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->get_prefix(pVal);
	}
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->put_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		*pVal = SysAllocString(L"http://www.w3.org/2000/svg");
		return S_OK;
	}
	STDMETHOD(put_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		ATLASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_nodeName(pVal);
	}
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->put_nodeName(newVal);
	}
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_childNodes(pVal);
	}
	STDMETHOD(GetNProp)(/*[in]*/ BSTR name, /*[out,retval]*/ DWORD* dwdata)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->GetNProp(name, dwdata);
	}
	STDMETHOD(SetNProp)(/*[in]*/ BSTR name, /*[in]*/ DWORD dwdata)
	{
		CComQIPtr<ILDOMNode> pElement = m_pDocument;
		return pElement->SetNProp(name, dwdata);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_attributes(pVal);
	}
	STDMETHOD(put_attributes)(/*[in]*/ ILDOMNamedNodeMap* newVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->put_attributes(newVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ VARIANT_BOOL deep, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->cloneNode(deep, ppResult);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(get_parentNode)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_parentNode(pVal);
	}
	STDMETHOD(put_parentNode)(ILDOMNode* pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->put_parentNode(pVal);
	}
	STDMETHOD(get_firstChild)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_firstChild(pVal);
	}
	STDMETHOD(get_lastChild)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_lastChild(pVal);
	}
	STDMETHOD(get_nextSibling)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_nextSibling(pVal);
	}
	STDMETHOD(get_previousSibling)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->get_previousSibling(pVal);
	}
	STDMETHOD(appendChild)(ILDOMNode * newChild, ILDOMNode * * result)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->appendChild(newChild, result);
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->getTextOffset(which, offset);
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->put_previousSibling(pVal);
	}
	STDMETHOD(put_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		CComQIPtr<ILDOMDocument> pElement;
		m_pDocument->QueryInterface(&pElement);
		return pElement->put_nextSibling(pVal);
	}
	STDMETHOD(get_ownerDocument)(ILDOMDocument * * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement;
		m_pDocument->QueryInterface(&pElement);
		return pElement->get_ownerDocument(pVal);
	}
	STDMETHOD(put_ownerDocument)(ILDOMDocument * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement;
		m_pDocument->QueryInterface(&pElement);
		return pElement->put_ownerDocument(pVal);
	}
// ILDOMDocument
//	STDMETHOD(load)(/*[in]*/ BSTR url, /*[out,retval]*/ VARIANT_BOOL* success);
//	STDMETHOD(createEvent)(/*[in]*/ BSTR name, /*[out,retval]*/ IDOMEvent** ppVal);
#if 0
	STDMETHOD(get_documentContainer)(/*[out, retval]*/ IDOMDocumentContainer* *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_documentContainer(pVal);
	}
	STDMETHOD(put_documentContainer)(/*[in]*/ IDOMDocumentContainer* newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_documentContainer(newVal);
	}
#endif
	STDMETHOD(load)(/*[in]*/ BSTR url, /*[out,retval]*/ VARIANT_BOOL* success)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->load(url, success);
	}
	STDMETHOD(getElementById)(/*[in]*/ BSTR elementId, /*[out,retval]*/ ILDOMElement** pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->getElementById(elementId, pVal);
	}
	STDMETHOD(createDocumentFragment)(/*[out,retval]*/ ILDOMDocumentFragment** pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->createDocumentFragment(pVal);
	}
	STDMETHOD(createElement)(/*[in]*/ BSTR tagName, /*[out,retval]*/ ILDOMElement** ppElement)
	{
//		CComQIPtr<ILDOMDocument> pElement;
//		m_pDocument->QueryInterface(&pElement);
		return createElementNS(NULL, tagName, ppElement);
	}
	STDMETHOD(createElementNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR qualifiedName, /*[out,retval]*/ ILDOMElement** ppElement)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		if (namespaceURI == NULL || wcslen(namespaceURI) == 0)
			return document->createElementNS(L"http://www.w3.org/2000/svg", qualifiedName, ppElement);
		else
			return document->createElementNS(namespaceURI, qualifiedName, ppElement);
	}
	STDMETHOD(createTextNode)(/*[in]*/ BSTR data, /*[out,retval]*/ ILDOMText** ppText)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->createTextNode(data, ppText);
	}
	STDMETHOD(createCDATASection)(/*[in]*/ BSTR data, /*[out,retval]*/ ILDOMCDATASection** pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->createCDATASection(data, pVal);
	}
	STDMETHOD(createComment)(/*[in]*/ BSTR data, /*[out,retval]*/ ILDOMComment** pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->createComment(data, pVal);
	}
	STDMETHOD(createAttributeNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR qualifiedName, /*[out,retval]*/ ILDOMAttr** ppAttr)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->createAttributeNS(namespaceURI, qualifiedName, ppAttr);
	}
	STDMETHOD(createAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ ILDOMAttr** ppAttr)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->createAttribute(name, ppAttr);
	}
	STDMETHOD(get_doctype)(/*[out, retval]*/ ILDOMDocumentType* *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_doctype(pVal);
	}
	STDMETHOD(put_doctype)(/*[in]*/ ILDOMDocumentType* newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_doctype(newVal);
	}
	STDMETHOD(saveXML)(/*[in]*/ ILDOMNode* node, /*[out,retval]*/ BSTR* pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->saveXML(node, pVal);
	}
	STDMETHOD(get_Version)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_Version(pVal);
	}
	STDMETHOD(put_Version)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_Version(newVal);
	}
	STDMETHOD(get_standalone)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_standalone(pVal);
	}
	STDMETHOD(put_standalone)(/*[in]*/ VARIANT_BOOL newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_standalone(newVal);
	}
	STDMETHOD(get_actualEncoding)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_actualEncoding(pVal);
	}
	STDMETHOD(put_actualEncoding)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_actualEncoding(newVal);
	}
	STDMETHOD(get_encoding)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_encoding(pVal);
	}
	STDMETHOD(put_encoding)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_encoding(newVal);
	}
	STDMETHOD(get_implementation)(/*[out, retval]*/ ILDOMImplementation* *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_implementation(pVal);
	}
	STDMETHOD(put_implementation)(/*[in]*/ ILDOMImplementation* newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_implementation(newVal);
	}
	STDMETHOD(get_url)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->get_url(pVal);
	}
	STDMETHOD(put_url)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMDocument> document = m_pDocument;
		return document->put_url(newVal);
	}
	STDMETHOD(get_async)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->get_async(pVal);
	}
	STDMETHOD(put_async)(/*[in]*/ VARIANT_BOOL newVal)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->put_async(newVal);
	}
	STDMETHOD(loadXML)(/*[in]*/ BSTR data, /*[out,retval]*/ VARIANT_BOOL* success)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->loadXML(data, success);
	}
	STDMETHOD(save)(/*[in]*/ BSTR url, /*[out,retval]*/ VARIANT_BOOL* success)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->save(url, success);
	}
	STDMETHOD(get_documentElement)(ILDOMElement * * pVal)
	{
		CComQIPtr<ILDOMDocument> pDocument = m_pDocument;
		return pDocument->get_documentElement(pVal);
	}
	STDMETHOD(put_documentElement)(ILDOMElement * pVal)
	{
		CComQIPtr<ILDOMDocument> pElement = m_pDocument;
		return pElement->put_documentElement(pVal);
	}
#if 0
// ILDOMDocumentView
	STDMETHOD(get_defaultView)(/*[out, retval]*/ ILDOMAbstractView* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		(*pVal = this)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_defaultView)(/*[in]*/ ILDOMAbstractView* newVal)
	{
		ATLASSERT(0);
		return S_OK;
	}
#endif
};

#endif //__LSVGDOCUMENT_H_
