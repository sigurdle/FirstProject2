#include "stdafx.h"
#include "LSVG2.h"
#include "SVGFEComponentTransferElement.h"
#include "PSVGFEComponentTransferElement.h"

namespace System
{
namespace Web
{

SVGFEComponentTransferElement::SVGFEComponentTransferElement() : SVGElement(new PSVGFEComponentTransferElement(this))
{
	m_in1 = NULL;

	ASSERT(0);
//	AddXMLAttribute(NewXMLAttr(&m_in1, NULL, WSTR("in")));

	SetAllValues(this);	// ???
}

SVGAnimatedString* SVGFEComponentTransferElement::get_in1()
{
	return m_in1->m_animated;
}

}	// Web
}
