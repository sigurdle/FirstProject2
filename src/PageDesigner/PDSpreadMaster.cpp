#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSpreadMaster.h"

#include "ObjectMap.h"
#include "PDDocument.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDObjectLayerGroup.h"
#include "PDGuides.h"

/////////////////////////
// CPDSpreadMaster

HRESULT CPDSpreadMaster::FinalConstruct()
{
	CPDSpreadImpl<IPDSpreadMaster>::FinalConstruct();
	return S_OK;
}

void CPDSpreadMaster::FinalRelease()
{
	CPDSpreadImpl<IPDSpreadMaster>::FinalRelease();
}

STDMETHODIMP CPDSpreadMaster::get_prefix(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_prefix.copy();
	return S_OK;
}

STDMETHODIMP CPDSpreadMaster::put_prefix(BSTR newVal)
{
	m_prefix = newVal;
	return S_OK;
}

STDMETHODIMP CPDSpreadMaster::get_name(BSTR *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_name.copy();
	return S_OK;
}

STDMETHODIMP CPDSpreadMaster::put_name(BSTR newVal)
{
	m_name = newVal;
	return S_OK;
}
