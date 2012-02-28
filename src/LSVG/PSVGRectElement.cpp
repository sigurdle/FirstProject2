#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGRectElement.h"
#include "SVGRectElement.h"

//#include "PSVGMaskElement.h"
//#include "PSVGFilterElement.h"

namespace System
{
namespace Web
{

PSVGRectElement::PSVGRectElement(SVGRectElement* element) : PSVGShapeElement(element)
{
	m_pGdipGraphicsPathF = NULL;
}

PSVGRectElement::~PSVGRectElement()
{
	if (m_pGdipGraphicsPathF)
	{
		delete m_pGdipGraphicsPathF;
		m_pGdipGraphicsPathF = NULL;
	}
}

	/*
//virtual
LDraw::Matrix3d* PSVGRectElement::GetLocalAnimatedMatrix()
{
	SVGRectElement* psvgElement = static_cast<SVGRectElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	if (m_animateMotionMatrix)
	{
		matrix = *matrix * *m_animateMotionMatrix;
	}

	return matrix;
}
*/

//virtual
LDraw::RectD PSVGRectElement::GetScreenBBox()
{
	SVGRectElement* psvgElement = static_cast<SVGRectElement*>(m_pNode);

	LDraw::RectD bbox;

	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);
		*/


	ASSERT(0);
#if 0
		gmMatrix3 matrix = m_pWindow->svgGetScreenCTM(this);	// TODO?: Should be GetScreenCTM2() ?
		bbox = CalcRoundRectBBox(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy, matrix);
#endif
		//PSVGElement::GetScreenBBox(seglist, &bbox);

		/*
		seglist->Release();
	}
	*/

	return bbox;
}

//virtual
void PSVGRectElement::CalculateBounds()
{
//	PSVGElement::FreeCachedBitmap();

	SVGRectElement* psvgElement = static_cast<SVGRectElement*>(m_pNode);

	LDraw::Matrix3d* matrix = GetLocalAnimatedMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	LDraw::RectD viewBox = pViewportElement->GetViewBox();

	ISVGLength* xLength = psvgElement->get_x()->get_animVal();
	ISVGLength* yLength = psvgElement->get_y()->get_animVal();
	ISVGLength* widthLength = psvgElement->get_width()->get_animVal();
	ISVGLength* heightLength = psvgElement->get_height()->get_animVal();
	ISVGLength* rxLength = psvgElement->get_rx()->get_animVal();
	ISVGLength* ryLength = psvgElement->get_ry()->get_animVal();

	m_computedX = LengthToUserUnits(xLength, viewBox.Width);
	m_computedY = LengthToUserUnits(yLength, viewBox.Height);
	m_computedWidth = LengthToUserUnits(widthLength, viewBox.Width);
	m_computedHeight = LengthToUserUnits(heightLength, viewBox.Height);
	m_computedRx = LengthToUserUnits(rxLength, viewBox.Width);
	m_computedRy = LengthToUserUnits(ryLength, viewBox.Height);

	// TODO specified or animated ??

	if (!psvgElement->get_rxAttr()->get_specified())
	{
		if (psvgElement->get_ryAttr()->get_specified())
		{
			m_computedRx = m_computedRy;
		}
	}

	if (!psvgElement->get_ryAttr()->get_specified())
	{
		if (psvgElement->get_rxAttr()->get_specified())
		{
			m_computedRy = m_computedRx;
		}
	}

	m_bounds.X = m_computedX;
	m_bounds.Y = m_computedY;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	if (m_pGdipGraphicsPathF)
	{
		delete m_pGdipGraphicsPathF;
		m_pGdipGraphicsPathF = NULL;
	}

//	m_xbounds = LDraw::CalcRoundRectBBox(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy, matrix);

//	m_pGdipGraphicsPathF = new LDraw::GraphicsPathF;
//	m_pGdipGraphicsPathF->AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);

//	LDraw::RectF bounds;
//	m_pGdipGraphicsPathF->GetBounds(&bounds, NULL/*LDraw::Matrix3f()*/, pen);
	m_expandedBBox.X = m_bounds.X - m_computedStrokeWidth/2;
	m_expandedBBox.Y = m_bounds.Y - m_computedStrokeWidth/2;
	m_expandedBBox.Width = m_bounds.Width + m_computedStrokeWidth;
	m_expandedBBox.Height = m_bounds.Height + m_computedStrokeWidth;

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

		/*
		LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

		m_filterRect.X = m_expandedBBox.X;
		m_filterRect.Y = m_expandedBBox.Y;
		m_filterRect.Width = m_expandedBBox.Width;
		m_filterRect.Height = m_expandedBBox.Height;
		*/
	}

