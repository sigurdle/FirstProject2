// XSLTApplyTemplatesDlg.cpp : Implementation of CXSLTApplyTemplatesDlg
#include "stdafx.h"

#if 0
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XSLTApplyTemplatesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXSLTApplyTemplatesDlg

LRESULT CXSLTApplyTemplatesDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CXSLTApplyTemplatesDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CXSLTApplyTemplatesDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTApplyTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTApplyTemplatesDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CXSLTApplyTemplatesDlg::SetControls()
{
	::EnableWindow(GetDlgItem(IDC_XSLTAPPLYTEMPLATES_SELECT), m_webElement != NULL);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		BSTR bselect;
		element->getAttribute(L"select", &bselect);
		_bstr_t select = _bstr_t(bselect, false);

		SetDlgItemText(IDC_XSLTAPPLYTEMPLATES_SELECT, select);
	}
	else
	{
		SetDlgItemText(IDC_XSLTAPPLYTEMPLATES_SELECT, _T(""));
	}
}

HRESULT __stdcall CXSLTApplyTemplatesDlg::OnDOMEvent(ILDOMEvent* evt)
{
	SetControls();
	return S_OK;
}

#endif