// UIScrollBar.cpp : Implementation of CUIScrollBar
#include "stdafx.h"
#include "UI.h"
#include "UIScrollBar.h"

#include "..\Color_Conversion.h"

//#include "UITheme.h"

#ifdef _GDIPLUS_H
void RoundRect(Gdiplus::GraphicsPath* path, double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ double rx, /*[in]*/ double ry)
{
	float left = x;
	float top = y;
	float right = x+width;
	float bottom = y+height;

	if (rx > width/2) rx = width/2;
	if (ry > height/2) ry = height/2;

    // MAGICAL CONSTANT to map ellipse to beziers
   //  			2/3*(sqrt(2)-1) 
    const double EToBConst =	0.2761423749154; 
	 Gdiplus::PointF offset;
	 offset.X = rx*2 * EToBConst;
	 offset.Y = ry*2 * EToBConst;
/*
    CDblPoint centre;
	 centre.x = (left + right) / 2;
	 centre.y = (top + bottom) / 2;
*/
	 path->AddLine(left+rx, top, right-rx, top);
	 /*
	// top line
	{
		CComObject<CLSVGPathSegMovetoAbs>* seg;
		CComObject<CLSVGPathSegMovetoAbs>::CreateInstance(&seg);

		seg->m_x = left+rx;	seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	{
		CComObject<CLSVGPathSegLinetoAbs>* seg;
		CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg);

		seg->m_x = right-rx;	seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	 path->AddBezier(right-rx, top,
		right-rx+offset.X, top,
		right, top+ry-offset.Y,
		right, top+ry);
		 /*
	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);

		seg->m_x1 = right-rx+offset.X;		seg->m_y1 = top;
		seg->m_x2 = right;						seg->m_y2 = top+ry-offset.Y;
		seg->m_x = right;						seg->m_y = top+ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	path->AddLine(right, top+ry,
		right, bottom-ry);
	/*
// right line
	{
		CComObject<CLSVGPathSegLinetoAbs>* seg;
		CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg);

		seg->m_x = right;	seg->m_y = bottom-ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	path->AddBezier(right, bottom-ry,
		right, bottom-ry+offset.Y,
		right-rx+offset.X, bottom,
		right-rx, bottom);
	/*
	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);

		seg->m_x1 = right;						seg->m_y1 = bottom-ry+offset.Y;
		seg->m_x2 = right-rx+offset.X;		seg->m_y2 = bottom;
		seg->m_x = right-rx;					seg->m_y = bottom;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	path->AddLine(right-rx, bottom,
		left+rx, bottom);
	/*
// bottom line
	{
		CComObject<CLSVGPathSegLinetoAbs>* seg;
		CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg);

		seg->m_x = left+rx;	seg->m_y = bottom;
		seg->m_pSegList = this;

		seg->AddRef();
		m_items.Add(seg);
	}
	*/

	path->AddBezier(left+rx, bottom,
		left+rx-offset.X,	bottom,
		left, bottom-ry+offset.Y,
		left, bottom-ry);
	/*
	{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);

		seg->m_x1 = left+rx-offset.X;	seg->m_y1 = bottom;
		seg->m_x2 = left;					seg->m_y2 = bottom-ry+offset.Y;
		seg->m_x = left;						seg->m_y = bottom-ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	path->AddLine(left, bottom-ry,
		left, top+ry);
	/*
// left line
	{
		CComObject<CLSVGPathSegLinetoAbs>* seg;
		CComObject<CLSVGPathSegLinetoAbs>::CreateInstance(&seg);

		seg->m_x = left;	seg->m_y = top+ry;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}
	*/

	path->AddBezier(left, top+ry,
		left, top+ry-offset.Y,
		left+rx-offset.X, top,
		left+rx, top);

		/*{
		CComObject<CLSVGPathSegCurvetoCubicAbs>* seg;
		CComObject<CLSVGPathSegCurvetoCubicAbs>::CreateInstance(&seg);

		seg->m_x1 = left;					seg->m_y1 = top+ry-offset.Y;
		seg->m_x2 = left+rx-offset.X;	seg->m_y2 = top;
		seg->m_x = left+rx;					seg->m_y = top;

		seg->AddRef();
		seg->m_pSegList = this;
		m_items.Add(seg);
	}

	ChangedSeg();
	*/

	path->CloseFigure();
}
#endif

