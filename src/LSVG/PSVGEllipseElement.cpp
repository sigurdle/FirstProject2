#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGEllipseElement.h"
#include "SVGEllipseElement.h"

namespace System
{
namespace Web
{

#if 0
void PSVGElement::Mask(LDraw::Bitmap* pBitmap, LDraw::RectF filterRect, double scaleX, double scaleY, LDraw::SmoothingMode smoothingMode)
{
	LDraw::Bitmap* pMask = GetOpacityMaskBitmap(filterRect, scaleX, scaleY, smoothingMode);
	if (pMask)
	{
		ProcessMaskBitmap(pMask, pBitmap);
		delete pMask;
	}
}

LDraw::Bitmap* PSVGElement::GetOpacityMaskBitmap(LDraw::RectF filterRect, double scaleX, double scaleY, LDraw::SmoothingMode smoothingMode)
{
	LDraw::Bitmap* pMask = NULL;

	if (m_pMaskElement)
	{
		pMask = new LDraw::Bitmap((int)ceil(filterRect.Width*scaleX), (int)ceil(filterRect.Height*scaleY), PixelFormat32bppARGB);
		if (pMask)
		{
			LDraw::Graphics graphics(pMask);
			graphics.SetSmoothingMode(smoothingMode);

			graphics.ScaleTransform((float)scaleX, (float)scaleY);
			graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);

			m_pMaskElement->Render(&graphics, scaleX, scaleY);
		}
	}

	return pMask;
}

void PSVGElement::ProcessMaskBitmap(LDraw::Bitmap* pMask, LDraw::Bitmap* pBitmap)
{
	ASSERT(pMask->GetWidth() == pBitmap->GetWidth());
	ASSERT(pMask->GetHeight() == pBitmap->GetHeight());

	LDraw::BitmapData bitmapData;
	pBitmap->LockBits(
		&LDraw::Rect(0, 0, pMask->GetWidth(), pMask->GetHeight()),
		LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
		PixelFormat32bppARGB,
		&bitmapData);

	LDraw::BitmapData maskData;
	pMask->LockBits(
		&LDraw::Rect(0, 0, pMask->GetWidth(), pMask->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppARGB,
		&maskData);

	for (UINT y = 0; y < bitmapData.Height; y++)
	{
		ARGBPixel* bitmapPixel = (ARGBPixel*)((BYTE*)bitmapData.Scan0+bitmapData.Stride*y);
		ARGBPixel* maskPixel = (ARGBPixel*)((BYTE*)maskData.Scan0+maskData.Stride*y);

		for (UINT x = 0; x < bitmapData.Width; x++)
		{
			int maskOpacity = /*255 -*/ (int)maskPixel->alpha*(((int)maskPixel->red + maskPixel->green + maskPixel->blue)/3)/255;

			bitmapPixel->alpha = bitmapPixel->alpha*maskOpacity/255;

			bitmapPixel++;
			maskPixel++;
		}
	}

	pBitmap->UnlockBits(&bitmapData);
	pMask->UnlockBits(&maskData);
}
#endif

////////////////////////////////////////////////////////////////////////
// CPSVGEllipseElement

PSVGEllipseElement::PSVGEllipseElement(SVGEllipseElement* element) : PSVGShapeElement(element)
{
}

PSVGEllipseElement::~PSVGEllipseElement()
{
	if (m_pFilterElement)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_pFilterElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pFilterElement->m_referencingElements.RemoveAt(pos);

		m_pFilterElement = NULL;
#endif
	}
}

/*
//virtual
LDraw::Matrix3d* PSVGEllipseElement::GetLocalAnimatedMatrix()
{
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	LDraw::Matrix3d* matrix = psvgElement->m_transform->m_animVal->consolidateToMatrix();
	if (m_animateMotionMatrix)
	{
		matrix = *matrix * *m_animateMotionMatrix;
	}

	return matrix;
}
*/

//virtual
gm::RectD PSVGEllipseElement::GetScreenBBox()
{
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	gm::RectD bbox;

	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();
		*/

		//seglist->AddEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy);

	ASSERT(0);
#if 0
		gmMatrix3 matrix = m_pWindow->svgGetScreenCTM(this);	// TODO?: Should be GetScreenCTM2() ?
		bbox = CalcEllipseBBox(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height, matrix);
#endif

//		PSVGElement::GetScreenBBox(seglist, &bbox);

		/*
		seglist->Release();
	}
	*/

	return bbox;
}

//virtual
void PSVGEllipseElement::CalculateBounds()
{
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	gm::Matrix3d* matrix = psvgElement->transform_attr()->m_animVal->consolidateToMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewBox = pViewportElement->GetViewBox();

	/*
	SVGLength* cxLength = psvgElement->m_cx->m_animated->m_animVal->m_value;
	SVGLength* cyLength = psvgElement->m_cy->m_animated->m_animVal->m_value;
	SVGLength* rxLength = psvgElement->m_rx->m_animated->m_animVal->m_value;
	SVGLength* ryLength = psvgElement->m_ry->m_animated->m_animVal->m_value;
	*/

	ISVGLength* cxLength = psvgElement->get_cx()->get_animVal();
	ISVGLength* cyLength = psvgElement->get_cy()->get_animVal();
	ISVGLength* rxLength = psvgElement->get_rx()->get_animVal();
	ISVGLength* ryLength = psvgElement->get_ry()->get_animVal();

	m_computedCx = LengthToUserUnits(cxLength, viewBox.Width);
	m_computedCy = LengthToUserUnits(cyLength, viewBox.Height);
	m_computedRx = LengthToUserUnits(rxLength, viewBox.Width);
	m_computedRy = LengthToUserUnits(ryLength, viewBox.Height);

	/*
	if (cxLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedCx = (cxLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedCx = cxLength->m_value;
	}

	if (cyLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedCy = (cyLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedCy = cyLength->m_value;
	}

	if (rxLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedRx = (rxLength->m_valueInSpecifiedUnits * viewBox.Width)/100;
	}
	else
	{
		m_computedRx = rxLength->m_value;
	}

	if (ryLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedRy = (ryLength->m_valueInSpecifiedUnits * viewBox.Height)/100;
	}
	else
	{
		m_computedRy = ryLength->m_value;
	}
	*/

	m_bounds.X = m_computedCx - m_computedRx;
	m_bounds.Y = m_computedCy - m_computedRy;
	m_bounds.Width = m_computedRx * 2;
	m_bounds.Height = m_computedRy * 2;

	m_xbounds = gm::CalcEllipseBBox(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height, matrix);

//	LDraw::GraphicsPathF GraphicsPathF;
//	GraphicsPathF.AddEllipse(float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));

//	LDraw::Pen pen(LDraw::Color(0,0,0), (float)m_computedStrokeWidth);

	/*
	LDraw::RectF bounds;
	GraphicsPathF.GetBounds(&bounds, NULL, &pen);
	*/
	m_expandedBBox.X = m_bounds.X - m_computedStrokeWidth/2;
	m_expandedBBox.Y = m_bounds.Y - m_computedStrokeWidth/2;
	m_expandedBBox.Width = m_bounds.Width + m_computedStrokeWidth;
	m_expandedBBox.Height = m_bounds.Height + m_computedStrokeWidth;
}

//virtual
void PSVGEllipseElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	double fillOpacity = m_computedFillOpacity;
	double strokeOpacity = m_computedStrokeOpacity;

