#include "stdafx.h"
#include "LSVG2.h"
#include "PSVGFEElement.h"

#include "SVGFilterPrimitiveStandardAttributesImpl.h"
#include "SVGFilterElement.h"
#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

void PSVGFEElement::CalculatePrimitiveSubRegion(PSVGFilterElement* pFilterElement, PSVGElement* pReferencingElement, /*in,out*/gm::RectF& subRegion)
{
	ISVGFilterPrimitiveStandardAttributes* pStdAttributes = dynamic_cast<ISVGFilterPrimitiveStandardAttributes*>(m_pNode);
	ASSERT(pStdAttributes != NULL);

	SVGFilterElement* psvgFilterElement = static_cast<SVGFilterElement*>(pFilterElement->m_pNode);

	ISVGLength* xLength = pStdAttributes->get_x()->get_animVal();
	ISVGLength* yLength = pStdAttributes->get_y()->get_animVal();
	ISVGLength* widthLength = pStdAttributes->get_width()->get_animVal();
	ISVGLength* heightLength = pStdAttributes->get_height()->get_animVal();

//	RectD filterRegion = pReferencingElement->m_filterRect;

//	RectD subRegion;

	if (psvgFilterElement->primitiveUnits_attr().m_animated->m_animVal->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		gm::RectD rect = pReferencingElement->m_bounds;

		if (pStdAttributes->get_xAttr()->get_specified())
		{
			if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.X = rect.X + (xLength->get_valueInSpecifiedUnits() * rect.Width/100);
			else
				subRegion.X = rect.X + (xLength->get_value() * rect.Width);
		}
		//else
		//	subRegion.X = filterRegion.X;

		if (pStdAttributes->get_yAttr()->get_specified())
		{
			if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Y = rect.Y + (yLength->get_valueInSpecifiedUnits() * rect.Height/100);
			else
				subRegion.Y = rect.Y + (yLength->get_value() * rect.Height);
		}
		//else
		//	subRegion.Y = filterRegion.Y;

		if (pStdAttributes->get_widthAttr()->get_specified())
		{
			if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Width = (widthLength->get_valueInSpecifiedUnits() * rect.Width/100);
			else
				subRegion.Width = (widthLength->get_value() * rect.Width);
		}
		//else
		//	subRegion.Width = filterRegion.Width;

		if (pStdAttributes->get_heightAttr()->get_specified())
		{
			if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Height = (heightLength->get_valueInSpecifiedUnits() * rect.Height/100);
			else
				subRegion.Height = (heightLength->get_value() * rect.Height);
		}
		//else
		//	subRegion.Height = filterRegion.Height;
	}
	else
	{
		gm::RectD rect = pReferencingElement->GetViewportElement()->GetViewBox();

		if (pStdAttributes->get_xAttr()->get_specified())
		{
			if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.X = rect.X + (xLength->get_valueInSpecifiedUnits() * rect.Width/100);
			else
				subRegion.X = xLength->get_value();
		}
		//else
		//	subRegion.X = filterRegion.X;

		if (pStdAttributes->get_yAttr()->get_specified())
		{
			if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Y = rect.Y + (yLength->get_valueInSpecifiedUnits() * rect.Height/100);
			else
				subRegion.Y = yLength->get_value();
		}
		//else
		//	subRegion.Y = filterRegion.Y;

		if (pStdAttributes->get_widthAttr()->get_specified())
		{
			if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Width = (widthLength->get_valueInSpecifiedUnits() * rect.Width/100);
			else
				subRegion.Width = widthLength->get_value();
		}
		//else
		//	subRegion.Width = filterRegion.Width;

		if (pStdAttributes->get_heightAttr()->get_specified())
		{
			if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
				subRegion.Height = (heightLength->get_valueInSpecifiedUnits() * rect.Height/100);
			else
				subRegion.Height = heightLength->get_value();
		}
		//else
		//	subRegion.Height = filterRegion.Height;
	}

//	return subRegion;
}

}	// Web
}	// System
