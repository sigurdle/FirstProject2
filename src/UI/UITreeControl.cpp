// UITreeControl.cpp : Implementation of CUITreeControl
#include "stdafx.h"
#include "UI.h"
#include "UITreeControl.h"

typedef HTHEME  (STDAPICALLTYPE *fOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (STDAPICALLTYPE *fCloseThemeData)(HTHEME hTheme);
typedef HRESULT (STDAPICALLTYPE *fDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);

extern fOpenThemeData uxOpenThemeData;
extern fCloseThemeData uxCloseThemeData;
extern fDrawThemeBackground uxDrawThemeBackground;

//static int m_thumbHeight = 0;
static int m_headerHeight = 18;

void DrawVStippledLine(HDC hDC, int x, int y1, int y2, COLORREF clr)
{
	for (int y = y1; y <= y2; y += 2)
	{
		SetPixelV(hDC, x, y, clr);
	}
}

void DrawHStippledLine(HDC hDC, int y, int x1, int x2, COLORREF clr)
{
	for (int x = x1; x <= x2; x += 2)
	{
		SetPixelV(hDC, x, y, clr);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTreeItem

STDMETHODIMP CUITreeControl::CTreeItem::GetText(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = _bstr_t(m_name).copy();
	return S_OK;
}

void CUITreeControl::CTreeItem::DeselectAll()
{
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CTreeItem* pItem = (CTreeItem*)(C2Obj*)m_childList.GetNext(pos);
		if (pItem->m_selected)
		{
			pItem->m_selected = FALSE;
			m_ownerCtl->Fire_ItemStateChange(pItem, 1, pItem->m_selected);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUITreeControl

int CUITreeControl::FinalConstruct()
{
	m_vert.CoCreateInstance(CLSID_UIScrollBar);
	m_vert->put_direction(1);
	IDispEventImpl<1, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_horz.CoCreateInstance(CLSID_UIScrollBar);
	m_horz->put_direction(0);
	IDispEventImpl<2, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);

	m_edit.CoCreateInstance(CLSID_UIEdit);

	m_hUxThemeLib = LoadLibrary("uxtheme.dll");
	if (m_hUxThemeLib)
	{
		uxOpenThemeData = (fOpenThemeData)GetProcAddress(m_hUxThemeLib, "OpenThemeData");
		uxCloseThemeData = (fCloseThemeData)GetProcAddress(m_hUxThemeLib, "CloseThemeData");
		uxDrawThemeBackground = (fDrawThemeBackground)GetProcAddress(m_hUxThemeLib, "DrawThemeBackground");

		m_hHeaderTheme = uxOpenThemeData(NULL, L"HEADER");
		m_hTreeViewTheme = uxOpenThemeData(NULL, L"TREEVIEW");
	}

	CComObject<CTreeItem>::CreateInstance(&m_pTree);
	m_pTree->AddRef();
	m_pTree->m_ownerCtl = this;

	return S_OK;
}

void CUITreeControl::FinalRelease()
{
	if (m_pTree)
	{
		FreeItem(m_pTree);
		m_pTree = NULL;
	}

	IDispEventImpl<1, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	IDispEventImpl<2, CUITreeControl, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);

	if (m_hHeaderTheme)
	{
		uxCloseThemeData(m_hHeaderTheme);
		m_hHeaderTheme = NULL;
	}

	if (m_hTreeViewTheme)
	{
		uxCloseThemeData(m_hTreeViewTheme);
		m_hTreeViewTheme = NULL;
	}

	if (m_hUxThemeLib)
	{
		FreeLibrary(m_hUxThemeLib);
		m_hUxThemeLib = NULL;
	}
}

void CUITreeControl::DrawColumnHeader(HDC hDC, CRect& rect, int nColumn)
{
	_bstr_t text = m_column[nColumn].m_name;

	if (text.length())
	{
		DrawText(hDC, text, text.length(), &rect, DT_SINGLELINE | DT_VCENTER);
	}
}

LRESULT CUITreeControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = m_hWnd;

	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axhorz.Create(hwnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axhorz.AttachControl(m_horz, &p);

	m_axvert.Create(hwnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axvert.AttachControl(m_vert, &p);

	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);

	_bstr_t faceName = lf.lfFaceName;

	FONTDESC	fd;
	fd.cbSizeofstruct = sizeof(fd);
	fd.lpstrName = faceName;
	fd.cySize.Lo = 9*10000;
	fd.cySize.Hi = 0;
	fd.sWeight = lf.lfWeight;
	fd.sCharset = lf.lfCharSet;
	fd.fItalic = lf.lfItalic;
	fd.fUnderline = lf.lfUnderline;
	fd.fStrikethrough = lf.lfStrikeOut;

	HRESULT hr = OleCreateFontIndirect(&fd, IID_IFontDisp, (void**)&m_pFont);
	ATLASSERT(SUCCEEDED(hr));

	return 0;
}

LRESULT CUITreeControl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	EndEdit(FALSE);
	m_pFont.Release();
	return 0;
}

HRESULT CUITreeControl::OnDraw(ATL_DRAWINFO& di)
{
	if (m_hWnd == NULL) return 0;

	HDC hDC = di.hdcDraw;
	CDCHandle dc(hDC);

	CRect& client = *(CRect*)di.prcBounds;

	CRect	clip;
	GetClipBox(hDC, &clip);

//	FillSolidRect(hDC, 0, 0, client.right, m_headerHeight, RGB(255, 0, 0));

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	//FillSolidRect(hDC, &client, RGB(255, 0, 0));

	Draw3DRect(hDC, &client, RGB(0,0,0), RGB(0,0,0));	// Black frame

	OffsetViewportOrgEx(hDC, 1, 0, NULL);

	SetBkMode(hDC, TRANSPARENT);

	if (TRUE)	// Header
	{
		{
			CRect	headerRect;
			headerRect.top = 1;
			headerRect.bottom = headerRect.top+m_headerHeight-2;
			headerRect.left = 0;

			for (int n = 0; n < m_column.GetSize(); n++)
			{
				if (m_column[n].m_bVisible)
				{
					headerRect.right = headerRect.left + m_column[n].m_width;

					CRect rc = headerRect;

					if (m_hHeaderTheme)
					{
						uxDrawThemeBackground(m_hHeaderTheme,
							 dc.m_hDC,
							 HP_HEADERITEM,
							 HIS_NORMAL,
							 &rc,
							 NULL);
					}
					else
					{
						dc.FillSolidRect(rc.right-1, rc.top, 1, rc.Height(), RGB(0,0,0));
						rc.right--;

						dc.FillSolidRect(rc.left, rc.top, 1, rc.Height(), GetSysColor(COLOR_3DHILIGHT));
						dc.FillSolidRect(rc.left+1, rc.top, rc.Width()-1, 1, GetSysColor(COLOR_3DHILIGHT));

						dc.FillSolidRect(rc.left+1, rc.bottom-1, rc.Width()-1, 1, GetSysColor(COLOR_3DSHADOW));
						dc.FillSolidRect(rc.right-1, rc.top+1, 1, rc.Height()-1, GetSysColor(COLOR_3DSHADOW));

				//	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
						rc.InflateRect(-1,-1);

		/*
					Draw3DRect(hDC, &rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
					rc.InflateRect(-1,-1);
		*/

						dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));
						rc.InflateRect(-1,-1);

						rc.left += 4;
						rc.right -= 4;
					}

					DrawColumnHeader(hDC, rc, n);

					headerRect.left += m_column[n].m_width;
				}
			}

		// Draw an empty column to the right of window
			headerRect.right = client.right;
		//	dc.FillSolidRect(&headerRect, GetSysColor(COLOR_BTNFACE)/*grayColor*/);
		//	dc.Draw3dRect(headerRect.left, headerRect.top, headerRect.Width(), headerRect.Height(), GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW)/*darkGrayColor*/);
			//Draw3DRect(hDC, headerRect.left+1, headerRect.top+1, headerRect.Width()-2, headerRect.Height()-2, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW)/*darkGrayColor*/);

			CRect rc = headerRect;
			if (m_hHeaderTheme)
			{
				uxDrawThemeBackground(m_hHeaderTheme,
					 dc.m_hDC,
					 HP_HEADERITEM,
					 HIS_NORMAL,
					 &rc,
					 NULL);
			}
			else
			{
				dc.FillSolidRect(rc.left, rc.top, 1, rc.Height(), GetSysColor(COLOR_3DHILIGHT));
				dc.FillSolidRect(rc.left+1, rc.top, rc.Width()-1, 1, GetSysColor(COLOR_3DHILIGHT));

				dc.FillSolidRect(rc.left+1, rc.bottom-1, rc.Width()-1, 1, GetSysColor(COLOR_3DSHADOW));
				dc.FillSolidRect(rc.right-1, rc.top+1, 1, rc.Height()-1, GetSysColor(COLOR_3DSHADOW));

				rc.InflateRect(-1,-1);

				dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));

			// dividing black line at bottom
				dc.FillSolidRect(0, m_headerHeight-1, client.right, 1, RGB(0,0,0));
			}
		}
	}

	dc.FillSolidRect(0, m_headerHeight, client.right, client.bottom- m_headerHeight, RGB(255, 255, 255)/*lightColor*/);

	long scrollposX; m_horz->get_pos(&scrollposX);
	long scrollposY; m_vert->get_pos(&scrollposY);

	int state = SaveDC(hDC);

	int icon_cx;
	int icon_cy;
	ImageList_GetIconSize(m_hImageList, &icon_cx, &icon_cy);

	BOOL bHasButtons = TRUE;
	BOOL bHasLines = TRUE;
	BOOL bLinesAtRoot = TRUE;

	IntersectClipRect(hDC,
		0, m_headerHeight,
		client.right -  GetSystemMetrics(SM_CXVSCROLL),
		client.bottom-16);

	POINT oldOrg;
	OffsetViewportOrgEx(hDC, -scrollposX, m_headerHeight -scrollposY, &oldOrg);

	if (bLinesAtRoot && bHasLines)
	{
	// TODO, draw this in right column
		int count = m_pTree->CountExpanded(1);
		int height = count*m_ItemHeight;

		DrawVStippledLine(hDC, 3+4, m_ItemHeight/2, height-m_ItemHeight/2, m_clrLines);
	}

	int y = 0;

	C2Obj* pParentItem = m_pTree;
	UPOSITION pos = pParentItem->GetHeadPosition();

	int nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		CTreeItem* pItem = (CTreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		SetTextColor(hDC, RGB(0,0,0));
		SetBkMode(hDC, TRANSPARENT);

		CRect columnClip;
		columnClip.top = y;
		columnClip.bottom = y+m_ItemHeight;
		columnClip.left = 0;

		for (int n = 0; n < m_column.GetSize(); n++)
		{
			SetTextColor(hDC, RGB(0,0,0));
			SetBkMode(hDC, TRANSPARENT);

			if (m_column[n].m_bVisible)
			{
				columnClip.right = columnClip.left + m_column[n].m_width;

				_bstr_t itemColumnText;
				if (m_pSite)
				{
					BSTR b;
					m_pSite->GetItemText(pItem->m_itemData, n, &b);
					if (b) itemColumnText = _bstr_t(b, false);
				}

				if (n == 0 && itemColumnText.length() == 0)
				{
					itemColumnText = pItem->m_name;
				}

				CRect trect = columnClip;
				if (n == 0)
				{
					trect.left += (level-1)*m_Indentation;
					if (bLinesAtRoot) trect.left += m_Indentation;

					if (bHasLines)
					{
						if (pItem->CanExpand() && pItem->m_expanded)
						{
							int count = pItem->CountExpanded(1);
							int height = count*m_ItemHeight;

						//	int height = pItem->m_childList.GetCount()*m_ItemHeight;


							int x = trect.left + 3+4;
							x += m_Indentation;
							DrawVStippledLine(hDC, x, y+m_ItemHeight, y+height+m_ItemHeight/2, m_clrLines);
						}

						DrawHStippledLine(hDC, y+m_ItemHeight/2, trect.left+3+4+1, trect.left+m_Indentation, m_clrLines);
					}

					if (bHasButtons)
					{
						if (pItem->CanExpand())
						{
							CRect rc;
							rc.left = trect.left + 3;
							rc.top = trect.top + (m_ItemHeight-8)/2;
							rc.right = rc.left + 8+1;
							rc.bottom = rc.top + 8+1;

							if (m_hTreeViewTheme)
							{
								uxDrawThemeBackground(m_hTreeViewTheme,
									 dc.m_hDC,
									 TVP_GLYPH,
									 (pItem->m_expanded)? GLPS_OPENED: GLPS_CLOSED,
									 &rc,
									 NULL);
							}
							else
							{
								int l = trect.left + 3;
								int t = trect.top + (m_ItemHeight-8)/2;
								Rectangle(hDC, l, t, l+8+1, t+8+1);

								if (pItem->m_expanded)
								{
									MoveToEx(hDC, l+2, t+4, NULL);
									LineTo(hDC, l+6+1, t+4);
								}
								else
								{
									MoveToEx(hDC, l+2, t+4, NULL);
									LineTo(hDC, l+6+1, t+4);

									MoveToEx(hDC, l+4, t+2, NULL);
									LineTo(hDC, l+4, t+6+1);
								}
							}
						}
					}

					trect.left += m_Indentation;

					if (m_hImageList)
					{
						if (pItem->m_iIndex >= 0)
						{
							ImageList_Draw(m_hImageList, pItem->m_iIndex, hDC, trect.left, trect.top + (trect.Height()-icon_cy)/2, ((pItem->m_selected & 1)? ILD_SELECTED: 0) | ILD_TRANSPARENT);
						}

						trect.left += 18;
					}
				}

				if (itemColumnText.length())
				{
					int oldBk = SetBkMode(hDC, TRANSPARENT);
					COLORREF oldTextClr = GetTextColor(hDC);

					if (n == 0)
					{
						BOOL bHilight = FALSE;

						if (pItem != m_pActive || m_axedit.m_hWnd == NULL)
						{
							if ((pItem->m_selected & 1) || (pItem->m_selected & 2))	// selected
							{
								bHilight = TRUE;
							}

							SIZE size;
							GetTextExtentPoint32(hDC, itemColumnText, itemColumnText.length(), &size);

							CRect trect2 = trect;
							trect2.right = trect.left+size.cx+4;
							if (trect2.right > trect.right) trect2.right = trect.right;

							if (bHilight)	// selected
							{
								SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
								FillSolidRect(hDC, &trect2, GetSysColor(COLOR_HIGHLIGHT));
							}
							else if (pItem->m_selected & 2)	// drop hilight
							{
								SetTextColor(hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
								FillSolidRect(hDC, &trect2, GetSysColor(COLOR_HIGHLIGHT));
							}
							else
							{
								SetTextColor(hDC, RGB(0, 0, 0));
							}

							DrawText(hDC, itemColumnText, itemColumnText.length(), &trect2, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

							if (pItem == m_pActive)
							{
								DrawFocusRect(hDC, &trect2);
							}
						}
					}
					else
					{
						DrawText(hDC, itemColumnText, itemColumnText.length(), &trect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
					}

					SetBkMode(hDC, oldBk);
					SetTextColor(hDC, oldTextClr);
				}

				columnClip.left += m_column[n].m_width;
			}
		}

		y += m_ItemHeight;
	}

	SetViewportOrgEx(hDC, oldOrg.x, oldOrg.y, NULL);

	RestoreDC(hDC, state);

	SelectObject(hDC, hOldFont);

	return S_OK;
}

void CUITreeControl::EndEdit(BOOL bReturn)
{
	if (m_axedit)
	{
		_bstr_t text;
		if (bReturn)
		{
			BSTR btext;
			m_edit->GetText(&btext);
			text = _bstr_t(btext, false);
		}

		IDispEventImpl<3, CUITreeControl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);
		m_axedit.DestroyWindow();

		if (bReturn)
		{
			Fire_EndLabelEdit(m_pActive, text);
		}
	}
}

void CUITreeControl::SizeEdit()
{
	BSTR btext;
	m_edit->GetText(&btext);
	_bstr_t text = _bstr_t(btext, false);

	HDC hDC = CreateCompatibleDC(NULL);

	CComQIPtr<IFont> font = m_pFont;
	HFONT hFont;
	font->get_hFont(&hFont);

	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	SIZE size;
	GetTextExtentPoint32(hDC, text, text.length(), &size);

	SIZE charsize;
	GetTextExtentPoint32(hDC, " ", 1, &charsize);

	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	int width = 2 + size.cx + charsize.cx*3;

	m_axedit.SetWindowPos(NULL, 0, 0, width, 16+2, SWP_NOZORDER | SWP_NOMOVE);
}

HRESULT __stdcall CUITreeControl::OnEditChange()
{
	SizeEdit();
	return S_OK;
}

HRESULT __stdcall CUITreeControl::OnEditChar(WCHAR ch)
{
	if (ch == '\n')
	{
	//MessageBeep(-1);
		EndEdit(TRUE);
	}

	return S_OK;
}

LRESULT CUITreeControl::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetFocus();

	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, FALSE);

	return 0;
}

