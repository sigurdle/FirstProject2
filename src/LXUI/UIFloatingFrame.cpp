#include "stdafx.h"
#include "LXUI2.h"
#include "UIFloatingFrame.h"

#include "SizeBox.h"
#include "DragContext.h"

namespace System
{
namespace UI
{

/////////////////////////////////////////////////////////////////////////
// CUIFloatingFrame

CUIFloatingFrame::CUIFloatingFrame()
{
	//m_pOwnedWindow = NULL;
//	m_hWndParent = NULL;
#if 0
	m_dlgSite = NULL;
#endif
	m_dwStyle = 0;//CBRS_SIZE_DYNAMIC;//0L;
}

CUIFloatingFrame::~CUIFloatingFrame()
{
}

#if 0
void CUIFloatingFrame::put_Content(Visual* pContent)
{
#if 0
	CUIFrameImpl::put_Content(pContent);
#else

	/*
	Visual* pParent = pContent->GetRParent();
	if (pParent)
	{
		pParent->RemoveRChild(pContent);
	}

	if (pContent->m_pDockParent != NULL)
	{
		pContent->m_pDockParent->RemoveControlBar(pContent);
	}
	*/

	pContent->SetParent(this);

//	pContent->m_pDockParent = this;

	m_pContent = pContent;

	SizeBoxRubber* p = new SizeBoxRubber;
	{
		Border* pBorder = new Border;
		pBorder->put_BorderThickness(Thickness(Length(1), Length(1), Length(1), Length(1)));
		/*
		pBorder->m_LeftBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(0, 1));
		pBorder->m_TopBrush = new CLLinearGradientBrush(new Color(255, 255, 255), new Color(190, 190, 190), new Point(0, 0), new Point(1, 0));
		pBorder->m_RightBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(0, 1));
		pBorder->m_BottomBrush = new CLLinearGradientBrush(new Color(190, 190, 190), new Color(0, 0, 0), new Point(0, 0), new Point(1, 0));
		*/
		pBorder->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255));
		pBorder->m_TopBrush = new SolidColorBrush(Color(255, 255, 255));
		pBorder->m_RightBrush = new SolidColorBrush(Color(90, 90, 90));
		pBorder->m_BottomBrush = new SolidColorBrush(Color(90, 90, 90));

		{
			m_pBorder2 = new Border;
			m_pBorder2->put_Background(new SolidColorBrush(Color(102, 136, 187)));
		//	pBorder2->m_LeftBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_TopBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_RightBrush = new SolidColorBrush(new Color(102, 136, 187));
		//	pBorder2->m_BottomBrush = new SolidColorBrush(new Color(102, 136, 187));
			m_pBorder2->put_BorderThickness(Thickness(Length(2), Length(2), Length(2), Length(2)));
			{
				DockPanel* pDockPanel = new DockPanel;
				{
					{
						Border* pBorder = new Border;
					//	pBorder->put_BorderThickness(new Thickness(new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute)));
					//	pBorder->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));
						{
							DockPanel* pDockPanel2 = new DockPanel;
							{
								{
									m_CloseButton = new Button(new TextString(OLESTR("X")));
									pDockPanel2->put_Dock(m_CloseButton, DockPanel::Right);
									pDockPanel2->AddRChild(m_CloseButton);
								}
								{
									Button* pButton = new Button(new TextString(OLESTR("-")));
									pDockPanel2->put_Dock(pButton, DockPanel::Right);
									pDockPanel2->AddRChild(pButton);
								}

								/*
								{
									SizeBoxRubber* pTitlebar = new SizeBoxRubber();

									Border* pCanvas = new Border;
									pCanvas->put_BorderThickness(new Thickness(new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute), new Length(2, Length::UnitAbsolute)));
									//pCanvas->put_BackgroundBrush(new SolidColorBrush(new Color(102, 136, 187)));
									{
										//m_Title = new TextString(OLESTR(""));
										//m_Title->put_TextFill(new SolidColorBrush(new Color(255, 255, 255)));

										pCanvas->put_Content(m_Title);
									}
									pTitlebar->put_VisualTree(pCanvas);

									pDockPanel2->put_Dock(pTitlebar, DockPanel::Fill);
									pDockPanel2->AddRChild(pTitlebar);
								}
								*/
							}
							pBorder->put_Content(pDockPanel2);
						}
						pDockPanel->AddRChild(pBorder);
					}
				}

				/*
				{
					SizeBoxRubber* p = new SizeBoxRubber();

				//	p->put_Height(new Length(16, Length::UnitAbsolute));

					{
						Border* pRect = new Border();
					//	pRect->put_Width(new Length(1, Length::UnitPercentage));
					//	pRect->put_Height(new Length(16, Length::UnitAbsolute));
					//	pRect->put_BackgroundBrush(new SolidColorBrush(new Color(255, 136, 187)));
					//	pRect->put_Content(new TextString(L"Size"));

						p->put_VisualTree(pRect);
					}

					pDockPanel->put_Dock(p, DockPanel::Bottom);

					pDockPanel->AddRChild(p);
				}
				*/

				{
					pDockPanel->put_Dock(get_Content(), DockPanel::Fill);

					pDockPanel->AddRChild(get_Content());
				}
				m_pBorder2->put_Content(pDockPanel);
			}
			pBorder->put_Content(m_pBorder2);
		}
		p->put_VisualTree(pBorder);
	}
	set_VisualTree(p);

#if 0
	m_pContent = pContent;

