#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGImageElement.h"
#include "SVGImageElement.h"

namespace System
{
namespace Web
{

gm::RectD GetViewBoxRect(gm::RectD viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectD viewPort);
gm::Matrix3f GetViewBoxMatrix(gm::RectD rect, gm::RectD viewPort);

gm::RectF GetViewBoxRect(gm::RectF viewBox, gm::RectF viewPort, SVGPreserveAspectRatioAlignType align, SVGMeetOrSliceType meetOrSlice)
{
	gm::RectF rect;

	if (align == SVG_PRESERVEASPECTRATIO_NONE)
	{
		rect.X = viewBox.X;
		rect.Y = viewBox.Y;
		rect.Width = viewBox.Width;
		rect.Height = viewBox.Height;
	}
	else
	{
		// Preserve aspect ratio

		if (meetOrSlice == SVG_MEETORSLICE_SLICE)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height < viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else if (meetOrSlice == SVG_MEETORSLICE_MEET)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height > viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else
			ASSERT(0);

		switch (align)
		{
		case SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case SVG_PRESERVEASPECTRATIO_XMINYMID:
		case SVG_PRESERVEASPECTRATIO_XMINYMAX:
			{
				rect.X = viewBox.X;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case SVG_PRESERVEASPECTRATIO_XMIDYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width)/2;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMAXYMIN:
		case SVG_PRESERVEASPECTRATIO_XMAXYMID:
		case SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width);
			}
			break;
		}

		switch (align)
		{
	///////////////////////////////////////////////////
		case SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case SVG_PRESERVEASPECTRATIO_XMAXYMIN:
			{
				rect.Y = viewBox.Y;
			}
			break;

		case SVG_PRESERVEASPECTRATIO_XMINYMID:
		case SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case SVG_PRESERVEASPECTRATIO_XMAXYMID:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height)/2;
			}
			break;

	////////////////////////////////////////////////
		case SVG_PRESERVEASPECTRATIO_XMINYMAX:
		case SVG_PRESERVEASPECTRATIO_XMIDYMAX:
		case SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height);
			}
			break;
		}
	}

	return rect;
}

gm::RectF GetViewBoxRect(gm::RectF viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectF viewPort)
{
	SVGPreserveAspectRatioAlignType align = preserveAspectRatio->get_align();
	SVGMeetOrSliceType meetOrSlice = preserveAspectRatio->get_meetOrSlice();

	return GetViewBoxRect(viewBox, viewPort, align, meetOrSlice);
}

gm::RectF GetViewBoxRect(SVGRectViewBox* _viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectF viewPort)
{
	return GetViewBoxRect(gm::RectF(_viewBox->m_x, _viewBox->m_y, _viewBox->m_width, _viewBox->m_height), preserveAspectRatio, viewPort);
}

PSVGImageElement::PSVGImageElement(SVGImageElement* element) : PSVGTransformableElement(element)
{
}

/*
//virtual
LDraw::Matrix3d* PSVGImageElement::GetLocalAnimatedMatrix()
{
	SVGImageElement* psvgElement = static_cast<SVGImageElement*>(m_pNode);
	return psvgElement->m_transform->m_animVal->consolidateToMatrix();
}
*/

//virtual
gm::RectD PSVGImageElement::GetScreenBBox()
{
	gm::RectD bbox;
	PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

	return bbox;
}

//virtual
void PSVGImageElement::CalculateBounds()
{
	PSVGElement::FreeCachedBitmap();

	SVGImageElement* psvgElement = static_cast<SVGImageElement*>(m_pNode);

	gm::Matrix3d* matrix = GetLocalAnimatedMatrix();

	PSVGElement* pViewportElement = GetViewportElement();
	ASSERT(pViewportElement);

	gm::RectD viewPort = pViewportElement->GetViewBox();

	SVGLength* xLength = psvgElement->x_attr()->m_animVal;
	SVGLength* yLength = psvgElement->y_attr()->m_animVal;
	SVGLength* widthLength = psvgElement->width_attr()->m_animVal;
	SVGLength* heightLength = psvgElement->height_attr()->m_animVal;

	m_computedX = LengthToUserUnits(xLength, viewPort.Width);
	m_computedY = LengthToUserUnits(yLength, viewPort.Height);
	m_computedWidth = LengthToUserUnits(widthLength, viewPort.Width);
	m_computedHeight = LengthToUserUnits(heightLength, viewPort.Height);

	/*
	if (xLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedX = (xLength->m_valueInSpecifiedUnits * viewPort.Width)/100;
	}
	else
	{
		m_computedX = xLength->m_value;
	}

	if (yLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedY = (yLength->m_valueInSpecifiedUnits * viewPort.Height)/100;
	}
	else
	{
		m_computedY = yLength->m_value;
	}

	if (widthLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedWidth = (widthLength->m_valueInSpecifiedUnits * viewPort.Width)/100;
	}
	else
	{
		m_computedWidth = widthLength->m_value;
	}

	if (heightLength->m_unitType == SVG_LENGTHTYPE_PERCENTAGE)
	{
		m_computedHeight = (heightLength->m_valueInSpecifiedUnits * viewPort.Height)/100;
	}
	else
	{
		m_computedHeight = heightLength->m_value;
	}
	*/

	m_bounds.X = m_computedX;
	m_bounds.Y = m_computedY;
	m_bounds.Width = m_computedWidth;
	m_bounds.Height = m_computedHeight;

	m_expandedBBox = m_bounds;

	gm::GetTransformRectBoundingBox(matrix, m_bounds, &m_xbounds);

	/*
	m_filterRect.X = m_bounds.X;
	m_filterRect.Y = m_bounds.Y;
	m_filterRect.Width = m_bounds.Width;
	m_filterRect.Height = m_bounds.Height;
	*/

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
		m_filterRect.X = m_bounds.X;
		m_filterRect.Y = m_bounds.Y;
		m_filterRect.Width = m_bounds.Width;
		m_filterRect.Height = m_bounds.Height;
		*/
	}

