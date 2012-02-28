#include "stdafx.h"
#include "LXMLEditor2.h"

#if 0
#include "HTMLFrameDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CHTMLFrameDlg

LRESULT CHTMLFrameDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_wndName.SubclassWindow(GetDlgItem(IDC_HTMLFRAME_NAME));
	m_wndSrc.SubclassWindow(GetDlgItem(IDC_HTMLFRAME_SRC));

	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SIZEUNIT), CB_ADDSTRING, 0, (LPARAM)_T("pixel"));
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SIZEUNIT), CB_ADDSTRING, 0, (LPARAM)_T("percent"));
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SIZEUNIT), CB_ADDSTRING, 0, (LPARAM)_T("scale"));

	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_ADDSTRING, 0, (LPARAM)_T("auto"));
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_ADDSTRING, 0, (LPARAM)_T("no"));
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_ADDSTRING, 0, (LPARAM)_T("yes"));

	return 0;
}

LRESULT CHTMLFrameDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CHTMLFrameDlg::OnNameKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_webElement)
	{
		if ((uMsg == WM_KILLFOCUS) ||
			(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
		{
			CComPtr<ILDOMElement> element;
			m_webElement->get_domElement(&element);

			TCHAR buf[512];
			GetDlgItemText(IDC_HTMLFRAME_NAME, buf, sizeof(buf));

			m_bChanging++;
			element->setAttribute(L"name", _bstr_t(buf));
			m_bChanging--;

			if (uMsg == WM_KEYDOWN)
				return 0;
		}
	}

	return m_wndName.DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CHTMLFrameDlg::OnSrcKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_webElement)
	{
		if ((uMsg == WM_KILLFOCUS) ||
			(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
		{
			CComPtr<ILDOMElement> element;
			m_webElement->get_domElement(&element);

			TCHAR buf[512];
			GetDlgItemText(IDC_HTMLFRAME_SRC, buf, sizeof(buf));

			m_bChanging++;
			element->setAttribute(L"src", _bstr_t(buf));
			m_bChanging--;

			if (uMsg == WM_KEYDOWN)
				return 0;
		}
	}

	return m_wndSrc.DefWindowProc(uMsg, wParam, lParam);
}

LRESULT CHTMLFrameDlg::OnChangeScrolling(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bChanging++;

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		int index = ::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_GETCURSEL, 0, 0);

		if (index == 1)
		{
			element->setAttribute(L"scrolling", L"no");
		}
		else if (index == 2)
		{
			element->setAttribute(L"scrolling", L"yes");
		}
		else // auto
		{
			element->removeAttribute(L"scrolling");
		}
	}

	m_bChanging--;

	return 0;
}

LRESULT CHTMLFrameDlg::OnClickedNoResize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bChanging++;

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		int b = IsDlgButtonChecked(IDC_HTMLFRAME_NORESIZE);
		if (b)
		{
			element->setAttribute(L"noresize", L"noresize");
		}
		else
		{
			element->removeAttribute(L"noresize");
		}
	}

	m_bChanging--;

	return 0;
}

STDMETHODIMP CHTMLFrameDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CHTMLFrameDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CHTMLFrameDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CHTMLFrameDlg::SetControls()
{
	::EnableWindow(GetDlgItem(IDC_HTMLFRAME_SIZE), m_webElement != NULL);
	::EnableWindow(GetDlgItem(IDC_HTMLFRAME_SIZEUNIT), m_webElement != NULL);
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SIZEUNIT), CB_SETCURSEL, -1, 0);

	::EnableWindow(GetDlgItem(IDC_HTMLFRAME_NAME), m_webElement != NULL);
	::EnableWindow(GetDlgItem(IDC_HTMLFRAME_SRC), m_webElement != NULL);

	::EnableWindow(GetDlgItem(IDC_HTMLFRAME_SCROLLING), m_webElement != NULL);
	::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_SETCURSEL, -1, 0);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

	// name
		CComBSTR name;
		element->getAttribute(L"name", &name);
		SetDlgItemText(IDC_HTMLFRAME_NAME, _bstr_t((BSTR)name));

	// src
		CComBSTR src;
		element->getAttribute(L"src", &src);
		SetDlgItemText(IDC_HTMLFRAME_SRC, _bstr_t((BSTR)src));

	// scrolling
		CComBSTR scrolling;
		element->getAttribute(L"scrolling", &scrolling);

		int nScrolling = 0;	// auto
		if (scrolling.Length())
		{
			if (!wcsicmp(scrolling, L"no"))
				nScrolling = 1;
			else if (!wcsicmp(scrolling, L"yes"))
				nScrolling = 2;
		}

		::SendMessage(GetDlgItem(IDC_HTMLFRAME_SCROLLING), CB_SETCURSEL, nScrolling, 0);

	// noresize
		VARIANT_BOOL noresize;
		element->hasAttribute(L"noresize", &noresize);

		CheckDlgButton(IDC_HTMLFRAME_NORESIZE, noresize?BST_CHECKED:BST_UNCHECKED);
	}
	else
	{
		SetDlgItemText(IDC_HTMLFRAME_NAME, _T(""));
		SetDlgItemText(IDC_HTMLFRAME_SRC, _T(""));
	}
}

HRESULT __stdcall CHTMLFrameDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_bChanging == 0)
	{
		SetControls();
	}

	return S_OK;
}

#endif