	DockPanel* pDockPanel = new DockPanel;
	{
		{
			SizeBoxRubber* p = new SizeBoxRubber;
			p->put_Height(new Length(16, Length::UnitAbsolute));

			{
				CLXUICanvas* pCanvas = new CLXUICanvas;
				pCanvas->put_Width(new Length(1, Length::UnitPercentage));
				pCanvas->put_Height(new Length(1, Length::UnitPercentage));

				{
					CLXUIRectangle* pRect = new CLXUIRectangle();
					pRect->put_RectangleWidth(new Length(1, Length::UnitPercentage));
					pRect->put_RectangleHeight(new Length(1, Length::UnitPercentage));
					pRect->put_Fill(new SolidColorBrush(new Color(102, 136, 187)));

					pCanvas->AddRChild(pRect);
				}
				{
				//	m_Title = new TextString(OLESTR(""), font);
					/*
					pRect->m_computedLeft = 0;
					pRect->m_computedTop = 0;
					pRect->put_RectangleWidth(new Length(1, UnitPercentage));
					pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
					pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));
					*/

				//	pCanvas->appendChild(m_Title);
				}
				p->put_VisualTree(pCanvas);
			}
/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->m_computedLeft = 0;
				pRect->m_computedTop = 0;
				pRect->put_RectangleWidth(new Length(1, UnitPercentage));
				pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
				pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));

				p->put_VisualTree(pRect);
			//	p->appendChild(pRect);
			}
			*/

			pDockPanel->put_Dock(p, DockPanel::Top);
			pDockPanel->AddRChild(p);
		}

		{
			SizeBox* p = new SizeBox;
			p->put_Height(new Length(16, Length::UnitAbsolute));

			{
				CLXUICanvas* pCanvas = new CLXUICanvas;
				pCanvas->put_Width(new Length(1, Length::UnitPercentage));
				pCanvas->put_Height(new Length(1, Length::UnitPercentage));

				{
					CLXUIRectangle* pRect = new CLXUIRectangle();
					pRect->put_RectangleWidth(new Length(1, Length::UnitPercentage));
					pRect->put_RectangleHeight(new Length(1, Length::UnitPercentage));
					pRect->put_Fill(new SolidColorBrush(new Color(102, 136, 187)));

					pCanvas->AddRChild(pRect);
				}
				{
				//	m_Title = new TextString(OLESTR(""), font);
					/*
					pRect->m_computedLeft = 0;
					pRect->m_computedTop = 0;
					pRect->put_RectangleWidth(new Length(1, UnitPercentage));
					pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
					pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));
					*/

				//	pCanvas->appendChild(m_Title);
				}
				p->put_VisualTree(pCanvas);
			}
/*
			{
				CLXUIRectangle* pRect = new CLXUIRectangle();
				pRect->m_computedLeft = 0;
				pRect->m_computedTop = 0;
				pRect->put_RectangleWidth(new Length(1, UnitPercentage));
				pRect->put_RectangleHeight(new Length(16, UnitAbsolute));
				pRect->put_Fill(new CLSolidColorBrush(new CLColor(102, 136, 187)));

				p->put_VisualTree(pRect);
			//	p->appendChild(pRect);
			}
			*/

			pDockPanel->put_Dock(p, DockPanel::Bottom);
			pDockPanel->AddRChild(p);
		}

		pDockPanel->put_Dock(pContent, DockPanel::Fill);
		pDockPanel->AddRChild(pContent);
	}