//#pragma comment(lib, "uxtheme.lib")

typedef HTHEME  (STDAPICALLTYPE *fOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (STDAPICALLTYPE *fCloseThemeData)(HTHEME hTheme);
typedef HRESULT (STDAPICALLTYPE *fDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);

fOpenThemeData uxOpenThemeData;
fCloseThemeData uxCloseThemeData;
fDrawThemeBackground uxDrawThemeBackground;

extern fOpenThemeData uxOpenThemeData;
extern fCloseThemeData uxCloseThemeData;
extern fDrawThemeBackground uxDrawThemeBackground;

/////////////////////////////////////////////////////////////////////////////
// CUIScrollBar

int CUIScrollBar::FinalConstruct()
{
//	xThemeInit();

	m_hUxThemeLib = LoadLibrary("uxtheme.dll");
	if (m_hUxThemeLib)
	{
		uxOpenThemeData = (fOpenThemeData)GetProcAddress(m_hUxThemeLib, "OpenThemeData");
		uxCloseThemeData = (fCloseThemeData)GetProcAddress(m_hUxThemeLib, "CloseThemeData");
		uxDrawThemeBackground = (fDrawThemeBackground)GetProcAddress(m_hUxThemeLib, "DrawThemeBackground");

		m_hTheme = uxOpenThemeData(NULL, L"SCROLLBAR");
	}

	return S_OK;
}

void CUIScrollBar::FinalRelease()
{
	if (m_hTheme)
	{
		uxCloseThemeData(m_hTheme);
		m_hTheme = NULL;
	}

	if (m_hUxThemeLib)
	{
		FreeLibrary(m_hUxThemeLib);
		m_hUxThemeLib = NULL;
	}
}

HRESULT CUIScrollBar::OnDraw(ATL_DRAWINFO& di)
{
	CRect& rc = *(CRect*)di.prcBounds;

	/*
	if (rc.left != m_rcPos.left || rc.top != m_rcPos.top || rc.right != m_rcPos.right || rc.bottom != m_rcPos.bottom)
	{
		::MessageBox(NULL, "scrollbar size diff!!", "", MB_OK);
	}
	*/

	OnSize(rc);

	HDC ehDC = di.hdcDraw;

	CRect client = rc;
	//GetClientRect(&client);

	BITMAPINFO	bmi = {0};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = client.Width();
	bmi.bmiHeader.biHeight = client.Height();
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 24;

	COLORREF clr = GetSysColor(COLOR_MENU);
	DWORD hsv = rgb_to_hsv(clr);

	int h = GetRValue(hsv);
	int s = GetGValue(hsv);
	int v = GetBValue(hsv);

	COLORREF bgdarkdark = hsv_to_rgb(RGB(h, s, v*0.4));
	COLORREF bgdark = hsv_to_rgb(RGB(h, s, v*0.6));
	COLORREF bglight = hsv_to_rgb(RGB(h, s, v*0.8));

	COLORREF fgdark = hsv_to_rgb(RGB(h, s, v*0.8));
	COLORREF fglight = hsv_to_rgb(RGB(h, s, v));

	LPBYTE bits;
	HBITMAP hBitmap = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);
	if (hBitmap)
	{
		HDC hDC = CreateCompatibleDC(ehDC);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);

		CDCHandle dc = hDC;

		if (m_hTheme)
		{
			int iPartId;
			int iStateId;

		// left/up
			if (m_dir == 1)	// vertical
			{
				if (m_dragging == 2 && m_bIsInside)
					iStateId = ABS_UPPRESSED;
				else
					iStateId = ABS_UPNORMAL;
			}
			else
			{
				if (m_dragging == 2 && m_bIsInside)
					iStateId = ABS_LEFTPRESSED;
				else
					iStateId = ABS_LEFTNORMAL;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 SBP_ARROWBTN,
				 iStateId,
				 &m_leftR,
				 NULL);
		
		// right/down
			if (m_dir == 1)	// vertical
			{
				if (m_dragging == 3 && m_bIsInside)
					iStateId = ABS_DOWNPRESSED;
				else
					iStateId = ABS_DOWNNORMAL;
			}
			else
			{
				if (m_dragging == 3 && m_bIsInside)
					iStateId = ABS_RIGHTPRESSED;
				else
					iStateId = ABS_RIGHTNORMAL;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 SBP_ARROWBTN,
				 iStateId,
				 &m_rightR,
				 NULL);

			if (m_dir == 0)
			{
				CRect leftTR(m_leftR.right, m_knobR.top, m_knobR.left, m_knobR.bottom);
				CRect rightTR(m_knobR.right, m_knobR.top, m_rightR.left, m_knobR.bottom);

				iPartId = SBP_UPPERTRACKHORZ;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &leftTR,
				 NULL);

				iPartId = SBP_LOWERTRACKHORZ;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &rightTR,
				 NULL);
			}
			else
			{
				CRect leftTR(m_knobR.left, m_leftR.bottom, m_knobR.right, m_knobR.top);
				CRect rightTR(m_knobR.left, m_knobR.bottom, m_knobR.right, m_rightR.top);

				iPartId = SBP_UPPERTRACKVERT;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &leftTR,
				 NULL);

				iPartId = SBP_LOWERTRACKVERT;
				uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 SCRBS_NORMAL,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &rightTR,
				 NULL);
			}

		//
			if (m_dir == 0)
			{
				iPartId = SBP_THUMBBTNHORZ;
			}
			else
			{
				iPartId = SBP_THUMBBTNVERT;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 (m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &m_knobR,
				 NULL);

		//
			if (m_dir == 0)
			{
				iPartId = SBP_GRIPPERHORZ;
			}
			else
			{
				iPartId = SBP_GRIPPERVERT;
			}

			uxDrawThemeBackground(m_hTheme,
				 hDC,
				 iPartId,
				 0,//(m_dragging == 1)? SCRBS_PRESSED: SCRBS_NORMAL,//int iStateId,
				 &m_knobR,
				 NULL);
		}
		else
		{
			if (FALSE)
			{
#if 0
				if (m_dir == 0)
				{
					{
						Gdiplus::Graphics graphics(hDC);
						Gdiplus::Rect rect(m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height());
						Gdiplus::LinearGradientBrush brush(rect, Gdiplus::Color(255, 230, 230, 230), Gdiplus::Color(255, 255, 255, 255), Gdiplus::LinearGradientModeVertical);
						graphics.FillRectangle(&brush, rect);
					}

					CRgn rgn;
					rgn.CreateRoundRectRgn(m_knobR.left, m_knobR.top, m_knobR.right, m_knobR.bottom, m_knobR.Height()/2, m_knobR.Height()/2);

				//	Gdiplus::GraphicsPath path;
				//	RoundRect(&path, m_knobR.left, m_knobR.top, m_knobR.Width(), m_knobR.Height(), m_knobR.Height()/2, m_knobR.Height()/2);

					SelectClipRgn(hDC, rgn);

					xThemeDrawBackground(hDC, &m_knobR);
					xThemeDrawEdge(hDC, &m_knobR, xTheme_EDGE_RECT, 0);
				}
				else
				{
					{
						Gdiplus::Graphics graphics(hDC);
						Gdiplus::Rect rect(m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height());
						Gdiplus::LinearGradientBrush brush(rect, Gdiplus::Color(255, 230, 230, 230), Gdiplus::Color(255, 255, 255, 255), Gdiplus::LinearGradientModeHorizontal);
						graphics.FillRectangle(&brush, rect);
					}

				//	Gdiplus::GraphicsPath path;
				//	RoundRect(&path, m_knobR.left, m_knobR.top, m_knobR.Width(), m_knobR.Height(), m_knobR.Width()/2, m_knobR.Width()/2);
				//	graphics.SetClip(&path);

					CRgn rgn;
					rgn.CreateRoundRectRgn(m_knobR.left, m_knobR.top, m_knobR.right, m_knobR.bottom, m_knobR.Width()/2, m_knobR.Width()/2);

					SelectClipRgn(hDC, rgn);

					xThemeDrawBackground(hDC, &m_knobR);
					xThemeDrawEdge(hDC, &m_knobR, xTheme_EDGE_RECT, 0);
				}
#endif
			}
			else	// old-style scrollbar
			{
				FillSolidRect(hDC, 0, 0, client.Width(), client.Height(), RGB(255, 0, 0));

				/*
				if (m_dir == 0)
				{
					DrawVertGradient(hDC, m_leftR, fglight, fgdark);
					DrawVertGradient(hDC, m_rightR, fglight, fgdark);
				}
				else
				{
					DrawHorzGradient(hDC, m_leftR, fglight, fgdark);
					DrawHorzGradient(hDC, m_rightR, fglight, fgdark);
				}
				*/

				if (m_dragging == 2 && m_bIsInside)
				{
					Draw3DRect(hDC, m_leftR.left, m_leftR.top, m_leftR.Width(), m_leftR.Height(), bgdarkdark, RGB(255, 255, 255));
				}
				else
				{
					Draw3DRect(hDC, m_leftR.left, m_leftR.top, m_leftR.Width(), m_leftR.Height(), RGB(255, 255, 255), bgdarkdark);
					Draw3DRect(hDC, m_leftR.left+1, m_leftR.top+1, m_leftR.Width()-2, m_leftR.Height()-2, RGB(200, 200, 200), RGB(60, 60, 60));
				}

				if (m_dragging == 3 && m_bIsInside)
				{
					Draw3DRect(hDC, m_rightR.left, m_rightR.top, m_rightR.Width(), m_rightR.Height(), bgdarkdark, RGB(255, 255, 255));
				}
				else
				{
					Draw3DRect(hDC, m_rightR.left, m_rightR.top, m_rightR.Width(), m_rightR.Height(), RGB(255, 255, 255), bgdarkdark);
					Draw3DRect(hDC, m_rightR.left+1, m_rightR.top+1, m_rightR.Width()-2, m_rightR.Height()-2, RGB(200, 200, 200), RGB(60, 60, 60));
				}
				
				/*
				if (m_dir == 0)
				{
					DrawVertGradient(hDC, m_slidR, bgdark, bglight);
				}
				else
				{
					DrawHorzGradient(hDC, m_slidR, bgdark, bglight);
				}
				*/
				{
					CBrush brush = dc.GetHalftoneBrush();
					dc.SetTextColor(GetSysColor(COLOR_SCROLLBAR));
					dc.SetBkColor(RGB(255, 255, 255));
					FillRect(hDC, &m_slidR, brush);
				}

			//	Draw3DRect(hDC, m_slidR.left, m_slidR.top, m_slidR.Width(), m_slidR.Height(), RGB(255, 255, 255), bgdark/*RGB(0, 0, 0)*/);
				
				HBRUSH	blackBrush = CreateSolidBrush(bgdarkdark);
				HBRUSH	hOldBrush = (HBRUSH)SelectObject(hDC, blackBrush);
				HPEN		blackPen = CreatePen(PS_SOLID, 1, bgdark);
				HPEN		hOldPen = (HPEN)SelectObject(hDC, blackPen);
				
				if (m_dir == 0)
				{
					DrawFrameControl(hDC, &m_leftR, DFC_SCROLL, DFCS_SCROLLLEFT | ((m_dragging == 2 && m_bIsInside)?DFCS_PUSHED:0));
					DrawFrameControl(hDC, &m_rightR, DFC_SCROLL, DFCS_SCROLLRIGHT | ((m_dragging == 3 && m_bIsInside)?DFCS_PUSHED:0));
					/*
					int o;
					
					o = 0;
					if (m_dragging == 3 && m_bIsInside) o++;

					POINT rpt[] =
					{
						m_rightR.left+4+o, m_rightR.top+4+o,
						m_rightR.left+4+o, m_rightR.bottom-4+o,
						m_rightR.right-4+o, m_rightR.Height()/2+o,
					};

					o = 0;
					if (m_dragging == 2 && m_bIsInside) o++;
					
					POINT lpt[] =
					{
						m_leftR.right-4+o, m_leftR.top+4+o,
						m_leftR.right-4+o, m_leftR.bottom-4+o,
						m_leftR.left+4+o, m_leftR.Height()/2+o,
					};
					
					Polygon(hDC, lpt, 3);
					Polygon(hDC, rpt, 3);
					*/
				}
				else
				{
					DrawFrameControl(hDC, &m_leftR, DFC_SCROLL, DFCS_SCROLLUP | ((m_dragging == 2 && m_bIsInside)?DFCS_PUSHED:0));
					DrawFrameControl(hDC, &m_rightR, DFC_SCROLL, DFCS_SCROLLDOWN | ((m_dragging == 3 && m_bIsInside)?DFCS_PUSHED:0));

					/*
					int o;
					
					o = 0;
					if (m_dragging == 3 && m_bIsInside) o++;

					POINT rpt[] =
					{
						m_rightR.left+4+o, m_rightR.top+4+o,
						m_rightR.right-4+o, m_rightR.top+4+o,
						m_rightR.left+m_rightR.Width()/2+o, m_rightR.bottom-4+o,
					};
					
					o = 0;
					if (m_dragging == 2 && m_bIsInside) o++;
					
					POINT lpt[] =
					{
						m_leftR.left+4+o, m_leftR.bottom-4+o,
						m_leftR.right-4+o, m_leftR.bottom-4+o,
						m_leftR.left+m_leftR.Width()/2+o, m_leftR.top+4+o,
					};
					
					Polygon(hDC, lpt, 3);
					Polygon(hDC, rpt, 3);
					*/
				}

				SelectObject(hDC, hOldBrush);
				SelectObject(hDC, hOldPen);
				
			// Draw the slider knob
				{
					CRect rc = m_knobR;

					dc.Draw3dRect(&rc, GetSysColor(COLOR_SCROLLBAR), bgdarkdark);
					rc.InflateRect(-1, -1);

					dc.Draw3dRect(&rc, RGB(255, 255, 255), bgdarkdark);
					rc.InflateRect(-1, -1);

					dc.FillSolidRect(&rc, GetSysColor(COLOR_SCROLLBAR));
				}

				DeleteObject(blackBrush);
				DeleteObject(blackPen);
			}
		}

	///
		BitBlt(ehDC, client.left, client.top, client.Width(), client.Height(), hDC, 0, 0, SRCCOPY);

		SelectObject(hDC, hOldBitmap);
		DeleteDC(hDC);
		DeleteObject(hBitmap);
	}

	return 0;
}

