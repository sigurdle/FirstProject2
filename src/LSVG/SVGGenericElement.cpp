#include "stdafx.h"
#include "LSVG2.h"
#include "SVGGenericElement.h"

namespace System
{
namespace Web
{

SVGGenericElement::SVGGenericElement(StringIn qualifiedName) : SVGElement(new PSVGElement(this))
{
	m_nodeName = qualifiedName;
	SetAllValues(this);	// ???
}

SVGGenericElement::SVGGenericElement(StringIn qualifiedName, NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	m_nodeName = qualifiedName;
	SetAllValues(this);	// ???
}

}	// Web
}