//	pDockPanel->SetOwnerWindow(this);
	put_VisualTree(pDockPanel);

#endif
#endif
}
#endif

#if 0
void CUIFloatingFrame::CalculateBounds()
{
//	CLXUIFloatingFrameElement* psvgElement = static_cast<CLXUIFloatingFrameElement*>(m_pNode);

//	if (m_childChanged == 0)
	{
	//	m_childChanged++;

		/*
		gmMatrix3 matrix = GetLocalAnimatedMatrix();

		CPSVGElementImpl* pViewportElement = GetViewportElement();
		ATLASSERT(pViewportElement);

		RectD viewPort = pViewportElement->GetViewBox();
		*/
#if 0
		LDraw::RectD viewPort = LDraw::RectD(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

		CLSVGLength* xLength = psvgElement->m_x->m_animated->m_animVal->m_value;
		CLSVGLength* yLength = psvgElement->m_y->m_animated->m_animVal->m_value;
	//	CLSVGLength* widthLength = psvgElement->m_width->m_animated->m_animVal->m_value;
	//	CLSVGLength* heightLength = psvgElement->m_height->m_animated->m_animVal->m_value;

		m_computedLeft = LengthToUserUnits(xLength, viewPort.Width);
		m_computedTop = LengthToUserUnits(yLength, viewPort.Height);
	//	m_computedWidth = LengthToUserUnits(widthLength, viewPort.Width);
	//	m_computedHeight = LengthToUserUnits(heightLength, viewPort.Height);

#if 0
		m_dlgSite = (CUIDlgSite*)GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"page", FALSE);
#endif

		m_pTitlebarElement = (CPElement*)GetElementByTagNameNS(L"http://www.lerstad.com/2004/lxui", L"TitleBar"/*, FALSE ???*/);
#endif
	//	GetClipPathElement();

	//	m_childChanged--;
	}
}

void CUIFloatingFrame::UpdateWindowSize()
{
#if 0
	CRect rect(m_computedLeft, m_computedTop, m_computedLeft+100/*+m_computedWidth*/, m_computedTop+100/*+m_computedHeight*/);

//	CUIMDIFrame* pFrame = (CUIMDIFrame*)m_parent;

	//CPoint point(40, 40);	// TODO
	DWORD dwStyle = CBRS_SIZE_DYNAMIC;	// TODO

	m_dwStyle = dwStyle;

	if (m_hWnd == NULL)
	{
#if 0
		Create(m_hWndParent,//pFrame->m_hWnd,
			rect, NULL,
			WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN,
			WS_EX_TOOLWINDOW, 0);

#if 0
		if (m_dlgSite)
		{
			m_dlgSite->m_pDockSite = pFrame;
			CreateControlBar(NULL);
		}
#endif
#endif
	}
	else
		RecalcLayout();
#endif
}
#endif

/*
// CPLXUIElementImpl
// virtual
void CUIFloatingFrame::Show()
{
#if 0
	UpdateWindowSize();	// hmm
//	MessageBeep(-1);
#endif
}
*/

#if 0
// CPElement

// _AfxDrawFrame: [static]
// Draws a frame in a given brush, with a given width for the lines.
// Works like the doors to a cabinet: two tall stiles up and down the sides
// and two short spacers across the top and bottom.  The thickness of the
// lines are painted inside the rectangle.
//
void _AfxDrawFrame(CDC* dc, LPCRECT lpRect, int nWidth, int nHeight, CBrush& br)
{
	CRect rect;

	// left stile
	rect = *lpRect;
	rect.right = rect.left + nWidth;
	dc->FillRect(rect, br);

	// right stile
	rect.right = lpRect->right;
	rect.left = rect.right - nWidth;
	dc->FillRect(rect, br);

	// top spacer
	rect = *lpRect;
	rect.bottom = rect.top + nHeight;
	rect.left += nWidth;
	rect.right -= nWidth;
	dc->FillRect(rect, br);

	// bottom spacer
	rect.bottom = lpRect->bottom;
	rect.top = rect.bottom - nHeight;
	dc->FillRect(rect, br);
}

