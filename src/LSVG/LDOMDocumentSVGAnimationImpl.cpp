#include "stdafx.h"
#include "LSVG2.h"

#include "SVGImplementation.h"

#include "SVGSeqElement.h"
#include "SVGParElement.h"

#include "SVGVideoElement.h"
#include "SVGAudioElement.h"

#include "SVGAnimateElement.h"
#include "SVGAnimateColorElement.h"
#include "SVGAnimateTransformElement.h"
#include "SVGAnimateMotionElement.h"
#include "SVGSetElement.h"

namespace System
{
namespace Web
{

Element* SVGImplementation::createSVGElementAnimation(StringIn localName, StringIn qualifiedName, NamedNodeMap* attributes)
{
	Element* newElement = NULL;

	if (localName == L"seq")
	{
		SVGSeqElement* pElement = new SVGSeqElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"par")
	{
		SVGParElement* pElement = new SVGParElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"video")
	{
		SVGVideoElement* pElement = new SVGVideoElement(attributes);
		newElement = pElement;
	}
#if 0
	else if (!wcscmp(localName, L"audio"))
	{
		CComObject<CLSVGAudioElement>* pElement;
		CComObject<CLSVGAudioElement>::CreateInstance(&pElement);
		if (pElement)
		{
			newElement = pElement;
		}
	}
	// Animation
	else
#endif
	else if (localName == L"animate")
	{
		SVGAnimateElement* pElement = new SVGAnimateElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"animateColor")
	{
		SVGAnimateColorElement* pElement = new SVGAnimateColorElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"animateTransform")
	{
		SVGAnimateTransformElement* pElement = new SVGAnimateTransformElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"animateMotion")
	{
		SVGAnimateMotionElement* pElement = new SVGAnimateMotionElement(attributes);
		newElement = pElement;
	}
	else if (localName == L"set")
	{
		SVGSetElement* pElement = new SVGSetElement(attributes);
		newElement = pElement;
	}

	return newElement;
}

}	// w3c
}
