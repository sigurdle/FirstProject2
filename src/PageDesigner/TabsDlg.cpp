// TabsDlg.cpp : Implementation of CTabsDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "TabsDlg.h"

#include "PDDocumentView.h"
#include "PDObjectSelected.h"

/////////////////////////////////////////////////////////////////////////////
// CTabsDlg

int CTabsDlg::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->FindMenu(IDR_TABS, &m_menu);

	return 0;
}

LRESULT CTabsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	GetDlgControl(IDC_TABS, IID_ITabsControl, (void**)&m_tabsCtl);
	IDispEventImpl<1, CTabsDlg, &DIID__ITabsControlEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_tabsCtl);

	m_hButtonBitmap[0] = CreateMappedBitmap(_Module.GetResourceInstance(), IDB_TABS_ALIGNLEFT, 0, NULL, 0);
	m_hButtonBitmap[1] = CreateMappedBitmap(_Module.GetResourceInstance(), IDB_TABS_ALIGNCENTER, 0, NULL, 0);
	m_hButtonBitmap[2] = CreateMappedBitmap(_Module.GetResourceInstance(), IDB_TABS_ALIGNRIGHT, 0, NULL, 0);
	m_hButtonBitmap[3] = CreateMappedBitmap(_Module.GetResourceInstance(), IDB_TABS_ALIGNDECIMAL, 0, NULL, 0);
	m_hButtonBitmap[4] = CreateMappedBitmap(_Module.GetResourceInstance(), IDB_TABS_POSITIONABOVEFRAME, 0, NULL, 0);

	::SendMessage(GetDlgItem(IDC_TABS_ALIGNLEFT), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hButtonBitmap[0]);
	::SendMessage(GetDlgItem(IDC_TABS_ALIGNCENTER), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hButtonBitmap[1]);
	::SendMessage(GetDlgItem(IDC_TABS_ALIGNRIGHT), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hButtonBitmap[2]);
	::SendMessage(GetDlgItem(IDC_TABS_ALIGNDECIMAL), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hButtonBitmap[3]);

	::SendMessage(GetDlgItem(IDC_TABS_POSITIONABOVEFRAME), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)m_hButtonBitmap[4]);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	::EnableWindow(GetDlgItem(IDC_TABS_X), FALSE/*selected != 0*/);

	return 0;
}

LRESULT CTabsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CTabsDlg, &DIID__ITabsControlEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_tabsCtl);

// ??
	DeleteObject(m_hButtonBitmap[0]);
	DeleteObject(m_hButtonBitmap[1]);
	DeleteObject(m_hButtonBitmap[2]);
	DeleteObject(m_hButtonBitmap[3]);
	DeleteObject(m_hButtonBitmap[4]);

	return 0;
}

LRESULT CTabsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	::MoveWindow(GetDlgItem(IDC_TABS), 0, 20, client.right-16, client.bottom-20, TRUE);
	::MoveWindow(GetDlgItem(IDC_TABS_POSITIONABOVEFRAME), client.right-16, client.bottom-16, 16, 16, TRUE);

	OnSize();
	Invalidate();

	return 0;
}

void CTabsDlg::OnSize()
{
}

LRESULT CTabsDlg::OnPositionAboveTextFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_view && m_view->m_pActiveObject)
	{
		CRect wViewRect;
		m_view->GetWindowRect(&wViewRect);

		CComQIPtr<IPDObjectFrame> frame = m_view->m_pActiveObject->m_object;
		if (frame == NULL)
		{
		}

		if (frame)
		{
			CComQIPtr<IPDObjectTransformable> objectTransformable = frame;

			RectD bounds;
			objectTransformable->get_bounds(&bounds);

			long scrollposX; m_view->m_horz->get_pos(&scrollposX);
			long scrollposY; m_view->m_vert->get_pos(&scrollposY);

			HWND hParent = ::GetParent(GetParent());

			CRect windowSheetRect;
			::GetWindowRect(hParent, &windowSheetRect);

			CRect windowViewRect;
			m_view->GetWindowRect(&windowViewRect);

			//CRect wrect = windowViewRect;
			//AdjustWindowRectEx(&wrect, WS_THICKFRAME | WS_CAPTION | WS_SYSMENU, FALSE, WS_EX_MDICHILD);
			
			CRect clientViewRect = windowViewRect;
			//wViewRect.left = windowViewRect.left + (windowViewRect.left-wrect.left);
			//wViewRect.top = windowViewRect.top;

			CRect desiredRect;
			desiredRect.left = -scrollposX + m_view->m_areaRect.left + clientViewRect.left + (bounds.X + m_view->m_activeSpreadOffset.x)*m_view->m_magnify;
			desiredRect.right = desiredRect.left + min(620, (bounds.Width)*m_view->m_magnify + 16);

			AdjustWindowRectEx(&desiredRect, WS_POPUP | WS_THICKFRAME | WS_CAPTION, FALSE, WS_EX_TOOLWINDOW);

			desiredRect.top = windowSheetRect.top;
			desiredRect.bottom = windowSheetRect.bottom;

			::SetWindowPos(hParent, NULL, desiredRect.left, desiredRect.top, desiredRect.Width(), desiredRect.Height(), SWP_NOZORDER);
		}
	}

	return 0;
}

