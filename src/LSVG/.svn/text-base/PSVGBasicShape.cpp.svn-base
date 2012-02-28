#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGElement.h"

namespace System
{
namespace Web
{

void DrawPathSegList(SVGPathSegList* seglist, Gui::Geometry* path, SVGMatrix* matrix);

bool /*PSVGBasicShape::*/HitTestPath(PElementBase* pElement, Graphics::Geometry* pGraphicsPathF, double x, double y, int pointerEvents)
{
	ASSERT(0);
	bool bOver = false;
#if 0

	LDraw::Pen pen(LDraw::Color(), (float)pElement->m_computedStrokeWidth);

	if (pointerEvents == PointerEvents_visiblePainted)
	{
		if (pElement->m_computedVisibility == Visibility_visible)
		{
			bOver =

				((pElement->m_computedFill.m_type != SVG_PAINTTYPE_NONE) &&
				pGraphicsPathF->IsVisible((float)x, (float)y))

				||

				((pElement->m_computedStroke.m_type != SVG_PAINTTYPE_NONE) &&
				pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen));
		}
	}
	else if (pointerEvents == PointerEvents_visibleFill)
	{
		if (pElement->m_computedVisibility == Visibility_visible)
		{
			bOver = pGraphicsPathF->IsVisible((float)x, (float)y);
		}
	}
	else if (pointerEvents == PointerEvents_visibleStroke)
	{
		if (pElement->m_computedVisibility == Visibility_visible)
		{
			bOver = pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen);
		}
	}
	else if (pointerEvents == PointerEvents_visible)
	{
		if (pElement->m_computedVisibility == Visibility_visible)
		{
			bOver =
				pGraphicsPathF->IsVisible((float)x, (float)y)
				||
				pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen);
		}
	}

	// Same as above, except ignore visiblity
	else if (pointerEvents == PointerEvents_painted)
	{
		bOver =

			((pElement->m_computedFill.m_type != SVG_PAINTTYPE_NONE) &&
			pGraphicsPathF->IsVisible((float)x, (float)y))

			||

			((pElement->m_computedStroke.m_type != SVG_PAINTTYPE_NONE) &&
			pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen));
	}
	else if (pointerEvents == PointerEvents_fill)
	{
		bOver = pGraphicsPathF->IsVisible((float)x, (float)y);
	}
	else if (pointerEvents == PointerEvents_stroke)
	{
		bOver = pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen);
	}
	else if (pointerEvents == PointerEvents_all)
	{
		bOver =
			pGraphicsPathF->IsVisible((float)x, (float)y)
			||
			pGraphicsPathF->IsOutlineVisible((float)x, (float)y, &pen);
	}
#endif
	return bOver;
}

}	// Web
}	// System
