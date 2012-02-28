#include "stdafx.h"
#include "LXUI2.h"
#include "UIDockBar.h"

#include "DragContext.h"	// TODO, remove

#include "UIFloatingFrame.h"	// TODO, remove
#include "SizeBox.h"

#include "ToolBar.h"

namespace System
{
namespace UI
{

CUIDockBar::CUIDockBar()
{
	m_dwStyle = 0L;
	m_bFloating = false;
	m_bHorz = true;
	m_height = 0;

	m_arrBars.Add(NULL);	// TODO, ???

#if 0
	m_pFrame = NULL;
#endif
}

#if 0
BOOL CUIDockBar::RemoveControlBar(CUIDlgSite* pBar, int nPosExclude/* = -1*/, int nAddPlaceHolder/* = 0*/)
{
	ASSERT(nAddPlaceHolder == 1 || nAddPlaceHolder == 0 || nAddPlaceHolder == -1);
	ASSERT_VALID(this);
	ASSERT(pBar != NULL);
	int nPos = FindBar(pBar, nPosExclude);
	ASSERT(nPos > 0);

	if (nAddPlaceHolder == 1)
	{
		HWND hwnd;
		pBar->get_hwnd(&hwnd);
		m_arrBars[nPos] = (CUIDlgSite*)_AfxGetDlgCtrlID(hwnd);

		// check for already existing place holder
		int nPosOld = FindBar(/*(IUIDlgSite*)*/m_arrBars[nPos], nPos);
		if (nPosOld > 0)
		{
			m_arrBars.RemoveAt(nPos);

			// remove section indicator (NULL) if nothing else in section
			if (m_arrBars[nPos-1] == NULL && m_arrBars[nPos] == NULL)
				m_arrBars.RemoveAt(nPos);
		}
	}
	else
	{
		m_arrBars.RemoveAt(nPos);
		if (m_arrBars[nPos-1] == NULL && m_arrBars[nPos] == NULL)
			m_arrBars.RemoveAt(nPos);

		// Remove any pre-existing place holders.
		if (nAddPlaceHolder != -1)
			RemovePlaceHolder(pBar);
	}

// SL
//	pBar->DestroyWindow();	// check if it's a child
///

	// don't do anything more in the shutdown case!
		return FALSE;
#if 0
	if (pBar->m_pDockContext == NULL)
		return FALSE;
#endif

#if 0
	// get parent frame for recalc layout/frame destroy
	CFrameWnd* pFrameWnd = GetDockingFrame();
	if (m_bFloating && GetDockedVisibleCount() == 0)
	{
		if (GetDockedCount() == 0)
		{
			pFrameWnd->DestroyWindow();
			return TRUE; // Self-Destruct
		}
		else
			pFrameWnd->ShowWindow(SW_HIDE);
	}
	else
		pFrameWnd->DelayRecalcLayout();
#endif

	return FALSE;
}
#endif

#if 0
void CUIDockBar::AddChild(Object* obj)
{
	UIElement* pVisual = dynamic_cast<UIElement*>(obj);
	if (pVisual == NULL) THROW(-1);

	// always add on current row, then create new one
	m_arrBars.Add(pBar);
	m_arrBars.Add(NULL);
}
#endif

// virtual
LDraw::SizeD CUIDockBar::MeasureOverride(LDraw::SizeD availSize)
{
//	m_availSize = availSize;	// TODO, not necessary

	//GetShowTabs();

#if 0
	m_arrBars.RemoveAll();

#if 0
	if (m_pFrame)
#endif
	{
		std::vector<UIElement*>::const_iterator pos = get_rchildList().begin();
		while (pos != get_rchildList().end())
		{
			UIElement* pNode = *pos++;//(CPNode*)m_rchildList.GetNext(pos);

		//	if (pNode->m_type == LNODE_ELEMENT)
			if (dynamic_cast<CUIFloatingFrame*>(pNode) == NULL)
			{
				m_arrBars.Add(pNode);
				/*
				CComQIPtr<ILXUIPageElement> page = pNode->m_pNode;
				if (page)
				{
#if 0
					((CUIDlgSite*)pNode)->m_pDockSite = m_pFrame;
#endif

					m_arrBars.Add((CUIDlgSite*)pNode);
				}
				else
				{
					m_arrBars.Add((CUIDlgSite*)NULL);
				}
				*/
			}
		}

		m_arrBars.Add((CLXUIControl*)NULL);
	}
#endif

	LDraw::Sizei size = CalcFixedLayout(false, availSize.Width, true/*bStretch*/, m_dwStyle & CBRS_ORIENT_HORZ);

	return LDraw::SizeD(size.Width, size.Height);
}

// virtual
LDraw::SizeD CUIDockBar::ArrangeOverride(LDraw::SizeD finalSize)
{
	CalcFixedLayout(true, finalSize.Width, true/*bStretch*/, m_dwStyle & CBRS_ORIENT_HORZ);
//	CLXUIControl::OnArrange(finalSize);

	return finalSize;
}

unsigned int CUIDockBar::get_VisualChildrenCount()
{
	return m_children.size();
}

Visual* CUIDockBar::GetVisualChild(unsigned int index)
{
	if (index < m_children.size())
	{
		return m_children[index];
	}
	else
	{
		throw new ArgumentOutOfRangeException();
	}
}

void CUIDockBar::RemoveControlBar(ToolBar* pBar)
{
	int nPos = FindBar(pBar, -1);
	RemoveRChild(m_arrBars[nPos]);
	m_arrBars.RemoveAt(nPos);
	if (m_arrBars[nPos-1] == NULL && m_arrBars[nPos] == NULL)
		m_arrBars.RemoveAt(nPos);

	InvalidateMeasure();
}

void CUIDockBar::DrawFocusRect(MSWindows::HDC hDC, LDraw::RectI rectDragHorz, LDraw::RectI rectFrameDragHorz)
{
	rectDragHorz.Inflate((1+3+6), (3+1), 3+1, 3+1);
}

void CUIDockBar::DockControlBar(ToolBar* pToolBar, LDraw::RectI* lpRect)
{
	ToolBar* pBar = pToolBar;

	if (lpRect)
	{
		// Screen To client
		LDraw::RectD bounds = GetScreenBounds();
		lpRect->Translate(-bounds.X, -bounds.Y);
	}

	// TODO
	MessageBeep(-1);
#if 0
//	IDockSite* pPrevParent = pBar->m_pDockParent;//GetRParent();
	IDockSite* pPrevParent = pBar->GetRParent();//GetRParent();
#endif
	CUIDockBar* pPrevParent = dynamic_cast<CUIDockBar*>(pBar->GetRParent());

//	CDlgSheet* pBar = static_cast<CDlgSheet*>(pBarI);
	//ASSERT_VALID(this);
	//ASSERT_VALID(pBar);
	//ASSERT_KINDOF(CControlBar, pBar);

	/*
	CWindow barWnd;
	pBar->get_hwnd(&barWnd.m_hWnd);

	if (barWnd.m_hWnd == NULL)
	{
		pBar->Create(m_hWnd);
		pBar->get_hwnd(&barWnd.m_hWnd);
	}

	CRect rectBar;
	barWnd.GetWindowRect(&rectBar);

	if (pBar->m_pDockBar == this && (lpRect == NULL || rectBar == *lpRect))
	{
		// already docked and no change in position
		return;
	}

	pBar->AddRef();
	*/

	// set CBRS_FLOAT_MULTI style if docking bar has it
#if 0
	if (m_bFloating && (pBar->m_dwDockStyle & CBRS_FLOAT_MULTI))
		m_dwStyle |= CBRS_FLOAT_MULTI;

	m_dwStyle &= ~(CBRS_SIZE_FIXED | CBRS_SIZE_DYNAMIC);
	m_dwStyle |= pBar->GetBarStyle() & (CBRS_SIZE_FIXED | CBRS_SIZE_DYNAMIC);
#endif

#if 0
	if (!(m_dwStyle & CBRS_FLOAT_MULTI))
	{
		TCHAR szTitle[_MAX_PATH];
		pBar->GetWindowText(szTitle, _countof(szTitle));
		AfxSetWindowText(m_hWnd, szTitle);
	}
#endif

	// align correctly and turn on all borders
	/*
	DWORD dwStyle = pBar->GetBarStyle();
	dwStyle &= ~(CBRS_ALIGN_ANY);
	dwStyle |=  (m_dwStyle & CBRS_ALIGN_ANY) | CBRS_BORDER_ANY;

//	dwStyle |= CBRS_TOP;	// TODO remove

	if (m_bFloating)
		dwStyle |= CBRS_FLOATING;
	else
		dwStyle &= ~CBRS_FLOATING;

	pBar->SetBarStyle(dwStyle);

	// hide first if changing to a new docking site to avoid flashing
	BOOL bShow = FALSE;
	*/

#if 0
	HWND hwnd;
	pBar->get_hwnd(&hwnd);
	if (pBar->m_pDockBar != this && ::IsWindowVisible(hwnd))
	{
		::SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_HIDEWINDOW);
		bShow = TRUE;
	}
#endif

#if 0
	ToolBar* pToolBar = new ToolBar;
#endif