LRESULT CUITreeControl::OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetFocus();

	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 1, FALSE);

	return DefWindowProc(uMsg, wParam, lParam);
	return 0;
}

LRESULT CUITreeControl::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	Fire_ContextMenu(point.x, point.y);
	return 0;
}

LRESULT CUITreeControl::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	OnButtonDown(wParam, point, 0, TRUE);

	return 0;
}

void CUITreeControl::OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk)
{
	EndEdit(TRUE);

//	point.x -= 1;

	if (!m_dragging)
	{
		/*
		if (point.y < m_thumbHeight)
		{
		}
		else
		*/
		{
			m_pane = -1;
			
			long scrollposY; m_vert->get_pos(&scrollposY);
			long scrollposX = 0;

			int x = 0;

			CRect paneRect;
			paneRect.left = 0;
			
			for (int i = 0; i < m_column.GetSize(); i++)
			{
				if (m_column[i].m_bVisible)
				{
					x += m_column[i].m_width;
					
					if (point.y >= 0 && point.y < m_headerHeight)
					{
						if (m_column[i].m_bSizeable)
						{
							if (abs(point.x - x) < 4)
							{
								m_dragging = 1;
								m_pane = i;
								break;
							}
						}
					}

					if (point.x < x)
					{
						m_pane = i;
						break;
					}

					paneRect.left = x;
				}
			}
			
			if (m_pane >= 0)
			{
				paneRect.right = paneRect.left + m_column[m_pane].m_width;

				if (point.y < m_headerHeight)
				{
					m_oldpt = point;
					m_oldwidth = m_column[m_pane].m_width;
				}
				else
				{
					DWORD bInsideExpand;
					CComPtr<IUITreeItem> pIFNode;
					HitTest(point, &bInsideExpand, &pIFNode);
					CTreeItem* pFNode = static_cast<CTreeItem*>(pIFNode.p);

					if (pFNode)
					{
						if (bInsideExpand)
						{
							if (pFNode->CanExpand())
							{
								long bCancel = VARIANT_FALSE;
								Fire_ItemExpanding(pFNode, !pFNode->m_expanded, &bCancel);

								if (TRUE)
								{
									Expand(pFNode, TV_TOGGLE, NULL);
								}
							}
						}
						else
						{
							DWORD oldstate = pFNode->m_selected;
							pFNode->m_selected = FALSE;	// Temporarily set it to deselected

							if (!(nFlags & MK_SHIFT) && m_pActive)
							{
								((CTreeItem*)m_pActive->m_parent)->DeselectAll();
							}

							pFNode->m_selected |= 1;	// Set it (back) to selected
							if ((oldstate & 1) == 0)	// previously deselected
							{
								Fire_ItemStateChange(pFNode, oldstate, pFNode->m_selected);
							}

							if (bDblClk)
							{
								if (iButton == 0)
								{
									m_pActive = pFNode;

									InvalidateRect(NULL, TRUE);
									UpdateWindow();

									Fire_DblClick(m_pActive);
								}
							}
							else
							{
								if (pFNode != m_pActive)
								{
									m_pActive = pFNode;

									InvalidateRect(NULL, TRUE);
									UpdateWindow();

									Fire_Click(m_pActive);
								}
								else
								{
									if (m_pane == 0)
									{
										if (iButton == 0)
										{
											VARIANT_BOOL val;
											Fire_BeginLabelEdit(m_pActive, &val);

											if (TRUE)
											{
												EditLabel(m_pActive, NULL);
											}
										}
									}
								}
							}
	#if 0
							if (iButton == 0)
							{
								if (pFNode->m_type == 2)
								{
									CSiteFile* pFile = (CSiteFile*)pFNode;
									CSiteDir* pDir = (CSiteDir*)pFile->m_parent;

									if (bDblClk)
									{
										/*
										TCHAR pathName[512];
										_makepath(pathName, NULL, pDir->m_pathName, pFile->m_name, NULL);

										BOOL success;
										gApp->OpenDocument(_bstr_t(pathName), &success);
										*/
									}
									else
									{
	#if 0
										HGLOBAL hData = BuildSelectedFilesClipboard();
										if (hData)
										{
											CMyDropSource*  dropSource = new CMyDropSource;
											CMyDataObject* dataObject = new CMyDataObject;

											STGMEDIUM	stg = {0};
											stg.tymed = TYMED_HGLOBAL;
											stg.hGlobal = hData;
											stg.pUnkForRelease = NULL;
											
											FORMATETC	etc = {0};
											etc.cfFormat = CF_HDROP;//CF_UNICODETEXT;//49285;//RegisterClipboardFormat(CFSTR_SHELLURL);//CF_TEXT;
											etc.tymed = TYMED_HGLOBAL;
											etc.ptd = NULL;
											etc.dwAspect = DVASPECT_CONTENT;
											etc.lindex = -1;

											dataObject->SetData(&etc, &stg, TRUE);

											DWORD dropEffect = 0;
											HRESULT hr = ::DoDragDrop(dataObject, dropSource, DROPEFFECT_LINK | DROPEFFECT_COPY | DROPEFFECT_MOVE, &dropEffect);

											if (hr == DRAGDROP_S_DROP)
											{
												if (dropEffect/* & DROPEFFECT_MOVE*/)
												{
												}
											}

											GlobalFree(hData);

										//	delete dataObject;
										//	delete dropSource;

		#if 0
											COleDataSource source;
											source.CacheGlobalData(CF_HDROP, hData, NULL);

											if (source.DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_MOVE, NULL, NULL) == DROPEFFECT_COPY)
											{
											}

											source.Empty();
		#endif
														
											GlobalFree(hData);
										}
	#endif
									}
								}
							}
							else	// right-button
							{
								CComQIPtr<IUIContextManager> uiManager;
								gApp->get_uiManager(&uiManager);

								CComQIPtr<IMenuItem> menu;
								uiManager->FindMenu(ID_SITEFILES, &menu);
								if (menu)
								{
									CComQIPtr<IUIWnd> uiwnd;
									QueryInterface(IID_IUIWnd, (void**)&uiwnd);

									POINT scrpoint = point;
									ClientToScreen(&scrpoint);

									IID selectedID;
									menu->PopupMenu(uiwnd, NULL, scrpoint, 0, &selectedID);
								}
							}
	#endif
						}
					}
					else
					{
						if (!(nFlags & MK_SHIFT) && m_pActive)
						{
							((CTreeItem*)m_pActive->m_parent)->DeselectAll();
						}

						m_pActive = NULL;

						InvalidateRect(NULL, TRUE);
					}
				}
			}
		}

		if (m_dragging)
		{
			SetCapture();
			
			if (m_dragging == 100)
			{
			//	m_bWasInside = FALSE;
			//	OnMouseMove(nFlags, point);
			}
			else
			{
			//	if (m_dragging == 10)
			//		OnMouseMove(nFlags, point);
			//	SetTimer(1, 50, NULL);
			}
		}
	}
}

