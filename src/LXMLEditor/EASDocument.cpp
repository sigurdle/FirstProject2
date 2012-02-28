// EASDocument.cpp : Implementation of CEASDocument
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "EASDocument.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CEASDocument

STDMETHODIMP CEASDocument::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEASDocument
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (ATL::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CEASDocument::ShowViews(IEFrame* pFrame)
{
	return S_OK;
}

STDMETHODIMP CEASDocument::Activate()
{
	return S_OK;
}

STDMETHODIMP CEASDocument::CloseDocument()
{
	return S_OK;
}

#endif