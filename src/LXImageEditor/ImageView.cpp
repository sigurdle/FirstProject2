#include "stdafx.h"
#include "LXImageEditor.h"

#include "ImageView.h"

#include "ImageDocument.h"
#include "ImageLayerGroup.h"
#include "ImageLayerBitmap.h"

using namespace System;

/*
namespace LDraw
{
DrawExt uint8 (*multab)[256];
}
*/

namespace System
{
namespace ImageEdit
{

/*
#include "WebEditorApp.h"	// TODO remove
#include "WebEditorFrame.h"	// TODO remove

extern CWebEditorApp* gApp;	// TODO remove
*/

//////////////////

void MaskBitmap(LDraw::Bitmap* pBitmap, LDraw::Bitmap* pMask, bool bInvert)
{
	LDraw::BitmapData inData;
	pBitmap->LockBits(
		&LDraw::RectI(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
		LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
		/*PixelFormat32bppARGB,*/ &inData);

	LDraw::BitmapData outData = inData;

	LDraw::BitmapData maskData;
	pMask->LockBits(
		&LDraw::RectI(0, 0, pMask->GetWidth(), pMask->GetHeight()),
		LDraw::ImageLockModeRead,
		/*PixelFormat32bppARGB,*/ &maskData);

	for (int y = 0; y < maskData.Height; y++)
	{
		LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((uint8*)inData.Scan0 + inData.Stride*y);
		LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)((uint8*)outData.Scan0 + outData.Stride*y);
		LDraw::PixelRGBAP_32* mask = (LDraw::PixelRGBAP_32*)((uint8*)maskData.Scan0 + maskData.Stride*y);

		for (int x = 0; x < maskData.Width; x++)
		{
			if (!bInvert)
				out->a = in->a * (mask->r + mask->g + mask->b)/3 * mask->a / (255*255);
			else
				out->a = in->a * (255-(mask->r + mask->g + mask->b)/3 * mask->a / 255) / 255;

			out->r = in->r;
			out->g = in->g;
			out->b = in->b;

			in++;
			out++;
			mask++;
		}
	}

	pMask->UnlockBits(&maskData);
	pBitmap->UnlockBits(&inData);
}

///////////////

struct FloodNode
{
	SHORT	x, y;
};

class CFlood
{
public:
	FloodNode*	m_ArrayPoints;
	LONG m_numArrayPoints;
	int m_width, m_height;

	ImageDef* m_inImage;

//	RECT	m_rect;

	CFlood::CFlood(ImageDef* inImage)
	{
		m_inImage = inImage;

		m_width = inImage->Width;
		m_height = inImage->Height;

		m_numArrayPoints = 0L;
	}

	uint8 * m_alphabits2;

	inline void SetBit(SHORT x, SHORT y);
	inline bool GetBit(SHORT x, SHORT y);
	inline bool IsPixel(SHORT x, SHORT y);
	inline void AddPoint(SHORT x, SHORT y);
	inline void DoUp(SHORT x, SHORT y);
	inline void DoDown(SHORT x, SHORT y);
	inline void DoLeft(SHORT x, SHORT y);
	inline void DoRight(SHORT x, SHORT y);

	void FloodFill(SHORT x, SHORT y, int tolerance);
};

static SHORT	alphaMin, alphaMax;
static SHORT	redMin, redMax;
static SHORT	grnMin, grnMax;
static SHORT	bluMin, bluMax;
static SHORT	lumMin, lumMax;
//static BYTE g_Red, g_Green, g_Blue, g_Lum;

static uint8 g_method;

inline void CFlood::SetBit(SHORT x, SHORT y)
{
	uint8 * mask = m_alphabits2 + m_width*y+x;

	*mask = 255;

//	LDraw::PixelRGBAP_32*	rgba = (LDraw::PixelRGBAP_32*)((LPBYTE)g->outImage->data + g->outImage->rowbytes*y + x*4);

//	rgba->alpha = 255;
//	rgba->red = g_Red;
//	rgba->green = g_Green;
//	rgba->blue = g_Blue;

//	if (x < m_rect.left) m_rect.left = x;
//	if (y < m_rect.top) m_rect.top = y;
//	if (x > m_rect.right) m_rect.right = x;
//	if (y > m_rect.bottom) m_rect.bottom = y;
}

inline bool CFlood::GetBit(SHORT x, SHORT y)
{
	uint8 * mask = m_alphabits2 + m_width*y+x;

	return (*mask);
}

inline bool CFlood::IsPixel(SHORT x, SHORT y)
{
	if ((x >= 0) && (y >= 0) && (x < m_width) && (y < m_height))
	{
		if (GetBit(x, y)) return false;	// Already set

		LDraw::PixelRGBAP_32	rgba = *(LDraw::PixelRGBAP_32*)((uint8*)m_inImage->Scan0 + m_inImage->Stride*y + x*4);

		rgba.r = ((int)rgba.r * rgba.a)/255;
		rgba.g = ((int)rgba.g * rgba.a)/255;
		rgba.b = ((int)rgba.b * rgba.a)/255;

		if (g_method == 0)	// RGB
		{
			if ((rgba.a >= alphaMin) && (rgba.a <= alphaMax) &&
				(rgba.r >= redMin) && (rgba.r<= redMax) &&
				(rgba.g >= grnMin) && (rgba.g <= grnMax) &&
				(rgba.b >= bluMin) && (rgba.b <= bluMax))
				return true;
			else
				return false;
		}
		else	// Luminance
		{
			int lum = (rgba.r + rgba.b + rgba.g)/3;

			if ((rgba.a >= alphaMin) && (rgba.a <= alphaMax) &&
				(lum >= lumMin) && (lum <= lumMax))
				return true;
			else
				return false;
		}
	}
	else
		return false;
}

inline void CFlood::AddPoint(SHORT x, SHORT y)
{
	m_ArrayPoints[m_numArrayPoints].x = x;
	m_ArrayPoints[m_numArrayPoints].y = y;
	m_numArrayPoints++;
}

inline void CFlood::DoUp(SHORT x, SHORT y)
{
	while (IsPixel(x, --y))
	{
		SetBit(x, y);
		if (IsPixel(x-1, y-1)) AddPoint(x-1, y-1);
		if (IsPixel(x+1, y-1)) AddPoint(x+1, y-1);
	}
}

inline void CFlood::DoDown(SHORT x, SHORT y)
{
	while (IsPixel(x, ++y))
	{
		SetBit(x, y);
		if (IsPixel(x-1, y+1)) AddPoint(x-1, y+1);
		if (IsPixel(x+1, y+1)) AddPoint(x+1, y+1);
	}
}

inline void CFlood::DoLeft(SHORT x, SHORT y)
{
	while (IsPixel(--x, y))
	{
		DoUp(x, y);
		DoDown(x, y);
		SetBit(x, y);
	}
}

inline void CFlood::DoRight(SHORT x, SHORT y)
{
	while (IsPixel(++x, y))
	{
		DoUp(x, y);
		DoDown(x, y);
		SetBit(x, y);
	}
}

void CFlood::FloodFill(SHORT x, SHORT y, int tolerance)
{
	if ((x < 0) || (y < 0) || (x >= m_width) || (y >= m_height)) return;

	LDraw::PixelRGBAP_32	rgba = *(LDraw::PixelRGBAP_32*)((uint8*)m_inImage->Scan0 + m_inImage->Stride*y + x*4);

	rgba.r = ((int)rgba.r * rgba.a)/255;
	rgba.g = ((int)rgba.g * rgba.a)/255;
	rgba.b = ((int)rgba.b * rgba.a)/255;

	if (g_method == 0)
	{
		if ((alphaMin = rgba.a-tolerance) < 0) alphaMin = 0;
		if ((alphaMax = rgba.a+tolerance) > 255) alphaMax = 255;

		if ((redMin = rgba.r-tolerance) < 0) redMin = 0;
		if ((redMax = rgba.r+tolerance) > 255) redMax = 255;

		if ((grnMin = rgba.g-tolerance) < 0) grnMin = 0;
		if ((grnMax = rgba.g+tolerance) > 255) grnMax = 255;

		if ((bluMin = rgba.b-tolerance) < 0) bluMin = 0;
		if ((bluMax = rgba.b+tolerance) > 255) bluMax = 255;
	}
	else
	{
		int lum = (rgba.r + rgba.b + rgba.g)/3;
		if ((lumMin = lum-tolerance) < 0) lumMin = 0;
		if ((lumMax = lum+tolerance) > 255) lumMax = 255;
	}

	AddPoint(x, y);

	while (m_numArrayPoints > 0)
	{
		m_numArrayPoints--;
		int x = m_ArrayPoints[m_numArrayPoints].x;
		int y = m_ArrayPoints[m_numArrayPoints].y;

		if (IsPixel(x, y))
		{
			DoUp(x, y);
			DoDown(x, y);
			DoLeft(x, y);
			DoRight(x, y);
			SetBit(x, y);
		}
	}
}

////////////////

#if 0
void MyEmptyRect(LDraw::RectI * lprect)
{
	lprect->X = 0x7fffff;
	lprect->Y = 0x7fffff;
	lprect->Width = 0x80000000;
	lprect->Height = 0x80000000;
/*
	lprect->left = 80000;
	lprect->top = 80000;
	lprect->right = -80000;
	lprect->bottom = -80000;
*/
}
#endif

bool MyIsRectEmpty(LDraw::BBoxi * lprect)
{
	return ((lprect->left > lprect->right) ||
				(lprect->top > lprect->bottom));
}

inline bool SelHasBitRow(uint8 * sel, int width)
{
	for (int x = 0; x < width; x++)
	{
		if (*sel) return true;
		sel += 4;
	}

	return false;
}

inline bool SelHasBitCol(uint8 * sel, int height, int rowBytes)
{
	for (int y = 0; y < height; y++)
	{
		if (*sel) return true;
		sel += rowBytes;
	}

	return false;
}

// TODO : Latest changes not tested
void GetAlphaBounds(ImageDef* image, LDraw::RectI* lprect)
{
//	MyEmptyRect(lprect);

	int rowBytes = image->Stride;
	int x, y;

// Top
	for (y = 0; y < image->Height; y++)
	{
		uint8 * sel = &((LDraw::PixelRGBAP_32*)((uint8*)image->Scan0 + rowBytes*y))->a;
		if (SelHasBitRow(sel, image->Width))
		{
//			lprect->Y = y;
			break;
		}
	}

	lprect->Y = y;

// Bottom
	for (y = image->Height-1; y >= 0; y--)
	{
		uint8 * sel = &((LDraw::PixelRGBAP_32*)((uint8*)image->Scan0 + rowBytes*y))->a;
		if (SelHasBitRow(sel, image->Width))
		{
//			lprect->Height = y - lprect->Y;
			break;
		}
	}
	lprect->Height = y - lprect->Y;

// Left
	for (x = 0; x < image->Width; x++)
	{
		uint8 * sel = &((LDraw::PixelRGBAP_32*)((uint8*)image->Scan0 + x*4))->a;
		if (SelHasBitCol(sel, image->Height, rowBytes))
		{
//			lprect->X = x;
			break;
		}
	}
	lprect->X = x;

// Right
	for (x = image->Width-1; x >= 0; x--)
	{
		uint8 * sel = &((LDraw::PixelRGBAP_32*)((uint8*)image->Scan0 + x*4))->a;
		if (SelHasBitCol(sel, image->Height, rowBytes))
		{
//			lprect->Width = x - lprect->X;
			break;
		}
	}

	lprect->Width = x - lprect->X;
}


///////////

#define dToR(d) ((d)*(M_PI/180))

void
Emboss(
		 double azimuth, double elevation,	/* light source direction */
		 int width45,			/* filter width */
		 LDraw::BitmapData* bump2,			/* monochrome bump image */
		 LDraw::BitmapData* texture2, LDraw::BitmapData* dst2,	/* texture & output images */
		 int xSize, int ySize,	/* image size */
	//	 WORD	iRowBytes, WORD aRowBytes,
	LDraw::BBoxi* lprect
		 )
{
	long Nx, Ny, Nz, Lx, Ly, Lz, Nz2, NzLz, NdotL;
	short shade, background;
	int x, y;
	
#define pixelScale 255.9
	
	/*
	* compute the light vector from the input parameters.
	* normalize the length to pixelScale for fast shading calculation.
	*/
	Lx = cos(azimuth) * cos(elevation) * pixelScale;
	Ly = sin(azimuth) * cos(elevation) * pixelScale;
	Lz = sin(elevation) * pixelScale;

	/*
	* constant z component of image surface normal - this depends on the
	* image slope we wish to associate with an angle of 45 degrees, which
	* depends on the width of the filter used to produce the source image.
	*/
	Nz = (6 * 255) / width45;
	Nz2 = Nz * Nz;
	NzLz = Nz * Lz;
	
	/* optimization for vertical normals: L.[0 0 1] */
	background = Lz;

	LDraw::BBoxi	rect = *lprect;

	rect.left--;
	rect.top--;
	rect.right++;
	rect.bottom++;

// This assumes that there is a row/column extra at right/bottom
// TODO
	if (rect.left < 1) rect.left = 1;
	if (rect.top < 1) rect.top = 1;
	if (rect.right > xSize-2) rect.right = xSize-2;
	if (rect.bottom > ySize-2) rect.bottom = ySize-2;

	for (y = rect.top; y <= rect.bottom; y++)
	{
		LDraw::PixelRGBAP_32*	dst = (LDraw::PixelRGBAP_32*)((uint8*)dst2->Scan0 + dst2->Stride*y + rect.left*4);
		LDraw::PixelRGBAP_32*	texture = (LDraw::PixelRGBAP_32*)((uint8*)texture2->Scan0 + texture2->Stride*y + rect.left*4);
		uint8 * bump = (uint8*)((uint8*)bump2->Scan0 + bump2->Stride*y + rect.left*2);
		
		uint16 * s1 = (uint16*)(bump - bump2->Stride);
		uint16 * s2 = (uint16*)(bump);
		uint16 * s3 = (uint16*)(bump + bump2->Stride);

		for (x = rect.left; x <= rect.right; x++)
		{
		/*
	     * compute the normal from the bump map. the type of the expression
		  * before the cast is compiler dependent. in some cases the sum is
		  * unsigned, in others it is signed. ergo, cast to signed.
			*/
			Nx = (int)(s1[-1] + s2[-1] + s3[-1] - s1[1] - s2[1] - s3[1]);
			Ny = (int)(s3[-1] + s3[0] + s3[1] - s1[-1] - s1[0] - s1[1]);
			
			/* shade with distant light source */
			if ( Nx == 0 && Ny == 0 )
				shade = background;
			else if ( (NdotL = Nx*Lx + Ny*Ly + NzLz) < 0 )
				shade = 0;
			else
				shade = NdotL / sqrt((double)Nx*Nx + Ny*Ny + Nz2);
			
			/* do something with the shading result */
			if ( texture2 )
			{
			//	dst->red = (texture->red * shade) / 255;
			//	dst->green = (texture->green * shade) / 255;
			//	dst->blue = (texture->blue * shade) / 255;

				dst->r = MAX(MIN((texture->r + (shade-127)), 255), 0);
				dst->g = MAX(MIN((texture->g + (shade-127)), 255), 0);
				dst->b = MAX(MIN((texture->b + (shade-127)), 255), 0);
				dst->a = texture->a;
			}
			else
			{
				dst->r = shade;
				dst->g = shade;
				dst->b = shade;
				dst->a = 255;	// ???
			}

			texture++;
			dst++;

			s1++;
			s2++;
			s3++;
		}
	}
}


////////////

void CStrokeObject::BltBrush(
	ImageDef* inImage,
	ImageDef* inDepth,
	ImageDef* outImage,
	double px, double py,
	const int opacity,
	const int grain,
	ImageDef* brushImage,
	ImageDef* paperImage,
	LDraw::RectI* lpclip,
	LDraw::RectI* lprect)
{
	ASSERT(0);
#if 0
	if (!m_pMethod)
	{
		ATLASSERT(0);
		return;
	}

#if 0
	CI2DLayer* pParent = GetParentLayer();
	ASSERT(pParent);
#endif

	ASSERT(outImage);
	ASSERT(lpclip);
//	ASSERT(lpclip->left >= 0);
//	ASSERT(lpclip->top >= 0);
//	ASSERT(lpclip->right < outImage->width);
//	ASSERT(lpclip->bottom < outImage->height);

	int	width = brushImage->Width;
	int	height = brushImage->Height;
	int	width2 = brushImage->Width/2;
	int	height2 = brushImage->Height/2;

//	long drawwith;
//	m_paramID[SHAPE_COLORDEPTH]->GetParamTags((PARAM_POPUP_Value), &drawwith, (TAG_DONE));
	BOOL bDrawColor = TRUE;//(drawwith == 0) || (drawwith == 2);
	BOOL bDrawDepth = TRUE;//(drawwith == 1) || (drawwith == 2);
	/*
	if (!pParent->GetImageDepth()) bDrawDepth = FALSE;
	*/
	if (inDepth == NULL) bDrawDepth = FALSE;

	RECT	rect;

	px -= width2;
	py -= height2;
	SetRect(&rect, px, py, px+width-1, py+height-1);

	if (rect.left < lpclip->left) rect.left = lpclip->left;
	if (rect.top < lpclip->top) rect.top = lpclip->top;
	if (rect.right > lpclip->right) rect.right = lpclip->right;
	if (rect.bottom > lpclip->bottom) rect.bottom = lpclip->bottom;

	if ((rect.left <= rect.right) && (rect.top <= rect.bottom))
	{
		*lprect = rect;

		int x1 = rect.left-px;
		int y1 = rect.top-py;
		int x2 = rect.right-px;
		int y2 = rect.bottom-py;

		LDraw::BitmapData* m_tImage = new LDraw::BitmapData;
		m_tImage->Width = brushImage->Width;
		m_tImage->Height = brushImage->Height;
		m_tImage->Stride = brushImage->Stride;
		m_tImage->Scan0 = (uint8*)GlobalAlloc(0, m_tImage->Stride * m_tImage->Height);

		int mindepth = 65535;
		int maxdepth = 0;
//		int depthrange;

		LDraw::BitmapData* m_tDepth = NULL;
		if (inDepth)
		{
			m_tDepth = new LDraw::BitmapData;
			m_tDepth->Width = brushImage->Width;
			m_tDepth->Height = brushImage->Height;
			m_tDepth->Stride = ROWBYTES(brushImage->Width, 16);
			m_tDepth->Scan0 = (uint8*)GlobalAlloc(0, m_tDepth->Stride * m_tDepth->Height);

		//	m_tDepth->AllocImage(brushImage->width, brushImage->height, IMODE_GRAY16, FALSE);

		// Fill temp with parent's depth buffer
			int y0 = y1;
			int y = y0 + py;

			for (; y0 <= y2; y0++, y++)
			{
				int x0 = x1;
				int x = x0 + px;

				LPWORD d = (LPWORD)((BYTE*)inDepth->Scan0 + inDepth->Stride*y + x*2);
				LPWORD t = (LPWORD)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);

				for (; x0 <= x2; x0++, x++)
				{
					if (*d < mindepth) mindepth = *d;
					if (*d > maxdepth) maxdepth = *d;

					*t++ = *d++;
				}
			}

		//	depthrange = maxdepth - mindepth + 1;
		}

	//	TRACE("inImage: %d, %d\n", inImage->width, inImage->height);

		m_effectRecord->sourceWidth = inImage->Width;
		m_effectRecord->sourceHeight = inImage->Height;
		m_effectRecord->boffset_x = x1;
		m_effectRecord->boffset_y = y1;
		m_effectRecord->uRect.left = rect.left;
		m_effectRecord->uRect.top = rect.top;
		m_effectRecord->uRect.right = rect.right;
		m_effectRecord->uRect.bottom = rect.bottom;

		m_effectRecord->inImage = inImage;
		m_effectRecord->outImage = m_tImage;
		m_effectRecord->brushImage = brushImage;
		m_effectRecord->inDepth = inDepth;
		m_effectRecord->outDepth = m_tDepth;

//		CAnimFrame* pFrame = GetComposition()->GetFrameAt(GetComposition()->m_framePos);
	//	m_effectRecord->bgImage = sVid->GetFrameImage(GetLayerLayer()->GetVideoData(), GetLayerLayer()->m_framePos);

		m_pMethod->m_method->FilterRect(m_effectRecord);

#if 0
		{
			for (int y = 0; y < m_tImage->Height; y++)
			{
				LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)((BYTE*)m_tImage->Scan0 + m_tImage->Stride*y);
				LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((BYTE*)brushImage->Scan0 + brushImage->Stride*y);
				for (int x = 0; x < m_tImage->Width; x++)
				{
					/*
					p->red = s->red;
					p->green = s->green;
					p->blue = s->blue;
					*/
					p->alpha = 0;//255;

					p++;
					s++;
				}
			}
		}
#endif

#if 0
		ImageDef* imageSel;
		BOOL bHasSelection = GetParentLayer()->HasSelectionYet();
		if (bHasSelection)
		{
			ASSERT(GetParentLayer()->GetImageSel());
			imageSel = GetParentLayer()->GetImageSel();
		}
#endif