	Gui::Brush* fillBrush = GetBrush(renderContext, &m_computedFill, m_pFillElement, fillOpacity, scaleX, scaleY);
	Gui::Brush* strokeBrush = GetBrush(renderContext, &m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

	if (fillBrush)
	{
		renderContext->FillEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy, fillBrush);
	}

	if (strokeBrush)
	{
		float strokeWidth = m_computedStrokeWidth;
		renderContext->DrawEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy, strokeBrush, strokeWidth);
	}

#if 0
	D2D1_ELLIPSE ellipse;
	ellipse.point.x = m_computedCx;
	ellipse.point.y = m_computedCy;
	ellipse.radiusX = m_computedRx;
	ellipse.radiusY = m_computedRy;
	if (fillBrush)
	{
		renderContext->GetRT()->m_spRT->FillEllipse(ellipse, fillBrush);
		fillBrush->Release();
	}

	if (strokeBrush)
	{
	//	LDraw::Pen* pPen = GetPen(pStrokeBrush);
		float strokeWidth = m_computedStrokeWidth;
		ID2D1StrokeStyle* strokeStyle = NULL;
		renderContext->GetRT()->m_spRT->DrawEllipse(ellipse, strokeBrush, strokeWidth, strokeStyle);
		strokeBrush->Release();
	}
#endif

	return;
#if 0
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

//	__release<LDraw::GraphicsPathF> GraphicsPathF = new LDraw::GraphicsPathF;
//	GraphicsPathF->AddEllipse(float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));
	//DrawPathSegList(seglist, &GraphicsPathF, NULL);

	double fillOpacity = m_computedFillOpacity;
	double strokeOpacity = m_computedStrokeOpacity;

	if (!bOffscreen)
	{
		fillOpacity *= m_computedOpacity;
		strokeOpacity *= m_computedOpacity;
	}

	LDraw::Brush* pFillBrush = GetBrush(&m_computedFill, m_pFillElement, fillOpacity, scaleX, scaleY);
	LDraw::Brush* pStrokeBrush = GetBrush(&m_computedStroke, m_pStrokeElement, strokeOpacity, scaleX, scaleY);

	if (pFillBrush != NULL)
	{
		pGraphics->FillEllipse(pFillBrush, float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));
	}

	if (pStrokeBrush != NULL)
	{
		LDraw::Pen* pPen = GetPen(pStrokeBrush);
		if (pPen != NULL)
		{
			pGraphics->DrawEllipse(pPen, float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));
		}
	}
#endif
}

//virtual
void PSVGEllipseElement::RenderPath(Gui::Geometry* pGraphicsPathF)
{
	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy);

		DrawPathSegList(seglist, pGraphicsPathF, NULL);
		*/
		pGraphicsPathF->AddEllipse(float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));

		/*
		seglist->Release();
	}
	*/
}

//virtual
bool PSVGEllipseElement::HitTest(double x, double y, int pointerEvents)
{
	SVGEllipseElement* psvgElement = static_cast<SVGEllipseElement*>(m_pNode);

	bool bOver = false;

	x -= m_computedCx;
	y -= m_computedCy;

	// Scale it into a circle
	x /= m_computedRx;
	y /= m_computedRy;

	if ((x*x + y*y) <= 1)
	{
		bOver = true;
	}

	return bOver;

#if 0
	/*
	CComObject<CLSVGPathSegList>* seglist;
	CComObject<CLSVGPathSegList>::CreateInstance(&seglist);
	if (seglist)
	{
		seglist->AddRef();

		seglist->AddEllipse(m_computedCx, m_computedCy, m_computedRx, m_computedRy);
		*/

		LDraw::GraphicsPathF GraphicsPathF;
	//	DrawPathSegList(seglist, &GraphicsPathF, NULL);
		GraphicsPathF.AddEllipse(float(m_bounds.X), float(m_bounds.Y), float(m_bounds.Width), float(m_bounds.Height));

		bOver = HitTestPath(this, &GraphicsPathF, x, y, pointerEvents);

		/*
		seglist->Release();
	}
	*/

	return bOver;
#endif
}

}	// w3c
}
