#include "stdafx.h"
#include "LSVG2.h"

//#include "PSVGFECompositeElement.h"
#include "SVGFECompositeElement.h"

namespace System
{
namespace Web
{

PSVGFECompositeElement::PSVGFECompositeElement(SVGFECompositeElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFECompositeElement::GetInCount()
{
	return 2;
}

//virtual
Gui::CEffect* PSVGFECompositeElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGFECompositeElement* psvgElement = static_cast<SVGFECompositeElement*>(m_pNode);

#if 0

	LONG err = 0;

	LDraw::Bitmap* inImage1 = inImage[0]->m_outImage;
	LDraw::Bitmap* inImage2 = inImage[1]->m_outImage;

	if (!inImage2)
	{
		ASSERT(0);
		return NULL;
	}

	LDraw::BitmapData indata1;
	if (inImage1->LockBits(
		&LDraw::RectI(0, 0, inImage1->GetWidth(), inImage1->GetHeight()),
		LDraw::ImageLockModeRead/*,
		PixelFormat32bppPARGB*/, &indata1) != 0)
	{
		ASSERT(0);
		return NULL;
	}

	LDraw::BitmapData indata2;
	if (inImage1 != inImage2)
	{
		if (inImage2->LockBits(
			&LDraw::RectI(0, 0, inImage2->GetWidth(), inImage2->GetHeight()),
			LDraw::ImageLockModeRead/*,
			PixelFormat32bppPARGB*/, &indata2) != 0)
		{
			inImage1->UnlockBits(&indata1);

			ASSERT(0);
			return NULL;
		}
	}
	else
	{
		indata2 = indata1;
	}

	LDraw::BitmapData outdata;
	if (outImage->LockBits(
		&LDraw::RectI(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite/*,
		PixelFormat32bppPARGB*/, &outdata) != 0)
	{
		inImage1->UnlockBits(&indata1);
		if (inImage1 != inImage2) inImage2->UnlockBits(&indata2);

		ASSERT(0);
		return NULL;
	}

	SVGCompositeOperatorType op = psvgElement->m_operator->m_animated->m_animVal->m_value;
	long k1 = (long)(psvgElement->m_k1->m_animated->m_animVal->m_value->m_value);
	long k2 = (long)(psvgElement->m_k2->m_animated->m_animVal->m_value->m_value);
	long k3 = (long)(psvgElement->m_k3->m_animated->m_animVal->m_value->m_value);
	long k4 = (long)(psvgElement->m_k4->m_animated->m_animVal->m_value->m_value);

	int width = outdata.Width;
	int height = outdata.Height;

	for (int y = 0; y < height; y++)
	{
		LDraw::PixelRGBAP_32* pin1 = (LDraw::PixelRGBAP_32*)((uint8*)indata1.Scan0 + indata1.Stride*y);
		LDraw::PixelRGBAP_32* pin2 = (LDraw::PixelRGBAP_32*)((uint8*)indata2.Scan0 + indata2.Stride*y);
		LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)((uint8*)outdata.Scan0 + outdata.Stride*y);

		for (int x = 0; x < width; x++)
		{
			ASSERT(pin1->r <= pin1->a);
			ASSERT(pin1->g <= pin1->a);
			ASSERT(pin1->b <= pin1->a);

			ASSERT(pin2->r <= pin2->a);
			ASSERT(pin2->g <= pin2->a);
			ASSERT(pin2->b <= pin2->a);

			LDraw::PixelRGBAP_32 in1;
			LDraw::PixelRGBAP_32 in2;

			/*
			if (FALSE)// Premultiply
			{
				in1.red = (int)pin1->red * pin1->alpha / 255;
				in1.green = (int)pin1->green * pin1->alpha / 255;
				in1.blue = (int)pin1->blue * pin1->alpha / 255;
				in1.alpha = (int)pin1->alpha;

				in2.red = (int)pin2->red * pin2->alpha / 255;
				in2.green = (int)pin2->green * pin2->alpha / 255;
				in2.blue = (int)pin2->blue * pin2->alpha / 255;
				in2.alpha = (int)pin2->alpha;
			}
			else
			*/
			{
				in1 = *pin1;
				in2 = *pin2;
			}

			switch (op)
			{
			case SVG_FECOMPOSITE_OPERATOR_OVER:	// Over
				{
					//	Porter-Duff Source Over Destination rule. The source is composited over the destination. 
					//	Fs = 1 and Fd = (1-As), thus: 
					
				//	Cd = Cs + Cd*(1-As)
				//	Ad = As + Ad*(1-As)

					out->r = (in1.r) + ((int)in2.r*(255-in1.a)/255);
					out->g = (in1.g) + ((int)in2.g*(255-in1.a)/255);
					out->b = (in1.b) + ((int)in2.b*(255-in1.a)/255);
					out->a = (in1.a) + ((int)in2.a*(255-in1.a)/255);
				}
				break;
				
			case SVG_FECOMPOSITE_OPERATOR_IN:	// In
				{
					//	Porter-Duff Source In Destination rule. The part of the source lying inside of the destination replaces the destination. 
					//	Fs = Ad and Fd = 0, thus: 
					
				//	Cd = Cs*Ad
				//	Ad = As*Ad

					out->r = ((int)in1.r * in2.a)/255;
					out->g = ((int)in1.g * in2.a)/255;
					out->b = ((int)in1.b * in2.a)/255;
					out->a = ((int)in1.a * in2.a)/255;
				}
				break;
				
			case SVG_FECOMPOSITE_OPERATOR_OUT:	// Out
				{
					ASSERT(0);
					//	Porter-Duff Source Held Out By Destination rule. The part of the source lying outside of the destination replaces the destination. 
					//	Fs = (1-Ad) and Fd = 0, thus: 
					
				//	Cd = Cs*(1-Ad)
				//	Ad = As*(1-Ad)
				}
				break;
				
			case SVG_FECOMPOSITE_OPERATOR_ATOP:	// Atop
				{
					ASSERT(0);
				}
				break;
				
			case SVG_FECOMPOSITE_OPERATOR_XOR:	// Xor
				{
					ASSERT(0);
				}
				break;
				
			case SVG_FECOMPOSITE_OPERATOR_ARITHMETIC:	// Arithmetic
				{
					//	result = k1*i1*i2 + k2*i1 + k3*i2 + k4

/*					in1.red = (int)pin1->red * pin1->alpha / 255;
					in1.green = (int)pin1->green * pin1->alpha / 255;
					in1.blue = (int)pin1->blue * pin1->alpha / 255;
					in1.alpha = (int)pin1->alpha;

					in2.red = (int)pin2->red * 255 / pin2->alpha;
					in2.green = (int)pin2->green * 255 / pin2->alpha;
					in2.blue = (int)pin2->blue * 255 / pin2->alpha;
					in2.alpha = (int)pin2->alpha;
*/

					/*
					if (pin1->alpha > 0)
					{
						in1.red = (int)pin1->red * 255 / pin1->alpha;
						in1.green = (int)pin1->green * 255 / pin1->alpha;
						in1.blue = (int)pin1->blue * 255 / pin1->alpha;
						in1.alpha = (int)pin1->alpha;
					}
					else
					{
						in1.red = 0;
						in1.green = 0;
						in1.blue = 0;
						in1.alpha = 0;
					}

					if (pin2->alpha > 0)
					{
						in2.red = (int)pin2->red * 255 / pin2->alpha;
						in2.green = (int)pin2->green * 255 / pin2->alpha;
						in2.blue = (int)pin2->blue * 255 / pin2->alpha;
						in2.alpha = (int)pin2->alpha;
					}
					else
					{
						in2.red = 0;
						in2.green = 0;
						in2.blue = 0;
						in2.alpha = 0;
					}
					*/

					//ASSERT(in1.red == 0 && in1.green == 127 && in1.blue == 0 && in1.alpha == 127);
/*
					in1.red = linear_to_sRGB[in1.red];
					in1.green = linear_to_sRGB[in1.green];
					in1.blue = linear_to_sRGB[in1.blue];

					in2.red = linear_to_sRGB[in2.red];
					in2.green = linear_to_sRGB[in2.green];
					in2.blue = linear_to_sRGB[in2.blue];
*/
					//
					long alpha = (k1*in1.a*in2.a/255 + k2*in1.a + k3*in2.a + k4*255);
					if (alpha < 0) alpha = 0;// Remove this (can't be < 0)
					else if (alpha > 255) alpha = 255;

					//
					long red = (k1*in1.r*in2.r/255 + k2*in1.r + k3*in2.r + k4*255);
					if (red < 0) red = 0;	// Remove this (can't be < 0)
					else if (red > 255) red = 255;

					//
					long green= (k1*in1.g*in2.g/255 + k2*in1.g + k3*in2.g + k4*255);
					if (green < 0) green = 0;// Remove this (can't be < 0)
					else if (green > 255) green = 255;

					//
					long blue = k1*in1.b*in2.b/255 + k2*in1.b + k3*in2.b + k4*255;
					if (blue < 0) blue = 0;// Remove this (can't be < 0)
					else if (blue > 255) blue = 255;

					//long alpha = 255;
					/*
					long alpha = k1*in1.alpha*in2.alpha + k2*(in1.alpha-128L) + k3*(in2.alpha-128L) + k4*255;

					long red = k1*in1.red*in2.red + k2*(in1.red-128L) + k3*(in2.red-128L) + k4*255;
					long green= k1*in1.green*in2.green + k2*(in1.green-128L) + k3*(in2.green-128L) + k4*255;
					long blue = k1*in1.blue*in2.blue + k2*(in1.blue-128L) + k3*(in2.blue-128L) + k4*255;
					*/
					//long alpha = 255;

					/*
					if (alpha > 255)
					{
						red = red * ((double)alpha/(alpha-255));
						green = green * ((double)alpha/(alpha-255));
						blue = blue * ((double)alpha/(alpha-255));
						alpha = 255;
					}
					*/


					//red * (alpha-255)
					//	long alpha = max(red, max(green, blue));

				//	long alpha = min(in1.alpha, in2.alpha);
				//	if (alpha < 0) alpha = 0;// Remove this (can't be < 0)
				//	else if (alpha > 255) alpha = 255;

/*					
					red = red * alpha / 255;
					green = green * alpha / 255;
					blue = blue * alpha / 255;
*/			

					ASSERT(alpha >= 0 && alpha <= 255);
					ASSERT(red >= 0 && red <= 255);
					ASSERT(green >= 0 && green <= 255);
					ASSERT(blue >= 0 && blue <= 255);

					/*
					red = sRGB_to_linear[red];
					green = sRGB_to_linear[green];
					blue = sRGB_to_linear[blue];
					*/
					/*
					red = linear_to_sRGB[red];
					green = linear_to_sRGB[green];
					blue = linear_to_sRGB[blue];
					*/

					//
					if (alpha < red) alpha = red;
					if (alpha < green) alpha = green;
					if (alpha < blue) alpha = blue;

					/*
					red = red * alpha / 255;
					green = green * alpha / 255;
					blue = blue * alpha / 255;
					*/

					out->r = (uint8)red;
					out->g = (uint8)green;
					out->b = (uint8)blue;
					out->a = (uint8)alpha;

					/*
					out->red = (int)out->red * out->alpha / 255;
					out->green = (int)out->green * out->alpha / 255;
					out->blue = (int)out->blue * out->alpha / 255;
					*/
/*
					out->red = ((int)out->red * 255) / out->alpha;
					out->green = ((int)out->green * 255) / out->alpha;
					out->blue = ((int)out->blue * 255) / out->alpha;
*/				}
				break;

			default:
				ASSERT(0);
			}

		// Un - premultiply destination
			/*
			if (out->alpha > 0)
			{
				out->red = ((int)out->red * 255) / out->alpha;
				out->green = ((int)out->green * 255) / out->alpha;
				out->blue = ((int)out->blue * 255) / out->alpha;
			}
			*/

			ASSERT(out->r <= out->a);
			ASSERT(out->g <= out->a);
			ASSERT(out->b <= out->a);

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
