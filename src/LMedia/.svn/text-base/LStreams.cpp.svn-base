// LStreams.cpp : Implementation of CLStreams
#include "stdafx.h"
#include "LMediaImpl.h"
#include "LStreams.h"

#if 0
/////////////////////////////////////////////////////////////////////////////
// CLStreams

STDMETHODIMP CLStreams::get_Count(/*[out,retval]*/ long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_items.GetSize();
	return S_OK;
}

STDMETHODIMP CLStreams::Item(long index, DispILMediaStream* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	if (index >= 0 && index < m_items.GetSize())
	{
		*pVal = m_items[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;
	return S_OK;
}

STDMETHODIMP CLStreams::get__newEnum(/*out,retval*/ IUnknown* *pVal)
{
	*pVal = NULL;
	return S_OK;
}

#endif