#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDColor.h"

/////////////////////////
// CPDColor

STDMETHODIMP CPDColor::get_colorMode(PDColorMode *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_colorMode;
	return S_OK;
}

STDMETHODIMP CPDColor::put_colorMode(PDColorMode newVal)
{
	m_colorMode = newVal;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDColor::putChannel(long n, double value)
{
	m_channel[n] = value;
	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
	return S_OK;
}

STDMETHODIMP CPDColor::getChannel(long n, double* pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_channel[n];
	return S_OK;
}

STDMETHODIMP CPDColor::setRGB(long red, long green, long blue)
{
	m_colorMode = COLORMODE_RGB;

	m_channel[0] = red;
	m_channel[1] = green;
	m_channel[2] = blue;

	FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDColor::clone(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDColor>* pColor;
	CComObject<CPDColor>::CreateInstance(&pColor);
	if (pColor)
	{
		copy(pColor);

		*pVal = pColor;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}

STDMETHODIMP CPDColor::copy(IPDColor *color)
{
	if (color == NULL) return E_INVALIDARG;

	CPDColor* pColor = static_cast<CPDColor*>(color);

	pColor->m_colorMode = m_colorMode;

	pColor->m_channel[0] = m_channel[0];
	pColor->m_channel[1] = m_channel[1];
	pColor->m_channel[2] = m_channel[2];
	pColor->m_channel[3] = m_channel[3];

	pColor->FireOnChanged(NOTIFY_MODIFY, pColor->GetUnknown(), DISPID_UNKNOWN);

	return S_OK;
}

STDMETHODIMP CPDColor::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"mode", _variant_t((long)m_colorMode));
	node->putAttribute(L"ch0", _variant_t(m_channel[0]));
	node->putAttribute(L"ch1", _variant_t(m_channel[1]));
	node->putAttribute(L"ch2", _variant_t(m_channel[2]));
	node->putAttribute(L"ch3", _variant_t(m_channel[3]));
	return S_OK;
}

STDMETHODIMP CPDColor::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	_variant_t v;

	node->getAttribute(L"mode", &v);
	m_colorMode = (PDColorMode)(long)v;

	node->getAttribute(L"ch0", &v);
	m_channel[0] = v;

	node->getAttribute(L"ch1", &v);
	m_channel[1] = v;

	node->getAttribute(L"ch2", &v);
	m_channel[2] = v;

	node->getAttribute(L"ch3", &v);
	m_channel[3] = v;

	return S_OK;
}
