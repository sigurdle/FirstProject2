#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEGaussianBlurElement.h"
#include "SVGFEGaussianBlurElement.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace System
{
namespace Web
{

long BlurARGB(Graphics::BitmapData* inImage, Graphics::BitmapData* outImage, gm::RectI& rect, int featherx, int feathery)
{
	int left = rect.X;
	int top = rect.Y;
	int right = rect.GetRight();//inImage->width-1;//r->uRect.right;
	int bottom = rect.GetBottom();//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x < right; x++)
	{
		uint8 * dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8 * src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y < bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			uint	blue = 0;

			uint num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				int radius2 = filtery[y2];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += inImage->Stride;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y < bottom; y++)
	{
		uint8* src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8* dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x < right; x++)
		{
			int left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			uint	blue = 0;

			uint	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				int radius2 = filterx[x2+featherx];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += 4;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

/*
The Gaussian blur kernel is an approximation of the normalized convolution:

H(x) = exp(-x2/ (2s2)) / sqrt(2* pi*s2)
*/

long GaussianBlurARGB(Graphics::BitmapData* inImage, Graphics::BitmapData* outImage, gm::RectI* rect, int featherx, int feathery)
{
	int left = rect->X;
	int top = rect->Y;
	int right = rect->GetRight();//inImage->width-1;//r->uRect.right;
	int bottom = rect->GetBottom();//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];

	int i;

	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8* dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8* src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8* src2 = (src + top2*inImage->Stride);
	
			uint alpha = 0;
			uint red = 0;
			uint green = 0;
			uint blue = 0;

			uint num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				int radius2 = filtery[y2];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += inImage->Stride;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		uint8* src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8* dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x <= right; x++)
		{
			int left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8* src2 = (src + left2*4);

			uint alpha = 0;
			uint red = 0;
			uint green = 0;
			uint blue = 0;

			uint num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				int radius2 = filterx[x2+featherx];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				blue += src2[3] *radius2;

				src2 += 4;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			dest[3] = (uint8)(blue/num);

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

PSVGFEGaussianBlurElement::PSVGFEGaussianBlurElement(SVGFEGaussianBlurElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEGaussianBlurElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEGaussianBlurElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inEffect[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGFEGaussianBlurElement* psvgElement = static_cast<SVGFEGaussianBlurElement*>(m_pNode);

	double devX = psvgElement->get_stdDeviationX()->get_animVal()*scaleX;
	double devY = psvgElement->get_stdDeviationY()->get_animVal()*scaleY;

	SVGGaussianBlurEffect* pEffect = new SVGGaussianBlurEffect;

	pEffect->m_inEffect = inEffect[0];

	pEffect->m_stdDeviationX = (float)devX;
	pEffect->m_stdDeviationY = (float)devY;
#if 0
	pEffect->m_techniqueH = pO->m_res->m_d3d9_effect->GetTechniqueByName("RenderFilterGaussianBlurH");
	ASSERT(pEffect->m_techniqueH);

	pEffect->m_techniqueV = pO->m_res->m_d3d9_effect->GetTechniqueByName("RenderFilterGaussianBlurV");
	ASSERT(pEffect->m_techniqueV);
#endif
	m_effect = pEffect;
	return pEffect;

#if 0
	LDraw::BitmapData srcdata;
	inPinImage[0]->m_outImage->LockBits(
		&LDraw::RectI(0, 0, inPinImage[0]->m_outImage->GetWidth(), inPinImage[0]->m_outImage->GetHeight()),
		LDraw::ImageLockModeRead/*,
		PixelFormat32bppARGB*/, &srcdata);

	LDraw::BitmapData dstdata;
	outImage->LockBits(
		&LDraw::RectI(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite/*,
		PixelFormat32bppARGB*/, &dstdata);

	//BlurARGB(&srcdata, &dstdata, uRect, devx, devy);
	GaussianBlurARGB(&srcdata, &dstdata,
		&LDraw::RectI(uRect.X, uRect.Y, uRect.GetRight(), uRect.GetBottom()),
		devx, devy);

	inPinImage[0]->m_outImage->UnlockBits(&srcdata);
	outImage->UnlockBits(&dstdata);
	return 0;
#endif
}

}	// w3c
}
