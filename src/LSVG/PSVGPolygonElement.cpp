#include "stdafx.h"
#include "LSVG2.h"
#include "SVGPolygonElement.h"
#include "PSVGPolygonElement.h"

//#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

PSVGPolygonElement::PSVGPolygonElement(SVGPolygonElement* element) : PSVGShapeElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGPolygonElement::GetLocalAnimatedMatrix() const
{
	SVGPolygonElement* psvgElement = static_cast<SVGPolygonElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	if (m_animateMotionMatrix)
	{
		matrix = *matrix * *m_animateMotionMatrix;
	}

	return matrix;
}
*/

//virtual
LDraw::RectD PSVGPolygonElement::GetScreenBBox()
{
	SVGPolygonElement* psvgElement = static_cast<SVGPolygonElement*>(m_pNode);

	ASSERT(0);
	ISVGTransformable* transformable = NULL;//m_pNode;

	SVGMatrix* matrix = transformable->getScreenCTM();

	LDraw::RectD bbox;
//	bbox = psvgElement->m_points->m_animVal->CalculateBoundingBox(matrix->m_matrix);

	return bbox;
}

//virtual
void PSVGPolygonElement::CalculateBounds()
{
	SVGPolygonElement* psvgElement = static_cast<SVGPolygonElement*>(m_pNode);

	LDraw::Matrix3d* matrix = GetLocalAnimatedMatrix();

	m_bounds = psvgElement->points_attr().m_animated.m_animVal->CalculateBoundingBox(NULL);
	m_xbounds = psvgElement->points_attr().m_animated.m_animVal->CalculateBoundingBox(matrix->m_matrix);

	/*
	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_points->m_animated->m_animVal->m_value->DrawToPath(&GraphicsPathF, true);

	LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

	LDraw::RectF bounds;
	GraphicsPathF.GetBounds(&bounds, NULL, &pen);

	m_expandedBBox = LDraw::RectD(bounds.X, bounds.Y, bounds.Width, bounds.Height);
*/
	m_expandedBBox = m_bounds;
#if 0

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
		m_filterRect = m_expandedBBox;
	}

	CalculateScale(matrix);
#endif
}

//virtual
void PSVGPolygonElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGPolygonElement* psvgElement = static_cast<SVGPolygonElement*>(m_pNode);

	double fillOpacity = m_computedFillOpacity;
	double strokeOpacity = m_computedStrokeOpacity;
	float strokeWidth = m_computedStrokeWidth;

	Gui::Brush* fillBrush = GetBrush(renderContext, &m_computedFill, m_pFillElement, fillOpacity, scaleX, scaleY);
	Gui::Brush* strokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

	Gui::Geometry* geometry =  psvgElement->get_animatedGeometry();

	if (fillBrush)
	{
		renderContext->FillGeometry(geometry, fillBrush);
	}

	if (strokeBrush)
	{
		renderContext->StrokeGeometry(geometry, strokeBrush, strokeWidth);
	}

#if 0
	ID2D1PathGeometry* geometry = psvgElement->points_attr().m_animated.m_animVal->GetD2DGeometry();
	if (geometry)
	{

		if (fillBrush)
		{
			renderContext->FillGeometry(geometry, fillBrush);
			/*
			renderContext->GetRT()->m_spRT->FillGeometry(geometry, fillBrush, NULL);

			fillBrush->Release();
			*/
		}

		if (strokeBrush)
		{
			renderContext->StrokeGeometry(geometry, fillBrush, strokeWidth);
			/*
			float strokeWidth = m_computedStrokeWidth;

			renderContext->GetRT()->m_spRT->DrawGeometry(geometry, strokeBrush, strokeWidth);

			strokeBrush->Release();
			*/
		}

		geometry->Release();
	}
#if 0
	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

//	LDraw::FillModeAlternate,
//  FillModeWinding

#if 0
	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_points->m_animated->m_animVal->m_value->DrawToPath(&GraphicsPathF, true);
#endif
	SVGPointListData* pointListData = psvgElement->m_animatedPoints->m_p;
	unsigned int npoints = pointListData->m_items.size();
	LDraw::PointF* points = new LDraw::PointF[npoints];
	for (unsigned int i = 0; i < npoints; i++)
	{
		points[i].X = float(pointListData->m_items[i]->m_x);
		points[i].Y = float(pointListData->m_items[i]->m_y);
	}

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
		pGraphics->FillPolygon(pFillBrush, points, npoints);
//		pGraphics->FillPath(pFillBrush, &GraphicsPathF);
	}

#if 0
	if (pStrokeBrush != NULL)
	{
		LDraw::Pen* pPen = GetPen(pStrokeBrush);
		if (pPen != NULL)
		{
			pGraphics->DrawPath(pPen, &GraphicsPathF);
		//	delete pPen;
		}
	}
#endif

	delete[] points;
#endif
#endif
}

//virtual
bool PSVGPolygonElement::HitTest(double x, double y, int pointerEvents)
{
	return true;
	/*
	SVGPolygonElement* psvgElement = static_cast<SVGPolygonElement*>(m_pNode);

	LDraw::GraphicsPathF GraphicsPathF(m_computedFillRule == FillRule_nonzero? LDraw::FillModeWinding: LDraw::FillModeAlternate);
	psvgElement->m_points->m_animVal->DrawToPath(&GraphicsPathF, true);

	bool bOver = HitTestPath(this, &GraphicsPathF, x, y, pointerEvents);

	return bOver;
	*/
}

}	// Web
}