LRESULT CUIFloatingFrame::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL fCalcValidRects = (BOOL)wParam;        // valid area flag 

	LPRECT lpncsp = (LPRECT)lParam;               // new window coordinates 

	lpncsp->left += 7;
	lpncsp->top += 20;
	lpncsp->right -= 7;
	lpncsp->bottom -= 7;

	if (fCalcValidRects)
	{
		return WVR_REDRAW;
	}
	else
	{
		return 0;
	}
}

LRESULT CUIFloatingFrame::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	HDC hDC = GetDCEx((wParam == 1)? NULL: (HRGN)wParam, DCX_WINDOW|DCX_INTERSECTRGN);
	//CWindowDC dc(m_hWnd);
	CWindowDC dc(m_hWnd);

	//Gdiplus::TextureBrush brush(m_pBackgroundBitmap);

	{
		CRect rect;
		::GetWindowRect(m_hWnd, &rect);
		rect.OffsetRect(-rect.left, -rect.top);

		dc.ExcludeClipRect(7, 20, rect.Width()-7, rect.Height()-7);

#if 0
		xThemeDrawBackground(dc, &rect);
		xThemeDrawEdge(dc, &rect, xTheme_EDGE_RECT, 0);
#endif
	}


#if 0
	{
		if (_afx_hfontMiniSys == NULL)
		{
			LOGFONT logFont; memset(&logFont, 0, sizeof(LOGFONT));
			logFont.lfHeight = -(_afx_sizeMiniSys.cy-1);
			logFont.lfCharSet = DEFAULT_CHARSET;
			logFont.lfWeight = FW_NORMAL;
			if (GetSystemMetrics(SM_DBCSENABLED))
				lstrcpy(logFont.lfFaceName, _T("Terminal"));
			else
				lstrcpy(logFont.lfFaceName, _T("Small Fonts"));
			//if (!AfxCustomLogFont(AFX_IDS_MINI_FONT, &logFont))
			//	logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
			logFont.lfHeight = 11;	// TODO ???
			_afx_hfontMiniSys = ::CreateFontIndirect(&logFont);
		}

		if (_afx_hfontMiniSys != NULL)
		{
			CClientDC dc(NULL);
			TEXTMETRIC tm;
			HFONT hFontOld = (HFONT)dc.SelectFont(_afx_hfontMiniSys);
			BOOL bResult = dc.GetTextMetrics(&tm);
			dc.SelectFont(hFontOld);

			/*
			if (!bResult || tm.tmHeight - tm.tmInternalLeading > _afx_sizeMiniSys.cy)
				AfxDeleteObject((HGDIOBJ*)&_afx_hfontMiniSys);
				*/
		}

		_afx_sizeMiniSys.cy = 16;
	}

	BOOL m_bActive = TRUE;

	CRect rect, rectCaption;
	LONG dwStyle = GetStyle();
	GetWindowRect(&rect);
	rect.OffsetRect(-rect.left, -rect.top);

	// Create brushes we might need.
	CBrush brFrame;
	brFrame.CreateSolidBrush(::GetSysColor(COLOR_WINDOWFRAME));
	CBrush brBorder;
	brBorder.CreateSolidBrush(::GetSysColor(m_bActive ?
		COLOR_ACTIVEBORDER : COLOR_INACTIVEBORDER));
	/*
	CBrush brCaption;
	brCaption.CreateSolidBrush(::GetSysColor(m_bActive ?
		COLOR_ACTIVECAPTION : COLOR_INACTIVECAPTION));
		*/

	CSize sizeBorder(GetSystemMetrics(SM_CXBORDER), GetSystemMetrics(SM_CYBORDER));
	CSize sizeFrame(GetSystemMetrics(SM_CXFRAME), GetSystemMetrics(SM_CYFRAME));

	// Draw the thickframe.  Remove it from the rect.
	if (dwStyle & (/*MFS_4THICKFRAME |*/ WS_THICKFRAME/* | MFS_THICKFRAME*/))
	{
		_AfxDrawFrame(&dc, rect, sizeBorder.cx, sizeBorder.cy, brFrame);
		rect.InflateRect(-sizeBorder.cx, -sizeBorder.cy);
		_AfxDrawFrame(&dc, rect, sizeFrame.cx - sizeBorder.cx,
			sizeFrame.cy - sizeBorder.cy, brBorder);

		CSize sizeTick(sizeFrame.cx - sizeBorder.cx * 2,
			sizeFrame.cy - sizeBorder.cy * 2);

#if 0
		if (TRUE)//!(dwStyle & MFS_4THICKFRAME))
		{
			CSize sizeOffset(sizeFrame.cx + _afx_sizeMiniSys.cx - sizeBorder.cx * 3,
				sizeFrame.cy + _afx_sizeMiniSys.cy - sizeBorder.cy * 2);

			dc.FillSolidRect(rect.left, rect.top + sizeOffset.cy,
				sizeTick.cx, 1, RGB(0, 0, 0));
			dc.FillSolidRect(rect.left, rect.bottom - sizeOffset.cy,
				sizeTick.cx, 1, RGB(0, 0, 0));
			dc.FillSolidRect(rect.right - sizeTick.cx,
				rect.top + sizeOffset.cy, sizeTick.cx, 1, RGB(0, 0, 0));
			dc.FillSolidRect(rect.right - sizeTick.cx,
				rect.bottom - sizeOffset.cy, sizeTick.cx, 1, RGB(0, 0, 0));

			dc.FillSolidRect(rect.left + sizeOffset.cx, rect.top,
				1, sizeTick.cy, RGB(0, 0, 0));
			dc.FillSolidRect(rect.right - sizeOffset.cx, rect.top,
				1, sizeTick.cy, RGB(0, 0, 0));
			dc.FillSolidRect(rect.left + sizeOffset.cx,
				rect.bottom - sizeTick.cy, 1, sizeTick.cy, RGB(0, 0, 0));
			dc.FillSolidRect(rect.right - sizeOffset.cx,
				rect.bottom - sizeTick.cy, 1, sizeTick.cy, RGB(0, 0, 0));
		}
#endif

		rect.InflateRect(-sizeTick.cx, -sizeTick.cy);
	}

	// Draw the caption.  Remove it from rect.
	if (dwStyle & WS_CAPTION)
	{
		rectCaption = rect;
		rectCaption.bottom = rectCaption.top + _afx_sizeMiniSys.cy + sizeBorder.cy;

		_AfxDrawFrame(&dc, rectCaption, sizeBorder.cx, sizeBorder.cy, brFrame);
		rectCaption.InflateRect(-sizeBorder.cx, -sizeBorder.cy);

		//dc.FillRect(&rectCaption, brCaption);
		{
			COLORREF c1 = GetSysColor(COLOR_ACTIVECAPTION);
			COLORREF c2 = GetSysColor(COLOR_GRADIENTACTIVECAPTION);

			/*
			CRgn rgn;
			rgn.CreateRoundRectRgn(0, y, client.right, y+16, 2, 2);
			dc.SelectClipRgn(rgn, RGN_COPY);
			*/

			TRIVERTEX v[2];

			v[0].x = rectCaption.left;
			v[0].y = rectCaption.top;
			v[0].Red = GetRValue(c1)*255;
			v[0].Green = GetGValue(c1)*255;
			v[0].Blue = GetBValue(c1)*255;
			v[0].Alpha = 255*255;

			v[1].x = rectCaption.right;
			v[1].y = rectCaption.bottom;
			v[1].Red = GetRValue(c2)*255;
			v[1].Green = GetGValue(c2)*255;
			v[1].Blue = GetBValue(c2)*255;
			v[1].Alpha = 255*255;

			GRADIENT_RECT gr = {0, 1};
			dc.GradientFill(v, 2, &gr, 1, GRADIENT_FILL_RECT_H);
		}

		// Draw the border around the client area.
		// At this point, rc==rcClient.InflateRect(cxBorder, cyBorder).
		//
		_AfxDrawFrame(&dc, rect, sizeBorder.cx, sizeBorder.cy, brFrame);

		if (_afx_hfontMiniSys != NULL)
		{
			HFONT hFontOld = (HFONT)dc.SelectFont(_afx_hfontMiniSys);

			CString strTitle;
			GetWindowText(strTitle.GetBuffer(256), 256);
			strTitle.ReleaseBuffer();

			int xLeft = rectCaption.left +
				(dwStyle & WS_SYSMENU ? _afx_sizeMiniSys.cx : 0);

			CSize sizeText;
			dc.GetTextExtent(strTitle, strTitle.GetLength(), &sizeText);
			/*
			if (sizeText.cx <= rectCaption.Width())
			{
				dc.SetTextAlign(TA_CENTER);
				xLeft += (rectCaption.right - xLeft) / 2;
			}
			*/

			TEXTMETRIC tm;
			dc.GetTextMetrics(&tm);
			int yHeight = tm.tmAscent + tm.tmDescent + tm.tmInternalLeading;
			rectCaption.InflateRect(0, 1);
			int yHeightDiff = (rectCaption.Height() - yHeight + 1) / 2;

			dc.SetTextColor(::GetSysColor(m_bActive ?
				COLOR_CAPTIONTEXT : COLOR_INACTIVECAPTIONTEXT));
			dc.SetBkMode(TRANSPARENT);
			dc.ExtTextOut(xLeft, rectCaption.top + yHeightDiff, ETO_CLIPPED,
				rectCaption, strTitle, strTitle.GetLength(), NULL);

			dc.SelectFont(hFontOld);
		}

		if (TRUE)
		{
			//CRect rectCaption = rect;
			//rectCaption.bottom = rectCaption.top + _afx_sizeMiniSys.cy + sizeBorder.cy;

			//rectCaption.InflateRect(-sizeBorder.cx, -sizeBorder.cy);

			CRect client = rectCaption;

			m_btn[0] = CRect(client.right-14, client.top+2, 12, 12);
			m_btn[0].right += m_btn[0].left;
			m_btn[0].bottom += m_btn[0].top;

			m_btn[1] = CRect(client.right-26, client.top+2, 12, 12);
			m_btn[1].right += m_btn[1].left;
			m_btn[1].bottom += m_btn[1].top;

			for (int n = 0; n < 2; n++)
			{
				CRect rc = m_btn[n];

				/*
				if (m_activeIndex == i && m_dragging == n+1 && m_bInside)
				{
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
					rc.InflateRect(-1,-1);
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DLIGHT));
					rc.InflateRect(-1,-1);
				}
				else
				*/
				{
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
					rc.InflateRect(-1,-1);
					dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
					rc.InflateRect(-1,-1);
				}

				dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
			}

			// Close
			{
				CRect rc = m_btn[0];
				//if (m_activeIndex == i && m_dragging == 1 && m_bInside)
				//	rc.OffsetRect(1, 1);

				int midx = rc.left+1 + (rc.Width()-3)/2;
				int midy = rc.top+1 + (rc.Height()-3)/2;

				dc.MoveTo(midx-2, midy-2);
				dc.LineTo(midx+2+1, midy+2+1);
				dc.MoveTo(midx-2+1, midy-2);
				dc.LineTo(midx+2+1+1, midy+2+1);

				dc.MoveTo(midx-2, midy+2);
				dc.LineTo(midx+2+1, midy-2-1);
				dc.MoveTo(midx-2+1, midy+2);
				dc.LineTo(midx+2+1+1, midy-2-1);
			}

			// Minimize/Restore
			{
				CRect rc = m_btn[1];
				//if (m_activeIndex == i && m_dragging == 2 && m_bInside)
				//	rc.OffsetRect(1, 1);

				if (TRUE/*pPage->m_expanded*/)
				{
					dc.MoveTo(rc.left+1, rc.top+2);
					dc.LineTo(rc.right-3, rc.top+2);

					dc.MoveTo(rc.left+1, rc.top+3);
					dc.LineTo(rc.right-3, rc.top+3);
				}
				else
				{
					dc.MoveTo(rc.left+2, rc.top+2);
					dc.LineTo(rc.right-3, rc.top+2);

					dc.MoveTo(rc.left+2, rc.top+3);
					dc.LineTo(rc.right-3, rc.top+3);

					dc.MoveTo(rc.left+2, rc.top+2);
					dc.LineTo(rc.left+2, rc.bottom-4);
					dc.LineTo(rc.right-4, rc.bottom-4);
					dc.LineTo(rc.right-4, rc.top+2);
				}
			}
		}
		/*
		// Draw the system menu.
		if (dwStyle & WS_SYSMENU)
		{
			CDC dcBitmap;
			HBITMAP hBitmapOld;
			if (!dcBitmap.CreateCompatibleDC(&dc))
				return;
			hBitmapOld = (HBITMAP)dcBitmap.SelectObject(_afx_hbmMiniSys);
			dc.BitBlt(rect.left, rect.top, _afx_sizeMiniSys.cx, _afx_sizeMiniSys.cy,
				&dcBitmap, 0, 0, SRCCOPY);
			dcBitmap.SelectObject(hBitmapOld);
		}
		*/

		rect.top = rectCaption.bottom;
	}
	else
	{
		// Draw the border around the client area.
		// At this point, rect == rcClient.InflateRect(cxBorder, cyBorder).
		_AfxDrawFrame(&dc, rect, sizeBorder.cx, sizeBorder.cy, brFrame);
	}