		int y0 = y1;
		int y = y0 + py;

		for (; y0 <= y2; y0++, y++)
		{
			int x0 = x1;
			int x = x0 + px;

			LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((BYTE*)inImage->Scan0 + inImage->Stride*y + x*4);
			LDraw::PixelRGBAP_32* d = (LDraw::PixelRGBAP_32*)((BYTE*)outImage->Scan0 + outImage->Stride*y + x*4);

			LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((BYTE*)brushImage->Scan0 + brushImage->Stride*y0 + x0*4);
			LDraw::PixelRGBAP_32* t = (LDraw::PixelRGBAP_32*)((BYTE*)m_tImage->Scan0 + m_tImage->Stride*y0 + x0*4);

			LPWORD dd, sd;
			if (bDrawDepth)
			{
				dd = (WORD*)((BYTE*)inDepth->Scan0 + inDepth->Stride*y + x*2);
				sd = (WORD*)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);
			}

			LDraw::PixelRGBAP_32* sel;
#if 0
			if (bHasSelection)
			{
				sel = (LDraw::PixelRGBAP_32*)(imageSel->data + imageSel->rowbytes*y + x*4);
			}
#endif

			for (; x0 <= x2; x0++, x++)
			{
				ASSERT(!IsBadWritePtr(t, 4) && !IsBadWritePtr(d, 4) && !IsBadWritePtr(s, 4));

				LDraw::PixelRGBAP_32* paper = NULL;

				if (paperImage)	// Paper
				{
					int papx = x % paperImage->Width;
					int papy = y % paperImage->Height;

					paper = (LDraw::PixelRGBAP_32*)((BYTE*)paperImage->Scan0 + paperImage->Stride*papy + papx*4);
				}

				if (FALSE)	// Grainy Edge flat color
				{
					int threshold = (grain*paper->alpha)>>8;

					if (s->alpha > threshold)
					{
						d->red = t->red;
						d->green = t->green;
						d->blue = t->blue;
						d->alpha = t->alpha;
					}
				}
				else
				{
				//	BYTE alpha = 255;//((((short)s->alpha) * opacity + 127) >> 8);
					BYTE alpha = ((((short)s->alpha) * opacity + 127) >> 8);

					if (bDrawColor)
					{
#if 0
						if (bHasSelection) alpha = ((short)alpha * sel->alpha)>>8;
#endif
						if (paper) alpha = ((int)alpha*paper->alpha)>>8;

						d->red = d->red + ((((short)t->red - d->red) * alpha + 127) >> 8);
						d->green = d->green + ((((short)t->green - d->green) * alpha + 127) >> 8);
						d->blue = d->blue + ((((short)t->blue - d->blue) * alpha + 127) >> 8);
						d->alpha = d->alpha + ((((short)t->alpha - d->alpha) * alpha + 127) >> 8);
					}
					else
					{
						*d = *in;
					}

					if (bDrawDepth)
					{
						double dalpha = (alpha/255.0);

						int depth1 = *dd + alpha;
						int depth2 = mindepth + alpha;

						long ndepth;

						ndepth = (1-dalpha)*(depth1) + (dalpha)*(depth2);
						ndepth = (1-dalpha)*(ndepth) + (dalpha)*(*sd);

						if (ndepth > 65535) ndepth = 65535;
						else if (ndepth < 0) ndepth = 0;
						*dd = ndepth;
					}
				}

				d++;
				s++;
				t++;
				sel++;

				sd++;
				dd++;

				in++;
			}
		}

		if (m_tDepth)
		{
			GlobalFree(m_tDepth->Scan0);
			delete m_tDepth;
		}

		GlobalFree(m_tImage->Scan0);
		delete m_tImage;
	}
#endif
}

#if 0
void SubPixelSample(ImageDef* inImage, long xpos, long ypos, LDraw::PixelRGBAP_32* dest);

void CStrokeObject::BltBrush(
	ImageDef* inImage,
	ImageDef* inDepth,
	ImageDef* outImage,
	double px, double py,
	const int opacity,
	const int grain,
	ImageDef* brushImage,
	ImageDef* paperImage,
	LPRECT lpclip,
	LPRECT lprect)
{
	if (!m_pMethod)
	{
		ATLASSERT(0);
		return;
	}

#if 0
	CI2DLayer* pParent = GetParentLayer();
	ASSERT(pParent);
#endif

	ASSERT(outImage);
	ASSERT(lpclip);
//	ASSERT(lpclip->left >= 0);
//	ASSERT(lpclip->top >= 0);
//	ASSERT(lpclip->right < outImage->width);
//	ASSERT(lpclip->bottom < outImage->height);

	int	width = brushImage->Width;
	int	height = brushImage->Height;
	int	width2 = brushImage->Width/2;
	int	height2 = brushImage->Height/2;

//	long drawwith;
//	m_paramID[SHAPE_COLORDEPTH]->GetParamTags((PARAM_POPUP_Value), &drawwith, (TAG_DONE));
	BOOL bDrawColor = TRUE;//(drawwith == 0) || (drawwith == 2);
	BOOL bDrawDepth = TRUE;//(drawwith == 1) || (drawwith == 2);
	/*
	if (!pParent->GetImageDepth()) bDrawDepth = FALSE;
	*/
	if (inDepth == NULL) bDrawDepth = FALSE;

	RECT	rect;

	px -= width2;
	py -= height2;
	SetRect(&rect, px, py, px+width-1, py+height-1);

	if (rect.left < lpclip->left) rect.left = lpclip->left;
	if (rect.top < lpclip->top) rect.top = lpclip->top;
	if (rect.right > lpclip->right) rect.right = lpclip->right;
	if (rect.bottom > lpclip->bottom) rect.bottom = lpclip->bottom;

	if ((rect.left <= rect.right) && (rect.top <= rect.bottom))
	{
		*lprect = rect;

		int x1 = rect.left-px;
		int y1 = rect.top-py;
		int x2 = rect.right-px;
		int y2 = rect.bottom-py;

		LDraw::BitmapData* m_tImage = new LDraw::BitmapData;
		m_tImage->Width = brushImage->Width;
		m_tImage->Height = brushImage->Height;
		m_tImage->Stride = brushImage->Stride;
		m_tImage->Scan0 = GlobalAlloc(0, m_tImage->Stride * m_tImage->Height);

		int mindepth = 65535;
		int maxdepth = 0;
//		int depthrange;

		LDraw::BitmapData* m_tDepth = NULL;
		if (inDepth)
		{
			m_tDepth = new LDraw::BitmapData;
			m_tDepth->Width = brushImage->Width;
			m_tDepth->Height = brushImage->Height;
			m_tDepth->Stride = ROWBYTES(brushImage->Width, 16);
			m_tDepth->Scan0 = GlobalAlloc(0, m_tDepth->Stride * m_tDepth->Height);

		//	m_tDepth->AllocImage(brushImage->width, brushImage->height, IMODE_GRAY16, FALSE);

		// Fill temp with parent's depth buffer
			int y0 = y1;
			int y = y0 + py;

			for (; y0 <= y2; y0++, y++)
			{
				int x0 = x1;
				int x = x0 + px;

				LPWORD d = (LPWORD)((BYTE*)inDepth->Scan0 + inDepth->Stride*y + x*2);
				LPWORD t = (LPWORD)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);

				for (; x0 <= x2; x0++, x++)
				{
					if (*d < mindepth) mindepth = *d;
					if (*d > maxdepth) maxdepth = *d;

					*t++ = *d++;
				}
			}

		//	depthrange = maxdepth - mindepth + 1;
		}

	//	TRACE("inImage: %d, %d\n", inImage->width, inImage->height);

		m_effectRecord->sourceWidth = inImage->Width;
		m_effectRecord->sourceHeight = inImage->Height;
		m_effectRecord->boffset_x = x1;
		m_effectRecord->boffset_y = y1;
		m_effectRecord->uRect.left = rect.left;
		m_effectRecord->uRect.top = rect.top;
		m_effectRecord->uRect.right = rect.right;
		m_effectRecord->uRect.bottom = rect.bottom;

		m_effectRecord->inImage = inImage;
		m_effectRecord->outImage = m_tImage;
		m_effectRecord->brushImage = brushImage;
		m_effectRecord->inDepth = inDepth;
		m_effectRecord->outDepth = m_tDepth;

//		CAnimFrame* pFrame = GetComposition()->GetFrameAt(GetComposition()->m_framePos);
	//	m_effectRecord->bgImage = sVid->GetFrameImage(GetLayerLayer()->GetVideoData(), GetLayerLayer()->m_framePos);

		m_pMethod->m_method->FilterRect(m_effectRecord);

#if 0
		{
			for (int y = 0; y < m_tImage->Height; y++)
			{
				LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)((BYTE*)m_tImage->Scan0 + m_tImage->Stride*y);
				LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((BYTE*)brushImage->Scan0 + brushImage->Stride*y);
				for (int x = 0; x < m_tImage->Width; x++)
				{
					/*
					p->red = s->red;
					p->green = s->green;
					p->blue = s->blue;
					*/
					p->alpha = 0;//255;

					p++;
					s++;
				}
			}
		}