//	m_expandedBBox = m_filterRect;//m_appearance->m_expandedRect;

	CalculateScale(/*m_expandedBBox,*/ matrix);

	//pMatrix->Release();
}

Graphics::Bitmap* PSVGImageElement::GetBitmap(Gui::RenderContext* renderContext, int m_scaledWidth, int m_scaledHeight, double m_scaleX, double m_scaleY)
{
	SVGImageElement* psvgElement = static_cast<SVGImageElement*>(m_pNode);

	CHTMLWindow* pSVGDocumentView = NULL;
	CImage* pImage = NULL;

	if (pSVGDocumentView == NULL)
		pImage = psvgElement->GetImage();
	else
		pImage = NULL;

	return pImage->m_bitmap;
}

//virtual
void PSVGImageElement::Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors)
{
	SVGImageElement* psvgElement = static_cast<SVGImageElement*>(m_pNode);

	gm::RectF viewBox = gm::RectF(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);

	CHTMLWindow* pSVGDocumentView;
	CImage* pImage;

	pSVGDocumentView = psvgElement->GetSVGDocumentView();
	if (pSVGDocumentView == NULL)
		pImage = psvgElement->GetImage();
	else
		pImage = NULL;

	if ((pSVGDocumentView/* && pSVGDocumentView->m_pSVGElement*/) ||
		(pImage && pImage->GetLoadStatus() >= 0))
	{
	//	LDraw::GraphicsState state = pGraphics->Save();

		SVGPreserveAspectRatioAlignType align = psvgElement->preserveAspectRatio_attr()->m_baseVal->get_align();
		SVGMeetOrSliceType meetOrSlice = psvgElement->preserveAspectRatio_attr()->m_baseVal->get_meetOrSlice();

		gm::RectF viewPort;

		if (pSVGDocumentView)
		{
#if 0
			SVGSVGElement* psvgsvgElement = static_cast<SVGSVGElement*>(pSVGDocumentView->m_pSVGElement->m_pNode);

			if (psvgsvgElement->m_viewBox->m_specified)
			{
				viewPort.X = psvgsvgElement->m_viewBox->m_animated->m_animVal->m_value->m_x;
				viewPort.Y = psvgsvgElement->m_viewBox->m_animated->m_animVal->m_value->m_y;
				viewPort.Width = psvgsvgElement->m_viewBox->m_animated->m_animVal->m_value->m_width;
				viewPort.Height = psvgsvgElement->m_viewBox->m_animated->m_animVal->m_value->m_height;
			}
			else
			{
			// TODO Untested
				viewPort.X = 0;
				viewPort.Y = 0;
				viewPort.Width = viewBox.Width;
				viewPort.Height = viewBox.Height;
			}
#endif
		}
		else if (pImage)
		{
			Graphics::Bitmap* pBitmap = pImage->m_bitmap;

			viewPort = gm::RectF(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
		}

		gm::RectF rect = GetViewBoxRect(viewBox, psvgElement->preserveAspectRatio_attr()->m_baseVal, viewPort);

#if 0
		if (m_computedOverflowX == Overflow_hidden || m_computedOverflowX == Overflow_scroll)
		{
			LDraw::RectD clipRect;
			clipRect.X = viewBox.X + m_computedClip[3];
			clipRect.Y = viewBox.Y + m_computedClip[0];
			clipRect.Width = viewBox.Width - m_computedClip[1] - m_computedClip[3];
			clipRect.Height = viewBox.Height - m_computedClip[2] - m_computedClip[0];

			pGraphics->IntersectClip(clipRect);
		}
#endif


		if (pSVGDocumentView)
		{
#if 0
			LDraw::Matrix3f matrix = w3c::GetViewBoxMatrix(rect, viewPort);

			//pGraphics->TranslateTransform(rect.X, rect.Y);

			/*
			LDraw::Matrix3f matrix(
				(float)mat[0][0], (float)mat[0][1],
				(float)mat[1][0], (float)mat[1][1],
				(float)mat[2][0], (float)mat[2][1]);
				*/

			pGraphics->MultiplyTransform(&matrix);

			double magnify = 1;
			//graphics.ScaleTransform(magnify, magnify);
			pSVGDocumentView->m_pSVGElement->Render4(NULL, NULL, pGraphics, magnify, magnify, false, false);
#endif
		}
		else
		{
			/*
			if (m_computedImageRendering == 1)	// optimizeSpeed
				pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighSpeed);
			else
				pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
		*/

			CColorProfile* pProfile = NULL;

			if (m_computedColorProfileType == CSS_STRING)
			{
#if 0
				pProfile = m_pWindow->GetColorProfileByName(m_computedColorProfileValue);
#endif
			}

#if 0
			if (pProfile)
			{
				LDraw::Bitmap* pBitmap = new LDraw::Bitmap(
					pImage->m_gdipImage->GetWidth(), pImage->m_gdipImage->GetHeight(),
					PixelFormat32bppARGB);

				if (pBitmap)
				{
					LDraw::BitmapData srcdata;
					if (pImage->m_gdipImage->LockBits(
						&LDraw::Rect(0, 0, pImage->m_gdipImage->GetWidth(), pImage->m_gdipImage->GetHeight()),
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
									LDraw::RectF(float(rect.X), float(rect.Y), float(rect.Width), float(rect.Height)),	// dest rect
									(float)viewPort.X, (float)viewPort.Y, (float)viewPort.Width, (float)viewPort.Height,	// source rect
									LDraw::UnitPixel, &imageAttributes, NULL, NULL);
							}
						}

						pImage->m_gdipImage->UnlockBits(&srcdata);
					}

					delete pBitmap;
				}
			}
			else	// No color profile, draw directly
#endif
			{

				if (false)
				{
				Graphics::Bitmap* pBitmap = pImage->m_bitmap;
			//	LDraw::ImageAttributes imageAttributes;

			//	Gui::RenderContext rt = *pC->m_rt;

				float opacity = (float)m_computedOpacity;

				GL::DrawBitmapArgs args(GL::ColorMatrix(	1, 0, 0, 0,
																0, 1, 0, 0,
																0, 0, 1, 0,
																0, 0, 0, opacity));

				GL::Direct10::s.Render(renderContext->GetRT(), pBitmap,
					rect,	// dest rect
					viewPort,	// source rect
					&args
					);
				}
				else
				{
					float opacity = (float)m_computedOpacity;

					renderContext->DrawBitmap(pImage->m_bitmap, rect, opacity);
				}
#if 0
				pGraphics->DrawImage(pBitmap,
					rect,	// dest rect
					(float)viewPort.X, (float)viewPort.Y, (float)viewPort.Width, (float)viewPort.Height	// source rect
					/*LDraw::UnitPixel, &imageAttributes, NULL, NULL*/);
#endif
			}
		}

	//	pGraphics->PopTransform();
	//	pGraphics->Restore(state);
	}
}

