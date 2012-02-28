#include "stdafx.h"
#include "LSVG2.h"

#include "SVGMaskElement.h"

#include "PSVGMaskElement.h"

namespace System
{
namespace Web
{

PSVGMaskElement::PSVGMaskElement(SVGMaskElement* element) : PSVGElement(element)
{
}

void ProcessMaskBitmap(Graphics::Bitmap* pMask, Graphics::Bitmap* pBitmap)
{
	ASSERT(0);
#if 0
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
#endif
}

gm::RectD PSVGMaskElement::CalculateMaskRegion(PSVGElement* pReferencingElement)
{
	ASSERT(pReferencingElement != NULL);

	SVGMaskElement* psvgElement = static_cast<SVGMaskElement*>(m_pNode);

	SVGLength* xLength = psvgElement->m_x->m_animVal;
	SVGLength* yLength = psvgElement->m_y->m_animVal;
	SVGLength* widthLength = psvgElement->m_width->m_animVal;
	SVGLength* heightLength = psvgElement->m_height->m_animVal;

	gm::RectD rect;

	if (psvgElement->m_maskUnits->m_animated->m_animVal->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
	{
		rect = pReferencingElement->m_bounds;
	}
	else	// SVG_UNIT_TYPE_USERSPACEONUSE
	{
		rect = pReferencingElement->GetViewportElement()->GetViewBox();
	}

	gm::RectD maskRegion;

	if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
		maskRegion.X = rect.X + (xLength->get_valueInSpecifiedUnits() * rect.Width/100);
	else
		maskRegion.X = xLength->get_value();

	if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
		maskRegion.Y = rect.Y + (yLength->get_valueInSpecifiedUnits() * rect.Height/100);
	else
		maskRegion.Y = yLength->get_value();

	if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
		maskRegion.Width = (widthLength->get_valueInSpecifiedUnits() * rect.Width/100);
	else
		maskRegion.Width = widthLength->get_value();

	if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
		maskRegion.Height = (heightLength->get_valueInSpecifiedUnits() * rect.Height/100);
	else
		maskRegion.Height = heightLength->get_value();

	return maskRegion;
}

void PSVGMaskElement::Mask(PSVGElement* pReferencingElement, Graphics::Bitmap* pBitmap, LDraw::RectF filterRect, double scaleX, double scaleY)
{
	ASSERT(pReferencingElement != NULL);

	SVGMaskElement* psvgElement = static_cast<SVGMaskElement*>(m_pNode);

	/*
	SVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
	SVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	SVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	SVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

	RectD rect;

	if (psvgElement->m_maskUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
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
*/
	gm::RectD rect = pReferencingElement->m_expandedBBox;

	Graphics::Bitmap* pMask = NULL;

	pMask = new Graphics::Bitmap((int)ceil(rect/*filterRect*/.Width*scaleX), (int)ceil(rect/*filterRect*/.Height*scaleY), LDraw::PixelFormat_t::RGBAP_32);
	if (pMask)
	{
		ASSERT(0);
#if 0
		UI::Graphics graphics(new LDraw::GraphicsO(pMask));
//		graphics.SetSmoothingMode(smoothingMode);

		if (psvgElement->m_maskContentUnits->m_animated->m_animVal->m_value->m_value == SVG_UNIT_TYPE_OBJECTBOUNDINGBOX)
		{
			graphics.ScaleTransform((float)scaleX, (float)scaleY);
			graphics.ScaleTransform((float)pReferencingElement->m_bounds.Width, (float)pReferencingElement->m_bounds.Height);
			//graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
			graphics.TranslateTransform(float(pReferencingElement->m_bounds.X), float(pReferencingElement->m_bounds.Y));
			graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
		}
		else
		{
			graphics.ScaleTransform((float)scaleX, (float)scaleY);
		//	graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);
			graphics.TranslateTransform((float)-rect.X, (float)-rect.Y);
			//graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);
		}

		Render(NULL/*pC*/, &graphics, scaleX, scaleY);

		ProcessMaskBitmap(pMask, pBitmap);

		delete pMask;
#endif
	}

#if 0
	LDraw::Bitmap* pMask = GetOpacityMaskBitmap(rect/*filterRect*/, scaleX, scaleY);
	if (pMask)
	{
		ProcessMaskBitmap(pMask, pBitmap);
		delete pMask;
	}
#endif
}

#if 0
LDraw::Bitmap* CPSVGMaskElement::GetOpacityMaskBitmap(LDraw::RectF filterRect, double scaleX, double scaleY)
{
	LDraw::Bitmap* pMask = NULL;

	pMask = new LDraw::Bitmap((int)ceil(filterRect.Width*scaleX), (int)ceil(filterRect.Height*scaleY), PixelFormat32bppARGB);
	if (pMask)
	{
		LDraw::Graphics graphics(pMask);
//		graphics.SetSmoothingMode(smoothingMode);

		graphics.ScaleTransform((float)scaleX, (float)scaleY);
		graphics.TranslateTransform((float)-filterRect.X, (float)-filterRect.Y);

		Render(&graphics, scaleX, scaleY);
	}

	return pMask;
}
#endif

//virtual
void PSVGMaskElement::CalculateBounds()
{
	m_bounds = CalculateRenderableChildrenBoundingBox();

//////// ??

	{
		double minx = 9999999;
		double miny = 9999999;
		double maxx = -9999999;
		double maxy = -9999999;

		ASSERT(0);
#if 0
		UPOSITION pos = m_childListRender.GetHeadPosition();
		while (pos)
		{
			PSVGElement* pElement = (PSVGElement*)m_childListRender.GetNext(pos);

			RectD objectExpandedRect = pElement->m_expandedBBox;
		//	object->getExpandedBBox(&objectExpandedRect);

			//CComQIPtr<ILSVGTransformable> objectTransformable = pElement->m_pNode;
			//ASSERT(objectTransformable != NULL);

			gmMatrix3 elementMatrix = pElement->GetLocalAnimatedMatrix();
			//if (pElementMatrix)
			{
				RectD objectExpandedRectX;
				GetTransformRectBoundingBox(elementMatrix, objectExpandedRect, &objectExpandedRectX);

			//	pElementMatrix->Release();

				minx = min(objectExpandedRectX.X, minx);
				miny = min(objectExpandedRectX.Y, miny);
				maxx = max(objectExpandedRectX.X+objectExpandedRectX.Width, maxx);
				maxy = max(objectExpandedRectX.Y+objectExpandedRectX.Height, maxy);
			}
			//else
			//	ASSERT(0);	// hm..
		}
#endif
		m_filterRect.X = minx;
		m_filterRect.Y = miny;
		m_filterRect.Width = maxx-minx;
		m_filterRect.Height = maxy-miny;
	}
#if 0
	GetTransformRectBoundingBox(pMatrix->m_matrix, &m_bounds, &m_xbounds);
#endif

	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;

/////// ??
}

// virtual
void PSVGMaskElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*pGraphics->GetSmoothingMode()*/);

	RenderChildren(pC, renderContext, scaleX, scaleY);

	PSVGElement::Render4(pC, pBitmap, renderContext, scaleX, scaleY, bOffscreen, bDrawBehaviors);
}

}	// Web
}	// System
