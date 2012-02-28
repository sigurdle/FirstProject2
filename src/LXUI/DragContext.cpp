#include "stdafx.h"
#include "LXUI2.h"

#include "LXUIBoxWindow.h"
#include "UIElement.h"

#include "DragContext.h"

//#include "UIFloatingFrame.h"
#include "SizeBox.h"

//#include "UIFrameImpl.h"

#include "UIDockBar.h"	// TODO remove

#include "ToolBar.h"

#if AMIGA
#include "../amiga_header.h"
#endif

#if WIN32
#include "../include/windows_header.h"
#endif

namespace System
{
using namespace MSWindows;

namespace UI
{

extern UIEXT __live_object_ptr<LayoutManager> pLayoutManager;

DependencyProperty* CDragContext::MRUWidthProperty = RegisterAttached(WSTR("MRUWidth"), typeid(int), typeid(CDragContext), IntObject::GetObject(32767));

int GetMRUWidth(DependencyObject* p)
{
	return dynamic_cast<IntObject*>(p->GetValue(CDragContext::MRUWidthProperty))->GetValue();
}

void SetMRUWidth(DependencyObject* p, int value)
{
	p->SetValue(CDragContext::MRUWidthProperty, IntObject::GetObject(value));
}

//UIElement* RecalculateParent(UIElement* pThis);

void GetClientWindowRect(PlatformWindow platformWnd, LDraw::RectI* lpRect)
{
//	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
//	DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);

//	CRect rc(0,0,0,0);
//	::AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);

#if WIN32

	MSWindows::RECT wrect;
	MSWindows::GetWindowRect(platformWnd, &wrect);
	lpRect->X = wrect.left;
	lpRect->Y = wrect.top;
	lpRect->Width = wrect.right - wrect.left;
	lpRect->Height = wrect.bottom - wrect.top;

#elif AMIGA

	lpRect->X = platformWnd->LeftEdge;
	lpRect->Y = platformWnd->TopEdge;
	lpRect->Width = platformWnd->Width;
	lpRect->Height = platformWnd->Height;

#endif

	lpRect->Inflate(0, -16, 0, -16);
}

void CalcBorders(LDraw::RectI* lpClientRect/*, DWORD dwStyle = WS_THICKFRAME | WS_CAPTION, DWORD dwExStyle = 0*/)
{
	lpClientRect->Y -= 16;
	lpClientRect->Height += 16+16;

	;//AdjustWindowRectEx(lpClientRect, dwStyle, FALSE, WS_EX_PALETTEWINDOW);
}

void _AdjustRectangle(LDraw::RectI& rect, LDraw::PointI pt)
{
	int nXOffset = (pt.X < rect.GetLeft()) ? (pt.X - rect.GetLeft()) :
					(pt.X > rect.GetRight()) ? (pt.X - rect.GetRight()) : 0;
	int nYOffset = (pt.Y < rect.GetTop()) ? (pt.Y - rect.GetTop()) :
					(pt.Y > rect.GetBottom()) ? (pt.Y - rect.GetBottom()) : 0;
	rect.Translate(nXOffset, nYOffset);
}

#if 0
void GetDockSites(UIElement* p, std::vector<IDockSite*>& list)
{
	for (int i = 0; i < p->m_rchildList.size(); i++)
	{
		GetDockSites(m_rchildList[i], list);

		IDockSite* dockSite = dynamic_cast<IDockSite*>(m_rchildList[i]);

		if (dockSite)
		{
			list.push_back(dockSite);
		}
	}
}
#endif

void GetIntersectionList(Visual* p, LDraw::Matrix3f* matrix, const LDraw::RectF& rect, vector<UIElement*>& arr)
{
	ASSERT(0);
#if 0
	matrix = *p->GetParentToElementTransformMatrix() * *matrix;

	LDraw::PointF pt(rect.X, rect.Y);
	LDraw::PointF xpt = matrix->GetInverse()->Transform(pt);

	LDraw::RectF xrect(xpt.X, xpt.Y, rect.Width, rect.Height);

	if (xrect.IntersectsWith(p->m_expandedBBox))
	{
		Visual* pVisual = p->get_VisualTree();

		if (pVisual)
		{
			GetIntersectionList(pVisual, matrix, rect, arr);
		}
		else
		{
			Visual* pParent = p;
			for (int i = 0; i < pParent->get_rchildList()->get_Size(); i++)
			{
				GetIntersectionList((*pParent->get_rchildList())[i], matrix, rect, arr);
			}
		}

		arr.Add(p);
	}
#endif
}

VisualContentSource* GetTopLevelWindow(UIElement* pVisual)
{
	return pVisual->GetOwnerWindow();
	ASSERT(0);
#if 0
	VisualContentSource* p = pVisual->get_OwnerWindow();
	while (p)
	{
		VisualContentSource* p2 = p->get_OwnerWindow();
		if (p2 == NULL)
			return dynamic_cast<VisualContentSource*>(p);
		p = p2;
	}
	ASSERT(0);
#endif
	return NULL;
}

#if 0
Control* /*IUIDockBar*/ CDragContext::GetDockBar(DWORD dwOverDockStyle)
{
	/*
	{
		CLXUIVisualContentSource* pWindow;
		
		HWND hWnd = WindowFromPoint(m_pt);
		while (hWnd)
		{
			pWindow = (CLXUIVisualContentSource*)GetProp(hWnd, "lxui_window");
			if (pWindow)
			{
				break;
			}

			hWnd = GetParent(hWnd);
		}

		if (pWindow)
		{
			Control* pDock = NULL;

			if (pDock)
			{
				return pDock;
			}
		}
	}
	*/


	std::vector<UIElement*> list;
	GetIntersectionList(GetTopLevelWindow(m_pBar)/*->get_OwnerWindow()*/->m_VisualTree, LDraw::Matrix().Identity(), LDraw::RectF(m_rectDragHorz.X, m_rectDragHorz.Y, m_rectDragHorz.Width, m_rectDragHorz.Height), list);

	if (list.size() > 0)
	{
	}

#if 0
	DWORD dw = 0;
	CComPtr<IUIDockBar> pBar;
	if (HORZF(dwOverDockStyle))
	{

		m_pBar->m_pDockSite->CanDock(m_rectDragHorz, dwOverDockStyle & ~CBRS_ORIENT_VERT, &pBar, &dw);
		ASSERT(dw != 0);
		ASSERT(pBar != NULL);
		return pBar;
	}
	if (VERTF(dwOverDockStyle))
	{
		m_pBar->m_pDockSite->CanDock(m_rectDragVert, dwOverDockStyle & ~CBRS_ORIENT_HORZ, &pBar, &dw);
		ASSERT(dw != 0);
		ASSERT(pBar != NULL);
		return pBar;
	}
#endif
	return NULL;
}
#endif

CDragContext::CDragContext()
{
	m_dwOverDockStyle = 0;
	m_bFlip = false;
	m_bRealTime = true;

	m_pDockSite = NULL;
#if WIN32
	m_pDC = NULL;
#endif
}

uint CDragContext::CanDock(IDockSite* *ppDockBar)
{
//	ASSERT(0);
//	return 0;
#if 1
	// Find the toplevel window
	VisualContentSource* pOwnerWindow = GetTopLevelWindow(m_pBar);
	/*
	CLXUIVisualContentSource* pOwnerWindow = m_pBar->get_OwnerWindow();
	while (pOwnerWindow->get_OwnerWindow())
	{
		pOwnerWindow = pOwnerWindow->get_OwnerWindow();
	}
	*/

#if WIN32
	MSWindows::RECT wrect;
	MSWindows::GetWindowRect(dynamic_cast<HwndSource*>(pOwnerWindow->m_pSite)->GetHwnd(), &wrect);
	__release<LDraw::Matrix3f> transform = LDraw::Matrix3f::GetTranslate(wrect.left, wrect.top);
#elif AMIGA
	HwndSource* pFrame = dynamic_cast<HwndSource*>(pOwnerWindow->m_pSite);
	__release<LDraw::Matrix3f> transform = LDraw::Matrix3f::GetTranslate(pFrame->GetHwnd()->LeftEdge, pFrame->GetHwnd()->TopEdge);
#endif

	vector<UIElement*> list;
	GetIntersectionList(pOwnerWindow->GetVisualTree(), transform, LDraw::RectF(m_rectDragHorz.X, m_rectDragHorz.Y, m_rectDragHorz.Width, m_rectDragHorz.Height), list);

	if (list.GetSize() > 0)
	{
		for (int i = 0; i < list.GetSize(); i++)
		{
			if (dynamic_cast<IDockSite*>(list[i]))
			{
				*ppDockBar = dynamic_cast<IDockSite*>(list[i]);
				return CBRS_ORIENT_HORZ;
			}
		}
	}

	*ppDockBar = dynamic_cast<IDockSite*>(pOwnerWindow);
	if (*ppDockBar)
		return CBRS_ORIENT_HORZ;
	else
		return 0;

#endif

#if 0
	BOOL bStyleHorz;
	DWORD dwDock = 0; // Dock Candidate
	DWORD dwCurr = 0; // Current Orientation

// First check
	{
		IUIDockBar* pDock = NULL;

		HWND hWnd = WindowFromPoint(m_ptLast);
		while (hWnd)
		{
			pDock = (IUIDockBar*)GetProp(hWnd, "mmsx_sheet");
			if (pDock)
			{
				if (pDock->CanDock(m_pBar) == S_OK)
					break;
			}

			hWnd = GetParent(hWnd);
		}

		if (pDock)
		{
			MessageBeep(-1);
			*ppDockBar = pDock;
			return m_pBar->GetBarStyle();	// ???
		}
	}

	// let's check for something in our current orientation first
	// then if the shift key is not forcing our orientation then
	// check for horizontal or vertical orientations as long
	// as we are close enough
	ASSERT(m_pBar->GetBarStyle() != 0);

//		ASSERT(::IsWindow(m_pDockSite->m_hWnd));

	bStyleHorz = HORZF(m_pBar->GetBarStyle());
	bStyleHorz = m_bFlip ? !bStyleHorz : bStyleHorz;

	if (bStyleHorz && HORZF(m_pBar->m_dwDockStyle))
		m_pBar->m_pDockSite->CanDock(m_rectDragHorz, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_VERT, ppDockBar, &dwDock);
	else if (VERTF(m_pBar->m_dwDockStyle))
		m_pBar->m_pDockSite->CanDock(m_rectDragVert, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_HORZ, ppDockBar, &dwDock);

	if (!m_bFlip)
	{
		if (dwDock == 0 && HORZF(m_pBar->m_dwDockStyle))
		{
			m_pBar->m_pDockSite->CanDock(m_rectDragVert, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_VERT, ppDockBar, &dwCurr);
			m_pBar->m_pDockSite->CanDock(m_rectDragHorz, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_VERT, ppDockBar, &dwDock);
			dwDock = (dwDock == dwCurr) ? dwDock : 0;
		}
		if (dwDock == 0 && VERTF(m_pBar->m_dwDockStyle))
		{
			m_pBar->m_pDockSite->CanDock(m_rectDragHorz, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_HORZ, ppDockBar, &dwCurr);
			m_pBar->m_pDockSite->CanDock(m_rectDragVert, m_pBar->m_dwDockStyle & ~CBRS_ORIENT_HORZ, ppDockBar, &dwDock);
			dwDock = (dwDock == dwCurr) ? dwDock : 0;
		}
	}

	return dwDock;
#endif
}

//void DrawDragRect(HDC hdc, LPCRECT lpRect, SIZE size, LPCRECT lpRectLast, SIZE sizeLast, HBRUSH hBrush = NULL, HBRUSH hBrushLast = NULL);

#if _WINDOWS

HBRUSH GetHalftoneBrush()
{
	HBRUSH halftoneBrush = NULL;
	uint16 grayPattern[8];
	for(int i = 0; i < 8; i++)
		grayPattern[i] = (uint16)(0x5555 << (i & 1));
	HBITMAP grayBitmap = MSWindows::CreateBitmap(8, 8, 1, 1, &grayPattern);
	if(grayBitmap != NULL)
	{
		halftoneBrush = MSWindows::CreatePatternBrush(grayBitmap);
		MSWindows::DeleteObject((void*)grayBitmap);
	}
	return halftoneBrush;
}

void DrawDragRect(HDC hdc, const LDraw::RectI* lpRect, LDraw::Sizei size, const LDraw::RectI* lpRectLast, LDraw::Sizei sizeLast, HBRUSH hBrush, HBRUSH hBrushLast)
{
	// first, determine the update region and select it
	MSWindows::HRGN hRgnNew;
	MSWindows::HRGN hRgnOutside, hRgnInside;
	MSWindows::RECT _rect = { lpRect->X, lpRect->Y, lpRect->GetRight(), lpRect->GetBottom()};
	MSWindows::RECT rect = _rect;
	hRgnOutside = MSWindows::CreateRectRgnIndirect(&rect);
	MSWindows::InflateRect(&rect, -size.Width, -size.Height);
	MSWindows::IntersectRect(&rect, &rect, &_rect);
	hRgnInside = MSWindows::CreateRectRgnIndirect(&rect);
	hRgnNew = MSWindows::CreateRectRgn(0, 0, 0, 0);
	MSWindows::CombineRgn(hRgnNew, hRgnOutside, hRgnInside, RGN_XOR);

	MSWindows::HBRUSH hBrushOld = NULL;
	if(hBrush == NULL)
		hBrush = GetHalftoneBrush();
	if(hBrushLast == NULL)
		hBrushLast = hBrush;

	MSWindows::HRGN hRgnLast = NULL, hRgnUpdate = NULL;
	if(lpRectLast != NULL)
	{
		MSWindows::RECT rectLast = { lpRectLast->X, lpRectLast->Y, lpRectLast->GetRight(), lpRectLast->GetBottom()};

		// find difference between new region and old region
		hRgnLast = MSWindows::CreateRectRgn(0, 0, 0, 0);
		MSWindows::SetRectRgn(hRgnOutside, rectLast.left, rectLast.top, rectLast.right, rectLast.bottom);
		rect = rectLast;
		MSWindows::InflateRect(&rect, -sizeLast.Width, -sizeLast.Height);
		MSWindows::IntersectRect(&rect, &rect, &rectLast);
		MSWindows::SetRectRgn(hRgnInside, rect.left, rect.top, rect.right, rect.bottom);
		MSWindows::CombineRgn(hRgnLast, hRgnOutside, hRgnInside, RGN_XOR);

		// only diff them if brushes are the same
		if(hBrush == hBrushLast)
		{
			hRgnUpdate = MSWindows::CreateRectRgn(0, 0, 0, 0);
			MSWindows::CombineRgn(hRgnUpdate, hRgnLast, hRgnNew, RGN_XOR);
		}
	}
	if(hBrush != hBrushLast && lpRectLast != NULL)
	{
		// brushes are different -- erase old region first
		MSWindows::SelectClipRgn(hdc, hRgnLast);
		MSWindows::GetClipBox(hdc, &rect);
		hBrushOld = (MSWindows::HBRUSH)MSWindows::SelectObject(hdc, hBrushLast);
		MSWindows::PatBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);
		MSWindows::SelectObject(hdc, hBrushOld);
		hBrushOld = NULL;
	}

