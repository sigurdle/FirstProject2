#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEBlendElement.h"
#include "SVGFEBlendElement.h"

namespace System
{

extern uint8 linear_to_sRGB[256];
extern uint8 sRGB_to_linear[256];

namespace Web
{

SVGBlendEffect::SVGBlendEffect()
{
}

unsigned int SVGBlendEffect::GetInputCount()
{
	return 2;
}

Gui::CEffect* SVGBlendEffect::GetInput(unsigned int index)
{
	if (index >= 2)
	{
		throw std::exception("Index out of bounds");
	}

	return m_input[index];
}

void SVGBlendEffect::SetInput(unsigned int index, Gui::CEffect* input)
{
	if (index >= 2)
	{
		raise(Exception("Index out of bounds"));
	}

	m_input[index] = input;
}

void SVGBlendEffect::Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection)
{
	ASSERT(0);
}

PSVGFEBlendElement::PSVGFEBlendElement(SVGFEBlendElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEBlendElement::GetInCount()
{
	return 2;
}

//virtual
Gui::CEffect* PSVGFEBlendElement::Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEBlendElement* psvgElement = static_cast<CLSVGFEBlendElement*>(m_pNode);

	LONG err = 0;

	LDraw::Bitmap* inImage1 = inPinImage[0]->m_outImage;
	LDraw::Bitmap* inImage2 = inPinImage[1]->m_outImage;

	if (!inImage2)
	{
		MessageBox(NULL, "No inImage2", "Blend Effect", MB_OK);
		return -1;
	}

	LDraw::BitmapData indata1;
	if (inImage1->LockBits(
		&LDraw::Rect(0, 0, inImage1->GetWidth(), inImage1->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppPARGB, &indata1) != 0)
	{
		ASSERT(0);
		return -1;
	}

	LDraw::BitmapData indata2;
	if (inImage1 != inImage2)
	{
		if (inImage2->LockBits(
			&LDraw::Rect(0, 0, inImage2->GetWidth(), inImage2->GetHeight()),
			LDraw::ImageLockModeRead,
			PixelFormat32bppPARGB, &indata2) != 0)
		{
			inImage1->UnlockBits(&indata1);

			ASSERT(0);
			return -1;
		}
	}
	else
	{
		indata2 = indata1;
	}

	LDraw::BitmapData outdata;
	if (outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		PixelFormat32bppPARGB, &outdata) != 0)
	{
		inImage1->UnlockBits(&indata1);
		if (inImage1 != inImage2) inImage2->UnlockBits(&indata2);

		ASSERT(0);
		return -1;
	}

	LSVGBlendModeType mode = psvgElement->m_mode->m_animated->m_animVal->m_value;

	int width = outdata.Width;
	int height = outdata.Height;

	for (int y = 0; y < height; y++)
	{
		ARGBPixel* pin1 = (ARGBPixel*)((BYTE*)indata1.Scan0 + indata1.Stride*y);
		ARGBPixel* pin2 = (ARGBPixel*)((BYTE*)indata2.Scan0 + indata2.Stride*y);
		ARGBPixel* out = (ARGBPixel*)((BYTE*)outdata.Scan0 + outdata.Stride*y);

		for (int x = 0; x < width; x++)
		{
			ASSERT(pin1->red <= pin1->alpha);
			ASSERT(pin1->green <= pin1->alpha);
			ASSERT(pin1->blue <= pin1->alpha);

			ASSERT(pin2->red <= pin2->alpha);
			ASSERT(pin2->green <= pin2->alpha);
			ASSERT(pin2->blue <= pin2->alpha);

			/*
			For all feBlend modes, the result opacity is computed as follows:

				qr = 1 - (1-qa)*(1-qb)
			*/

			out->alpha = (255 - (255-pin1->alpha)*(255-pin2->alpha)/255);

			switch (mode)
			{
			case SVG_FEBLEND_MODE_NORMAL:
				{
					// cr = (1 - qa) * cb + ca
					out->red =		(255-pin1->alpha)*pin2->red/255	+ pin1->red;
					out->green =	(255-pin1->alpha)*pin2->green/255+ pin1->green;
					out->blue =		(255-pin1->alpha)*pin2->blue/255	+ pin1->blue;
				}
				break;

			case SVG_FEBLEND_MODE_MULTIPLY:
				{
					// cr = (1-qa)*cb + (1-qb)*ca + ca*cb
					out->red =		(255-pin1->alpha)*pin2->red/255		+ (255-pin1->alpha)*pin1->red/255		+ pin1->red		*pin2->red / 255;
					out->green =	(255-pin1->alpha)*pin2->green/255	+ (255-pin1->alpha)*pin1->green/255	+ pin1->green	*pin2->green / 255;
					out->blue =		(255-pin1->alpha)*pin2->blue/255		+ (255-pin1->alpha)*pin1->blue/255		+ pin1->blue	*pin2->blue / 255;
				}
				break;

			case SVG_FEBLEND_MODE_SCREEN:
				{
					// cr = cb + ca - ca * cb
					out->red =		pin2->red	+ pin1->red		-pin1->red	*pin2->red / 255;
					out->green =	pin2->green + pin1->green	-pin1->green*pin2->green / 255;
					out->blue =		pin2->blue	+ pin1->blue	-pin1->blue	*pin2->blue / 255;
				}
				break;

			case SVG_FEBLEND_MODE_DARKEN:
				{
					// cr = Min ((1 - qa) * cb + ca, (1 - qb) * ca + cb)
					out->red =		min((255-pin1->alpha) * pin2->red/255	+ pin1->red,	(255-pin2->alpha)*pin1->red/255	+pin2->red);
					out->green =	min((255-pin1->alpha) * pin2->green/255+ pin1->green,	(255-pin2->alpha)*pin1->green/255+pin2->green);
					out->blue =		min((255-pin1->alpha) * pin2->blue/255	+ pin1->blue,	(255-pin2->alpha)*pin1->blue/255	+pin2->blue);
				}
				break;

			case SVG_FEBLEND_MODE_LIGHTEN:
				{
					// cr = Max ((1 - qa) * cb + ca, (1 - qb) * ca + cb)
					out->red =		max((255-pin1->alpha) * pin2->red/255	+ pin1->red,	(255-pin2->alpha)*pin1->red/255	+pin2->red);
					out->green =	max((255-pin1->alpha) * pin2->green/255+ pin1->green,	(255-pin2->alpha)*pin1->green/255+pin2->green);
					out->blue =		max((255-pin1->alpha) * pin2->blue/255	+ pin1->blue,	(255-pin2->alpha)*pin1->blue/255	+pin2->blue);
				}
				break;

			default:
				ASSERT(0);
			}

			pin1++;
			pin2++;
			out++;
		}
	}

	inImage1->UnlockBits(&indata1);
	if (inImage1 != inImage2) inImage2->UnlockBits(&indata2);

	outImage->UnlockBits(&outdata);
#endif
	return 0;
}

}	// w3c
}
