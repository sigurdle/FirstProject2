#include "stdafx.h"
#include "LSVG2.h"

#include "SVGMissingGlyphElement.h"

namespace System
{
namespace Web
{

ErrorCode SVGMissingGlyphElement::dispatchEvent2(Event* evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault)
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

	return CLDOMEventTargetImpl<SVGMissingGlyphElement>::dispatchEvent2(evt, bCapture, doDefault);
#endif
}

}	// LSVG
}
