#pragma once

class CLSVGElementImplImpl
{
public:
	IUnknown* m_pElement;

	HRESULT get_viewportElement(ILDOMElement* thisNode, /*[out, retval]*/ ILSVGElement* *pVal);
	HRESULT get_ownerSVGElement(ILDOMElement* thisNode, /*[out, retval]*/ ILSVGSVGElement* *pVal);
};

template <class IBase> class ATL_NO_VTABLE CLSVGElementImpl :
	public IBase,
	public CLSVGElementImplImpl
{
public:
// ILSVGElement
	STDMETHOD(get_viewportElement)(/*[out, retval]*/ ILSVGElement* *pVal)
	{
		return CLSVGElementImplImpl::get_viewportElement(static_cast<IBase*>(this), pVal);
	}
	STDMETHOD(get_ownerSVGElement)(/*[out, retval]*/ ILSVGSVGElement* *pVal)
	{
		return CLSVGElementImplImpl::get_ownerSVGElement(static_cast<IBase*>(this), pVal);
	}

// ILDOMElement
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->getTextOffset(which, offset);
	}
	STDMETHOD(setAttributeNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR qualifiedName, /*[in]*/ BSTR value)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->setAttributeNS(namespaceURI, qualifiedName, value);
	}
	STDMETHOD(getAttributeNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR localName, /*[out,retval]*/ BSTR* pVal)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->getAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHOD(removeAttribute)(/*[in]*/ BSTR name)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->removeAttribute(name);
	}
	STDMETHOD(getAttributeNode)(/*[in]*/ BSTR name, /*[out,retval]*/ ILDOMAttr** ppResult)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->getAttributeNode(name, ppResult);
	}
	STDMETHOD(setAttribute)(/*[in]*/ BSTR name, /*[in]*/ BSTR value)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->setAttribute(name, value);
	}
	STDMETHOD(getAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ BSTR* pValue)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->getAttribute(name, pValue);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->get_attributes(pVal);
	}
	STDMETHOD(put_attributes)(/*[in]*/ ILDOMNamedNodeMap* newVal)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->put_attributes(newVal);
	}
	STDMETHOD(get_tagName)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->get_tagName(pVal);
	}
	STDMETHOD(put_tagName)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->put_tagName(newVal);
	}
	STDMETHOD(setAttributeNode)(/*[in]*/ ILDOMAttr* newAttr, /*[out,retval]*/ ILDOMAttr** ppAttr)
	{
		CComQIPtr<ILDOMElement> pElement = m_pElement;
		return pElement->setAttributeNode(newAttr, ppAttr);
	}
// ILDOMNode
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_textContent(pVal);
	}
	STDMETHOD(put_textContent)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_textContent(newVal);
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_uniqID(pVal);
	}
	STDMETHOD(put_uniqID)(/*[in]*/ GUID newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_uniqID(newVal);
	}
	STDMETHOD(getWhiteSpace)(/*[in]*/ long which, /*[out,retval]*/ BSTR* whitespace)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->getWhiteSpace(which, whitespace);
	}
	STDMETHOD(setWhiteSpace)(/*[in]*/ long which, /*[in]*/ BSTR whitespace)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->setWhiteSpace(which, whitespace);
	}
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_childNodes(pVal);
	}
	STDMETHOD(GetNProp)(/*[in]*/ BSTR name, /*[out,retval]*/ DWORD* dwdata)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->GetNProp(name, dwdata);
	}
	STDMETHOD(SetNProp)(/*[in]*/ BSTR name, /*[in]*/ DWORD dwdata)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->SetNProp(name, dwdata);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_localName(pVal);
	}
	STDMETHOD(put_localName)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_prefix(pVal);
	}
	STDMETHOD(put_prefix)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_namespaceURI(pVal);
	}
	STDMETHOD(put_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_namespaceURI(newVal);
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_nodeName(pVal);
	}
	STDMETHOD(put_nodeName)(/*[in]*/ BSTR newVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_nodeName(newVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ VARIANT_BOOL deep, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->cloneNode(deep, ppResult);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ VARIANT_BOOL* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(get_nodeType)(LDOMNodeType* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_nodeType(pVal);
	}
	STDMETHOD(get_parentNode)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_parentNode(pVal);
	}
	STDMETHOD(put_parentNode)(ILDOMNode* pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_parentNode(pVal);
	}
	STDMETHOD(get_firstChild)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_firstChild(pVal);
	}
	STDMETHOD(get_lastChild)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_lastChild(pVal);
	}
	STDMETHOD(get_nextSibling)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_nextSibling(pVal);
	}
	STDMETHOD(get_previousSibling)(ILDOMNode * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_previousSibling(pVal);
	}
	STDMETHOD(appendChild)(ILDOMNode * newChild, ILDOMNode * * result)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->appendChild(newChild, result);
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_previousSibling(pVal);
	}
	STDMETHOD(put_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_nextSibling(pVal);
	}
	STDMETHOD(get_ownerDocument)(ILDOMDocument * * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->get_ownerDocument(pVal);
	}
	STDMETHOD(put_ownerDocument)(ILDOMDocument * pVal)
	{
		CComQIPtr<ILDOMNode> pElement = m_pElement;
		return pElement->put_ownerDocument(pVal);
	}
};