#endif

#if 0
		ImageDef* imageSel;
		BOOL bHasSelection = GetParentLayer()->HasSelectionYet();
		if (bHasSelection)
		{
			ASSERT(GetParentLayer()->GetImageSel());
			imageSel = GetParentLayer()->GetImageSel();
		}
#endif

		int y0 = y1;
		int y = (y0 + py)*65536;

		for (; y0 <= y2; y0++, y += 65536)
		{
			int x0 = x1;
			int x = (x0 + px)*65536;

			//LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((BYTE*)inImage->Scan0 + inImage->Stride*y + x*4);
			LDraw::PixelRGBAP_32* d = (LDraw::PixelRGBAP_32*)((BYTE*)outImage->Scan0 + outImage->Stride*y + x*4);

			LDraw::PixelRGBAP_32* s = (LDraw::PixelRGBAP_32*)((BYTE*)brushImage->Scan0 + brushImage->Stride*y0 + x0*4);
			LDraw::PixelRGBAP_32* t = (LDraw::PixelRGBAP_32*)((BYTE*)m_tImage->Scan0 + m_tImage->Stride*y0 + x0*4);

			LDraw::PixelRGBAP_32 _in;
			SubPixelSample(inImage, x, y, &_in);
			LDraw::PixelRGBAP_32* in = &_in;

			LPWORD dd, sd;
			if (bDrawDepth)
			{
				dd = (WORD*)((BYTE*)inDepth->Scan0 + inDepth->Stride*y + x*2);
				sd = (WORD*)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);
			}

			LDraw::PixelRGBAP_32* sel;
#if 0
			if (bHasSelection)
			{
				sel = (LDraw::PixelRGBAP_32*)(imageSel->data + imageSel->rowbytes*y + x*4);
			}
#endif

			for (; x0 <= x2; x0++, x += 65536)
			{
				ASSERT(!IsBadWritePtr(t, 4) && !IsBadWritePtr(d, 4) && !IsBadWritePtr(s, 4));

				LDraw::PixelRGBAP_32* paper = NULL;

				if (paperImage)	// Paper
				{
					int papx = x % paperImage->Width;
					int papy = y % paperImage->Height;

					paper = (LDraw::PixelRGBAP_32*)((BYTE*)paperImage->Scan0 + paperImage->Stride*papy + papx*4);
				}

				if (FALSE)	// Grainy Edge flat color
				{
					int threshold = (grain*paper->alpha)>>8;

					if (s->alpha > threshold)
					{
						d->red = t->red;
						d->green = t->green;
						d->blue = t->blue;
						d->alpha = t->alpha;
					}
				}
				else
				{
				//	BYTE alpha = 255;//((((short)s->alpha) * opacity + 127) >> 8);
					BYTE alpha = ((((short)s->alpha) * opacity + 127) >> 8);

					if (bDrawColor)
					{
#if 0
						if (bHasSelection) alpha = ((short)alpha * sel->alpha)>>8;
#endif
						if (paper) alpha = ((int)alpha*paper->alpha)>>8;

						d->red = d->red + ((((short)t->red - d->red) * alpha + 127) >> 8);
						d->green = d->green + ((((short)t->green - d->green) * alpha + 127) >> 8);
						d->blue = d->blue + ((((short)t->blue - d->blue) * alpha + 127) >> 8);
						d->alpha = d->alpha + ((((short)t->alpha - d->alpha) * alpha + 127) >> 8);
					}
					else
					{
						*d = *in;
					}

					if (bDrawDepth)
					{
						double dalpha = (alpha/255.0);

						int depth1 = *dd + alpha;
						int depth2 = mindepth + alpha;

						long ndepth;

						ndepth = (1-dalpha)*(depth1) + (dalpha)*(depth2);
						ndepth = (1-dalpha)*(ndepth) + (dalpha)*(*sd);

						if (ndepth > 65535) ndepth = 65535;
						else if (ndepth < 0) ndepth = 0;
						*dd = ndepth;
					}
				}

				d++;
				s++;
				t++;
				sel++;

				sd++;
				dd++;

				in++;
			}
		}


		if (m_tDepth)
		{
			GlobalFree(m_tDepth->Scan0);
			delete m_tDepth;
		}

		GlobalFree(m_tImage->Scan0);
		delete m_tImage;
	}
}
#endif

static int step;
static int stepCount;
static int brush_opacity = 255;
static int brush_grain;
static int brush_jitter;

double g_oldx;
double g_oldy;

void CStrokeObject::SetBrush(
		double x, double y,
		ImageDef* inImage,
		ImageDef* inDepth,
		ImageDef* outImage)
{
	//if (step > stepCount)
	{
	//	CComposition* pComp = (CComposition*)GetComposition();
	//	ASSERT(pComp->IsValid());

	//	double xsampling = pComp->m_XSampling/65536.0;
	//	double ysampling = pComp->m_YSampling/65536.0;

		m_effectRecord->dx = (x-g_oldx);///xsampling;
		m_effectRecord->dy = (y-g_oldy);///ysampling;

		g_oldx = x;
		g_oldy = y;

		/*
		if (brush_jitter)
		{
			x += -brush_jitter/2 + rand()%brush_jitter;
			y += -brush_jitter/2 + rand()%brush_jitter;
		}
		*/

	//	CI2DLayer* pParent = GetParentLayer();
	//	ASSERT(pParent);

		//ImageDef* inImage = GetDrawOnParentLayer()->TOP()->GetImage();
		//ImageDef* outImage = inImage;//pParent->TOP()->GetImage();

		LDraw::RectI	rect(99999, 99999, -99999, -999999);
		//MyEmptyRect(&rect);

//		int xsampling = pComp->m_XSampling>>16;
//		int ysampling = pComp->m_YSampling>>16;

		LDraw::RectI clipRect2 = m_clipRect;
		/*
		clipRect2.left /= xsampling;
		clipRect2.right /= xsampling;
		clipRect2.top /= ysampling;
		clipRect2.bottom /= ysampling;
		*/

		LDraw::BitmapData brushData;
		m_pBrushBitmap->LockBits(
			&LDraw::RectI(0, 0, m_pBrushBitmap->GetWidth(), m_pBrushBitmap->GetHeight()),
			LDraw::ImageLockModeRead,
			/*PixelFormat32bppARGB,*/ &brushData);

			ASSERT(0);
#if 0
		//ASSERT(m_cachedBrush);
		BltBrush(
			inImage,
			inDepth,
			outImage,
			x, y, brush_opacity, brush_grain,
			&brushData,//m_cachedBrush,
			NULL,//m_paperImage,
			&clipRect2, &rect);
#endif
		m_pBrushBitmap->UnlockBits(&brushData);

		double xsampling = 1;
		double ysampling = 1;

		rect.X *= xsampling;
		rect.Width *= xsampling;
		rect.Y *= ysampling;
		rect.Height *= ysampling;

		ASSERT(0);
#if 0
		if (rect.left < m_updateRect.left) m_updateRect.left = rect.left;
		if (rect.top < m_updateRect.top) m_updateRect.top = rect.top;
		if (rect.right > m_updateRect.right) m_updateRect.right = rect.right;
		if (rect.bottom > m_updateRect.bottom) m_updateRect.bottom = rect.bottom;

		if (rect.left < m_imageRect.left) m_imageRect.left = rect.left;
		if (rect.top < m_imageRect.top) m_imageRect.top = rect.top;
		if (rect.right > m_imageRect.right) m_imageRect.right = rect.right;
		if (rect.bottom > m_imageRect.bottom) m_imageRect.bottom = rect.bottom;
#endif

		step = 0;
	}

	step++;
}

bool CStrokeObject::BeginBrushStroke(double scaleX, double scaleY)
{
#if 0
	CComposition* pComp = (CComposition*)GetComposition();

	COLORREF	cref;
	m_paramID[SHAPE_COLOR]->GetParamTags((PARAM_COLOR_Value), &cref, (TAG_DONE));

	srand(5000);

	m_brushImage = (ImageDef*)sBasic->CreateCmdTarget(IID_IMAGE);
	if (!m_brushImage) return FALSE;

	m_tImage = (ImageDef*)sBasic->CreateCmdTarget(IID_IMAGE);

// Temporary depth buffer
	m_tDepth = (ImageDef*)sBasic->CreateCmdTarget(IID_IMAGE);

	if (!MakeBrushImage(m_brushImage, cref))
		return FALSE;

	m_paperImage = NULL;

	if (m_paperRes)
	{
		m_paperImage = (ImageDef*)sBasic->CreateCmdTarget(IID_IMAGE);
		MakePaperImage(m_paperImage);
	}

	ASSERT(m_effectRecord);
	m_effectRecord->x_sampling = pComp->m_XSampling;
	m_effectRecord->y_sampling = pComp->m_YSampling;

	ASSERT(m_brushCache.GetSize() == 0);

	step = 0;
#endif

	m_effectRecord = new PFILTERRECORD;

	m_imageRect = LDraw::RectI(99999, 99999, -99999, -99999);

	m_effectRecord->x_sampling = 1;
	m_effectRecord->y_sampling = 1;

	{
		LDraw::Bitmap* pBitmap = m_pBrushTip->GetBitmap();

		m_pBrushBitmap = pBitmap;
#if 0
		m_pBrushBitmap = new LDraw::Bitmap(ceil(m_brushSize*scaleX), ceil(m_brushSize*scaleY)/*, PixelFormat32bppARGB*/);

		LDraw::Graphics graphics(m_pBrushBitmap);
		graphics.DrawImage(
			pBitmap,
			LDraw::RectF(0, 0, ceil(m_brushSize*scaleX), ceil(m_brushSize*scaleY)),
			(float)0, (float)0, (float)pBitmap->GetWidth(), (float)pBitmap->GetHeight()/*,
			LDraw::UnitPixel*/);
#endif
	}

	{
		LDraw::BitmapData brushData;
		m_pBrushBitmap->LockBits(
			&LDraw::RectI(0, 0, m_pBrushBitmap->GetWidth(), m_pBrushBitmap->GetHeight()),
			LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
			/*PixelFormat32bppARGB,*/ &brushData);
		{
			for (int y = 0; y < brushData.Height; y++)
			{
				LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)((uint8*)brushData.Scan0 + brushData.Stride*y);
				for (int x = 0; x < brushData.Width; x++)
				{
					//p->alpha = (p->red+p->green+p->blue)/3;
					p->r = m_color[0] * p->a / 255;
					p->g = m_color[1] * p->a / 255;
					p->b = m_color[2] * p->a / 255;

					p++;
				}
			}

			m_pBrushBitmap->UnlockBits(&brushData);
		}
	}

	return true;
}

void CStrokeObject::EndBrushStroke()
{
	// TODO, use cache instead
	if (m_pBrushBitmap)
	{
	//	delete m_pBrushBitmap;
		m_pBrushBitmap = NULL;
	}

	delete m_effectRecord;
	m_effectRecord = NULL;

#if 0
	for (int i = 0; i < m_brushCache.GetSize(); i++)
	{
		ImageDef* pImage = m_brushCache[i];
		ASSERT(pImage && pImage->data);

		pImage->Release();
	}

	m_brushCache.RemoveAll();

	m_brushImage->Release();
	m_brushImage = NULL;

	m_tImage->Release();
	m_tImage = NULL;

	m_tDepth->Release();
	m_tDepth = NULL;


	if (m_paperImage)
	{
		m_paperImage->Release();
		m_paperImage = NULL;
	}
#endif
}

void CStrokeObject::OnRender(UI::Graphics* pGraphics)
{
	//	LDraw::Graphics graphics(new LDraw::GraphicsO(pInBitmap));

	UI::Graphics& graphics = *pGraphics;

	LDraw::SmoothingMode oldSmoothingMode = graphics.GetSmoothingMode();
	graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	if (m_points.GetSize() > 0)
	{
		LDraw::PointD oldpt = m_points[0];

		for (int i = 1; i < m_points.GetSize(); i++)
		{
			LDraw::PointD wpt = m_points[i];

			double dx = (wpt.X - oldpt.X);
			double dy = (wpt.Y - oldpt.Y);

			double length = sqrt(dx*dx + dy*dy);

			double factor = 5;

			/*
			if (nsteps == 0)
				nsteps = 1;
				*/

			dx /= length;
			dy /= length;
			dx *= m_brushSize * factor;
			dy *= m_brushSize * factor;

			int nsteps = length / (m_brushSize * factor);

		//	double dx = (wpt.X - g_oldx) / nsteps;
		//	double dy = (wpt.Y - g_oldy) / nsteps;

			double x = g_oldx;// + m_pStroke->m_brushSize/2;
			double y = g_oldy;// + m_pStroke->m_brushSize/2;

			for (int n = 0; n < nsteps; n++)
			{

			/*	LDraw::Matrix3f oldTransform =*/ graphics.PushTransform();
				graphics.TranslateTransform(x, y);
				graphics.RotateTransform(45);
				graphics.ScaleTransform(1, 5);
				graphics.TranslateTransform(-m_brushSize/2, -m_brushSize/2);

				LDraw::RectF destRect(0, 0, m_brushSize, m_brushSize);
				graphics.DrawImage(m_pBrushBitmap, destRect, 0, 0, m_pBrushBitmap->GetWidth(), m_pBrushBitmap->GetHeight());

				graphics.PopTransform();//(oldTransform);
				x += dx;
				y += dy;
			}

			oldpt.X = x;
			oldpt.Y = y;
		}
	}

	graphics.SetSmoothingMode(oldSmoothingMode);
}

