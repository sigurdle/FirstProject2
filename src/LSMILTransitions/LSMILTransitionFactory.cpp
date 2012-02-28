#include "stdafx.h"
#include "LSMILTransitions.h"
#include "LSMILTransitionFactory.h"

//#include "..\StructsD.h"

namespace System
{

long BlurRGB(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int left = rect->left;
	int top = rect->top;
	int right = rect->right;//inImage->width-1;//r->uRect.right;
	int bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int width = inImage->Width;//right-left+1;
	int height = inImage->Height;//bottom-top+1;

	uint8 * tmask = new uint8[width*height*3];
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

	int m_alphabytesPerRow = width*3;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8 * dest = (tmask + m_alphabytesPerRow*top + x*3);
		uint8 * src = ((uint8*)inImage->Scan0 + inImage->Stride*top + x*3);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 *	src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			//DWORD	blue = 0;

			uint	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				int	radius2 = filtery[y2];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
			//	blue += src2[3] *radius2;

				src2 += inImage->Stride;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			//dest[3] = (BYTE)(blue/num);

			src += inImage->Stride;
			dest += m_alphabytesPerRow;
		}
	}

// Horizontal
	for (int y = top; y <= bottom; y++)
	{
		uint8 * src = (tmask + m_alphabytesPerRow*y + left*3);
		uint8 * dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*3);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 *	src2 = (src + left2*3);

			uint	alpha = 0;
			uint	red = 0;
			uint	green = 0;
			//DWORD	blue = 0;

			uint	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
			{
				int	radius2 = filterx[x2+featherx];
				num += radius2;

				alpha += src2[0] *radius2;
				red += src2[1] *radius2;
				green += src2[2] *radius2;
			//	blue += src2[3] *radius2;

				src2 += 3;
			}

			dest[0] = (uint8)(alpha/num);
			dest[1] = (uint8)(red/num);
			dest[2] = (uint8)(green/num);
			//dest[3] = (BYTE)(blue/num);

			src += 3;
			dest += 3;
		}
	}

	return 0;
}

