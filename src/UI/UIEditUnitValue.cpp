// UIEditUnitValue.cpp : Implementation of CUIEditUnitValue

#include "stdafx.h"
#include "UI.h"
#include "UIEditUnitValue.h"

/////////////////////////////////////////////////////////////////////////////
// CUIEditUnitValue

LRESULT CUIEditUnitValue::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IUnknown* p;
	CRect rc(0,0,0,0);

	m_edit.CoCreateInstance(CLSID_UIEdit);

	m_axedit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axedit.AttachControl(m_edit, &p);

	IDispEventImpl<1, CUIEditUnitValue, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>::DispEventAdvise(m_edit);

	return 0;
}

LRESULT CUIEditUnitValue::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<1, CUIEditUnitValue, &DIID__IUIEditEvents	, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_edit);

	m_axedit.DestroyWindow();
	m_edit.Release();

	return 0;
}

LRESULT CUIEditUnitValue::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);
	m_axedit.MoveWindow(0, 0, client.right, client.bottom);

	return 0;
}

HRESULT __stdcall CUIEditUnitValue::OnEditChange()
{
	BSTR str;
	m_edit->GetText(&str);

	m_value = atof(_bstr_t(str));

	SysFreeString(str);

	Fire_change();

	return S_OK;
}

STDMETHODIMP CUIEditUnitValue::get_value(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_value;
	return S_OK;
}

STDMETHODIMP CUIEditUnitValue::put_value(double newVal)
{
	m_value = newVal;

	WCHAR str[256];
	swprintf(str, L"%g", m_value);

	m_edit->SetText(str);

	return S_OK;
}
