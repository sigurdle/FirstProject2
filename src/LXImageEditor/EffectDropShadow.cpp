#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageDocument.h"

namespace System
{
namespace ImageEdit
{

long BlurARGB(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery);

ErrorCode CDropShadow::Filter(LDraw::Bitmap* inBitmap, LDraw::Bitmap* outBitmap)
{
#if 0
	long distancex = m_distance;//distance / (long)r->x_sampling;
	long distancey = m_distance;//distance / (long)r->y_sampling;

//	long blurx = blur / (long)r->x_sampling;
//	long blury = blur / (long)r->y_sampling;

	double radian = m_angle * (M_PI/180);

	int offx = (int)(cos(radian)*distancex);
	int offy = (int)(sin(radian)*distancey);

	/*
	RectDef	tRect;

	tRect = r->aRect;

// Get above stuff right, and remove these 4 lines
	tRect.left = 0;
	tRect.top = 0;
	tRect.right = r->outImage->width-1;
	tRect.bottom = r->outImage->height-1;

	ASSERT(tRect.left >= 0);
	ASSERT(tRect.top >= 0);
	*/

	PixelDef color;
	color.red = 0;
	color.green = 0;
	color.blue = 0;
	color.alpha = 255;

#if 0
	int srcx = 0;
	int srcy = 0;
	int dstx = m_distance;//r->out_x_origin + offx;
	int dsty = m_distance;//0;//r->out_y_origin + offy;
	ASSERT(dstx >= 0);
	ASSERT(dsty >= 0);

	for (int y = 0; y < Image->height; y++)
	{
		PixelDef* in = (PixelDef*)(r->inImage->data + r->inImage->rowbytes*(y+srcy) + (srcx)*4);
		PixelDef* dp = (PixelDef*)(r->outImage->data + r->outImage->rowbytes*(y+dsty) + (dstx)*4);

		for (int x = 0; x < r->inImage->width; x++)
		{
			dp->red = color.red;
			dp->green = color.green;
			dp->blue = color.blue;
			dp->alpha = in->alpha;

			dp++;
			in++;
		}
	}
#endif


	{
		LDraw::Graphics graphics(outBitmap);

		graphics.DrawImage(inBitmap,
			LDraw::Rect(offx, offy, inBitmap->GetWidth(), inBitmap->GetHeight()),
			0, 0, inBitmap->GetWidth(), inBitmap->GetHeight()/*,
			LDraw::UnitPixel*/);
	}

	{
		/*
		LDraw::BitmapData inData;
		inBitmap->LockBits(
			&LDraw::Rect(0, 0, inBitmap->GetWidth(), inBitmap->GetHeight()),
			LDraw::ImageLockModeRead,
			PixelFormat32bppARGB, &inData);
			*/

		LDraw::BitmapData outData;
		outBitmap->LockBits(
			&LDraw::Rect(0, 0, outBitmap->GetWidth(), outBitmap->GetHeight()),
			LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
			PixelFormat32bppARGB, &outData);

		for (int y = 0; y < outData.Height; y++)
		{
			//PixelDef* in = (PixelDef*)(inData->data + r->inImage->rowbytes*(y+srcy) + (srcx)*4);
			PixelDef* dp = (PixelDef*)((BYTE*)outData.Scan0 + outData.Stride*y);

			for (int x = 0; x < outData.Width; x++)
			{
				dp->red = color.red;
				dp->green = color.green;
				dp->blue = color.blue;
				//dp->alpha = in->alpha;

				dp++;
				//in++;
			}
		}

		CRect tRect(0, 0, outData.Width, outData.Height);
		BlurARGB(&outData, &outData, &tRect, m_size, m_size);

		//inBitmap->UnlockBits(&inData);
		outBitmap->UnlockBits(&outData);
	}

	{
		LDraw::Graphics graphics(outBitmap);

		graphics.DrawImage(inBitmap,
			LDraw::Rect(0, 0, inBitmap->GetWidth(), inBitmap->GetHeight()),
			0, 0, inBitmap->GetWidth(), inBitmap->GetHeight(),
			LDraw::UnitPixel);
	}

//	r->inImage->BlendImage(0, 0, r->inImage->width, r->inImage->height, r->outImage, r->out_x_origin, r->out_y_origin, FALSE);
#endif
	return Success;
}

}
}
