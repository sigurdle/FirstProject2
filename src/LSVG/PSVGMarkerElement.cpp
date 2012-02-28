#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGMarkerElement.h"
#include "SVGMarkerElement.h"

namespace System
{
namespace Web
{

PSVGMarkerElement::PSVGMarkerElement(SVGMarkerElement* element) : PSVGElement(element)
{
}

//virtual
void PSVGMarkerElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	m_bounds = CalculateRenderableChildrenBoundingBox();
}

// virtual
void PSVGMarkerElement::RecalculateParentBounds()
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

gm::RectD GetViewBoxRect(gm::RectD viewBox, SVGPreserveAspectRatio* preserveAspectRatio, LDraw::RectD viewPort);

void PSVGMarkerElement::DrawMarker(CHTMRenderContext* pC, Gui::RenderContext* pGraphics, PSVGElement* pReferencingElement, MarkerVertex* vertex)
{
	ASSERT(0);
#if 0
	Gdiplus::GraphicsState state = pGraphics->Save();

	CLSVGMarkerElement* psvgMarkerElement = static_cast<CLSVGMarkerElement*>(m_pNode);

	RectD viewBox(
		0,
		0,
		psvgMarkerElement->m_markerWidth->m_animated->m_animVal->m_value->m_value,
		psvgMarkerElement->m_markerHeight->m_animated->m_animVal->m_value->m_value);

	RectD viewPort = RectD(
		psvgMarkerElement->m_viewBox->m_animated->m_animVal->m_value->m_x,
		psvgMarkerElement->m_viewBox->m_animated->m_animVal->m_value->m_y,
		psvgMarkerElement->m_viewBox->m_animated->m_animVal->m_value->m_width,
		psvgMarkerElement->m_viewBox->m_animated->m_animVal->m_value->m_height);

	RectD rect = GetViewBoxRect(
		viewBox,
		psvgMarkerElement->m_preserveAspectRatio->m_animated->m_animVal->m_value,
		viewPort);

	double refX = psvgMarkerElement->m_refX->m_animated->m_animVal->m_value->m_value;
	double refY = psvgMarkerElement->m_refY->m_animated->m_animVal->m_value->m_value;

//	gmMatrix3 mat = gmMatrix3::identity();
//	mat = mat * gmMatrix3::translate(vertex->x, vertex->y);
	pGraphics->TranslateTransform(vertex->x, vertex->y);

	if (psvgMarkerElement->m_orientType->m_animated->m_animVal->m_value->m_value == SVG_MARKER_ORIENT_AUTO)
	{
		//mat = mat * gmMatrix3::rotate(vertex->tangent);
		pGraphics->RotateTransform(vertex->tangent);
	}
	else
	{
		//mat = mat * gmMatrix3::rotate(psvgMarkerElement->m_orientAngle->m_animated->m_animVal->m_value->m_value);
		pGraphics->RotateTransform(psvgMarkerElement->m_orientAngle->m_animated->m_animVal->m_value->m_value);
	}

	if (psvgMarkerElement->m_markerUnits->m_animated->m_animVal->m_value->m_value == SVG_MARKERUNITS_STROKEWIDTH)
	{
		//mat = mat * gmMatrix3::scale(pReferencingElement->m_computedStrokeWidth, pReferencingElement->m_computedStrokeWidth);
		pGraphics->ScaleTransform(pReferencingElement->m_computedStrokeWidth, pReferencingElement->m_computedStrokeWidth);
	}

	//mat = mat * gmMatrix3::translate(-refX*(rect.Width/viewPort.Width), -refY*(rect.Height/viewPort.Height));
	pGraphics->TranslateTransform(-refX*(rect.Width/viewPort.Width), -refY*(rect.Height/viewPort.Height));

	if (m_computedOverflowX == Overflow_hidden || m_computedOverflowX == Overflow_scroll)
	{
		RectD clipRect;

		clipRect.X = rect.X + m_computedClip[3];
		clipRect.Y = rect.Y + m_computedClip[0];
		clipRect.Width = rect.Width - m_computedClip[1] - m_computedClip[3];
		clipRect.Height = rect.Height - m_computedClip[2] - m_computedClip[0];

		pGraphics->IntersectClip(clipRect);
	}

	//mat = mat * gmMatrix3::scale(rect.Width/viewPort.Width, rect.Height/viewPort.Height);
	pGraphics->ScaleTransform(rect.Width/viewPort.Width, rect.Height/viewPort.Height);

	/*
	Gdiplus::Matrix matrix(
		(float)mat[0][0], (float)mat[0][1],
		(float)mat[1][0], (float)mat[1][1],
		(float)mat[2][0], (float)mat[2][1]);
		*/

//	pGraphics->MultiplyTransform(&matrix);

	RenderChildren(pC, pGraphics, 1/*markerScaleX*/, 1/*markerScaleY*/);

	pGraphics->Restore(state);
#endif
}

}	// LSVG
}
