#ifndef w3c_SVGAnimationElement_h
#define w3c_SVGAnimationElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGAnimationElement : public SVGElement
{
public:

	CTOR SVGAnimationElement(PSVGElement* pelement, NamedNodeMap* attributes, CalcModeType calcMode);

	ElementAnimate* m_animateImpl;

protected:

	virtual bool dispatchEvent2(Event* evt, bool bCapture);

#if 0
	STDMETHOD(get_targetElement)(ILSVGElement* *pVal)
	{
		ASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		*pVal = NULL;

		CComBSTR targetElement;
		static_cast<T*>(this)->getAttribute(L"targetElement", &targetElement);
		if (targetElement.Length() > 0)
		{
			CComPtr<ILDOMElement> element;
			static_cast<T*>(this)->m_ownerDocument->getElementById(targetElement, &element);

			CComQIPtr<ILSVGElement> svgElement = element;
			*pVal = svgElement.Detach();

			return S_OK;
		}

/*	  getAttribute(L"xlink:href", &href);
		if (href)
		{
		}

	  m_svgdocument->getElementByID(...);

		*/

		CComPtr<ILDOMNode> parentNode;
		static_cast<T*>(this)->get_parentNode(&parentNode);

		CComQIPtr<ILSVGElement> svgElement = parentNode;
		*pVal = svgElement.Detach();

		return S_OK;
	}
#endif
};

}	// w3c
}

#endif // w3c_SVGAnimationElement_h