LRESULT CUITreeControl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_hWnd)
	{
		POINT point;
		point.x = (short)LOWORD(lParam);
		point.y = (short)HIWORD(lParam);

	//	point.x -= 1;

		if (m_dragging)
		{
			int width = m_oldwidth + (point.x-m_oldpt.x);
			m_oldwidth = width;

			if (width < 4) width = 4;
			else if (width > 800) width = 800;

			if (width != m_column[m_pane].m_width)
			{
				m_column[m_pane].m_width = width;
				Invalidate();
			}

			m_oldpt = point;
		}
	}

	return 0;
}

LRESULT CUITreeControl::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;
	}

	return 0;
}

LRESULT CUITreeControl::OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HWND hwnd = (HWND) wParam;       // handle to window with cursor 
	int nHittest = LOWORD(lParam);  // hit-test code 
	UINT wMouseMsg = HIWORD(lParam); // mouse-message identifier 

	if (nHittest == HTCLIENT)
	{
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);

		if (point.y < m_headerHeight)
		{
			int pane = -1;
			
			long scrollposY; m_vert->get_pos(&scrollposY);
			long scrollposX = 0;

			int x = 0;

			CRect paneRect;
			paneRect.left = 0;

			for (int i = 0; i < m_column.GetSize(); i++)
			{
				if (m_column[i].m_bVisible)
				{
					x += m_column[i].m_width;
					
					if (m_column[i].m_bSizeable)
					{
						if (abs(point.x - x) < 4)
						{
							pane = i;
							break;
						}
					}

					paneRect.left = x;
				}
			}

			if (pane >= 0)
			{
				::SetCursor(::LoadCursor(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDC_RESIZECOLUMN)));
				return TRUE;
			}
		}
	}

	return DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CUITreeControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect	client;
	GetClientRect(&client);

	int cx = client.Width();
	int cy = client.Height();

	int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
	int sbHeight = GetSystemMetrics(SM_CXVSCROLL);

	int top = m_headerHeight;

	::MoveWindow(m_axhorz.m_hWnd, 0, cy-sbHeight, cx-sbWidth, sbHeight, TRUE);
	::MoveWindow(m_axvert.m_hWnd, cx-sbWidth, top, sbWidth, cy-top-sbHeight, TRUE);

	::ShowWindow(m_axhorz.m_hWnd, SW_SHOW);
	::ShowWindow(m_axvert.m_hWnd, SW_SHOW);

	OnSize();
	InvalidateRect(NULL, TRUE);

	return 0;
}