#endif

	return 0;
}

LRESULT CUIFloatingFrame::OnNcCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	if (!CFrameWnd::OnNcCreate(lpcs))
		return FALSE;
		*/

#if 0
	if (TRUE)//GetStyle() & MFS_SYNCACTIVE)
	{
		// syncronize activation state with top level parent
		HWND pParentWnd = GetTopLevelParent();
		ASSERT(pParentWnd != NULL);
		HWND pActiveWnd = GetForegroundWindow();
		BOOL bActive = (pParentWnd == pActiveWnd) ||
			(pParentWnd->GetLastActivePopup() == pActiveWnd &&
			 pActiveWnd->SendMessage(WM_FLOATSTATUS, FS_SYNCACTIVE) != 0);

		// the WM_FLOATSTATUS does the actual work
		SendMessage(WM_FLOATSTATUS, bActive ? FS_ACTIVATE : FS_DEACTIVATE);
	}
#endif

	return TRUE;
}

LRESULT CUIFloatingFrame::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bActive = (BOOL)wParam;

#if 0
	if (m_dlgSite)
	{
		CComPtr<IUIDlg> dlg;
		m_dlgSite->GetDlg(&dlg);
		if (dlg)	// TODO ???
		{
			dlg->OnFrameActivate(bActive);
		}
	}
