// PDSymbol.cpp : Implementation of CPDSymbol
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDSymbol.h"

#include "ObjectMap.h"

/////////////////////////////////////////////////////////////////////////////
// CPDSymbol

STDMETHODIMP CPDSymbol::get_symbolObject(IPDObject **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_symbolObject;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDSymbol::put_symbolObject(IPDObject *newVal)
{
	m_symbolObject = newVal;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDSymbol::get_name(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPDSymbol::put_name(BSTR newVal)
{
	m_name = newVal;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDSymbol::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"name", _variant_t(m_name));

	node->putObject(m_symbolObject);

	return S_OK;
}

STDMETHODIMP CPDSymbol::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"name", &v);
	m_name = v;

	CComObject<CObjectMap>* pMap;
	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->deserializeObjectMap(pMap, NULL)))
		{
			if (pMap->m_items.GetSize() == 1)
			{
				m_symbolObject = static_cast<IPDObject*>(pMap->m_items[0]);
			}
		}
		pMap->Release();
	}

	return S_OK;
}
