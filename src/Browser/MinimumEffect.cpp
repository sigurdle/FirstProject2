#include "stdafx.h"
#include "MinimumEffect.h"

namespace System
{

long Minimum(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int left = rect->left;
	int top = rect->top;
	int right = rect->right;
	int bottom = rect->bottom;

	int width = inImage->Width;
	int height = inImage->Height;

	uint8* tmask = new uint8[width*height*4];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width) right = width;
	if (bottom > height) bottom = height;

	/*
	int* filterx = new int[featherx*2+1];
	int* filtery = new int[feathery*2+1];*/

//	int i;

	/*
	for (i = -featherx; i <= featherx; i++)
	{
		filterx[i+featherx] = featherx-abs(i)+1;
	}

	for (i = -feathery; i <= feathery; i++)
	{
		filtery[i+feathery] = feathery-abs(i)+1;
	}
	*/

	int m_alphabytesPerRow = width*4;

// Vertical
	for (int x = left; x < right; x++)
	{
		uint8* dest = (tmask + m_alphabytesPerRow*top + x*4);
		uint8* src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*4);

		for (int y = top; y < bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height) bottom2 = height;
			bottom2 = bottom2-y;

			uint8* src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			uint	blue = 255;

			int	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 < bottom2; y2++)
			{
				/*
				int	radius2 = filtery[y2];
				num += radius2;
				*/

				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];
				/*
				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				//blue += src2[3] *radius2;
				*/

				src2 += inImage->Stride;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;
/*
			dest[0] = (BYTE)(alpha/num);
			dest[1] = (BYTE)(red/num);
			dest[2] = (BYTE)(green/num);
			//dest[3] = (BYTE)(blue/num);
*/
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

			int	right2 = x+featherx;
			if (right2 > width) right2 = width;
			right2 = right2-x;

			uint8* src2 = (src + left2*4);

			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			uint	blue = 255;

			uint	num = 0;

			for (int x2 = left2; x2 < right2; x2++)
			{
				/*
				int	radius2 = filterx[x2+featherx];
				num += radius2;
				*/

				/*
				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
				*/
				/*
				if (src2[0] > alpha) alpha = src2[0];
				if (src2[1] > red) red = src2[1];
				if (src2[2] > green) green = src2[2];
				*/
				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
				if (src2[3] < blue) blue = src2[3];

				//blue += src2[3] *radius2;

				src2 += 4;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;
			dest[3] = blue;

			/*
			dest[0] = (BYTE)(alpha/num);
			dest[1] = (BYTE)(red/num);
			dest[2] = (BYTE)(green/num);
		//	dest[3] = (BYTE)(blue/num);
		*/

			src += 4;
			dest += 4;
		}
	}

	delete[] tmask;

	return 0;
}

MinimumEffect::MinimumEffect()
{
	SetClipMode(false);

	m_radius = 0;
}

double MinimumEffect::get_Radius()
{
	return m_radius;
}

void MinimumEffect::put_Radius(double value)
{
	m_radius = value;
	if (GetRParent())
	{
		GetRParent()->InvalidateRender();
	}
}

void MinimumEffect::OnRender(UI::Graphics* pGraphics)
{
	LDraw::RectD RenderBounds = GetRParent()->m_expandedBBox;

	LDraw::Bitmap* bitmap = new LDraw::Bitmap(ceil(RenderBounds.Width), ceil(RenderBounds.Height), LDraw::PixelFormat_t::RGBAP_32);

	{
		ASSERT(0);
#if 0
		UI::Graphics* graphics = new UI::Graphics(new LDraw::GraphicsO(bitmap));

		GetRParent()->_OnRender(graphics);
#endif
	}

	LDraw::BitmapData bitmapData;
	bitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &bitmapData);

//	uint32 skip = (bitmapData.Stride>>2) - bitmapData.Width;
//	LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)(bitmapData.Scan0);

	Minimum(&bitmapData, &bitmapData, &LDraw::BBoxi(0, 0, bitmapData.Width, bitmapData.Height), m_radius, m_radius);

	bitmap->UnlockBits(&bitmapData);

	pGraphics->DrawImage(bitmap, 0, 0);
}

}
