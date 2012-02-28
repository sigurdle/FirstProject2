#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDFilterPrimitive.h"

/////////////////////////////////////
// CPDFilterPrimitive

STDMETHODIMP CPDFilterPrimitive::get_nextSibling(/*[out, retval]*/ IPDFilterPrimitive* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nextSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::put_nextSibling(/*[in]*/ IPDFilterPrimitive* newVal)
{
	m_nextSibling = newVal;
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::get_previousSibling(/*[out, retval]*/ IPDFilterPrimitive* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_previousSibling;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::put_previousSibling(/*[in]*/ IPDFilterPrimitive* newVal)
{
	m_previousSibling = newVal;
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::get_parent(/*[out, retval]*/ IPDAppearance* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_parent;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::put_parent(/*[in]*/ IPDAppearance* newVal)
{
	m_parent = newVal;
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::get_pluginFilter(/*[out, retval]*/ IPluginFilter* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pluginFilter;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::put_pluginFilter(/*[in]*/ IPluginFilter* newVal)
{
	ATLASSERT(m_parent == NULL);	// Cannot change after it's been added

	m_pluginFilter = newVal;
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::get_name(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::GetInPin(/*[in]*/ long n, /*[out,retval]*/ IPDFilterPrimitive* *pVal)
{
	*pVal = m_inpins[n];
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::SetInPin(long n, IPDFilterPrimitive *newVal)
{
	m_inpins[n] = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::GetType(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_type;
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDFilterPrimitive::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	long npincount = GetInPinCount();
	for (int i = 0; i < npincount; i++)
	{
		WCHAR buf[64];
		swprintf(buf, L"in%d", i);
		node->putElement(buf, m_inpins[i]);
	}

	if (m_pluginFilter)
	{
		node->putElement(L"pluginFilter", m_pluginFilter);
	}
	else
	{
	}

	return S_OK;
}

STDMETHODIMP CPDFilterPrimitive::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	node->getElement(L"pluginFilter", NULL, (IUnknown**)&m_pluginFilter);

	return S_OK;
}