void CStrokeObject::Render(LDraw::Bitmap* pBitmap, double scaleX, double scaleY)
{
	LDraw::BitmapData inData;
	pBitmap->LockBits(
		&LDraw::RectI(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
		LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
		/*PixelFormat32bppARGB,*/ &inData);
	{
//		LDraw::Graphics graphics(pBitmap);

		LDraw::RectI clip(0, 0, pBitmap->GetWidth()-1, pBitmap->GetHeight()-1);
		//CRect rect;

		m_clipRect = clip;

		BeginBrushStroke(scaleX, scaleY);

		double brushSizeX = m_brushSize*scaleX;
		double brushSizeY = m_brushSize*scaleY;

		for (int i = 0; i < m_points.GetSize(); i++)
		{
			LDraw::PointD pt = LDraw::PointD(m_points[i].X*scaleX, m_points[i].Y*scaleY); 
			SetBrush(pt.X, pt.Y, &inData, NULL, &inData);

			/*
			graphics.DrawImage(m_pBrushBitmap,
				LDraw::RectF(pt.X-brushSizeX/2, pt.Y-brushSizeY/2, brushSizeX, brushSizeY),
				(float)0, (float)0, (float)brushSizeX, (float)brushSizeY,
				LDraw::UnitPixel);
				*/
		}
	}

	EndBrushStroke();

	pBitmap->UnlockBits(&inData);
}

#if 0
ErrorCode GetTransformRectBoundingBox(gmMatrix3& mat, RectD* bounds, RectD* pVal)
{
	PointD pts[4] =
	{
		PointD(bounds->X, bounds->Y),
		PointD(bounds->X+bounds->Width, bounds->Y),
		PointD(bounds->X+bounds->Width, bounds->Y+bounds->Height),
		PointD(bounds->X, bounds->Y+bounds->Height),
	};

	double minx = 9999999;
	double miny = 9999999;
	double maxx = -9999999;
	double maxy = -9999999;

	//LDraw::PointF	xpts[4];

	for (int i = 0; i < 4; i++)
	{
		PointD xpt = mat.transform(pts[i]);

		if (xpt.X < minx) minx = xpt.X;
		if (xpt.Y < miny) miny = xpt.Y;
		if (xpt.X > maxx) maxx = xpt.X;
		if (xpt.Y > maxy) maxy = xpt.Y;
	}

	pVal->X = minx;
	pVal->Y = miny;
	pVal->Width = maxx-minx;
	pVal->Height = maxy-miny;

	return S_OK;
}
#endif

/////////////////////////////////////////////////////////

PaintbrushTool::PaintbrushTool()
{
	m_pStroke = NULL;
	m_dragging = 0;
	m_oldpressure = 0;
}

ErrorCode PaintbrushTool::OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

	LDraw::matrix3f ilayermat = pLayerBitmap->m_matrix.getInverse();
	LDraw::PointF wpt = ilayermat.transform(LDraw::vector2f(point.X, point.Y));

	g_oldx = wpt.X;
	g_oldy = wpt.Y;
	m_oldpressure = pressure;

#if 0
	if (g_pImageApp->m_pActivePaintMethod)
#endif
	{
		pView->CaptureMouse();
		m_dragging = 1;

		m_pStroke = new CStrokeObject;
#if 0
		m_pStroke->m_pMethod = g_pImageApp->m_pActivePaintMethod;
#endif

		//m_pStroke->m_effectRecord->

		m_pStroke->m_pBrushTip = new CCircularBrushTip;//NULL;//g_pImageApp->m_pActiveBrushTip;
		/*
		{
			CCustomBrushTip* pCustom = new CCustomBrushTip;
			pCustom->m_filename = L"C:/brushtip0.png";

			m_pStroke->m_pBrushTip = pCustom;
		}
		*/

		m_pStroke->m_pBrushTip->m_refcount++;

		m_pStroke->m_brushSize = 5;//g_pImageApp->m_brushSize;
		m_pStroke->m_color[0] = 0;//pView->m_document->m_color[0];
		m_pStroke->m_color[1] = 0;//pView->m_document->m_color[1];
		m_pStroke->m_color[2] = 0;//pView->m_document->m_color[2];

		LDraw::RectI clip(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight());
		m_pStroke->m_clipRect = clip;

		m_pStroke->BeginBrushStroke(1, 1);
	}
#if 0
	else
	{
		::MessageBox(NULL/*GetMainHwnd()*/, "Select a paint method", "", MB_OK);
	}
#endif

	return Success;
}

ErrorCode PaintbrushTool::OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

	m_pStroke->EndBrushStroke();

#if 0
	m_pStroke->m_imageBitmap = new LDraw::Bitmap(m_pStroke->m_imageRect.Width, m_pStroke->m_imageRect.Height);

	LDraw::Graphics graphics(m_pStroke->m_imageBitmap);
	ASSERT(0);
#endif
#if 0
	graphics.DrawImage(pView->m_pActiveBitmap,
	// destination
		0, 0,
	// source
		m_pStroke->m_imageRect.left, m_pStroke->m_imageRect.top,
		m_pStroke->m_imageRect.Width(), m_pStroke->m_imageRect.Height()/*,
	//
		LDraw::UnitPixel*/);
#endif
	m_dragging = 0;
	pView->ReleaseMouseCapture();

	{
		LDraw::BitmapData bitmapData;
		pLayerBitmap->m_pBitmap->LockBits(
			&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
			LDraw::ImageLockModeRead,
			/*PixelFormat32bppARGB,*/ &bitmapData);

		GetAlphaBounds(&bitmapData, &pLayerBitmap->m_alphaBounds);

		pLayerBitmap->m_pBitmap->UnlockBits(&bitmapData);
	}

#if 0	// TODO, had this
	pView->m_pActiveGroup->m_objects.Add(m_pStroke);
#endif

	m_pStroke = NULL;

	return Success;
}

ErrorCode PaintbrushTool::OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	if (!m_dragging)
		return 0;

	LDraw::RectI client;
#if 0	// Had this
	pView->GetClientRect(&client);
#endif


	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

	LDraw::matrix3f ilayermat = pLayerBitmap->m_matrix.getInverse();
	LDraw::PointF wpt = ilayermat.transform(LDraw::vector2f(point.X, point.Y));

	double factor = 0.3;

	double dx = (wpt.X - g_oldx);
	double dy = (wpt.Y - g_oldy);

	double length = sqrt(dx*dx + dy*dy);
	if (length == 0)
		return 0;

	dx /= length;
	dy /= length;

	double minBrushSize = 0.2;
	double maxBrushSize = 10;

	double minOpacity = 0;
	double maxOpacity = 3;

	double startBrushSize = minBrushSize + m_oldpressure * (maxBrushSize - minBrushSize);
	double endBrushSize = minBrushSize + pressure * (maxBrushSize - minBrushSize);

	double startOpacity = minOpacity + m_oldpressure * (maxOpacity - minOpacity);
	double endOpacity = minOpacity + pressure * (maxOpacity - minOpacity);

	double startDx = dx * startBrushSize * factor;
	double endDx = dx * endBrushSize * factor;

	double startDy = dy * startBrushSize * factor;
	double endDy = dy * endBrushSize * factor;

	double brushSizeDelta = (endBrushSize - startBrushSize) / length;
	double opacityDelta = (endOpacity - startOpacity) / length;
	double dxDelta = (endDx - startDx) / length;
	double dyDelta = (endDy - startDy) / length;

	int nsteps = length / ((startBrushSize + endBrushSize)/2 * factor);

//	m_pStroke->m_points.Add(LDraw::PointD(point.X, point.Y));

	pView->m_pActiveBitmap = static_cast<CImageLayerBitmap*>(pView->m_pActiveLayer->m_layerUnknown)->m_pBitmap;
	LDraw::Bitmap* pInBitmap = pView->m_pActiveBitmap;//pLayerBitmap->m_pBitmap;
	LDraw::Bitmap* pOutBitmap = pView->m_pActiveBitmap;//pLayerBitmap->m_pBitmap;
	LDraw::Bitmap* pInDepthBitmap = pLayerBitmap->m_pBitmapDepth;

	LDraw::BitmapData inData;
#if 0
	pInBitmap->LockBits(
		&LDraw::RectI(0, 0, pInBitmap->GetWidth(), pInBitmap->GetHeight()),
		LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
		/*PixelFormat32bppARGB,*/ &inData);
#endif
		
	LDraw::BitmapData inDepthData;
	if (pInDepthBitmap)
	{
		pInDepthBitmap->LockBits(
			&LDraw::RectI(0, 0, pInBitmap->GetWidth(), pInBitmap->GetHeight()),
			LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
			/*PixelFormat16bppGrayScale,*/ &inDepthData);
	}


	LDraw::BitmapData outData = inData;
/*
	CRect clip(0, 0, inData.Width, inData.Height);
	//CRect rect;

	m_pStroke->m_clipRect = clip;
*/
	m_pStroke->m_updateRect = LDraw::RectI(99999, 99999, -99999, -99999);

	LDraw::RectD area;

#if 0
	m_pStroke->SetBrush(
		wpt.X, wpt.Y,
		&inData,
		pInDepthBitmap? &inDepthData : NULL,
		&outData/*,
		point.x, point.y, 255, 0, &brushData, NULL, &clip, &rect*/);
#endif
	{
		ASSERT(0);
#if 0
		UI::Graphics graphics(new LDraw::GraphicsO(pInBitmap));

	//	double dx = (wpt.X - g_oldx) / nsteps;
	//	double dy = (wpt.Y - g_oldy) / nsteps;

		double x = g_oldx;// + m_pStroke->m_brushSize/2;
		double y = g_oldy;// + m_pStroke->m_brushSize/2;

		LDraw::SmoothingMode oldSmoothingMode = graphics.GetSmoothingMode();
		graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		double opacity = startOpacity;
		double brushSize = startBrushSize;
		dx = startDx;
		dy = startDy;

		for (int n = 0; n < nsteps; n++)
		{
			if (brushSize > 0)
			{
				double minx = x - brushSize/2;
				double miny = y - brushSize/2;
				int iminx = floor(minx);
				int iminy = floor(miny);
				int iwidth = (int)ceil(brushSize);
				int iheight = (int)ceil(brushSize);

				LDraw::Bitmap* tbitmap = new LDraw::Bitmap(iwidth, iheight, LDraw::PixelFormat_t::RGBAP_32);
				int imaxx = iminx + tbitmap->GetWidth();
				int imaxy = iminy + tbitmap->GetHeight();
				{
					UI::Graphics graphics(new LDraw::GraphicsO(tbitmap));
					LDraw::RectF destRect(minx - iminx, miny - iminy, brushSize, brushSize);
					graphics.SetCompositingMode(LDraw::CompositingModeSourceCopy);
					graphics.DrawImage(m_pStroke->m_pBrushBitmap, destRect, 0, 0, m_pStroke->m_pBrushBitmap->GetWidth(), m_pStroke->m_pBrushBitmap->GetHeight());
				}

				LDraw::Bitmap* tsel = new LDraw::Bitmap(iwidth, iheight, LDraw::PixelFormat_t::GRAY_8);
				if (pView->m_document->m_pBitmapSelection)
				{
					ASSERT(0);
#if 0
					UI::Graphics graphics(new LDraw::GraphicsO(tsel));
					LDraw::RectF destRect(0, 0, iwidth, iheight);
					graphics.SetCompositingMode(LDraw::CompositingModeSourceCopy);
					graphics.DrawImage(pView->m_document->m_pBitmapSelection, destRect, iminx, iminy, iwidth, iheight);
#endif
				}

				if (true)
				{
					LDraw::BitmapData tselData;
					tsel->LockBits(NULL, LDraw::ImageLockModeRead, &tselData);

					LDraw::BitmapData tbitmapData;
					tbitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &tbitmapData);

					for (int y = 0; y < iheight; y++)
					{
						LDraw::PixelRGBAP_32* pbrush = (LDraw::PixelRGBAP_32*)(tbitmapData.Scan0 + tbitmapData.Stride*(y));
						uint8* psel = (tselData.Scan0 + tselData.Stride*(y));

						for (int x = 0; x < iwidth; x++)
						{
							uint8 a = *psel++;

							pbrush->r = LDraw::multab[a][pbrush->r];
							pbrush->g = LDraw::multab[a][pbrush->g];
							pbrush->b = LDraw::multab[a][pbrush->b];
							pbrush->a = LDraw::multab[a][pbrush->a];

							pbrush++;
						}
					}

					tbitmap->UnlockBits(&tbitmapData);
					tsel->UnlockBits(&tselData);
				}

				if (false)
				{
					LDraw::BitmapData tbitmapData;
					tbitmap->LockBits(NULL, LDraw::ImageLockModeRead, &tbitmapData);

					int mindepth0 = 65535;
					int maxdepth0 = 0;

					for (int y = iminy; y < imaxy; y++)
					{
						uint16* d = (uint16*)((uint8*)inDepthData.Scan0 + inDepthData.Stride*y + iminx*2);
						LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)(tbitmapData.Scan0 + tbitmapData.Stride*(y-iminy));
						for (int x = iminx; x < imaxx; x++)
						{
							//LPWORD t = (LPWORD)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);

							long adepth0 = (*d);
							long adepth1 = (*d);

							if (adepth0 < mindepth0) mindepth0 = adepth0;
							if (adepth1 > maxdepth0) maxdepth0 = adepth1;

							/* *t++ = */ *d++;
							p++;
						}
					}

#if 0
					int mindepth = 65535;
					int maxdepth = 0;

					int range = maxdepth - mindepth;

					{
						for (int y = miny; y < maxy; y++)
						{
							LPWORD d = (LPWORD)((BYTE*)inDepthData.Scan0 + inDepthData.Stride*y + minx*2);
							LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)(tbitmap.GetBitmapData() + tbitmap.GetRowBytes()*(y-miny));
							for (int x = minx; x < maxx; x++)
							{
								//LPWORD t = (LPWORD)((BYTE*)m_tDepth->Scan0 + m_tDepth->Stride*y0 + x0*2);

								long adepth0 = mindepth0 + (range - ((*d * range) >> 8));
								long adepth = mindepth0 + (*d * range) >> 8;

								if (adepth0 < mindepth) mindepth = adepth0;
								if (adepth > maxdepth) maxdepth = adepth;

								/* *t++ = */ *d++;
								p++;
							}
						}
					}
#endif

					{
						for (int y = iminy; y < imaxy; y++)
						{
							LDraw::PixelRGBAP_32* p = (LDraw::PixelRGBAP_32*)(tbitmapData.Scan0 + tbitmapData.Stride*(y-iminy));
							uint16* d = (uint16*)((uint8*)inDepthData.Scan0 + inDepthData.Stride*y + iminx*2);

							uint16 *dd, *sd;
						//	if (bDrawDepth)
							{
								LDraw::BitmapData* m_tDepth = &inDepthData;
								dd = (uint16*)((uint8*)inDepthData.Scan0 + inDepthData.Stride*y + iminx*2);
								sd = (uint16*)((uint8*)m_tDepth->Scan0 + m_tDepth->Stride*y + iminx*2);
							}

							for (int x = iminx; x < imaxx; x++)
							{
								int alpha = p->a;
								double dalpha = alpha/255.0;

								long depth = (1-dalpha)*(*dd + alpha) + (mindepth0 + alpha + 64)*dalpha;//(*dd + (*dd + alpha*2))/2;//(maxdepth - mindepth)/2 + alpha;

								if (depth > 65535) depth = 65535;
								else if (depth < 0) depth = 0;

								*dd = depth;

								/*
								double dalpha = (alpha/255.0);

								int depth1 = *dd + alpha;
								int depth2 = mindepth + alpha;

								long ndepth;

								ndepth = (1-dalpha)*(depth1) + (dalpha)*(depth2);
								ndepth = (1-dalpha)*(ndepth) + (dalpha)*(*sd);

								if (ndepth > 65535) ndepth = 65535;
								else if (ndepth < 0) ndepth = 0;
								*dd = ndepth;
								*/

								p++;
								d++;

								sd++;
								dd++;
							}
						}
					}

					tbitmap->UnlockBits(&tbitmapData);
				}

			//	int ix = floor(x);
			//	int iy = floor(y);
			//	LDraw::Matrix oldTransform = graphics.GetTransform();
			//	graphics.TranslateTransform(minx, miny);
			//	graphics.RotateTransform(45);
			//	graphics.ScaleTransform(1, 5);
			//	graphics.TranslateTransform(-brushSize/2, -brushSize/2);

				// opacity
				LDraw::ColorMatrixF colorMatrix(	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
																0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
																0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
																0.0f, 0.0f, 0.0f, opacity, 0.0f,
																0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

				LDraw::RectF destRect(iminx, iminy, tbitmap->GetWidth(), tbitmap->GetHeight());
				graphics.DrawImage(tbitmap/*m_pStroke->m_pBrushBitmap*/, destRect, 0, 0, tbitmap->GetWidth(), tbitmap->GetHeight(), LDraw::WrapModeClamp, &colorMatrix);

				if (area.IsEmptyArea())
					area = LDraw::RectD(destRect.X, destRect.Y, destRect.Width, destRect.Height);
				else
					LDraw::RectD::Union(area, area, LDraw::RectD(destRect.X, destRect.Y, destRect.Width, destRect.Height));

			//	graphics.SetTransform(oldTransform);
			}

			x += dx;
			y += dy;

			opacity += opacityDelta;
			brushSize += brushSizeDelta;
			dx += dxDelta;
			dy += dyDelta;
		}

		graphics.SetSmoothingMode(oldSmoothingMode);
		//	x += dx;
		//	y += dy;

		g_oldx = x;//wpt.X;
		g_oldy = y;//wpt.Y;