long Maximum(LDraw::BitmapData* inImage, LDraw::BitmapData* outImage, LDraw::BBoxi* rect, int featherx, int feathery)
{
	int	left = rect->left;
	int	top = rect->top;
	int	right = rect->right;//inImage->width-1;//r->uRect.right;
	int	bottom = rect->bottom;//inImage->height-1;//r->uRect.bottom;

	int	width = inImage->Width;//right-left+1;
	int	height = inImage->Height;//bottom-top+1;

	uint8 *	tmask = new uint8[width*height*3];
	if (!tmask) return -1;

	if (left < 0) left = 0;
	if (top < 0) top = 0;
	if (right > width-1) right = width-1;
	if (bottom > height-1) bottom = height-1;

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

	int m_alphabytesPerRow = width*3;

// Vertical
	for (int x = left; x <= right; x++)
	{
		uint8 *	dest = (tmask + m_alphabytesPerRow*top + x*3);
		uint8 *	src = ((uint8 *)inImage->Scan0 + inImage->Stride*top + x*3);

		for (int y = top; y <= bottom; y++)
		{
			int top2 = y-feathery;
			if (top2 < 0) top2 = 0;
			top2 = top2-y;

			int bottom2 = y+feathery;
			if (bottom2 > height-1) bottom2 = height-1;
			bottom2 = bottom2-y;

			uint8 *	src2 = (src + top2*inImage->Stride);
	
			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			//DWORD	blue = 0;

			uint	num = 0;

			top2 += feathery;
			bottom2 += feathery;

			for (int y2 = top2; y2 <= bottom2; y2++)
			{
				/*
				int	radius2 = filtery[y2];
				num += radius2;
				*/

				if (src2[0] < alpha) alpha = src2[0];
				if (src2[1] < red) red = src2[1];
				if (src2[2] < green) green = src2[2];
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
	for (int y = top; y <= bottom; y++)
	{
		uint8 *	src = (tmask + m_alphabytesPerRow*y + left*3);
		uint8 *	dest = ((uint8*)outImage->Scan0 + outImage->Stride*y + left*3);

		for (int x = left; x <= right; x++)
		{
			int	left2 = x-featherx;
			if (left2 < 0) left2 = 0;
			left2 = left2-x;

			int	right2 = x+featherx;
			if (right2 > width-1) right2 = width-1;
			right2 = right2-x;

			uint8 *	src2 = (src + left2*3);

			uint	alpha = 255;
			uint	red = 255;
			uint	green = 255;
			//DWORD	blue = 0;

			uint	num = 0;

			for (int x2 = left2; x2 <= right2; x2++)
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

				//blue += src2[3] *radius2;

				src2 += 3;
			}

			dest[0] = alpha;
			dest[1] = red;
			dest[2] = green;

			/*
			dest[0] = (BYTE)(alpha/num);
			dest[1] = (BYTE)(red/num);
			dest[2] = (BYTE)(green/num);
		//	dest[3] = (BYTE)(blue/num);
		*/

			src += 3;
			dest += 3;
		}
	}

	return 0;
}

void Maximum(LDraw::Bitmap* pBitmap, int devx, int devy)
{
	LDraw::BitmapData data;
	pBitmap->LockBits(
		&LDraw::RectI(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
		LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
		/*PixelFormat24bppRGB,*/ &data);

		Maximum(&data, &data, &LDraw::BBoxi(0, 0, pBitmap->GetWidth()-1, pBitmap->GetHeight()-1), devx, devy);

	pBitmap->UnlockBits(&data);
}

void Negative(LDraw::Bitmap* pSrcBitmap, LDraw::Bitmap* pDstBitmap)
{
	LDraw::BitmapData srcdata;
	pSrcBitmap->LockBits(
		&LDraw::RectI(0, 0, pSrcBitmap->GetWidth(), pSrcBitmap->GetHeight()),
		LDraw::ImageLockModeRead,
		/*PixelFormat24bppRGB,*/ &srcdata);

	LDraw::BitmapData dstdata;
	pDstBitmap->LockBits(
		&LDraw::RectI(0, 0, pDstBitmap->GetWidth(), pDstBitmap->GetHeight()),
		LDraw::ImageLockModeWrite,
		/*PixelFormat24bppRGB,*/ &dstdata);

	for (int y = 0; y < srcdata.Height; y++)
	{
		uint8 * dst = ((uint8 *)dstdata.Scan0 + dstdata.Stride*y);
		uint8 * src = ((uint8 *)srcdata.Scan0 + srcdata.Stride*y);

		for (int x = 0; x < srcdata.Width; x++)
		{
			dst[0] = 255-src[0];
			dst[1] = 255-src[1];
			dst[2] = 255-src[2];

			dst += 3;
			src += 3;
		}
	}

	pSrcBitmap->UnlockBits(&srcdata);
	pDstBitmap->UnlockBits(&dstdata);
}

void Combine(LDraw::Bitmap* pSrcBitmap[2], LDraw::Bitmap* pDstBitmap)
{
	LDraw::BitmapData srcdata[2];

	pSrcBitmap[0]->LockBits(
		&LDraw::RectI(0, 0, pSrcBitmap[0]->GetWidth(), pSrcBitmap[0]->GetHeight()),
		LDraw::ImageLockModeRead,
		/*PixelFormat24bppRGB,*/ &srcdata[0]);

	pSrcBitmap[1]->LockBits(
		&LDraw::RectI(0, 0, pSrcBitmap[1]->GetWidth(), pSrcBitmap[1]->GetHeight()),
		LDraw::ImageLockModeRead,
		/*PixelFormat24bppRGB,*/ &srcdata[1]);

	LDraw::BitmapData dstdata;
	pDstBitmap->LockBits(
		&LDraw::RectI(0, 0, pDstBitmap->GetWidth(), pDstBitmap->GetHeight()),
		LDraw::ImageLockModeWrite,
		/*PixelFormat32bppARGB,*/ &dstdata);

	for (int y = 0; y < dstdata.Height; y++)
	{
		uint8 *	dst = ((uint8 *)dstdata.Scan0 + dstdata.Stride*y);
		uint8 *	src0 = ((uint8 *)srcdata[0].Scan0 + srcdata[0].Stride*y);
		uint8 *	src1 = ((uint8 *)srcdata[1].Scan0 + srcdata[1].Stride*y);

		for (int x = 0; x < dstdata.Width; x++)
		{
			dst[0] = 0;
			dst[1] = 0;
			dst[2] = 255;
			dst[3] = 255 - (src0[0]+src1[0]);

			dst += 4;
			src0 += 3;
			src1 += 3;
		}
	}

	pSrcBitmap[0]->UnlockBits(&srcdata[0]);
	pSrcBitmap[1]->UnlockBits(&srcdata[1]);
	pDstBitmap->UnlockBits(&dstdata);
}

class CSMILTransition : public ISMILTransition
{
public:
	System::StringW* m_type;
	System::StringW* m_subtype;

#if 0
	STDMETHOD(Process)(double progress,
		_RectD _rectA, long _pBitmapA,
		_RectD _rectB, long _pBitmapB,
		_RectD _rect, long _pBitmap)
	{
		LDraw::RectF rectA(_rectA.X, _rectA.Y, _rectA.Width, _rectA.Height);
		LDraw::RectF rectB(_rectB.X, _rectB.Y, _rectB.Width, _rectB.Height);
		LDraw::RectF rect(_rect.X, _rect.Y, _rect.Width, _rect.Height);

		return Process(progress,
			rectA, (LDraw::Bitmap*)_pBitmapA,
			rectB, (LDraw::Bitmap*)_pBitmapB,
			rect, (LDraw::Bitmap*)_pBitmap);
	}
#endif

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap) = 0;
};

class CBarWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
/*		if (!wcscmp(subtype, L"topToBottom"))
		{
		}
		else // "leftToRight"
		{
			double dstx = mediaRect.Width * progress;

			{
				double srcx = pMediaBitmap->GetWidth() * progress;

				srcgraphics->DrawImage(pMediaBitmap,
					LDraw::RectF(0, 0, dstx, mediaRect.Height),
					srcx, 0, pMediaBitmap->GetWidth()-srcx, pMediaBitmap->GetHeight(),
					LDraw::UnitPixel);
			}

			{
				LDraw::RectI bgRect(dstx, 0, mediaRect.Width-dstx, mediaRect.Height);
				bgRect.Offset(mediaRect.X, mediaRect.Y);

				srcgraphics->DrawImage(pBgBitmap,
					LDraw::RectF(dstx, 0, mediaRect.Width-dstx, mediaRect.Height),
					bgRect.X, bgRect.Y, bgRect.Width, bgRect.Height,
					LDraw::UnitPixel);
			}
		}
*/
		return Success;
	}
};

class CBoxWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		LDraw::Graphics2D* dstGraphics = new LDraw::GraphicsO(pBitmap);
		// Draw background first, common for all subtypes
		{
			dstGraphics->DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		LDraw::RectF rc;

		if (*m_subtype == L"topLeft")
		{
			rc = LDraw::RectF(
				rect.X,	rect.Y,
				rect.Width*progress,	rect.Height*progress);
		}
		else if (*m_subtype == L"topRight")
		{
			rc = LDraw::RectF(
				rect.X + rect.Width*(1-progress), rect.Y,
				rect.Width*progress, rect.Height*progress);
		}
		else if (*m_subtype == L"bottomRight")
		{
			rc = LDraw::RectF(
				rect.X + rect.Width*(1-progress), rect.Y + rect.Height*(1-progress),
				rect.Width*progress, rect.Height*progress);
		}
		else if (*m_subtype == L"bottomLeft")
		{
			rc = LDraw::RectF(
				rect.X, rect.Y + rect.Height*(1-progress),
				rect.Width*progress, rect.Height*progress);
		}

	//	LDraw::GraphicsState state = dstGraphics.Save();

		dstGraphics->SetClip(rc);

		dstGraphics->DrawImage(pBitmapB,
			rect,
			rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
			LDraw::UnitPixel*/);

	//	dstGraphics.Restore(state);

		return Success;
	}
};

class CFourBoxWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		//LDraw::GraphicsState state = dstGraphics.Save();

		if (!wcscmp(m_subtype->c_str(), L"cornersIn"))
		{
			LDraw::RectF rc0;
			LDraw::RectF rc1;
			LDraw::RectF rc2;
			LDraw::RectF rc3;

			rc0 = LDraw::RectF(
				rect.X,	rect.Y,
				rect.Width/2*progress,	rect.Height/2*progress);

			rc1 = LDraw::RectF(
				rect.X + rect.Width/2 + (1-progress)*rect.Width/2,	rect.Y,
				rect.Width/2*progress,	rect.Height/2*progress);

			rc2 = LDraw::RectF(
				rect.X, rect.Y + rect.Height/2 + (1-progress)*rect.Height/2,
				rect.Width/2*progress,	rect.Height/2*progress);

			rc3 = LDraw::RectF(
				rect.X + rect.Width/2 + (1-progress)*rect.Width/2,	rect.Y + rect.Height/2 + (1-progress)*rect.Height/2,
				rect.Width/2*progress,	rect.Height/2*progress);

			dstGraphics.m_p->SetClip(rc0, LDraw::CombineModeReplace);
			dstGraphics.m_p->SetClip(rc1, LDraw::CombineModeUnion);
			dstGraphics.m_p->SetClip(rc2, LDraw::CombineModeUnion);
			dstGraphics.m_p->SetClip(rc3, LDraw::CombineModeUnion);
		}
		else if (!wcscmp(m_subtype->c_str(), L"cornersOut"))
		{
			LDraw::RectF rc0;
			LDraw::RectF rc1;
			LDraw::RectF rc2;
			LDraw::RectF rc3;

			rc0 = LDraw::RectF(
				rect.X + rect.Width/4 - rect.Width/4*(progress), rect.Y + rect.Height/4 - rect.Height/4*(progress),
				rect.Width/2*progress,	rect.Height/2*progress);

			rc1 = LDraw::RectF(
				rect.X + rect.Width/2 + rect.Width/4 - rect.Width/4*(progress),	rect.Y + rect.Height/4 - rect.Height/4*(progress),
				rect.Width/2*progress,	rect.Height/2*progress);

			rc2 = LDraw::RectF(
				rect.X + rect.Width/4 - rect.Width/4*(progress), rect.Y + rect.Height/2 + rect.Height/4 - rect.Height/4*(progress),
				rect.Width/2*progress,	rect.Height/2*progress);

			rc3 = LDraw::RectF(
				rect.X + rect.Width/2 + rect.Width/4 - rect.Width/4*(progress),	rect.Y + rect.Height/2 + rect.Height/4 - rect.Height/4*(progress),
				rect.Width/2*progress,	rect.Height/2*progress);

			dstGraphics.m_p->SetClip(rc0, LDraw::CombineModeReplace);
			dstGraphics.m_p->SetClip(rc1, LDraw::CombineModeUnion);
			dstGraphics.m_p->SetClip(rc2, LDraw::CombineModeUnion);
			dstGraphics.m_p->SetClip(rc3, LDraw::CombineModeUnion);
		}

		dstGraphics.DrawImage(pBitmapB,
			rect,
			rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
			LDraw::UnitPixel*/);

		//dstGraphics.Restore(state);

		return Success;
	}
};

class CBarnDoorWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		if (!wcscmp(m_subtype->c_str(), L"diagonalTopLeft"))
		{
			//LDraw::GraphicsState state = dstGraphics.Save();

			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X, rect.Y),
				LDraw::PointF(rect.X + rect.Width*progress, rect.Y),
				LDraw::PointF(rect.X + rect.Width, rect.Y + rect.Height*(1-progress)),
				LDraw::PointF(rect.X + rect.Width, rect.Y + rect.Height),
				LDraw::PointF(rect.X + rect.Width*(1-progress), rect.Y + rect.Height),
				LDraw::PointF(rect.X, rect.Y + rect.Height * progress),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));

			dstGraphics.m_p->SetClip(&path);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

		//	dstGraphics.Restore(state);
		}
		else if (!wcscmp(m_subtype->c_str(), L"diagonalBottomLeft"))
		{
		//	LDraw::GraphicsState state = dstGraphics.Save();

			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X + rect.Width*(1-progress), rect.Y),
				LDraw::PointF(rect.X + rect.Width, rect.Y),
				LDraw::PointF(rect.X + rect.Width, rect.Y + rect.Height*progress),
				LDraw::PointF(rect.X + rect.Width*progress, rect.Y + rect.Height),
				LDraw::PointF(rect.X, rect.Y + rect.Height),
				LDraw::PointF(rect.X, rect.Y + rect.Height * (1-progress)),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));

			dstGraphics.m_p->SetClip(&path);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

		//	dstGraphics.Restore(state);
		}
		else if (!wcscmp(m_subtype->c_str(), L"horizontal"))
		{
		//	LDraw::GraphicsState state = dstGraphics.Save();

			double cy = rect.Y + rect.Height/2;

			LDraw::RectF rc(
				rect.X,		cy - rect.Height*progress/2,
				rect.Width,	rect.Height*progress);

			dstGraphics.m_p->SetClip(rc);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

		//	dstGraphics.Restore(state);
		}
		else if (!wcscmp(m_subtype->c_str(), L"vertical"))
		{
		//	LDraw::GraphicsState state = dstGraphics.Save();

			double cx = rect.X + rect.Width/2;

			LDraw::RectF rc(
				cx - rect.Width*progress/2,	rect.Y,
				rect.Width*progress,				rect.Height);

			dstGraphics.m_p->SetClip(rc);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

		//	dstGraphics.Restore(state);
		}

		return Success;
	}
};

class CDiagonalWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		if (!wcscmp(m_subtype->c_str(), L"topLeft"))
		{
			dstGraphics.PushClip();

			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X, rect.Y),
				LDraw::PointF(rect.X + rect.Width*2*progress, rect.Y),
				LDraw::PointF(rect.X, rect.Y + rect.Height*2*progress),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));

			dstGraphics.m_p->SetClip(&path);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.PopClip();
		}
		else
		{
		//	LDraw::GraphicsState state = dstGraphics.Save();
			dstGraphics.PushClip();

			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X + rect.Width - rect.Width*2*(progress), rect.Y),
				LDraw::PointF(rect.X + rect.Width, rect.Y),
				LDraw::PointF(rect.X + rect.Width, rect.Y + rect.Height*2*progress),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));

			dstGraphics.m_p->SetClip(&path);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.PopClip();
		//	dstGraphics.Restore(state);
		}

		return Success;
	}
};

class CMiscDiagonalWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		if (!wcscmp(m_subtype->c_str(), L"doubleBarnDoor"))
		{
			//LDraw::GraphicsState state = dstGraphics.Save();
			dstGraphics.PushClip();

			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X+rect.Width/2*progress, rect.Y),
				LDraw::PointF(rect.X+rect.Width/2, rect.Y+rect.Height/2 -rect.Height/2*progress),
				LDraw::PointF(rect.X+rect.Width-rect.Width/2*progress, rect.Y),
				LDraw::PointF(rect.X+rect.Width, rect.Y),
				LDraw::PointF(rect.X+rect.Width, rect.Y+rect.Height/2*progress),
				LDraw::PointF(rect.X+rect.Width/2+rect.Width/2*progress, rect.Y+rect.Height/2),
				LDraw::PointF(rect.X+rect.Width, rect.Y+rect.Height-rect.Height/2*progress),
				LDraw::PointF(rect.X+rect.Width, rect.Y+rect.Height),
				LDraw::PointF(rect.X+rect.Width-rect.Width/2*progress, rect.Y+rect.Height),
				LDraw::PointF(rect.X+rect.Width/2, rect.Y+rect.Height/2+rect.Height/2*progress),
				LDraw::PointF(rect.X+rect.Width/2*progress, rect.Y+rect.Height),
				LDraw::PointF(rect.X, rect.Y+rect.Height),
				LDraw::PointF(rect.X, rect.Y+rect.Height-rect.Height/2*progress),
				LDraw::PointF(rect.X+rect.Width/2-rect.Width/2*progress, rect.Y+rect.Height/2),
				LDraw::PointF(rect.X, rect.Y+rect.Height/2*progress),
				LDraw::PointF(rect.X, rect.Y),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));

			dstGraphics.m_p->SetClip(&path);

			dstGraphics.DrawImage(pBitmapB,
				rect,
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.PopClip();
			//dstGraphics.Restore(state);
		}
		else	// doubleDiamond
		{
		}

		return Success;
	}
};

class CVeeWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

