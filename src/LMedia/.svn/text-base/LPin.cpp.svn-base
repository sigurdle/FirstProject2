#include "stdafx.h"
#include "LMediaImpl.h"

#include "LFilterGraph.h"

//////////////////////////////////////////////////////////////////////////
// CDispLPin

#if 0
STDMETHODIMP CDispLPin::get_Pin(IUnknown* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_Pin;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CDispLPin::get_ConnectedTo(IDispatch* *pVal)
{
#if 0
	ILPin* pPin;
	m_Pin->ConnectedTo(&pPin);

	CComPtr<ILBaseFilter> filter;
	pPin->QueryFilter(&filter);
#endif

	return E_FAIL;
}

STDMETHODIMP CDispLPin::get_Filter(IDispatch* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_Filter;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CDispLPin::get_Direction(/*[out,retval]*/ LPIN_DIRECTION *pVal)
{
	return m_Pin->QueryDirection(pVal);
}

STDMETHODIMP CDispLPin::ConnectDirect(/*[in]*/ IUnknown* pPin)
{
	CComQIPtr<ILPin> pinin = pPin;
	if (pinin == NULL) return E_NOINTERFACE;

	return m_Filter->m_pFilterGraph->ConnectDirect(m_Pin, pinin, NULL);
}
#endif