#endif
	}

	m_oldpressure = pressure;

#if 0
	pInBitmap->UnlockBits(&inData);
#endif
	if (pInDepthBitmap)
	{
		pInDepthBitmap->UnlockBits(&inDepthData);
	}

	LDraw::RectD urect = LDraw::RectD(m_pStroke->m_updateRect.X, m_pStroke->m_updateRect.Y, m_pStroke->m_updateRect.Width, m_pStroke->m_updateRect.Height);

	{
	// Account for layer effects
		urect.X -= 8;
		urect.Y -= 8;
		urect.Width += 16;
		urect.Height += 16;

#if 0
		LDraw::RectD xrect;
		GetTransformRectBoundingBox(pLayerBitmap->m_matrix, &urect, &xrect);

		CRect wrect(xrect.X, xrect.Y, xrect.X+xrect.Width, xrect.Y+xrect.Height);

		long scrollposX; pView->m_horz->get_pos(&scrollposX);
		long scrollposY; pView->m_vert->get_pos(&scrollposY);

		wrect.OffsetRect(-scrollposX, -scrollposY);

		pView->InvalidateRect(&wrect);
		pView->UpdateWindow();
#endif
		if (nsteps > 0)
		{
			pView->InvalidateRender(area);
		}
	}

	return Success;
}

void SelectTool::DrawMarquee(MSWindows::HDC hDC, LDraw::RectI& rect)
{
#if 0
	if (m_nTool == ID_IMAGETOOL_RECTANGULARMARQUEE)
		Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
	else
		Ellipse(hDC, rect.left, rect.top, rect.right, rect.bottom);
#endif
}

ErrorCode SelectTool::OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	if (!m_dragging)
	{
		m_dragging = 1;
		pView->CaptureMouse();

		m_rect.X = point.X;
		m_rect.Y = point.Y;
		m_rect.Width = 0;
		m_rect.Height = 0;
	}

	return Success;
}

ErrorCode SelectTool::OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags)
{
	if (m_dragging)
	{
		pView->ReleaseMouseCapture();
		m_dragging = 0;

		if (pView->m_document->m_pBitmapSelection == NULL)
		{
			pView->m_document->m_pBitmapSelection = new LDraw::Bitmap(pView->m_document->m_width, pView->m_document->m_height, LDraw::PixelFormat_t::GRAY_8);

			pView->m_document->m_groupSelection = new CGroupImageObject;
			//pView->m_document->m_groupSelection->AddRef();

			ASSERT(0);
#if 0
			UI::Graphics graphics(new LDraw::GraphicsO(pView->m_document->m_pBitmapSelection));

			graphics.Clear(LDraw::Color(0,0,0,0));
#endif
		}

		if (pView->m_document->m_pBitmapSelection)
		{
			ASSERT(0);
#if 0
			UI::Graphics graphics(new LDraw::GraphicsO(pView->m_document->m_pBitmapSelection));

			LDraw::SmoothingMode oldSmoothingMode = graphics.GetSmoothingMode();

			// Add to selection
			if (m_nTool == ID_IMAGETOOL_RECTANGULARMARQUEE)
			{
			//	graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

				graphics.FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255, 255)),
					LDraw::RectF(m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height));
			}
			else if (m_nTool == ID_IMAGETOOL_ELLIPTICALMARQUEE)
			{
			//	graphics.SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

				graphics.FillEllipse(new LDraw::SolidBrush(LDraw::Color(255, 255, 255, 255)),
					LDraw::RectF(m_rect.X, m_rect.Y, m_rect.Width, m_rect.Height));
			}
			else if (m_nTool = ID_IMAGETOOL_MAGICWAND)
			{
				CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

				LDraw::BitmapData inData;
				pLayerBitmap->m_pBitmap->LockBits(
					&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
					LDraw::ImageLockModeRead,
					/*PixelFormat32bppARGB,*/ &inData);

				/*
				g_Red = GetRValue(color);
				g_Green = GetGValue(color);
				g_Blue = GetBValue(color);
				*/

				long tolerance = 20;

				LDraw::BitmapData outData;
				pView->m_document->m_pBitmapSelection->LockBits(
					&LDraw::RectI(0, 0, pView->m_document->m_pBitmapSelection->GetWidth(), pView->m_document->m_pBitmapSelection->GetHeight()),
					LDraw::ImageLockModeRead,
					/*PixelFormat32bppARGB,*/ &outData);

				CFlood flood(&inData);

				flood.m_alphabits2 = (uint8*)new uint8[flood.m_width*flood.m_height];
				std::memset(flood.m_alphabits2, 0, flood.m_width*flood.m_height);
			//	MyEmptyRect(&flood.m_rect);

				flood.m_ArrayPoints = (FloodNode*)new uint8[(flood.m_width*flood.m_height)*sizeof(FloodNode)];
				if (flood.m_ArrayPoints)
				{
					// last point
					flood.FloodFill(m_rect.GetRight(), m_rect.GetBottom(), tolerance);

					{
						for (int y = 0; y < outData.Height; y++)
						{
						//	LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)(g->inImage->data + g->inImage->rowbytes*y);
							uint8* /*LDraw::PixelRGBAP_32* */ out = ((uint8*)outData.Scan0 + outData.Stride*y);
							uint8* src = flood.m_alphabits2 + flood.m_width*y;

							for (int x = 0; x < outData.Width; x++)
							{
								if (*src)
								{
									*out = 255;
								//	out->r = 255;//g_Red;
								//	out->g = 255;//g_Green;
								//	out->b = 255;//g_Blue;
								}

							//	in++;
								out++;
								src++;
							}
						}
					}
				}

				if (flood.m_ArrayPoints)
				{
					delete flood.m_ArrayPoints;
				}

				if (flood.m_alphabits2)
				{
					delete flood.m_alphabits2;
				}

				pView->m_document->m_pBitmapSelection->UnlockBits(&outData);
				pLayerBitmap->m_pBitmap->UnlockBits(&inData);
			}

			graphics.SetSmoothingMode(oldSmoothingMode);
#endif
		}

		pView->Invalidate();
	}

	return Success;
}

ErrorCode SelectTool::OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	if (m_dragging)
	{
		if (m_nTool != ID_IMAGETOOL_MAGICWAND)
		{
#if 0
			HDC hDC = pView->GetDC();

			DrawMarquee(hDC, m_rect);
#endif

			m_rect.Width = point.X - m_rect.X;
			m_rect.Height = point.Y - m_rect.Y;

#if 0
			DrawMarquee(hDC, m_rect);

			pView->ReleaseDC(hDC);
#endif
		}
	}

	return Success;
}

MagicWandTool::MagicWandTool()
{
	m_nTool = ID_IMAGETOOL_MAGICWAND;
}

SelectEllipseTool::SelectEllipseTool()
{
	m_nTool = ID_IMAGETOOL_ELLIPTICALMARQUEE;
}

SelectRectangleTool::SelectRectangleTool()
{
	m_nTool = ID_IMAGETOOL_RECTANGULARMARQUEE;
}

MoveTool::MoveTool()
{
	m_dragging = 0;
	m_hit = 0;
}

ErrorCode MoveTool::OnLButtonDown(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

	LDraw::BitmapData seldata;
	pView->m_document->m_pBitmapSelection->LockBits(NULL, LDraw::ImageLockModeRead, &seldata);

	uint8* p = seldata.Scan0 + seldata.Stride*(int)point.Y + (int)point.X;
	if (*p >= 128)
	{
		LDraw::BitmapData imagedata;

		pLayerBitmap->m_pBitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &imagedata);

		int width = seldata.Width;
		int height = seldata.Height;

		for (int y = 0; y < height; y++)
		{
			LDraw::PixelRGBAP_32* pbrush = (LDraw::PixelRGBAP_32*)(imagedata.Scan0 + imagedata.Stride*(y));
			uint8* psel = (seldata.Scan0 + seldata.Stride*(y));

			for (int x = 0; x < width; x++)
			{
				uint8 a = 255 - *psel;

				pbrush->r = LDraw::multab[a][pbrush->r];
				pbrush->g = LDraw::multab[a][pbrush->g];
				pbrush->b = LDraw::multab[a][pbrush->b];
				pbrush->a = LDraw::multab[a][pbrush->a];

				pbrush++;
				psel++;
			}
		}

		pLayerBitmap->m_pBitmap->UnlockBits(&imagedata);

	}
	else
	{
	}

	pView->m_document->m_pBitmapSelection->UnlockBits(&seldata);
#if 0
	LDraw::PointD dpt;
	dpt.X = point.x;
	dpt.Y = point.y;

	if (!m_dragging)
	{
		wstartpt = dpt;

		CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

		LDraw::RectI rc(pLayerBitmap->m_alphaBounds.left, pLayerBitmap->m_alphaBounds.top, pLayerBitmap->m_alphaBounds.Width(), pLayerBitmap->m_alphaBounds.Height());

		LDraw::PointD pts[8] =
		{
			LDraw::PointD(rc.X, rc.Y),
			LDraw::PointD(rc.X+rc.Width/2, rc.Y),
			LDraw::PointD(rc.X+rc.Width, rc.Y),
			LDraw::PointD(rc.X+rc.Width, rc.Y+rc.Height/2),
			LDraw::PointD(rc.X+rc.Width, rc.Y+rc.Height),
			LDraw::PointD(rc.X+rc.Width/2, rc.Y+rc.Height),
			LDraw::PointD(rc.X, rc.Y+rc.Height),
			LDraw::PointD(rc.X, rc.Y+rc.Height/2)
		};

		LDraw::PointF xpts[8];

		for (int i = 0; i < 8; i++)
		{
			gmVector2 xpt = pLayerBitmap->m_matrix.transform(gmVector2(pts[i].X, pts[i].Y));
			xpts[i].X = xpt[0];
			xpts[i].Y = xpt[1];
		}

		LDraw::PointD pt = dpt;

		for (i = 0; i < 8; i++)
		{
			if ((fabs(dpt.X-xpts[i].X) <= 6) && (fabs(dpt.Y-xpts[i].Y) <= 6))
			{
				m_offsetPt.X = (pt.X-xpts[i].X);//*magnify;
				m_offsetPt.Y = (pt.Y-xpts[i].Y);////*magnify;

				m_hit = i+2;
				break;
			}
		}

		if (m_hit)
		{
			m_matrix = pLayerBitmap->m_matrix;

			m_dragging = 1;
#if 0
			pView->SetCapture();
#endif
		}
	}
#endif
	return Success;
}

ErrorCode MoveTool::OnLButtonUp(CImageView* pView, LDraw::PointD point, UINT nFlags)
{
	if (m_dragging)
	{
		pView->ReleaseMouseCapture();

		m_dragging = 0;

		CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

		pLayerBitmap->CalculateScale(LDraw::RectD(0, 0, 1, 1), pLayerBitmap->m_matrix);

	// Rerender objects on this layer ?
		pLayerBitmap->Render();

#if 0	// Had this
		pView->Invalidate();
#endif
	}

	return Success;
}

ErrorCode MoveTool::OnMouseMove(CImageView* pView, LDraw::PointD point, double pressure, UINT nFlags)
{
	LDraw::PointD dpt;
	dpt.X = point.X;
	dpt.Y = point.Y;

	LDraw::PointD wpt = dpt;

	if (m_dragging)
	{
		CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)pView->m_pActiveLayer)->m_layerUnknown);

		LDraw::matrix3f xMat;

#if 0
		if (m_hit == 0)	// Rotate
		{
			xMat = GetRotateObjectMatrix(svgsvgElement, wstartpt, wpt, m_pivotPt.X, m_pivotPt.Y);
		}
		else
