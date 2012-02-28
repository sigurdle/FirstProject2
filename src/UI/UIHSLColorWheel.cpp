// HSLColorWheel.cpp : Implementation of CUIHSLColorWheel

#include "stdafx.h"
#include "UI.h"
#include "UIHSLColorWheel.h"

#include <math.h>
#include "..\Color_Conversion.h"
#include "..\gm\gmUtils.h"

#define M_PI 3.14159265358979323846

double GetLineAngle(double x1, double y1, double x2, double y2)
{
	double dx = x2-x1;
	double dy = y2-y1;

	double distance2 = sqrt(dx*dx + dy*dy);

	if (distance2 == 0.0) distance2 = 0.00001;
	if (dy < 0) distance2 =-distance2;
	double angle = acos(dx/distance2);
	if (dy < 0) angle += M_PI;

	return angle;
}

/////////////////////////////////////////////////////////////////////////////
// CUIHSLColorWheel

HRESULT CUIHSLColorWheel::OnDraw(ATL_DRAWINFO& di)
{
	RECT& rc = *(RECT*)di.prcBounds;
//	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

	CRect rect = rc;

	CDCHandle dc(di.hdcDraw);

	int width = min(rect.Width(), rect.Height());
	int height = width;

	int radius = width/2;

	if (m_bEnabled)
	{
		LPBITMAPINFO lpbmi = (LPBITMAPINFO)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER));
		if (lpbmi)
		{
			lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			lpbmi->bmiHeader.biWidth = width;
			lpbmi->bmiHeader.biHeight = height;
			lpbmi->bmiHeader.biBitCount = 32;
			lpbmi->bmiHeader.biPlanes = 1;
			lpbmi->bmiHeader.biCompression = BI_RGB;

			int rowbytes = ROWBYTES(width, lpbmi->bmiHeader.biBitCount);

			LPBYTE bits;
			HBITMAP hBitmap = CreateDIBSection(NULL, (BITMAPINFO*)lpbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
			if (hBitmap)
			{
				for (int y = 0; y < height; y++)
				{
					LPBYTE p = bits + rowbytes*(height-y-1);

					for (int x = 0; x < width; x++)
					{
						int dx = x-radius;
						int dy = y-radius;

						double distance = sqrt(dx*dx+dy*dy);

						if (distance > radius-10 && distance < radius)
						{
							double distance2 = distance;

							if (distance2 == 0.0) distance2 = 0.00001;
							if (dy < 0) distance2 =-distance2;
							double radangle = acos(dx/distance2);
							if (dy < 0) radangle += M_PI;

						//	COLORREF clr = HLStoRGB(HLS(gmDegrees(radangle)*255/360, 128, 200));
							COLORREF clr = HLStoRGB(HLS(gmDegrees(radangle)*255/360, 140, 210));

							p[0] = GetRValue(clr);
							p[1] = GetGValue(clr);
							p[2] = GetBValue(clr);

							if (distance < radius-8)
							{
								p[3] = 255*(distance-(radius-10))/2;
							}
							else if (distance < radius-2)
							{
								p[3] = 255;
							}
							else
							{
								p[3] = 255*(2-(distance-(radius-2)))/2;
							}
						}
						else
						{
							int left = radius - radius*2/4;
							int right = radius + radius*2/4;

							if (x >= left && x < right && y >= left && y < right)
							{
								int sat = (x-left)*255 / (right-left);
								int lum = (right-y)*255 / (right-left);
								COLORREF clr = HLStoRGB(HLS(m_hue*255/360, lum, sat));

								p[0] = GetRValue(clr);
								p[1] = GetGValue(clr);
								p[2] = GetBValue(clr);
								p[3] = 255;
							}
							else
							{
								p[3] = 0;
							}
						}

					// premultiply
						p[0] = p[0]*p[3]/255;
						p[1] = p[1]*p[3]/255;
						p[2] = p[2]*p[3]/255;

						p += 4;
					}
				}

				HDC hDC = CreateCompatibleDC(NULL);
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

				BLENDFUNCTION bf;
				bf.BlendOp = AC_SRC_OVER;
				bf.BlendFlags = 0;
				bf.SourceConstantAlpha = 255;
				bf.AlphaFormat = AC_SRC_ALPHA;

				AlphaBlend(dc.m_hDC, rect.left, rect.top, width, height, hDC, 0, 0, width, height, bf);

				SelectObject(hDC, hOldBitmap);
				DeleteDC(hDC);

				DeleteObject(hBitmap);
			}

			GlobalFree(lpbmi);
		}

		{
			int x = rect.left + cos(gmRadians(m_hue))*(radius-5) + radius;
			int y = rect.top + sin(gmRadians(m_hue))*(radius-5) + radius;

			dc.Ellipse(x-3, y-3, x+4, y+4);
		}
	}
	else	// m_bEnabled = FALSE
	{
		HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(NULL_BRUSH));

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		HPEN hOldPen = dc.SelectPen(pen);

		dc.Ellipse(rect.left, rect.top, rect.left+width, rect.left+height);

		dc.SelectPen(hOldPen);
		dc.SelectBrush(hOldBrush);
	}


	return S_OK;
}

LRESULT CUIHSLColorWheel::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect rect = m_rcPos;

	point.x -= rect.left;
	point.y -= rect.top;

	if (m_dragging == 0)
	{
		m_dragging = 1;
		m_spInPlaceSite->SetCapture(TRUE);
	}

	return 0;
}

LRESULT CUIHSLColorWheel::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_spInPlaceSite->SetCapture(FALSE);
		m_dragging = 0;
	}

	return 0;
}

LRESULT CUIHSLColorWheel::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect rect = m_rcPos;

	point.x -= rect.left;
	point.y -= rect.top;

	if (m_dragging)
	{
		int width = min(rect.Width(), rect.Height());
		int height = width;

		int radius = width/2;

		double rad = GetLineAngle(radius, radius, point.x, point.y);

		m_hue = gmDegrees(rad);

		m_spInPlaceSite->InvalidateRect(NULL, FALSE);
	}

	return 0;
}

STDMETHODIMP CUIHSLColorWheel::get_hue(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_hue;
	return S_OK;
}

STDMETHODIMP CUIHSLColorWheel::put_hue(long newVal)
{
	m_hue = newVal;
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, FALSE);
	}

	return S_OK;
}

STDMETHODIMP CUIHSLColorWheel::get_sat(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_sat;
	return S_OK;
}

STDMETHODIMP CUIHSLColorWheel::put_sat(long newVal)
{
	m_sat = newVal;
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, FALSE);
	}
	return S_OK;
}

STDMETHODIMP CUIHSLColorWheel::get_lum(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lum;
	return S_OK;
}

STDMETHODIMP CUIHSLColorWheel::put_lum(long newVal)
{
	m_lum = newVal;
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, FALSE);
	}
	return S_OK;
}