void CUIScrollBar::OnSize(RECT& rcPos)
{
	int cx = rcPos.right-rcPos.left;
	int cy = rcPos.bottom-rcPos.top;

	int l = 0;//m_rcPos.left;
	int t = 0;//m_rcPos.top;
	int r = cx;
	int b = cy;

	if (m_dir == 0)
	{
		SetRect(&m_leftR, l, t, l+16, b);
		SetRect(&m_rightR, r-16, 0, r, b);
		SetRect(&m_slidR, l+16, t, r-16, b);
	}
	else
	{
		SetRect(&m_leftR, l, t, r, t+16);
		SetRect(&m_rightR, l, b-16, r, b);
		SetRect(&m_slidR, l, t+16, r, b-16);
	}

	SetIt();
}

void CUIScrollBar::SetIt()
{
	int minsize = 10;

	int totalrange = m_max-m_min+1;
	int abspos = m_pos - m_min;
	int width = (m_dir == 0)? m_slidR.Width(): m_slidR.Height();

	int kpos;
	int ksize;

	if (totalrange > m_visible)
	{
		ksize = (width * (m_visible)) / (totalrange);

		if (ksize < minsize) ksize = minsize;	// Don't allow smaller than this

	//	kpos = (abspos * width) / totalrange;
		kpos = (abspos * (width-ksize)) / (totalrange-m_visible);

		if (ksize > width) ksize = width;
	}
	else
	{
		kpos = 0;
		ksize = width;
	}

	if (m_dir == 0)	// horizontal
	{
		m_knobR.SetRect(
			m_slidR.left + kpos, m_slidR.top,
			m_slidR.left + kpos + ksize, m_slidR.bottom);
	}
	else	// vertical
	{
		m_knobR.SetRect(
			m_slidR.left, m_slidR.top+kpos,
			m_slidR.right, m_slidR.top + kpos + ksize);
	}
}

