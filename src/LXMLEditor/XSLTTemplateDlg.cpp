// XSLTTemplateDlg.cpp : Implementation of CXSLTTemplateDlg
#include "stdafx.h"

#if 0
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "XSLTTemplateDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXSLTTemplateDlg

LRESULT CXSLTTemplateDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CXSLTTemplateDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CXSLTTemplateDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTTemplateDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CXSLTTemplateDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CXSLTTemplateDlg::SetControls()
{
	::EnableWindow(GetDlgItem(IDC_XSLTTEMPLATE_MATCH), m_webElement != NULL);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		BSTR bmatch;
		element->getAttribute(L"match", &bmatch);
		_bstr_t match = _bstr_t(bmatch, false);

		SetDlgItemText(IDC_XSLTTEMPLATE_MATCH, match);
	}
	else
	{
		SetDlgItemText(IDC_XSLTTEMPLATE_MATCH, _T(""));
	}
}

HRESULT __stdcall CXSLTTemplateDlg::OnDOMEvent(ILDOMEvent* evt)
{
	SetControls();
	return S_OK;
}

#endif