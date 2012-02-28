// TextWrapDlg.cpp : Implementation of CTextWrapDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "TextWrapDlg.h"

#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"

extern CPageDesignerApp* gApp;

#if 0
/////////////////////////////////////////////////////////////////////////////
// CTextWrapDlg

LRESULT CTextWrapDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_hImageList = ImageList_LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TEXTWRAP), 18, 0, RGB(192, 192, 192), IMAGE_BITMAP, LR_SHARED);

	GetDlgControl(IDC_TEXTWRAP_NONE, IID_IUIButton, (void**)&m_wrapCtl[0]);
	GetDlgControl(IDC_TEXTWRAP_BBOX, IID_IUIButton, (void**)&m_wrapCtl[1]);
	GetDlgControl(IDC_TEXTWRAP_SHAPE, IID_IUIButton, (void**)&m_wrapCtl[2]);
	GetDlgControl(IDC_TEXTWRAP_OBJECT, IID_IUIButton, (void**)&m_wrapCtl[3]);
	GetDlgControl(IDC_TEXTWRAP_COLUMN, IID_IUIButton, (void**)&m_wrapCtl[4]);

	IDispEventImpl<1, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_wrapCtl[0]);
	IDispEventImpl<2, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_wrapCtl[1]);
	IDispEventImpl<3, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_wrapCtl[2]);
	IDispEventImpl<4, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_wrapCtl[3]);
	IDispEventImpl<5, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_wrapCtl[4]);

	for (int i = 0; i < 5; i++)
	{
		m_wrapCtl[i]->put_imageList((DWORD)m_hImageList);
		m_wrapCtl[i]->put_imageIndex(i);
	}

	CComQIPtr<IUIManager> uiManager = gApp->m_frame;
	uiManager->AddEventHandler(this);

	return 1;  // Let the system set the focus
}

LRESULT CTextWrapDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gApp->m_frame;
	uiManager->RemoveEventHandler(this);

	IDispEventImpl<1, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_wrapCtl[0]);
	IDispEventImpl<2, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_wrapCtl[1]);
	IDispEventImpl<3, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_wrapCtl[2]);
	IDispEventImpl<4, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_wrapCtl[3]);
	IDispEventImpl<5, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_wrapCtl[4]);

	return 0;
}

void CTextWrapDlg::SetControlValues()
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDObject> object = m_targetObjects[i];
		PDTextWrap wrap;
		object->get_textWrap(&wrap);

		for (int j = 0; j < 5; j++)
		{
			m_wrapCtl[j]->put_checked(wrap == (PDTextWrap)j);
		}
	}
}

void CTextWrapDlg::SetTextWrap(PDTextWrap wrap)
{
	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDObject> object = m_targetObjects[i];
		object->put_textWrap(wrap);
	}

	SetControlValues();
}

STDMETHODIMP CTextWrapDlg::handleActivateObjectEvent(IUnknown* unk, long* cookie)
{
	CComQIPtr<IPDObject> object = unk;
	if (object)
	{
		m_targetObjects.Add(object);
		object.Detach();

		*cookie = m_targetObjects.GetSize();

		SetControlValues();
	}

	return S_OK;
}

STDMETHODIMP CTextWrapDlg::handleDeactivateObjectEvent(IUnknown* unk, long cookie, BOOL* bAllow)
{
	m_targetObjects[cookie-1]->Release();
	m_targetObjects.RemoveAt(cookie-1);

	SetControlValues();

	return S_OK;
}

void __stdcall CTextWrapDlg::OnClickNone()
{
	SetTextWrap(TEXTWRAP_NONE);
}

void __stdcall CTextWrapDlg::OnClickBBox()
{
	SetTextWrap(TEXTWRAP_BBOX);
}

void __stdcall CTextWrapDlg::OnClickShape()
{
	SetTextWrap(TEXTWRAP_SHAPE);
}

void __stdcall CTextWrapDlg::OnClickObject()
{
	SetTextWrap(TEXTWRAP_JUMPOBJECT);
}

void __stdcall CTextWrapDlg::OnClickColumn()
{
	SetTextWrap(TEXTWRAP_JUMPCOLUMN);
}

#endif