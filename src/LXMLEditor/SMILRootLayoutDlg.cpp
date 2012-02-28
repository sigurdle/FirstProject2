// SMILRootLayoutDlg.cpp : Implementation of CSMILRootLayoutDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0
#include "SMILRootLayoutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSMILRootLayoutDlg

LRESULT CSMILRootLayoutDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return 0;
}

LRESULT CSMILRootLayoutDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CSMILRootLayoutDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CSMILRootLayoutDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CSMILRootLayoutDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CSMILRootLayoutDlg::SetControls()
{
	::EnableWindow(GetDlgItem(IDC_SMILROOTLAYOUT_WIDTH), m_webElement != NULL);
	::EnableWindow(GetDlgItem(IDC_SMILROOTLAYOUT_HEIGHT), m_webElement != NULL);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		CComBSTR width;
		element->getAttribute(L"width", &width);

		CComBSTR height;
		element->getAttribute(L"height", &height);

		SetDlgItemText(IDC_SMILROOTLAYOUT_WIDTH, _bstr_t(width));
		SetDlgItemText(IDC_SMILROOTLAYOUT_HEIGHT, _bstr_t(height));
	}
	else
	{
		SetDlgItemText(IDC_SMILROOTLAYOUT_WIDTH, _T(""));
		SetDlgItemText(IDC_SMILROOTLAYOUT_HEIGHT, _T(""));
	}
}

HRESULT __stdcall CSMILRootLayoutDlg::OnDOMEvent(ILDOMEvent* evt)
{
	SetControls();
	return S_OK;
}

#endif