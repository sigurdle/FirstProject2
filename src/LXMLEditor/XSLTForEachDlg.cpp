// XSLTForEachDlg.cpp : Implementation of CXSLTForEachDlg
#include "stdafx.h"

#if 0
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XSLTForEachDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXSLTForEachDlg

LRESULT CXSLTForEachDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CXSLTForEachDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CXSLTForEachDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTForEachDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTForEachDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CXSLTForEachDlg::SetControls()
{
	::EnableWindow(GetDlgItem(IDC_XSLTFOREACH_SELECT), m_webElement != NULL);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		BSTR bselect;
		element->getAttribute(L"select", &bselect);
		_bstr_t select = _bstr_t(bselect, false);

		SetDlgItemText(IDC_XSLTFOREACH_SELECT, select);
	}
	else
	{
		SetDlgItemText(IDC_XSLTFOREACH_SELECT, _T(""));
	}
}

HRESULT __stdcall CXSLTForEachDlg::OnDOMEvent(ILDOMEvent* evt)
{
	SetControls();
	return S_OK;
}

#endif