//virtual
bool PSVGImageElement::HitTest(double x, double y, int pointerEvents)
{
//	ASSERT(0);
	SVGImageElement* psvgElement = static_cast<SVGImageElement*>(m_pNode);

	bool bOver = false;
#if 0

	if (pointerEvents != PointerEvents_none)
	{
		if (m_bounds.Contains(x, y))
		{
			CImage* pImage = psvgElement->GetImage();
			LDraw::Bitmap* pGdipBitmap = NULL;

			if (pImage && pImage->m_gdipImage && pImage->m_gdipImage->GetLastStatus() == 0)
				pGdipBitmap = pImage->m_gdipImage;

			switch (pointerEvents)
			{
			case PointerEvents_visiblePainted:
				{
					if (m_computedVisibility == Visibility_visible)
					{
						if (pGdipBitmap)
						{
							LDraw::Color pixelColor;
							pGdipBitmap->GetPixel((INT)(x-m_bounds.X), (INT)(y-m_bounds.Y), &pixelColor);

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
						bOver = TRUE;
					}
				}
				break;

			// Same as above, except ignore visiblity
			case PointerEvents_painted:
				{
					if (pGdipBitmap)
					{
						LDraw::Color pixelColor;
						pGdipBitmap->GetPixel((INT)(x-m_bounds.X), (INT)(y-m_bounds.Y), &pixelColor);

						bOver = pixelColor.GetAlpha() > 0;
					}
				}
				break;

			case PointerEvents_fill:
			case PointerEvents_stroke:
			case PointerEvents_all:
				{
					bOver = TRUE;
				}
				break;
			}
		}
	}
#endif
	return bOver;
}

}	// Web
}	// System
