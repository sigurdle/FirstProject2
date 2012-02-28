// FEFreeTransform.cpp : Implementation of CFEFreeTransform
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "FEFreeTransform.h"

/////////////////////////////////////////////////////////////////////////////
// CFEFreeTransform

// IPluginFilter
STDMETHODIMP CFEFreeTransform::GetInPinCount(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 1;
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::GetInPinType(long n, long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 2;
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::GetResultType(long* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = 2;
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::GetName(BSTR* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = SysAllocString(L"Free Transform");
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::FrameSetup(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::FrameSetdown(DWORD filterRecord)
{
	return S_OK;
}

STDMETHODIMP CFEFreeTransform::Filter(DWORD dwFilterRecord)
{
	PFILTERRECORD* r = (PFILTERRECORD*)dwFilterRecord;

	return S_OK;
}

STDMETHODIMP CFEFreeTransform::ShowOptions(HWND hParent)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFEFreeTransform::SetPluginFilterClass(IPluginFilterClass *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CFEFreeTransform::GetPluginFilterClass(IPluginFilterClass **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