#endif
			if (m_hit == 1)	// Move
		{
				xMat = LDraw::matrix3f::getTranslate(wpt.X-wstartpt.X, wpt.Y-wstartpt.Y);
				/*
			CComPtr<ILSVGMatrix> mat;
			svgsvgElement->createSVGMatrix(&mat);
			mat->translate(wpt.X-wstartpt.X, wpt.Y-wstartpt.Y, &xMat);
			*/
		}
		else if (m_hit >= 2)	// Scale
		{
			double cx = 0;
			double cy = 0;
			double sx;
			double sy;

			LDraw::RectD m_objectsBoundingBox(pLayerBitmap->m_alphaBounds.X, pLayerBitmap->m_alphaBounds.Y, pLayerBitmap->m_alphaBounds.Width, pLayerBitmap->m_alphaBounds.Height);

			LDraw::RectD bounds = m_objectsBoundingBox;

#if 0
			if (mouse->nFlags & MK_ALT)
			{
				cy = bounds.Y + bounds.Height/2;
				cx = bounds.X + bounds.Width/2;
			}
			else
#endif
			{
				if (m_hit == 2)	// top-left
				{
					cx = bounds.X + bounds.Width;
					cy = bounds.Y + bounds.Height;
				}
				else if (m_hit == 3)
				{
					cx = bounds.X + bounds.Width/2;
					cy = bounds.Y + bounds.Height;
				}
				else if (m_hit == 4)
				{
					cx = bounds.X;
					cy = bounds.Y + bounds.Height;
				}
				else if (m_hit == 5)
				{
					cx = bounds.X;
					cy = bounds.Y + bounds.Height/2;
				}
				else if (m_hit == 6)
				{
					cx = bounds.X;
					cy = bounds.Y;
				}
				else if (m_hit == 7)
				{
					cx = bounds.X + bounds.Width/2;
					cy = bounds.Y;
				}
				else if (m_hit == 8)
				{
					cx = bounds.X+bounds.Width;
					cy = bounds.Y;
				}
				else if (m_hit == 9)
				{
					cx = bounds.X+bounds.Width;
					cy = bounds.Y + bounds.Height/2;
				}
			}

#if 0
			CComPtr<ILSVGMatrix> mat0;

			if (mouse->nFlags & MK_CONTROL &&
				(m_hit == 3 || m_hit == 7 || m_hit == 5 || m_hit == 9))
			{
				if (m_hit == 3 || m_hit == 7)	// Skew Y
				{
					double angle = 90 - GetLineAngle(wpt.X, wstartpt.Y, cx, cy) * (180/M_PI);

					CComPtr<ILSVGMatrix> mat3;
					svgsvgElement->createSVGMatrix(&mat3);

					CComPtr<ILSVGMatrix> mat2;
					mat3->translate(0, -cy, &mat2);

					CComQIPtr<ILSVGMatrix> mat1;
					mat2->skewY(angle, &mat1);

					mat1->translate(0, cy, &mat0);
				}
				else	// SkewX
				{
					double angle = GetLineAngle(wstartpt.X, wpt.Y, cx, cy) * (180/M_PI);

					CComPtr<ILSVGMatrix> mat3;
					svgsvgElement->createSVGMatrix(&mat3);

					CComPtr<ILSVGMatrix> mat2;
					mat3->translate(-cx, 0, &mat2);

					CComQIPtr<ILSVGMatrix> mat1;
					mat2->skewX(angle, &mat1);

					mat1->translate(cx, 0, &mat0);
				}
			}
			else
			{
				svgsvgElement->createSVGMatrix(&mat0);
			}
#endif

			if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
			{
				sx = (wpt.X - cx)/(wstartpt.X-m_offsetPt.X - cx);
				sy = (wpt.Y - cy)/(wstartpt.Y-m_offsetPt.Y - cy);
			}
			else if (m_hit == 3 || m_hit == 7)
			{
				sx = 1;
				sy = (wpt.Y - cy)/(wstartpt.Y-m_offsetPt.Y - cy);
			}
			else if (m_hit == 5 || m_hit == 9)
			{
				sx = (wpt.X - cx)/(wstartpt.X-m_offsetPt.X - cx);
				sy = 1;
			}

#if 0
			CComPtr<ILSVGMatrix> mat1;
			mat0->translate(-cx, -cy, &mat1);

			CComQIPtr<ILSVGMatrix> mat2;
			mat1->scaleNonUniform(sx, sy, &mat2);

			mat2->translate(cx, cy, &xMat);
#endif

			xMat = LDraw::matrix3f::getTranslate(-cx,-cy) * 
				LDraw::matrix3f::getScale(sx,sy) *
				LDraw::matrix3f::getTranslate(cx,cy);
		}

#if 0
		ATLASSERT(xMat != NULL);
		ATLASSERT(m_freeTransformMatrix != NULL);
#endif

		LDraw::matrix3f imatrix = m_matrix.getInverse();

		pLayerBitmap->m_matrix = m_matrix * /*imatrix **/ xMat;

#if 0	// Had this
		pView->Invalidate();
#endif

#if 0
		m_freeTransformMatrix = xMat;
		for (int i = 0; i < m_currentTransform.GetSize(); i++)
		{
			CComPtr<IEElement> eElement;
			m_element[i]->get_eElement(&eElement);

			CComPtr<ILDOMElement> domElement;
			eElement->get_domElement(&domElement);

			CComQIPtr<ILSVGTransformable> objectTransformable = domElement;
			if (objectTransformable)
			{
				CComPtr<ILDOMNode> parentNode;
				domElement->get_parentNode(&parentNode);

				CComPtr<ILSVGMatrix> parentCTM;
				window->svgGetScreenCTM((ILSVGElement*)parentNode.p, &parentCTM);

				CComPtr<ILSVGMatrix> iparentCTM;
				parentCTM->inverse(&iparentCTM);

				CComPtr<ILSVGMatrix> mat;
				xMat->multiply(iparentCTM, &mat);

				CComPtr<ILSVGMatrix> mat2;
				parentCTM->multiply(mat, &mat2);

				m_currentTransform[i]->setMatrix(mat2);
			}
			else
			{
				m_currentTransform[i]->setMatrix(xMat);
			}
		}
#endif
	}

	return Success;
}

/////////////////////////////////////////////////////////////////////////////
// CImageView

CImageView::CImageView()
{
//		m_viewGroup = NULL;

	m_document = NULL;

	m_dragging = 0;

	m_pImageLayerGroup = NULL;

	m_activeLayer = NULL;
	m_pActiveGroup = NULL;
	m_pActiveBitmap = NULL;

	m_pActiveLayer = NULL;	// Remove ??

	m_bRulers = false;
	m_magnify = 1.0;

//		m_pActiveTool = NULL;

	m_pressure = 0;
}

CImageDocument* CImageView::GetDocument()
{
	return m_document;
}

#if 0
LRESULT CImageView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;
	
	m_axhorz.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);
	
	m_axvert.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	m_sizeGrip.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);

	IDispEventImpl<1, CImageView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);
	IDispEventImpl<2, CImageView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_pImageLayerGroup = new CPImageLayerGroup;
	m_pImageLayerGroup->m_layerUnknown = m_document->m_imageLayerGroup;

	for (int i = 0; i < m_document->m_imageLayerGroup->m_subLayers.GetSize(); i++)
	{
		CImageLayerBitmap* layerBitmap = (CImageLayerBitmap*)m_document->m_imageLayerGroup->m_subLayers[i];

		CPImageLayerBitmap* pPLayerBitmap = new CPImageLayerBitmap;
		pPLayerBitmap->m_layerUnknown = layerBitmap;

		m_pActiveLayer = pPLayerBitmap;

		m_pImageLayerGroup->m_subLayers.Add(pPLayerBitmap);
	}
	
	SetTimer(1, 100);

	return 0;
}

LRESULT CImageView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(1);

	IDispEventImpl<1, CImageView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, CImageView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);

	return 0;
}

LRESULT CImageView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	int sbHeight = GetSystemMetrics(SM_CYHSCROLL);
	int sbWidth = GetSystemMetrics(SM_CXVSCROLL);

	BOOL bVertSB = TRUE;
	BOOL bHorzSB = TRUE;

	m_imageRect.left = 0;
	m_imageRect.top = 0;
	m_imageRect.right = client.right;
	m_imageRect.bottom = client.bottom;

	m_imageRect.right -= sbWidth;
	m_imageRect.bottom -= sbHeight;

	if (m_bRulers)
	{
		m_imageRect.left += 16;
		m_imageRect.top += 16;
	}
/*
	double pageWidth;
	double pageHeight;
	m_document->get_pageWidth(&pageWidth);
	m_document->get_pageHeight(&pageHeight);
*/
	double minx;
	double miny;
	double maxx;
	double maxy;

	minx = (-0)*m_magnify;
	miny = (-0)*m_magnify;
	maxx = (m_document->m_width+0)*m_magnify;
	maxy = (m_document->m_height+0)*m_magnify;

	if (bHorzSB)
	{
		double width = maxx-minx;

		if (m_imageRect.Width() > width)
		{
			m_horz->SetInfo(
				(minx -(m_imageRect.Width()-width)/2),
				(minx -(m_imageRect.Width()-width)/2),
				m_imageRect.Width());
		}
		else
		{
			m_horz->SetInfo(minx, maxx, m_imageRect.Width());
		}

		m_axhorz.MoveWindow(0, m_imageRect.bottom, m_imageRect.right, sbHeight);
		m_axhorz.ShowWindow(SW_SHOW);
	}
	else
	{
		m_horz->SetInfo(0, 0, 0);
		m_axhorz.ShowWindow(SW_HIDE);
	}

	if (bVertSB)
	{
		double height = maxy-miny;

		if (m_imageRect.Height() > height)
		{
			m_vert->SetInfo(
				(miny -(m_imageRect.Height()-height)/2),
				(miny -(m_imageRect.Height()-height)/2),
				m_imageRect.Height());
		}
		else
		{
			m_vert->SetInfo(miny, maxy, m_imageRect.Height());
		}

		m_axvert.MoveWindow(m_imageRect.right, 0, sbWidth, m_imageRect.bottom);
		m_axvert.ShowWindow(SW_SHOW);
	}
	else
	{
		m_vert->SetInfo(0, 0, 0);
		m_axvert.ShowWindow(SW_HIDE);
	}

	m_sizeGrip.MoveWindow(m_imageRect.right, m_imageRect.bottom, client.right-m_imageRect.right, client.bottom-m_imageRect.bottom, TRUE);

	return 0;
}
#endif

//LRESULT CImageView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
//{

void CImageView::SetOwnerWindow(UI::VisualContentSource* pWindow)
{
	UIElement::SetOwnerWindow(pWindow);

	if (pWindow)
	{
		pWindow->AddStylusPlugin(this);
	}
}

LDraw::SizeD CImageView::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(m_document->m_width, m_document->m_height);
}

void CImageView::OnRender(UI::Graphics* pGraphics)
{
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_computedSize.Width, m_computedSize.Height);

		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	/*
	CRect clipBox;
	dc.GetClipBox(&clipBox);

	if (dc.IntersectClipRect(m_imageRect.left, m_imageRect.top, m_imageRect.right, m_imageRect.bottom) > NULLREGION)
	{
		HDC hDC = CreateCompatibleDC(dc);
		HBITMAP hBitmap = CreateCompatibleBitmap(dc, clipBox.Width(), clipBox.Height());
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
		*/

		{
		//	LDraw::Graphics& graphics = *pGraphics;//(hDC);


#if 0
			graphics.FillRectangle(&LDraw::SolidBrush(LDraw::Color(190, 190, 190)), 0, 0, clipBox.Width(), clipBox.Height());

			graphics.TranslateTransform(-clipBox.left, -clipBox.top);

			graphics.TranslateTransform(-scrollposX, -scrollposY);

			LDraw::RectD imageClipBox(clipBox.left, clipBox.top, clipBox.Width(), clipBox.Height());
			imageClipBox.Offset(scrollposX, scrollposY);
#endif

			if (false)
			{
				//CComQIPtr<IPDDocumentSettings> documentSettings = m_document;
				long gridSizeX = 16;
				long gridSizeY = 16;
				LDraw::Color gridColor0(255, 255, 255);
				LDraw::Color gridColor1(204, 204, 204);

				/*
				documentSettings->get_transpGridSizeX(&gridSizeX);
				documentSettings->get_transpGridSizeY(&gridSizeY);
				documentSettings->get_transpGridColor0(&gridColor0);
				documentSettings->get_transpGridColor1(&gridColor1);
				*/

				LDraw::SolidBrush* brush0 = new LDraw::SolidBrush(gridColor0);
				LDraw::SolidBrush* brush1 = new LDraw::SolidBrush(gridColor1);

				LDraw::Bitmap* gridbitmap = new LDraw::Bitmap(gridSizeX*2, gridSizeY*2, LDraw::PixelFormat_t::RGB_32);
				{
					ASSERT(0);
#if 0
					UI::Graphics graphics(new LDraw::GraphicsO(gridbitmap));

					graphics.FillRectangle(brush0, 0, 0, gridSizeX, gridSizeY);
					graphics.FillRectangle(brush1, gridSizeX, 0, gridSizeX, gridSizeY);
					graphics.FillRectangle(brush1, 0, gridSizeY, gridSizeX, gridSizeY);
					graphics.FillRectangle(brush0, gridSizeX, gridSizeY, gridSizeX, gridSizeY);
#endif
				}

			//	pGraphics->DrawImage(&gridbitmap, 0, 0);
				LDraw::TextureBrush* tbrush = new LDraw::TextureBrush(gridbitmap, LDraw::WrapModeTile/*, LDraw::RectI(0, 0, gridSizeX*2, gridSizeY*2)*/);

				LDraw::RectI pasteBoardRect(0, 0, m_document->m_width, m_document->m_height);

				pGraphics->FillRectangle(tbrush, pasteBoardRect);
			}

			for (int i = 0; i < m_document->m_imageLayerGroup->m_subLayers.GetSize(); i++)
			{
				CImageLayerBitmap* pLayerBitmap = (CImageLayerBitmap*)m_document->m_imageLayerGroup->m_subLayers[i];

#if 0
				if (pLayerBitmap->m_pBitmapDepth || pLayerBitmap->m_pBitmapMask)
				{
					if (pLayerBitmap->m_pBitmapFinal == NULL)
					{
						pLayerBitmap->m_pBitmapFinal = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), RGBA_32/*PixelFormat32bppARGB*/);
					}

					LDraw::BitmapData inData;
					pLayerBitmap->m_pBitmap->LockBits(
						&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
						LDraw::ImageLockModeRead,
						/*PixelFormat32bppARGB,*/ &inData);

					LDraw::BitmapData outData;
					pLayerBitmap->m_pBitmapFinal->LockBits(
						&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapFinal->GetWidth(), pLayerBitmap->m_pBitmapFinal->GetHeight()),
						LDraw::ImageLockModeWrite,
						/*PixelFormat32bppARGB,*/ &outData);
					
					if (pLayerBitmap->m_pBitmapDepth)
					{
						LDraw::BitmapData depthData;
						pLayerBitmap->m_pBitmapDepth->LockBits(
							&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapDepth->GetWidth(), pLayerBitmap->m_pBitmapDepth->GetHeight()),
							LDraw::ImageLockModeRead,
							/*PixelFormat16bppGrayScale,*/ &depthData);

						double azimuth = 45*(M_PI/180);
						double elevation = 60*(M_PI/180);

						CRect rect(
							1,
							1,
							pLayerBitmap->m_pBitmapDepth->GetWidth()-1,
							pLayerBitmap->m_pBitmapDepth->GetHeight()-1);

						Emboss(
							azimuth, elevation, 2,//width45,
							
							&depthData,
							&inData,			// source (texture)
							&outData,		// dest
							
							inData.Width, inData.Height,
							&rect);

						pLayerBitmap->m_pBitmapDepth->UnlockBits(&depthData);
					}

					if (pLayerBitmap->m_pBitmapMask)
					{
						LDraw::BitmapData maskData;
						pLayerBitmap->m_pBitmapMask->LockBits(
							&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapMask->GetWidth(), pLayerBitmap->m_pBitmapMask->GetHeight()),
							LDraw::ImageLockModeRead,
							PixelFormat32bppARGB, &maskData);

						for (int y = 0; y < maskData.Height; y++)
						{
							LDraw::PixelRGBAP_32* in = (LDraw::PixelRGBAP_32*)((BYTE*)inData.Scan0 + inData.Stride*y);
							LDraw::PixelRGBAP_32* out = (LDraw::PixelRGBAP_32*)((BYTE*)outData.Scan0 + outData.Stride*y);
							LDraw::PixelRGBAP_32* mask = (LDraw::PixelRGBAP_32*)((BYTE*)maskData.Scan0 + maskData.Stride*y);

							for (int x = 0; x < maskData.Width; x++)
							{
								out->alpha = in->alpha * (mask->red + mask->green + mask->blue)/3 * mask->alpha / (255*255);
								out->red = in->red;
								out->green = in->green;
								out->blue = in->blue;

								in++;
								out++;
								mask++;
							}
						}

						pLayerBitmap->m_pBitmapMask->UnlockBits(&maskData);
					}

					pLayerBitmap->m_pBitmap->UnlockBits(&inData);
					pLayerBitmap->m_pBitmapFinal->UnlockBits(&outData);

					graphics.DrawImage(pLayerBitmap->m_pBitmapFinal, LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
						0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(),
						LDraw::UnitPixel);
				}
				else
