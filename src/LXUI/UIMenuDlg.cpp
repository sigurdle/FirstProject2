#include "stdafx.h"

#if 0
//#include "UIT.h"
#include "LXUI.h"
#include "..\LHTML\LHTML2.h"

#include "LXUIDocument.h"	// TODO "..View.h"

#include "UIMenuDlg.h"

#include "PLXUIMenuItemElement.h"

#include "LXUIBoxWindow.h"
#include "..\LHTML\PImage.h"
#include "..\LHTML\LDOMElementImpl.h"
#include "..\LHTML\PElement.h"
#include "..\LHTML\HTMPElement.h"

#include "..\LHTML\HTMContext.h"
#include "..\LHTML\PBlockBox.h"

#if 0
///////////////////////////////////////////////////////////////////////////////////
// CShadowWnd

LRESULT CShadowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);

	return 0;
}

LRESULT CShadowWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CRect client;
	GetClientRect(&client);

	LPBITMAPV4HEADER m_lpBmi;

	HDC hDCScreen = ::GetDC(NULL);

	if (m_lpBmi = (LPBITMAPV4HEADER)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPV4HEADER)))
	{
		m_lpBmi->bV4Size = sizeof(BITMAPV4HEADER);
		m_lpBmi->bV4Width = client.Width();
		m_lpBmi->bV4Height = client.Height();
		m_lpBmi->bV4Planes = 1;
		m_lpBmi->bV4BitCount = 32;
		m_lpBmi->bV4V4Compression = BI_RGB;

		LPBYTE m_bmBits;
		HBITMAP m_hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, NULL, 0);
		if (m_hBitmap)
		{
			HDC m_hDC = CreateCompatibleDC(hDCScreen);
			SelectObject(m_hDC, m_hBitmap);

		//	Draw(m_hDC);

			{
				for (int y = 0; y < m_lpBmi->bV4Height; y++)
				{
					BYTE* p = (BYTE*)m_bmBits + (m_lpBmi->bV4Width*4)*(m_lpBmi->bV4Height-y-1);
					for (int x = 0; x < m_lpBmi->bV4Width; x++)
					{
						BYTE opacity = 255;

						if (x < 8) opacity = (opacity * (255*x/8)) / 255;
						else if (x > m_lpBmi->bV4Width-8) opacity = (opacity * (255*(m_lpBmi->bV4Width-x)/8)) / 255;

						if (y < 8) opacity = (opacity * (255*y/8)) / 255;
						else if (y > m_lpBmi->bV4Height-8) opacity = (opacity * (255*(m_lpBmi->bV4Height-y)/8)) / 255;

						//if (x < m_lpBmi->bV4Width-8)
						{
							p[0] = 0;
							p[1] = 0;
							p[2] = 0;
							p[3] = opacity;
						}

						p += 4;
					}
				}
			}

			BLENDFUNCTION bf;
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 255;
			bf.AlphaFormat = AC_SRC_ALPHA;

			SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);

			CRect wrect;
			GetWindowRect(&wrect);

			CPoint ptSrc(0,0);
			if (!UpdateLayeredWindow(m_hWnd,
				hDCScreen,//HDC hdcDst,
				&CPoint(wrect.left, wrect.top),//POINT* pptDst,
				&CSize(wrect.Width(), wrect.Height()),//SIZE* psize,
				m_hDC,
				&ptSrc,
				0,//COLORREF crKey,
				&bf,//BLENDFUNCTION* pblend,
				ULW_ALPHA//DWORD dwFlags
				))
			{
				ASSERT(0);
			}
		}
	}

	::ReleaseDC(NULL, hDCScreen);
#endif

	return 0;
}
#endif


#if 0
///////////////////////////////////////////////////////////////////////////////////
// CUIMenuDlg

int CUIMenuDlg::FinalConstruct()
{
	CComObject<CLXUIWindowImplImpl>::CreateInstance(&m_pOwnedWindow);
	m_pOwnedWindow->AddRef();

	m_pOwnedWindow->m_htmTree = this;
	return S_OK;
}

void CUIMenuDlg::FinalRelease()
{
	RemoveDispItems();

	if (m_pOwnedWindow)
	{
		m_pOwnedWindow->Release();
		m_pOwnedWindow = NULL;
	}
}

// virtual
void CUIMenuDlg::DistributeBlockChildren(CHTMFlowBlockContext* pC, double oparentwidth)
{
	CSize size;
	CalcLayout(LM_MRUWIDTH | LM_COMMIT, oparentwidth, &size);	// TODO, optimize this to work directly on the above m_items ??
	PlaceItems(pC);
}

#if 0
LRESULT CUIMenuDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	if (m_orientation != 0)	// ??
	{
		RemoveBoxesAndChildren();
		CSize size;
		CalcLayout(LM_MRUWIDTH | LM_COMMIT, client.right, &size);	// TODO, optimize this to work directly on the above m_items ??
		PlaceItems();
	}

	ASSERT(m_pBox);

	InvalidateRect(NULL, TRUE);


	return 0;
}
#endif

#if 0
STDMETHODIMP CUIMenuDlg::InitMenu(IMenuItem* menuItem, ICommandTarget* target, int orientation)
{
	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_orientation = orientation;
#if 0
	m_pCmdWnd = target;
#endif

	CreateItems(m_items);
	SizeDispItemsArray(m_orientation, m_items);

	return S_OK;
}
#endif

#if 0
STDMETHODIMP CUIMenuDlg::get_title(BSTR* pVal)
{
	ASSERT(m_menuItem != NULL);
	return m_menuItem->get_text(pVal);//*pVal = SysAllocString(L"Gradient");
}
#endif

