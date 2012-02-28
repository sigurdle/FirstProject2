#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGCircleElement.h"
#include "SVGCircleElement.h"

//#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

PSVGCircleElement::PSVGCircleElement(SVGCircleElement* element) : PSVGShapeElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGCircleElement::GetLocalAnimatedMatrix()
{
	SVGCircleElement* psvgElement = static_cast<SVGCircleElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
LDraw::RectD PSVGCircleElement::GetScreenBBox()
{
	SVGCircleElement* psvgElement = static_cast<SVGCircleElement*>(m_pNode);

	LDraw::RectD bbox;

	ASSERT(0);
#if 0
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddEllipse(m_computedCx, m_computedCy, m_computedR, m_computedR);

		PSVGElement::GetScreenBBox(seglist, &bbox);

		seglist->Release();
	}
#endif

	return bbox;
}

//virtual
void PSVGCircleElement::CalculateBounds()
{
//	PSVGElement::FreeCachedBitmap();

	SVGCircleElement* psvgElement = static_cast<SVGCircleElement*>(m_pNode);

	LDraw::Matrix3d* pMatrix = psvgElement->transform_attr()->m_animVal->consolidateToMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	LDraw::RectD viewBox = pViewportElement->GetViewBox();

	ISVGLength* cxLength = psvgElement->get_cx()->get_animVal();
	ISVGLength* cyLength = psvgElement->get_cy()->get_animVal();
	ISVGLength* rLength = psvgElement->get_r()->get_animVal();

	if (cxLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedCx = (cxLength->get_valueInSpecifiedUnits() * viewBox.Width)/100;
	}
	else
	{
		m_computedCx = cxLength->get_value();
	}

	if (cyLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedCy = (cyLength->get_valueInSpecifiedUnits() * viewBox.Height)/100;
	}
	else
	{
		m_computedCy = cyLength->get_value();
	}

	//sqrt((actual-width)**2 + (actual-height)**2))/sqrt(2)
	double viewBoxSize = sqrt(viewBox.Width*viewBox.Width + viewBox.Height*viewBox.Height)/M_SQRT2;

	m_computedR = LengthToUserUnits(rLength, viewBoxSize);

#if 0
	if (rLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{

		m_computedR = (rLength->m_valueInSpecifiedUnits * viewBoxSize)/100;
	}
	else
	{
		m_computedR = rLength->m_value;
	}
#endif

	m_bounds.X = m_computedCx-m_computedR;
	m_bounds.Y = m_computedCy-m_computedR;
	m_bounds.Width = m_computedR*2;
	m_bounds.Height = m_computedR*2;

//	LDraw::GraphicsPathF GraphicsPathF;
//	GraphicsPathF.AddEllipse(m_computedCx-m_computedR, m_computedCy-m_computedR, m_computedR*2, m_computedR*2);
	//DrawPathSegList(seglist, &GraphicsPathF, NULL);

//	LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

	//	LDraw::RectF bounds;
	//	GraphicsPathF.GetBounds(&bounds, NULL, &pen);
	//	m_expandedBBox = LDraw::RectD(bounds.X, bounds.Y, bounds.Width, bounds.Height);
	m_expandedBBox.X = m_bounds.X - m_computedStrokeWidth/2;
	m_expandedBBox.Y = m_bounds.Y - m_computedStrokeWidth/2;
	m_expandedBBox.Width = m_bounds.Width + m_computedStrokeWidth;
	m_expandedBBox.Height = m_bounds.Height + m_computedStrokeWidth;

	/*
	GetFillUriElement();
	GetStrokeUriElement();
	GetFilterElement();

	if (m_pFilterElement)
	{
		m_filterRect = m_pFilterElement->CalculateFilterRegion(this);
	}
	else
	{
		m_filterRect = m_expandedBBox;
	}

	CalculateScale(pMatrix);
	*/
}

//virtual
void PSVGCircleElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGCircleElement* pElement = static_cast<SVGCircleElement*>(m_pNode);

//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

//	LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF;
//	path->AddEllipse(m_computedCx-m_computedR, m_computedCy-m_computedR, m_computedR*2, m_computedR*2);

	Gui::Brush* pFillBrush = GetBrush(renderContext, &m_computedFill, m_pFillElement, m_computedFillOpacity, scaleX, scaleY);
	Gui::Brush* pStrokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, m_computedStrokeOpacity, scaleX, scaleY);

	if (pFillBrush != NULL)
	{
		renderContext->FillEllipse(m_computedCx, m_computedCy, m_computedR, m_computedR, pFillBrush);
	}

	if (pStrokeBrush != NULL)
	{
		float strokeWidth = m_computedStrokeWidth;
		renderContext->DrawEllipse(m_computedCx, m_computedCy, m_computedR, m_computedR, pStrokeBrush, strokeWidth);
	}
}

//virtual
void PSVGCircleElement::RenderPath(Gui::Geometry* pGraphicsPathF)
{
//	LDraw::GraphicsPathF* path = new LDraw::GraphicsPathF;
	pGraphicsPathF->AddEllipse(m_computedCx-m_computedR, m_computedCy-m_computedR, m_computedR*2, m_computedR*2);

	//ASSERT(0);
#if 0
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddEllipse(m_computedCx, m_computedCy, m_computedR, m_computedR);

		DrawPathSegList(seglist, pGraphicsPathF, NULL);

		seglist->Release();
	}
#endif
}

//virtual
bool PSVGCircleElement::HitTest(double x, double y, int pointerEvents)
{
	bool bOver = false;

	x -= m_computedCx;
	y -= m_computedCy;

	if ((x*x + y*y) <= m_computedR*m_computedR)
	{
		bOver = true;
	}

	return bOver;

#if 0

	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddEllipse(m_computedCx, m_computedCy, m_computedR, m_computedR);

		LDraw::GraphicsPathF GraphicsPathF;
		DrawPathSegList(seglist, &GraphicsPathF, NULL);

		bOver = CPSVGBasicShape::HitTest(this, &GraphicsPathF, x, y, pointerEvents);

		seglist->Release();
	}
#endif
	return bOver;
}

}	// Web
}
