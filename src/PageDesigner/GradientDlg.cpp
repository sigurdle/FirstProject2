// GradientDlg.cpp : Implementation of CGradientDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "GradientDlg.h"

/*
#include "PageDesignerApp.h"
#include "PageDesignerFrame.h"

extern CPageDesignerApp* gApp;
*/

/////////////////////////////////////////////////////////////////////////////
// CGradientDlg

LRESULT CGradientDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_gradientEdit.CoCreateInstance(CLSID_GradientEdit);
	IDispEventImpl<1, CGradientDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventAdvise(m_gradientEdit);

	CRect rc(0,0,0,0);
	IUnknown* p;

	m_axgradientEdit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axgradientEdit.AttachControl(m_gradientEdit, &p);

	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->AddEventHandler(this);

	return 0;
}

LRESULT CGradientDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->RemoveEventHandler(this);

	m_axgradientEdit.DestroyWindow();

	IDispEventImpl<1, CGradientDlg, &DIID__IGradientEditEvents, &LIBID_PAGEDESIGNERLib, 1, 0>::DispEventUnadvise(m_gradientEdit);
	m_gradientEdit.Release();

	return 0;
}

LRESULT CGradientDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axgradientEdit.MoveWindow(0, 0, client.right, 42);

	return 0;
}

void __stdcall CGradientDlg::OnClickGradientEmpty()
{
	HRESULT hr;

	for (int i = 0; i < m_targetObjects.GetSize(); i++)
	{
		CComPtr<IPDObjectFrame> frame = m_targetObjects[i];

		CComPtr<IPDBrush> brush;

		ATLASSERT(0);
#if 0
		if (gApp->m_strokeOrFill == 0)
		{
			frame->get_strokeBrush(&brush);
		}
		else
		{
			frame->get_fillBrush(&brush);
		}
		#endif

		CComPtr<IPDGradient> gradient;
		brush->setGradient(&gradient);

		CComPtr<IPDGradientStop> stop0;
		gradient->createStop(&stop0);
		stop0->put_offset(0);
		stop0->setColorRGB(0, 0, 0);

		CComPtr<IPDGradientStop> stop1;
		gradient->createStop(&stop1);
		stop1->put_offset(1);
		stop1->setColorRGB(255, 255, 255);

		gradient->append(stop0);
		gradient->append(stop1);

		if (i == 0)
			m_gradientEdit->put_gradient(gradient);
	}
}

void __stdcall CGradientDlg::OnClickStop(IPDGradientStop* stop)
{
	CComQIPtr<IUIManager> uiManager = gIFrame;
	uiManager->ActivateObject(NULL, stop);
}

STDMETHODIMP CGradientDlg::handleActivateObjectEvent(IUnknown* object, long* cookie)
{
	CComQIPtr<IPDObjectFrame> frame = object;
	if (frame)
	{
		m_targetObjects.Add(frame);
		frame.Detach();

		*cookie = m_targetObjects.GetSize();

//		SetControlValues();
	}

	return S_OK;
}

STDMETHODIMP CGradientDlg::handleDeactivateObjectEvent(IUnknown* object, long cookie, BOOL* bAllow)
{
	m_targetObjects[cookie-1]->Release();
	m_targetObjects.RemoveAt(cookie-1);

//	SetControlValues();

	return S_OK;
}