STDMETHODIMP CUIMenuDlg::get_menuItem(IMenuItem **pVal)
{
	*pVal = m_menuItem;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

long CPopupWindow::TrackMenu2()
{
#if 0
//	ASSERT(m_bParentMsgLoop == FALSE);

//	m_bParentMsgLoop = TRUE;

//		m_pPrevActiveItem = NULL;

//		PopupActiveItem();

//		if (m_activeSubDlg)
	{
		m_pElement->m_bParentMsgLoop = TRUE;
		long result = 0;
		m_pElement->m_result = 0;

		MSG lastMsg;
		BOOL bLastMsg = FALSE;

#ifdef _DEBUG
		//MessageBeep(-1);
#endif

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
		{
			if (msg.message == WM_MOUSEMOVE ||
				msg.message == WM_LBUTTONDOWN ||
				msg.message == WM_RBUTTONDOWN)
			{
				HWND hWnd2 = WindowFromPoint(msg.pt);
				HWND hWnd = hWnd2;

				CPopupWindow* pMenu = NULL;
				do
				{
					pMenu = (CPopupWindow*)GetProp(hWnd, "menudlg");
					if (pMenu)
						break;

					hWnd = ::GetParent(hWnd);
				}
				while (hWnd);

				CPopupWindow* pTest = this;
				while (pTest)
				{
					if (pMenu == pTest)
						break;

					pTest = pTest->m_activeSubDlg;
				}
				if (pTest == NULL)
					pMenu = NULL;

				if (pMenu)
				{
					pMenu->SetCapture();
				}
				else
				{
					if (msg.message == WM_LBUTTONDOWN ||
						msg.message == WM_RBUTTONDOWN)
					{
						bLastMsg = TRUE;
						lastMsg = msg;
						//lastMsg.hwnd = hWnd2;

						result = -2;	// Cancel
						if (result != 0) break;
					}
				}
			}

			CUIMenuDlg* pMenu = NULL;

			if (msg.hwnd)
			{
				HWND hWnd = msg.hwnd;
				do
				{
					pMenu = (CUIMenuDlg*)GetProp(hWnd, "menudlg");
					if (pMenu)
						break;

					hWnd = ::GetParent(hWnd);
				}
				while (hWnd);
			}

			if (pMenu)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				result = m_pElement->m_result;
/*	// Had this previously instead of above
					{
						if (m_activeSubDlg)	// ?? When is this NULL ?
							m_activeSubDlg->get_result(&result);
					}
					*/
			}
			else
			{
				switch (msg.message)
				{
				case WM_PAINT:
				case WM_ERASEBKGND:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					break;

				case WM_ACTIVATE:
				case WM_NCACTIVATE:
				case WM_MOUSEACTIVATE:
					TranslateMessage(&msg);
					DispatchMessage(&msg);

				case WM_NCLBUTTONDOWN:
				case WM_NCLBUTTONDBLCLK:

					/*
				case WM_LBUTTONDOWN:
				case WM_LBUTTONDBLCLK:

				case WM_RBUTTONDOWN:
				case WM_RBUTTONDBLCLK:
				*/
					result = -2;	// Cancel

					bLastMsg = TRUE;
					lastMsg = msg;

					break;

				//	/*
				default:	// TODO remove
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				//	*/
				}
			}

			if (result > 0 && m_selectedID)
			{
#if 0	// TODO, have this
				ASSERT(m_pActiveItem);
#endif
			}
			if (result != 0) break;
		}

		ReleaseCapture();

		//long selectedID = 0;

		if (m_activeSubDlg)
		{
			//m_activeSubDlg->get_selectedID(&selectedID);

			ASSERT(0);
#if 0
			if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
				m_activeSubDlg->DestroyWindow();
#endif

			m_activeSubDlg->Release();
			m_activeSubDlg = NULL;
		}

#if 1
		MessageBeep(-1);
#endif

		if (result > 0 && m_selectedID)
		{
			ASSERT(m_pElement->m_pActiveItem);

#if 0	// TODO, have this
			DWORD menuType;
			m_pActiveItem->m_menuItem->get_type(&menuType);
			if (menuType & MF_POPUP)
			{
			// Set this menu items command to the selected command
				CComPtr<IUICommand> command;
				m_menuItem->m_uiManager->FindCommand(m_selectedID, &command);
				if (command)
				{
					m_pActiveItem->m_menuItem->put_command(command);
				}
			}
#endif
		}

		m_pPrevActiveItem = NULL;
		SetActiveItem(NULL);

		if (m_bDestroy)//if (m_parentMenuDlg/*m_bParentMsgLoop*/)
		{
			DestroyWindow();
			//m_parentMenuDlg = NULL;//m_bParentMsgLoop = FALSE;
		}

		if (result > 0)
		{
		/*
			if (flags & TPM_RETURNCMD)
			{
				*iid = selectedID;
			}
			else if (pWnd || pTarget)
			*/
			{
				if (m_selectedID == 0)
				{
					/*
					HWND hWnd;
					m_pCmdWnd->get_hwnd(&hWnd);
					*/

				/*
					if (m_selectedID >= 0xF000)	// System menu
					{
						SendMessage(hWnd, WM_SYSCOMMAND,
							MAKEWPARAM(m_selectedID, 0), (LPARAM)NULL);
					}
				*/
				}
				else
				{
					// Fire event
					CComQIPtr<ILDOMDocumentEvent> documentEvent = CComQIPtr<CLDOMNodeImplImpl>(m_menuItem->m_pNode)->m_ownerDocument;
					ASSERT(documentEvent);
					if (documentEvent)
					{
						CComPtr<ILDOMUIEvent> evt;
						documentEvent->createEvent(L"UIEvents", (ILDOMEvent**)&evt);
						evt->initUIEvent(L"command",
							VARIANT_TRUE,	// bubbles
							VARIANT_TRUE,	// cancelable
							m_pOwnedWindow,//((CLXUIDocumentView*)m_menuItem->m_pView),	// viewArg
							m_selectedID->get_commandID()		// detail
							);

						ASSERT(evt);
						if (evt)
						{
							CComQIPtr<ILDOMEventTarget> eventTarget = m_selectedID->m_pNode;//static_cast<IBase*>(this);
							ASSERT(eventTarget);

							bool doDefault;
							eventTarget->dispatchEvent(evt, &doDefault);
						}
					}

#if 0
					CComQIPtr<ICommandTarget> target = m_pCmdWnd;

					if (target)
					{
						BOOL bHandled = FALSE;
						target->OnCmdMsg(m_selectedID, (result==1)? 0: BN_DBLCLK, NULL, &bHandled);
					}
#endif

				//	SendMessage(hWnd, WM_COMMAND,
				//		MAKEWPARAM(m_selectedID, 0), (LPARAM)NULL);
				}
			}
		}
		else if (bLastMsg)
		{
			TranslateMessage(&lastMsg);
			DispatchMessage(&lastMsg);
		}

		return result;
	}
#endif
	return 0;
}

void CUIMenuDlg::put_result(long newVal)
{
	m_result = newVal;

	if (m_parentMenuDlg)
	{
		m_parentMenuDlg->m_pElement->put_result(m_result);
	}
}

void CUIMenuDlg::SizeDispItem(int m_orientation, CDispItem* pItem)
{
#if 0
	HDC hDC = CreateCompatibleDC(NULL);
#endif

	/*
	LOGFONT lf;
	GetObject(hDC, sizeof(lf), &lf);
	lf.lfEscapement = 90*10;
	lf.lfOrientation = 90*10;

	HFONT hVerticalFont = CreateFontIndirect(&lf);
	ASSERT(hVerticalFont != NULL);
	*/

	/*
	HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

	HFONT hVerticalFont;
	
	if (m_orientation == 2)
	{
		hVerticalFont = CreateFont(16, 0, -90*10, -90*10, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Verdana");
		SelectObject(hDC, hVerticalFont);
	}
	else
	{
		SelectObject(hDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
	}

	_bstr_t text = pItem->m_text;
	*/

//	DWORD type;
//	pItem->m_menuItem->get_type(&type);

	//pItem->idCommand = ID;

//	m_textwidth = 0;

	if (m_orientation == 2)	// top to bottom - vertical text
	{
		ASSERT(0);

#if 0
		CRect rc(0,0,0,0);
		DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);
	//	CRect rc(0,0,40,80);

		pItem->m_size.cx = 2+rc.Height()+2;
		pItem->m_size.cy = 4+rc.Width()+4;
#endif
	}
	else if (m_orientation == 0)	// top-bottom
	{
		// nothing to do, use m_textWidth, m_itemHeight
	//	pItem->m_size.cx = m_textWidth;

			// Get max width
			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

	// TODO, remove these
				pItem->m_computedDisplayModel = DisplayModel_block_inside;
				pItem->m_computedDisplayRole = DisplayRole_block;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, 0x0fffffff);
				ASSERT(pC->m_pBlockBox);

				pItem->m_maxContentWidth = pC->m_maxx;

				pItem->m_maxWidth = pItem->m_maxContentWidth +
					pItem->m_computedBorderWidth[0] +
					pItem->m_computedMargin[0] +
					pItem->m_computedPadding[0] +

					pItem->m_computedBorderWidth[2] +
					pItem->m_computedMargin[2] +
					pItem->m_computedPadding[2];

				pItem->m_height = pItem->m_contentSize.Height +
					pItem->m_computedBorderWidth[1] +
					pItem->m_computedMargin[1] +
					pItem->m_computedPadding[1] +

					pItem->m_computedBorderWidth[3] +
					pItem->m_computedMargin[3] +
					pItem->m_computedPadding[3];

				delete pC;

			//	m_textwidth = max(m_textwidth, pItem->m_maxContentWidth);	// TODO Remove

				pItem->RemoveBoxesAndChildren();
			}

#if 0
		ASSERT(0);
#endif
#if 0
		pItem->m_size.cy = itemHeight;
#endif
	}
	else if (m_orientation == 1)	// left to right
	{
		ASSERT(0);
#if 0
		CRect rc(0,0,0,0);
		DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);

		pItem->m_size.cx = 4+rc.Width()+4;
		pItem->m_size.cy = 2+itemHeight+2;
#endif
	}
	else if (m_orientation == -1)	// rows and columns
	{
		if (pItem->fsStyle & TBSTYLE_SEP)
		{
			ASSERT(0);
#if 0
			pItem->m_size.cx = iBitmap;
			pItem->m_size.cy = 2+18+2;
#endif
		}
		else
		{
			// Get max width
			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

	// Force this one, TODO, should allow table also
				pItem->m_computedDisplayModel = DisplayModel_block_inside;
				pItem->m_computedDisplayRole = DisplayRole_block;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, 0x0fffffff);
				ASSERT(pC->m_pBlockBox);

				pItem->m_maxContentWidth = pC->m_maxx;

				pItem->m_maxWidth = pItem->m_maxContentWidth +
					pItem->m_computedBorderWidth[0] +
					pItem->m_computedMargin[0] +
					pItem->m_computedPadding[0] +

					pItem->m_computedBorderWidth[2] +
					pItem->m_computedMargin[2] +
					pItem->m_computedPadding[2];

				pItem->m_height = pItem->m_contentSize.Height +
					pItem->m_computedBorderWidth[1] +
					pItem->m_computedMargin[1] +
					pItem->m_computedPadding[1] +

					pItem->m_computedBorderWidth[3] +
					pItem->m_computedMargin[3] +
					pItem->m_computedPadding[3];

				delete pC;

			//	m_pBox = NULL;
			//	m_boxList.RemoveAll();
				pItem->RemoveBoxesAndChildren();
			}

#if 0
			long itemWidth = -1;
			long bitmapIndex = pItem->m_bitmapIndex;
			/*
			if (cmd)
			{
				cmd->get_bitmapIndex(&bitmapIndex);
				cmd->get_itemWidth(&itemWidth);
			}
			*/

			pItem->m_size.cx = 0;
			pItem->m_size.cy = 0;

			pItem->m_size.cy = 2+18+2;

			if (bitmapIndex >= 0)	// icon
			{
				pItem->m_size.cx = 2+18+2;
			}
			else if (itemWidth < 0) // Display as text
			{
				SIZE size;
				GetTextExtentPoint32(hDC, text, text.length(), &size);

				pItem->m_size.cx = 2+size.cx+2;
			}

			if (itemWidth > -1)
			{
				pItem->m_controlWidth = itemWidth;
				pItem->m_size.cx += itemWidth;
			}