	//m_filterRect = m_expandedBBox;// ??

	if (m_pMaskElement)
	{
		LDraw::RectD maskRegion = m_pMaskElement->CalculateMaskRegion(this);

		LDraw::RectD::Intersect(m_expandedBBox, maskRegion, m_filterRect);
	}
	else
	{
	//	m_expandedBBox = m_filterRect;
	}

	CalculateScale(matrix);
#endif
}

//virtual
void PSVGRectElement::Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGRectElement* psvgElement = static_cast<SVGRectElement*>(m_pNode);

	//if (m_pGdipGraphicsPathF)
	{
		float fillOpacity = m_computedFillOpacity;
		float strokeOpacity = m_computedStrokeOpacity;

		if (!bOffscreen)
		{
			fillOpacity *= m_computedOpacity;
			strokeOpacity *= m_computedOpacity;
		}

//		ID2D1Brush* pFillBrush = GetFillBrush(fillOpacity, scaleX, scaleY);
//		ID2D1Brush* pStrokeBrush = GetD2DStrokeBrush(strokeOpacity, scaleX, scaleY);

		Gui::Brush* fillBrush = GetBrush(renderContext, &m_computedFill, m_pFillElement, fillOpacity, scaleX, scaleY);
		Gui::Brush* strokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

		LDraw::RectF rect(float(m_bounds.GetLeft()), float(m_bounds.GetTop()), float(m_bounds.GetRight()), float(m_bounds.GetBottom()));

		if (fillBrush != NULL)
		{
			renderContext->FillRectangle(rect, fillBrush);

//			ASSERT(0);
#if 0
			D2D1_ROUNDED_RECT roundedRect =
			{
				float(m_bounds.GetLeft()), float(m_bounds.GetTop()), float(m_bounds.GetRight()), float(m_bounds.GetBottom()),
				float(m_computedRx), float(m_computedRy)
			};

			renderContext->GetRT()->m_spRT->FillRoundedRectangle(roundedRect, pFillBrush);
		//	pGraphics->FillRectangle(pFillBrush, float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));
			//pGraphics->FillPath(pFillBrush, m_pGdipGraphicsPathF);

			pFillBrush->Release();
#endif
		}

		if (strokeBrush)
		{
			float strokeWidth = m_computedStrokeWidth;
			renderContext->StrokeRectangle(rect, strokeBrush, strokeWidth);
		}

#if 0
		if (pStrokeBrush != NULL)
		{
			LDraw::Pen* pPen = GetPen(pStrokeBrush);
			if (pPen != NULL)
			{
				pGraphics->DrawRectangle(pPen, float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));
			}

#if 0
			LDraw::Pen* pPen = GetPen(pStrokeBrush);
			if (pPen != NULL)
			{
				pGraphics->DrawPath(pPen, m_pGdipGraphicsPathF);
			}
#endif
		}
#endif
	}
}

//virtual
void PSVGRectElement::RenderPath(LDraw::GraphicsPathF* pGraphicsPathF)
{
	pGraphicsPathF->AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);
	
	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);

		DrawPathSegList(seglist, pGraphicsPathF, NULL);

		seglist->Release();
	}
	*/

}

//virtual
bool PSVGRectElement::HitTest(double x, double y, int pointerEvents)
{
	bool bOver = false;

	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);
*/
		LDraw::GraphicsPathF GraphicsPathF;
//		DrawPathSegList(seglist, &GraphicsPathF, NULL);
		GraphicsPathF.AddRoundRect(m_computedX, m_computedY, m_computedWidth, m_computedHeight, m_computedRx, m_computedRy);

		bOver = HitTestPath(this, &GraphicsPathF, x, y, pointerEvents);

		/*
		seglist->Release();
	}*/

	return bOver;
}

}	// Web
}
