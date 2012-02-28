// ImageToolsDlg.cpp : Implementation of CImageToolsDlg
#include "stdafx.h"
#include "LXImageEditor.h"
#include "Image2.h"
#include "ImageToolsDlg.h"

/*
#include "WebEditorApp.h"	// TODO remove
#include "WebEditorFrame.h"	// TODO remove
extern CWebEditorApp* gApp;	// TODO remove
*/

/////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CImageToolsDlg

LRESULT CImageToolsDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
#endif

#if 0
	CComPtr<IMenuItem> menu;
	uiManager->FindMenu(IDR_IMAGETOOLS, &menu);
	if (menu == NULL)
		return -1;

	CComObject<CUIMenuDlg>::CreateInstance(&m_menuDlg);//.CoCreateInstance(CLSID_UIMenuDlg);
	m_menuDlg->AddRef();

	CComPtr<IMenuItem> menu0;
	menu->GetSubMenu(0, &menu0);

	CComQIPtr<ICommandTarget> targetFrame = gIFrame;
	m_menuDlg->CreateForMenuItem(menu0, m_hWnd, targetFrame, -1);

	menu.Detach();	// ?? Doesn't CreateForMenuItem AddRef()?
#endif

#if 0
	uiManager->AddEventHandler(this);
#endif

	return 0;
}

LRESULT CImageToolsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	if (m_menuDlg)
	{
		m_menuDlg->DestroyWindow();

		m_menuDlg->Release();
		m_menuDlg = NULL;
	}
#endif

	return 0;
}

LRESULT CImageToolsDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	int top = client.bottom-64;

	if (m_menuDlg)
	{
		HWND hwnddlg;
		CComQIPtr<IUIDlg> dlg = m_menuDlg;
		dlg->get_hwnd(&hwnddlg);

		::MoveWindow(hwnddlg, 0, 0, client.right, top, TRUE);
	}

	double nwidth = (client.Width()-2)/3.0;

	m_fillrc = CRect(8, top+6, 8+24, top+6+24);
	m_strokerc = CRect(8+12, top+6+12, 8+24+12, top+6+24+12);

	m_drc[0] = CRect(2, top+48+2, 2+16, top+48+2+14);
	m_drc[1] = CRect(2+16, top+2+48, 2+16+16, top+48+2+14);
	m_drc[2] = CRect(2+16+16, top+2+48, 2+16+16+16, top+48+2+14);

	return 0;
}

LRESULT CImageToolsDlg::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC pdc(m_hWnd);

	return 0;
}

LRESULT CImageToolsDlg::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HDC hDC = (HDC)wParam;

	return TRUE;
}

LRESULT CImageToolsDlg::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);


	return 0;
}

// IUIEventHandler
STDMETHODIMP CImageToolsDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
#if 0
	CComQIPtr<IEXMLViewGroup> viewGroup = object;
	if (viewGroup)
	{
		if (m_viewGroup != NULL)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			m_viewGroup->GetCurrentSelectionCSSStyle(&style);

			style->removeHandler(this);

#if 0
			static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	//		CComQIPtr<ILDOMEventTarget> eventTarget = m_xmlDocument;
	//		eventTarget->removeEventListener(L"DOMNodeInserted", this, VARIANT_TRUE);

	//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
		}

		m_viewGroup = viewGroup;
#if 0
		static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->addHandler(this);
#endif

		CComPtr<ILCSSStyleDeclaration> style;
		m_viewGroup->GetCurrentSelectionCSSStyle(&style);

		style->addHandler(this);

//		IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventAdvise(m_document);

		if (m_hWnd)
		{
			Invalidate();
		}

		*cookie = 1;
	}
#endif

	return S_OK;
}

STDMETHODIMP CImageToolsDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
#if 0
//	ATLASSERT(IsUnknownEqualUnknown(m_document, object));

//	IDispEventImpl<2, CSVGFiltersDlg, &DIID__IWebXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);

	CComPtr<ILCSSStyleDeclaration> style;
	m_viewGroup->GetCurrentSelectionCSSStyle(&style);

	style->removeHandler(this);

#if 0
	static_cast<CWebXMLViewGroup*>(m_viewGroup.p)->m_currentSelectionStyle->removeHandler(this);
#endif
	m_viewGroup.Release();

	if (m_hWnd)
	{
		Invalidate();
	}
#endif
	return S_OK;
}