#endif
		}
	}

#if 0
	if (m_orientation == 0)
	{
		m_textwidth = 0;
		m_shortcutwidth = 0;

		unsigned long nchildren;
		m_menuItem->CountItems(&nchildren);

		m_size.cx = 0;
		m_size.cy = 0;
		int x = 0;
		int y = 0;

		for (unsigned long i = 0; i < nchildren; i++)
		{
			CComQIPtr<IMenuItem> pItem;
			m_menuItem->GetSubMenu(i, &pItem);

			SIZE size;
			BSTR text;
			pItem->get_text(&text);

			if (m_orientation == 0)
			{
				if (text)
				{
					WCHAR* tab = wcschr(text, L'\t');
					if (tab)
					{
						GetTextExtentPoint32(hDC, _bstr_t(text), (tab-text)/2, &size);
						if (size.cx > m_textwidth) m_textwidth = size.cx;

						GetTextExtentPoint32(hDC, _bstr_t(tab+1), wcslen(tab+1), &size);
						if (size.cx > m_shortcutwidth) m_shortcutwidth = size.cx;
					}
					else
					{
						GetTextExtentPoint32(hDC, _bstr_t(text), wcslen(text), &size);
						if (size.cx > m_textwidth) m_textwidth = size.cx;
					}
				}

				y += itemHeight;
			}

			SysFreeString(text);
		}
	}
#endif

	/*
	SelectObject(hDC, hOldFont);
	DeleteDC(hDC);

	if (hVerticalFont)
		DeleteObject(hVerticalFont);
		*/
}

void CUIMenuDlg::SizeDispItemsArray(int m_orientation, CArray<CComObject<CDispItem>*,CComObject<CDispItem>*>& m_items)
{
//	if (m_menuItem)
	{
	//	HDC hDC = CreateCompatibleDC(NULL);

		/*
		LOGFONT lf;
		GetObject(hDC, sizeof(lf), &lf);
		lf.lfEscapement = 90*10;
		lf.lfOrientation = 90*10;

		HFONT hVerticalFont = CreateFontIndirect(&lf);
		ASSERT(hVerticalFont != NULL);
		*/

	/*
		HFONT hOldFont = (HFONT)GetCurrentObject(hDC, OBJ_FONT);

		HFONT hVerticalFont;
		
		if (m_orientation == 2)
		{
			hVerticalFont = CreateFont(16, 0, -90*10, -90*10, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Verdana");
			SelectObject(hDC, hVerticalFont);
		}
		else
		{
			SelectObject(hDC, (HFONT)GetStockObject(DEFAULT_GUI_FONT));
		}
		*/

	// Create controls/calculate size of items
//		unsigned long nchildren;
//		m_menuItem->CountItems(&nchildren);

//		for (unsigned long i = 0; i < nchildren; i++)
		for (int i = 0; i < m_items.GetSize(); i++)
		{
			//CComPtr<IMenuItem> item;
			//m_menuItem->GetSubMenu(i, &item);

			CComObject<CDispItem>* pItem = m_items[i];
			/*
			CComObject<CDispItem>::CreateInstance(&pItem);
			pItem->AddRef();
			pItem->m_menuDlg = this;//static_cast<T*>(this);
			pItem->m_menuItem = item;

			pItem->m_parent = this;
			pItem->m_pNode = m_menuItem->m_subItems[i]->m_pNode;

			item->get_commandID(&pItem->idCommand);

			pItem->m_menuItem->get_text(&pItem->m_text);
			*/

			SizeDispItem(m_orientation, pItem);

#if 0
#if 0
			CComPtr<IUICommand> cmd;
			item->get_command(&cmd);

			long ID = 0;
			if (cmd)
			{
				cmd->get_ID(&ID);
			}
#endif

			BSTR btext;
			pItem->m_menuItem->get_text(&btext);
			_bstr_t text = _bstr_t(btext, false);

			DWORD type;
			pItem->m_menuItem->get_type(&type);

			if (type & MF_SEPARATOR) pItem->fsStyle |= TBSTYLE_SEP;

			//pItem->idCommand = ID;

			if (m_orientation == 2)
			{
				CRect rc(0,0,0,0);
				DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);
			//	CRect rc(0,0,40,80);

				pItem->m_size.cx = 2+rc.Height()+2;
				pItem->m_size.cy = 4+rc.Width()+4;
			}
			else if (m_orientation == 0)
			{
				// nothing to do, use m_textWidth, m_itemHeight
			//	pItem->m_size.cx = m_textWidth;
				pItem->m_size.cy = itemHeight;
			}
			else if (m_orientation == 1)
			{
				CRect rc(0,0,0,0);
				DrawText(hDC, text, text.length(), &rc, DT_CALCRECT | DT_SINGLELINE);

				pItem->m_size.cx = 4+rc.Width()+4;
				pItem->m_size.cy = 2+itemHeight+2;
			}
			else if (m_orientation == -1)
			{
				if (pItem->fsStyle & TBSTYLE_SEP)
				{
					pItem->m_size.cx = iBitmap;
					pItem->m_size.cy = 2+18+2;
				}
				else
				{
					long itemWidth = -1;
					long bitmapIndex = -1;
#if 0
					if (cmd)
					{
						cmd->get_bitmapIndex(&bitmapIndex);
						cmd->get_itemWidth(&itemWidth);
					}
#endif

					pItem->m_size.cx = 0;
					pItem->m_size.cy = 0;

					pItem->m_size.cy = 2+18+2;

					if (bitmapIndex >= 0)	// icon
					{
						pItem->m_size.cx = 2+18+2;
					}
					else if (itemWidth < 0) // Display as text
					{
						SIZE size;
						GetTextExtentPoint32(hDC, text, text.length(), &size);

						pItem->m_size.cx = 2+size.cx+2;
					}

					if (itemWidth > -1)
					{
						pItem->m_controlWidth = itemWidth;
						pItem->m_size.cx += itemWidth;
					}
				}
			}
#endif
		}

#if 0
		if (m_orientation == 0)
		{
			m_textwidth = 0;
			m_shortcutwidth = 0;

			long nchildren;
			m_menuItem->CountItems(&nchildren);

			m_size.cx = 0;
			m_size.cy = 0;
			int x = 0;
			int y = 0;

			for (long i = 0; i < nchildren; i++)
			{
				CComQIPtr<IMenuItem> pItem;
				m_menuItem->GetSubMenu(i, &pItem);

				SIZE size;
				BSTR text;
				pItem->get_text(&text);

				if (m_orientation == 0)
				{
					if (text)
					{
						WCHAR* tab = wcschr(text, L'\t');
						if (tab)
						{
							GetTextExtentPoint32(hDC, _bstr_t(text), (tab-text)/2, &size);
							if (size.cx > m_textwidth) m_textwidth = size.cx;

							GetTextExtentPoint32(hDC, _bstr_t(tab+1), wcslen(tab+1), &size);
							if (size.cx > m_shortcutwidth) m_shortcutwidth = size.cx;
						}
						else
						{
							GetTextExtentPoint32(hDC, _bstr_t(text), wcslen(text), &size);
							if (size.cx > m_textwidth) m_textwidth = size.cx;
						}
					}

					y += itemHeight;
				}
				/*
				else if (m_orientation == 1)
				{
					_bstr_t t = text;
					int len = t.length();
					GetTextExtentPoint32(hDC, t, t.length(), &size);

					x += size.cx + 8;

					m_size.cx = 4+x+4;
					m_size.cy = 4+itemHeight+4;
				}
				*/

				SysFreeString(text);
			}
		}
#endif

		/*
		SelectObject(hDC, hOldFont);
		DeleteDC(hDC);

		if (hVerticalFont)
			DeleteObject(hVerticalFont);
			*/
	}
}

void CUIMenuDlg::UpdateItems()
{
#if 0
	if (m_pCmdWnd)
	{
	// First build an array of items to update (in case the target adds/deletes items dynamically)
	/*
		CArray <CMenuItem*, CMenuItem*> items;

		unsigned long nchildren;
		m_menuItem->CountItems(&nchildren);

		for (int i = 0; i < nchildren; i++)
		{
			CComQIPtr<IMenuItem> pItem;
			m_menuItem->GetSubMenu(i, &pItem);
			items.Add(pItem);
		}
*/

	// Now update the items
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();
			pCmdUI->m_dlg = this;

			long nchildren;
			m_menuItem->CountItems(&nchildren);

			for (long i = 0; i < nchildren; i++)
			{
				CComQIPtr<IMenuItem> item;
				m_menuItem->GetSubMenu(i, &item);

				pCmdUI->m_menuItem = item;
				//pCmdUI->m_controlItem = m_items[i]->m_control;
				pCmdUI->m_hwndControl = m_items[i]->m_hWnd;

				//CComPtr<IUICommand> command;
				//item->get_command(&command);
				//if (command)
				{
					long id;
					item->get_commandID(&id);

					if (id)
					{
#if 0
						CComQIPtr<ICommandTarget> target = m_pCmdWnd;
						if (target)
						{
							BOOL bHandled;
							target->OnCmdMsg(id, -1, pCmdUI, &bHandled);
						}
#endif
					}
				}
			}

			pCmdUI->Release();
			pCmdUI = NULL;
		}
	}
