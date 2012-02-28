#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEImageElement.h"
#include "SVGFEImageElement.h"

//#include "../LXML/PImage.h"

namespace System
{
namespace Web
{

gm::RectD GetViewBoxRect(gm::RectD viewBox, SVGPreserveAspectRatio* preserveAspectRatio, gm::RectD viewPort);

PSVGFEImageElement::PSVGFEImageElement(SVGFEImageElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEImageElement::GetInCount()
{
	return 0;
}

//virtual
Gui::CEffect* PSVGFEImageElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEImageElement* psvgElement = static_cast<CLSVGFEImageElement*>(m_pNode);

	LDraw::Graphics out(outImage);

	CImage* pImage = psvgElement->GetImage();

//	LDraw::RectF dstRect(0, 0, outImage->GetWidth(), outImage->GetHeight());
//	RectD viewBox = RectD(0, 0, outImage->GetWidth(), outImage->GetHeight());
	RectD viewBox = uRect;//RectD(m_bounds.X, m_bounds.Y, m_bounds.Width, m_bounds.Height);

	if (pImage)
	{

		RectD viewPort;

		LDraw::Image* pGdipImage = pImage->m_gdipImage;
		viewPort = RectD(0, 0, pGdipImage->GetWidth(), pGdipImage->GetHeight());

		RectD rect = GetViewBoxRect(viewBox, psvgElement->m_preserveAspectRatio->m_animated->m_baseVal->m_value, viewPort);

		LDraw::Bitmap* pBitmap = pImage->m_gdipImage;
		LDraw::ImageAttributes imageAttributes;

		out.DrawImage(pBitmap,
			rect,	// dest rect
			(float)viewPort.X, (float)viewPort.Y, (float)viewPort.Width, (float)viewPort.Height,	// source rect
			LDraw::UnitPixel, &imageAttributes, NULL, NULL);
		/*
		LDraw::Image* pGdipImage = pImage->m_gdipImage;
		if (pGdipImage->GetLastStatus() == 0)
		{
			LDraw::ImageAttributes imageAttributes;

			out.DrawImage(pGdipImage,
				dstRect,
				0, 0, pGdipImage->GetWidth(), pGdipImage->GetHeight(),
				LDraw::UnitPixel, &imageAttributes, NULL, NULL);
		}
		*/
	}
#endif
	return 0;
}

}	// w3c
}
