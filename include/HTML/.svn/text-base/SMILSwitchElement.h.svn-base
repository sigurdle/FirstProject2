// LSMILSwitchElement.h : Declaration of the CLSMILSwitchElement

#ifndef __LSMILSWITCHELEMENT_H_
#define __LSMILSWITCHELEMENT_H_

//#include "resource.h"       // main symbols

#include "LSMILElementImpl.h"

class CLSMILSwitchElement : 
	public CComObjectRootEx<CComSingleThreadModel>,

	public CLSMILElementImpl<CLSMILSwitchElement>,
	public CLElementEditVALImpl<CLSMILSwitchElement>,

//	public CLElementEditASImpl<CLSMILSwitchElement>,

	public ILSMILSwitchElement,
	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<CLSMILSwitchElement>,
	public CNotifySendImpl<CLSMILSwitchElement>
{
public:

	typedef CLSMILSwitchElement T;

	CTOR CLSMILSwitchElement()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLSMILElementImpl<CLSMILSwitchElement>::FinalConstruct();
		if (FAILED(hr)) return hr;

		SetAllValues(this);	// ???

		return 0;
	}

	void FinalRelease()
	{
		CLSMILElementImpl<CLSMILSwitchElement>::FinalRelease();
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSMILSwitchElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILSMILElement)
	COM_INTERFACE_ENTRY(ILSMILSwitchElement)
	COM_INTERFACE_ENTRY(ILDOMEventTarget)
	COM_INTERFACE_ENTRY(ILNodeEditAS)
	COM_INTERFACE_ENTRY(ILElementEditAS)
	COM_INTERFACE_ENTRY(ILNodeEditVAL)

//
	COM_INTERFACE_ENTRY(CLDOMNodeImplImpl)
	COM_INTERFACE_ENTRY(CLDOMElementImplImpl)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// ILSMILSwitchElement
public:

// ILDOMNode
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILElementImpl<T>::get_childNodes(pVal);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_localName(pVal);
	}
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_prefix(pVal);
	}
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_namespaceURI(pVal);
	}
	STDMETHOD(put_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_namespaceURI(newVal);
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_nodeName(pVal);
	}
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_nodeName(newVal);
	}
	STDMETHOD(get_nodeValue)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_nodeValue(pVal);
	}
	STDMETHOD(put_nodeValue)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_nodeValue(newVal);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		return CLSMILElementImpl<T>::get_attributes(pVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILElementImpl<T>::isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ bool* pVal)
	{
		return CLSMILElementImpl<T>::hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ bool deep, /*[out,retval]*/ ILDOMNode** pVal)
	{
		return CLSMILElementImpl<T>::cloneNode(deep, pVal);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ bool* pVal)
	{
		return CLSMILElementImpl<T>::hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILElementImpl<T>::replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILElementImpl<T>::removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ VARIANT refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILElementImpl<T>::insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(appendChild)(/*[in]*/ ILDOMNode* newChild, /*[out,retval]*/ ILDOMNode** result)
	{
		return CLSMILElementImpl<T>::appendChild(newChild, result);
	}
	STDMETHOD(get_ownerDocument)(/*[out, retval]*/ ILDOMDocument* *pVal)
	{
		return CLSMILElementImpl<T>::get_ownerDocument(pVal);
	}
	STDMETHOD(put_ownerDocument)(/*[in]*/ ILDOMDocument* newVal)
	{
		return CLSMILElementImpl<T>::put_ownerDocument(newVal);
	}
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILElementImpl<T>::get_previousSibling(pVal);
	}
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ ILDOMNode **pVal)
	{
		return CLSMILElementImpl<T>::get_nextSibling(pVal);
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLSMILElementImpl<T>::put_previousSibling(pVal);
	}
	STDMETHOD(put_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLSMILElementImpl<T>::put_nextSibling(pVal);
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILElementImpl<T>::get_lastChild(pVal);
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILElementImpl<T>::get_firstChild(pVal);
	}
	STDMETHOD(get_parentNode)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILElementImpl<T>::get_parentNode(pVal);
	}
	STDMETHOD(put_parentNode)(/*[in]*/ ILDOMNode* pVal)
	{
		return CLSMILElementImpl<T>::put_parentNode(pVal);
	}
	STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType* pVal)
	{
		return CLSMILElementImpl<T>::get_nodeType(pVal);
	}
	STDMETHOD(normalize)()
	{
		return CLSMILElementImpl<T>::normalize();
	}
	STDMETHOD(lookupPrefix)(/*[in]*/ BSTR namespaceURI, /*[out,retval]*/ BSTR* pVal)
	{
		return CLSMILElementImpl<T>::lookupPrefix(namespaceURI, pVal);
	}
	STDMETHOD(lookupNamespaceURI)(/*[in]*/ BSTR prefix, /*[out,retval]*/ BSTR* pVal)
	{
		return CLSMILElementImpl<T>::lookupNamespaceURI(prefix, pVal);
	}
	STDMETHOD(setUserData)(/*[in]*/ BSTR key, /*[in]*/ LDOMUserData data, /*[in]*/ ILDOMUserDataHandler* handler, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLSMILElementImpl<T>::setUserData(key, data, handler, pVal);
	}
	STDMETHOD(getUserData)(/*[in]*/ BSTR key, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLSMILElementImpl<T>::getUserData(key, pVal);
	}
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_textContent(pVal);
	}
	STDMETHOD(set_textContent)(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::set_textContent(newVal);
	}
	STDMETHOD(removeChildren)()
	{
		return CLSMILElementImpl<T>::removeChildren();
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		return CLSMILElementImpl<T>::get_uniqID(pVal);
	}
	STDMETHOD(put_uniqID)(/*[in]*/ GUID newVal)
	{
		return CLSMILElementImpl<T>::put_uniqID(newVal);
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		return CLSMILElementImpl<T>::setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		return CLSMILElementImpl<T>::getTextOffset(which, offset);
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
		return CLSMILElementImpl<T>::get_tagName(pVal);
	}
	STDMETHODIMP put_tagName(BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_tagName(newVal);
	}
	STDMETHODIMP setAttributeNode(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLSMILElementImpl<T>::setAttributeNode(newAttr, pVal);
	}
	STDMETHODIMP setAttributeNodeNS(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLSMILElementImpl<T>::setAttributeNodeNS(newAttr, pVal);
	}
	STDMETHODIMP removeAttribute(BSTR name)
	{
		return CLSMILElementImpl<T>::removeAttribute(name);
	}
	STDMETHODIMP removeAttributeNS(BSTR namespaceURI, BSTR localName)
	{
		return CLSMILElementImpl<T>::removeAttributeNS(namespaceURI, localName);
	}
	STDMETHODIMP setAttribute(BSTR name, BSTR value)
	{
		return CLSMILElementImpl<T>::setAttribute(name, value);
	}
	STDMETHODIMP setAttributeNS(BSTR namespaceURI, BSTR qualifiedName, BSTR value)
	{
		return CLSMILElementImpl<T>::setAttributeNS(namespaceURI, qualifiedName, value);
	}
	STDMETHODIMP getAttribute(BSTR name, BSTR *pVal)
	{
		return CLSMILElementImpl<T>::getAttribute(name, pVal);
	}
	STDMETHODIMP getAttributeNS(BSTR namespaceURI, BSTR localName, BSTR *pVal)
	{
		return CLSMILElementImpl<T>::getAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getAttributeNode(BSTR name, ILDOMAttr **pVal)
	{
		return CLSMILElementImpl<T>::getAttributeNode(name, pVal);
	}
	STDMETHODIMP getAttributeNodeNS(BSTR qualifiedName, BSTR localName, ILDOMAttr **pVal)
	{
		return CLSMILElementImpl<T>::getAttributeNodeNS(qualifiedName, localName, pVal);
	}
	STDMETHOD(removeAttributeNode)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLSMILElementImpl<T>::removeAttributeNode(oldAttr, pVal);
	}
	STDMETHOD(removeAttributeNodeNS)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLSMILElementImpl<T>::removeAttributeNodeNS(oldAttr, pVal);
	}
	STDMETHOD(hasAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILElementImpl<T>::hasAttribute(name, pVal);
	}
	STDMETHOD (hasAttributeNS)(/*[in]*/ BSTR namespaceURI,  /*[in]*/ BSTR localName, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILElementImpl<T>::hasAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getElementsByTagName(/*[in]*/ BSTR tagName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILElementImpl<T>::getElementsByTagName(tagName, pVal);
	}
	STDMETHODIMP getElementsByTagNameNS(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR localName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILElementImpl<T>::getElementsByTagNameNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP get_markupContent(/*[out,retval]*/ BSTR *pVal)
	{
		return CLSMILElementImpl<T>::get_markupContent(pVal);
	}
	STDMETHODIMP put_markupContent(/*[in]*/ BSTR newVal)
	{
		return CLSMILElementImpl<T>::put_markupContent(newVal);
	}
	STDMETHODIMP setActive()
	{
		return CLSMILElementImpl<T>::setActive();
	}
	STDMETHOD(addBehavior)(/*[in]*/ BSTR bstrUrl, /*[in]*/ VARIANT* pvarFactory, /*[out,retval]*/ long *pCookie)
	{
		return CLSMILElementImpl<T>::addBehavior(bstrUrl, pvarFactory, pCookie);
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
	STDMETHOD(isNodeValid)(/*[in]*/ bool deep, /*[in]*/ CheckTypeVAL wFValidityCheckLevel, /*[out,retval]*/ bool *pVal)
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

#endif //__LSMILSWITCHELEMENT_H_
