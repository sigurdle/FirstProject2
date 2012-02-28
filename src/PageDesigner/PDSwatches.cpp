#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSwatches.h"

#include "PDSwatchColor.h"
#include "PDSwatchTint.h"
#include "PDSwatchGradient.h"
#include "PDSwatchPattern.h"

#include "ObjectMap.h"

/////////////////////////
// CPDSwatches

int CPDSwatches::FinalConstruct()
{
	CComObject<CObjectMap>::CreateInstance(&m_swatches);
	return 0;
}

void CPDSwatches::FinalRelease()
{
	if (m_swatches)
	{
		for (int i = m_swatches->m_items.GetSize()-1; i >= 0; i--)
		{
			CComQIPtr<INotifySend> cp = m_swatches->m_items[i];
			cp->Unadvise(this);

			/*
			m_items[i]->Release();
			m_items.RemoveAt(i);
			*/
		}
		m_swatches->Release();
		m_swatches = NULL;
	}
}

STDMETHODIMP CPDSwatches::createSwatchColor(IPDSwatchColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSwatchColor>* pSwatch;
	CComObject<CPDSwatchColor>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;
	
	return S_OK;
}

STDMETHODIMP CPDSwatches::createSwatchGradient(IPDSwatchGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSwatchGradient>* pSwatch;
	CComObject<CPDSwatchGradient>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDSwatches::createSwatchTint(IPDSwatchColor *swatchColor, IPDSwatchTint **pVal)
{
	if (pVal == NULL) return E_POINTER;
	if (swatchColor == NULL) return E_POINTER;

	CComObject<CPDSwatchTint>* pSwatch;
	CComObject<CPDSwatchTint>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		pSwatch->m_swatchColor = swatchColor;

		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDSwatches::createSwatchPattern(IPDSwatchPattern **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSwatchPattern>* pSwatch;
	CComObject<CPDSwatchPattern>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;
	
	return S_OK;
}

STDMETHODIMP CPDSwatches::get_length(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatches->m_items.GetSize();
	return S_OK;
}

STDMETHODIMP CPDSwatches::item(long index, IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;
	if (index >= 0 && index < m_swatches->m_items.GetSize())
	{
		*pVal = (IPDSwatch*)m_swatches->m_items[index];
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

HRESULT CPDSwatches::insertSwatch(IPDSwatch* object, IPDSwatch* before)
{
	if (object == NULL) return E_INVALIDARG;

	CPDSwatch<IPDSwatch>* pObject = static_cast<CPDSwatch<IPDSwatch>*>(object);
	CPDSwatch<IPDSwatch>* pBefore = static_cast<CPDSwatch<IPDSwatch>*>(before);

	int refcount = object->AddRef();

// First remove it from previous parent
	if (pObject->m_parent)
	{
		pObject->m_parent->removeSwatch(object);
	}

	CPDSwatch<IPDSwatch>* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousSibling;
	else
		pAfter = m_lastChild;

	pObject->m_nextSibling = pBefore;
	pObject->m_previousSibling = pAfter;

	if (pAfter == NULL)
		m_firstChild = pObject;
	else
		pAfter->m_nextSibling = pObject;

	if (pBefore == NULL)
		m_lastChild = pObject;
	else
		pBefore->m_previousSibling = pObject;

	pObject->m_parent = this;//static_cast<CPDObjectImpl<IPDObject>*>((IPDObject*)this);//static_cast<CComObject<CPDGradient>*>(this);

	HRESULT hr = E_FAIL;

	if (pBefore)
	{
		for (int i = 0; i < m_swatches->m_items.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_swatches->m_items[i], before))
			{
				m_swatches->m_items.InsertAt(i, object);
				hr = S_OK;
				break;
			}
		}
	}
	else
	{
		m_swatches->m_items.Add(object);
		hr = S_OK;
	}

	if (SUCCEEDED(hr))
	{
		CComQIPtr<INotifySend> cp = object;
		DWORD cookie;
		cp->Advise(this, &cookie);

		FireOnChanged(NOTIFY_ADD, object, DISPID_UNKNOWN);
	}

	return hr;
}

STDMETHODIMP CPDSwatches::appendSwatch(IPDSwatch *swatch)
{
	return insertSwatch(swatch, NULL);
}

STDMETHODIMP CPDSwatches::removeSwatch(IPDSwatch *object)
{
	if (object == NULL)
	{
		ATLASSERT(0);
		return E_POINTER;
	}

	CPDSwatch<IPDSwatch>* pObject = static_cast<CPDSwatch<IPDSwatch>*>(object);

	for (int i = 0; i < m_swatches->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_swatches->m_items[i], object))
		{
			CComQIPtr<INotifySend> cp = object;
			cp->Unadvise(this);

			if (pObject->m_previousSibling != NULL)
				pObject->m_previousSibling->m_nextSibling = pObject->m_nextSibling;
			else
				m_firstChild = pObject->m_nextSibling;

			if (pObject->m_nextSibling != NULL)
				pObject->m_nextSibling->m_previousSibling = pObject->m_previousSibling;
			else
				m_lastChild = pObject->m_previousSibling;

			pObject->m_previousSibling = NULL;
			pObject->m_nextSibling = NULL;

			pObject->m_parent = NULL;

			FireOnChanged(NOTIFY_REMOVE, object, DISPID_UNKNOWN);

			object->Release();
			m_swatches->m_items.RemoveAt(i);

			return S_OK;
		}
	}

	ATLASSERT(0);
	return E_FAIL;
}

STDMETHODIMP CPDSwatches::get_firstChild(IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstChild;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CPDSwatches::get_lastChild(IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lastChild;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDSwatches::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->serializeObjectMap(m_swatches);
	return S_OK;
}

STDMETHODIMP CPDSwatches::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CComObject<CObjectMap>* pMap;

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->deserializeObjectMap(pMap, NULL)))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				IPDSwatch* swatch = static_cast<IPDSwatch*>(pMap->m_items[i]);
				insertSwatch(swatch, NULL);
			}
		}
		pMap->Release();
	}

	return S_OK;
}

STDMETHODIMP CPDSwatches::GetClassID(/*[out,retval]*/ CLSID* pClassID)
{
	*pClassID = CLSID_NULL;
	return S_OK;
}
