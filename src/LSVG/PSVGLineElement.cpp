#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGLineElement.h"
#include "SVGLineElement.h"

namespace System
{
namespace Web
{

void SetPathSegListToLine(SVGPathSegList* seglist, double x1, double y1, double x2, double y2);

PSVGLineElement::PSVGLineElement(SVGLineElement* element) : PSVGShapeElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGLineElement::GetLocalAnimatedMatrix()
{
	SVGLineElement* psvgElement = static_cast<SVGLineElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
gm::RectD PSVGLineElement::GetScreenBBox()
{
	SVGLineElement* psvgElement = static_cast<SVGLineElement*>(m_pNode);

	gm::RectD bbox;

	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();
		*/

	ASSERT(0);

#if 0
		gmMatrix3 matrix = m_pWindow->svgGetScreenCTM(this);	// TODO?: Should be GetScreenCTM2() ?

		bbox = CalcLineBBox(m_computedX1, m_computedY1, m_computedX2, m_computedY2, matrix);

	//	seglist->AddEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy);
//		SetPathSegListToLine(seglist, m_computedX1, m_computedY1, m_computedX2, m_computedY2);

//		PSVGElement::GetScreenBBox(seglist, &bbox);

//		seglist->Release();
//	}
#endif

	return bbox;
}

//virtual
void PSVGLineElement::CalculateBounds()
{
//	PSVGElement::FreeCachedBitmap();

	SVGLineElement* psvgElement = static_cast<SVGLineElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewBox = pViewportElement->GetViewBox();

	ISVGLength* x1Length = psvgElement->get_x1()->get_animVal();
	ISVGLength* y1Length = psvgElement->get_y1()->get_animVal();
	ISVGLength* x2Length = psvgElement->get_x2()->get_animVal();
	ISVGLength* y2Length = psvgElement->get_y2()->get_animVal();

	m_computedX1 = LengthToUserUnits(x1Length, viewBox.Width);
	m_computedY1 = LengthToUserUnits(y1Length, viewBox.Height);
	m_computedX2 = LengthToUserUnits(x2Length, viewBox.Width);
	m_computedY2 = LengthToUserUnits(y2Length, viewBox.Height);

	/*
	if (x1Length->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedX1 = (x1Length->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedX1 = x1Length->m_value;
	}

	if (y1Length->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedY1 = (y1Length->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedY1 = y1Length->m_value;
	}

	if (x2Length->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedX2 = (x2Length->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedX2 = x2Length->m_value;
	}

	if (y2Length->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedY2 = (y2Length->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedY2 = y2Length->m_value;
	}
	*/

	m_bounds.X = m_computedX1;
	m_bounds.Y = m_computedY1;
	m_bounds.Width = m_computedX2-m_computedX1;
	m_bounds.Height = m_computedY2-m_computedY1;

	m_xbounds = LDraw::CalcLineBBox(m_computedX1, m_computedY1, m_computedX2, m_computedY2, matrix);

	/*
	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();
	GetMaskElement();
	GetClipPathElement();
	*/

	LDraw::GraphicsPathF path;// = new LDraw::GraphicsPathF;
	path.AddMove(float(m_computedX1), float(m_computedY1));
	path.AddLine(float(m_computedX2), float(m_computedY2));

	gm::RectF bounds;
	LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);
	path.GetBounds(&bounds, NULL, &pen);
	m_expandedBBox = gm::RectD(bounds.X, bounds.Y, bounds.Width, bounds.Height);

	/*
	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		m_filterRect = m_expandedBBox;
	}

	CalculateScale(matrix);
	*/
}

//virtual
void PSVGLineElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGLineElement* psvgElement = static_cast<SVGLineElement*>(m_pNode);

//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	double strokeOpacity = m_computedStrokeOpacity;

	if (!bOffscreen)
	{
		strokeOpacity *= m_computedOpacity;
	}

	Gui::Brush* strokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

	if (strokeBrush != NULL)
	{
		float strokeWidth = m_computedStrokeWidth;

		gm::PointF point0 = gm::PointF(m_computedX1, m_computedY1);
		gm::PointF point1 = gm::PointF(m_computedX2, m_computedY2);

		renderContext->DrawLine(point0, point1, strokeBrush, strokeWidth);
		/*
		ID2D1StrokeStyle* strokeStyle = NULL;

		D2D1_POINT_2F point0 = D2D1::Point2F(m_computedX1, m_computedY1);
		D2D1_POINT_2F point1 = D2D1::Point2F(m_computedX2, m_computedY2);

		renderContext->GetRT()->m_spRT->DrawLine(point0, point1, strokeBrush, strokeWidth, strokeStyle);
		*/
		/*
		LDraw::Pen* pPen = GetPen(pStrokeBrush);
		if (pPen != NULL)
		{
//			pGraphics->DrawLine(pPen, m_computedX1, m_computedY1, m_computedX2, m_computedY2);
		}
		*/
	}
}

//virtual
bool PSVGLineElement::HitTest(double x, double y, int pointerEvents)
{
	bool bOver = false;

	return false;
	// TODO

	Gui::Geometry* GraphicsPathF;
#if 0
	ASSERT(0);
	GraphicsPathF.AddLine((float)m_computedX1, (float)m_computedY1, (float)m_computedX2, (float)m_computedY2);
#endif
	bOver = HitTestPath(this, GraphicsPathF, x, y, pointerEvents);

	return bOver;
}

}	// LSVG
}
