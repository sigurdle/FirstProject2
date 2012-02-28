// ByteArray.cpp : Implementation of CByteArray
#include "stdafx.h"
#include "LMedia.h"
#include "ByteArray.h"

namespace LMedia
{

/////////////////////////////////////////////////////////////////////////////
// CByteArray

STDMETHODIMP CByteArray::GetArray(/*[out,retval]*/ VARIANT *pVal)
{
	HGLOBAL hGlobal;

	ULARGE_INTEGER pos;
	LARGE_INTEGER li;
	li.QuadPart = 0;
	m_stream->Seek(li, System::IO::STREAM_SEEK_CUR, &pos);

	if (SUCCEEDED(GetHGlobalFromStream(m_stream, &hGlobal)))
	{
		void* data = GlobalLock(hGlobal);

		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = (DWORD)pos.QuadPart;
		SAFEARRAY* psa = SafeArrayCreate(VT_UI1, 1, rgsabound);

		//sa = SafeArrayCreateVector(VT_I1, 0, (DWORD)pos.QuadPart);

		void* pv;
		SafeArrayAccessData(psa, (void**)&pv);

		CopyMemory(pv, data, (DWORD)pos.QuadPart);

		SafeArrayUnaccessData(psa);

		GlobalUnlock(hGlobal);

		VariantInit(pVal);
		pVal->vt = VT_ARRAY | VT_UI1;
		pVal->parray = psa;

		return S_OK;
	}

	return E_FAIL;
}

}	// LMedia