long CUIScrollBar::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT nID = wParam;

	//CIUIWnd* pParent = GetParent();

	if (m_dragging > 1)
	{
		if (m_bIsInside)
		{
			if (m_dragging == 2)
			{
				if (m_pos > m_min)
					Fire_SetPos(SB_LINELEFT, 0);//pParent->TOP()->OnScroll(SB_LINELEFT, 0, this);
			}
			else if (m_dragging == 3)
			{
				if (m_pos < m_max-m_visible)
					Fire_SetPos(SB_LINERIGHT, 0);//pParent->TOP()->OnScroll(SB_LINERIGHT, 0, this);
			}
		}
	}

	return 0;
}

long CUIScrollBar::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	if (m_leftR.PtInRect(point))	// Left arrow
	{
		m_dragging = 2;
		m_spInPlaceSite->InvalidateRect(&m_leftR, TRUE);
	}
	else if (m_rightR.PtInRect(point))	// Right arrow
	{
		m_dragging = 3;
		m_spInPlaceSite->InvalidateRect(&m_rightR, TRUE);
	}
	else if (m_knobR.PtInRect(point))	// Knob
	{
		m_dragging = 1;

		if (m_dir == 0)
			m_ptoffset = point.x - m_knobR.left;
		else
			m_ptoffset = point.y - m_knobR.top;
	}
	else if (m_slidR.PtInRect(point))	// Either on left or right side of knob
	{
		if (m_dir == 0)
		{
			if (point.x < m_knobR.left)
				m_dragging = 4;
			else
				m_dragging = 5;
		}
		else
		{
			if (point.y < m_knobR.top)
				m_dragging = 4;
			else
				m_dragging = 5;
		}

		//CIUIWnd* pParent = GetParent();

		if (m_dragging == 4)
		{
			if (m_pos > m_min)
				Fire_SetPos(SB_PAGELEFT, 0);//pParent->TOP()->OnScroll(SB_PAGELEFT, 0, this);
		}
		else
		{
			if (m_pos < m_max-m_visible)
				Fire_SetPos(SB_PAGERIGHT, 0);//pParent->TOP()->OnScroll(SB_PAGERIGHT, 0, this);
		}

		m_dragging = 0;
	}

	if (m_dragging)
	{
		m_bIsInside = TRUE;

		if (m_dragging > 1)
		{
			BOOL bHandled = TRUE;
			OnTimer(WM_TIMER, 1, 0, bHandled);

#if 0
			HWND hwnd;
			get_hwnd(&hwnd);

			SetTimer(hwnd, 1, 200, NULL);
#endif
		}

		m_spInPlaceSite->SetCapture(TRUE);
	}

	return 0;
}

