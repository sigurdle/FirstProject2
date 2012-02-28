#include "stdafx.h"
#include "LSVG2.h"

#include "SVGClipPathElement.h"
#include "PSVGClipPathElement.h"

namespace System
{
namespace Web
{

PSVGClipPathElement::PSVGClipPathElement(SVGClipPathElement* element) : PSVGElement(element)
{
}

// virtual
void PSVGClipPathElement::RecalculateParentBounds()
{
	CalculateBounds();
	PSVGElement::RecalculateParentBounds();

	ASSERT(0);
#if 0

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

#if 0

void ProcessClipPathBitmap(Gdiplus::Bitmap* pClipPath, Gdiplus::Bitmap* pBitmap)
{
	ASSERT(pClipPath->GetWidth() == pBitmap->GetWidth());
	ASSERT(pClipPath->GetHeight() == pBitmap->GetHeight());

	Gdiplus::BitmapData bitmapData;
	pBitmap->LockBits(
		&Gdiplus::Rect(0, 0, pClipPath->GetWidth(), pClipPath->GetHeight()),
		Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite,
		PixelFormat32bppARGB,
		&bitmapData);

	Gdiplus::BitmapData ClipPathData;
	pClipPath->LockBits(
		&Gdiplus::Rect(0, 0, pClipPath->GetWidth(), pClipPath->GetHeight()),
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB,
		&ClipPathData);

	for (UINT y = 0; y < bitmapData.Height; y++)
	{
		ARGBPixel* bitmapPixel = (ARGBPixel*)((BYTE*)bitmapData.Scan0+bitmapData.Stride*y);
		ARGBPixel* ClipPathPixel = (ARGBPixel*)((BYTE*)ClipPathData.Scan0+ClipPathData.Stride*y);

		for (UINT x = 0; x < bitmapData.Width; x++)
		{
			int ClipPathOpacity = /*255 -*/ (int)ClipPathPixel->alpha*(((int)ClipPathPixel->red + ClipPathPixel->green + ClipPathPixel->blue)/3)/255;

			bitmapPixel->alpha = bitmapPixel->alpha*ClipPathOpacity/255;

			bitmapPixel++;
			ClipPathPixel++;
		}
	}

	pBitmap->UnlockBits(&bitmapData);
	pClipPath->UnlockBits(&ClipPathData);
}

RectD CPSVGClipPathElement::CalculateClipPathRegion(PSVGElement* pReferencingElement)
{
	ASSERT(pReferencingElement != NULL);

	CLSVGClipPathElement* psvgElement = static_cast<CLSVGClipPathElement*>(m_pNode);

	CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
	CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	RectD rect;

	if (psvgElement->m_ClipPathUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		rect = pReferencingElement->m_bounds;
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		rect = pReferencingElement->GetViewportElement()->GetViewBox();
	}

	RectD ClipPathRegion;

	if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		ClipPathRegion.X = rect.X + (xLength->m_valueInSpecifiedUnits * rect.Width/100);
	else
		ClipPathRegion.X = xLength->m_value;

	if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		ClipPathRegion.Y = rect.Y + (yLength->m_valueInSpecifiedUnits * rect.Height/100);
	else
		ClipPathRegion.Y = yLength->m_value;

	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		ClipPathRegion.Width = (widthLength->m_valueInSpecifiedUnits * rect.Width/100);
	else
		ClipPathRegion.Width = widthLength->m_value;

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
		ClipPathRegion.Height = (heightLength->m_valueInSpecifiedUnits * rect.Height/100);
	else
		ClipPathRegion.Height = heightLength->m_value;

	return ClipPathRegion;
}

void CPSVGClipPathElement::ClipPath(PSVGElement* pReferencingElement, Gdiplus::Bitmap* pBitmap, Gdiplus::RectF filterRect, double scaleX, double scaleY)
{
	ASSERT(pReferencingElement != NULL);

	CLSVGClipPathElement* psvgElement = static_cast<CLSVGClipPathElement*>(m_pNode);

	CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
	CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	RectD rect;

	if (psvgElement->m_ClipPathUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			rect.X = pReferencingElement->m_bounds.X + (xLength->m_valueInSpecifiedUnits * pReferencingElement->m_bounds.Width/100);
		else
			rect.X = xLength->m_value;

		if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			rect.Y = pReferencingElement->m_bounds.Y + (yLength->m_valueInSpecifiedUnits * pReferencingElement->m_bounds.Height/100);
		else
			rect.Y = yLength->m_value;

		if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			rect.Width = pReferencingElement->m_bounds.X + (widthLength->m_valueInSpecifiedUnits * pReferencingElement->m_bounds.Width/100);
		else
			rect.Width = widthLength->m_value;

		if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
			rect.Height = pReferencingElement->m_bounds.Y + (heightLength->m_valueInSpecifiedUnits * pReferencingElement->m_bounds.Height/100);
		else
			rect.Height = heightLength->m_value;
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		ASSERT(0);
	}

	Gdiplus::Bitmap* pClipPath = NULL;

	pClipPath = new Gdiplus::Bitmap((int)ceil(rect/*filterRect*/.Width*scaleX), (int)ceil(rect/*filterRect*/.Height*scaleY), PixelFormat32bppPARGB);
	if (pClipPath)
	{
		Gdiplus::Graphics graphics(pClipPath);
//		graphics.SetSmoothingMode(smoothingMode);

		graphics.ScaleTransform((float)scaleX, (float)scaleY);
	//	graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);
		graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
		//graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);

		Render(&graphics, scaleX, scaleY);

		ProcessClipPathBitmap(pClipPath, pBitmap);

		delete pClipPath;
	}

#if 0
	Gdiplus::Bitmap* pClipPath = GetOpacityClipPathBitmap(rect/*filterRect*/, scaleX, scaleY);
	if (pClipPath)
	{
		ProcessClipPathBitmap(pClipPath, pBitmap);
		delete pClipPath;
	}
#endif
}

#if 0
Gdiplus::Bitmap* CPSVGClipPathElement::GetOpacityClipPathBitmap(Gdiplus::RectF filterRect, double scaleX, double scaleY)
{
	Gdiplus::Bitmap* pClipPath = NULL;

	pClipPath = new Gdiplus::Bitmap((int)ceil(filterRect.Width*scaleX), (int)ceil(filterRect.Height*scaleY), PixelFormat32bppARGB);
	if (pClipPath)
	{
		Gdiplus::Graphics graphics(pClipPath);
//		graphics.SetSmoothingMode(smoothingMode);

		graphics.ScaleTransform((float)scaleX, (float)scaleY);
		graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);

		Render(&graphics, scaleX, scaleY);
	}

	return pClipPath;
}
#endif

#endif

//virtual
void PSVGClipPathElement::CalculateBounds()
{
	m_bounds = CalculateRenderableChildrenBoundingBox();
#if 0
//////// ??

	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		UPOSITION pos = m_childListRender.GetHeadPosition();
		while (pos)
		{
			PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

			RectD objectExpandedRect = pElement->m_expandedBBox;
		//	object->getExpandedBBox(&objectExpandedRect);

			//CComQIPtr<ILSVGTransformable> objectTransformable = pElement->m_pNode;
			//ASSERT(objectTransformable != NULL);

			CComObject<CLSVGMatrix>* pElementMatrix = pElement->GetLocalAnimatedMatrix();
			if (pElementMatrix)
			{
				RectD objectExpandedRectX;
				GetTransformRectBoundingBox(pElementMatrix->m_matrix, &objectExpandedRect, &objectExpandedRectX);

				pElementMatrix->Release();

				minx = min(objectExpandedRectX.X, minx);
				miny = min(objectExpandedRectX.Y, miny);
				maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}
			else
				ASSERT(0);	// hm..
		}

		m_filterRect.X = minx;
		m_filterRect.Y = miny;
		m_filterRect.Width = maxx-minx;
		m_filterRect.Height = maxy-miny;
	}
#if 0
	LDraw::GetTransformRectBoundingBox(pMatrix->m_matrix, &m_bounds, &m_xbounds);
#endif

	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;
#endif
/////// ??
}

#if 0
//virtual
void CPSVGClipPathElement::Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY)
{
	Gdiplus::Graphics* pGraphics = (Gdiplus::Graphics*)dwGraphics;

	pGraphics->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);

	UPOSITION pos = m_childListRender.GetHeadPosition();
	while (pos)
	{
		PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

		pElement->RenderPath(pGraphics/*, scaleX, scaleY*/);//Render(dwBitmap, dwGraphics, scaleX, scaleY);
	}

//	RenderChildren(pGraphics, scaleX, scaleY);

//	PSVGElement::Render2(dwBitmap, dwGraphics, scaleX, scaleY);
}
#endif

}	// LSVG
}
