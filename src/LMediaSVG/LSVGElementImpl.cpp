#include "stdafx.h"
#include "LSVG.h"
#include "LSVGElementImpl.h"

HRESULT CLSVGElementImplImpl::get_ownerSVGElement(ILDOMElement* thisNode, ILSVGSVGElement **pVal)
{
	CComQIPtr<ILDOMElement> parent;
	thisNode->get_parentNode((ILDOMNode**)&parent);

	while (parent != NULL)
	{
		CComQIPtr<ILSVGSVGElement> svgsvgElement = parent;

		if (svgsvgElement != NULL)
		{
			*pVal = svgsvgElement;
			(*pVal)->AddRef();
			return S_OK;
		}

		CComQIPtr<ILDOMNode> parentNode;
		parent->get_parentNode(&parentNode);
		parent = parentNode;
	}

	*pVal = NULL;

	return S_OK;
}

HRESULT CLSVGElementImplImpl::get_viewportElement(ILDOMElement* thisNode, ILSVGElement **pVal)
{
	CComQIPtr<ILDOMElement> parent;
	thisNode->get_parentNode((ILDOMNode**)&parent);

	while (parent != NULL)
	{
		CComQIPtr<ILSVGElement> svgelement = parent;
		if (svgelement)
		{
			ATLASSERT(0);
#if 0
			CComQIPtr<ISVGFitToViewBox> viewbox = svgelement;

			if (viewbox != NULL)
			{
				*pVal = svgelement;
				(*pVal)->AddRef();
				return S_OK;
			}
#endif
		}

		CComQIPtr<ILDOMNode> parentNode;
		parent->get_parentNode(&parentNode);
		parent = parentNode;
	}

	*pVal = NULL;

	return S_OK;
}