LRESULT CUIScrollBar::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	if (m_dragging)
	{
		if (m_dragging == 1)
		{
		//	CIUIWnd* pParent = GetParent();
			
			POINT pt;
			pt.x = point.x - m_slidR.left;
			pt.y = point.y - m_slidR.top;

			int width = (m_dir == 0)? m_slidR.Width(): m_slidR.Height();
			int ksize = (m_dir == 0)? m_knobR.Width(): m_knobR.Height();

			int totalrange = m_max - m_min+1;// - m_visible;
			if (width > ksize)
			{
				int abspos;
				
				if (m_dir == 0)
				{
					abspos = (pt.x-m_ptoffset)*(totalrange-m_visible) / (width-ksize);
				}
				else
				{
					abspos = (pt.y-m_ptoffset)*(totalrange-m_visible) / (width-ksize);
				}
				
				int pos = abspos + m_min;
				
				if (pos > m_max-m_visible+1) pos = m_max-m_visible+1;
				if (pos < m_min) pos = m_min;
				
				Fire_SetPos(SB_THUMBTRACK, pos);
				//pParent->TOP()->OnScroll(SB_THUMBTRACK, pos, this);
			}
		}
		else
		{
			BOOL bInside;

			if (m_dragging == 2) bInside = m_leftR.PtInRect(point);
			else if (m_dragging == 3) bInside = m_rightR.PtInRect(point);

			if (m_bIsInside != bInside)
			{
				if (m_dragging == 2) m_spInPlaceSite->InvalidateRect(&m_leftR, TRUE);
				else if (m_dragging == 3) m_spInPlaceSite->InvalidateRect(&m_rightR, TRUE);

				m_bIsInside = bInside;
			}
		}
	}

	return 0;
}