#endif
#if 0
				{
					if (pLayerBitmap->m_effects[0])
					{
						LDraw::RectD rect = imageClipBox;
						/*
						rect.X -= 8;
						rect.Y -= 8;
						rect.Width += 16;
						rect.Height += 16;
						*/

						gmMatrix3 imatrix = pLayerBitmap->m_matrix.inverse();

						RectD xrect;

						GetTransformRectBoundingBox(imatrix, &rect, &xrect);

						LDraw::Bitmap* pOutBitmap = new LDraw::Bitmap(ceil(xrect.Width), ceil(xrect.Height), PixelFormat32bppARGB);
						if (pOutBitmap)
						{
							LDraw::Bitmap* pInBitmap = new LDraw::Bitmap(ceil(rect.Width), ceil(rect.Height), PixelFormat32bppARGB);

							{
								LDraw::Graphics graphics(pInBitmap);

								LDraw::Matrix oldmat;
								graphics.GetTransform(&oldmat);

								LDraw::Matrix matrix(
									(float)imatrix[0][0], (float)imatrix[0][1],
									(float)imatrix[1][0], (float)imatrix[1][1],
									(float)imatrix[2][0], (float)imatrix[2][1]);
								graphics.MultiplyTransform(&matrix);

								graphics.DrawImage(pLayerBitmap->m_pBitmap,
									LDraw::RectI(0, 0, rect.Width, rect.Height),
									rect.X, rect.Y, (float)rect.Width, (float)rect.Height,
									LDraw::UnitPixel);

								graphics.SetTransform(&oldmat);
							}

							pLayerBitmap->m_effects[0]->m_pEffect->Filter(pInBitmap, pOutBitmap);

							LDraw::Matrix oldmat;
							graphics.GetTransform(&oldmat);

							LDraw::Matrix matrix(
								(float)pLayerBitmap->m_matrix[0][0], (float)pLayerBitmap->m_matrix[0][1],
								(float)pLayerBitmap->m_matrix[1][0], (float)pLayerBitmap->m_matrix[1][1],
								(float)pLayerBitmap->m_matrix[2][0], (float)pLayerBitmap->m_matrix[2][1]);
							graphics.MultiplyTransform(&matrix);

							graphics.DrawImage(pOutBitmap,
								LDraw::RectF(xrect.X, xrect.Y, (float)xrect.Width, (float)xrect.Height),
								0, 0, (float)xrect.Width, (float)xrect.Height,
								LDraw::UnitPixel);

							graphics.SetTransform(&oldmat);

							delete pInBitmap;
							delete pOutBitmap;
						}
					}
				}
#endif

				if (pLayerBitmap->m_pBitmapFinal == NULL)
				{
					pLayerBitmap->m_pBitmapFinal = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), LDraw::PixelFormat_t::RGBAP_32/*PixelFormat32bppARGB*/);
				}

				LDraw::BitmapData inData;
				pLayerBitmap->m_pBitmap->LockBits(
					&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
					LDraw::ImageLockModeRead,
					/*PixelFormat32bppARGB,*/ &inData);

				LDraw::BitmapData outData;
				pLayerBitmap->m_pBitmapFinal->LockBits(
					&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapFinal->GetWidth(), pLayerBitmap->m_pBitmapFinal->GetHeight()),
					LDraw::ImageLockModeWrite,
					/*PixelFormat32bppARGB,*/ &outData);

					/*
				if (pLayerBitmap->m_pBitmapDepth == NULL)
				{
					pLayerBitmap->m_pBitmapDepth = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), GRAY_16);
				}
				*/

				if (pLayerBitmap->m_pBitmapDepth)
				{
					LDraw::BitmapData depthData;
					pLayerBitmap->m_pBitmapDepth->LockBits(
						&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapDepth->GetWidth(), pLayerBitmap->m_pBitmapDepth->GetHeight()),
						LDraw::ImageLockModeRead,
						/*PixelFormat16bppGrayScale,*/ &depthData);

					double azimuth = 45*(M_PI/180);
					double elevation = 60*(M_PI/180);

					LDraw::BBoxi rect(
						1,
						1,
						pLayerBitmap->m_pBitmapDepth->GetWidth()-1,
						pLayerBitmap->m_pBitmapDepth->GetHeight()-1);

					Emboss(
						azimuth, elevation, 2,//width45,
						
						&depthData,
						&inData,			// source (texture)
						&outData,		// dest
						
						inData.Width, inData.Height,
						&rect);

		//			pLayerBitmap->m_pBitmapDepth->UnlockBits(&depthData);


				}
					pLayerBitmap->m_pBitmap->UnlockBits(&inData);
					pLayerBitmap->m_pBitmapFinal->UnlockBits(&outData);

#if 0
				pGraphics->DrawImage(pLayerBitmap->m_pBitmapFinal, LDraw::RectI(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()),
					0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()/*,
					LDraw::UnitPixel*/);
#endif

				pGraphics->DrawImage(pLayerBitmap->m_pBitmap, LDraw::RectI(0, 0, pLayerBitmap->m_width/*m_pBitmap->GetWidth()*/, pLayerBitmap->m_height/*m_pBitmap->GetHeight()*/),
					0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight()/*,
					LDraw::UnitPixel*/);

#if 0
			if (m_pActiveLayer)
			{
				CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

				LDraw::RectI rc(pLayerBitmap->m_alphaBounds.X, pLayerBitmap->m_alphaBounds.Y, pLayerBitmap->m_alphaBounds.Width, pLayerBitmap->m_alphaBounds.Height);

				PointD pts[8] =
				{
					PointD(rc.X, rc.Y),
					PointD(rc.X+rc.Width/2, rc.Y),
					PointD(rc.X+rc.Width, rc.Y),
					PointD(rc.X+rc.Width, rc.Y+rc.Height/2),
					PointD(rc.X+rc.Width, rc.Y+rc.Height),
					PointD(rc.X+rc.Width/2, rc.Y+rc.Height),
					PointD(rc.X, rc.Y+rc.Height),
					PointD(rc.X, rc.Y+rc.Height/2)
				};

				LDraw::PointF xpts[8];

				for (int i = 0; i < 8; i++)
				{
					gmVector2 xpt = pLayerBitmap->m_matrix.transform(gmVector2(pts[i].X, pts[i].Y));
					xpts[i].X = xpt[0];
					xpts[i].Y = xpt[1];
				}

				LDraw::Pen pen(LDraw::Color(0, 0, 200));

				graphics.DrawLine(&pen, xpts[0], xpts[2]);
				graphics.DrawLine(&pen, xpts[2], xpts[4]);
				graphics.DrawLine(&pen, xpts[4], xpts[6]);
				graphics.DrawLine(&pen, xpts[6], xpts[0]);
			}
#endif
			}

		/*
		dc.BitBlt(clipBox.left, clipBox.top, clipBox.Width(), clipBox.Height(), hDC, 0, 0, SRCCOPY);

		SelectObject(hDC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(hDC);
	}
	*/
	}

		pGraphics->SetSmoothingMode(oldSmoothingMode);
	OnTimer(pGraphics);
}

#if 0
void PrepareImageAsCircularBrush(LDraw::BitmapData* pImage/*, CCurve* pCurve*/)
{
	ASSERT(pImage && pImage->data);
	ASSERT(pImage->width == 255 && pImage->height == 255);

	int radius = (pImage->width-1)/2;

	for (int y2 = -radius; y2 <= radius; y2++)
	{
		int	x2 = -radius;

		LDraw::PixelRGBAP_32* dest = (LDraw::PixelRGBAP_32*)((LPBYTE)pImage->data + pImage->rowbytes*(y2+radius)+(x2+radius)*4);

		for (; x2 <= radius; x2++)
		{
			int	len = (int)(sqrt(y2*y2+x2*x2)+0.5);

			BYTE	alpha = 0;

			if (len <= radius)
			{
				alpha = 255-pCurve->m_data.values[len*2];
			}

			dest->alpha = alpha;
			dest->red = 0;
			dest->green = 0;
			dest->blue = 0;

			dest++;
		}
	}
}
#endif

void CImageView::OnLButtonDown(LDraw::PointD point)
{
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

	//if (!m_dragging)
	//	point.x += scrollposX;
	//	point.y += scrollposY;

	if (m_document->m_pActiveTool == NULL)
	{
		/*
		m_document->m_pActiveTool = NULL;

		if (m_document->m_activeTool == ID_IMAGETOOL_SELECT)
		{
			m_pActiveTool = new CMoveTool;
		}
		else if (m_document->m_activeTool == ID_IMAGETOOL_PAINTBRUSH)
		{
			m_pActiveTool = new CPaintbrushTool;
		}
		else if (m_document->m_activeTool == ID_IMAGETOOL_RECTANGULARMARQUEE ||
					m_document->m_activeTool == ID_IMAGETOOL_ELLIPTICALMARQUEE ||
					m_document->m_activeTool == ID_IMAGETOOL_MAGICWAND)
		{
			CMarqueeTool* pTool = new CMarqueeTool;
			pTool->m_nTool = m_document->m_activeTool;

			m_pActiveTool = pTool;
		}
		*/

	}

	if (m_document->m_pActiveTool)
	{
		m_document->m_pActiveTool->OnLButtonDown(this, point, m_pressure, 0/*nFlags*/);
	}
}

void CImageView::OnLButtonUp(LDraw::PointD point)
{
	if (m_document->m_pActiveTool)
	{
	//	point.x += scrollposX;
	//	point.y += scrollposY;

		//ReleaseCapture();

		m_document->m_pActiveTool->OnLButtonUp(this, point, 0/*nFlags*/);

	//	delete m_pActiveTool;	// TODO remove
	//	m_pActiveTool = NULL;
	}
}

void CImageView::OnPacket(UI::StylusPacket* packet)
{
	m_pressure = packet->m_pressure;

	if (m_document->m_pActiveTool)
	{
		LDraw::PointD clientpt = ScreenToElement(packet->m_screenX, packet->m_screenY);

		m_document->m_pActiveTool->OnMouseMove(this, clientpt, m_pressure, 0/*nFlags*/);
	}
}

void CImageView::OnMouseMove(LDraw::PointD point)
{
	long scrollposX = 0;// m_horz->get_pos(&scrollposX);
	long scrollposY = 0;// m_vert->get_pos(&scrollposY);

//	if (m_dragging)
	{
	//	point.x += scrollposX;
	//	point.y += scrollposY;

#if 1
		if (m_document->m_pActiveTool)
		{
			m_document->m_pActiveTool->OnMouseMove(this, point, 1/*pressure*/, 0/*nFlags*/);
		}
#endif
	}
}

