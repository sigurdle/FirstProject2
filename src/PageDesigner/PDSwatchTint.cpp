#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSwatchTint.h"
#include "PDColor.h"

#include "PDSwatches.h"

/////////////////////////
// CPDSwatchTint

STDMETHODIMP CPDSwatchTint::get_tint(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_tint;
	return S_OK;
}

STDMETHODIMP CPDSwatchTint::put_tint(double newVal)
{
	m_tint = newVal;
	return S_OK;
}

STDMETHODIMP CPDSwatchTint::get_swatchColor(IPDSwatchColor* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_swatchColor;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDSwatchTint::put_swatchColor(IPDSwatchColor* newVal)
{
	if (newVal == NULL) return E_POINTER;
	m_swatchColor = newVal;
	return S_OK;
}

STDMETHODIMP CPDSwatchTint::clone(IPDSwatch **pVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDSwatchTint::get_finalColor(IPDColor **pVal)
{
	if (pVal == NULL) return E_POINTER;

	CComObject<CPDColor>* color;
	CComObject<CPDColor>::CreateInstance(&color);

	CComObject<CPDColor>* scolor;
	m_swatchColor->get_color((IPDColor**)&scolor);

	color->m_colorMode = scolor->m_colorMode;
	color->m_channel[0] = 255-((255-scolor->m_channel[0])*m_tint);
	color->m_channel[1] = 255-((255-scolor->m_channel[1])*m_tint);
	color->m_channel[2] = 255-((255-scolor->m_channel[2])*m_tint);
	color->m_channel[3] = 255-((255-scolor->m_channel[3])*m_tint);

	scolor->Release();

	*pVal = color;
	(*pVal)->AddRef();

	return S_OK;
}