#endif
}

void CUIMenuDlg::SetActiveItem(CDispItem* pItem)
{
	ASSERT(0);
#if 0

	ASSERT(m_hWnd);

	if (pItem != m_pActiveItem)
	{
		if (m_pActiveItem)
		{
			RECT rect = GetItemRect(m_pActiveItem);
			InvalidateRect(&rect, TRUE);
		}

		m_pActiveItem = pItem;
		if (m_pActiveItem)
		{
			RECT rect = GetItemRect(m_pActiveItem);
			InvalidateRect(&rect, TRUE);
		}
		else
		{
			ATLTRACE("m_pActiveItem=NULL\n");
		}

		UpdateWindow();
	}
#endif
}

void CUIMenuDlg::PopupActiveItem()
{
	ASSERT(0);
#if 0
	if (m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}

	if (m_pPrevActiveItem != m_pActiveItem)
	{
		// Destroy any previous child popup menu
		if (m_activeSubDlg != NULL)
		{
			ASSERT(0);
#if 0
			if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
				m_activeSubDlg->DestroyWindow();
#endif

			m_activeSubDlg->Release();
			m_activeSubDlg = NULL;
		}

		m_pPrevActiveItem = m_pActiveItem;

		if (m_pActiveItem)
		{
			long childrencount;
			m_pActiveItem->m_menuItem->CountItems(&childrencount);

			if (childrencount > 0)	// Bring up sub-menu
			{
				DWORD menuType;
				m_pActiveItem->m_menuItem->get_type(&menuType);
				if (menuType & MF_POPUP)
				{
				}

				int index = GetItemIndex(m_pActiveItem);

				RECT client;
				GetClientRect(&client);

				POINT point;

				if (m_orientation == 0)
				{
					point.x = m_items[index]->m_pBox->m_outerRect.GetRight()-4;
					point.y = m_items[index]->m_pBox->m_outerRect.Y;
				}
				else if (m_orientation == 2)
				{
					point.x = m_items[index]->m_pBox->m_outerRect.GetRight();
					point.y = m_items[index]->m_pBox->m_outerRect.Y;
				}
				else
				{
					point.x = m_items[index]->m_pBox->m_outerRect.X-4;
					point.y = m_items[index]->m_pBox->m_outerRect.GetBottom()+2;
				}

				ClientToScreen(&point);

				ASSERT(m_activeSubDlg == NULL);
				CComObject<CUIMenuDlg>::CreateInstance(&m_activeSubDlg);
				if (m_activeSubDlg)
				{
					m_activeSubDlg->AddRef();

					m_activeSubDlg->m_pView = m_pView;

					//if (m_orientation == 1)	// Menu bar
					{
					// Make it look pushed right away
						InvalidateRect(&GetItemRect(m_pActiveItem), TRUE);
					//	Invalidate();
						UpdateWindow();
					}

					m_activeSubDlg->m_bParentMsgLoop = m_bParentMsgLoop;

					DWORD menuType;
					m_pActiveItem->m_menuItem->get_type(&menuType);

					if (menuType & MF_POPUP)
					{
						m_activeSubDlg->m_orientation = -1;
					}

					m_activeSubDlg->PopupMenu2(m_pActiveItem->m_menuItem, this, NULL/*m_pCmdWnd*/, point, m_popupFlags);
				}
			}
		}
	}
#endif
}

void CUIMenuDlg::DrawInsertBar(HDC hDC, int insertIndex)
{
	ASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);

	int oldR2 = SetROP2(hDC, R2_NOTXORPEN);

	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));
	HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));

	if (m_orientation == 0)
	{
		int y = 4 + floatHeight;
		if (insertIndex > 0)
			y = m_items[insertIndex-1]->m_pBox->m_outerRect.GetBottom();

		POINT pt[] =
		{
			3, y-4,
			3, y+4,
			6, y+1,
			client.right-6, y+1,
			client.right-3, y+4,
			client.right-3, y-4,
			client.right-6, y-1,
			6, y-1,
		};

		Polygon(hDC, pt, 8);
	}
	else
	{
		int x = 4;
		if (insertIndex > 0)
			x = m_items[insertIndex-1]->m_pBox->m_outerRect.GetRight();

		POINT pt[] =
		{
			x-4, 2,
			x+4, 2,
			x+1, 5,
			x+1, client.bottom-7,
			x+4, client.bottom-3,
			x-4, client.bottom-3,
			x-1, client.bottom-7,
			x-1, 5
		};

		Polygon(hDC, pt, 8);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	SetROP2(hDC, oldR2);
#endif
}

STDMETHODIMP CUIMenuDlg::PopupMenu2(IMenuItem* menuItem, CUIMenuDlg* pParentMenuDlg, ICommandTarget * /*pCmdWnd*/, POINT point, DWORD flags)
{
	ASSERT(0);
#if 0
//	ASSERT(pCmdWnd);

	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_parentMenuDlg = pParentMenuDlg;

#if 0
	m_pCmdWnd = pCmdWnd;
#endif
	m_popupFlags = flags;

	CreateItems(m_items);
	GetCSSPropertiesAndChildren();
	BuildRenderChildren();
	ASSERT(0);
#if 0
	((CLXUIDocumentView*)m_pView)->CalcDims(this);
#endif
	SizeDispItemsArray(m_orientation, m_items);

	PlaceItems();

//	CSize size;
//	CalcLayout(LM_MRUWIDTH, 32767, &size);	// TODO, optimize this to work directly on the above m_items ??

	int width;
	int height;
	
#if 0
	if (m_orientation == 0)
	{
		long count;
		m_menuItem->CountItems(&count);

		width = 4 + (20 + m_textwidth + 4 + /*m_shortcutwidth +*/ 20) + 4;
		height = floatHeight + 4 + count*itemHeight + 4;
	}
	else
	{
		ASSERT(0);
#if 0
		width = size.cx;
		height = size.cy;
#endif
	}
#endif
	width = m_pBox->m_outerRect.Width;
	height = m_pBox->m_outerRect.Height;

	RECT screenRect;
	::SystemParametersInfo(SPI_GETWORKAREA, 0, &screenRect, 0);

	RECT menuRect = {point.x, point.y, point.x + width, point.y + height };

	if (menuRect.right > screenRect.right) OffsetRect(&menuRect, -(menuRect.right - screenRect.right), 0);
	if (menuRect.bottom > screenRect.bottom) OffsetRect(&menuRect, 0, -(menuRect.bottom - screenRect.bottom));
	if (menuRect.left < screenRect.left) OffsetRect(&menuRect, (screenRect.left - menuRect.left), 0);
	if (menuRect.top < screenRect.top) OffsetRect(&menuRect, 0, (screenRect.top - menuRect.top));

	HWND ownerHWnd = NULL;

//	m_bParentMsgLoop = TRUE;

	CWindowImpl<CUIMenuDlg>::
		Create(
		ownerHWnd,
		CRect(menuRect.left, menuRect.top, menuRect.left+width, menuRect.top+height),
		NULL,
		WS_POPUP,
		WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
		0);

	UpdateItems();

	if (FALSE)
	{
		if (!AnimateWindow(m_hWnd, 150, AW_BLEND/*AW_HOR_POSITIVE | AW_VER_POSITIVE*/))
		{
			ASSERT(0);
		}
	}
	else
	{
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}

#if 0
	if (FALSE)
	{
		m_wndShadow.Create(ownerHWnd, CRect(menuRect.left+5, menuRect.top+5, menuRect.left+width+5, menuRect.top+height+5),
			NULL,
			WS_POPUP,
			WS_EX_TOOLWINDOW);

		m_wndShadow.SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);

		/*
		CRect client;
		GetClientRect(&client);

		LPBITMAPV4HEADER m_lpBmi;

		HDC hDCScreen = ::GetDC(NULL);

		if (m_lpBmi = (LPBITMAPV4HEADER)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPV4HEADER)))
		{
			m_lpBmi->bV4Size = sizeof(BITMAPV4HEADER);
			m_lpBmi->bV4Width = client.Width();
			m_lpBmi->bV4Height = client.Height();
			m_lpBmi->bV4Planes = 1;
			m_lpBmi->bV4BitCount = 32;
			m_lpBmi->bV4V4Compression = BI_RGB;

			LPBYTE m_bmBits;
			HBITMAP m_hBitmap = ::CreateDIBSection(NULL, (BITMAPINFO*)m_lpBmi, DIB_RGB_COLORS, (void**)&m_bmBits, NULL, 0);
			if (m_hBitmap)
			{
				HDC m_hDC = CreateCompatibleDC(hDCScreen);
				SelectObject(m_hDC, m_hBitmap);

				Draw(m_hDC);

				{
					for (int y = 0; y < m_lpBmi->bV4Height; y++)
					{
						BYTE* p = (BYTE*)m_bmBits + (m_lpBmi->bV4Width*4)*(m_lpBmi->bV4Height-y-1);
						for (int x = 0; x < m_lpBmi->bV4Width; x++)
						{
							//if (x < m_lpBmi->bV4Width-8)
							{
								p[3] = 128;
							}

							p += 4;
						}
					}
				}

				BLENDFUNCTION bf;
				bf.BlendOp = AC_SRC_OVER;
				bf.BlendFlags = 0;
				bf.SourceConstantAlpha = 255;
				bf.AlphaFormat = AC_SRC_ALPHA;
	
				SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_LAYERED);

				CRect wrect;
				GetWindowRect(&wrect);

				CPoint ptSrc(0,0);
				if (!UpdateLayeredWindow(m_hWnd,
					hDCScreen,//HDC hdcDst,
					&CPoint(wrect.left, wrect.top),//POINT* pptDst,
					&CSize(wrect.Width(), wrect.Height()),//SIZE* psize,
					m_hDC,
					&ptSrc,
					0,//COLORREF crKey,
					&bf,//BLENDFUNCTION* pblend,
					ULW_ALPHA//DWORD dwFlags
					))
				{
					ASSERT(0);
				}
			}
		}

		::ReleaseDC(NULL, hDCScreen);
		*/
	}
