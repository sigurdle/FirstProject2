// HTMLFrameSetDlg.cpp : Implementation of CHTMLFrameSetDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "WebEditor2.h"

#include "HTMLFrameSetDlg.h"

#include "WebEditorApp.h"	// TODO remove

/////////////////////////////////////////////////////////////////////////////
// CHTMLFrameSetDlg

LRESULT CHTMLFrameSetDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_ADDSTRING, 0, (LPARAM)_T("values"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_ADDSTRING, 0, (LPARAM)_T("from-to"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_ADDSTRING, 0, (LPARAM)_T("from-by"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_ADDSTRING, 0, (LPARAM)_T("by"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_ADDSTRING, 0, (LPARAM)_T("to"));

	::SendMessage(GetDlgItem(IDC_SMILANIMATE_CALCMODE), CB_ADDSTRING, 0, (LPARAM)_T("discrete"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_CALCMODE), CB_ADDSTRING, 0, (LPARAM)_T("linear"));
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_CALCMODE), CB_ADDSTRING, 0, (LPARAM)_T("paced"));
*/
	return 0;
}

LRESULT CHTMLFrameSetDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

class CFrameSetBorderColor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IEColor
{
public:
	CFrameSetBorderColor()
	{
	}

	CComPtr<ILHTMLFrameSetElement> m_frameSetElement;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CFrameSetBorderColor)
	COM_INTERFACE_ENTRY(IEColor)
END_COM_MAP()

public:
	STDMETHOD(get_red)(long *pVal)
	{
		long colorValue;
		m_frameSetElement->get_borderColorRGBValue(&colorValue);

		*pVal = GetRValue(colorValue);

		return S_OK;
	}
	STDMETHOD(get_green)(long *pVal)
	{
		long colorValue;
		m_frameSetElement->get_borderColorRGBValue(&colorValue);

		*pVal = GetGValue(colorValue);

		return S_OK;
	}
	STDMETHOD(get_blue)(long *pVal)
	{
		long colorValue;
		m_frameSetElement->get_borderColorRGBValue(&colorValue);

		*pVal = GetBValue(colorValue);

		return S_OK;
	}
	STDMETHOD(setRGBValue)(long red, long green, long blue)
	{
		return m_frameSetElement->put_borderColorRGBValue(RGB(red, green, blue));
	}
};

LRESULT CHTMLFrameSetDlg::OnClickedBorderColorValue(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		CComQIPtr<ILHTMLFrameSetElement> frameSetElement = element;
		ATLASSERT(frameSetElement);

		CComObject<CFrameSetBorderColor>* pEColor;
		CComObject<CFrameSetBorderColor>::CreateInstance(&pEColor);
		pEColor->m_frameSetElement = frameSetElement;

		gApp->m_frame->EditColor(pEColor);
	}

	return 0;
}

LRESULT CHTMLFrameSetDlg::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT idCtl = (UINT)wParam;             // control identifier 
	LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam; // item-drawing information 

	CRect& rcItem = *(CRect*)&lpdis->rcItem;

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		if (idCtl == IDC_HTMLFRAMESET_BORDERCOLORVALUE)
		{
			CComQIPtr<ILHTMLFrameSetElement> frameSetElement = element;
			ATLASSERT(frameSetElement);

			long colorValue;
			frameSetElement->get_borderColorRGBValue(&colorValue);

			FillSolidRect(lpdis->hDC, &rcItem, colorValue);
		}
	}

	return 0;
}

LRESULT CHTMLFrameSetDlg::OnClickedFrameSpacing(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_bChanging++;

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		int b = IsDlgButtonChecked(IDC_HTMLFRAMESET_FRAMESPACING);

		if (b)
		{
			int framespacingValue = GetDlgItemInt(IDC_HTMLFRAMESET_FRAMESPACINGVALUE);

			WCHAR buf[64];
			swprintf(buf, L"%d", framespacingValue);

			element->setAttribute(L"framespacing", _bstr_t(buf));
		}
		else
		{
			element->removeAttribute(L"framespacing");
		}
	}

	m_bChanging--;

	return 0;
}

STDMETHODIMP CHTMLFrameSetDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CHTMLFrameSetDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CHTMLFrameSetDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CHTMLFrameSetDlg::SetControls()
{
	/*
	::EnableWindow(GetDlgItem(IDC_SMILANIMATE_TYPE), m_webElement != NULL);
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, -1, 0);
	*/

	::InvalidateRect(GetDlgItem(IDC_HTMLFRAMESET_BORDERCOLORVALUE), NULL, TRUE);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->get_domElement(&element);

		CComBSTR rows;
		element->getAttribute(L"rows", &rows);

		CComBSTR cols;
		element->getAttribute(L"cols", &cols);

		int nOrientation = -1;

		if (rows.Length() && cols.Length())
		{
			nOrientation = 2;
		}
		else if (rows.Length())
		{
			nOrientation = 1;
		}
		else if (cols.Length())
		{
			nOrientation = 0;
		}

		CheckRadioButton(IDC_HTMLFRAMESET_ORIENTATION0, IDC_HTMLFRAMESET_ORIENTATION2, IDC_HTMLFRAMESET_ORIENTATION0+nOrientation);
	}
	else
	{
		CheckRadioButton(IDC_HTMLFRAMESET_ORIENTATION0, IDC_HTMLFRAMESET_ORIENTATION2, 0);
	}
}

HRESULT __stdcall CHTMLFrameSetDlg::OnDOMEvent(ILDOMEvent* evt)
{
	if (m_bChanging == 0)
	{
		SetControls();
	}

	return S_OK;
}
