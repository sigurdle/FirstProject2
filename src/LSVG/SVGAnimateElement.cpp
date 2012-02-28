#include "stdafx.h"
#include "LSVG2.h"

#include "SVGAnimateElement.h"

namespace System
{
namespace Web
{

SVGAnimateElement::SVGAnimateElement(NamedNodeMap* attributes) :
	SVGAnimationElement(new PSVGElement(this), attributes, CALCMODE_LINEAR)
{
	/*
	AddXMLAttribute(NewNXMLAttr(&m_animateImpl->m_calcMode, NULL, WSTR("calcMode"), WSTR("linear")));

	SetAllValues(this);	// ???
	*/
}

}	// w3c
}
