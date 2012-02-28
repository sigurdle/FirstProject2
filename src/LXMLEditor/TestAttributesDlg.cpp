// TestAttributesDlg.cpp : Implementation of CTestAttributesDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "TestAttributesDlg.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CTestAttributesDlg

LRESULT CTestAttributesDlg::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComObject<CControlsContainer>* p;
	CComObject<CControlsContainer>::CreateInstance(&p);
	if (p)
	{
		m_controlWindow = p;
		p->m_pControlsHandler = this;

		m_controlWindow->Create(m_hWnd);
		m_controlWindow->ShowWindow(SW_SHOW);

	// Data
		m_controlWindow->AddData(new CXMLStringData(L"@systemLanguage", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@systemBitrate", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@systemOperatingSystem", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@requiredFeatures", L""));
		m_controlWindow->AddData(new CXMLStringData(L"@requiredExtensions", L""));

	// Controls
		m_controlWindow->AddControl(new CXMLControlString("systemLanguage"));
		m_controlWindow->GetControl("systemLanguage")->ConnectData(m_controlWindow->GetData(L"@systemLanguage"));

		//m_controlWindow->AddControl(new CXMLControlNumber("systemBitrate"));
		//m_controlWindow->GetControl("systemBitrate")->ConnectData(m_controlWindow->GetData(L"@systemBitrate"));
		m_controlWindow->AddControl(new CXMLControlPopup("systemBitrate", L"0|28800|33600|56600|64000|128000|256000|384000|512000|768000|1000000|1500000|10000000"));
		m_controlWindow->GetControl("systemBitrate")->ConnectData(m_controlWindow->GetData(L"@systemBitrate"));

		m_controlWindow->AddControl(new CXMLControlPopup("systemOperatingSystem", L"aix|beos|bsdi|dgux|freebsd|hpux|irix|linux|macos|ncr|nec|netbsd|nextstep|nto|openbsd|openvms|os2|osf|palmos|qnx|sinix|rhapsody|sco|solaris|sonly|sunos|unixware|win16|win32|win9x|winnt|wince||unknown"));
		m_controlWindow->GetControl("systemOperatingSystem")->ConnectData(m_controlWindow->GetData(L"@systemOperatingSystem"));

		m_controlWindow->AddControl(new CXMLControlString("requiredFeatures"));
		m_controlWindow->GetControl("requiredFeatures")->ConnectData(m_controlWindow->GetData(L"@requiredFeatures"));

		m_controlWindow->AddControl(new CXMLControlString("requiredExtensions"));
		m_controlWindow->GetControl("requiredExtensions")->ConnectData(m_controlWindow->GetData(L"@requiredExtensions"));

		if (FALSE/*TRUE*/)	// Maybe only supported for SMIL ?
		{
		// CustomTestArgumentValue := IDREF (S? '+' S? IDREF)*
			m_controlWindow->AddData(new CXMLStringData(L"@customTest", L""));

			m_controlWindow->AddControl(new CXMLControlString("customTest"));
			m_controlWindow->GetControl("customTest")->ConnectData(m_controlWindow->GetData(L"@customTest"));
		}
	}

	IDispEventImpl<1, CTestAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_viewGroup);

	OnViewGroupSelectionChanged();

	return 0;
}

LRESULT CTestAttributesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CTestAttributesDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_viewGroup);

	return 0;
}

LRESULT CTestAttributesDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	HWND hwnd;
	m_controlWindow->get_hwnd(&hwnd);
	::MoveWindow(hwnd, 0, 0, client.right, client.bottom, TRUE);

	return 0;
}

void __stdcall CTestAttributesDlg::OnViewGroupSelectionChanged()
{
	BOOL bTests = FALSE;

	// Go over all targetElements and check that all supports test attributes

/*
TODO, if I decide to support different test attributes for SMIL and SVG,
I must also check for namespaceURI on each element
*/

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

		bTests = TRUE;

		CComQIPtr<ILSVGTests> tests = domElement;
		if (tests == NULL)
		{
			bTests = FALSE;
			break;
		}
	}

	if (bTests)
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

void __stdcall CTestAttributesDlg::OnViewGroupSelectionChanging()
{
}

#endif