//		LDraw::GraphicsState state = dstGraphics.Save();
		//LDraw::Region oldClip;
		dstGraphics.PushClip();

		if (!wcscmp(m_subtype->c_str(), L"down"))
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X + rect.Width/2-rect.Width*2, rect.Y - rect.Height*2 + rect.Height*2*(progress)),
				LDraw::PointF(rect.X + rect.Width/2+rect.Width*2, rect.Y - rect.Height*2 + rect.Height*2*(progress)),
				LDraw::PointF(rect.X + rect.Width/2, rect.Y + rect.Height*2*progress),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));
			dstGraphics.m_p->SetClip(&path);
		}
		else if (!wcscmp(m_subtype->c_str(), L"left"))
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X + rect.Width - (-rect.Width*2 + rect.Width*2*(progress)), rect.Y + rect.Height/2-rect.Height*2),
				LDraw::PointF(rect.X + rect.Width - (-rect.Width*2 + rect.Width*2*(progress)), rect.Y + rect.Height/2+rect.Height*2),
				LDraw::PointF(rect.X + rect.Width - (rect.Width*2*progress), rect.Y + rect.Height/2),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));
			dstGraphics.m_p->SetClip(&path);
		}
		else if (!wcscmp(m_subtype->c_str(), L"up"))
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X + rect.Width/2-rect.Width*2, rect.Y + rect.Height - (-rect.Height*2 + rect.Height*2*(progress))),
				LDraw::PointF(rect.X + rect.Width/2+rect.Width*2, rect.Y + rect.Height - (-rect.Height*2 + rect.Height*2*(progress))),
				LDraw::PointF(rect.X + rect.Width/2, rect.Y + rect.Height - (rect.Height*2*progress)),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));
			dstGraphics.m_p->SetClip(&path);
		}
		else if (!wcscmp(m_subtype->c_str(), L"right"))
		{
			LDraw::PointF points[] =
			{
				LDraw::PointF(rect.X - rect.Width*2 + rect.Width*2*(progress), rect.Y + rect.Height/2-rect.Height*2),
				LDraw::PointF(rect.X - rect.Width*2 + rect.Width*2*(progress), rect.Y + rect.Height/2+rect.Height*2),
				LDraw::PointF(rect.X + rect.Width*2*progress, rect.Y + rect.Height/2),
			};

			LDraw::GraphicsPathF path;
			path.AddPolygon(points, sizeof(points)/sizeof(LDraw::PointF));
			dstGraphics.m_p->SetClip(&path);
		}

		dstGraphics.DrawImage(pBitmapB,
			rect,
			rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
			LDraw::UnitPixel*/);

		dstGraphics.PopClip();

		return Success;
	}
};

class CPushWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));

		if (!wcscmp(m_subtype->c_str(), L"fromLeft"))
		{
			double dstx = rect.Width * progress;

			dstGraphics.DrawImage(pBitmapA,
				LDraw::RectF(rect.X + dstx, rect.Y, rect.Width, rect.Height),
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.DrawImage(pBitmapB,
				LDraw::RectF(rect.X + dstx - rect.Width, rect.Y, rect.Width, rect.Height),
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);
		}
		else if (!wcscmp(m_subtype->c_str(), L"fromRight"))
		{
			double dstx = rect.Width * (1-progress);

			dstGraphics.DrawImage(pBitmapA,
				LDraw::RectF(rect.X + dstx, rect.Y, rect.Width, rect.Height),
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.DrawImage(pBitmapB,
				LDraw::RectF(rect.X + dstx - rect.Width, rect.Y, rect.Width, rect.Height),
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);
		}
		else if (!wcscmp(m_subtype->c_str(), L"fromTop"))
		{
			double dsty = rect.Height * progress;

			dstGraphics.DrawImage(pBitmapA,
				LDraw::RectF(rect.X, rect.Y + dsty, rect.Width, rect.Height),
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.DrawImage(pBitmapB,
				LDraw::RectF(rect.X, rect.Y + dsty - rect.Height, rect.Width, rect.Height),
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);
		}
		else if (!wcscmp(m_subtype->c_str(), L"fromBottom"))
		{
			double dsty = rect.Height * (1-progress);

			dstGraphics.DrawImage(pBitmapA,
				LDraw::RectF(rect.X, rect.Y + dsty, rect.Width, rect.Height),
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);

			dstGraphics.DrawImage(pBitmapB,
				LDraw::RectF(rect.X, rect.Y + dsty - rect.Height, rect.Width, rect.Height),
				rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
				LDraw::UnitPixel*/);
		}

		return Success;
	}
};

class CSingleSweepWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		LDraw::RectF ellipseRect;

		double start;
		double sweep = progress*360;

		if (!wcscmp(m_subtype->c_str(), L"clockwiseTop"))
		{
			double dx = rect.Width/4;
			double dy = rect.Height;

			double rx = sqrt(dx*dx+dy*dy);
			double ry = rx;

			ellipseRect = LDraw::RectF(rect.X+rect.Width/2-rx, rect.Y-ry, rect.X+rect.Width/2+rx, rect.Y+ry);
			start = 0;
		}

	//	LDraw::GraphicsState state = dstGraphics.Save();

		LDraw::GraphicsPathF path;
		path.AddPie(ellipseRect, start, sweep);

		dstGraphics.m_p->SetClip(&path);

		dstGraphics.DrawImage(pBitmapB,
			rect,
			rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
			LDraw::UnitPixel*/);

	//	dstGraphics.Restore(state);

		return Success;
	}
};

class CClockWipe :
	public CSMILTransition
{
public:

	virtual ErrorCode Process(double progress,
		LDraw::RectF rectA, LDraw::Bitmap* pBitmapA,
		LDraw::RectF rectB, LDraw::Bitmap* pBitmapB,
		LDraw::RectF rect, LDraw::Bitmap* pBitmap)
	{
		UI::Graphics dstGraphics(new LDraw::GraphicsO(pBitmap));
		// Draw background first, common for all subtypes
		{
			dstGraphics.DrawImage(pBitmapA,
				rect,
				rectA.X, rectA.Y, rectA.Width, rectA.Height/*,
				LDraw::UnitPixel*/);
		}

		double dx = rect.Width/2;
		double dy = rect.Height/2;

		double rx = sqrt(dx*dx+dy*dy);
		double ry = rx;
		LDraw::RectF ellipseRect(rect.X+rect.Width/2 - rx, rect.Y+rect.Height/2 - ry, rx*2, ry*2);

		double start;
		double sweep = progress*360;

		if (!wcscmp(m_subtype->c_str(), L"clockwiseTwelve"))
		{
			start = -90;
		}
		else if (!wcscmp(m_subtype->c_str(), L"clockwiseThree"))
		{
			start = 0;
		}
		else if (!wcscmp(m_subtype->c_str(), L"clockwiseSix"))
		{
			start = 90;
		}
		else if (!wcscmp(m_subtype->c_str(), L"clockwiseNine"))
		{
			start = 180;
		}

	//	LDraw::GraphicsState state = dstGraphics.Save();

		double cx = rect.X + rect.Width/2;

		LDraw::GraphicsPathF path;
		path.AddPie(ellipseRect, start, sweep);

		dstGraphics.m_p->SetClip(&path);

		dstGraphics.DrawImage(pBitmapB,
			rect,
			rectB.X, rectB.Y, rectB.Width, rectB.Height/*,
			LDraw::UnitPixel*/);

	//	dstGraphics.Restore(state);

		return Success;
	}
};

