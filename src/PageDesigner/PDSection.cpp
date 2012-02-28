#include "stdafx.h"
#include "PageDesigner.h"

#include "PDSection.h"

/////////////////////////
// CPDSection

int CPDSection::FinalConstruct()
{
	return S_OK;
}

void CPDSection::FinalRelease()
{
}

STDMETHODIMP CPDSection::get_pageNumbering(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageNumbering;
	return S_OK;
}

STDMETHODIMP CPDSection::put_pageNumbering(long newVal)
{
	m_pageNumbering = newVal;
	// TODO update
	return S_OK;
}

STDMETHODIMP CPDSection::get_pageNumberingStartAt(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageNumberingStartAt;
	return S_OK;
}

STDMETHODIMP CPDSection::put_pageNumberingStartAt(long newVal)
{
	m_pageNumberingStartAt = newVal;
	// TODO update
	return S_OK;
}

STDMETHODIMP CPDSection::get_style(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	return S_OK;
}

STDMETHODIMP CPDSection::put_style(long newVal)
{
	m_style = newVal;
	return S_OK;
}
