#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEDisplacementMapElement.h"
#include "SVGFEDisplacementMapElement.h"

namespace System
{
namespace Web
{

PSVGFEDisplacementMapElement::PSVGFEDisplacementMapElement(SVGFEDisplacementMapElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEDisplacementMapElement::GetInCount()
{
	return 2;
}

//virtual
Gui::CEffect* PSVGFEDisplacementMapElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEDisplacementMapElement* psvgElement = static_cast<CLSVGFEDisplacementMapElement*>(m_pNode);

	LDraw::BitmapData indata1;
	if (inImage[0]->m_outImage->LockBits(
		&LDraw::Rect(0, 0, inImage[0]->m_outImage->GetWidth(), inImage[0]->m_outImage->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppPARGB, &indata1) != 0)
	{
		ASSERT(0);
		return -1;
	}

	LDraw::BitmapData indata2;
	if (inImage[0] != inImage[1])
	{
		if (inImage[1]->m_outImage->LockBits(
			&LDraw::Rect(0, 0, inImage[1]->m_outImage->GetWidth(), inImage[1]->m_outImage->GetHeight()),
			LDraw::ImageLockModeRead,
			PixelFormat32bppPARGB, &indata2) != 0)
		{
			inImage[0]->m_outImage->UnlockBits(&indata1);
			ASSERT(0);
			return -1;
		}
	}
	else
	{
		indata2 = indata1;
	}

	LDraw::BitmapData dstdata;
	if (outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		PixelFormat32bppPARGB, &dstdata) != 0)
	{
		inImage[0]->m_outImage->UnlockBits(&indata1);
		if (inImage[0] != inImage[1]) inImage[1]->m_outImage->UnlockBits(&indata2);

		ASSERT(0);
		return -1;
	}

	int width = dstdata.Width;
	int height = dstdata.Height;

	double scalex = psvgElement->m_scale->m_animated->m_animVal->m_value*scaleX;
	double scaley = scalex*scaleX;

	LSVGChannelSelector xChannelSelector = psvgElement->m_xChannelSelector->m_animated->m_animVal->m_value;
	LSVGChannelSelector yChannelSelector = psvgElement->m_yChannelSelector->m_animated->m_animVal->m_value;

	int xch;
	switch (xChannelSelector)
	{
	case SVG_CHANNEL_A: xch = 3; break;
	case SVG_CHANNEL_R: xch = 2; break;
	case SVG_CHANNEL_G: xch = 1; break;
	case SVG_CHANNEL_B: xch = 0; break;
	}

	int ych;
	switch (yChannelSelector)
	{
	case SVG_CHANNEL_A: ych = 3; break;
	case SVG_CHANNEL_R: ych = 2; break;
	case SVG_CHANNEL_G: ych = 1; break;
	case SVG_CHANNEL_B: ych = 0; break;
	}

// P'(x,y) <- P( x + scale * ((XC(x,y) - .5), y + scale * (YC(x,y) - .5))

	for (int y = 0; y < height; y++)
	{
		BYTE* in2 = (BYTE*)((BYTE*)indata2.Scan0 + indata2.Stride*y);
		BYTE* out = (BYTE*)((BYTE*)dstdata.Scan0 + dstdata.Stride*y);

		for (int x = 0; x < width; x++)
		{
			int x0 = x + (scalex * (((double)in2[xch])/255 - 0.5));
			int y0 = y + (scaley * (((double)in2[ych])/255 - 0.5));

			if (x0 >= 0 && y0 >= 0 && x0 < width && y0 < height)
			{
				BYTE* in1 = (BYTE*)((BYTE*)indata1.Scan0 + indata1.Stride*y0 + x0*sizeof(ARGBPixel));

				*(DWORD*)out = *(DWORD*)in1;
			}
			else
			{
				*(DWORD*)out = 0;
			}

			in2 += 4;
			out += 4;
		}
	}

	outImage->UnlockBits(&dstdata);

	inImage[0]->m_outImage->UnlockBits(&indata1);
	if (inImage[0] != inImage[1]) inImage[1]->m_outImage->UnlockBits(&indata2);
#endif
	return 0;
}

}	// w3c
}