#endif

	SetCapture();
#endif

	return S_OK;
}

#if 0
void CUIMenuDlg::Init(IMenuItem *menuItem, DWORD orientation)
{
	ASSERT(menuItem != NULL);

	m_menuItem = static_cast<CMenuItem*>(menuItem);
	m_parentMenuDlg = NULL;//pParentMenuDlg;

	m_orientation = orientation;

//	CalculateMaxWidth((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	RemoveDispItems();
	CreateItems(m_items);
	GetCSSPropertiesAndChildren();
	BuildRenderChildren();
	((CLXUIDocumentView*)m_pView)->CalcDims(this);
	SizeDispItemsArray(m_orientation, m_items);
}
#endif

STDMETHODIMP CUIMenuDlg::CreateForMenuItem(IMenuItem *menuItem, HWND hParent, ICommandTarget *pCmdWnd, DWORD orientation)
{
	ASSERT(0);
#if 0
	if (m_hWnd)
	{
		ASSERT(IsWindow());
		ASSERT(0);
		return E_FAIL;
	}

	ASSERT(hParent != NULL);

//	CSize size;
//	CalcLayout(LM_MRUWIDTH, 32767, &size);	// TODO, optimize this to work directly on the above m_items ??

//	m_bParentMsgLoop = FALSE;

	CWindowImpl<CUIMenuDlg>::Create(hParent, CRect(0,0,0,0), NULL, WS_CHILD, 0, 0);

	UpdateItems();

	SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_SHOWWINDOW);
#endif

	return S_OK;
}

void CUIMenuDlg::SetCommand(CDispItem* pItem)
{
	/*
	m_selectedID = pItem->GetCommandID();
	m_result = 1;	// Ok
	*/

	ASSERT(0);

#if 0
	put_selectedID(pItem->m_menuItem);

	if (m_bParentMsgLoop)
	{
		put_result(1);	// Ok
	}
	else
	{
#if 0
		BOOL bHandled = FALSE;
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();
			pCmdUI->m_dlg = this;

			pCmdUI->m_menuItem = pItem->m_menuItem;
			pCmdUI->m_hwndControl = pItem->m_hWnd;

			m_pCmdWnd->OnCmdMsg(m_selectedID->get_commandID(), 0, pCmdUI, &bHandled);

			pCmdUI->Release();
			pCmdUI = NULL;
		}
#endif
	}
#endif
}

STDMETHODIMP CUIMenuDlg::CalcLayout(DWORD dwMode, long nLength, SIZE* pVal)
{
	int orientation;

	if (m_orientation == -1)
		orientation = -1;
	else
		orientation = 0;//(dwMode & LM_VERTDOCK)? 2: 1;

	int nCount = m_items.GetSize();
	_TBBUTTON* items = new _TBBUTTON[nCount];// CArray<CComObject<CToolbarButton>*,CComObject<CToolbarButton>*> items;
	GetButtonInfo(items, 0, m_items.GetSize());

	//CreateSizeDispItemsArray(orientation, items);

	_TBBUTTON* pData = items;//.GetData();

	DWORD m_dwStyle = CBRS_FLOATING;

	CSize sizeResult(0,0);

	if (nCount > 0)
	{
		{
			BOOL bDynamic = TRUE;//m_dwStyle & CBRS_SIZE_DYNAMIC;

#if 0
			if (bDynamic && (dwMode & LM_MRUWIDTH))
			{
				SizeToolBar(pData, nCount, GetMRUWidth());
			}
			else if (bDynamic && (dwMode & LM_HORZDOCK))
			{
				SizeToolBar(pData, nCount, /*nLength > 0? nLength-8:*/ 32767);
			}
			else if (bDynamic && (dwMode & LM_VERTDOCK))
			{
				SizeToolBar(pData, nCount, 0);//nLength-8/*0*/);
			}
			else
#endif
				if (bDynamic && /*(nLength > 0)*/(nLength != -1))
			{
				CRect rect; rect.SetRectEmpty();
				CalcInsideRect(rect, (dwMode & LM_HORZ));
				BOOL bVert = (dwMode & LM_LENGTHY);
				int nLen = nLength + (bVert ? rect.Height() : rect.Width());

				SizeToolBar(pData, nCount, nLen, bVert);
			}
			else if (nLength == 0)
			{
				SizeToolBar(pData, nCount, nLength);
			}
#if 0
			else if (bDynamic && (m_dwStyle & CBRS_FLOATING))
			{
				SizeToolBar(pData, nCount, 32767/*m_nMRUWidth*/);
			}
#endif
			else
				SizeToolBar(pData, nCount, (dwMode & LM_HORZ) ? 32767 : 0);
		}

		sizeResult = CalcSize(pData, nCount);
	}

	//
	// Stretch out to fill ?
	if ((dwMode & LM_HORZDOCK)/* && !(m_dwStyle & CBRS_FLOATING)*/)
	{
		if (nLength > 0)
			sizeResult.cx = nLength-8;//max(nLength-8, sizeResult.cx);
	}
	//

	//BLOCK: Adjust Margins
	{
#if 0	// Test without this
		CRect rect; rect.SetRectEmpty();
		CalcInsideRect(rect, (dwMode & LM_HORZ));
		sizeResult.cy -= rect.Height();
		sizeResult.cx -= rect.Width();
#endif

		/*
		CSize size = CControlBar::CalcFixedLayout((dwMode & LM_STRETCH), (dwMode & LM_HORZ));
		sizeResult.cx = max(sizeResult.cx, size.cx);
		sizeResult.cy = max(sizeResult.cy, size.cy);
		*/
	}

	*pVal = sizeResult;

	if (dwMode & LM_COMMIT)
	{
		for (int i = 0; i < nCount; i++)
		{
			m_items[i]->fsState = pData[i].fsState;
			m_items[i]->fsStyle = pData[i].fsStyle;

			if (m_items[i]->fsState & TBSTATE_WRAP)
			{
				MessageBeep(-1);
			}

			//m_items[i]->fsState = pData[i].fsState;
			//m_items[i]->fsState = pData[i].fsState;
		}
		/*
		m_items.RemoveAll();

		for (i = 0; i < nCount; i++)
		{
			m_items.Add(items[i]);
		}
		*/

		m_orientation = orientation;
	}
	else
	{
		/*
	// Cleanup
		for (int i = 0; i < items.GetSize(); i++)
		{
			items[i]->Release();
		}
		*/
	}
	//items.RemoveAll();
	delete items;

	return S_OK;
}

