#include "stdafx.h"
#include "PageDesigner.h"

#include "ObjectMap.h"

/////////////////////////
// CObjectMap

void CObjectMap::FinalRelease()
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		m_items[i]->Release();
	}
}

STDMETHODIMP CObjectMap::get_length(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_items.GetSize();
	return S_OK;
}

STDMETHODIMP CObjectMap::item(long index, IUnknown** pVal)
{
	if (index >= 0 && index < m_items.GetSize())
	{
		*pVal = m_items[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CObjectMap::Serialize(IArchive *ar, IArchiveElement* node)
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
		CComQIPtr<IObjectSerializable> object = m_items[i];
		if (object)
		{
			node->putElement(L"object", _variant_t(object));
		}
	}

	return S_OK;
}

STDMETHODIMP CObjectMap::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}
