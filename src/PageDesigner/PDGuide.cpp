#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "ObjectMap.h"
#include "PDGuides.h"
#include "PDGuide.h"
#include "PDLayer.h"

/////////////////////////
// CPDGuide

STDMETHODIMP CPDGuide::get_pageIndex(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pageIndex;
	return S_OK;
}

STDMETHODIMP CPDGuide::put_pageIndex(long newVal)
{
	m_pageIndex = newVal;
	return S_OK;
}

STDMETHODIMP CPDGuide::get_position(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_position;
	return S_OK;
}

STDMETHODIMP CPDGuide::put_position(double newVal)
{
	m_position = newVal;
	return S_OK;
}

STDMETHODIMP CPDGuide::get_direction(long *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_direction;
	return S_OK;
}

STDMETHODIMP CPDGuide::put_direction(long newVal)
{
	m_direction = newVal;
	return S_OK;
}

STDMETHODIMP CPDGuide::get_ownerSpread(IPDSpread **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDGuide::offsetPosition(double delta)
{
	m_position += delta;
	return S_OK;
}
