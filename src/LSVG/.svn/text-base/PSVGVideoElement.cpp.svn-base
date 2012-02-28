#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGVideoElement.h"
#include "SVGVideoElement.h"

//#include "PSVGFilterElement.h"
//#include "SVGSVGElement.h"

namespace System
{
namespace Web
{

gm::RectD GetViewBoxRect(gm::RectD viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectD viewPort);

PSVGVideoElement::PSVGVideoElement(SVGVideoElement* element) : PSVGElement(element)
{
}

//virtual
gm::Matrix3d* PSVGVideoElement::GetLocalAnimatedMatrix()
{
	SVGVideoElement* psvgElement = static_cast<SVGVideoElement*>(m_pNode);
	return psvgElement->transform_attr()->m_animVal->consolidateToMatrix();
}

//virtual
gm::RectD PSVGVideoElement::GetScreenBBox()
{
	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

	return bbox;
}

//virtual
void PSVGVideoElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	SVGVideoElement* psvgElement = static_cast<SVGVideoElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewPort = pViewportElement->GetViewBox();

	SVGLength* xLength = psvgElement->m_x->m_animVal;
	SVGLength* yLength = psvgElement->m_y->m_animVal;
	SVGLength* widthLength = psvgElement->m_width->m_animVal;
	SVGLength* heightLength = psvgElement->m_height->m_animVal;

	if (xLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedX = (xLength->get_valueInSpecifiedUnits() * viewPort.Width)/100;
	}
	else
	{
		m_computedX = xLength->get_value();
	}

	if (yLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedY = (yLength->get_valueInSpecifiedUnits() * viewPort.Height)/100;
	}
	else
	{
		m_computedY = yLength->get_value();
	}

	if (widthLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedWidth = (widthLength->get_valueInSpecifiedUnits() * viewPort.Width)/100;
	}
	else
	{
		m_computedWidth = widthLength->get_value();
	}

	if (heightLength->get_unitType() == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedHeight = (heightLength->get_valueInSpecifiedUnits() * viewPort.Height)/100;
	}
	else
	{
		m_computedHeight = heightLength->get_value();
	}

	m_bounds.X = m_computedX;
	m_bounds.Y = m_computedY;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	m_expandedBBox = m_bounds;

	gm::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

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
}

//virtual
void PSVGVideoElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGVideoElement* psvgElement = static_cast<SVGVideoElement*>(m_pNode);

	ASSERT(0);
#if 0
	RectD viewBox = RectD(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);

