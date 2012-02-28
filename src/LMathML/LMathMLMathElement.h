// LMathMLMathElement.h : Declaration of the CLMathMLMathElement

#ifndef __LMATHMLMATHELEMENT_H_
#define __LMATHMLMATHELEMENT_H_

//#include "resource.h"       // main symbols

#include "LMathMLElementImpl.h"
//#include "LElementEditASImpl.h"
#include "LElementEditVALImpl.h"
#include "LElementCSSInlineStyleImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLMathElement
class ATL_NO_VTABLE CLMathMLMathElement : 
	public CComObjectRootEx<CComMultiThreadModel>,

	public CLMathMLElementImpl<CLMathMLMathElement>,
//	public CLElementCSSInlineStyleImpl<CLMathMLMathElement>,
//	public CLElementEditASImpl<CLMathMLMathElement>,
	public CLElementEditVALImpl<CLMathMLMathElement>,

	public ILMathMLMathElement,
	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<CLMathMLMathElement>,
	public CNotifySendImpl<CLMathMLMathElement>
{
public:

typedef CLMathMLMathElement T;

	CLMathMLMathElement()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLMathMLElementImpl<CLMathMLMathElement>::FinalConstruct();
		if (FAILED(hr)) return hr;

		//hr = CLElementCSSInlineStyleImpl<CLMathMLMathElement>::FinalConstruct();
		//if (FAILED(hr)) return hr;

		return S_OK;
	}

	void FinalRelease()
	{
		//CLElementCSSInlineStyleImpl<CLMathMLMathElement>::FinalRelease();
		CLMathMLElementImpl<CLMathMLMathElement>::FinalRelease();
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_LMathMLMathElement)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLMathMLMathElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILMathMLElement)
	COM_INTERFACE_ENTRY(ILMathMLMathElement)
//	COM_INTERFACE_ENTRY(ILElementCSSInlineStyle)

	COM_INTERFACE_ENTRY(ILDOMEventTarget)
// AS/VAL
	COM_INTERFACE_ENTRY(ILNodeEditAS)
	COM_INTERFACE_ENTRY(ILElementEditAS)
	COM_INTERFACE_ENTRY(ILNodeEditVAL)
//
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
	//	if (m_fireReentrance == 0)
	//	{
	//		m_fireReentrance++;

			FireOnChanged(type, targetObject, dispID);

	//		m_fireReentrance--;
	//	}

		return S_OK;
	}

// ILMathMLMathElement
public:
	STDMETHOD(get_macros)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_macros)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_display)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_display)(/*[in]*/ BSTR newVal);

//	STDMETHOD_LNodeEditVAL(CLMathMLMathElement)
//	STDMETHOD_LElementEditVAL(CLMathMLMathElement)