#if 0
void DrawSelectionOutline(
	HDC hDC, CI2DLayer* pLayer,
	CPoint offset, CPoint offset2, double magnify)
{

#endif

	void CImageView::OnTimer(UI::Graphics* pGraphics)
{
//	HDC hDC = NULL;//GetDC();

	if (m_document->m_pBitmapSelection)
	{
		static int	dir = 0;
		static int	ddi = 10;

		double magnify = m_magnify;

			//DrawSelectionOutline(hDC
	// TODO : Restrict display to the visible view.

		//ASSERT(pLayer);
	//	ASSERT(pLayer->GetComposition());

		long scrollposX = 0;// m_horz->get_pos(&scrollposX);
		long scrollposY = 0;// m_vert->get_pos(&scrollposY);

		LDraw::PointI offset(-scrollposX,-scrollposY);
		LDraw::PointI offset2(0,0);

		double xsampling = 1;//pLayer->GetComposition()->m_XSampling/65536.0;
		double ysampling = 1;//pLayer->GetComposition()->m_YSampling/65536.0;

		LDraw::RectI rect(0, 0, m_document->m_width-1, m_document->m_height-1);

		rect.X += offset2.X;
		//rect.right += offset2.x;
		rect.Y += offset2.Y;
		//rect.bottom += offset2.y;

		if (rect.X < 0)
		{
			rect.Width += rect.X;
			rect.X = 0;
		}

		if (rect.Y < 0)
		{
			rect.Height += rect.Y;
			rect.Y = 0;
		}

#if 0
		if (rect.right > pLayer->GetWidth()-1) rect.right = pLayer->GetWidth()-1;
		if (rect.bottom > pLayer->GetHeight()-1) rect.bottom = pLayer->GetHeight()-1;
#endif

		LDraw::SolidBrush* blackBrush = new LDraw::SolidBrush(LDraw::Color(0,0,0));
		LDraw::SolidBrush* whiteBrush = new LDraw::SolidBrush(LDraw::Color(255,255,255));

		//if (!((rect.left > rect.right) || (rect.top > rect.bottom)))
		if (rect.Width > 0 && rect.Height > 0)
		{

			int left = rect.X;
			int top = rect.Y;
			int width = rect.Width;//rect.right-rect.left+1;
			int height = rect.Height;//rect.bottom-rect.top+1;

			left = (int)(left/xsampling);
			top = (int)(top/ysampling);
			width = (int)(width/xsampling);
			height = (int)(height/ysampling);

			int x, y;

			bool b2;

			//ImageDef* image = pLayer->GetImageSel();
			LDraw::BitmapData image;
			m_document->m_pBitmapSelection->LockBits(
				&LDraw::RectI(0, 0, m_document->m_pBitmapSelection->GetWidth(), m_document->m_pBitmapSelection->GetHeight()),
				LDraw::ImageLockModeRead,
				/*PixelFormat32bppARGB,*/ &image);

		// Left right
			if (dir == 0)
			{
				for (y = top; y < top+height; y++)
				{
					if (--ddi < 0) ddi = 10;
					int dd = ddi;

					uint8* sel = ((uint8*)image.Scan0 + image.Stride*y + left);

					b2 = 0;

					for (x = left; x < left+width; x++)
					{
						uint8 value = *sel;

						bool	b = (value > 127) ? true: false;
						sel++;

						if (b2 != b)
						{
							int x2 = (int)(x*magnify*xsampling)+offset.X;
							int y2 = (int)(y*magnify*ysampling)+offset.Y;

							for (int i = 0; i < magnify*ysampling; i++)
							{
							//	SetPixelV(hDC, x2, y2++, (dd<5)? RGB(255,255,255): RGB(0,0,0));

								LDraw::SolidBrush* brush = (dd<5)? whiteBrush: blackBrush;
								pGraphics->FillRectangle(brush, x2, y2, 1, 1);
								y2++;

								if (--dd < 0) dd = 10;

								y2 += ysampling;
							}

							b2 = b;
						}
					}

				}

				dir = 1;
			}

			// Top bottom
			if (dir == 1)
			{
				for (x = left; x < left+width; x++)
				{
					if (--ddi < 0) ddi = 10;
					int dd = ddi;

					uint8* sel = ((uint8*)image.Scan0 + image.Stride*top + x);

					b2 = 0;

					for (y = top; y < top+height; y++)
					{
						uint8 value = *sel;

						bool	b = (value > 127)? true: false;

						if (b2 != b)
						{
							int x2 = (int)(x*magnify*xsampling)+offset.X;
							int y2 = (int)(y*magnify*ysampling)+offset.Y;

							for (int i = 0; i < magnify*xsampling; i++)
							{
//								SetPixelV(hDC, x2, y2, (dd<5)? RGB(255,255,255): RGB(0,0,0));
//								LDraw::SolidBrush brush((dd<5)? LDraw::Color(255,255,255): LDraw::Color(0,0,0));
								LDraw::SolidBrush* brush = (dd<5)? whiteBrush: blackBrush;
								pGraphics->FillRectangle(brush, x2, y2, 1, 1);
								if (--dd < 0) dd = 10;

								x2 += xsampling;
							}

							b2 = b;
						}

						sel += image.Stride;
					}
				}

				dir = 0;
			}

			if (--ddi < 0) ddi = 10;

			m_document->m_pBitmapSelection->UnlockBits(&image);
		}
	}

//	ReleaseDC(hDC);
}

#if 0
STDMETHODIMP CImageView::OnActivate(BOOL bActivate, IUIDlg* pActivateView, IUIDlg* pDeactivateView)
{
	CComQIPtr<IUIActiveManager> uiActiveManager = m_document->m_app;

	if (bActivate)
	{
		uiActiveManager->ActivateObject(NULL, m_document->GetUnknown());
		uiActiveManager->ActivateObject(m_document->GetUnknown(), GetUnknown());
	}
	else
	{
		uiActiveManager->DeactivateObject(GetUnknown());
		uiActiveManager->DeactivateObject(m_document->GetUnknown());
	}

	return S_OK;
}

void __stdcall CImageView::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);
	m_horz->put_pos(pos);

#if 0
	m_bInvalid = true;

	// Scroll bitmap
	{
		LDraw::Bitmap* newbm = new LDraw::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
		{
			LDraw::Graphics graphicsbm(newbm);
			graphicsbm.DrawImage(m_pBitmap, oldPos-pos, 0);
		}
		delete m_pBitmap;
		m_pBitmap = newbm;
	}

	EraseBrushOutline();
#endif

#if 0
	ScrollWindow(oldPos-pos, 0, &m_imageRect, &m_imageRect);
#endif
/*
	CRect rulerRect(16, 0, m_imageRect.right, 16);
	ScrollWindow(oldPos-pos, 0, &rulerRect, &rulerRect);
*/
//	Fire_ViewBoxChanged();
}

void __stdcall CImageView::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);
	m_vert->put_pos(pos);

#if 0
	m_bInvalid = true;

	// Scroll bitmap
	{
		LDraw::Bitmap* newbm = new LDraw::Bitmap(m_areaRect.Width(), m_areaRect.Height()/*, PixelFormat24bppRGB*/);
		{
			LDraw::Graphics graphicsbm(newbm);
			graphicsbm.DrawImage(m_pBitmap, 0, oldPos-pos);
		}
		delete m_pBitmap;
		m_pBitmap = newbm;
	}

	EraseBrushOutline();
#endif

#if 0
	ScrollWindow(0, oldPos-pos, &m_imageRect, &m_imageRect);
#endif

	/*
	CRect rulerRect(0, 16, 16, m_imageRect.bottom);
	ScrollWindow(0, oldPos-pos, &rulerRect, &rulerRect);
	*/

//	Fire_ViewBoxChanged();
}
#endif

#if 0
// ICommandTarget
STDMETHODIMP CImageView::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try document
	CComQIPtr<ICommandTarget> target = m_document->GetUnknown();
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

	return S_OK;
}
#endif

#if 0
void CImageView::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
			//LDraw::PointD pointd(point->get_X(), point->get_Y());
			OnLButtonDown(point);
		}
		else if (*type == L"mouseup")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
			OnLButtonUp(point);
		}
		else if (*type == L"mousemove")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);
			LDraw::PointD point = ScreenToClient(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY());
			OnMouseMove(point);
		}
		else
			;//return ProcessTargetCommands::handleEvent(evt);
	}
}
#endif

BEGIN_CMD_MAP(CImageView)
#if 0
	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomIn)
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomOut)

	CMD_HANDLER(ID_LAYER_NEW_LAYERVIACUT, OnNewLayerViaCut)
	CMD_HANDLER(ID_LAYER_NEW_LAYERVIACOPY, OnNewLayerViaCopy)
	CMD_HANDLER(ID_LAYER_NEWADJUSTMENTLAYER_POSTERIZE, OnNewAdjustmentLayerPosterize)

	CMD_HANDLER(ID_LAYER_LAYERMASK_REVEALALL, OnLayerMaskRevealAll)
	CMD_HANDLER(ID_LAYER_LAYERMASK_HIDEALL, OnLayerMaskHideAll)
	CMD_HANDLER(ID_LAYER_LAYERMASK_ENABLE, OnLayerMaskEnable)

	CMD_HANDLER(ID_LAYER_DEPTH_ADD, OnDepthAdd)
	CMD_HANDLER(ID_LAYER_DEPTH_CLEAR, OnDepthClear)

	CMD_HANDLER(ID_LAYER_LAYERSTYLE_DROPSHADOW, OnLayerStyleDropShadow)
/*
	CMD_HANDLER(ID_VIEW_ACTUALSIZE, OnViewActualSize)

	CMD_HANDLER(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecial)
	CMD_UPDATE(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecialUpdate)

	CMD_HANDLER(ID_INSERT_IMAGE, OnInsertImage)
	CMD_HANDLER(ID_TABLE_INSERT_TABLE, OnInsertTable)

	CMD_HANDLER(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPath)
	CMD_UPDATE(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPathUpdate)

	CMD_HANDLER(ID_OBJECT_EDITPAINT, OnEditPaint)
	CMD_HANDLER(ID_OBJECT_EDITMASK, OnObjectEditMask)
	CMD_HANDLER(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPath)
	CMD_HANDLER(ID_OBJECT_EDITFILTER, OnObjectEditFilter)
	CMD_UPDATE(ID_OBJECT_EDITPAINT, OnObjectEditPaintUpdate)
	CMD_UPDATE(ID_OBJECT_EDITMASK, OnObjectEditMaskUpdate)
	CMD_UPDATE(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPathUpdate)
	CMD_UPDATE(ID_OBJECT_EDITFILTER, OnObjectEditFilterUpdate)

	CMD_HANDLER(ID_VIEW_SHOWMARKUP, OnShowMarkup)
	CMD_UPDATE(ID_VIEW_SHOWMARKUP, OnShowMarkupUpdate)
	*/
#endif
END_CMD_MAP()

void CImageView::OnViewZoomIn(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_magnify *= 2;

}

void CImageView::OnViewZoomOut(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_magnify /= 2;

}

LDraw::PointD CImageView::OnSetPos(LDraw::PointD pos)
{
	pos.X = ((int)pos.X);
	pos.Y = ((int)pos.Y);
	return pos;
}

#if 0
#include "DropShadowDlg.h"

LRESULT CImageView::OnLayerStyleDropShadow(WORD wNotifyCode, WORD wID, HWND hWndCtl, bool& bHandled)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

	CDropShadowDlg dlg;
	dlg.m_angle = 45;
	dlg.m_distance = 5;
	dlg.m_size = 1;

	if (dlg.DoModal() == IDOK)
	{
		CDropShadow* pDropShadow = new CDropShadow;
		pDropShadow->m_angle = dlg.m_angle;
		pDropShadow->m_distance = dlg.m_distance;
		pDropShadow->m_size = dlg.m_size;

		CLayerEffect* pEffect = new CLayerEffect;
		pEffect->m_pEffect = pDropShadow;

		pLayerBitmap->m_effects[0] = pEffect;

		CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
		paintSite->InvalidateRect(NULL);
	}

	return 0;
}

#include "NewLayerDlg.h"

LRESULT CImageView::OnNewLayerViaCut(WORD wNotifyCode, WORD wID, HWND hWndCtl, bool& bHandled)
{
	if (m_document->m_pBitmapSelection)
	{
		CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

		CComObject<CImageLayerBitmap>* pLayer;
		CComObject<CImageLayerBitmap>::CreateInstance(&pLayer);
		if (pLayer)
		{
			pLayer->AddRef();

			pLayer->m_width = pLayerBitmap->m_width;
			pLayer->m_height = pLayerBitmap->m_height;

			pLayer->m_pInitialBitmap = pLayerBitmap->m_pInitialBitmap->Clone(0, 0, pLayerBitmap->m_pInitialBitmap->GetWidth(), pLayerBitmap->m_pInitialBitmap->GetHeight(), PixelFormat32bppARGB);
			pLayer->m_pBitmap = pLayerBitmap->m_pBitmap->Clone(0, 0, pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), PixelFormat32bppARGB);

			pLayer->m_name = L"Layer 1";
			((CImageLayerGroup*)pLayerBitmap->m_parentGroup)->m_subLayers.Add(pLayer);

			MaskBitmap(pLayer->m_pBitmap, m_document->m_pBitmapSelection, FALSE);
			{
				LDraw::BitmapData bitmapData;
				pLayer->m_pBitmap->LockBits(
					&LDraw::RectI(0, 0, pLayer->m_pBitmap->GetWidth(), pLayer->m_pBitmap->GetHeight()),
					LDraw::ImageLockModeRead,
					PixelFormat32bppARGB, &bitmapData);

				GetAlphaBounds(&bitmapData, &pLayer->m_alphaBounds);

				pLayer->m_pBitmap->UnlockBits(&bitmapData);
			}


			// Cut
			MaskBitmap(pLayerBitmap->m_pBitmap, m_document->m_pBitmapSelection, TRUE);

			//pLayerBitmap->m_parentGroup->InsertBefore(pLayer, 
		}
	}

	return 0;
}

LRESULT CImageView::OnNewLayerViaCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, bool& bHandled)
{
	return 0;
}

#include "AdjustmentPosterizeDlg.h"

LRESULT CImageView::OnNewAdjustmentLayerPosterize(WORD wNotifyCode, WORD wID, HWND hWndCtl, bool& bHandled)
{
	CNewLayerDlg layerdlg;

	if (layerdlg.DoModal() == IDOK)
	{
		CAdjustmentPosterizeDlg adjustdlg;

		//CComObject<CAdjustmentLayer

		if (adjustdlg.DoModal() == IDOK)
		{
		}
	}

	return 0;
}

LRESULT CImageView::OnLayerMaskRevealAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

	pLayerBitmap->m_pBitmapMask = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), PixelFormat32bppARGB);
	CComObject<CGroupImageObject>::CreateInstance(&pLayerBitmap->m_groupMask);
	pLayerBitmap->m_groupMask->AddRef();

// set all to 255
	LDraw::BitmapData maskData;
	pLayerBitmap->m_pBitmapMask->LockBits(
		&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapMask->GetWidth(), pLayerBitmap->m_pBitmapMask->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppARGB, &maskData);

	FillMemory(maskData.Scan0, maskData.Stride*maskData.Height, 255);

	pLayerBitmap->m_pBitmapMask->UnlockBits(&maskData);

	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
	paintSite->InvalidateRect(NULL);

	return 0;
}

LRESULT CImageView::OnLayerMaskHideAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

	pLayerBitmap->m_pBitmapMask = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), PixelFormat32bppARGB);
	pLayerBitmap->m_groupMask = new CGroupImageObject;
	pLayerBitmap->m_groupMask->AddRef();

// set all to 0
	LDraw::BitmapData maskData;
	pLayerBitmap->m_pBitmapMask->LockBits(
		&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapMask->GetWidth(), pLayerBitmap->m_pBitmapMask->GetHeight()),
		LDraw::ImageLockModeRead,
		PixelFormat32bppARGB, &maskData);

	ZeroMemory(maskData.Scan0, maskData.Stride*maskData.Height);

	pLayerBitmap->m_pBitmapMask->UnlockBits(&maskData);

	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
	paintSite->InvalidateRect(NULL);

	return 0;
}

LRESULT CImageView::OnLayerMaskEnable(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	return 0;
}

LRESULT CImageView::OnDepthAdd(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

	pLayerBitmap->m_pBitmapDepth = new LDraw::Bitmap(pLayerBitmap->m_pBitmap->GetWidth(), pLayerBitmap->m_pBitmap->GetHeight(), PixelFormat16bppGrayScale);

	CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
	paintSite->InvalidateRect(NULL);

	return 0;
}

LRESULT CImageView::OnDepthClear(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	CImageLayerBitmap* pLayerBitmap = ((CImageLayerBitmap*)((CPImageLayerBitmap*)m_pActiveLayer)->m_layerUnknown);

	if (pLayerBitmap->m_pBitmapDepth)
	{
		LDraw::BitmapData depthData;
		pLayerBitmap->m_pBitmapDepth->LockBits(
			&LDraw::RectI(0, 0, pLayerBitmap->m_pBitmapDepth->GetWidth(), pLayerBitmap->m_pBitmapDepth->GetHeight()),
			LDraw::ImageLockModeRead,
			PixelFormat16bppGrayScale, &depthData);

		ZeroMemory(depthData.Scan0, depthData.Stride*depthData.Height);

		pLayerBitmap->m_pBitmapDepth->UnlockBits(&depthData);

		CComQIPtr<IHTMLPaintSite> paintSite = m_pBehaviorSite;
		paintSite->InvalidateRect(NULL);
	}

	return 0;
}

#endif

}
}
