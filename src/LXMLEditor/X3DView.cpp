// X3DView.cpp : Implementation of CX3DView
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "X3DView.h"

#include "ESceneDocument.h"

#if 0
////////////////////////////////////////////////////////////////////////////
// CX3DView

int CX3DView::FinalConstruct()
{
	HRESULT hr;

	hr = m_viewer.CoCreateInstance(CLSID_LX3DViewer);
	if (FAILED(hr)) return hr;

	return S_OK;
}

void CX3DView::FinalRelease()
{
	m_viewer.Release();
}

LRESULT CX3DView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	{
		CComPtr<ILDOMElement> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IESceneDocument> document(unk);

		m_pDocument = static_cast<CESceneDocument*>(document.p);
	}

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axviewer.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axviewer.AttachControl(m_viewer, &p);
	//IDispEventImpl<1, CX3DView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);

	m_viewer->replaceWorld(m_pDocument->m_scene);

	return 0;
}

LRESULT CX3DView::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);


	return 0;
}

LRESULT CX3DView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	//client.InflateRect(-GetSystemMetrics(SM_CXEDGE),-GetSystemMetrics(SM_CYEDGE));

	m_areaRect = client;

	m_axviewer.MoveWindow(m_areaRect.left, m_areaRect.top, m_areaRect.Width(), m_areaRect.Height());
	//m_vert->SetInfo(0, y, (m_areaRect.Height()));

	return 0;
}

#if 0
void __stdcall CX3DView::OnVertScroll(long code, long pos)
{
	long oldPos; m_vert->get_pos(&oldPos);

	/*
	if (m_edit)
	{
		CRect wrect;
		::GetWindowRect(m_edit, &wrect);
		ScreenToClient((LPPOINT)&wrect.left);
		ScreenToClient((LPPOINT)&wrect.right);
		::SetWindowPos(m_edit, NULL, wrect.left, wrect.top + (oldPos-pos), 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOREDRAW);
	}
	*/

	CRect	rect = m_areaRect;
	m_vert->put_pos(pos);
	//ScrollWindow(0, (oldPos-pos)*16, &rect, &rect);
	Invalidate();
}
#endif

#endif