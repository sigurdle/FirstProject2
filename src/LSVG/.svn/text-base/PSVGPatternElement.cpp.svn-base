#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGPatternElement.h"
#include "SVGPatternElement.h"

#include "SVGURIReferenceImpl.h"

namespace System
{
namespace Web
{

PSVGPatternElement::PSVGPatternElement(SVGPatternElement* element) : PSVGElement(element)
{
}

//virtual
void PSVGPatternElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	m_bounds = CalculateRenderableChildrenBoundingBox();
}

// virtual
void PSVGPatternElement::RecalculateParentBounds()
{
	ASSERT(0);
#if 0
	CalculateBounds();
	PSVGElement::RecalculateParentBounds();

// Notify dependant elements
	CUPtrList list;
	UPOSITION pos;

// Make a copy of the list first
	pos = m_referencingElements.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_referencingElements.GetNext(pos);
		list.AddTail(pElement);
	}

	pos = list.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)list.GetNext(pos);

	// TODO, have a ReferenceChanged(Element) ??
		pElement->CalculateBoundsAndChildren();
		pElement->RecalculateParentBounds();
	}
#endif
}

//virtual
Gui::Brush* PSVGPatternElement::CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY)
{
	SVGPatternElement* psvgElement = static_cast<SVGPatternElement*>(m_pNode);

	ASSERT(0);
	return NULL;
#if 0

//	RectD bounds = m_bounds;

	CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
	CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	gmMatrix3 mat;

	bool bHasViewBox = psvgElement->hasAttribute(L"viewBox");

	if (bHasViewBox)
	{
		// Ignore patternContentUnits when viewBox is specified
	}
	else
	{
	}

	if (psvgElement->m_patternUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		ASSERT(0);
		return NULL;
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		LDraw::RectD bounds;
		bounds.X = 0;
		bounds.Y = 0;
		bounds.Width = psvgElement->m_width->m_animated->m_animVal->m_value->m_valueInSpecifiedUnits;
		bounds.Height = psvgElement->m_height->m_animated->m_animVal->m_value->m_valueInSpecifiedUnits;

	//	rect = pReferencingElement->GetViewportElement()->GetViewBox();

		LDraw::Bitmap bitmap(ceil(bounds.Width*scaleX), ceil(bounds.Height*scaleY));
		{
			LDraw::Graphics graphics(&bitmap);
			graphics.ScaleTransform(float(scaleX), float(scaleY));
			graphics.TranslateTransform(float(-bounds.X), float(-bounds.Y));

			LXML::CHTMRenderContext rcontext;
			rcontext.m_clip = LDraw::RectF(0, 0, bounds.Width, bounds.Height);

			RenderChildren(&rcontext, &graphics, scaleX, scaleY);
		}

	//	LDraw::RectF texbounds(0, 0, bounds.Width, bounds.Height);
		LDraw::TextureBrush* pTexBrush = new LDraw::TextureBrush(&bitmap, LDraw::WrapModeTile, 0, 0, bounds.Width*scaleX, bounds.Height*scaleY);

		pTexBrush->TranslateTransform(xLength->m_value, yLength->m_value);

		pTexBrush->ScaleTransform(1/scaleX, 1/scaleY);

		gmMatrix3 matrix = psvgElement->m_patternTransform->m_animated->m_animVal->m_value->consolidate();
		//if (pMatrix)
		{
			LDraw::Matrix matrix(
				(float)matrix[0][0], (float)matrix[0][1],
				(float)matrix[1][0], (float)matrix[1][1],
				(float)matrix[2][0], (float)matrix[2][1]);

			pTexBrush->MultiplyTransform(&matrix);

			//pMatrix->Release();
		}

		return pTexBrush;
	}
#endif
}

}	// LSVG
}
