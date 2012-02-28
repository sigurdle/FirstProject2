#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSpreadDocument.h"

#include "ObjectMap.h"
#include "PDDocument.h"
#include "PDSpreadDocument.h"
#include "PDPage.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDObjectLayerGroup.h"
#include "PDGuides.h"

/////////////////////////
// CPDSpreadDocument

HRESULT CPDSpreadDocument::FinalConstruct()
{
	CPDSpreadImpl<IPDSpreadDocument>::FinalConstruct();
	return S_OK;
}

void CPDSpreadDocument::FinalRelease()
{
	CPDSpreadImpl<IPDSpreadDocument>::FinalRelease();
}

STDMETHODIMP CPDSpreadDocument::get_keepSpreadTogether(VARIANT_BOOL *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_keepSpreadTogether;
	return S_OK;
}

STDMETHODIMP CPDSpreadDocument::put_keepSpreadTogether(VARIANT_BOOL newVal)
{
	m_keepSpreadTogether = newVal;
	return S_OK;
}

STDMETHODIMP CPDSpreadDocument::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDSpreadDocument;
	return S_OK;
}