LRESULT CUIMenuDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0

	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);



	//HWND hWnd = WindowFromPoint(screenpt);
	//if (m_hWnd == hWnd)
	{
		if (m_orientation == 0 && !m_dragging && point.y < 4+floatHeight)
		{
			// Detach the menu

#if 0
			CComQIPtr<IUIFrame> frame = m_pCmdWnd;
			if (frame)
			{
#if 0
				CComQIPtr<IDlgManager> dlgman;
				frame->get_dlgManager(&dlgman);

				m_selectedID = 0L;
				m_result = ID_CANCEL;

				CRect wrect;
				GetWindowRect(&wrect);

				DestroyWindow();

				{
					m_parentMenuDlg = NULL;
					m_bParentMsgLoop = FALSE;

					ASSERT(0);
					// The following
#if 0
					// Create sheet
					CComObject<CDlgSheet>* sheet;
					CComObject<CDlgSheet>::CreateInstance(&sheet);
					sheet->AddRef();
					sheet->m_dlgManager = dlgman;

					static_cast<CDlgManager*>(dlgman.p)->m_pSheets.AddTail(sheet);

				// Add us to the sheet
					sheet->AddPage(this);

				// Show sheet
					BOOL b;
					sheet->Create(CRect(0,0,200, 20), &b);

					sheet->SetWindowPos(NULL, wrect.left, wrect.top, wrect.Width()+8, wrect.Height()+20, SWP_NOZORDER);
#endif
				}

				BSTR text;
				m_menuItem->get_text(&text);

				CComPtr<IUIRegisteredDlg> dlgclass;
				m_menuItem->m_uiManager->RegisterMenuDlg(0, text, 0, &dlgclass);

				SysFreeString(text);

			//	SendMessage(hwndsheet, WM_NC
#endif
			}
#endif
		}
		else
		{
			int index = IndexFromPoint(point);

			CDispItem* pItem = (index >= 0)?m_items[index]: NULL;

			if (pItem)
				m_dragging = 1;

			if (/*m_parentMenuDlg == NULL*/m_bParentMsgLoop == FALSE)	// top-level menu
			{
				if (m_activeSubDlg == NULL)
				{
					SetActiveItem(pItem);	// ??
					if (pItem)
					{
						m_bParentMsgLoop = TRUE;

						m_pPrevActiveItem = NULL;

						PopupActiveItem();

						if (m_activeSubDlg)
						{
							long result = TrackMenu2();
						}

						m_bParentMsgLoop = FALSE;
						//long result = TrackMenu();
					}
				}
				else
				{
					if (m_pActiveItem == pItem)	// Toggle off
					{
#if 0
						SetActiveItem(pItem);	// ??
#endif
						/*m_activeSubDlg->*/put_result(-2);	// Cancel

						// Destroy any previous child popup menu
						if (m_activeSubDlg != NULL)
						{
							ASSERT(0);
#if 0
							if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
								m_activeSubDlg->DestroyWindow();
#endif

							m_activeSubDlg->Release();
							m_activeSubDlg = NULL;
						}

						SetActiveItem(NULL);
					//	m_activeSubDlg->m_result = -2;	// Cancel
						//m_selectedID = -1;	// Cancel
					}
					else
					{
						if (pItem)
						{
							PopupActiveItem();
						}
						else
						{
							/*m_activeSubDlg->*/put_result(-2);	// Cancel
						}
					}
				}
			}
			else	// Clicked on Submenu->item
			{
				SetActiveItem(pItem);
				PopupActiveItem();
			}

			if (pItem)
			{
				/*
				unsigned long childrencount;
				m_pActiveItem->m_menuItem->CountItems(&childrencount);

				CComPtr<IUIManager> uiManager;
				m_menuItem->get_uiManager(&uiManager);

				BOOL bDesignMode = FALSE;
				if (uiManager)
					uiManager->get_DesignMode(&bDesignMode);

				if (bDesignMode)
				{
					PopupActiveItem();
				}
				else
				*/
			}
		}
	}
	/*
	else
	{
		//ReleaseCapture();
		m_selectedID = -2;
	}
	*/
#endif

	return 0;
}

LRESULT CUIMenuDlg::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		m_dragging = 0;

		//CComQIPtr<IMenuItem> pItem;// = NULL;
		//if (m_pActiveItem) pItem = m_pActiveItem;

		if (m_pActiveItem)
		{
			ASSERT(0);
#if 0
			long childrencount;
			m_pActiveItem->m_menuItem->CountItems(&childrencount);
			if (childrencount == 0)
			{
				SetCommand(m_pActiveItem);
			}
#endif
		}
	}

	return 0;
}

LRESULT CUIMenuDlg::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);
	UINT nFlags = wParam;

	CRect client;
	GetClientRect(&client);

	BOOL bInsideWindow = point.x >= 0 && point.y >= 0 && point.x < client.right && point.y < client.bottom;
	if (bInsideWindow != m_bInsideWindow)
	{
		m_bInsideWindow = bInsideWindow;
		if (m_bInsideWindow)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = m_hWnd;
			tme.dwFlags = TME_LEAVE;
			tme.dwHoverTime = 0;
			TrackMouseEvent(&tme);
		}
	}

	if (m_pOwnedWindow)
	{
		m_pOwnedWindow->m_pView = m_pView;	// TODO somewhere else
		m_pOwnedWindow->OnMouseMove(nFlags, point);
	}

	Invalidate();	// TODO remove

	int index = IndexFromPoint(point);

	if (index >= 0)
	{
		CDispItem* pItem = m_items[index];

		if (pItem != m_pActiveItem)
		{
			DWORD type;
			pItem->m_menuItem->get_type(&type);

			if (TRUE)	// Menu item description
			{
				CComPtr<ILDOMDocument> document;
				m_pNode->get_ownerDocument(&document);

				CComPtr<ILDOMElement> element;
				document->getElementById(L"cmd_description", &element);
				if (element)
				{
					CComQIPtr<ILXUIMenuItemElement> menuItem = pItem->m_pNode;

					CComVariant description;
					menuItem->get_caption(&description);

					element->put_textContent(_bstr_t(description));
				}
			}

			if (!(type & MF_SEPARATOR))
			{
				if (m_nTimer)
				{
					KillTimer(m_nTimer);
					m_nTimer = 0;
				}

				SetActiveItem(pItem);

				m_nTimer = SetTimer(1, 500);

				if (m_parentMenuDlg == NULL)
				{
					if (m_activeSubDlg != NULL)
					{
						PopupActiveItem();
					}
				}
			}
		}
	}
	else
	{
		if (m_activeSubDlg == NULL)
			SetActiveItem(NULL);
	}
#endif

	return 0;
}

LRESULT CUIMenuDlg::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_bInsideWindow = FALSE;

	if (m_activeSubDlg == NULL)
		SetActiveItem(NULL);

	return 0;
}

LRESULT CUIMenuDlg::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CDispItem* pItem = m_pActiveItem;

	if (pItem)
	{
		/*
		put_selectedID(pItem->GetCommandID());
		put_result(2);	// Ok double click
		*/

		//if (m_bParentMsgLoop)
		{
			ReleaseCapture();
			//DestroyWindow();
			//m_bParentMsgLoop = FALSE;
		}

		put_result(-2);	// Cancel

#if 0
		BOOL bHandled = FALSE;
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();

			pCmdUI->m_dlg = this;
			pCmdUI->m_menuItem = pItem->m_menuItem;
			pCmdUI->m_hwndControl = pItem->m_hWnd;

			m_pCmdWnd->OnCmdMsg(pItem->GetCommandID(), BN_DBLCLK, pCmdUI, &bHandled);

			pCmdUI->Release();
			pCmdUI = NULL;
		}
#endif
	}

	return 0;
}

LRESULT CUIMenuDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//ModifyStyleEx(0, WS_EX_LAYERED);

	ASSERT(0);
#if 0

	m_bInsideWindow = FALSE;

	SetProp(m_hWnd, "menudlg", (HANDLE)this);
	::RegisterDragDrop(m_hWnd, (IDropTarget*)this);

#ifdef WTL_APPLICATION
	_Module.GetMessageLoop()->AddIdleHandler(this);
#endif

	if (m_toolTipCtrl.Create(m_hWnd, NULL, NULL, TTS_ALWAYSTIP, WS_EX_TOPMOST) == NULL)
	{
		ASSERT(0);
		return -1;
	}

// Create controls
	for (long i = 0; i < m_items.GetSize(); i++)
	{
		CDispItem* pItem = m_items[i];
		CMenuItem* item = pItem->m_menuItem;

#if 0
		CComPtr<IUICommand> cmd;
		item->get_command(&cmd);

		long ID = 0;
		if (cmd)
		{
			cmd->get_ID(&ID);
		}
#endif

		BSTR btext;
		pItem->m_menuItem->get_text(&btext);
		_bstr_t text = _bstr_t(btext, false);

		DWORD type;
		pItem->m_menuItem->get_type(&type);

#if 0
		if (cmd)
		{
		// Add tool to tooltip control
			m_toolTipCtrl.AddTool(CToolInfo(TTF_SUBCLASS, m_hWnd, ID, NULL, text));
		}

#endif
	}
#endif

	return 0;
}

int CUIMenuDlg::IndexFromPoint(POINT point)
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		if (m_items[i]->m_pBox->m_outerRect.Contains(point.x, point.y))
			return i;
	}

	return -1;
}