	int nPos = -1;
	if (lpRect != NULL)
	{
		// insert into appropriate row
		LDraw::RectI rect(*lpRect);
#if 0
		ScreenToClient(&rect);
#endif
		LDraw::PointD ptMid(rect.X + rect.Width/2, rect.Y + rect.Height/2);
		nPos = Insert(pToolBar, rect, ptMid);

		// position at requested position

		pToolBar->m_computedLeft = rect.X;
		pToolBar->m_computedTop = rect.Y;

#if 0
		::SetWindowPos(hwnd, NULL, rect.left, rect.top, rect.Width(),
			rect.Height(), SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
#endif
	}
	else
	{
	//	ASSERT(0);
		// always add on current row, then create new one
		m_arrBars.Add(pToolBar);
		m_arrBars.Add(NULL);

#if 0
		// align off the edge initially
		::SetWindowPos(hwnd, NULL, -0/*afxData.cxBorder2*/, -0/*afxData.cyBorder2*/, 0, 0,
			SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOCOPYBITS);
#endif
	}

	if (pPrevParent == this)
	{
	// RemoveControlBar
		nPos = FindBar(pBar, nPos/*except this one*/);

		RemoveRChild(m_arrBars[nPos]);

		m_arrBars.RemoveAt(nPos);
		if (m_arrBars[nPos-1] == NULL && m_arrBars[nPos] == NULL)
			m_arrBars.RemoveAt(nPos);
	}
	else
	{
		if (pPrevParent != NULL)
		{
			pPrevParent->RemoveControlBar(pBar);
		}

#if 0
		pBar->m_pDockParent = this;
#endif
	}

#if 0
	if (pPrevParent)
		pPrevParent->RemoveRChild(pBar);
#endif

#if 0
	if (pBar->GetRParent())
		pBar->GetRParent()->RemoveRChild(pBar);
#endif

#if 0
	pToolBar->set_Content(pBar);
#endif
//	pToolBar->SetOwnerWindow(m_pOwnerWindow);	// TODO, shouldn't be needed here
//	get_Children()->Add(pToolBar);
//	pToolBar->SetRParent(this);
	AddVisualChild(pToolBar);
	m_children.push_back(pToolBar);
//	AddRChild(pToolBar);

#if 0
	// attach it to the docking site
	if (::GetParent(hwnd) != m_hWnd)
		::SetParent(hwnd, m_hWnd);
	if (pBar->m_pDockBar == this)
	{
		CUIDockBar* pDockBar = static_cast<CUIDockBar*>(pBar->m_pDockBar);
		pDockBar->RemoveControlBar(pBar, nPos);
	}
	else if (pBar->m_pDockBar != NULL)
	{
	//	CUIDockBar* pDockBar = static_cast<CUIDockBar*>(pBar->m_pDockBar);

		ASSERT(0);
#if 0	// Had this
		pBar->m_pDockBar->RemoveControlBar(pBar/*, -1, m_bFloating && !pDockBar->m_bFloating*/);
#endif
	}
//	pBar->m_pDockBar = this;
#endif

//	if (bShow)
	{
		/*
		ASSERT(!::IsWindowVisible(hwnd));
		::SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
			SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
			*/
	}

	// remove any place holder for pBar in this dockbar
	RemovePlaceHolder(pBar);

	// get parent frame for recalc layout
#if 0
	CFrameWnd* pFrameWnd = GetDockingFrame();
	pFrameWnd->DelayRecalcLayout();
#endif

	//MessageBeep(-1);
	// TODO, update
#if 0
	LDraw::Size size = CalcFixedLayout(TRUE, m_dwStyle & CBRS_ORIENT_HORZ);

	if (m_dwStyle & CBRS_ORIENT_HORZ)
		m_height = size.cy;
	else
		m_height = size.cx;
#endif
	InvalidateMeasure();
}

int CUIDockBar::Insert(ToolBar* pBarIns, LDraw::RectI rect, LDraw::PointD ptMid)
{
//	ASSERT_VALID(this);
	ASSERT(pBarIns != NULL);

	int nPos = 0;
	int nPosInsAfter = 0;
	int nWidth = 0;
	int nTotalWidth = 0;
	bool bHorz = true;//m_dwStyle & CBRS_ORIENT_HORZ;

//	AddRChild(pBarIns);

	for (nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
		UIElement* pBar = m_arrBars[nPos];//GetDockedControlBar(nPos);
		if (pBar != NULL)// && pBar->IsVisible()==S_OK)
		{
			/*
			CWindow barWnd;
			pBar->get_hwnd(&barWnd.m_hWnd);

			CRect rectBar;
			barWnd.GetWindowRect(&rectBar);

			ScreenToClient(&rectBar);
			*/

			LDraw::RectD rectBar(pBar->m_computedLeft, pBar->m_computedTop, pBar->m_computedSize.Width, pBar->m_computedSize.Height);

			nWidth = MAX(nWidth,
				bHorz ? rectBar.Height : rectBar.Width - 1);
			if (bHorz ? rect.X > rectBar.X : rect.Y > rectBar.Y)
				nPosInsAfter = nPos;
		}
		else // end of row because pBar == NULL
		{
			nTotalWidth += nWidth - 0/*afxData.cyBorder2*/;
			nWidth = 0;
			if ((bHorz ? ptMid.Y : ptMid.X) < nTotalWidth)
			{
				if (nPos == 0) // first section
					m_arrBars.InsertAt(nPosInsAfter+1, (ToolBar*)NULL);
				m_arrBars.InsertAt(nPosInsAfter+1, pBarIns);
				return nPosInsAfter+1;
			}
			nPosInsAfter = nPos;
		}
	}

	// create a new row
	m_arrBars.InsertAt(nPosInsAfter+1, (ToolBar*)NULL);
	m_arrBars.InsertAt(nPosInsAfter+1, pBarIns);

	return nPosInsAfter+1;
}

#if 0
void CUIDockBar::RecalcLayout()
{
	LDraw::Size size = CalcFixedLayout(TRUE, TRUE);
	m_height = size.cy;
	m_specifiedHeight = m_height;	// ???
// ??
	//m_computedHeight = size.cy;
//	m_pBox->m_innerRect.Height = size.cy;
//	m_pBox->m_outerRect.Height = size.cy;
//	m_pBox->m_outerRect.Width = m_pOwnerBox->m_innerRect.Width;
//	m_pBox->m_outerRect.Height = m_pOwnerBox->m_innerRect.Height;
}
#endif

LDraw::Sizei CUIDockBar::CalcFixedLayout(bool bArrange, int maxWidth, bool bStretch, bool bHorz)
{
	LDraw::Sizei sizeFixed(0,0);
	//ASSERT_VALID(this);


	//LDraw::Size sizeFixed = CControlBar::CalcFixedLayout(bStretch, bHorz);

	// get max size
	LDraw::SizeF sizeMax(maxWidth,800);	// TODO
	/*
	if (!m_rectLayout.IsRectEmpty())
		sizeMax = m_rectLayout.Size();
	else
	*/
#if 0
	{
		HWND pFrame = GetParent();
		CRect rectFrame;
//		CFrameWnd* pFrame = GetParentFrame();
		::GetClientRect(pFrame, &rectFrame);
		sizeMax = rectFrame.Size();
	}
#endif

#if 0
	HDWP hDWP;

	// prepare for layout
	/*
	//AFX_SIZEPARENTPARAMS layout;
	/*layout.*/hDWP = /*m_bLayoutQuery ?
		NULL : */::BeginDeferWindowPos(m_arrBars.GetSize());
#endif

	LDraw::PointD pt(0/*-afxData.cxBorder2*/, -0/*afxData.cyBorder2*/);
	double nWidth = 0;

	bool bWrapped = false;

	// layout all the control bars
	for (int nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
	//	UIElement* pBar = GetDockedControlBar(nPos);
		UIElement* pBar = m_arrBars[nPos];

		if (pBar != NULL && dynamic_cast<CUIFloatingFrame*>(pBar) == NULL)
		{

			if (true/*pBar->IsVisible()==S_OK*/)
			{
#if 0	// Experimental remove this
				// get ideal rect for bar
				DWORD dwMode = 0;
				if ((pBar->GetBarStyle() & CBRS_SIZE_DYNAMIC) &&
					(pBar->GetBarStyle() & CBRS_FLOATING))
					dwMode |= LM_HORZ | LM_MRUWIDTH;
				else if (pBar->GetBarStyle() & CBRS_ORIENT_HORZ)
					dwMode |= LM_HORZ;// | LM_HORZDOCK;
				else
					dwMode |=  0;//LM_VERT;//LM_VERTDOCK;

				LDraw::Size sizeBar;
				if (pBar->GetBarStyle() & CBRS_STRETCH)
				{
					sizeBar = pBar->CalcDynamicLayout(sizeMax.cx, dwMode/* | LM_COMMIT*/);
				}
				else
				{
					sizeBar = pBar->CalcDynamicLayout(-1, dwMode);
				}

				Gdiplus::RectF rect(pt, sizeBar);
#endif

				double maxwidth;
				{
					if (!bArrange)
						pBar->Measure(LDraw::SizeD(99999, 0));
				//	maxwidth = 
					/*
					CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
					//double old = pBar->m_specifiedHeight;
					//pBar->m_specifiedHeight = rect.Height();
					pBar->DistributeWithinBlock(pC, 0xfffffff);

					pBar->m_pBox->AdjustOuterRect();

					maxwidth = pBar->m_pBox->m_outerRect.Width;
					ASSERT(maxwidth < 80000);
					*/
#if 0
					maxwidth = pC->m_maxx;

					// TODO, have this somewhere else?
					maxwidth += pBar->m_computedMargin[0] + pBar->m_computedMargin[2] +
						pBar->m_computedBorderWidth[0] + pBar->m_computedBorderWidth[2] +
						pBar->m_computedPadding[0] + pBar->m_computedPadding[2];
#endif

				//	maxwidth = pBar->m_pBox->m_outerRect.Width;

					//pBar->m_specifiedHeight = old;
				}

#if 0	// Had this
				{
					CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
					double old = pBar->m_specifiedHeight;
					//pBar->m_specifiedHeight = rect.Height();
					pBar->DistributeWithinBlock(pC, maxwidth);

					//pBar->m_specifiedHeight = old;
					delete pC;

					pBar->m_pBox->AdjustOuterRect();

					/*
					pBar->m_pBox = pBar->CreateBlockBox();

					pBar->m_pBox->m_outerRect.X = rect.left;
					pBar->m_pBox->m_outerRect.Y = rect.top;
					pBar->m_pBox->m_outerRect.Width = rect.Width();
					pBar->m_pBox->m_outerRect.Height = rect.Height();

					pBar->m_pBox->m_innerRect.X = 0;
					pBar->m_pBox->m_innerRect.Y = 0;
					pBar->m_pBox->m_innerRect.Width = rect.Width();
					pBar->m_pBox->m_innerRect.Height = rect.Height();
					*/

					m_pBox->AddChildBox(pBar->m_pBox);
				}
#endif

				LDraw::SizeD sizeBar = pBar->get_DesiredSize();

				LDraw::RectD rect(pt, sizeBar);

				//Gdiplus::RectF rect = pBar->m_pBox->m_outerRect;//(pt, sizeBar);
				//rect.Offset(pt);

				// get current rect for bar
				LDraw::RectD rectBar;

				//ASSERT(0);

#if 0	// Had this
				CComQIPtr<ILXUIPageElement> page = pBar->m_pNode;
				{
					CComBSTR bstr;
					page->getAttribute(L"x", &bstr);
					if (bstr)
						rectBar.X = atof(_bstr_t(bstr));
					else
						rectBar.X = 0;
				}
				{
					CComBSTR bstr;
					page->getAttribute(L"y", &bstr);
					if (bstr)
						rectBar.Y = atof(_bstr_t(bstr));
					else
						rectBar.Y = 0;
				}
#else
				rectBar.X = pBar->m_computedLeft;
				rectBar.Y = pBar->m_computedTop;

				rectBar.Width = pBar->get_DesiredSize().Width;
				rectBar.Height = pBar->get_DesiredSize().Height;
#endif
				//rectBar.right = rectBar.left+sizeBar.cx;
				//rectBar.bottom = rectBar.top+sizeBar.cy;

#if 0
				CWindow barWnd;
				pBar->get_hwnd(&barWnd.m_hWnd);

				barWnd.GetWindowRect(&rectBar);
				ScreenToClient(&rectBar);
#endif

				if (true)//bHorz)
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.X > rect.X && !m_bFloating)
						rect.Translate(rectBar.X - rect.X, 0);

					// If ControlBar goes off the right, then right justify
					if (rect.GetRight() > sizeMax.Width && !m_bFloating)
					{
						//MessageBeep(-1);
						double x = rect.Width - 0;//afxData.cxBorder2;
						x = MAX(sizeMax.Width - x, pt.X);
						rect.Translate(x - rect.X, 0);
					}

					// If ControlBar has been wrapped, then left justify
					if (bWrapped)
					{
						bWrapped = false;
						rect.Translate(-(rect.X + 0/*afxData.cxBorder2*/), 0);
					}
//#if 0	// Had this ???
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.X >= (sizeMax.Width - 0/*afxData.cxBorder2*/)) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						if (bArrange)
							m_arrBars.InsertAt(nPos, (ToolBar*)NULL);
						pBar = NULL; ;//pVoid = NULL;
						bWrapped = true;
					}
//#endif
					if (!bWrapped)
					{
						if (!rect.Equals(rectBar))
						{
							/*
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
							*/
						}
						pt.X = rect.X + sizeBar.Width - 0;//afxData.cxBorder2;
						nWidth = MAX(nWidth, sizeBar.Height);

						if (bArrange)
						{
						//	pBar->m_pBox->m_outerRect.Offset(rect.X, rect.Y);
							pBar->Arrange(rect);//pBar->get_DesiredSize());
							//pBar->SetLayoutOffset(rect.X, rect.Y);	// TODO, do in Arrange()
						}
					}
				}
				else
				{
					ASSERT(0);
#if 0
					// Offset Calculated Rect out to Actual
					if (rectBar.top > rect.top && !m_bFloating)
						rect.OffsetRect(0, rectBar.top - rect.top);

					// If ControlBar goes off the bottom, then bottom justify
					if (rect.bottom > sizeMax.cy && !m_bFloating)
					{
						int y = rect.Height() - 0;//afxData.cyBorder2;
						y = MAX(sizeMax.cy - y, pt.y);
						rect.OffsetRect(0, y - rect.top);
					}

					// If ControlBar has been wrapped, then top justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(0, -(rect.top + 0/*afxData.cyBorder2*/));
					}
#if 0	// Had this ??
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.top >= (sizeMax.cy - 0/*afxData.cyBorder2*/)) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CUIDlgSite*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}
#endif
					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							/*
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
						*/
							if (TRUE)
							{
								pBar->m_pBox = pBar->CreateBlockBox();

								pBar->m_pBox->m_outerRect.X = rect.left;
								pBar->m_pBox->m_outerRect.Y = rect.top;
								pBar->m_pBox->m_outerRect.Width = rect.Width();
								pBar->m_pBox->m_outerRect.Height = rect.Height();

								pBar->m_pBox->m_innerRect.X = 0;
								pBar->m_pBox->m_innerRect.Y = 0;
								pBar->m_pBox->m_innerRect.Width = rect.Width();
								pBar->m_pBox->m_innerRect.Height = rect.Height();

								m_pBox->AddChildBox(pBar->m_pBox);
							}
