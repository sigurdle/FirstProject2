// UIColorSlider.cpp : Implementation of CUIColorSlider
#include "stdafx.h"
#include "UI.h"
#include "UIColorSlider.h"

#include "..\Color_Conversion.h"

void inline SetRGBTriple(RGBTRIPLE* triple, BYTE r, BYTE g, BYTE b)
{
	triple->rgbtRed = r;
	triple->rgbtGreen = g;
	triple->rgbtBlue = b;
}

/////////////////////////////////////////////////////////////////////////////
// CUIColorSlider

long CUIColorSlider::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	if (!(m_ddc = DrawDibOpen())) return -1;

	return 0;
}

long CUIColorSlider::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	if (m_ddc) DrawDibClose(m_ddc);

	return 0;
}

HRESULT CUIColorSlider::OnDraw(ATL_DRAWINFO& di)
{
	CDCHandle dc(di.hdcDraw);

	ASSERT((m_type >= 0) && (m_type <= 3)); 

	CRect client = *(CRect*)di.prcBounds;
//	CRect	client = m_rcPos;

	CRect sliderRect = client;
	sliderRect.left += 3;
	sliderRect.right -= 3;
	sliderRect.bottom -= 5;

	if (!m_bEnabled)
	{
		dc.Draw3dRect(&sliderRect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DSHADOW));
	}
	else
	{
		dc.Draw3dRect(&sliderRect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHILIGHT));
		sliderRect.InflateRect(-1,-1);

		dc.Draw3dRect(&sliderRect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW));
		sliderRect.InflateRect(-1,-1);

		if (m_bEnabled == 1)
		{
	#define ROWBYTES(width,bitcount)			((((width)*(bitcount)+31) >> 3) & 0xfffc)

			int bytesPerRow = ROWBYTES(sliderRect.Width(), 24);
			BITMAPINFOHEADER	bmi;
			ZeroMemory(&bmi, sizeof(bmi));
			bmi.biSize = sizeof(BITMAPINFOHEADER);
			bmi.biWidth = sliderRect.Width();
			bmi.biHeight = sliderRect.Height();
			bmi.biPlanes = 1;
			bmi.biBitCount = 24;
			bmi.biCompression = BI_RGB;
			bmi.biSizeImage = bytesPerRow*sliderRect.Height();

			LPBYTE bits = (LPBYTE)GlobalAlloc(0, bmi.biSizeImage);

			if (bits)
			{
				int from[4] = {GetRValue(m_fromValue), GetGValue(m_fromValue), GetBValue(m_fromValue)};
				int to[4] = {GetRValue(m_toValue), GetGValue(m_toValue), GetBValue(m_toValue)};

				for (int x = 0; x < sliderRect.Width(); x++)
				{
					RGBTRIPLE rgb;

					int value = (x*256)/sliderRect.Width();

					int v[4];

					for (int i = 0; i < 3; i++)
					{
						v[i] = from[i] + (to[i]-from[i])*value/255;
					}

					if (m_colorMode == 1)	// Grayscale
					{
						rgb.rgbtRed = value;
						rgb.rgbtGreen = value;
						rgb.rgbtBlue = value;
					}
					else if (m_colorMode == 2)	// RGB
					{
						rgb.rgbtRed = v[0];
						rgb.rgbtGreen = v[1];
						rgb.rgbtBlue = v[2];
					}
					else if (m_colorMode == 3)	// HSB
					{
						COLORREF clr = HLStoRGB(HLS(v[0], v[1], v[2]));
						rgb.rgbtRed = GetRValue(clr);
						rgb.rgbtGreen = GetGValue(clr);
						rgb.rgbtBlue = GetBValue(clr);
					}

					LPBYTE p = (bits + x*3);

					for (int y = 0; y < sliderRect.Height(); y++)
					{
						*(RGBTRIPLE*)p = rgb;
						p += bytesPerRow;
					}
				}

				/*
				if (TRUE)
				{
					DrawDibDraw(m_ddc, hDC,
						1, 1, width, height,
						&bmi, bits,
						0, 0, width, height,
						((m_type == 2)? DDF_SAME_HDC: 0) | DDF_BACKGROUNDPAL);
				}
				else
				*/
				{
					dc.SetDIBitsToDevice(
						sliderRect.left, sliderRect.top, sliderRect.Width(), sliderRect.Height(),
						0, 0, 0, sliderRect.Height(),
						bits, (LPBITMAPINFO)&bmi,
						DIB_RGB_COLORS);
				}

				GlobalFree(bits);
			}
		}

		if (m_pos >= 0 && m_pos <= 255)	// Defined
		{
			sliderRect.left -= 1;
			sliderRect.right += 1;

			int x = sliderRect.left + (double)(m_pos*(sliderRect.Width()-1))/(256) + 0.5;
			int y = sliderRect.bottom+1;

		//	ATLTRACE("draw: %d, %d\n", sliderRect.left, sliderRect.Width());

			POINT pts[3] =
			{
				x, y,
				x-4, y+4,
				x+4, y+4,
			};

			dc.Polygon(pts, 3);
		}
	}

	return 0;
}

long CUIColorSlider::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