#endif

	return DefWindowProc(uMsg, wParam, lParam);

	/*
	if ((GetStyle() & MFS_SYNCACTIVE) == 0)
	{
		if (afxData.bSmCaption)
			return Default();

		if (m_bActive != bActive)
		{
			m_bActive = bActive;
			SendMessage(WM_NCPAINT);
		}
	}
	else if (m_nFlags & WF_KEEPMINIACTIVE)
	*/
	{
		return FALSE;
	}
	return TRUE;
}

LRESULT CUIFloatingFrame::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	int fActive = LOWORD(wParam);           // activation flag 
	if (m_dlgSite)
	{
		CComPtr<IUIDlg> dlg;
		m_dlgSite->GetDlg(&dlg);
		dlg->OnFrameActivate(fActive);
	}
#endif

	return 0;
}

LRESULT CUIFloatingFrame::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	UINT nHit = DefWindowProc(uMsg, wParam, lParam);

	if (nHit == HTCLOSE)
		return HTCAPTION;
	else
		return nHit;

	return 0;
}

LRESULT CUIFloatingFrame::OnNcLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	int nHitTest = (INT)wParam;    // hit-test value 

	CDragContext context;
	context.m_pBar = m_dlgSite;

	if (nHitTest == HTCAPTION)
	{
		// special activation for floating toolbars
		ActivateTopParent();

		//SetActiveWindow();
		context.StartDrag(point);
		return 0;
	}
	else if (nHitTest >= HTSIZEFIRST && nHitTest <= HTSIZELAST)
	{
		// special activation for floating toolbars
		ActivateTopParent();

		/*
		// special activation for floating toolbars
		ActivateTopParent();

		int nPos = 1;
		CControlBar* pBar = NULL;
		while(pBar == NULL && nPos < m_wndDockBar.m_arrBars.GetSize())
			pBar = m_wndDockBar.GetDockedControlBar(nPos++);

		ASSERT(pBar != NULL);
		ASSERT_KINDOF(CControlBar, pBar);
		ASSERT(pBar->m_pDockContext != NULL);

		// CBRS_SIZE_DYNAMIC toolbars cannot have the CBRS_FLOAT_MULTI style
		ASSERT((m_wndDockBar.m_dwStyle & CBRS_FLOAT_MULTI) == 0);
		*/
		context.StartResize(nHitTest, point);
		return 0;
	}
	else