struct TypeDefault
{
	TypeDefault(System::StringW* _type, System::StringW* _default)
	{
		type = _type;
		defaultSubType = _default;
	}

	__live_object_ptr<System::StringW> type;
	__live_object_ptr<System::StringW> defaultSubType;
};

TypeDefault defaults[] =
{
	TypeDefault(WSTR("barWipe"), WSTR("leftToRight")),
	TypeDefault(WSTR("boxWipe"), WSTR("topLeft")),
	TypeDefault(WSTR("fourBoxWipe"), WSTR("cornersIn")),
	TypeDefault(WSTR("barnDoorWipe"), WSTR("vertical")),
	TypeDefault(WSTR("diagonalWipe"), WSTR("topLeft")),
	TypeDefault(WSTR("bowTieWipe"), WSTR("vertical")),
	TypeDefault(WSTR("miscDiagonalWipe"), WSTR("doubleBarnDoor")),
	TypeDefault(WSTR("veeWipe"), WSTR("down")),
	TypeDefault(WSTR("barnVeeWipe"), WSTR("down")),
	TypeDefault(WSTR("zigZagWipe"), WSTR("leftToRight")),
	TypeDefault(WSTR("barnZigZagWipe"), WSTR("vertical")),
	TypeDefault(WSTR("irisWipe"), WSTR("rectangle")),
	TypeDefault(WSTR("triangleWipe"), WSTR("up")),
	TypeDefault(WSTR("arrowHeadWipe"), WSTR("up")),
	TypeDefault(WSTR("pentagonWipe"), WSTR("up")),
	TypeDefault(WSTR("hexagonWipe"), WSTR("horizontal")),
	TypeDefault(WSTR("ellipseWipe"), WSTR("circle")),
	TypeDefault(WSTR("eyeWipe"), WSTR("horizontal")),
	TypeDefault(WSTR("roundRectWipe"), WSTR("horizontal")),
	TypeDefault(WSTR("starWipe"), WSTR("fourPoint")),
	TypeDefault(WSTR("miscShapeWipe"), WSTR("heart")),
	TypeDefault(WSTR("clockWipe"), WSTR("clockwiseTwelve")),
	TypeDefault(WSTR("pinWheelWipe"), WSTR("twoBladeVertical")),
	TypeDefault(WSTR("singleSweepWipe"), WSTR("clockwiseTop")),
	TypeDefault(WSTR("fanWipe"), WSTR("centerTop")),
	TypeDefault(WSTR("doubleFanWipe"), WSTR("fanOutVertical")),
	TypeDefault(WSTR("doubleSweepWipe"), WSTR("parallelVertical")),
	TypeDefault(WSTR("saloonDoorWipe"), WSTR("top")),
	TypeDefault(WSTR("windshieldWipe"), WSTR("right")),
	TypeDefault(WSTR("snakeWipe"), WSTR("topLeftHorizontal")),
	TypeDefault(WSTR("spiralWipe"), WSTR("topLeftClockwise")),
	TypeDefault(WSTR("parallelSnakesWipe"), WSTR("verticalTopSame")),
	TypeDefault(WSTR("boxSnakesWipe"), WSTR("twoBoxTop")),
	TypeDefault(WSTR("waterfallWipe"), WSTR("verticalLeft")),

	TypeDefault(WSTR("pushWipe"), WSTR("fromLeft")),
	TypeDefault(WSTR("slideWipe"), WSTR("fromLeft")),
	TypeDefault(WSTR("fade"), WSTR("crossfade")),
};

/////////////////////////////////////////////////////////////////////////////
// SMILTransitionFactory

SMILTransitionFactory::SMILTransitionFactory()
{
}

SMILTransitionFactory::~SMILTransitionFactory()
{
}