// ILDOMNode
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		return CLMathMLElementImpl<T>::get_childNodes(pVal);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_localName(pVal);
	}
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_prefix(pVal);
	}
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_namespaceURI(pVal);
	}
	STDMETHOD(put_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_namespaceURI(newVal);
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_nodeName(pVal);
	}
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_nodeName(newVal);
	}
	STDMETHOD(get_nodeValue)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_nodeValue(pVal);
	}
	STDMETHOD(put_nodeValue)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_nodeValue(newVal);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		return CLMathMLElementImpl<T>::get_attributes(pVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<T>::isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<T>::hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ VARIANT_BOOL deep, /*[out,retval]*/ ILDOMNode** pVal)
	{
		return CLMathMLElementImpl<T>::cloneNode(deep, pVal);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<T>::hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<T>::replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<T>::removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ VARIANT refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<T>::insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(appendChild)(/*[in]*/ ILDOMNode* newChild, /*[out,retval]*/ ILDOMNode** result)
	{
		return CLMathMLElementImpl<T>::appendChild(newChild, result);
	}
	STDMETHOD(get_ownerDocument)(/*[out, retval]*/ ILDOMDocument* *pVal)
	{
		return CLMathMLElementImpl<T>::get_ownerDocument(pVal);
	}
	STDMETHOD(put_ownerDocument)(/*[in]*/ ILDOMDocument* newVal)
	{
		return CLMathMLElementImpl<T>::put_ownerDocument(newVal);
	}
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<T>::get_previousSibling(pVal);
	}
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ ILDOMNode **pVal)
	{
		return CLMathMLElementImpl<T>::get_nextSibling(pVal);
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLMathMLElementImpl<T>::put_previousSibling(pVal);
	}
	STDMETHOD(put_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLMathMLElementImpl<T>::put_nextSibling(pVal);
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<T>::get_lastChild(pVal);
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<T>::get_firstChild(pVal);
	}
	STDMETHOD(get_parentNode)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<T>::get_parentNode(pVal);
	}
	STDMETHOD(put_parentNode)(/*[in]*/ ILDOMNode* pVal)
	{
		return CLMathMLElementImpl<T>::put_parentNode(pVal);
	}
	STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType* pVal)
	{
		return CLMathMLElementImpl<T>::get_nodeType(pVal);
	}
	STDMETHOD(normalize)()
	{
		return CLMathMLElementImpl<T>::normalize();
	}
	STDMETHOD(lookupPrefix)(/*[in]*/ BSTR namespaceURI, /*[out,retval]*/ BSTR* pVal)
	{
		return CLMathMLElementImpl<T>::lookupPrefix(namespaceURI, pVal);
	}
	STDMETHOD(lookupNamespaceURI)(/*[in]*/ BSTR prefix, /*[out,retval]*/ BSTR* pVal)
	{
		return CLMathMLElementImpl<T>::lookupNamespaceURI(prefix, pVal);
	}
	STDMETHOD(setUserData)(/*[in]*/ BSTR key, /*[in]*/ LDOMUserData data, /*[in]*/ ILDOMUserDataHandler* handler, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLMathMLElementImpl<T>::setUserData(key, data, handler, pVal);
	}
	STDMETHOD(getUserData)(/*[in]*/ BSTR key, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLMathMLElementImpl<T>::getUserData(key, pVal);
	}
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_textContent(pVal);
	}
	STDMETHOD(put_textContent)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_textContent(newVal);
	}
	STDMETHOD(removeChildren)()
	{
		return CLMathMLElementImpl<T>::removeChildren();
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		return CLMathMLElementImpl<T>::get_uniqID(pVal);
	}
	STDMETHOD(put_uniqID)(/*[in]*/ GUID newVal)
	{
		return CLMathMLElementImpl<T>::put_uniqID(newVal);
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		return CLMathMLElementImpl<T>::setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		return CLMathMLElementImpl<T>::getTextOffset(which, offset);
	}
	STDMETHOD(getFirstChild)(ILDOMNode* *pVal)
	{
		return get_firstChild(pVal);
	}
	STDMETHOD(getLastChild)(ILDOMNode* *pVal)
	{
		return get_lastChild(pVal);
	}