#if 0
							else
							{
								HWND hwnd;
								pBar->get_hwnd(&hwnd);
								::DeferWindowPos(hDWP, hwnd, NULL, rect.left, rect.top, rect.Width(), rect.Height(), 0);
							//	::DeferWindowPos(hDWP, pBar->m_hWnd, &rect);
								//AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
							}
#endif
						}
						pt.y = rect.top + sizeBar.cy - 0/*afxData.cyBorder2*/;
						nWidth = MAX(nWidth, sizeBar.cx);
					}
#endif
				}
			}
			if (!bWrapped)
			{
				// handle any delay/show hide for the bar
				//pBar->RecalcDelayShow(&layout);
			}
		}
		if (pBar == NULL /*&& pVoid == NULL*/ && nWidth != 0)
		{
			// end of row because pBar == NULL
			if (true)//bHorz)
			{
			//	MessageBeep(-1);
				pt.Y += nWidth - 0;//afxData.cyBorder2;
				sizeFixed.Width = MAX(sizeFixed.Width, pt.X);
				sizeFixed.Height = MAX(sizeFixed.Height, pt.Y);
				pt.X = -0;//afxData.cxBorder2;
			}
			else
			{
				pt.X += nWidth - 0;//afxData.cxBorder2;
				sizeFixed.Width = MAX(sizeFixed.Width, pt.X);
				sizeFixed.Height = MAX(sizeFixed.Height, pt.Y);
				pt.Y = -0;//afxData.cyBorder2;
			}
			nWidth = 0;
		}
	}
		/*
	if (!m_bLayoutQuery)
	{
		// move and resize all the windows at once!
		if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
			TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
	}
			*/
	return sizeFixed;
}

