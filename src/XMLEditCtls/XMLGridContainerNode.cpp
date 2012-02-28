#include "stdafx.h"
#include "XMLEditCtls.h"
#include "XMLGridContainerNode.h"
#include "XMLGridCtl.h"

namespace System
{

void DrawTopLeft(MSWindows::HDC hDC, LDraw::RectI* rc, LDraw::Color clr);

// virtual
void CGridContainerNode::OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree)
{
	ASSERT(0);
#if 0
	m_bEditChanged = TRUE;

	//m_pTree->Size(hDC, m_pTree->m_size.cx);
	Size(hDC, 0);

	if (m_parent)
		m_parent->RecalculateParentSize(hDC);

//	::SetWindowPos(m_hWndEdit, NULL, 0, 0, m_size.cx+2, m_nameHeight/*m_size.cy*/+2, SWP_NOMOVE);
	::SetWindowPos(m_hWndEdit, NULL, 0, 0, m_size.cx-16+2, m_nameHeight/*m_size.cy*/+2, SWP_NOMOVE);

	m_pUI->Invalidate();
#if 0
	m_pUI->OnSize();
#endif
#endif
}

// virtual
void CGridContainerNode::EndEdit()
{
	ASSERT(0);
#if 0
	CXMLGridCtl* pUI = m_pUI;

	if (m_bEditChanged)
	{
		m_bEditChanged = false;

		ATLASSERT(m_hWndEdit);

		int len = ::GetWindowTextLength(m_hWndEdit);
		TCHAR* buf = new TCHAR[len+1];
		::GetWindowText(m_hWndEdit, buf, len+1);
		m_hWndEdit = NULL;
		sysstring name = buf;
		delete buf;

		CComPtr<ILDOMDocument> ownerDocument;
		m_domNode->get_ownerDocument(&ownerDocument);

		CComPtr<ILDOMNode> newNode;
		// TODO namespace
		ownerDocument->renameNode(m_domNode, L"", name, &newNode);
// We could be deleted now

	// In case we got deleted and replaced, reselect the new corresponding node
		CComPtr<IXMLGridNode> xnode;
		pUI->GetXMLNodeFromDOMNode(newNode, &xnode);
		pUI->SelectItem(xnode);
	}
	else
	{
		m_hWndEdit = NULL;
	}

	pUI->m_wndEdit.DestroyWindow();
#endif
}

int CGridContainerNode::GetChildrenWidth()
{
	int maxx = 0;
	ASSERT(0);
#if 0

// Child elements
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

		maxx = max(maxx, pChild->m_size.cx);
	}
#endif
	return maxx;
}

// Called when one of the children have changed size
void CGridContainerNode::RecalculateParentSize(MSWindows::HDC hDC)
{
	ASSERT(0);
#if 0
	m_size.cx = 0;

	int maxx = GetChildrenWidth();
	ResizeChildren(hDC, maxx);

	CalculateChildrenSize();

	int y = 0;

	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

		pChild->m_pos.y = y;
		y += pChild->m_size.cy;
	}

	if (m_parent)
	{
		CComBSTR tagName;
		m_domNode->get_nodeName(&tagName);

		SelectObject(hDC, m_pUI->m_hFont[Font_ElementName]);

		CRect rc(0,0,0,0);
		DrawText(hDC, sysstring(tagName), tagName.Length(), &rc, DT_CALCRECT | DT_SINGLELINE);

		m_nameHeight = rc.Height();

		m_size.cx += m_childrenIndent;//20;
		m_size.cy += m_nameHeight;

		{
			UPOSITION pos = m_childList.GetHeadPosition();
			while (pos)
			{
				CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

				pChild->m_pos.x = m_childrenIndent;//20;
				pChild->m_pos.y += m_nameHeight;
			}
		}

		m_parent->RecalculateParentSize(hDC);
	}
#endif
}

//virtual
int CGridContainerNode::HitTestContent(LDraw::PointD point, UINT nFlags, CGridItem* *pVal)
{
	ASSERT(0);
#if 0
	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx+2 && point.y < m_size.cy+2)
	{
		//if (!bDblClk)
		{
			if (abs(m_size.cx-point.x) <= 2)
			{
				/*
				POINT org;
				GetViewportOrgEx(hDC, &org);

				HWND hwnd = m_pUI->m_hWnd;

				m_pUI->SetCapture();

				BOOL bLoop = TRUE;
				MSG msg;
				while (bLoop && GetMessage(&msg, hwnd, 0, 0))
				{
					TranslateMessage(&msg);

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

							pt.x += org.x;
							pt.y += org.y;

							SizeContent(hDC, pt.x);
							m_pUI->Invalidate();
							m_pUI->OnSize();
						}
						break;

					default:
						DispatchMessage(&msg);
						break;
					}
				}

				ReleaseCapture();
				*/

				*pVal = this;
				return 3;
			}
		}
	}

	int y = 0;

// Children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

		POINT childpoint = point;
		childpoint.y -= y;
		childpoint.x -= 0;

		/*
		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 0, y, &oldOrg);
		*/

		int nClick = pChild->HitTest(childpoint, nFlags, pVal);

		//SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		if (*pVal)
			return nClick;

		y += pChild->m_size.cy;
	}

	*pVal = NULL;
#endif
	return 0;
}

int CGridContainerNode::ClickContent(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem** pVal)
{
	ASSERT(0);
#if 0
	if (point.x >= 0 && point.y >= 0 && point.x < m_size.cx+2 && point.y < m_size.cy+2)
	{
		if (!bDblClk)
		{
			if (abs(m_size.cx-point.x) <= 2)
			{
				POINT org;
				GetViewportOrgEx(hDC, &org);

				HWND hwnd = m_pUI->m_hWnd;

				m_pUI->SetCapture();

				BOOL bLoop = TRUE;
				MSG msg;
				while (bLoop && GetMessage(&msg, hwnd, 0, 0))
				{
					TranslateMessage(&msg);

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

							pt.x += org.x;
							pt.y += org.y;

							SizeContent(hDC, pt.x);
							m_pUI->Invalidate();
							m_pUI->OnSize();
						}
						break;

					default:
						DispatchMessage(&msg);
						break;
					}
				}

				ReleaseCapture();

				*pVal = this;
				return 0;
			}
		}
	}

	int y = 0;

// Children
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CGridItem* pChild = (CGridItem*)m_childList.GetNext(pos);

		POINT childpoint = point;
		childpoint.y -= y;
		childpoint.x -= 0;

		POINT oldOrg;
		OffsetViewportOrgEx(hDC, 0, y, &oldOrg);

		int nClick = pChild->Click(hDC, childpoint, nFlags, bDblClk, pVal);

		SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

		if (*pVal)
			return nClick;

		y += pChild->m_size.cy;
	}

	*pVal = NULL;
#endif
	return 0;
}

}
