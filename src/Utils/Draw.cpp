#include "stdafx.h"

#include "Rect.h"
#include "Draw.h"

void Draw3DRect(HDC hDC, int x, int y, int cx, int cy, COLORREF light, COLORREF dark)
{
	HPEN hlpen = CreatePen(PS_SOLID, 1, light);
	HPEN hdpen = CreatePen(PS_SOLID, 1, dark);

	HPEN hOldPen = (HPEN)SelectObject(hDC, hlpen);

	MoveToEx(hDC, x+cx-1, y, NULL);
	LineTo(hDC, x, y);
	LineTo(hDC, x, y+cy-1);

	SelectObject(hDC, hdpen);
	LineTo(hDC, x+cx-1, y+cy-1);
	LineTo(hDC, x+cx-1, y);

	SelectObject(hDC, hOldPen);
	DeleteObject(hlpen);
	DeleteObject(hdpen);
}

void Draw3DRect(HDC hDC, int x, int y, int cx, int cy, RGBQUAD light, RGBQUAD dark)
{
	Draw3DRect(hDC, x, y, cx, cy, RGB(light.rgbRed, light.rgbGreen, light.rgbBlue), RGB(dark.rgbRed, dark.rgbGreen, dark.rgbBlue));
}

void Draw3DRect(HDC hDC, RECT* rect, COLORREF light, COLORREF dark)
{
	Draw3DRect(hDC, rect->left, rect->top, rect->right-rect->left, rect->bottom-rect->top, light, dark);
}

void FillSolidRect(HDC hDC, RECT* rect, COLORREF clr)
{
	FillSolidRect(hDC, rect->left, rect->top, rect->right-rect->left, rect->bottom-rect->top, clr);
}

void FillSolidRect(HDC hDC, int left, int top, int cx, int cy, COLORREF clr)
{
	HBRUSH hBrush = CreateSolidBrush(clr);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));

	Rectangle(hDC, left, top, left+cx+1, top+cy+1);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
}

void DrawVertGradient(HDC hDC, RECT* rect, COLORREF light, COLORREF dark)
{
	int height = rect->bottom - rect->top;
	int width = rect->right - rect->left;

	for (int y = 0; y < height; y++)
	{
		COLORREF clr = RGB(
			GetRValue(light) + (GetRValue(dark)-GetRValue(light)) * y / height,
			GetGValue(light) + (GetGValue(dark)-GetGValue(light)) * y / height,
			GetBValue(light) + (GetBValue(dark)-GetBValue(light)) * y / height,
		);

		FillSolidRect(hDC, rect->left, rect->top + y, width, 1, clr);
	}
}

void DrawHorzGradient(HDC hDC, RECT* rect, COLORREF light, COLORREF dark)
{
	int width = rect->right - rect->left;
	int height = rect->bottom - rect->top;

	for (int x = 0; x < width; x++)
	{
		COLORREF clr = RGB(
			GetRValue(light) + (GetRValue(dark)-GetRValue(light)) * x / width,
			GetGValue(light) + (GetGValue(dark)-GetGValue(light)) * x / width,
			GetBValue(light) + (GetBValue(dark)-GetBValue(light)) * x / width,
		);

		FillSolidRect(hDC, rect->left+x, rect->top, 1, height, clr);
	}
}

void DrawVertGradient(HDC hDC, RECT& rect, COLORREF light, COLORREF dark)
{
	DrawVertGradient(hDC, &rect, light, dark);
}

void DrawHorzGradient(HDC hDC, RECT& rect, COLORREF light, COLORREF dark)
{
	DrawHorzGradient(hDC, &rect, light, dark);
}

void TransparentBlt(HDC pDestDc, int x, int y, int w, int h, HBITMAP pBmp, int sx, int sy, COLORREF crTransparent)
{
	HDC memDC, maskDC, tempDC;
	maskDC = CreateCompatibleDC(pDestDc);
	HBITMAP maskBitmap;
	
	//add these to store return of SelectObject() calls
	HBITMAP pOldMemBmp = NULL;
	HBITMAP pOldMaskBmp = NULL;
	
	memDC = CreateCompatibleDC(pDestDc);
	tempDC = CreateCompatibleDC(pDestDc);
	HBITMAP bmpImage;
	bmpImage = CreateCompatibleBitmap( pDestDc, w, h);
	pOldMemBmp = (HBITMAP)SelectObject(memDC, bmpImage );

	HBITMAP oldBmp = (HBITMAP)SelectObject(tempDC, pBmp);
	
	BitBlt(memDC, 0,0,w, h, tempDC, sx, sy, SRCCOPY );
	
	// Create monochrome bitmap for the mask
	maskBitmap = CreateBitmap(w, h, 1, 1, NULL);
	pOldMaskBmp = (HBITMAP)SelectObject(maskDC, maskBitmap );
	SetBkColor(memDC, crTransparent);
	
	// Create the mask from the memory DC
	BitBlt(maskDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
	
	SetBkColor(memDC, RGB(0,0,0));
	SetTextColor(memDC, RGB(255,255,255));
	BitBlt(memDC, 0, 0, w, h, maskDC, 0, 0, SRCAND);
	
	// Set the foreground to black. See comment above.
	COLORREF oldBk = SetBkColor(pDestDc, RGB(255,255,255));
	COLORREF oldTx = SetTextColor(pDestDc, RGB(0,0,0));
	BitBlt(pDestDc, x, y, w, h, maskDC, 0, 0, SRCAND);
	
	// Combine the foreground with the background
	BitBlt(pDestDc, x, y, w, h, memDC, 0, 0, SRCPAINT);

	SetBkColor(pDestDc, oldBk);
	SetTextColor(pDestDc, oldTx);
	
	SelectObject(tempDC, oldBmp);
	if (pOldMaskBmp) SelectObject(maskDC, pOldMaskBmp );
	if (pOldMemBmp)  SelectObject(memDC, pOldMemBmp );

	DeleteDC(maskDC);
	DeleteDC(memDC);
	DeleteDC(tempDC);

	DeleteObject(bmpImage);
	DeleteObject(maskBitmap);
}
