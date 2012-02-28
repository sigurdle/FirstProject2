// LFilterMapper.cpp : Implementation of CLFilterMapper
#include "stdafx.h"
#include "LMedia.h"
#include "LFilterMapper.h"

#include "../LXML/LDOMDocument.h"

namespace LMedia
{

/////////////////////////////////////////////////////////////////////////////
// CLFilterMapper

STDMETHODIMP CLFilterMapper::RegisterFilter(REFCLSID clsidFilter, LPCWSTR name, HINSTANCE hInst, long resID)
{
	USES_CONVERSION;

	HRESULT hr = E_FAIL;

	HRSRC hRes = FindResource(hInst, MAKEINTRESOURCE(resID), _T("FILTER"));
	if (hRes)
	{
		HGLOBAL h = LoadResource(hInst, hRes);
		if (h)
		{
			char* p = (char*)GlobalLock(h);

			LXML::CLDOMDocument* document = new LXML::CLDOMDocument;
//			hr = document.CoCreateInstance(CLSID_LDOMDocument);
			//if (FAILED(hr)) return hr;

			bool success = document->loadXML(A2W(p));
			if (success)
			{
				CRegKey filterCatKey;
				filterCatKey.Create(HKEY_CURRENT_USER, "Software\\Lerstad\\LMedia");
				if (filterCatKey)
				{
					LPOLESTR string;
					StringFromCLSID(clsidFilter, &string);

					CRegKey filterKey;
					filterKey.Create(filterCatKey, _bstr_t(string));

					filterKey.SetValue(_bstr_t(p));

					CoTaskMemFree(string);
					
					hr = S_OK;
				}
			}

			GlobalUnlock(p);

			FreeResource(h);
		}
	}

	return hr;
}

}	// LMedia
