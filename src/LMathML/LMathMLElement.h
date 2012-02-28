// LMathMLElement.h : Declaration of the CLMathMLElement

#ifndef __LMATHMLELEMENT_H_
#define __LMATHMLELEMENT_H_

//#include "resource.h"       // main symbols

#include "LMathMLElementImpl.h"
//#include "LElementEditASImpl.h"
#include "LElementEditVALImpl.h"
#include "LElementCSSInlineStyleImpl.h"

#include "AnimationTarget.h"

/////////////////////////////////////////////////////////////////////////////
// CLMathMLElement
class ATL_NO_VTABLE CLMathMLElement : 
	public CComObjectRootEx<CComMultiThreadModel>,

	public CLMathMLElementImpl<CLMathMLElement>,
//	public CLElementCSSInlineStyleImpl<CLMathMLElement>,
//	public CLElementEditASImpl<CLMathMLElement>,
	public CLElementEditVALImpl<CLMathMLElement>,

	public ILMathMLElement,
	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<CLMathMLElement>,
	public CNotifySendImpl<CLMathMLElement>
{
public:
	typedef CLMathMLElement T;

	CLMathMLElement()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLMathMLElementImpl<CLMathMLElement>::FinalConstruct();
		if (FAILED(hr)) return hr;

		//hr = CLElementCSSInlineStyleImpl<CLMathMLElement>::FinalConstruct();
		//if (FAILED(hr)) return hr;

		return S_OK;
	}

	void FinalRelease()
	{
		//CLElementCSSInlineStyleImpl<CLMathMLElement>::FinalRelease();
		CLMathMLElementImpl<CLMathMLElement>::FinalRelease();
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_LMathMLElement)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLMathMLElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILMathMLElement)
//	COM_INTERFACE_ENTRY(ILElementCSSInlineStyle)
	COM_INTERFACE_ENTRY(ILDOMEventTarget)
// AS/VAL
	COM_INTERFACE_ENTRY(ILNodeEditAS)
	COM_INTERFACE_ENTRY(ILElementEditAS)
	COM_INTERFACE_ENTRY(ILNodeEditVAL)
	COM_INTERFACE_ENTRY(ILElementEditVAL)
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

// ILMathMLElement
public:
// ILDOMNode
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_childNodes(pVal);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_localName(pVal);
	}
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_prefix(pVal);
	}
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_namespaceURI(pVal);
	}
	STDMETHOD(put_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_namespaceURI(newVal);
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_nodeName(pVal);
	}
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_nodeName(newVal);
	}
	STDMETHOD(get_nodeValue)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_nodeValue(pVal);
	}
	STDMETHOD(put_nodeValue)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_nodeValue(newVal);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_attributes(pVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ VARIANT_BOOL deep, /*[out,retval]*/ ILDOMNode** pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::cloneNode(deep, pVal);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<CLMathMLElement>::replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ VARIANT refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLMathMLElementImpl<CLMathMLElement>::insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(appendChild)(/*[in]*/ ILDOMNode* newChild, /*[out,retval]*/ ILDOMNode** result)
	{
		return CLMathMLElementImpl<CLMathMLElement>::appendChild(newChild, result);
	}
	STDMETHOD(get_ownerDocument)(/*[out, retval]*/ ILDOMDocument* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_ownerDocument(pVal);
	}
	STDMETHOD(put_ownerDocument)(/*[in]*/ ILDOMDocument* newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_ownerDocument(newVal);
	}
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_previousSibling(pVal);
	}
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ ILDOMNode **pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_nextSibling(pVal);
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_previousSibling(pVal);
	}
	STDMETHOD(put_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_nextSibling(pVal);
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_lastChild(pVal);
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_firstChild(pVal);
	}
	STDMETHOD(get_parentNode)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_parentNode(pVal);
	}
	STDMETHOD(put_parentNode)(/*[in]*/ ILDOMNode* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_parentNode(pVal);
	}
	STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_nodeType(pVal);
	}
	STDMETHOD(normalize)()
	{
		return CLMathMLElementImpl<CLMathMLElement>::normalize();
	}
	STDMETHOD(lookupPrefix)(/*[in]*/ BSTR namespaceURI, /*[out,retval]*/ BSTR* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::lookupPrefix(namespaceURI, pVal);
	}
	STDMETHOD(lookupNamespaceURI)(/*[in]*/ BSTR prefix, /*[out,retval]*/ BSTR* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::lookupNamespaceURI(prefix, pVal);
	}
	STDMETHOD(setUserData)(/*[in]*/ BSTR key, /*[in]*/ LDOMUserData data, /*[in]*/ ILDOMUserDataHandler* handler, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setUserData(key, data, handler, pVal);
	}
	STDMETHOD(getUserData)(/*[in]*/ BSTR key, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getUserData(key, pVal);
	}
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_textContent(pVal);
	}
	STDMETHOD(put_textContent)(/*[in]*/ BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_textContent(newVal);
	}
	STDMETHOD(removeChildren)()
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeChildren();
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::get_uniqID(pVal);
	}
	STDMETHOD(put_uniqID)(/*[in]*/ GUID newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_uniqID(newVal);
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getTextOffset(which, offset);
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
		return CLMathMLElementImpl<CLMathMLElement>::get_tagName(pVal);
	}
	STDMETHODIMP put_tagName(BSTR newVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::put_tagName(newVal);
	}
	STDMETHODIMP setAttributeNode(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setAttributeNode(newAttr, pVal);
	}
	STDMETHODIMP setAttributeNodeNS(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setAttributeNodeNS(newAttr, pVal);
	}
	STDMETHODIMP removeAttribute(BSTR name)
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeAttribute(name);
	}
	STDMETHODIMP removeAttributeNS(BSTR namespaceURI, BSTR localName)
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeAttributeNS(namespaceURI, localName);
	}
	STDMETHODIMP setAttribute(BSTR name, BSTR value)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setAttribute(name, value);
	}
	STDMETHODIMP setAttributeNS(BSTR namespaceURI, BSTR qualifiedName, BSTR value)
	{
		return CLMathMLElementImpl<CLMathMLElement>::setAttributeNS(namespaceURI, qualifiedName, value);
	}
	STDMETHODIMP getAttribute(BSTR name, BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getAttribute(name, pVal);
	}
	STDMETHODIMP getAttributeNS(BSTR namespaceURI, BSTR localName, BSTR *pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getAttributeNode(BSTR name, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getAttributeNode(name, pVal);
	}
	STDMETHODIMP getAttributeNodeNS(BSTR qualifiedName, BSTR localName, ILDOMAttr **pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::getAttributeNodeNS(qualifiedName, localName, pVal);
	}
	STDMETHOD(removeAttributeNode)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeAttributeNode(oldAttr, pVal);
	}
	STDMETHOD(removeAttributeNodeNS)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::removeAttributeNodeNS(oldAttr, pVal);
	}
	STDMETHOD(hasAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::hasAttribute(name, pVal);
	}
	STDMETHOD (hasAttributeNS)(/*[in]*/ BSTR namespaceURI,  /*[in]*/ BSTR localName, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		return CLMathMLElementImpl<CLMathMLElement>::hasAttributeNS(namespaceURI, localName, pVal);
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

#endif //__LMATHMLELEMENT_H_
