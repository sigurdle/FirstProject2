// ErrorListCtl.cpp : Implementation of CErrorListCtl

#include "stdafx.h"
#include "ErrorMod.h"
#include "ErrorListCtl.h"

/////////////////////////////////////////////////////////////////////////////
// CErrorListCtl

LRESULT CErrorListCtl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axerrorListBox.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axerrorListBox.AttachControl(m_errorListBox, &p);

	m_errorListBox->put_multiLine(VARIANT_TRUE);
	m_errorListBox->put_lineNumbers(VARIANT_TRUE);
	m_errorListBox->put_wordWrap(VARIANT_TRUE);
	m_errorListBox->put_vertScroll(VARIANT_TRUE);

	HRESULT hr;

	hr = IDispEventImpl<1, CErrorListCtl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_errorListBox);
	ATLASSERT(SUCCEEDED(hr));

	return 0;
}

LRESULT CErrorListCtl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT hr;

	hr = IDispEventImpl<1, CErrorListCtl, &DIID__IUIEditEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_errorListBox);
	ATLASSERT(SUCCEEDED(hr));

	return 0;
}

LRESULT CErrorListCtl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axerrorListBox.MoveWindow(0, 0, client.right, client.bottom);
	return 0;
}

void __stdcall CErrorListCtl::OnEditDblClick(long offset, long line, long column)
{
	long count;
	m_errorList->GetErrorCount(&count);

	if (line < count)
	{
		CComQIPtr<IErrorItem> error;
		m_errorList->GetErrorItem(line, &error);

		Fire_OnClickError(error);
	}
}

static WCHAR* SeverityString[3] =
{
	L"warning",
	L"error",
	L"fatal error",
};

void CErrorListCtl::FillErrorListBox()
{
	m_errorListBox->SetText(L"");
// TODO, must also release the IErrorItems

	if (m_errorList != NULL)
	{
		long count;
		m_errorList->GetErrorCount(&count);

		for (int i = 0; i < count; i++)
		{
			CComQIPtr<IErrorItem> error;
			m_errorList->GetErrorItem(i, &error);

			long offset;
			error->GetOffset(&offset);

			CComBSTR message;
			error->get_message(&message);

			CComBSTR uri;
			error->get_uri(&uri);

			long severity;
			error->get_severity(&severity);

			WCHAR str[1024];
			swprintf(str, L"%s(%d) : %s: %s", (BSTR)uri, offset, SeverityString[severity], (BSTR)message);

			CComBSTR text;
			m_errorListBox->GetText(&text);

			text += str;
			text += L"\n";

			m_errorListBox->SetText(text);
		}
	}
}

STDMETHODIMP CErrorListCtl::get_errorList(IErrorList **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_errorList;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CErrorListCtl::put_errorList(IErrorList *newVal)
{
	m_errorList = newVal;
	FillErrorListBox();

	return S_OK;
}

STDMETHODIMP CErrorListCtl::UpdateList()
{
	FillErrorListBox();
	return S_OK;
}
