#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGPolylineElement.h"
#include "SVGPolylineElement.h"

#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

PSVGPolylineElement::PSVGPolylineElement(SVGPolylineElement* element) : PSVGShapeElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGPolylineElement::GetLocalAnimatedMatrix()
{
	SVGPolylineElement* psvgElement = static_cast<SVGPolylineElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
gm::RectD PSVGPolylineElement::GetScreenBBox()
{
	SVGPolylineElement* psvgElement = static_cast<SVGPolylineElement*>(m_pNode);

	/*
	CComQIPtr<ILSVGTransformable> transformable = m_pNode;

	CComPtr<ILSVGMatrix> matrix;
	transformable->getScreenCTM(&matrix);
	*/

	gm::Matrix3d* matrix = GetScreenCTM();
	//matrix = matrix * m_

	LDraw::RectD bbox;
	ASSERT(0);
	//bbox = psvgElement->m_points->m_animated->m_animVal->m_value->CalculateBoundingBox(matrix->m_matrix);

	return bbox;
}

//virtual
void PSVGPolylineElement::CalculateBounds()
{
	SVGPolylineElement* psvgElement = static_cast<SVGPolylineElement*>(m_pNode);

	LDraw::Matrix3d* matrix = GetLocalAnimatedMatrix();

	ASSERT(0);
#if 0

	m_bounds = psvgElement->m_points->m_animated->m_animVal->m_value->CalculateBoundingBox(NULL);
	m_xbounds = psvgElement->m_points->m_animated->m_animVal->m_value->CalculateBoundingBox(matrix->m_matrix);

	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_animatedPoints->DrawToPath(&GraphicsPathF, true);

	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();
	GetMaskElement();
	GetClipPathElement();

	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

		LDraw::RectF bounds;
		GraphicsPathF.GetBounds(&bounds, NULL, pen);

		m_filterRect.X = bounds.X;
		m_filterRect.Y = bounds.Y;
		m_filterRect.Width = bounds.Width;
		m_filterRect.Height = bounds.Height;
	}

	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;

	CalculateScale(matrix);
#endif
}

//virtual
void PSVGPolylineElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	ASSERT(0);
#if 0
	SVGPolylineElement* psvgElement = static_cast<SVGPolylineElement*>(m_pNode);

	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_points->m_animated->m_animVal->m_value->DrawToPath(&GraphicsPathF, false);

	double fillOpacity = m_computedFillOpacity;
	double strokeOpacity = m_computedStrokeOpacity;

	if (!bOffscreen)
	{
		fillOpacity *= m_computedOpacity;
		strokeOpacity *= m_computedOpacity;
	}

	LDraw::Brush* pFillBrush = GetFillBrush(fillOpacity, scaleX, scaleY);
	LDraw::Brush* pStrokeBrush = GetStrokeBrush(strokeOpacity, scaleX, scaleY);

	if (pFillBrush != NULL)
	{
		pGraphics->FillPath(pFillBrush, &GraphicsPathF);
	}

	if (pStrokeBrush != NULL)
	{
		LDraw::Pen* pPen = GetPen(pStrokeBrush);
		if (pPen != NULL)
		{
			pGraphics->DrawPath(pPen, &GraphicsPathF);
		}
	}
#endif
}

//virtual
bool PSVGPolylineElement::HitTest(double x, double y, int pointerEvents)
{
	SVGPolylineElement* psvgElement = static_cast<SVGPolylineElement*>(m_pNode);

	return true;
	/*

	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_points->m_animated->m_animVal->m_value->DrawToPath(&GraphicsPathF, false);

	bool bOver = HitTestPath(this, &GraphicsPathF, x, y, pointerEvents);

	return bOver;
	*/
}

}	// w3c
}