void CUITreeControl::OnSize()
{
	if (m_hWnd)
	{
		ResetVScrollSize();
	}
}

void CUITreeControl::ResetVScrollSize()
{
	CRect client;
	GetClientRect(&client);

	int top = m_headerHeight;

	int height = 0;

	C2Obj* pParentItem = m_pTree;
	UPOSITION pos = pParentItem->GetHeadPosition();
	int nextlevel = 0;
	while (pos)
	{
		CTreeItem* pItem = (CTreeItem*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);
		height += m_ItemHeight;
	}

	m_vert->SetInfo(0, height, client.Height()-top-16);
}

HRESULT __stdcall CUITreeControl::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	CRect client;
	GetClientRect(&client);

	int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
	int sbHeight = GetSystemMetrics(SM_CXVSCROLL);

	CRect rect(0, m_headerHeight,
		client.Width() - sbWidth, client.bottom-sbHeight);

	m_vert->put_pos(pos);
	ScrollWindow(0, oldPos-pos, &rect, &rect);

	return S_OK;
}

HRESULT __stdcall CUITreeControl::OnHorzScroll(long code, long pos)
{
	long oldPos; m_horz->get_pos(&oldPos);

//	HWND hwnd;
//	get_hwnd(&hwnd);

	CRect client;
	GetClientRect(&client);

	int sbWidth = GetSystemMetrics(SM_CYHSCROLL);
	int sbHeight = GetSystemMetrics(SM_CXVSCROLL);

	CRect rect(0, m_headerHeight,
		client.Width() - sbWidth, client.bottom-sbHeight);

	m_horz->put_pos(pos);
	ScrollWindow(oldPos-pos, 0, &rect, &rect);

	return S_OK;
}