#endif
	{
		return DefWindowProc(uMsg, wParam, lParam);
	}
}
#endif

#if 0
void CUIFloatingFrame::CreateControlBar(RECT* lpRect)
{
	ATLASSERT(m_dlgSite);

	//m_dlgSite->AddRef();
	HWND hwnd = NULL;
	ATLASSERT(0);
	//m_dlgSite->get_hwnd(&hwnd);
	if (hwnd)
	{
		::SetParent(hwnd, m_hWnd);
	}
	else
	{
		ATLASSERT(0);
		//m_dlgSite->Create(m_hWnd);
	}

	DWORD dwStyle = m_dlgSite->GetBarStyle();
	dwStyle &= ~(CBRS_ALIGN_ANY);
	dwStyle |=  (m_dwStyle & CBRS_ALIGN_ANY) | CBRS_BORDER_ANY;

	//if (m_bFloating)
		dwStyle |= CBRS_FLOATING;
		/*
	else
		dwStyle &= ~CBRS_FLOATING;
		*/

	m_dlgSite->SetBarStyle(dwStyle);

// Remove bar from any previous dockbar
	if (m_dlgSite->m_pDockBar)
	{
		ATLASSERT(0);
#if 0	// Had this
		m_dlgSite->m_pDockBar->RemoveControlBar(m_dlgSite);
#endif
	}

	CComBSTR name;
	m_dlgSite->GetName(&name);
	SetWindowText(_bstr_t(name));

	m_dlgSite->m_pDockBar = this;
	RecalcLayout();
}
#endif