// ILDOMElement
	STDMETHODIMP get_tagName(BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_tagName(pVal);
	}
	STDMETHODIMP put_tagName(BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_tagName(newVal);
	}
	STDMETHODIMP setAttributeNode(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<T>::setAttributeNode(newAttr, pVal);
	}
	STDMETHODIMP setAttributeNodeNS(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<T>::setAttributeNodeNS(newAttr, pVal);
	}
	STDMETHODIMP removeAttribute(BSTR name)
	{
		return CLMathMLElementImpl<T>::removeAttribute(name);
	}
	STDMETHODIMP removeAttributeNS(BSTR namespaceURI, BSTR localName)
	{
		return CLMathMLElementImpl<T>::removeAttributeNS(namespaceURI, localName);
	}
	STDMETHODIMP setAttribute(BSTR name, BSTR value)
	{
		return CLMathMLElementImpl<T>::setAttribute(name, value);
	}
	STDMETHODIMP setAttributeNS(BSTR namespaceURI, BSTR qualifiedName, BSTR value)
	{
		return CLMathMLElementImpl<T>::setAttributeNS(namespaceURI, qualifiedName, value);
	}
	STDMETHODIMP getAttribute(BSTR name, BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::getAttribute(name, pVal);
	}
	STDMETHODIMP getAttributeNS(BSTR namespaceURI, BSTR localName, BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::getAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getAttributeNode(BSTR name, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<T>::getAttributeNode(name, pVal);
	}
	STDMETHODIMP getAttributeNodeNS(BSTR qualifiedName, BSTR localName, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<T>::getAttributeNodeNS(qualifiedName, localName, pVal);
	}
	STDMETHOD(removeAttributeNode)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLMathMLElementImpl<T>::removeAttributeNode(oldAttr, pVal);
	}
	STDMETHOD(removeAttributeNodeNS)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLMathMLElementImpl<T>::removeAttributeNodeNS(oldAttr, pVal);
	}
	STDMETHOD(hasAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<T>::hasAttribute(name, pVal);
	}
	STDMETHOD (hasAttributeNS)(/*[in]*/ BSTR namespaceURI,  /*[in]*/ BSTR localName, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<T>::hasAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getElementsByTagName(/*[in]*/ BSTR tagName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLMathMLElementImpl<T>::getElementsByTagName(tagName, pVal);
	}
	STDMETHODIMP getElementsByTagNameNS(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR localName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLMathMLElementImpl<T>::getElementsByTagNameNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP get_markupContent(/*[out,retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_markupContent(pVal);
	}
	STDMETHODIMP put_markupContent(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_markupContent(newVal);
	}
	STDMETHODIMP setActive()
	{
		return CLMathMLElementImpl<T>::setActive();
	}
	STDMETHOD(addBehavior)(/*[in]*/ BSTR bstrUrl, /*[in]*/ VARIANT* pvarFactory, /*[out,retval]*/ long *pCookie)
	{
		return CLMathMLElementImpl<T>::addBehavior(bstrUrl, pvarFactory, pCookie);
	}
// ILMathMLElement
	STDMETHODIMP put_className(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_className(newVal);
	}
	STDMETHODIMP get_className(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_className(pVal);
	}
	STDMETHODIMP put_mathElementStyle(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_mathElementStyle(newVal);
	}
	STDMETHODIMP get_mathElementStyle(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_mathElementStyle(pVal);
	}
	STDMETHODIMP put__id(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put__id(newVal);
	}
	STDMETHODIMP get__id(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get__id(pVal);
	}
	STDMETHODIMP put_xref(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_xref(newVal);
	}
	STDMETHODIMP get_xref(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_xref(pVal);
	}
	STDMETHODIMP put_href(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<T>::put_href(newVal);
	}
	STDMETHODIMP get_href(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<T>::get_href(pVal);
	}
	STDMETHODIMP get_ownerMathElement(/*[out, retval]*/ ILMathMLMathElement* *pVal)
	{
		return CLMathMLElementImpl<T>::get_ownerMathElement(pVal);
	}
// ILNodeEditVAL
	STDMETHOD(get_defaultValue)(/*[out,retval]*/ BSTR *pVal)
	{
		return CLElementEditVALImpl<T>::get_defaultValue(pVal);
	}
	STDMETHOD(get_enumeratedValues)(/*[out,retval]*/ ILDOMStringList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_enumeratedValues(pVal);
	}
	STDMETHOD(isNodeValid)(/*[in]*/ VARIANT_BOOL deep, /*[in]*/ CheckTypeVAL wFValidityCheckLevel, /*[out,retval]*/ VARIANT_BOOL *pVal)
	{
		return CLElementEditVALImpl<T>::isNodeValid(deep, wFValidityCheckLevel, pVal);
	}
// ILElementEditVAL
	STDMETHOD(get_allowedChildren)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_allowedChildren(pVal);
	}
	STDMETHOD(get_allowedParents)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_allowedParents(pVal);
	}
	STDMETHOD(get_allowedNextSiblings)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_allowedNextSiblings(pVal);
	}
	STDMETHOD(get_allowedPreviousSiblings)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_allowedPreviousSiblings(pVal);
	}
	STDMETHOD(get_allowedAttributes)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_allowedAttributes(pVal);
	}
	STDMETHOD(get_requiredAttributes)(/*[out,retval]*/ ILDOMNameList* *pVal)
	{
		return CLElementEditVALImpl<T>::get_requiredAttributes(pVal);
	}
};

#endif //__LMATHMLMATHELEMENT_H_
