#include "stdafx.h"
#include "LSVG2.h"
#include "SVGImplementation.h"

#include "SVGFilterElement.h"
#include "SVGFEBlendElement.h"
#include "SVGFEGaussianBlurElement.h"
#include "SVGFECompositeElement.h"
#include "SVGFEFloodElement.h"
#include "SVGFEOffsetElement.h"
#include "SVGFESpecularLightingElement.h"
#include "SVGFEDiffuseLightingElement.h"
#include "SVGFEDistantLightElement.h"
#include "SVGFEPointLightElement.h"
#include "SVGFESpotLightElement.h"
#include "SVGFETileElement.h"
#include "SVGFETurbulenceElement.h"
#include "SVGFEDisplacementMapElement.h"
#include "SVGFEMorphologyElement.h"
#include "SVGFEColorMatrixElement.h"
#include "SVGFEConvolveMatrixElement.h"
#include "SVGFEImageElement.h"
#include "SVGFEComponentTransferElement.h"
#include "SVGFEFuncAElement.h"
#include "SVGFEFuncRElement.h"
#include "SVGFEFuncGElement.h"
#include "SVGFEFuncBElement.h"
#include "SVGFEMergeElement.h"
#include "SVGFEMergeNodeElement.h"

namespace System
{
namespace Web
{

Element* SVGImplementation::createSVGElementFilters(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	Element* newElement = NULL;

	// Filter
	if (localName == L"filter")
	{
		SVGFilterElement* pElement = new SVGFilterElement(attributes);
		newElement = pElement;
	}
#if 0
	// feElement(s)
	else if (!wcscmp(localName, L"feBlend"))
	{
		CComObject<CLSVGFEBlendElement>* pElement;
		CComObject<CLSVGFEBlendElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"feGaussianBlur")
	{
		SVGFEGaussianBlurElement* pElement = new SVGFEGaussianBlurElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feOffset")
	{
		SVGFEOffsetElement* pElement = new SVGFEOffsetElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feComposite")
	{
		SVGFECompositeElement* pElement = new SVGFECompositeElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feFlood")
	{
		SVGFEFloodElement* pElement = new SVGFEFloodElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feSpecularLighting")
	{
		SVGFESpecularLightingElement* pElement = new SVGFESpecularLightingElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feDiffuseLighting")
	{
		SVGFEDiffuseLightingElement* pElement = new SVGFEDiffuseLightingElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feDistantLight")
	{
		SVGFEDistantLightElement* pElement = new SVGFEDistantLightElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"fePointLight")
	{
		SVGFEPointLightElement* pElement = new SVGFEPointLightElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feSpotLight")
	{
		SVGFESpotLightElement* pElement = new SVGFESpotLightElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName, L"feTurbulence"))
	{
		CComObject<CLSVGFETurbulenceElement>* pElement;
		CComObject<CLSVGFETurbulenceElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feDisplacementMap"))
	{
		CComObject<CLSVGFEDisplacementMapElement>* pElement;
		CComObject<CLSVGFEDisplacementMapElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feMorphology"))
	{
		CComObject<CLSVGFEMorphologyElement>* pElement;
		CComObject<CLSVGFEMorphologyElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"feColorMatrix")
	{
		SVGFEColorMatrixElement* pElement = new SVGFEColorMatrixElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName, L"feConvolveMatrix"))
	{
		CComObject<CLSVGFEConvolveMatrixElement>* pElement;
		CComObject<CLSVGFEConvolveMatrixElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feImage"))
	{
		CComObject<CLSVGFEImageElement>* pElement;
		CComObject<CLSVGFEImageElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feTile"))
	{
		CComObject<CLSVGFETileElement>* pElement;
		CComObject<CLSVGFETileElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
// Component transfer filter
	else if (!wcscmp(localName, L"feComponentTransfer"))
	{
		CComObject<CLSVGFEComponentTransferElement>* pElement;
		CComObject<CLSVGFEComponentTransferElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feFuncA"))
	{
		CComObject<CLSVGFEFuncAElement>* pElement;
		CComObject<CLSVGFEFuncAElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feFuncR"))
	{
		CComObject<CLSVGFEFuncRElement>* pElement;
		CComObject<CLSVGFEFuncRElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feFuncG"))
	{
		CComObject<CLSVGFEFuncGElement>* pElement;
		CComObject<CLSVGFEFuncGElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	else if (!wcscmp(localName, L"feFuncB"))
	{
		CComObject<CLSVGFEFuncBElement>* pElement;
		CComObject<CLSVGFEFuncBElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
#endif
	else if (localName == L"feMerge")
	{
		SVGFEMergeElement* pElement = new SVGFEMergeElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"feMergeNode")
	{
		SVGFEMergeNodeElement* pElement = new SVGFEMergeNodeElement(attributes);
		newElement = pElement;
	}

	return newElement;
}

}	// Web
}
