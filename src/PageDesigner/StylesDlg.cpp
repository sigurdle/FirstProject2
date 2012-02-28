// StylesDlg.cpp : Implementation of CStylesDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "StylesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CStylesDlg

STDMETHODIMP CStylesDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IStylesDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