int CUIDockBar::FindBar(UIElement* pBar, int nPosExclude/* = -1*/)
{
	ASSERT(0);
#if 0

	ASSERT(dynamic_cast<ToolBar*>(pBar) == NULL);

	for (int nPos = 0; nPos< m_arrBars.GetSize(); nPos++)
	{
		if (nPos != nPosExclude && m_arrBars[nPos] && m_arrBars[nPos]->get_Content() == pBar)
			return nPos;
	}
#endif
	return -1;
}

int CUIDockBar::FindPlaceholder(UIElement* pBar)
{
	for (int nPos = 0; nPos< m_arrBars.GetSize(); nPos++)
	{
		CUIFloatingFrame* p = dynamic_cast<CUIFloatingFrame*>(m_arrBars[nPos]);
		if (p && p->get_Content() == pBar)
			return nPos;
	}
	return -1;
}

void CUIDockBar::RemovePlaceHolder(UIElement* pBar)
{
#if 0
	if (pBar->GetRParent() && pBar->GetRParent()->GetRParent() && dynamic_cast<CUIFloatingFrame*>(pBar->GetRParent()->GetRParent()))
	{
		pBar = pBar->GetRParent()->GetRParent();
	}
	else
		return;
#endif

#if 0	// ????
	// remove remembered docking position
	if (HIWORD(pBar) != 0)
	{
		HWND hwnd;
		pBar->get_hwnd(&hwnd);
		pBar = (CUIDlgSite*)_AfxGetDlgCtrlID(hwnd);
	}
#endif
	int nOldPos = FindPlaceholder(pBar);
	if (nOldPos > 0)
	{
		m_arrBars.RemoveAt(nOldPos);

		// remove section indicator (NULL) if nothing else in section
		if (m_arrBars[nOldPos-1] == NULL && m_arrBars[nOldPos] == NULL)
			m_arrBars.RemoveAt(nOldPos);
	}
}

}	// UI
}
