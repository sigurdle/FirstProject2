#pragma once

#include "PDTextRangeImpl.h"

class ATL_NO_VTABLE CPDTextRange : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDTextRangeImpl<IPDTextRange>
{
public:
	CPDTextRange()
	{
	}

	int FinalConstruct()
	{
	//	HRESULT hr;

	//	hr = m_domrange.CoCreateInstance(CLSID_Range);
	//	if (FAILED(hr)) return hr;

		return S_OK;
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDTextRange)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDTextRange)
END_COM_MAP()

public:
};
