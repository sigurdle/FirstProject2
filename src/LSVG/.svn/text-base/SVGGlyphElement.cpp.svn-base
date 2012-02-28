#include "stdafx.h"
#include "LSVG2.h"

#include "SVGGlyphElement.h"

namespace System
{
namespace Web
{

SVGGlyphElement::SVGGlyphElement(NamedNodeMap* attributes) : SVGElement(new PSVGGlyphElement(this), attributes)
{
	NewNXMLAttr(&m_d, NULL, WSTR("d"));
	AddXMLAttribute(m_d);

	m_d->m_value->m_value->m_seglist->m_pListener = this;
	m_d->m_value->m_value->m_normalizedseglist->m_pListener = this;

	AddXMLAttribute(NewXMLAttr(&m_horiz_adv_x, NULL, WSTR("horiz-adv-x")));

	SetAllValues(this);	// ???
}

SVGGlyphElement::~SVGGlyphElement()
{
	m_d->m_value->m_value->m_seglist->m_pListener = NULL;
	m_d->m_value->m_value->m_normalizedseglist->m_pListener = NULL;
}

void SVGGlyphElement::OnPathSegListChange(SVGPathSegList* pSegList)
{
	if (pSegList == m_d->m_value->m_value->m_seglist)
	{
		// TODO
		m_d->OnBaseValChanged();
	}
	else if (pSegList == m_d->m_value->m_value->m_normalizedseglist)
	{
	// Copy the normalized seglist to the the seglist
		m_d->m_value->m_value->m_seglist->RemoveAll();
		m_d->m_value->m_value->m_seglist->AddSegListNoUpdate(m_d->m_value->m_value->m_normalizedseglist);

		m_d->OnBaseValChanged();
	}
}

ErrorCode SVGGlyphElement::dispatchEvent2(Event* evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault)
{
	ASSERT(0);
	return 0;
#if 0
	LDOMEventPhaseType phase;
	evt->get_eventPhase(&phase);

	if (phase != CAPTURING_PHASE)	// ??
	{
		CComBSTR type;
		evt->get_type(&type);

		if (!wcscmp(type, L"mousedown"))
		{
			Fire_onmousedown(evt);
		}
		else if (!wcscmp(type, L"mouseup"))
		{
			Fire_onmouseup(evt);
		}
		else if (!wcscmp(type, L"mousemove"))
		{
			Fire_onmousemove(evt);
		}
		else if (!wcscmp(type, L"keydown"))
		{
			Fire_onkeydown(evt);
		}
		else if (!wcscmp(type, L"keyup"))
		{
			Fire_onkeyup(evt);
		}
		else if (!wcscmp(type, L"contextmenu"))
		{
			Fire_oncontextmenu(evt);
		}
		else if (!wcscmp(type, L"select"))
		{
			Fire_onselect(evt);
		}
	}

	return CLDOMEventTargetImpl<SVGGlyphElement>::dispatchEvent2(evt, bCapture, doDefault);
#endif
}

}	// w3c
}