long CUIScrollBar::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	point.x -= m_rcPos.left;
	point.y -= m_rcPos.top;

	if (m_dragging)
	{
		if (m_dragging > 1)
		{
#if 0
			HWND hwnd;
			get_hwnd(&hwnd);
			KillTimer(hwnd, 1);
#endif
		}

		m_spInPlaceSite->SetCapture(FALSE);
		m_dragging = 0;

	//	InvalidateRect(&m_leftR, TRUE);
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);

		//CIUIWnd* pParent = GetParent();
		Fire_SetPos(SB_ENDSCROLL, m_pos);//pParent->OnScroll(SB_ENDSCROLL, 0, this);
	}

	return 0;
}

STDMETHODIMP CUIScrollBar::get_pos(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pos;
	return S_OK;
}

STDMETHODIMP CUIScrollBar::put_pos(long newVal)
{
	if (newVal > m_max-m_visible+1) newVal = m_max-m_visible+1;
	if (newVal < m_min) newVal = m_min;

	if (newVal != m_pos)
	{
		m_pos = newVal;

		SetIt();

		if (m_spInPlaceSite)
		{
			m_spInPlaceSite->InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}

STDMETHODIMP CUIScrollBar::SetInfo(long minv, long maxv, long visible)
{
	m_min = minv;
	m_max = maxv;
	m_visible = visible;
	if (m_visible < 0) m_visible = 0;

	long pos = m_pos;

	if (pos > m_max-(m_visible/*-1*/))
		pos = m_max-(m_visible/*-1*/);

	if (pos < m_min)
		pos = m_min;

	if (pos != m_pos)
	{
		Fire_SetPos(SB_THUMBTRACK, pos);
	}

	SetIt();
	if (m_spInPlaceSite)
	{
		m_spInPlaceSite->InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUIScrollBar::get_direction(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_dir;
	return S_OK;
}

STDMETHODIMP CUIScrollBar::put_direction(long newVal)
{
	m_dir = newVal;
	return S_OK;
}

STDMETHODIMP CUIScrollBar::get_minv(/*[out, retval]*/ long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_min;
	return S_OK;
}

STDMETHODIMP CUIScrollBar::get_maxv(/*[out, retval]*/ long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_max;
	return S_OK;
}

STDMETHODIMP CUIScrollBar::get_visible(/*[out, retval]*/ long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_visible;
	return S_OK;
}
