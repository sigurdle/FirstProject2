// ElementTimeDlg.cpp : Implementation of CElementTimeDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ElementTimeDlg.h"

#if 0

/////////////////////////////////////////////////////////////////////////////
// CElementTimeDlg

LRESULT CElementTimeDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComObject<CControlsContainer>* p;
	CComObject<CControlsContainer>::CreateInstance(&p);
	if (p)
	{
		m_controlWindow = p;
		p->m_pControlsHandler = this;

		m_controlWindow->Create(m_hWnd);
		m_controlWindow->ShowWindow(SW_SHOW);

	//
		m_controlWindow->AddData(new CXMLStringData(L"@repeatCount", L""));
		// TODO indefinite
		m_controlWindow->AddData(new CXMLStringData(L"@repeatDur", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@speed", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@accelerate", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@decelerate", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@autoReverse", L""));

		m_controlWindow->AddControl(new CXMLControlNumber("repeatCount"));
		m_controlWindow->GetControl("repeatCount")->ConnectData(m_controlWindow->GetData(L"@repeatCount"));

		m_controlWindow->AddControl(new CXMLControlNumber("repeatDur"));
		m_controlWindow->GetControl("repeatDur")->ConnectData(m_controlWindow->GetData(L"@repeatDur"));

		m_controlWindow->AddControl(new CXMLControlNumber("speed"));
		m_controlWindow->GetControl("speed")->ConnectData(m_controlWindow->GetData(L"@speed"));

		m_controlWindow->AddControl(new CXMLControlNumber("accelerate"));
		m_controlWindow->GetControl("accelerate")->ConnectData(m_controlWindow->GetData(L"@accelerate"));

		m_controlWindow->AddControl(new CXMLControlNumber("decelerate"));
		m_controlWindow->GetControl("decelerate")->ConnectData(m_controlWindow->GetData(L"@decelerate"));

		m_controlWindow->AddControl(new CXMLControlCheckbox("autoReverse"));
		m_controlWindow->GetControl("autoReverse")->ConnectData(m_controlWindow->GetData(L"@autoReverse"));
	}

	IDispEventImpl<1, CElementTimeDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

	OnViewGroupSelectionChanged();

	return 1;  // Let the system set the focus
}

LRESULT CElementTimeDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CElementTimeDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	return 0;
}

LRESULT CElementTimeDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	HWND hwnd;
	m_controlWindow->get_hwnd(&hwnd);
	::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);

	return 0;
}

void __stdcall CElementTimeDlg::OnViewGroupSelectionChanged()
{
	BOOL bElementTime = FALSE;

	// Go over all targetElements and check that all supports timing attributes

	long ncount;
	m_viewGroup->GetSelectedCount(&ncount);

	for (int i = 0; i < ncount; i++)
	{
		CComPtr<IESelectedElement> selectedElement;
		m_viewGroup->GetSelectedElementN(i, &selectedElement);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<ILDOMElement> domElement;
		eElement->get_domElement(&domElement);

		bElementTime = TRUE;

		CComQIPtr<ILElementTime> elementTime = domElement;
		if (elementTime == NULL)
		{
			bElementTime = FALSE;
			break;
		}
	}

	if (bElementTime)
	{
		for (int nattr = 0; nattr < m_controlWindow->m_attributes.GetSize(); nattr++)
		{
			CXMLData* pData = m_controlWindow->m_attributes[nattr];

			UpdateData(pData);
		}

		m_controlWindow->ShowWindow(SW_SHOW);
	}
	else
	{
		m_controlWindow->ShowWindow(SW_HIDE);
	}
}

void __stdcall CElementTimeDlg::OnViewGroupSelectionChanging()
{
}

#endif