LRESULT CTabsDlg::OnChangedValueX(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	long selected;
	m_tabsCtl->get_selected(&selected);

	if (selected != 0)
	{
		BOOL bTrans;
		float x = (float)GetDlgItemValue(m_hWnd, IDC_TABS_X, &bTrans);
		if (!bTrans)
		{
			MessageBox("Invalid X value", "PageDesigner", MB_OK);
			return 0;
		}

		if (selected < 0)
		{
			float marginLeft;
			m_textPara->GetLeftIndent(&marginLeft);

			float marginRight;
			m_textPara->GetRightIndent(&marginRight);

			float textIndent;
			m_textPara->GetFirstLineIndent(&textIndent);

			if (selected == -3)
			{
				marginRight = x;
			}
			else if (selected == -2)
			{
				textIndent = x;
			}
			else if (selected == -1)
			{
				marginLeft = x;
			}

			m_textPara->SetIndents(textIndent, marginLeft, marginRight);
		}
		else	// Tab
		{
			float tbPos;
			m_textPara->GetTab(selected-1, &tbPos, NULL, NULL);

			float newtbPos = x;

			if (tbPos != newtbPos)
			{
				long newIndex;
				m_textPara->SetTabPos(selected-1, newtbPos, &newIndex);
				m_tabsCtl->put_selected(newIndex+1);
			}
		}
	}

	return 0;
}

LRESULT CTabsDlg::OnTabAlign(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_tabsCtl->put_tbAlign(wID-IDC_TABS_ALIGNLEFT);
	return 0;
}

void CTabsDlg::SetX(long selected)
{
	if (selected)
	{
		float x;

		if (selected == -3)
		{
			m_textPara->GetRightIndent(&x);
		}
		else if (selected == -2)
		{
			m_textPara->GetFirstLineIndent(&x);
		}
		else if (selected == -1)
		{
			m_textPara->GetLeftIndent(&x);
		}
		else	// Tab
		{
			m_textPara->GetTab(selected-1, &x, NULL, NULL);
		}

		SetDlgItemValue(m_hWnd, IDC_TABS_X, x, UNIT_PT);
	}
	else
	{
		SetDlgItemText(IDC_TABS_X, "");
	}
}

void __stdcall CTabsDlg::OnTabsChanged()
{
	ATLASSERT(m_range != NULL);

	CComPtr<IPDStory> story;
	m_range->GetStory(&story);
	ATLASSERT(story != NULL);

	story->SetTextPara(m_range, m_textPara);
}

void __stdcall CTabsDlg::OnTabsChanging(long selected)
{
	SetX(selected);// Update the X edit control
}

void __stdcall CTabsDlg::OnTabsSelected(long selected)
{
// Update the X edit control
	::EnableWindow(GetDlgItem(IDC_TABS_X), selected != 0);
	SetX(selected);

// Update the align buttons to reflect the currently selected tab
	long align;

	if (selected > 0)
		m_textPara->GetTab(selected-1, NULL, &align, NULL);
	else
		align = -1;	// Unselect

	CheckRadioButton(IDC_TABS_ALIGNLEFT, IDC_TABS_ALIGNDECIMAL, IDC_TABS_ALIGNLEFT+align);
}

STDMETHODIMP CTabsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDDocumentView> view = object;
	if (view)
	{
		m_view = static_cast<CComObject<CPDDocumentView>*>(view.p);
		m_view->AddRef();

		*cookie = 1;
	}
	else
	{
		CComQIPtr<IPDTextRange> range = object;
		if (range)
		{
			ATLASSERT(m_range == NULL);	// Only one range can be active at a time

			m_range = range;	// Remember it

			CComPtr<IPDStory> story;
			m_range->GetStory(&story);

			ATLASSERT(m_textPara == NULL);
			story->GetTextPara(m_range, &m_textPara);

			{
				CComPtr<ILDOMRange> domrange;
				m_range->GetDOMRange(&domrange);

				CComPtr<ILDOMNode> startContainer;
				long startOffset;
				domrange->get_startContainer(&startContainer);
				domrange->get_startOffset(&startOffset);

				CComPtr<IPDObjectText> objectText;
				story->GetObjectTextFromRangePosition(startContainer, startOffset, &objectText);
				if (objectText)
				{
					CComQIPtr<IPDTextFrameOptions> textFrameOptions = objectText;

					double columnsWidth;
					textFrameOptions->get_columnsWidth(&columnsWidth);

					/*
					CComQIPtr<IPDObjectLocatable> locatable = objectText;

					RectD bounds;
					locatable->get_bounds(&bounds);
					*/

					m_tabsCtl->put_pageWidth(columnsWidth/*bounds.Width*/);
				}
			}

			m_tabsCtl->put_textPara(m_textPara);
			m_tabsCtl->put_Enabled(TRUE);

			*cookie = 1;
		}
	}

	if (m_hWnd)
	{
		Invalidate();
		OnSize();
	}

	return S_OK;
}

STDMETHODIMP CTabsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	if (IsUnknownEqualUnknown(object, m_view->GetUnknown()))
	{
		m_view->Release();
		m_view = NULL;
	}
	else if (IsUnknownEqualUnknown(object, m_range))
	{
		m_textPara.Release();
		m_tabsCtl->put_textPara(NULL);
		m_tabsCtl->put_Enabled(FALSE);

		m_range.Release();
	}

	if (m_hWnd)
	{
		Invalidate();
		OnSize();
	}

	return S_OK;
}

BEGIN_CMD_MAP(CTabsDlg)
	CMD_HANDLER(ID_TABS_CLEARALL, OnTabsClearAll)
	CMD_UPDATE(ID_TABS_CLEARALL, OnTabsClearAllUpdate)
END_CMD_MAP()

LRESULT CTabsDlg::OnTabsClearAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_textPara)
	{
		m_textPara->ClearAllTabs();
		OnTabsChanged();	// Set para on story
	}

	return 0;
}

void CTabsDlg::OnTabsClearAllUpdate(long iid, IUICmdUpdate* pCmdUI)
{
	BOOL bEnable = FALSE;
	if (m_textPara)
	{
		long ntabs;
		m_textPara->GetTabCount(&ntabs);
		bEnable = ntabs > 0;
	}

	pCmdUI->Enable(bEnable);
}
