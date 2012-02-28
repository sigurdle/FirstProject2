// ColorSpectrum.cpp : Implementation of CColorSpectrum

#include "stdafx.h"
#include "UI.h"
#include "ColorSpectrum.h"

#include "..\Color_Conversion.h"

/////////////////////////////////////////////////////////////////////////////
// CColorSpectrum

HRESULT CColorSpectrum::OnDraw(ATL_DRAWINFO& di)
{
	CRect& rc = *(CRect*)di.prcBounds;
	HDC hDC = di.hdcDraw;

	if (m_bEnabled)
	{
#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

		int width = rc.Width()-20;
		int height = rc.Height();

		FillSolidRect(hDC, rc.left+width, rc.top, 20, height/2, RGB(255, 255, 255));
		FillSolidRect(hDC, rc.left+width, rc.top+height/2, 20, rc.Height()-height/2, RGB(0, 0, 0));

		int bytesPerRow = ROWBYTES(width, 24);
		BITMAPINFOHEADER	bmi;
		ZeroMemory(&bmi, sizeof(bmi));
		bmi.biSize = sizeof(BITMAPINFOHEADER);
		bmi.biWidth = width;
		bmi.biHeight = height;
		bmi.biPlanes = 1;
		bmi.biBitCount = 24;
		bmi.biCompression = BI_RGB;
		bmi.biSizeImage = bytesPerRow*height;

		LPBYTE	bits = (LPBYTE)GlobalAlloc(0, bmi.biSizeImage);

		if (bits)
		{
			for (int y = 0; y < height; y++)
			{
				RGBTRIPLE* dest = (RGBTRIPLE*)(bits + (height-y-1)*bytesPerRow);

				for (int x = 0; x < width; x++)
				{
					int h = (x * 255)/width;
					int l = ((height-y-1) * 255)/height;
					int s = ((height-y-1) * 255)/height;
					//int s = 127;//(x * width)/255;

					COLORREF clr = HLStoRGB(HLS(h, l, s));
					dest->rgbtRed = GetRValue(clr);
					dest->rgbtGreen = GetGValue(clr);
					dest->rgbtBlue = GetBValue(clr);

					dest++;
				}
			}

			SetDIBitsToDevice(hDC,
				rc.left, rc.top, width, height,
				0, 0, 0, height,
				bits, (LPBITMAPINFO)&bmi,
				DIB_RGB_COLORS);

			GlobalFree(bits);
		}
	}

	return S_OK;
}

void CColorSpectrum::OnMouseMove(CPoint point, UINT nFlags)
{
	CRect	rcPos = m_rcPos;

	point.x -= rcPos.left;
	point.y -= rcPos.top;

	if (m_dragging)
	{
		COLORREF rgb;

		if (point.x > rcPos.Width()-20)
		{
			if (point.y < rcPos.Height()/2)
			{
				rgb = RGB(255, 255, 255);
			}
			else
			{
				rgb = RGB(0, 0, 0);
			}
		}
		else
		{
			int h = point.x * 255 / rcPos.Width();
			int l = (rcPos.Height()-point.y)*255 / rcPos.Height();
			int s = (rcPos.Height()-point.y)*255 / rcPos.Height();

			if (h < 0) h = 0;
			else if (h > 255) h = 255;

			if (l < 0) l = 0;
			else if (l > 255) l = 255;

			if (s < 0) s = 0;
			else if (s > 255) s = 255;

			rgb = HLStoRGB(HLS(h, l, s));
		}

		Fire_SetColorRGB(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	}
}

LRESULT CColorSpectrum::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	if (!m_dragging)
	{
		m_dragging = 1;
		m_spInPlaceSite->SetCapture(TRUE);

		OnMouseMove(point, nFlags);
	}

	return 0;
}

LRESULT CColorSpectrum::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		m_spInPlaceSite->SetCapture(FALSE);
	}

	return 0;
}

LRESULT CColorSpectrum::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	OnMouseMove(point, nFlags);

	return 0;
}