RECT CUIMenuDlg::GetItemRect(CDispItem* pItem)
{
	return CRect(pItem->m_pBox->m_outerRect.X, pItem->m_pBox->m_outerRect.Y, pItem->m_pBox->m_outerRect.GetRight(), pItem->m_pBox->m_outerRect.GetBottom());
}

LRESULT CUIMenuDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ASSERT(0);
#if 0

#if 0
	if (m_wndShadow.m_hWnd)
		m_wndShadow.DestroyWindow();
#endif

	if (GetCapture() == m_hWnd)
		ReleaseCapture();

#ifdef WTL_APPLICATION
	_Module.GetMessageLoop()->RemoveIdleHandler(this);
#endif

	RevokeDragDrop(m_hWnd);

//	m_toolTipCtrl.DestroyWindow();

	if (m_nTimer)
	{
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}

	if (m_activeSubDlg)
	{
		ASSERT(0);
#if 0
		if (m_activeSubDlg->m_pDlgSite/*->m_pDockBar*/ == NULL)
			m_activeSubDlg->DestroyWindow();
#endif

		m_activeSubDlg->Release();
		m_activeSubDlg = NULL;
	}

	if (m_pActiveItem) m_pActiveItem = NULL;//.Release();// = NULL;
	if (m_pPrevActiveItem) m_pPrevActiveItem = NULL;//.Release();// = NULL;
#endif

	return 0;
}

#if 0
LRESULT CUIMenuDlg::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int wNotifyCode = HIWORD(wParam); // notification code 
	int wID = LOWORD(wParam);         // item, control, or accelerator identifier 
	HWND hwndCtl = (HWND) lParam;      // handle of control 

	for (int i = 0; i < m_items.GetSize(); i++)
	{
		if (m_items[i]->GetCommandID() == wID) break;;
	}

	if (i < m_items.GetSize())
	{
		CDispItem* pItem = m_items[i];

		BOOL bHandled = FALSE;
		CComObject<CUICmdUpdate>* pCmdUI;
		CComObject<CUICmdUpdate>::CreateInstance(&pCmdUI);
		if (pCmdUI)
		{
			pCmdUI->AddRef();
			pCmdUI->m_dlg = this;

			pCmdUI->m_menuItem = pItem->m_menuItem;
			pCmdUI->m_hwndControl = pItem->m_hWnd;

			m_pCmdWnd->OnCmdMsg(wID, wNotifyCode, pCmdUI, &bHandled);

			pCmdUI->Release();
			pCmdUI = NULL;
		}
	}

	return 0;
}
#endif

void CUIMenuDlg::PlaceItems(CHTMFlowBlockContext* pCIn)
{
	ASSERT(pCIn->m_maxx == 0);

//	ASSERT(::IsWindow(m_hWnd));

//	CRect client;
//	GetClientRect(&client);

	CPoint cur(0,0);

	CHTMFlowBlockContext pC;
	//pC.m_frameClient = m_client;

//	m_specifiedWidth = client.Width();
//	m_specifiedHeight = client.Height();
	m_computedDisplayModel = DisplayModel_block_inside;	// ??
//	m_bVScroll = false;	// Always vertical scrollbar on outer element (TODO unless specified)

	pC.m_pBlockBox = NULL;
	pC.m_pCurLineBox = NULL;
	pC.m_pPrevLeftFloatBox = NULL;

	pC.m_floatBottom = 0;
	pC.m_curpos.X = pC.m_curpos.Y = 0;
	pC.m_linepos.X = pC.m_linepos.Y = 0;
	pC.m_maxx = 0;

	m_pBox = CreateBlockBox();	// Principal box
	ASSERT(pC.m_pBlockBox == NULL);
	pC.m_pBlockBox = m_pBox;

	m_pBox->m_innerRect.Width = 0;//m_specifiedWidth;
	m_pBox->m_innerRect.Height = 0;//m_specifiedHeight;

//	/*m_shadowTree->*/DistributeWithinBlock(&pC, client.Width());

	//m_orientation = -1;	// TODO remove

	for (unsigned long i = 0; i < m_items.GetSize(); i++)
	{
		CDispItem* pItem = m_items[i];
		//CComQIPtr<IMenuItem> item = pItem->m_menuItem;

		SIZE size;
	//	BSTR text = pItem->m_text;
		//item->get_text(&text);

		if (m_orientation == 2)	// top to bottom - vertical text
		{
			ASSERT(0);
#if 0
			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.y += size.cy;
#endif
		}
		else if (m_orientation == 0)	// top to bottom
		{
			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

				pItem->m_computedDisplayModel = DisplayModel_block_inside;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, pItem->m_maxWidth);
				ASSERT(pC->m_pBlockBox);
				ASSERT(pItem->m_pBox == pC->m_pBlockBox);
				delete pC;

				size.cx = pItem->m_pBox->m_outerRect.Width;
				size.cy = pItem->m_pBox->m_outerRect.Height;

				CPoint rc;
				/*
				rc.left = 2+cur.x;
				rc.top = 2+cur.y;
				rc.bottom = 2+cur.y+size.cy;
				rc.right = 2+cur.x+size.cx;
				*/
				rc.x = 4;
				rc.y = floatHeight + 4 + cur.y;
				//rc.right = 4 + 20 + m_textwidth + 4 + m_shortcutwidth + 20;

				cur.y += size.cy;//itemHeight;

				pItem->m_pBox->m_outerRect.X = rc.x;
				pItem->m_pBox->m_outerRect.Y = rc.y;

				m_pBox->AddChildBox(pItem->m_pBox);
			}

#if 0
			pItem->m_rc.top = floatHeight + 4 + cur.y;
			pItem->m_rc.left = 4;
			pItem->m_rc.right = 4 + 20 + m_textwidth + 4 + m_shortcutwidth + 20;

			cur.y += pItem->m_size.cy;//itemHeight;

			pItem->m_rc.bottom = floatHeight + 4 + cur.y;
#endif
		}
		else if (m_orientation == 1)	// left to right
		{
			ASSERT(0);
#if 0
			if (pItem->fsStyle & TBSTYLE_SEP)
			{
			}
			else
			{
			}

			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.x += size.cx;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight+2;
			}
#endif
		}
		else if (m_orientation == -1)	// rows and columns
		{
			fg
#if 0
			int cySep = 12;//pData[i].iBitmap;
			cySep = cySep * 2 / 3;
#endif

			{
				ASSERT(pItem->m_boxList.GetSize()==0);
				ASSERT(pItem->m_pBox == NULL);

				pItem->m_computedDisplayModel = DisplayModel_block_inside;

				CHTMFlowBlockContext* pC = new CHTMFlowBlockContext;
				pItem->DistributeWithinBlock(pC, pItem->m_maxWidth);
				ASSERT(pC->m_pBlockBox);
				ASSERT(pItem->m_pBox == pC->m_pBlockBox);

				pItem->m_pBox->AdjustOuterRect();

				//size.cx = pItem->m_pBox->m_outerRect.Width;
				//size.cy = pItem->m_pBox->m_outerRect.Height;

				CPoint rc;
				rc.x = /*2+*/cur.x;
				rc.y = /*2+*/cur.y;

				pItem->m_pBox->m_outerRect.X = rc.x;
				pItem->m_pBox->m_outerRect.Y = rc.y;

				m_pBox->AddChildBox(pItem->m_pBox);
			}

			if (pItem->fsStyle & TBSTYLE_SEP)
				cur.x += /*pData[i].*/iBitmap;
			else
				cur.x += pItem->m_pBox->m_outerRect.Width - CX_OVERLAP;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight/*+2*/;

				if (pItem->fsStyle & TBSTYLE_SEP)
					cur.y += cySep;
			}

#if 0
			// Set tool rect
			if (pItem->GetCommandID())
			{
				m_toolTipCtrl.SetToolRect(m_hWnd, pItem->GetCommandID(), &pItem->m_rc);
			}
#endif
		}

		/*
		if (pItem->m_axcontrol)
		{
			pItem->m_axcontrol->MoveWindow(&pItem->m_rc, TRUE);
		}
		*/
#if 0
		if (pItem->m_hWnd)
		{
			CComPtr<IUICommand> cmd;
			item->get_command(&cmd);

			BSTR bwindowClassname;
			cmd->get_windowClassname(&bwindowClassname);
			_bstr_t windowClassname = _bstr_t(bwindowClassname, false);

			int height = pItem->m_rc.Height();

			if (!wcsicmp(windowClassname, L"combobox"))
				height += 260;

			::SetWindowPos(pItem->m_hWnd, NULL, pItem->m_rc.left+(pItem->m_rc.Width()-pItem->m_controlWidth), pItem->m_rc.top, pItem->m_controlWidth, height, SWP_NOZORDER | SWP_NOACTIVATE);
		}