STDMETHODIMP CUITreeControl::InsertColumn(long index, BSTR name, long width, BOOL bSizeable, BOOL bVisible, long *pVal)
{
	CTreeColumn column;
	column.m_name = name;
	column.m_width = width;
	column.m_bSizeable = bSizeable;
	column.m_bVisible = bVisible;

	if (index >= 0)
		m_column.InsertAt(index, column);
	else
		m_column.Add(column);

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::CreateItem(/*[in]*/ DWORD itemData, /*[in]*/ BSTR name, /*[in]*/ long iIndex, /*[in]*/ long cChildren, /*[out,retval]*/ IUITreeItem* *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CComObject<CTreeItem>* pItem;
	CComObject<CTreeItem>::CreateInstance(&pItem);
	
	pItem->m_ownerCtl = this;
	pItem->m_itemData = itemData;
	pItem->m_name = name;
	pItem->m_iIndex = iIndex;
	pItem->m_cChildren = cChildren;

	*pVal = pItem;
	(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::InsertItem(DWORD itemData, IUITreeItem* parentItem, IUITreeItem* beforeItem, BSTR name, long iIndex, long cChildren, IUITreeItem* *pVal)
{
	ATLASSERT(pVal != NULL);
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pParent = (CTreeItem*)parentItem;
	if (pParent == NULL)
		pParent = m_pTree;

	CTreeItem* pBefore = (CTreeItem*)beforeItem;

	UPOSITION beforepos = NULL;
	if (pBefore)
	{
		beforepos = pParent->m_childList.Find((C2Obj*)pBefore);
		if (beforepos == NULL)
			return E_INVALIDARG;
	}

	CComObject<CTreeItem>* pItem;
	CComObject<CTreeItem>::CreateInstance(&pItem);
	pItem->AddRef();
	
	pItem->m_ownerCtl = this;
	pItem->m_itemData = itemData;
	pItem->m_name = name;
	pItem->m_iIndex = iIndex;
	pItem->m_cChildren = cChildren;

	pItem->m_parent = pParent;
	if (beforepos)
		pParent->m_childList.InsertBefore(beforepos, (C2Obj*)pItem);
	else
		pParent->m_childList.AddTail((C2Obj*)pItem);

	*pVal = pItem;
	(*pVal)->AddRef();

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

void CUITreeControl::FreeItem(CTreeItem* pItem)
{
	if (m_pActive == pItem) m_pActive = NULL;

	while (!pItem->m_childList.IsEmpty())
	{
		CTreeItem* pChild = (CTreeItem*)(C2Obj*)pItem->m_childList.RemoveHead();
		FreeItem(pChild);
	}

	pItem->Release();
}

STDMETHODIMP CUITreeControl::DeleteItem(IUITreeItem* item)
{
	if (item == NULL) return E_INVALIDARG;

	CTreeItem* pItem = (CTreeItem*)item;

	UPOSITION pos = pItem->m_parent->m_childList.Find((C2Obj*)pItem);
	ATLASSERT(pos);

	pItem->m_parent->m_childList.RemoveAt(pos);

	FreeItem(pItem);

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::SetSite(IUITreeControlSite *pSite)
{
	m_pSite = pSite;

	return S_OK;
}

STDMETHODIMP CUITreeControl::get_hImageList(DWORD *pVal)
{
	*pVal = (DWORD)m_hImageList;
	return S_OK;
}

STDMETHODIMP CUITreeControl::put_hImageList(DWORD newVal)
{
	m_hImageList = (HIMAGELIST)newVal;
	return S_OK;
}

STDMETHODIMP CUITreeControl::get_Indentation(long *pVal)
{
	*pVal = m_Indentation;
	return S_OK;
}

STDMETHODIMP CUITreeControl::put_Indentation(long newVal)
{
	if (m_Indentation != newVal)
	{
		m_Indentation = newVal;
		if (m_Indentation < MinIndent) m_Indentation = MinIndent;

		if (m_hWnd)
		{
			OnSize();	// TODO, only size horizontally
			InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetItemInfo(IUITreeItem* item, DWORD *itemdata, long *iIndex, long *cChildren)
{
	CTreeItem* pItem = (CTreeItem*)item;
	if (itemdata) *itemdata = pItem->m_itemData;
	if (iIndex) *iIndex = pItem->m_iIndex;
	if (cChildren) *cChildren = pItem->m_cChildren;

	return S_OK;
}

STDMETHODIMP CUITreeControl::SetItemInfo(IUITreeItem* item, DWORD itemdata, long iIndex, long cChildren)
{
	CTreeItem* pItem = (CTreeItem*)item;
	pItem->m_itemData = itemdata;
	pItem->m_iIndex = iIndex;
	pItem->m_cChildren = cChildren;

	Invalidate();

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetParentItem(IUITreeItem* item, IUITreeItem* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	if (item == NULL) return E_INVALIDARG;

	CTreeItem* pItem = (CTreeItem*)item;
	*pVal = (CTreeItem*)pItem->m_parent;
	if (*pVal)
		(*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::ResetContent(IUITreeItem* item)
{
	ATLASSERT(m_pTree);

	if (item == NULL)
	{
		if (!m_pTree->m_childList.IsEmpty())
		{
			FreeItem(m_pTree);
			m_pTree = NULL;
			//m_pTree->Release();

			CComObject<CTreeItem>::CreateInstance(&m_pTree);
			m_pTree->AddRef();
			m_pTree->m_ownerCtl = this;

			m_pActive = NULL;
			// Fire_
		}
	}
	else
	{
		CTreeItem* pItem = (CTreeItem*)item;

	// Remove children
		while (!pItem->m_childList.IsEmpty())
		{
			CTreeItem* pChild = (CTreeItem*)(C2Obj*)pItem->m_childList.RemoveHead();
			FreeItem(pChild);
		}
	}

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetNextSiblingItem(IUITreeItem* item, IUITreeItem* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;
	UPOSITION pos = pItem->m_parent->m_childList.Find((C2Obj*)pItem);

	pItem->m_parent->m_childList.GetNext(pos);

	if (pos)
	{
		*pVal = (CTreeItem*)(C2Obj*)pItem->m_parent->m_childList.GetAt(pos);
		(*pVal)->AddRef();
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetPrevSiblingItem(IUITreeItem* item, IUITreeItem* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;
	UPOSITION pos = pItem->m_parent->m_childList.Find((C2Obj*)pItem);

	pItem->m_parent->m_childList.GetPrev(pos);
	if (pos)
	{
		*pVal = (CTreeItem*)(C2Obj*)pItem->m_parent->m_childList.GetAt(pos);
		(*pVal)->AddRef();
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetSelectedItem(IUITreeItem* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_pActive;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::SetSelectedItem(IUITreeItem* item)
{
	if (m_pActive != item)
	{
		if (m_pActive)	// Deselect all
		{
			((CTreeItem*)m_pActive->m_parent)->DeselectAll();
		}

		m_pActive = (CTreeItem*)item;

		if (m_pActive)
		{
			if (!(m_pActive->m_selected & 1))
			{
				m_pActive->m_selected |= 1;
				Fire_ItemStateChange(m_pActive, 0, m_pActive->m_selected);
			}
		}

		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetRootItem(IUITreeItem* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = m_pTree;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetFirstChildItem(IUITreeItem* item, IUITreeItem* *pVal)
{
	if (item == NULL) return E_POINTER;
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;

	if (!pItem->m_childList.IsEmpty())
	{
		*pVal = (CTreeItem*)(C2Obj*)pItem->m_childList.GetHead();
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetLastChildItem(IUITreeItem* item, IUITreeItem* *pVal)
{
	if (item == NULL) return E_POINTER;
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;

	if (!pItem->m_childList.IsEmpty())
	{
		*pVal = (CTreeItem*)(C2Obj*)pItem->m_childList.GetTail();
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CUITreeControl::SetItemState(IUITreeItem* item, DWORD state)
{
	if (item == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;
	if (pItem->m_selected != state)
	{
		DWORD oldState = pItem->m_selected;
		pItem->m_selected = state;
		Fire_ItemStateChange(pItem, oldState, state);

		Invalidate();
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetItemState(IUITreeItem* item, DWORD *pVal)
{
	if (item == NULL) return E_POINTER;
	if (pVal == NULL) return E_POINTER;

	CTreeItem* pItem = (CTreeItem*)item;
	*pVal = pItem->m_selected;

	return S_OK;
}

#if 0
STDMETHODIMP CUITreeControl::SetExpanded(DWORD item, VARIANT_BOOL bExpanded)
{
	CTreeItem* pItem = (CTreeItem*)item;
	if ((pItem->m_expanded == 0) != (bExpanded == 0))
	{
		pItem->m_expanded = bExpanded;

		OnSize();
		Invalidate();
	}

	return S_OK;
}
#endif

STDMETHODIMP CUITreeControl::SetRootItem(DWORD itemdata, IUITreeItem* *pItem)
{
	ATLASSERT(m_pTree != NULL);

	m_pTree->m_itemData = itemdata;
	if (pItem)
		(*pItem = m_pTree)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::HitTest(POINT point, DWORD* flags, IUITreeItem* *pItem)
{
	if (pItem == NULL) return E_POINTER;

	long scrollposY; m_vert->get_pos(&scrollposY);
	long scrollposX = 0;

	*pItem = NULL;
	if (flags) *flags = 0;

	if (point.y < m_headerHeight)
	{
	}
	else
	{
		POINT pt;
		pt.y = (point.y - (m_headerHeight)) + scrollposY;
		pt.x = point.x;

		C2Obj* pParentItem = m_pTree;//((CWebSite*)m_pDocument.p)->m_pRootDir;
		UPOSITION pos = pParentItem->GetHeadPosition();

		int topy;
		int y = 0;

		CTreeItem* pFNode = NULL;

		int levelx;

		int	nextlevel = 0;
		while (pos)
		{
			int level = nextlevel;
			CTreeItem* pItem = (CTreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

			levelx = level*m_Indentation;

			topy = y;

			y += m_ItemHeight;

			if (pt.y < y)
			{
				pFNode = pItem;
				break;
			}
		}

		if (pFNode)
		{
			BOOL bInsideExpand = ((pt.x >= levelx && pt.x < levelx+16)/* || bDblClk*/);
			if (flags) *flags = bInsideExpand;

			*pItem = pFNode;
			(*pItem)->AddRef();
		}
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetEditControl(IUIEdit **pEdit)
{
	if (pEdit == NULL) return E_POINTER;

	*pEdit = m_edit;
	if (*pEdit) (*pEdit)->AddRef();

	return S_OK;
}

STDMETHODIMP CUITreeControl::GetItemRect(IUITreeItem* item, long pane, VARIANT_BOOL bTextOnly, RECT *pRect)
{
	if (pRect == NULL) return E_POINTER;

	SetRectEmpty(pRect);

	long scrollposY; m_vert->get_pos(&scrollposY);
	
	BOOL bHasButtons = TRUE;
	BOOL bLinesAtRoot = TRUE;

	int y = m_headerHeight;
	y -= scrollposY;

	C2Obj* pParentItem = m_pTree;
	UPOSITION pos = pParentItem->GetHeadPosition();

	int nextlevel = 0;
	while (pos)
	{
		int level = nextlevel;
		CTreeItem* pItem = (CTreeItem*)(C2Obj*)pParentItem->Iterate(pParentItem, pos, nextlevel, FALSE);

		if ((CTreeItem*)item == pItem)
		{
			CRect columnClip;
			columnClip.top = y;
			columnClip.bottom = y+m_ItemHeight;
			columnClip.left = 0;

			if (pane == -1)
			{
			}
			else
			{
				_bstr_t itemColumnText;
				if (m_pSite)
				{
					BSTR b;
					m_pSite->GetItemText(pItem->m_itemData, pane, &b);
					itemColumnText = _bstr_t(b, false);
				}

				if (pane == 0 && itemColumnText.length() == 0)
				{
					itemColumnText = pItem->m_name;
				}

				for (int n = 0; n <= pane; n++)
				{
					columnClip.right = columnClip.left + m_column[n].m_width;
					if (n < pane)
						columnClip.left += m_column[n].m_width;
				}

				*pRect = columnClip;

				if (pane == 0)
				{
					pRect->left += (level-1)*m_Indentation;
					if (bLinesAtRoot) pRect->left += m_Indentation;

					pRect->left += m_Indentation;

					//if (bHasButtons) pRect->left += 18;
					if (m_hImageList) pRect->left += 18;
				}
			}

			break;
		}

		y += m_ItemHeight;
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::EditLabel(IUITreeItem* item, IUIEdit **ppEdit)
{
	if (m_pActive)
	{
		((CTreeItem*)m_pActive->m_parent)->DeselectAll();
	}

	m_pActive = (CTreeItem*)item;

	_bstr_t text;
	if (m_pSite)
	{
		BSTR btext;
		m_pSite->GetItemText(m_pActive->m_itemData, m_pane, &btext);
		text = _bstr_t(btext, false);
	}

	if (m_pane == 0 && text.length() == 0)
	{
		text = m_pActive->m_name;
	}

	CRect itemrect;
	GetItemRect(m_pActive, 0, FALSE, &itemrect);

	IUnknown* p;
	CRect rc = itemrect;
	rc.InflateRect(1, 1);
	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);

	SizeEdit();

	IDispEventImpl<3, CUITreeControl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);

	m_edit->put_font(m_pFont);
	m_edit->SetText(text);

	m_axedit.SetFocus();
	m_edit->SetSel(0, -1, VARIANT_FALSE);
	
	if (ppEdit)
	{
		*ppEdit = m_edit;
		(*ppEdit)->AddRef();
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::Expand(IUITreeItem* item, TVExpandCode code, VARIANT_BOOL *pSuccess)
{
	CTreeItem* pItem = (CTreeItem*)item;
	if (pItem == NULL)
	{
		if (pSuccess) *pSuccess = VARIANT_FALSE;
		return S_OK;
	}

	switch (code)
	{
	case TV_COLLAPSE:
		pItem->m_expanded = VARIANT_FALSE;
		break;

	case TV_EXPAND:
		pItem->m_expanded = VARIANT_TRUE;
		break;

	case TV_TOGGLE:
		pItem->m_expanded = !pItem->m_expanded;
		break;

	case TV_COLLAPSERESET:
		{
			pItem->m_expanded = VARIANT_FALSE;

		// Remove children
			while (!pItem->m_childList.IsEmpty())
			{
				CTreeItem* pChild = (CTreeItem*)(C2Obj*)pItem->m_childList.RemoveHead();
				FreeItem(pChild);
			}
		}
		break;

	default:
		if (pSuccess) *pSuccess = VARIANT_FALSE;
		return S_OK;
	}

	if (m_hWnd)
	{
		OnSize();
		InvalidateRect(NULL, TRUE);
	}

	if (pSuccess) *pSuccess = VARIANT_TRUE;

	return S_OK;
}

STDMETHODIMP CUITreeControl::get_ItemHeight(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ItemHeight;
	return S_OK;
}

STDMETHODIMP CUITreeControl::put_ItemHeight(long newVal)
{
	if (m_ItemHeight != newVal)
	{
		m_ItemHeight = newVal;
		if (m_ItemHeight <= 0) m_ItemHeight = 18;

		if (m_hWnd)
		{
			OnSize();
			InvalidateRect(NULL, TRUE);
		}
	}

	return S_OK;
}

STDMETHODIMP CUITreeControl::UpdateItem(IUITreeItem *item)
{
	// TODO, invalidate only items rect

	if (m_hWnd)
	{
		Invalidate();
	}

	return S_OK;
}