ErrorCode SMILTransitionFactory::FindTransition(System::StringW* type, System::StringW* _subtype, ISMILTransition* *pVal)
{
	/*
	ASSERT(pVal != NULL);
	ASSERT(type != NULL);
	if (pVal == NULL) return E_POINTER;
	if (type == NULL) return E_INVALIDARG;
*/

	*pVal = NULL;

	System::StringW* subtype = _subtype;

	if (subtype == NULL)
	{
		int nTypes = sizeof(defaults)/sizeof(TypeDefault);

		for (int n = 0; n < nTypes; n++)
		{
			if (!wcscmp(defaults[n].type->c_str(), type->c_str()))
			{
				subtype = defaults[n].defaultSubType;
			}
		}
	}

	if (!wcscmp(type->c_str(), L"barWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"leftToRight") ||
			!wcscmp(subtype->c_str(), L"topToBottom"))
		{
			CBarWipe* p = new CBarWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}
	else if (!wcscmp(type->c_str(), L"boxWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"topLeft") ||
			!wcscmp(subtype->c_str(), L"topRight") ||
			!wcscmp(subtype->c_str(), L"bottomRight") ||
			!wcscmp(subtype->c_str(), L"bottomLeft") ||
			!wcscmp(subtype->c_str(), L"topCenter") ||
			!wcscmp(subtype->c_str(), L"rightCenter") ||
			!wcscmp(subtype->c_str(), L"bottomCenter") ||
			!wcscmp(subtype->c_str(), L"fromTop"))
		{
			CBoxWipe* p = new CBoxWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}
	else if (!wcscmp(type->c_str(), L"fourBoxWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"cornersIn") ||
			!wcscmp(subtype->c_str(), L"cornersOut"))
		{
			CFourBoxWipe* p = new CFourBoxWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}
	else if (!wcscmp(type->c_str(), L"barnDoorWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"vertical") ||
			!wcscmp(subtype->c_str(), L"horizontal") ||
			!wcscmp(subtype->c_str(), L"diagonalBottomLeft") ||
			!wcscmp(subtype->c_str(), L"diagonalTopLeft"))
		{
			CBarnDoorWipe* p = new CBarnDoorWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}
	else if (!wcscmp(type->c_str(), L"diagonalWipe"))
	{
		CDiagonalWipe* p = new CDiagonalWipe;
		if (p)
		{
			//p->AddRef();

			p->m_type = type;
			p->m_subtype = subtype;

			*pVal = p;
		}
	}
	/*
	else if (bowTieWipe)
	{
	}
	*/
	else if (!wcscmp(type->c_str(), L"miscDiagonalWipe"))
	{
		CMiscDiagonalWipe* p = new CMiscDiagonalWipe;
		if (p)
		{
			//p->AddRef();

			p->m_type = type;
			p->m_subtype = subtype;

			*pVal = p;
		}
	}
	else if (!wcscmp(type->c_str(), L"veeWipe"))
	{
		CVeeWipe* p = new CVeeWipe;
		if (p)
		{
			//p->AddRef();

			p->m_type = type;
			p->m_subtype = subtype;

			*pVal = p;
		}
	}
	else if (!wcscmp(type->c_str(), L"pushWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"fromLeft") ||
			!wcscmp(subtype->c_str(), L"fromTop") ||
			!wcscmp(subtype->c_str(), L"fromRight") ||
			!wcscmp(subtype->c_str(), L"fromBottom"))
		{
			CPushWipe* p = new CPushWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}
	else if (!wcscmp(type->c_str(), L"singleSweepWipe"))
	{
		CSingleSweepWipe* p = new CSingleSweepWipe;
		if (p)
		{
			//p->AddRef();

			p->m_type = type;
			p->m_subtype = subtype;

			*pVal = p;
		}
	}
	else if (!wcscmp(type->c_str(), L"clockWipe"))
	{
		if (!wcscmp(subtype->c_str(), L"clockwiseTwelve") ||
			!wcscmp(subtype->c_str(), L"clockwiseThree") ||
			!wcscmp(subtype->c_str(), L"clockwiseSix") ||
			!wcscmp(subtype->c_str(), L"clockwiseNine"))
		{
			CClockWipe* p = new CClockWipe;
			if (p)
			{
				//p->AddRef();

				p->m_type = type;
				p->m_subtype = subtype;

				*pVal = p;
			}
		}
	}

	return Success;
}

ErrorCode SMILTransitionFactory::ProcessTransition(
	ISMILTransition* pTransition,
	long horzRepeat, long vertRepeat, long borderWidth, bool borderColorBlend,
	double progress, /*_RectD srcRectA,*/ LDraw::Bitmap* pBitmapA, /*_RectD srcRectB,*/ LDraw::Bitmap* pBitmapB, /*_RectD dstRect,*/ LDraw::Bitmap* pBitmap)
{
//	LDraw::Bitmap* pBitmapA = (LDraw::Bitmap*)srcBitmapA;
//	LDraw::Bitmap* pBitmapB = (LDraw::Bitmap*)srcBitmapB;
//	LDraw::Bitmap* pBitmap = (LDraw::Bitmap*)dstBitmap;

	LDraw::RectF rectA(0, 0, pBitmapA->GetWidth(), pBitmapA->GetHeight());
	LDraw::RectF rectB(0, 0, pBitmapB->GetWidth(), pBitmapB->GetHeight());
	LDraw::RectF rect(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());

	if (horzRepeat < 1) horzRepeat = 1;
	if (vertRepeat < 1) vertRepeat = 1;

//	CSMILTransition* pTransition = static_cast<CSMILTransitionNULL;

	if (pTransition)
	{
		LDraw::SizeF sizeA(rectA.Width/horzRepeat, rectA.Height/vertRepeat);
		LDraw::SizeF sizeB(rectB.Width/horzRepeat, rectB.Height/vertRepeat);
		LDraw::SizeF size(rect.Width/horzRepeat, rect.Height/vertRepeat);

		for (int x = 0; x < horzRepeat; x++)
		{
			for (int y = 0; y < vertRepeat; y++)
			{
				LDraw::RectF subrectA(rectA.X+x*sizeA.Width, rectA.Y+y*sizeA.Height, sizeA.Width, sizeA.Height);
				LDraw::RectF subrectB(x*sizeB.Width, y*sizeB.Height, sizeB.Width, sizeB.Height);
				LDraw::RectF subrect(x*size.Width, y*size.Height, size.Width, size.Height);

				if (borderWidth == 0)
				{
					static_cast<CSMILTransition*>(pTransition)->Process(progress,
						subrectA, pBitmapA,
						subrectB, pBitmapB,
						subrect, pBitmap);
				}
				else
				{
					LDraw::Bitmap* pBlackBitmap = new LDraw::Bitmap(rect.Width, rect.Height, LDraw::PixelFormat_t::RGB_24/*PixelFormat24bppRGB*/);
					{
						LDraw::Graphics2D* g = new LDraw::GraphicsO(pBlackBitmap);
						g->Clear(LDraw::Color(0,0,0));
					}

					LDraw::Bitmap* pWhiteBitmap = new LDraw::Bitmap(rect.Width, rect.Height, LDraw::PixelFormat_t::RGB_24/*PixelFormat24bppRGB*/);
					{
						LDraw::Graphics2D* g = new LDraw::GraphicsO(pWhiteBitmap);
						g->Clear(LDraw::Color(255,255,255));
					}

					LDraw::Bitmap* pMonoResult = new LDraw::Bitmap(rect.Width, rect.Height, LDraw::PixelFormat_t::RGB_24/*PixelFormat24bppRGB*/);

					LDraw::RectF rc(0, 0, rect.Width, rect.Height);
					/*static_cast<CSMILTransition*>*/(pTransition)->Process(progress,
						rc, pWhiteBitmap,
						rc, pBlackBitmap,
						rc, pMonoResult);

					int devx = borderWidth;
					int devy = borderWidth;

					if (borderColorBlend)
					{
						LDraw::BitmapData monoData;
						pMonoResult->LockBits(
							&LDraw::RectI(0, 0, pMonoResult->GetWidth(), pMonoResult->GetHeight()),
							LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
							/*PixelFormat24bppRGB,*/ &monoData);

						BlurRGB(&monoData, &monoData, &LDraw::BBoxi(0, 0, monoData.Width, monoData.Height), (int)(borderWidth/2.0+0.5), (int)(borderWidth/2.0+0.5));

						LDraw::BitmapData dataA;
						pBitmapA->LockBits(
							&LDraw::RectI(subrectA.X, subrectA.Y, subrectA.Width, subrectA.Height),
							LDraw::ImageLockModeRead,
							/*PixelFormat32bppARGB,*/ &dataA);

						LDraw::BitmapData dataB;
						pBitmapB->LockBits(
							&LDraw::RectI(subrectB.X, subrectB.Y, subrectB.Width, subrectB.Height),
							LDraw::ImageLockModeRead,
							/*PixelFormat32bppARGB,*/ &dataB);

						LDraw::BitmapData data;
						pBitmap->LockBits(
							&LDraw::RectI(subrect.X, subrect.Y, subrect.Width, subrect.Height),
							LDraw::ImageLockModeWrite,
							/*PixelFormat32bppARGB,*/ &data);

						for (int y = 0; y < data.Height; y++)
						{
							uint8 * mono = ((uint8 *)monoData.Scan0 + monoData.Stride*y); 
							uint8 * dst = ((uint8 *)data.Scan0 + data.Stride*y);
							uint8 * srcA = ((uint8 *)dataA.Scan0 + dataA.Stride*y);
							uint8 * srcB = ((uint8 *)dataB.Scan0 + dataB.Stride*y);

							for (int x = 0; x < data.Width; x++)
							{
								dst[0] = ((int)srcA[0] * mono[0])/255 + ((int)srcB[0] * (255-mono[0]))/255;
								dst[1] = ((int)srcA[1] * mono[0])/255 + ((int)srcB[1] * (255-mono[0]))/255;
								dst[2] = ((int)srcA[2] * mono[0])/255 + ((int)srcB[2] * (255-mono[0]))/255;
								dst[3] = ((int)srcA[3] * mono[0])/255 + ((int)srcB[3] * (255-mono[0]))/255;

								mono += 3;
								dst += 4;
								srcA += 4;
								srcB += 4;
							}
						}

						pBitmapA->UnlockBits(&dataA);
						pBitmapB->UnlockBits(&dataB);
						pBitmap->UnlockBits(&data);
						pMonoResult->UnlockBits(&monoData);
					}
					else
					{
						LDraw::Bitmap* pMonoResult2 = new LDraw::Bitmap(rect.Width, rect.Height, LDraw::PixelFormat_t::RGB_24/*PixelFormat24bppRGB*/);
						Negative(pMonoResult, pMonoResult2);

						Maximum(pMonoResult, devx, devy);
						Maximum(pMonoResult2, devx, devy);

						///
						/*
						LDraw::Graphics g(pBitmap);
						g.DrawImage(pMonoResult,
							rect,
							rc.X, rc.Y, rc.Width, rc.Height,
							LDraw::UnitPixel);
							*/

						LDraw::Bitmap* src[2] = {pMonoResult, pMonoResult2};

						LDraw::Bitmap* pD = new LDraw::Bitmap(rect.Width, rect.Height, LDraw::PixelFormat_t::RGBAP_32/*PixelFormat32bppARGB*/);
						Combine(src, pD);

						UI::Graphics g(new LDraw::GraphicsO(pBitmap));
					//	g.SetCompositingMode(LDraw::CompositingModeSourceCopy);
						g.DrawImage(pD,
							rect,	// dest rect
							float(rc.X), float(rc.Y), float(rc.Width), float(rc.Height)/*,	// source rect
							LDraw::UnitPixel*/);

						delete pMonoResult2;
					}

					delete pMonoResult;
					delete pBlackBitmap;
					delete pWhiteBitmap;
				}
			}
		}

		return Success;
	}

	return Error;
}

}
