#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSwatches.h"
#include "PDColor.h"
#include "PDSwatchColor.h"

/////////////////////////
// CPDSwatchColor

int CPDSwatchColor::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CPDColor>::CreateInstance(&m_color);
	if (FAILED(hr)) return hr;
	m_color->AddRef();

	DWORD cookie;
	m_color->Advise(this, &cookie);

	return S_OK;
}

void CPDSwatchColor::FinalRelease()
{
	if (m_color)
	{
		m_color->Unadvise(this);

		m_color->Release();
		m_color = NULL;
	}
}

STDMETHODIMP CPDSwatchColor::get_color(IPDColor* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_color;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDSwatchColor::get_name(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;

	ATLASSERT(m_color);

	if (m_nameWithColorValue)
	{
		WCHAR str[256];

		if (m_color->m_colorMode == COLORMODE_RGB)
		{
			swprintf(str, L"R=%d G=%d B=%d", (int)m_color->m_channel[0], (int)m_color->m_channel[1], (int)m_color->m_channel[2]);
		}
		else if (m_color->m_colorMode == COLORMODE_CMYK)
		{
			swprintf(str, L"C=%d M=%d Y=%d K=%d", (int)m_color->m_channel[0], (int)m_color->m_channel[1], (int)m_color->m_channel[2], (int)m_color->m_channel[3]);
		}
		else if (m_color->m_colorMode == COLORMODE_LAB)
		{
			swprintf(str, L"L=%d A=%d B=%d", (int)m_color->m_channel[0], (int)m_color->m_channel[1], (int)m_color->m_channel[2]);
		}
		else
			ATLASSERT(0);

		*pVal = SysAllocString(str);
	}
	else
	{
		*pVal = m_name.copy();
	}

	return S_OK;
}

/*
STDMETHODIMP CPDSwatchColor::put_name(BSTR newVal)
{
//	m_nameWithColorValue = VARIANT_FALSE;
	m_name = newVal;
	return S_OK;
}
*/

STDMETHODIMP CPDSwatchColor::clone(IPDSwatch **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDSwatchColor>* pSwatch;
	CComObject<CPDSwatchColor>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		pSwatch->m_canEdit = m_canEdit;
		pSwatch->m_canDelete = m_canDelete;
		pSwatch->m_name = m_name;
		m_color->copy(pSwatch->m_color);

		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDSwatchColor::get_nameWithColorValue(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_nameWithColorValue;
	return S_OK;
}

STDMETHODIMP CPDSwatchColor::put_nameWithColorValue(VARIANT_BOOL newVal)
{
	m_nameWithColorValue = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDSwatchColor::get_colorType(PDColorType *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_colorType;
	return S_OK;
}

STDMETHODIMP CPDSwatchColor::put_colorType(PDColorType newVal)
{
	m_colorType = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDSwatchColor::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"colorType", _variant_t((long)m_colorType));
	node->putAttribute(L"nameWithColorValue", _variant_t(m_nameWithColorValue));

	node->serializeElement(L"color", (IPDColor*)m_color);

	return S_OK;
}

STDMETHODIMP CPDSwatchColor::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"colorType", &v);
	m_colorType = (PDColorType)(long)v;

	node->getAttribute(L"nameWithColorValue", &v);
	m_nameWithColorValue = v;

	node->deserializeElement(L"color", (IPDColor*)m_color, NULL);

	return S_OK;
}

STDMETHODIMP CPDSwatchColor::GetClassID(/*[out,retval]*/ CLSID* pClassID)
{
	*pClassID = CLSID_PDSwatchColor;
	return S_OK;
}

