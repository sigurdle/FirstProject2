#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridNode.h"

#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

//////////////////////////////////////////////////////////////////////
// CGridContainer

void CGridContainer::Deselect()
{
	m_selected = false;

	ASSERT(0);
#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pNode = (CGridItem*)m_childList.GetNext(pos);
		pNode->Deselect();
	}
#endif
}

void CGridContainer::DrawExpand(MSWindows::HDC hDC, bool bOver)
{
	ASSERT(0);
#if 0
	CDCHandle dc(hDC);

	CRect rc(2, 2, 2+12, 2+m_computedSize.Height-4);

	dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE)/*RGB(190, 190, 190)*/);
	
	rc.InflateRect(-1,-1);

	int o;
	if (bOver)
	{
		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DHILIGHT));
		o = 1;
	}
	else
	{
		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		o = 0;
	}

	HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(BLACK_PEN));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

	if (m_expanded)
	{
		POINT pt[3] =
		{
			7+o, 4+o,
			10+o, 7+o,
			4+o, 7+o
		};

		Polygon(hDC, pt, 3);
	}
	else
	{
		POINT pt[3] =
		{
			7+o, 7+o,
			10+o, 4+o,
			4+o, 4+o
		};

		Polygon(hDC, pt, 3);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
#endif
}

// virtual
int CGridContainer::Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal)
{
	ASSERT(0);
#if 0
	*pVal = NULL;

	CRect erect(2, 2, 12+1, m_size.cy-2);

	POINT org;
	GetViewportOrgEx(hDC, &org);

	if (PtInRect(&erect, point))
	{
		HWND hwnd = m_pUI->m_hWnd;

		m_pUI->SetCapture();

		BOOL bOver = TRUE;
		DrawExpand(hDC, bOver);

		BOOL bLoop = TRUE;
		MSG msg;
		while (bLoop && GetMessage(&msg, hwnd, 0, 0))
		{
			TranslateMessage(&msg);
			//DispatchMessage

			switch (msg.message)
			{
			case WM_LBUTTONUP:
				{
					bLoop = FALSE;
				}
				break;
				
			case WM_MOUSEMOVE:
				{
					POINT pt;
					pt.x = (short)LOWORD(msg.lParam);
					pt.y = (short)HIWORD(msg.lParam);

					pt.x -= org.x;
					pt.y -= org.y;

					BOOL bNowOver = PtInRect(&erect, pt);

					if (bNowOver != bOver)
					{
						bOver = bNowOver;
						DrawExpand(hDC, bOver);
					}
				}
				break;
			}
		}

		ReleaseCapture();

		if (bOver)
		{
			m_expanded = !m_expanded;

			Size(hDC, 0/*m_size.cx*/);	// Resize this

			if (m_parent)
			{
				m_parent->RecalculateParentSize(hDC);
			}

			m_pUI->Invalidate();
			m_pUI->OnSize();
		}

		*pVal = this;
	}
#endif
	return 0;
}

}
