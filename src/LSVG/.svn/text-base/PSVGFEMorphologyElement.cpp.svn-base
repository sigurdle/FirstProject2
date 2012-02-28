#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEMorphologyElement.h"
#include "SVGFEMorphologyElement.h"

namespace System
{
namespace Web
{

static long Minimum(Graphics::BitmapData* inImage, Graphics::BitmapData* outImage, gm::BBoxi& rect, int featherx, int feathery)
{
	int left = rect.left;
	int top = rect.top;
	int right = rect.right;//inImage->width-1;//r->uRect.right;
	int bottom = rect.bottom;//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

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
			if (bottom2 > height) bottom2 = height;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			uint	blue = 255;

			uint num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 < bottom2; y2++)
			{
				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];

				src2 += inImage->Stride;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y < bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x < right; x++)
		{
			int left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;
			if (right2 > width) right2 = width;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			uint	blue = 255;

			uint	num = 0;

			for (int x2 = left2; x2 < right2; x2++)
			{
				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];

				src2 += 4;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

static long Maximum(Graphics::BitmapData* inImage, Graphics::BitmapData* outImage, gm::BBoxi& rect, int featherx, int feathery)
{
	int left = rect.left;
	int top = rect.top;
	int right = rect.right;//inImage->width-1;//r->uRect.right;
	int bottom = rect.bottom;//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

//	int i;

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
			if (bottom2 > height) bottom2 = height;
			bottom2 = bottom2-y;

			uint8 * src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			uint	blue = 0;

			uint num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 < bottom2; y2++)
			{
				if (src2[0] > alpha) alpha = src2[0];
				if (src2[1] > red) red = src2[1];
				if (src2[2] > green) green = src2[2];
				if (src2[3] > blue) blue = src2[3];

				src2 += inImage->Stride;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y < bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*4);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*4);

		for (int x = left; x < right; x++)
		{
			int left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int right2 = x+featherx;
			if (right2 > width) right2 = width;
			right2 = right2-x;

			uint8 * src2 = (src + left2*4);

			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			uint	blue = 0;

			uint	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				if (src2[0] > alpha) alpha = src2[0];
				if (src2[1] > red) red = src2[1];
				if (src2[2] > green) green = src2[2];
				if (src2[3] > blue) blue = src2[3];

				src2 += 4;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			src += 4;
			dest += 4;
		}
	}

	return 0;
}

PSVGFEMorphologyElement::PSVGFEMorphologyElement(SVGFEMorphologyElement* element) : PSVGFEElement(element)
{
}

// virtual
int PSVGFEMorphologyElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEMorphologyElement::Filter(Gui::RenderTarget* rt, Gui::CEffect* inImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
#if 0
	CLSVGFEMorphologyElement* psvgElement = static_cast<CLSVGFEMorphologyElement*>(m_pNode);

	LDraw::BitmapData indata;
	if (inImage[0]->m_outImage->LockBits(
		&LDraw::Rect(0, 0, inImage[0]->m_outImage->GetWidth(), inImage[0]->m_outImage->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppPARGB, &indata) != 0)
	{
		ASSERT(0);
		return -1;
	}

	LDraw::BitmapData outdata;
	if (outImage->LockBits(
		&LDraw::Rect(0, 0, outImage->GetWidth(), outImage->GetHeight()),
		LDraw::ImageLockModeWrite,
		PixelFormat32bppPARGB, &outdata) != 0)
	{
		inImage[0]->m_outImage->UnlockBits(&indata);

		ASSERT(0);
		return -1;
	}

	LSVGMorphologyOperator op = psvgElement->m_operator->m_animated->m_animVal->m_value.m_value;
	double radiusX = psvgElement->m_radius->m_animated->m_animVal->m_value->m_value[0]*scaleX;
	double radiusY = psvgElement->m_radius->m_animated->m_animVal->m_value->m_value[1]*scaleY;

	if (op == SVG_MORPHOLOGY_OPERATOR_ERODE)
	{
		Minimum(&indata, &outdata,
				CRect(uRect.X, uRect.Y, uRect.GetRight(), uRect.GetBottom()),
				radiusX, radiusY);
	}
	else if (op == SVG_MORPHOLOGY_OPERATOR_DILATE)
	{
		Maximum(&indata, &outdata,
			CRect(uRect.X, uRect.Y, uRect.GetRight(), uRect.GetBottom()),
			radiusX, radiusY);
	}
	else
		ASSERT(0);

	inImage[0]->m_outImage->UnlockBits(&indata);
	outImage->UnlockBits(&outdata);
#endif
	return 0;
}

}	// Web
}	// System
