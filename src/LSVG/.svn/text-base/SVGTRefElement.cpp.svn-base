#include "stdafx.h"
#include "LSVG2.h"
#include "SVGTRefElement.h"
#include "PSVGTRefElement.h"

namespace System
{
namespace Web
{

SVGTRefElement::SVGTRefElement(NamedNodeMap* attributes) : SVGTextPositioningElementImpl(new PSVGTRefElement(this), attributes)
{
	m_refElement = NULL;

	SetAllValues(this);	// ???
}

long SVGTRefElement::getNumberOfChars()
{
	ASSERT(0);
#if 0
	if (m_refElement == NULL)
	{
		sysstring href = m_href->m_animated->m_animVal->m_value.m_value;
		if (href.length())
		{
			if ((href.c_str())[0] == L'#')
			{
				const OLECHAR* id = &(href.c_str())[1];

				LXML::Element element = m_ownerDocument->getElementById(id);

				m_refElement = element;
			}
		}
	}

	if (m_refElement)
	{
		sysstring textContent = m_refElement->get_textContent();
		return textContent.length();
	}
#endif
	return 0;
}

}	// LSVG
}