long CUIColorSlider::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_bEnabled)
	{
		if (!m_dragging)
		{
			m_dragging = 1;
			m_spInPlaceSite->SetCapture(TRUE);

			BOOL bHandled = TRUE;
			OnMouseMove(uMsg, wParam, lParam, bHandled);
		}
	}

	return 0;
}

long CUIColorSlider::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		m_dragging = 0;
		m_spInPlaceSite->SetCapture(FALSE);
	}

	return 0;
}

LRESULT CUIColorSlider::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		CRect	client = m_rcPos;

		CRect sliderRect = client;
		sliderRect.left += 3+1;
		sliderRect.right -= 3+1;
		sliderRect.bottom -= 5;

		point.x -= sliderRect.left;//client.left;
		point.y -= client.top;

	//	ATLTRACE("mousemove: x:%d,width:%d\n", point.x, sliderRect.Width());

		long pos;

		if (TRUE)	// Horizontal
			pos = (point.x*256)/(sliderRect.Width()-1);
		else
			;

		if (pos < 0) pos = 0;
		else if (pos > 255) pos = 255;

		if (pos != m_pos)
		{
			m_pos = pos;

			/*
			if (m_channel < 3)
			{
				BYTE	red = GetRValue(m_rgb);
				BYTE	green = GetGValue(m_rgb);
				BYTE	blue = GetBValue(m_rgb);

				if (m_channel == 0)
					m_rgb = RGB(pos, green, blue);
				else if (m_channel == 1)
					m_rgb = RGB(red, pos, blue);
				else
					m_rgb = RGB(red, green, pos);
			}
			*/
		/*
			else if (m_slide < 6)
			{
				COLORREF	hls = RGBtoHLS(m_rgb);
				BYTE	hue = GetHValue(hls);
				BYTE	lum = GetLValue(hls);
				BYTE	sat = GetSValue(hls);

				if (m_slide == 3)
					m_rgb = HLStoRGB(HLS(pos, lum, sat));
				else if (m_slide == 4)
					m_rgb = HLStoRGB(HLS(hue, pos, sat));
				else
					m_rgb = HLStoRGB(HLS(hue, lum, pos));
			}
			*/
			/*
			else	// Grayscale
			{
			//	m_rgb = RGB(pos, pos, pos);
			}
			*/

			Fire_SetPos(m_pos);
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}

	return 0;
}

STDMETHODIMP CUIColorSlider::get_channel(long *pVal)
{
	*pVal = m_channel;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_channel(long newVal)
{
	m_channel = newVal;
	m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	return S_OK;
}

STDMETHODIMP CUIColorSlider::get_rgb(DWORD *pVal)
{
	if (m_channel == 0)
	{
		*pVal = RGB(m_pos, GetGValue(m_fromValue), GetBValue(m_fromValue));
	}
	else if (m_channel == 1)
	{
		*pVal = RGB(GetRValue(m_fromValue), m_pos, GetBValue(m_fromValue));
	}
	else if (m_channel == 2)
	{
		*pVal = RGB(GetRValue(m_fromValue), GetGValue(m_fromValue), m_pos);
	}
	/*
	else if (m_channel == 3)
	{
		*pVal = RGB(m_pos, GetGValue(m_fromVal), GetBValue(m_fromVal));
	}
	*/

//	*pVal = m_rgb;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_rgb(DWORD newVal)
{
	if (m_channel == 0)
	{
		m_fromValue = RGB(0, GetGValue(newVal), GetBValue(newVal));
		m_toValue = RGB(255, GetGValue(newVal), GetBValue(newVal));
		m_pos = GetRValue(newVal);
	}
	else if (m_channel == 1)
	{
		m_fromValue = RGB(GetRValue(newVal), 0, GetBValue(newVal));
		m_toValue = RGB(GetRValue(newVal), 255, GetBValue(newVal));
		m_pos = GetGValue(newVal);
	}
	else if (m_channel == 2)
	{
		m_fromValue = RGB(GetRValue(newVal), GetGValue(newVal), 0);
		m_toValue = RGB(GetRValue(newVal), GetGValue(newVal), 255);
		m_pos = GetBValue(newVal);
	}
	else if (m_channel == 3)
	{
		m_fromValue = CMYK(GetCValue(newVal), GetMValue(newVal), GetYValue(newVal), 0);
		m_toValue = CMYK(GetCValue(newVal), GetMValue(newVal), GetYValue(newVal), 255);
	}

	m_spInPlaceSite->InvalidateRect(NULL, TRUE);

	return S_OK;
}

STDMETHODIMP CUIColorSlider::get_colorMode(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_colorMode;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_colorMode(long newVal)
{
	if (m_colorMode != newVal)
	{
		m_colorMode = newVal;

		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUIColorSlider::get_fromValue(DWORD *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_fromValue;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_fromValue(DWORD newVal)
{
	m_fromValue = newVal;
	m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	return S_OK;
}

STDMETHODIMP CUIColorSlider::get_toValue(DWORD *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_toValue;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_toValue(DWORD newVal)
{
	m_toValue = newVal;
	m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	return S_OK;
}

STDMETHODIMP CUIColorSlider::get_pos(long *pVal)
{
	*pVal = m_pos;
	return S_OK;
}

STDMETHODIMP CUIColorSlider::put_pos(long newVal)
{
	m_pos = newVal;
	m_spInPlaceSite->InvalidateRect(NULL, TRUE);

	return S_OK;
}
