#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDSwatchNone.h"

#include "PDSwatches.h"

/////////////////////////
// CPDSwatchNone

STDMETHODIMP CPDSwatchNone::clone(IPDSwatch **pVal)
{
	CComObject<CPDSwatchNone>* pSwatch;
	CComObject<CPDSwatchNone>::CreateInstance(&pSwatch);
	if (pSwatch)
	{
		pSwatch->m_canEdit = m_canEdit;
		pSwatch->m_canDelete = m_canDelete;
		pSwatch->m_name = m_name;

		*pVal = pSwatch;
		(*pVal)->AddRef();
	}
	else
		*pVal = NULL;

	return S_OK;
}
