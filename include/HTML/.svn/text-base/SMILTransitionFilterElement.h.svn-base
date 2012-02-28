// LSMILTransitionFilterElement.h : Declaration of the CLSMILTransitionFilterElement

#ifndef __LSMILTRANSITIONFILTERELEMENT_H_
#define __LSMILTRANSITIONFILTERELEMENT_H_

//#include "resource.h"       // main symbols

#include "LSMILAnimationElementImpl.h"
#include "AnimationElement.h"
#include "LElementEditVALImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CLSMILTransitionFilterElement
class CLSMILTransitionFilterElement : 
	public CComObjectRootEx<CComSingleThreadModel>,

	public CLSMILAnimationElementImpl<CLSMILTransitionFilterElement>,
	public CLElementAnimateImpl<CLSMILTransitionFilterElement>,
	public CLElementEditVALImpl<CLSMILTransitionFilterElement>,

	public ILSMILTransitionFilterElement,
	public ILAnimationElement,//ILElementTime,
	public ILElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<CLSMILTransitionFilterElement>,
	public CNotifySendImpl<CLSMILTransitionFilterElement>
{
public:
	typedef CLSMILTransitionFilterElement T;

	CLSMILTransitionFilterElement()
	{
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CLSMILAnimationElementImpl<CLSMILTransitionFilterElement>::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CLElementAnimateImpl<CLSMILTransitionFilterElement>::FinalConstruct();
		if (FAILED(hr)) return hr;

		return 0;
	}

	void FinalRelease()
	{
		CLElementAnimateImpl<CLSMILTransitionFilterElement>::FinalRelease();
		CLSMILAnimationElementImpl<CLSMILTransitionFilterElement>::FinalRelease();
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLSMILTransitionFilterElement)
	COM_INTERFACE_ENTRY(ILDOMNode)
	COM_INTERFACE_ENTRY(ILDOMElement)
	COM_INTERFACE_ENTRY(ILSMILElement)
	COM_INTERFACE_ENTRY(ILSMILAnimation)
	COM_INTERFACE_ENTRY(ILSMILTransitionFilterElement)
	COM_INTERFACE_ENTRY(ILElementTime)
	COM_INTERFACE_ENTRY(ILAnimationElement)
	COM_INTERFACE_ENTRY(ILDOMEventTarget)
	COM_INTERFACE_ENTRY(ILNodeEditVAL)
	COM_INTERFACE_ENTRY(ILElementEditVAL)

	COM_INTERFACE_ENTRY(CLDOMNodeImplImpl)
	COM_INTERFACE_ENTRY(CLDOMElementImplImpl)
	COM_INTERFACE_ENTRY(CLElementTimeImplImpl)

	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown *targetObject, IUnknown *immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// ILSMILTransitionFilterElement
public:

// ILDOMNode
	STDMETHOD(get_childNodes)(/*[out, retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_childNodes(pVal);
	}
	STDMETHOD(get_localName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_localName(pVal);
	}
	STDMETHOD(set_localName)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_localName(newVal);
	}
	STDMETHOD(get_prefix)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_prefix(pVal);
	}
	STDMETHOD(set_prefix)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_prefix(newVal);
	}
	STDMETHOD(get_namespaceURI)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_namespaceURI(pVal);
	}
	STDMETHOD(set_namespaceURI)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_namespaceURI(newVal);
	}
	STDMETHOD(get_nodeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_nodeName(pVal);
	}
	STDMETHOD(set_nodeName)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_nodeName(newVal);
	}
	STDMETHOD(get_nodeValue)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_nodeValue(pVal);
	}
	STDMETHOD(set_nodeValue)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_nodeValue(newVal);
	}
	STDMETHOD(get_attributes)(/*[out, retval]*/ ILDOMNamedNodeMap* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_attributes(pVal);
	}
	STDMETHOD(isSupported)(/*[in]*/ BSTR feature, /*[in]*/ BSTR version, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILAnimationElementImpl<T>::isSupported(feature, version, pVal);
	}
	STDMETHOD(hasAttributes)(/*[out,retval]*/ bool* pVal)
	{
		return CLSMILAnimationElementImpl<T>::hasAttributes(pVal);
	}
	STDMETHOD(cloneNode)(/*[in]*/ bool deep, /*[out,retval]*/ ILDOMNode** pVal)
	{
		return CLSMILAnimationElementImpl<T>::cloneNode(deep, pVal);
	}
	STDMETHOD(hasChildNodes)(/*[out,retval]*/ bool* pVal)
	{
		return CLSMILAnimationElementImpl<T>::hasChildNodes(pVal);
	}
	STDMETHOD(replaceChild)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ ILDOMNode* oldChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILAnimationElementImpl<T>::replaceChild(newChild, oldChild, ppResult);
	}
	STDMETHOD(removeChild)(/*[in]*/ ILDOMNode* oldChild,  /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILAnimationElementImpl<T>::removeChild(oldChild, ppResult);
	}
	STDMETHOD(insertBefore)(/*[in]*/ ILDOMNode* newChild, /*[in]*/ VARIANT refChild, /*[out,retval]*/ ILDOMNode** ppResult)
	{
		return CLSMILAnimationElementImpl<T>::insertBefore(newChild, refChild, ppResult);
	}
	STDMETHOD(appendChild)(/*[in]*/ ILDOMNode* newChild, /*[out,retval]*/ ILDOMNode** result)
	{
		return CLSMILAnimationElementImpl<T>::appendChild(newChild, result);
	}
	STDMETHOD(get_ownerDocument)(/*[out, retval]*/ ILDOMDocument* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_ownerDocument(pVal);
	}
	STDMETHOD(set_ownerDocument)(/*[in]*/ ILDOMDocument* newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_ownerDocument(newVal);
	}
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_previousSibling(pVal);
	}
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ ILDOMNode **pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_nextSibling(pVal);
	}
	STDMETHOD(set_previousSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLSMILAnimationElementImpl<T>::set_previousSibling(pVal);
	}
	STDMETHOD(set_nextSibling)(/*[in]*/ ILDOMNode *pVal)
	{
		return CLSMILAnimationElementImpl<T>::set_nextSibling(pVal);
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_lastChild(pVal);
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_firstChild(pVal);
	}
	STDMETHOD(get_parentNode)(/*[out, retval]*/ ILDOMNode* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_parentNode(pVal);
	}
	STDMETHOD(set_parentNode)(/*[in]*/ ILDOMNode* pVal)
	{
		return CLSMILAnimationElementImpl<T>::set_parentNode(pVal);
	}
	STDMETHOD(get_nodeType)(/*[out, retval]*/ LDOMNodeType* pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_nodeType(pVal);
	}
	STDMETHOD(normalize)()
	{
		return CLSMILAnimationElementImpl<T>::normalize();
	}
	STDMETHOD(lookupPrefix)(/*[in]*/ BSTR namespaceURI, /*[out,retval]*/ BSTR* pVal)
	{
		return CLSMILAnimationElementImpl<T>::lookupPrefix(namespaceURI, pVal);
	}
	STDMETHOD(lookupNamespaceURI)(/*[in]*/ BSTR prefix, /*[out,retval]*/ BSTR* pVal)
	{
		return CLSMILAnimationElementImpl<T>::lookupNamespaceURI(prefix, pVal);
	}
	STDMETHOD(setUserData)(/*[in]*/ BSTR key, /*[in]*/ LDOMUserData data, /*[in]*/ ILDOMUserDataHandler* handler, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLSMILAnimationElementImpl<T>::setUserData(key, data, handler, pVal);
	}
	STDMETHOD(getUserData)(/*[in]*/ BSTR key, /*[out,retval]*/ LDOMUserData *pVal)
	{
		return CLSMILAnimationElementImpl<T>::getUserData(key, pVal);
	}
	STDMETHOD(get_textContent)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_textContent(pVal);
	}
	STDMETHOD(set_textContent)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_textContent(newVal);
	}
	STDMETHOD(removeChildren)()
	{
		return CLSMILAnimationElementImpl<T>::removeChildren();
	}
	STDMETHOD(get_uniqID)(/*[out, retval]*/ GUID *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_uniqID(pVal);
	}
	STDMETHOD(set_uniqID)(/*[in]*/ GUID newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_uniqID(newVal);
	}
	STDMETHOD(setTextOffset)(/*[in]*/ long which, /*[in]*/ long offset)
	{
		return CLSMILAnimationElementImpl<T>::setTextOffset(which, offset);
	}
	STDMETHOD(getTextOffset)(/*[in]*/ long which, /*[out,retval]*/ long* offset)
	{
		return CLSMILAnimationElementImpl<T>::getTextOffset(which, offset);
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
		return CLSMILAnimationElementImpl<T>::get_tagName(pVal);
	}
	STDMETHODIMP set_tagName(BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_tagName(newVal);
	}
	STDMETHODIMP setAttributeNode(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLSMILAnimationElementImpl<T>::setAttributeNode(newAttr, pVal);
	}
	STDMETHODIMP setAttributeNodeNS(ILDOMAttr *newAttr, ILDOMAttr **pVal)
	{
		return CLSMILAnimationElementImpl<T>::setAttributeNodeNS(newAttr, pVal);
	}
	STDMETHODIMP removeAttribute(BSTR name)
	{
		return CLSMILAnimationElementImpl<T>::removeAttribute(name);
	}
	STDMETHODIMP removeAttributeNS(BSTR namespaceURI, BSTR localName)
	{
		return CLSMILAnimationElementImpl<T>::removeAttributeNS(namespaceURI, localName);
	}
	STDMETHODIMP setAttribute(BSTR name, BSTR value)
	{
		return CLSMILAnimationElementImpl<T>::setAttribute(name, value);
	}
	STDMETHODIMP setAttributeNS(BSTR namespaceURI, BSTR qualifiedName, BSTR value)
	{
		return CLSMILAnimationElementImpl<T>::setAttributeNS(namespaceURI, qualifiedName, value);
	}
	STDMETHODIMP getAttribute(BSTR name, BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::getAttribute(name, pVal);
	}
	STDMETHODIMP getAttributeNS(BSTR namespaceURI, BSTR localName, BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::getAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHODIMP getAttributeNode(BSTR name, ILDOMAttr **pVal)
	{
		return CLSMILAnimationElementImpl<T>::getAttributeNode(name, pVal);
	}
	STDMETHODIMP getAttributeNodeNS(BSTR qualifiedName, BSTR localName, ILDOMAttr **pVal)
	{
		return CLSMILAnimationElementImpl<T>::getAttributeNodeNS(qualifiedName, localName, pVal);
	}
	STDMETHOD(removeAttributeNode)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLSMILAnimationElementImpl<T>::removeAttributeNode(oldAttr, pVal);
	}
	STDMETHOD(removeAttributeNodeNS)(/*[in]*/ ILDOMAttr* oldAttr, /*[out,retval]*/ ILDOMAttr** pVal)
	{
		return CLSMILAnimationElementImpl<T>::removeAttributeNodeNS(oldAttr, pVal);
	}
	STDMETHOD(hasAttribute)(/*[in]*/ BSTR name, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILAnimationElementImpl<T>::hasAttribute(name, pVal);
	}
	STDMETHOD (hasAttributeNS)(/*[in]*/ BSTR namespaceURI,  /*[in]*/ BSTR localName, /*[out,retval]*/ bool* pVal)
	{
		return CLSMILAnimationElementImpl<T>::hasAttributeNS(namespaceURI, localName, pVal);
	}
	STDMETHOD(getElementsByTagName)(/*[in]*/ BSTR tagName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::getElementsByTagName(tagName, pVal);
	}
	STDMETHOD(getElementsByTagNameNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR localName, /*[out,retval]*/ ILDOMNodeList* *pVal)
	{
		return CLSMILAnimationElementImpl<T>::getElementsByTagNameNS(namespaceURI, localName, pVal);
	}
	STDMETHOD(get_markupContent)(/*[out,retval]*/ BSTR *pVal)
	{
		return CLSMILAnimationElementImpl<T>::get_markupContent(pVal);
	}
	STDMETHOD(set_markupContent)(/*[in]*/ BSTR newVal)
	{
		return CLSMILAnimationElementImpl<T>::set_markupContent(newVal);
	}
	STDMETHOD(setActive)()
	{
		return CLSMILAnimationElementImpl<T>::setActive();
	}
	STDMETHOD(addBehavior)(/*[in]*/ BSTR bstrUrl, /*[in]*/ VARIANT* pvarFactory, /*[out,retval]*/ long *pCookie)
	{
		return CLSMILAnimationElementImpl<T>::addBehavior(bstrUrl, pvarFactory, pCookie);
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
// ILAnimationElement
	STDMETHOD(get_targetElement)(ILDOMElement* *pVal)
	{
		return CLElementAnimateImpl<T>::get_targetElement(pVal);
	}
	STDMETHOD(get_attributeName)(/*[out, retval]*/ BSTR *pVal)
	{
		return CLElementAnimateImpl<T>::get_attributeName(pVal);
	}
	STDMETHOD(set_attributeName)(/*[in]*/ BSTR newVal)
	{
		return CLElementAnimateImpl<T>::set_attributeName(newVal);
	}
	STDMETHOD(get_attributeType)(/*[out, retval]*/ LAttributeType *pVal)
	{
		return CLElementAnimateImpl<T>::get_attributeType(pVal);
	}
	STDMETHOD(set_attributeType)(/*[in]*/ LAttributeType newVal)
	{
		return CLElementAnimateImpl<T>::set_attributeType(newVal);
	}
// ILElementTime
	STDMETHOD(get_fill)(LAnimFillType *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_fill)(LAnimFillType newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_repeatCount)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_repeatCount)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_repeatDur)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_repeatDur)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_restart)(LAnimRestartType *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_restart)(LAnimRestartType newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_dur)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_dur)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_begin)(ILSMILTimeList* *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_end)(ILSMILTimeList* *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(seekElement)(double seekTo)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(beginElement)(bool* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(beginElementAt)(double offset, bool* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(endElement)(bool* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(endElementAt)(double offset, bool* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_speed)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_speed)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_accelerate)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_accelerate)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_decelerate)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_decelerate)(double newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_autoReverse)(bool *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(set_autoReverse)(bool newVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}

// Extensions
	STDMETHOD(get_currentInterval)(ILTimeInterval* *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_simpleTime)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(get_activeTime)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(getSimpleDuration)(double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(getActiveDuration)(/*[out,retval]*/ double *pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHODIMP ActiveTimeToSimpleTime(double tau, double* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
	STDMETHOD(SimpleTimeToActiveTime)(double tsf, double* pVal)
	{
		ASSERT(0);
		return E_NOTIMPL;
	}
};

#endif //__LSMILTRANSITIONFILTERELEMENT_H_