#endif

		m_pBox->m_innerRect.Width = max(m_pBox->m_innerRect.Width, pItem->m_pBox->m_outerRect.GetRight());
		m_pBox->m_innerRect.Height = max(m_pBox->m_innerRect.Height, pItem->m_pBox->m_outerRect.GetBottom());

		pCIn->m_maxx += pItem->m_maxWidth;
	}

	m_pBox->m_outerRect.Width = m_pBox->m_innerRect.Width;
	m_pBox->m_outerRect.Height = m_pBox->m_innerRect.Height;

	m_pBox->AdjustOuterRect();

#if 0
	ASSERT(::IsWindow(m_hWnd));

	HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	HDC hDC = CreateCompatibleDC(NULL);
	HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

	CRect client;
	GetClientRect(&client);

	unsigned long nchildren = m_items.GetSize();

	CPoint cur(0,0);

	for (unsigned long i = 0; i < nchildren; i++)
	{
		CComObject<CDispItem>* pItem = m_items[i];
		CComQIPtr<IMenuItem> item = pItem->m_menuItem;

		SIZE size;
		BSTR text;
		item->get_text(&text);

		if (m_orientation == 2)	// top to bottom - vertical text
		{
			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.y += size.cy;
		}
		else if (m_orientation == 0)	// top to bottom
		{
			pItem->m_rc.top = floatHeight + 4 + cur.y;
			pItem->m_rc.left = 4;
			pItem->m_rc.right = 4 + 20 + m_textwidth + 4 + m_shortcutwidth + 20;

			cur.y += pItem->m_size.cy;//itemHeight;

			pItem->m_rc.bottom = floatHeight + 4 + cur.y;
		}
		else if (m_orientation == 1)	// left to right
		{
			if (pItem->fsStyle & TBSTYLE_SEP)
			{
			}
			else
			{
			}

			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			cur.x += size.cx;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight+2;
			}
		}
		else if (m_orientation == -1)	// rows and columns
		{
			int cySep = 12;//pData[i].iBitmap;
			cySep = cySep * 2 / 3;

			size = pItem->m_size;

			pItem->m_rc.left = 2+cur.x;
			pItem->m_rc.top = 2+cur.y;
			pItem->m_rc.bottom = 2+cur.y+size.cy;
			pItem->m_rc.right = 2+cur.x+size.cx;

			/*
			cur.x += size.cx;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += 2+18+2;
			}
			*/
			if (pItem->fsStyle & TBSTYLE_SEP)
				cur.x += /*pData[i].*/iBitmap;
			else
				cur.x += pItem->m_size.cx - CX_OVERLAP;

			if (pItem->fsState & TBSTATE_WRAP)
			{
				cur.x = 0;
				cur.y += itemHeight+2;//m_sizeButton.cy;

				if (pItem->fsStyle & TBSTYLE_SEP)
					cur.y += cySep;
			}

			// Set tool rect
			if (pItem->GetCommandID())
			{
#if 0
				m_toolTipCtrl.SetToolRect(m_hWnd, pItem->GetCommandID(), &pItem->m_rc);
#endif
			}
		}

		SysFreeString(text);

		/*
		if (pItem->m_axcontrol)
		{
			pItem->m_axcontrol->MoveWindow(&pItem->m_rc, TRUE);
		}
		*/
#if 0
		if (pItem->m_hWnd)
		{
			CComPtr<IUICommand> cmd;
			item->get_command(&cmd);

			BSTR bwindowClassname;
			cmd->get_windowClassname(&bwindowClassname);
			_bstr_t windowClassname = _bstr_t(bwindowClassname, false);

			int height = pItem->m_rc.Height();

			if (!wcsicmp(windowClassname, L"combobox"))
				height += 260;

			::SetWindowPos(pItem->m_hWnd, NULL, pItem->m_rc.left+(pItem->m_rc.Width()-pItem->m_controlWidth), pItem->m_rc.top, pItem->m_controlWidth, height, SWP_NOZORDER | SWP_NOACTIVATE);
		}
#endif
	}
#endif
}

// IDropTarget
STDMETHODIMP CUIMenuDlg::DragOver(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ASSERT(0);
#if 0
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);

	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
		m_dragInsertIndex = -1;
	}

	BOOL bHandled;
	OnMouseMove(WM_MOUSEMOVE, 0, MAKELPARAM(point.x, point.y), bHandled);
	PopupActiveItem();

	long subitems;
	m_menuItem->CountItems(&subitems);

	if (m_orientation == 0)
	{
		m_dragInsertIndex = ((point.y-4-floatHeight) + itemHeight/2)/itemHeight;
	}
	else
	{
		m_dragInsertIndex = m_items.GetSize();

		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (point.x+m_items[i]->m_pBox->m_outerRect.Width/2 < m_items[i]->m_pBox->m_outerRect.GetRight())
			{
				m_dragInsertIndex = i;
				break;
			}
		}
	}

	if (m_dragInsertIndex < 0) m_dragInsertIndex = 0;
	else if (m_dragInsertIndex > (int)subitems) m_dragInsertIndex = (int)subitems;
	
// Draw new insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
	}

	ReleaseDC(hDC);

	*pdwEffect = DROPEFFECT_COPY | DROPEFFECT_MOVE;
#endif
	return S_OK;
}

STDMETHODIMP CUIMenuDlg::DragLeave()
{
#if 0
	HWND hwnd = m_hWnd;

	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
		m_dragInsertIndex = -1;
	}

	ReleaseDC(hDC);
#endif

	return S_OK;
}

STDMETHODIMP CUIMenuDlg::Drop(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect)
{
	ASSERT(0);
#if 0
	HDC hDC = GetDC();

// Erase previous insert bar
	if (m_dragInsertIndex >= 0)
	{
		DrawInsertBar(hDC, m_dragInsertIndex);
	}

	//ReleaseDC(hDC);

/*
	POINT point;
	point.x = pt.x;
	point.y = pt.y;
	ScreenToClient(&point);
*/

#if 0
	ReleaseCapture();
#endif

	COleDataObjectWrapper dataObject;
	dataObject.Attach(pDataObject);

	HGLOBAL hData;

	if (hData = dataObject.GetGlobalData(CF_HDROP))
	{
#if 0
		DROPFILES* dp = (DROPFILES*)GlobalLock(hData);
		if (dp)
		{
			char* p = (char*)(dp+1);

			int i = 0;
			TCHAR filename[512];
			while (*p)
			{
				filename[i++] = *p++;
			}
			filename[i] = 0;
		}

		GlobalUnlock(hData);
#endif

		*pdwEffect = DROPEFFECT_COPY;
	}
	else if (hData = dataObject.GetGlobalData(RegisterClipboardFormat("MMStudio-Command")))
	{
		long* pguid = (long*)GlobalLock(hData);
		long guid = *pguid;

		//CComQIPtr<IUIContextManager> uiManager;
		//m_menuItem->get_uiManager(&uiManager);

		//m_uiManager

		ASSERT(0);
#if 0
		CComQIPtr<IUICommand> command;
		m_menuItem->m_uiManager->FindCommand(guid, &command);
		if (command)
		{
			CComObject<CMenuItem>* item;
			CComObject<CMenuItem>::CreateInstance(&item);

			item->put_type(MF_STRING);
			item->put_command(command);

			ASSERT(0);
#if 0
			m_menuItem->InsertBefore(m_dragInsertIndex, item);
#endif

			if (m_pDlgSite/*->m_pDockBar*/ == NULL)
			{
				RemoveDispItems();
				CreateSizeDispItemsArray(m_orientation, m_items);

				PlaceItems();

				int width;
				int height;
	
				if (m_orientation == 0)
				{
					long count;
					m_menuItem->CountItems(&count);

					width = 4 + (20 + m_textwidth + 4 + m_shortcutwidth + 20) + 4;
					height = floatHeight + 4 + count*itemHeight + 4;
				}
				else
				{
					CSize size;
					CalcLayout(LM_MRUWIDTH/* | LM_COMMIT*/, 32767, &size);

					width = size.cx;
					height = size.cy;
				}

				SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
			}
			else
			{
				ASSERT(0);
			}
#if 0
			CalculateMaxWidth((HFONT)GetStockObject(DEFAULT_GUI_FONT));

			unsigned long count;
			m_menuItem->CountItems(&count);

		// Resize window
			int width = m_textwidth + 30 + m_shortcutwidth + 24;

			int endWidth = width;
			int endHeight = floatHeight + 4 + count*itemHeight + 4;

			SetWindowPos(hwnd, NULL, 0, 0, endWidth, endHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
#endif
		}
		else
		{
			::MessageBox(NULL, "This command is not registered in the UIManager", "MMStudio", MB_OK);
		}
#endif

		GlobalUnlock(hData);

		*pdwEffect = DROPEFFECT_COPY;
	}

	m_dragInsertIndex = -1;
#endif

	return S_OK;
}
#endif
#endif