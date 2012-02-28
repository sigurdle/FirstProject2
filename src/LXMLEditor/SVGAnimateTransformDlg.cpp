// SVGAnimateTransformDlg.cpp : Implementation of CSVGAnimateTransformDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#if 0
#include "SVGAnimateTransformDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSVGAnimateTransformDlg

LRESULT CSVGAnimateTransformDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CSVGAnimateTransformDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

STDMETHODIMP CSVGAnimateTransformDlg::SetElement(IEElement *webElement)
{
	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CSVGAnimateTransformDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(document);
	}

	m_webElement = webElement;

	if (m_webElement)
	{
		CComPtr<IEXMLDocument> document;
		m_webElement->get_ownerDocument(&document);

		IDispEventImpl<2, CSVGAnimateTransformDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(document);
	}

	SetControls();

	return S_OK;
}

void CSVGAnimateTransformDlg::SetControls()
{
	/*
	::EnableWindow(GetDlgItem(IDC_SMILANIMATE_TYPE), m_webElement != NULL);
	::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, -1, 0);

	if (m_webElement)
	{
		CComPtr<ILDOMElement> element;
		m_webElement->GetElement(&element);

		//CComQIPtr<ILAnimatiSVGEllipseElement> ellipse = element;

		BSTR bstr;

		CComBSTR from;
		element->getAttribute(L"from", &from);

		CComBSTR by;
		element->getAttribute(L"by", &by);

		CComBSTR to;
		element->getAttribute(L"to", &to);

		CComBSTR values;
		element->getAttribute(L"values", &values);

		if (values.Length())
		{
			::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, 0, 0);
		}
		else if (from.Length())
		{
			if (to.Length())
			{
				::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, 1, 0);
			}
			else if (by.Length())
			{
				::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, 2, 0);
			}
		}
		else if (by.Length())
		{
			::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, 3, 0);
		}
		else if (to.Length())
		{
			::SendMessage(GetDlgItem(IDC_SMILANIMATE_TYPE), CB_SETCURSEL, 4, 0);
		}
	}
	else
	{
	}
	*/
}

HRESULT __stdcall CSVGAnimateTransformDlg::OnDOMEvent(ILDOMEvent* evt)
{
	SetControls();
	return S_OK;
}

#endif