#if 0
STDMETHODIMP CUIFloatingFrame::DockControlBar(IUIDlgSite* pBar, RECT* lpRect)
{
	ATLASSERT(0);
//	CDlgSheet* pBar = static_cast<CDlgSheet*>(pBarI);

#if 0
	ATLASSERT(m_dlgSite == NULL);	// Only one bar allowed in us

//	pBar->m_pDockSite = m_pDockSite;

	m_dlgSite = (CUIDlgSite*)pBar;

	CreateControlBar(lpRect);
#endif

	return S_OK;
}

STDMETHODIMP CUIFloatingFrame::RemoveControlBar(IUIDlgSite* pBar)
{
	ATLASSERT(0);

#if 0
// There's only one controlbar
	ATLASSERT(pBar == m_dlgSite);

	pBar->m_pDockBar = NULL;

	m_dlgSite = NULL;

	PostMessage(WM_CLOSE);
//	DestroyWindow();	// Destroy us as well as the controlbar window
// OnFinalMessage() of m_pSheet should call Release()

//	pBarI->Release();
#endif

	return S_OK;
}

void CUIFloatingFrame::RemovedFromDocument()
{
	CPElement::RemovedFromDocument();
	if (m_hWnd)
	{
		ShowWindow(SW_HIDE);
	}
}

STDMETHODIMP CUIFloatingFrame::RecalcLayout()
{
#if 0
	if (m_dlgSite)
	{
		HWND hwnd = NULL;
		ATLASSERT(0);
		//m_dlgSite->get_hwnd(&hwnd);

		if (m_dlgSite->IsVisible() == S_OK/*::GetWindowLong(hwnd, GWL_STYLE) & WS_VISIBLE*/)
		{
			CSize size;
			size = m_dlgSite->CalcDynamicLayout(0/*-1*/, LM_MRUWIDTH | LM_HORZ);

			CRect rect(0, 0, size.cx, size.cy);
			CalcBorders(&rect);

			SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
		}
		else
		{
			ShowWindow(SW_HIDE);
		}
	}
	/*
	else
	{
		SetWindowPos(NULL, 0, 0, 20, 20, SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}
	*/
#endif

	return S_OK;
}
#endif

}	// UI
}