	// draw into the update/new region
	MSWindows::SelectClipRgn(hdc, hRgnUpdate != NULL ? hRgnUpdate : hRgnNew);
	MSWindows::GetClipBox(hdc, &rect);
	hBrushOld = (MSWindows::HBRUSH)MSWindows::SelectObject(hdc, hBrush);
	MSWindows::PatBlt(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, PATINVERT);

	// cleanup DC
	if(hBrushOld != NULL)
		MSWindows::SelectObject(hdc, hBrushOld);
	MSWindows::SelectClipRgn(hdc, NULL);
}

#elif AMIGA

void DrawDragRect(struct RastPort* rp, const LDraw::RectI* lpRect, LDraw::Sizei size, const LDraw::RectI* lpRectLast, LDraw::Sizei sizeLast)
{
	UBYTE drmd = GetDrMd(rp);
	SetDrMd(rp, COMPLEMENT);

	if (lpRectLast)
	{
		gfxMove(rp, lpRectLast->X, lpRectLast->Y);
		gfxDraw(rp, lpRectLast->GetRight(), lpRectLast->Y);
		gfxDraw(rp, lpRectLast->GetRight(), lpRectLast->GetBottom());
		gfxDraw(rp, lpRectLast->X, lpRectLast->GetBottom());
		gfxDraw(rp, lpRectLast->X, lpRectLast->Y);
	}
	gfxMove(rp, lpRect->X, lpRect->Y);
	gfxDraw(rp, lpRect->GetRight(), lpRect->Y);
	gfxDraw(rp, lpRect->GetRight(), lpRect->GetBottom());
	gfxDraw(rp, lpRect->X, lpRect->GetBottom());
	gfxDraw(rp, lpRect->X, lpRect->Y);

	SetDrMd(rp, drmd);
}

#endif

void CDragContext::DrawFocusRect(bool bRemoveRect/* = false*/)
{
	// default to thin frame
	LDraw::Sizei size(1/*CX_BORDER*/, 1/*CY_BORDER*/);

	// determine new rect and size
	LDraw::RectI rect;

#if WIN32
	ASSERT(m_pDC != NULL);
	MSWindows::HBRUSH pWhiteBrush = (MSWindows::HBRUSH)MSWindows::GetStockObject(WHITE_BRUSH);

	MSWindows::HBRUSH pBrush = pWhiteBrush;
#endif

//////////////////////////	// Disallow docking (for now)
	if (HORZF(m_dwOverDockStyle))
		rect = m_rectDragHorz;
#if 0
	else if (VERTF(m_dwOverDockStyle))
		rect = m_rectDragVert;
#endif
#if WIN32
	else
	{
		// use thick frame instead
		size.Width = MSWindows::GetSystemMetrics(SM_CXFRAME) - 1;//CX_BORDER;
		size.Height = MSWindows::GetSystemMetrics(SM_CYFRAME) - 1;//CY_BORDER;
		if (true/*(HORZF(m_pBar->GetBarStyle()) && !m_bFlip) || (VERTF(m_pBar->GetBarStyle()) && m_bFlip)*/)
			rect = m_rectFrameDragHorz;
		else
			rect = m_rectFrameDragVert;
		pBrush = m_pDitherBrush;
	}
#endif
	if (bRemoveRect)
		size.Width = size.Height = 0;

	/*
	if (afxData.bWin4 &&
		(HORZF(m_dwOverDockStyle) || VERTF(m_dwOverDockStyle)))
		*/
	{
		// looks better one pixel in (makes the bar look pushed down)
		//rect.Inflate(-1/*CX_BORDER*/, -1/*CY_BORDER*/);
	}

//	DrawDragRect(m_pDC, &rect, size, &m_rectLast, m_sizeLast, pBrush, m_bDitherLast ? m_pDitherBrush : pWhiteBrush);
	// draw it and remember last size
#if WIN32
	DrawDragRect(m_pDC, &rect, size, &m_rectLast, m_sizeLast, pBrush, m_bDitherLast ? m_pDitherBrush : pWhiteBrush);
#elif AMIGA
#if 0	// TODO
	DrawDragRect(&m_pBar->get_OwnerWindow()->GetHwnd()->WScreen->RastPort, &rect, size, &m_rectLast, m_sizeLast/*, pBrush, m_bDitherLast ? m_pDitherBrush : pWhiteBrush*/);
#endif
#endif
	m_rectLast = rect;
	m_sizeLast = size;
#if WIN32
	m_bDitherLast = (pBrush == m_pDitherBrush);

	MSWindows::DeleteObject(pWhiteBrush);
#endif
}

void CDragContext::InitLoop()
{
#if WIN32
	m_pDitherBrush = GetHalftoneBrush();
#endif

	// initialize state
	m_rectLast = LDraw::RectI(0,0,0,0);
	m_sizeLast.Width = m_sizeLast.Height = 0;
	/*m_bForceFrame = m_bFlip =*/ m_bDitherLast = false;

#if WIN32

	ASSERT(m_pDC == NULL);

	if (!m_bRealTime)
	{
		HWND hWnd = MSWindows::GetDesktopWindow();
		if (true)
		{
			if (MSWindows::LockWindowUpdate(hWnd))
				m_pDC = MSWindows::GetDCEx(hWnd, NULL, DCX_WINDOW|DCX_CACHE|DCX_LOCKWINDOWUPDATE);
			else
				m_pDC = MSWindows::GetDCEx(hWnd, NULL, DCX_WINDOW|DCX_CACHE);
		//	m_pDC = GetDC(hWnd);
		}
		else
		{
			m_pDC = MSWindows::GetDC(hWnd);
		}

		ASSERT(m_pDC != NULL);
	}

#endif
}

void CDragContext::StartDrag(LDraw::PointI pt)
{

	m_bDragging = true;

	PlatformWindow hwnd;
	VisualContentSource* pVisualContentSource = m_pBar->GetOwnerWindow();
	if (pVisualContentSource)
		hwnd = dynamic_cast<HwndSource*>(pVisualContentSource->m_pSite)->GetHwnd();
	else
		hwnd = dynamic_cast<HwndSource*>(m_pBar)->GetHwnd();

	LDraw::RectD bounds = m_pBar->GetWindowToElementBounds();
	bounds.Y -= 16;

	LDraw::RectI rect;
	GetClientWindowRect(hwnd, &rect);
	rect.X += bounds.X;
	rect.Y += bounds.Y;

	m_pBar->Measure(LDraw::SizeD(32767, 0));
	LDraw::Sizei sizeHorz = LDraw::Sizei(m_pBar->get_DesiredSize().Width, m_pBar->get_DesiredSize().Height);//m_pBar->CalcDynamicLayout(32767, LM_HORZ/* | LM_HORZDOCK*/);

	m_pBar->Measure(LDraw::SizeD(0, 0));
	LDraw::Sizei sizeVert = LDraw::Sizei(40,40);//m_pBar->CalcDynamicLayout(0, LM_VERTDOCK);

	int nMRUWidth = GetMRUWidth(m_pBar);
	m_pBar->Measure(LDraw::SizeD(nMRUWidth, 0));
	LDraw::Sizei sizeFloat = LDraw::Sizei(m_pBar->get_DesiredSize().Width, m_pBar->get_DesiredSize().Height);//m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH);

	m_rectDragHorz = LDraw::Recti(rect.GetTopLeft(), sizeHorz);
	m_rectDragHorz.Inflate((1+3+6), (3+1), 3+1, 3+1);
	m_rectDragVert = LDraw::Recti(rect.GetTopLeft(), sizeVert);
	m_rectDragVert.Inflate((1+3+6), (3+1), 3+1, 3+1);

	/*
	// calculate frame dragging rectangle
	m_rectFrameDragHorz = LDraw::RectI(rect.TopLeft(), sizeFloat);
	m_rectFrameDragHorz.Inflate(0, 0, 6, 16);
	m_rectFrameDragVert = LDraw::RectI(rect.TopLeft(), sizeFloat);

	CalcBorders(&m_rectFrameDragHorz);
	CalcBorders(&m_rectFrameDragVert);

	// adjust rectangles so that point is inside
	_AdjustRectangle(m_rectDragHorz, pt);
	_AdjustRectangle(m_rectDragVert, pt);
	_AdjustRectangle(m_rectFrameDragHorz, pt);
	_AdjustRectangle(m_rectFrameDragVert, pt);
	*/

	m_dwOverDockStyle = CanDock(&m_pDockSite);

	m_ptLast = pt;

	InitLoop();

	// GetWindowRect returns screen coordinates(not mirrored)
	// So if the desktop is mirrored then turn off mirroring
	// for the desktop dc so that we draw correct focus rect

	// if (GetLayout(m_pDC) & LAYOUT_RTL)
	//	SetLayout(m_pDC, 0/*LAYOUT_LTR*/);

//	SetCapture(hwnd);
//	m_dragging = 2;
	Track();
}

void CDragContext::StartResize(int nHitTest, LDraw::PointI pt)
{
	m_pDockSite = dynamic_cast<IDockSite*>(m_pBar->m_pDockParent);
/*
	ASSERT_VALID(m_pBar);
	ASSERT(m_pBar->m_dwStyle & CBRS_SIZE_DYNAMIC);
	*/
	m_bDragging = false;

	InitLoop();

	// GetWindowRect returns screen coordinates(not mirrored)
	// So if the desktop is mirrored then turn off mirroring
	// for the desktop dc so that we draw correct focus rect

	/*
	if (m_pDC->GetLayout() & LAYOUT_RTL)
		m_pDC->SetLayout(LAYOUT_LTR);
		*/

		// get true bar size (including borders)

	PlatformWindow hwnd;
	if (m_pBar->GetOwnerWindow())
		hwnd = dynamic_cast<HwndSource*>(m_pBar->GetOwnerWindow())->GetHwnd();
	else
		hwnd = dynamic_cast<HwndSource*>(m_pBar)->GetHwnd();

	LDraw::Recti rect;
	/*m_pBar->*/GetClientWindowRect(hwnd, &rect);
	m_ptLast = pt;
	m_nHitTest = nHitTest;

	int nMRUWidth = GetMRUWidth(m_pBar);
//	LDraw::Sizei size = m_pBar->CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH);
	m_pBar->Measure(LDraw::SizeD(nMRUWidth/*32767*/, 0));
	LDraw::Sizei size = LDraw::Sizei(m_pBar->get_DesiredSize().Width, m_pBar->get_DesiredSize().Height);//m_pBar->CalcDynamicLayout(32767, LM_HORZ/* | LM_HORZDOCK*/);

	m_rectRequestedSize = LDraw::Recti(rect.GetTopLeft(), size);
	m_rectActualSize = LDraw::Recti(rect.GetTopLeft(), size);
	m_rectActualFrameSize = LDraw::Recti(rect.GetTopLeft(), size);

	m_rectActualFrameSize.Inflate(0, 0, 6, 16);

//	m_rectDragHorz.Inflate((1+3+6), (3+1), 3+1, 3+1);

	/*
	if (m_bShowTabs)
	{
		m_rectActualFrameSize.bottom += 14;
		//m_rectFrameDragVert.bottom += 14;
	}
	*/

	// calculate frame rectangle
	CalcBorders(&m_rectActualFrameSize);
	//m_rectActualFrameSize.InflateRect(-afxData.cxBorder2, -afxData.cyBorder2);

	m_rectFrameBorders = LDraw::RectI(LDraw::PointI(0,0),
		m_rectActualFrameSize.GetSize() - m_rectActualSize.GetSize());

	// initialize tracking state and enter tracking loop
	m_dwOverDockStyle = 0;
	Stretch(pt);//CLXUIVisualContentSource// call it here to handle special keys
	Track();

//	SetCapture();
//	m_dragging = 3;
}

void CDragContext::Move(LDraw::PointI pt)
{
	if (pt != m_ptLast)
	{
		LDraw::PointI ptOffset = pt - m_ptLast;

		// offset all drag rects to new position
		m_rectDragHorz.Translate(ptOffset);
		m_rectFrameDragHorz.Translate(ptOffset);
		m_rectDragVert.Translate(ptOffset);
		m_rectFrameDragVert.Translate(ptOffset);
		m_ptLast = pt;

		m_dwOverDockStyle = CanDock(&m_pDockSite);

		if (!m_bRealTime)
		{
	#if WIN32
			m_pDockSite->DrawFocusRect(m_pDC, m_rectDragHorz, m_rectFrameDragHorz);
	#endif
		}
		else
		{
			PlaceDrag();
		}
	}
}

void CDragContext::Stretch(LDraw::PointI pt)
{
	if (pt != m_ptLast)
	{
		LDraw::PointI ptOffset = pt - m_ptLast;

		// offset all drag rects to new position
		int nLength = 0;
		DWORD dwMode = LM_HORZ;
		if (m_nHitTest == HTLEFT || m_nHitTest == HTRIGHT)
		{
			if (m_nHitTest == HTLEFT)
			{
				m_rectRequestedSize.X += ptOffset.Y;
				m_rectRequestedSize.Width -= ptOffset.X;
			}
			else
				m_rectRequestedSize.Width += ptOffset.X;

			nLength = m_rectRequestedSize.Width;
		}
		else
		{
			dwMode |= LM_LENGTHY;
			if (m_nHitTest == HTTOP)
			{
				m_rectRequestedSize.Y += ptOffset.Y;
				m_rectRequestedSize.Height -= ptOffset.Y;
			}
			else
				m_rectRequestedSize.Height += ptOffset.Y;

			nLength = m_rectRequestedSize.Height;
		}
		nLength = (nLength >= 0) ? nLength : 0;

		MessageBeep(-1);

	//	CSize size = m_pBar->CalcDynamicLayout(nLength, dwMode);
		m_pBar->Measure(LDraw::SizeD(nLength, 0));
		LDraw::Sizei size = LDraw::Sizei(m_pBar->get_DesiredSize().Width, m_pBar->get_DesiredSize().Height);//m_pBar->CalcDynamicLayout(32767, LM_HORZ/* | LM_HORZDOCK*/);

	#if WIN32
		MSWindows::HWND hWndDesk = MSWindows::GetDesktopWindow();
		MSWindows::RECT rc;
		MSWindows::GetWindowRect(hWndDesk, &rc);
		LDraw::RectI rectDesk(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
	#else
		// TODO
		LDraw::RectI rectDesk;
	#endif

		LDraw::RectI rectTemp = m_rectActualFrameSize;

		if (m_nHitTest == HTLEFT || m_nHitTest == HTTOP)
		{
			ASSERT(0);
	#if 0
			rectTemp.X = rectTemp.GetRight() - (size.Width + m_rectFrameBorders.Width);
			rectTemp.Y = rectTemp.GetBottom() - (size.Height + m_rectFrameBorders.Height);
			LDraw::RectI rect;
			if (LDraw::RectI::Intersect(rect, rectDesk, rectTemp))
			{
				m_rectActualSize.X = m_rectActualSize.GetRight() - size.Width;
				m_rectActualSize.Y = m_rectActualSize.GetBottom() - size.Height;
				m_rectActualFrameSize.X = rectTemp.X;
				m_rectActualFrameSize.Y = rectTemp.Y;
			}
	#endif
		}
		else
		{
			rectTemp.Width = /*rectTemp.left +*/ (size.Width + m_rectFrameBorders.Width);
			rectTemp.Height = /*rectTemp.top +*/ (size.Height + m_rectFrameBorders.Height);
			LDraw::RectI rect;
			if (LDraw::RectI::Intersect(rect, rectDesk, rectTemp))
			{
				m_rectActualSize.Width = /*m_rectActualSize.X +*/ size.Width;
				m_rectActualSize.Height = /*m_rectActualSize.Y +*/ size.Height;
				m_rectActualFrameSize.Width = rectTemp.GetRight() - m_rectActualFrameSize.X;
				m_rectActualFrameSize.Height = rectTemp.GetBottom() - m_rectActualFrameSize.Y;
			}
		}

		m_ptLast = pt;

		// update feedback
	//	DrawFocusRect();
	#if WIN32
		m_pDockSite->DrawFocusRect(m_pDC, m_rectDragHorz, m_rectFrameDragHorz);
	#endif
	}
}

void CDragContext::CancelLoop()
{
	if (m_bDragging < 2)
	{
		if (!m_bRealTime)
		{
			;//m_pDockSite->DrawFocusRect(hDC, m_rectDragHorz, m_rectFrameDragHorz);
			;//DrawFocusRect(TRUE/*bRemove*/);
		}
	}

#if WIN32
	MSWindows::ReleaseCapture();

	MSWindows::HWND hWndDesktop = MSWindows::GetDesktopWindow();
	MSWindows::LockWindowUpdate(NULL);
	if (m_pDC != NULL)
	{
		MSWindows::ReleaseDC(hWndDesktop, m_pDC/*.Detach()*/);
		m_pDC = NULL;
	}

	MSWindows::DeleteObject(m_pDitherBrush);
	m_pDitherBrush = NULL;
#endif

/*

	if (dragging == 2)
	{
		EndDrag();
	}
	else if (dragging == 3)
	{
		EndResize();
	}
	DrawFocusRect(TRUE);CLXUIVisualContentSource // gets rid of focus rect
	ReleaseCapture();

	CWnd* pWnd = CWnd::GetDesktopWindow();
	pWnd->UnlockWindowUpdate();
	if (m_pDC != NULL)
	{
		pWnd->ReleaseDC(m_pDC);
		m_pDC = NULL;
	}
	*/
}

void CDragContext::PlaceDrag()
{
#if 0
	CPoint/*m_pBar->*/ m_ptMRUFloatPos = m_rectFrameDragHorz.TopLeft();
//	CComQIPtr<IUIMDIFrame>(m_pBar->m_pDockSite)->WindowControlBar(m_pBar, m_pBar->m_ptMRUFloatPos/*, m_pBar->m_dwMRUFloatStyle*/);

	HWND hwnd;
	if (m_pBar->get_OwnerWindow())
		hwnd = m_pBar->get_OwnerWindow()->GetHwnd();
	else
		hwnd = dynamic_cast<CLXUIVisualContentSource*>(m_pBar)->GetHwnd();

	SetWindowPos(hwnd, NULL, m_ptMRUFloatPos.x, m_ptMRUFloatPos.y, 0, 0, SWP_NOSIZE);
#endif

//	ASSERT(0);
	if (m_dwOverDockStyle != 0)
	{
		//IUIDockBar* pDockBar = GetDockBar(m_dwOverDockStyle);
	//	IDockSite* pDockBar = m_pDockBar;
		ASSERT(m_pDockSite != NULL);

		LDraw::RectI rect = (m_dwOverDockStyle & CBRS_ORIENT_VERT) ? m_rectDragVert : m_rectDragHorz;

		{
//			m_uMRUDockID = uID;
#if 0	// Have this
			m_pBar->m_rectMRUDockPos = rect;
			hwndDockBar.ScreenToClient(&m_pBar->m_rectMRUDockPos);
#endif
		}

		// dock it at the specified position, RecalcLayout will snap
//			m_pDockSite->DockControlBar(this/*m_pBar*/, pDockBar, &rect);

		/*
		UIElement* pParent = m_pBar->GetRParent();

		CUIFloatingFrame* pPrevFrame = dynamic_cast<CUIFloatingFrame*>(pParent);
		if (pPrevFrame)
		{
			pParent->RemoveRChild(m_pBar);
		}
		else
		*/
		m_pDockSite->DockControlBar(m_pBar, &rect);
	}
#if 0
	else
		if ((m_pBar->GetBarStyle() & CBRS_SIZE_DYNAMIC) || (HORZF(m_pBar->GetBarStyle()) && !m_bFlip) ||
			(VERTF(m_pBar->GetBarStyle()) && m_bFlip))
	{
		//m_pBar->m_pDockBar->BeforeRemoveControlBar(m_pBar);

		if (TRUE)
		{
			m_pBar->m_dwMRUFloatStyle = CBRS_ALIGN_TOP | (m_pBar->m_dwDockStyle & CBRS_FLOAT_MULTI);
			m_pBar->m_ptMRUFloatPos = m_rectFrameDragHorz.TopLeft();
#if 0	// This is what I had previously
			m_pBar->m_pDockSite->FloatControlBar(m_pBar, m_pBar->m_ptMRUFloatPos, m_pBar->m_dwMRUFloatStyle);
#endif

			CComQIPtr<ILXUIMDIFrameElement> dockframe = ((CPElementBase*)CComQIPtr<ILViewNode>(m_pBar->m_pDockSite).p);
			
			dockframe->floatBar(CComQIPtr<ILXUIPageElement>(((CPElementBase*)(CComQIPtr<ILViewNode>(m_pBar).p))), m_pBar->m_ptMRUFloatPos.x, m_pBar->m_ptMRUFloatPos.y);
		}
#if 0
		else
		{
			m_pBar->m_ptMRUFloatPos = m_rectFrameDragHorz.TopLeft();
			CComQIPtr<IUIMDIFrame>(m_pBar->m_pDockSite)->WindowControlBar(m_pBar, m_pBar->m_ptMRUFloatPos/*, m_pBar->m_dwMRUFloatStyle*/);
		}
#endif
	}
	else // vertical float
	{
		ASSERT(0);
#if 0
		m_pBar->m_dwMRUFloatStyle = CBRS_ALIGN_LEFT | (m_pBar->m_dwDockStyle & CBRS_FLOAT_MULTI);
		m_pBar->m_ptMRUFloatPos = m_rectFrameDragVert.TopLeft();
		m_pBar->m_pDockSite->FloatControlBar(m_pBar, m_pBar->m_ptMRUFloatPos, m_pBar->m_dwMRUFloatStyle);
#endif
	}
#endif

}

void CDragContext::EndDrag()
{
	CancelLoop();

	PlaceDrag();
}

void CDragContext::EndResize()
{
	CancelLoop();

	VisualContentSource* pFrame = m_pBar->GetOwnerWindow();
	HWND hWnd = NULL;//pFrame->GetHwnd();
	ASSERT(0);

	SetMRUWidth(m_pBar, m_rectActualSize.Width);

//	pFrame->Measure(LDraw::SizeD(m_rectActualFrameSize.Width, m_rectActualFrameSize.Height));
	pFrame->m_Content->Arrange(LDraw::RectD(0, 0, m_rectActualFrameSize.Width, m_rectActualFrameSize.Height));

//	::SetWindowPos(hWnd, NULL, m_rectActualFrameSize.X, m_rectActualFrameSize.Y, m_rectActualFrameSize.Width, m_rectActualFrameSize.Height, SWP_NOZORDER);
#if 0

	m_pBar->SetMRUWidth(m_rectActualSize.Width());
	m_pBar->CalcDynamicLayout(m_rectActualSize.Width(), LM_HORZ | LM_COMMIT);

	ASSERT(0);
#if 0	// Had this
	m_pBar->m_pDockSite->FloatControlBar(m_pBar, m_rectActualFrameSize.TopLeft(),
		CBRS_ALIGN_TOP | (m_pBar->m_dwDockStyle & CBRS_FLOAT_MULTI) | CBRS_SIZE_DYNAMIC);
#endif

#if 0
				CRect rect = m_rectActualFrameSize;
				SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER);
#endif
#endif
}

bool CDragContext::Track()
{
#if WIN32
	// don't handle if capture already set
	if (MSWindows::GetCapture() != NULL)
		return false;

	// set capture to the window which received this message
	HWND hwnd = NULL;
	if (m_pBar->GetOwnerWindow())
	{
		hwnd = dynamic_cast<HwndSource*>(m_pBar->GetOwnerWindow()->m_pSite)->GetHwnd();
	}
	else
	{
		hwnd = dynamic_cast<HwndSource*>(m_pBar)->GetHwnd();
	}
	ASSERT(::IsWindow(hwnd));

	MSWindows::SetCapture(hwnd);
	//ASSERT(m_pBar == CWnd::GetCapture());
#elif AMIGA

	PlatformWindow pWindow;
	pWindow = dynamic_cast<HwndSource*>(m_pBar->get_OwnerWindow()->m_pSite)->GetHwnd();

#endif

#if WIN32

	// get messages until capture lost or cancelled/accepted
	while (MSWindows::GetCapture() == hwnd)
	{
		MSWindows::MSG msg;
		if (!MSWindows::GetMessageA(&msg, NULL, 0, 0))
		{
			//AfxPostQuitMessage(msg.wParam);
			break;
		}

		switch (msg.message)
		{
		case WM_LBUTTONUP:
			//if (m_bDragging == 2)
			//	EndDragPage();
			//else
			if (m_bDragging)
				EndDrag();
			else
				EndResize();
			return true;
		case WM_MOUSEMOVE:
			//if (m_bDragging == 2)
			//	MovePage(msg.pt);
			//else
			if (m_bDragging)
				Move(LDraw::PointI(msg.pt.x, msg.pt.y));
			else
				Stretch(LDraw::PointI(msg.pt.x, msg.pt.y));

		//	MessageBeep(-1);

			break;
		case WM_KEYUP:
			/*
			if (m_bDragging)
				OnKey((int)msg.wParam, FALSE);
				*/
			break;
		case WM_KEYDOWN:
			/*
			if (m_bDragging)
				OnKey((int)msg.wParam, TRUE);
			if (msg.wParam == VK_ESCAPE)
			{
				CancelLoop();
				return FALSE;
			}
			*/
			break;
		case WM_RBUTTONDOWN:
			CancelLoop();
			return false;

		// just dispatch rest of the messages
		default:
			MSWindows::DispatchMessageA(&msg);
			break;
		}

		ASSERT(0);
		//pLayoutManager->MeasureAll();
		pLayoutManager->RenderAll();
	}

#elif AMIGA

	bool bDone = false;
	while (!bDone)
	{
		int nSigMask = execWait(SysBase, 1<<pWindow->UserPort->mp_SigBit);// | CONTROL_C);

		if (nSigMask & (1<<pWindow->UserPort->mp_SigBit))
		{
		// As of V39 really is ExtIntuiMessage
			while (struct IntuiMessage* pMsg = (IntuiMessage*)GetMsg(pWindow->UserPort))
			{
				struct IntuiMessage msg = *pMsg;
				ReplyMsg((struct Message*)pMsg);

				if (msg.aos_Class == IDCMP_MOUSEMOVE)
				{
					LDraw::PointI point(pWindow->MouseX + pWindow->LeftEdge, pWindow->MouseY + pWindow->TopEdge);

					if (m_bDragging)
						Move(point);
					else
						Stretch(point);
				}
				else if (msg.aos_Class == IDCMP_MOUSEBUTTONS)
				{
					if (true)
					{
						if (m_bDragging)
							EndDrag();
						else
							EndResize();
						return true;
					}
					/*
					else
					{
						bDone = true;
						break;
					}
					*/
				}
				else
				{
					WindowUserData* pUserData = reinterpret_cast<WindowUserData*>(msg.IDCMPWindow->UserData);
					pUserData->pHandler(&msg, pUserData->pData);
				}
			}

			pLayoutManager->MeasureAll();
			pLayoutManager->RenderAll();
		}
	}

#endif

	CancelLoop();

	return false;
}

}	// UI
}