	if (psvgElement->m_pMedia && psvgElement->m_pMedia->m_pVideoFilter)
	{
		if (psvgElement->m_pCurrentInterval && psvgElement->m_pCurrentInterval->m_bActive)
		{
			SVGPreserveAspectRatioAlignType align = psvgElement->m_preserveAspectRatio->m_animated->m_baseVal->m_value->get_align();
			SVGMeetOrSliceType meetOrSlice = psvgElement->m_preserveAspectRatio->m_animated->m_baseVal->m_value->get_meetOrSlice();

			RectD viewPort;

			LDraw::Bitmap* pGdipBitmap;
			psvgElement->m_pMedia->m_pVideoFilter->GetBitmap(&pGdipBitmap);

			if (pGdipBitmap)
			{
				LDraw::GraphicsState state = pGraphics->Save();

				if (m_computedImageRendering == 1)	// optimizeSpeed
					pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighSpeed);
				else
					pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias/*8x8*/);

				viewPort = RectD(0, 0, pGdipBitmap->GetWidth(), pGdipBitmap->GetHeight());

				RectD rect = GetViewBoxRect(viewBox, psvgElement->m_preserveAspectRatio->m_animated->m_baseVal->m_value, viewPort);

				if (m_computedOverflowX == Overflow_hidden || m_computedOverflowX == Overflow_scroll)
				{
					RectD clipRect;
					clipRect.X = viewBox.X + m_computedClip[3];
					clipRect.Y = viewBox.Y + m_computedClip[0];
					clipRect.Width = viewBox.Width - m_computedClip[1] - m_computedClip[3];
					clipRect.Height = viewBox.Height - m_computedClip[2] - m_computedClip[0];

					pGraphics->IntersectClip(clipRect);
				}

				{
					CColorProfile* pProfile = NULL;

					if (m_computedColorProfileType == CSS_STRING)
					{
						pProfile = m_pWindow->GetColorProfileByName(m_computedColorProfileValue);
					}

					if (pProfile)
					{
						LDraw::Bitmap* pBitmap = new LDraw::Bitmap(
							pGdipBitmap->GetWidth(), pGdipBitmap->GetHeight(),
							PixelFormat32bppARGB);

						if (pBitmap)
						{
							LDraw::BitmapData srcdata;
							if (pGdipBitmap->LockBits(
								&LDraw::Rect(0, 0, pGdipBitmap->GetWidth(), pGdipBitmap->GetHeight()),
								LDraw::ImageLockModeRead,
								PixelFormat32bppARGB, &srcdata) == 0)
							{
								LDraw::BitmapData dstdata;
								if (pBitmap->LockBits(
									&LDraw::Rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
									LDraw::ImageLockModeWrite,
									PixelFormat32bppARGB, &dstdata) == 0)
								{
									HTRANSFORM hTransform = pProfile->GetProfile2sRGB();
									if (hTransform)
									{
										TranslateBitmapBits(hTransform,
											srcdata.Scan0, BM_xRGBQUADS, srcdata.Width, srcdata.Height, srcdata.Stride,
											dstdata.Scan0, BM_xRGBQUADS, dstdata.Stride,
											NULL, 0);

										pBitmap->UnlockBits(&dstdata);

										LDraw::ImageAttributes imageAttributes;

										pGraphics->DrawImage(pBitmap,
											rect,	// dest rect
											(float)viewPort.X, (float)viewPort.Y, (float)viewPort.Width, (float)viewPort.Height,	// source rect
											LDraw::UnitPixel, &imageAttributes, NULL, NULL);
									}
								}

								pGdipBitmap->UnlockBits(&srcdata);
							}

							delete pBitmap;
						}
					}
					else	// No color profile, draw directly
					{
						LDraw::Bitmap* pBitmap = pGdipBitmap;
						LDraw::ImageAttributes imageAttributes;

						pGraphics->DrawImage(pBitmap,
							rect,	// dest rect
							(float)viewPort.X, (float)viewPort.Y, (float)viewPort.Width, (float)viewPort.Height,	// source rect
							LDraw::UnitPixel, &imageAttributes, NULL, NULL);
					}
				}

				pGraphics->Restore(state);
			}
		}
	}
#endif
}

//virtual
bool PSVGVideoElement::HitTest(double x, double y, int pointerEvents)
{
	SVGVideoElement* psvgElement = static_cast<SVGVideoElement*>(m_pNode);

	bool bOver = false;

	if (pointerEvents != PointerEvents_none)
	{
		if (m_bounds.Contains(x, y))
		{
			Graphics::Bitmap* pGdipBitmap = NULL;

			if (psvgElement->m_pMedia && psvgElement->m_pMedia->m_pVideoFilter)
			{
				psvgElement->m_pMedia->m_pVideoFilter->GetBitmap(&pGdipBitmap);
			}

			switch (pointerEvents)
			{
			case PointerEvents_visiblePainted:
				{
					if (m_computedVisibility == Visibility_visible)
					{
						if (pGdipBitmap)
						{
							Graphics::Color pixelColor;
							ASSERT(0);
#if 0
							pGdipBitmap->GetPixel((INT)(x-m_bounds.X), (INT)(y-m_bounds.Y), &pixelColor);
#endif

							bOver = pixelColor.GetAlpha() > 0;
						}
					}
				}
				break;

			case PointerEvents_visibleFill:
			case PointerEvents_visibleStroke:
			case PointerEvents_visible:
				{
					if (m_computedVisibility == Visibility_visible)
					{
						bOver = true;
					}
				}
				break;

			// Same as above, except ignore visiblity
			case PointerEvents_painted:
				{
					if (pGdipBitmap)
					{
						Graphics::Color pixelColor;
						ASSERT(0);
#if 0
						pGdipBitmap->GetPixel((INT)(x-m_bounds.X), (INT)(y-m_bounds.Y), &pixelColor);
#endif
						bOver = pixelColor.GetAlpha() > 0;
					}
				}
				break;

			case PointerEvents_fill:
			case PointerEvents_stroke:
			case PointerEvents_all:
				{
					bOver = true;
				}
				break;
			}
		}
	}

	return bOver;
}

}	// LSVG
}
