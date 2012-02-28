// SwatchLibraryDlg.cpp : Implementation of CSwatchLibraryDlg
#include "stdafx.h"
#include "PageDesigner.h"
#include "SwatchLibraryDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CSwatchLibraryDlg

STDMETHODIMP CSwatchLibraryDlg::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISwatchLibraryDlg
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
