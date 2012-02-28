#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDGradient.h"

#include "ObjectMap.h"
#include "PDGradientStop.h"
#include "PDColor.h"

/////////////////////////
// CPDGradient

int CPDGradient::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CObjectMap>::CreateInstance(&m_stops);
	if (FAILED(hr)) return hr;
	m_stops->AddRef();

	return S_OK;
}

void CPDGradient::FinalRelease()
{
	if (m_stops)
	{
		for (int i = 0; i < m_stops->m_items.GetSize(); i++)
		{
			CComQIPtr<INotifySend> cp = m_stops->m_items[i];
			cp->Unadvise(this);
		}

		m_stops->Release();
		m_stops = NULL;
	}
}

STDMETHODIMP CPDGradient::get_type(PDGradientType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_type;
	return S_OK;
}

STDMETHODIMP CPDGradient::put_type(PDGradientType newVal)
{
	m_type = newVal;
	return S_OK;
}

STDMETHODIMP CPDGradient::get_stops(/*[out,retval]*/ IObjectMap* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_stops;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDGradient::append(IPDGradientStop *stop)
{
	if (stop == NULL) return E_INVALIDARG;

	CComObject<CPDGradientStop>* pStop = static_cast<CComObject<CPDGradientStop>*>(stop);

	stop->AddRef();

// Remove first from any previous gradient
	if (pStop->m_parent)
	{
		pStop->m_parent->removeStop(pStop);
	}

	int beforeIndex = -1;
	CComObject<CPDGradientStop>* pBefore = NULL;

	for (int i = 0; i < m_stops->m_items.GetSize(); i++)
	{
		CComObject<CPDGradientStop>* p = static_cast<CComObject<CPDGradientStop>*>((IPDGradientStop*)(m_stops->m_items[i]));
		if (pStop->m_offset < p->m_offset)
		{
			beforeIndex = i;
			pBefore = p;
			break;
		}
	}

	CComObject<CPDGradientStop>* pAfter;

	if (pBefore)
		pAfter = pBefore->m_previousSibling;
	else
		pAfter = m_lastChild;

	pStop->m_nextSibling = pBefore;
	pStop->m_previousSibling = pAfter;

	if (pAfter == NULL)
		m_firstChild = pStop;
	else
		pAfter->m_nextSibling = pStop;

	if (pBefore == NULL)
		m_lastChild = pStop;
	else
		pBefore->m_previousSibling = pStop;

	pStop->m_parent = static_cast<CComObject<CPDGradient>*>(this);
	if (pBefore)
		m_stops->m_items.InsertAt(beforeIndex, stop);
	else
		m_stops->m_items.Add(stop);

	DWORD cookie;
	pStop->Advise(this, &cookie);

	FireOnChanged(NOTIFY_ADD, stop, DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDGradient::createStop(IPDGradientStop **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDGradientStop>* stop;
	CComObject<CPDGradientStop>::CreateInstance(&stop);
	if (stop)
	{
		*pVal = stop;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGradient::removeStop(IPDGradientStop *stop)
{
	CPDGradientStop* pObject = static_cast<CPDGradientStop*>(stop);

	for (int i = 0; i < m_stops->m_items.GetSize(); i++)
	{
		if (m_stops->m_items[i] == stop)
		{
			//ATLASSERT(pObject->m_parent == this);

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

			pObject->Unadvise(this);

			FireOnChanged(NOTIFY_REMOVE, stop, DISPID_UNKNOWN);

			pObject->Release();
			m_stops->m_items.RemoveAt(i);

			return S_OK;
		}
	}

	return S_OK;
}

STDMETHODIMP CPDGradient::get_firstChild(IPDGradientStop **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_firstChild;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDGradient::get_lastChild(IPDGradientStop **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_lastChild;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDGradient::Equals(IPDGradient *gradient, VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	if (gradient == NULL) return E_INVALIDARG;

	CComObject<CPDGradient>* pGradient = static_cast<CComObject<CPDGradient>*>(gradient);

	*pVal = VARIANT_FALSE;

	if (m_type != pGradient->m_type)
	{
		return S_OK;
	}

	if (m_stops->m_items.GetSize() != pGradient->m_stops->m_items.GetSize())
	{
		return S_OK;
	}

	for (int i = 0; i < m_stops->m_items.GetSize(); i++)
	{
		CComObject<CPDGradientStop>* pStop = static_cast<CComObject<CPDGradientStop>*>((IPDGradientStop*)(m_stops->m_items[i]));
		CComObject<CPDGradientStop>* pStop2 = static_cast<CComObject<CPDGradientStop>*>((IPDGradientStop*)(pGradient->m_stops->m_items[i]));

		if (pStop->m_offset != pStop2->m_offset)
			return S_OK;

		if (i < m_stops->m_items.GetSize()-1)
		{
			if (pStop->m_middle != pStop2->m_middle) return S_OK;
		}

		if ((pStop->m_color == NULL) != (pStop2->m_color == NULL))
			return S_OK;

		if ((pStop->m_swatch == NULL) != (pStop2->m_swatch == NULL))
			return S_OK;

		if (pStop->m_color)
		{
			if (pStop->m_color->m_colorMode != pStop2->m_color->m_colorMode)
				return S_OK;

			if (pStop->m_color->m_colorMode == COLORMODE_RGB)
			{
				if (pStop->m_color->m_channel[0] != pStop2->m_color->m_channel[0]) return S_OK;
				if (pStop->m_color->m_channel[1] != pStop2->m_color->m_channel[1]) return S_OK;
				if (pStop->m_color->m_channel[2] != pStop2->m_color->m_channel[2]) return S_OK;
			}
			else if (pStop->m_color->m_colorMode == COLORMODE_CMYK)
			{
				if (pStop->m_color->m_channel[0] != pStop2->m_color->m_channel[0]) return S_OK;
				if (pStop->m_color->m_channel[1] != pStop2->m_color->m_channel[1]) return S_OK;
				if (pStop->m_color->m_channel[2] != pStop2->m_color->m_channel[2]) return S_OK;
				if (pStop->m_color->m_channel[3] != pStop2->m_color->m_channel[3]) return S_OK;
			}
		}
		else if (pStop->m_swatch)
		{
			if (!IsUnknownEqualUnknown(pStop->m_swatch, pStop2->m_swatch))
				return S_OK;
		}
	}

	*pVal = VARIANT_TRUE;

	return S_OK;
}

STDMETHODIMP CPDGradient::clone(IPDGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDGradient>* pGradient;
	CComObject<CPDGradient>::CreateInstance(&pGradient);
	if (pGradient)
	{
		copy(pGradient);

		*pVal = pGradient;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDGradient::copy(IPDGradient *gradient)
{
	CComObject<CPDGradient>* pGradient = static_cast<CComObject<CPDGradient>*>(gradient);

	{
		// Remove any previous stops
		for (int i = pGradient->m_stops->m_items.GetSize()-1; i >= 0; i--)
		{
			CComObject<CPDGradientStop>* pStop = static_cast<CComObject<CPDGradientStop>*>((IPDGradientStop*)(pGradient->m_stops->m_items[i]));

			pStop->Unadvise(pGradient);

			pGradient->m_stops->m_items[i]->Release();
			pGradient->m_stops->m_items.RemoveAt(i);
		}

		pGradient->m_firstChild = NULL;
		pGradient->m_lastChild = NULL;
	}

	pGradient->m_type = m_type;

	for (int i = 0; i < m_stops->m_items.GetSize(); i++)
	{
		CComObject<CPDGradientStop>* pStop = static_cast<CComObject<CPDGradientStop>*>((IPDGradientStop*)(m_stops->m_items[i]));

		CComObject<CPDGradientStop>* pStop2;
		CComObject<CPDGradientStop>::CreateInstance(&pStop2);

		pStop2->m_offset = pStop->m_offset;
		pStop2->m_middle = pStop->m_middle;

		if (pStop->m_color)
		{
			pStop->m_color->clone((IPDColor**)&pStop2->m_color);

			DWORD cookie;
			pStop2->m_color->Advise(pStop2, &cookie);
		}
		else
		{
			pStop2->m_swatch = pStop->m_swatch;	// Swatches are set by reference

			CComQIPtr<INotifySend> cp = pStop2->m_swatch;
			DWORD cookie;
			cp->Advise(pStop2, &cookie);
		}

		pGradient->append(pStop2);
	}

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDGradient::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"type", _variant_t((long)m_type));

	node->putObjectMap(L"stops", m_stops);

	return S_OK;
}

STDMETHODIMP CPDGradient::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"type", &v);
	m_type = (PDGradientType)(long)v;

	CComObject<CObjectMap>* pMap;

	CComObject<CObjectMap>::CreateInstance(&pMap);
	if (pMap)
	{
		if (SUCCEEDED(node->getObjectMap(L"stops", pMap, NULL)))
		{
			for (int i = 0; i < pMap->m_items.GetSize(); i++)
			{
				IPDGradientStop* stop = static_cast<IPDGradientStop*>(pMap->m_items[i]);
				append(stop);
			}
		}
		pMap->Release();
	}

	return S_OK;
}
