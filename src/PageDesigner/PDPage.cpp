#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDPage.h"

#include "PDDocument.h"
//#include "PDSpread.h"
#include "PDSpreadMaster.h"
#include "ObjectMap.h"
#include "PDObjectGroup.h"
#include "PDObjectLayerGroup.h"
#include "PDLayer.h"
#include "PDGuides.h"
#include "PDSection.h"

bool CPDPage::IsLeftOfSpine()
{
	for (int pageIndex = 0; pageIndex < m_ownerSpread->m_pages->m_items.GetSize(); pageIndex++)
	{
		if (IsUnknownEqualUnknown(m_ownerSpread->m_pages->m_items[pageIndex], GetUnknown()))
		{
			break;
		}
	}

	ATLASSERT(pageIndex < m_ownerSpread->m_pages->m_items.GetSize());

	return pageIndex < m_ownerSpread->m_spine;
}

CPDPage* CPDPage::GetBasePage()
{
	ATLASSERT(m_baseMaster);

	for (int pageIndex = 0; pageIndex < m_ownerSpread->m_pages->m_items.GetSize(); pageIndex++)
	{
		if (IsUnknownEqualUnknown(m_ownerSpread->m_pages->m_items[pageIndex], GetUnknown()))
		{
			break;
		}
	}

	ATLASSERT(pageIndex < m_ownerSpread->m_pages->m_items.GetSize());

//	m_ownerSpread->m_spine;
//	m_baseMaster->m_pages->m_items.GetSize();

	int basepageIndex = m_baseMaster->m_pages->m_items.GetSize()-1 - (m_ownerSpread->m_spine - pageIndex);

	ATLASSERT(basepageIndex >= 0);
	ATLASSERT(basepageIndex < m_baseMaster->m_pages->m_items.GetSize());

	return static_cast<CPDPage*>((IPDPage*)(m_baseMaster->m_pages->m_items[basepageIndex]));
}

/////////////////////////
// CPDPage

STDMETHODIMP CPDPage::getPageRect(RectD *pVal)
{
	double x = 0;

	for (int i = 0; i < m_ownerSpread->m_pages->m_items.GetSize(); i++)
	{
		if (IsUnknownEqualUnknown(m_ownerSpread->m_pages->m_items[i], GetUnknown()))
		{
			break;
		}

		x += m_pDocument->m_pageWidth;
	}

	pVal->X = x;
	pVal->Y = 0;
	pVal->Width = m_pDocument->m_pageWidth;
	pVal->Height = m_pDocument->m_pageHeight;

	return S_OK;
}

STDMETHODIMP CPDPage::get_marginTop(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_marginTop;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_marginTop(pVal);
	}
}

STDMETHODIMP CPDPage::get_marginBottom(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_marginBottom;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_marginBottom(pVal);
	}
}

double CPDPage::GetMarginInside()
{
	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		return m_marginInside;
	}
	else
	{
		return GetBasePage()->GetMarginInside();
	}
}

double CPDPage::GetMarginOutside()
{
	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		return m_marginOutside;
	}
	else
	{
		return GetBasePage()->GetMarginOutside();
	}
}

STDMETHODIMP CPDPage::get_marginLeft(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (IsLeftOfSpine())
		*pVal = GetMarginOutside();
	else
		*pVal = GetMarginInside();

	return S_OK;
}

STDMETHODIMP CPDPage::get_marginRight(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (IsLeftOfSpine())
		*pVal = GetMarginInside();
	else
		*pVal = GetMarginOutside();

	return S_OK;
}

STDMETHODIMP CPDPage::get_marginInside(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_marginInside;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_marginInside(pVal);
	}
}

STDMETHODIMP CPDPage::get_marginOutside(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_marginOutside;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_marginOutside(pVal);
	}
}

STDMETHODIMP CPDPage::get_columnNumber(long *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_columnNumber;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_columnNumber(pVal);
	}
}

STDMETHODIMP CPDPage::put_columnNumber(long newVal)
{
	ATLASSERT(0);
	m_columnNumber = newVal;
	return S_OK;
}

STDMETHODIMP CPDPage::get_columnGutter(double *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_marginsAndColumnsOverriden || m_baseMaster == NULL)
	{
		*pVal = m_columnGutter;
		return S_OK;
	}
	else
	{
		return GetBasePage()->get_columnGutter(pVal);
	}
}

STDMETHODIMP CPDPage::put_columnGutter(double newVal)
{
	ATLASSERT(0);
	m_columnGutter = newVal;
	return S_OK;
}

STDMETHODIMP CPDPage::setMarginsAndColumns(double marginTop, double marginBottom, double marginInside, double marginOutside, long columnNumber, double columnGutter)
{
	m_marginsAndColumnsOverriden = TRUE;

	m_marginTop = marginTop;
	m_marginBottom = marginBottom;
	m_marginInside = marginInside;
	m_marginOutside = marginOutside;

	m_columnNumber = columnNumber;
	m_columnGutter = columnGutter;

	return S_OK;
}

STDMETHODIMP CPDPage::get_ownerSpread(IPDSpread **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_ownerSpread;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDPage::get_baseMaster(IPDSpreadMaster **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_baseMaster;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDPage::put_baseMaster(IPDSpreadMaster *newVal)
{
	m_baseMaster = (CPDSpreadMaster*)newVal;
	// TODO, fire some event (?)
	return S_OK;
}

STDMETHODIMP CPDPage::get_section(IPDSection **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_section;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDPage::put_section(IPDSection *newVal)
{
	CComPtr<IPDSection> section = m_section;	// For AddRef/Release
	m_section = static_cast<CComObject<CPDSection>*>(newVal);
	if (m_section) m_section->AddRef();

	return S_OK;
}

STDMETHODIMP CPDPage::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	node->putAttribute(L"marginsAndColumnsOverriden", _variant_t((long)m_marginsAndColumnsOverriden));
	node->putAttribute(L"marginTop", _variant_t(m_marginTop));
	node->putAttribute(L"marginBottom", _variant_t(m_marginBottom));
	node->putAttribute(L"marginInside", _variant_t(m_marginInside));
	node->putAttribute(L"marginOutside", _variant_t(m_marginOutside));
	node->putAttribute(L"columnNumber", _variant_t(m_columnNumber));
	node->putAttribute(L"columnGutter", _variant_t(m_columnGutter));

	return S_OK;
}

STDMETHODIMP CPDPage::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
//	CComQIPtr<IPDDocument> document = pUnkExtra;
//	m_pDocument = static_cast<CPDDocument*>((IPDDocument*)document.p);

	CComQIPtr<IPDSpread> spread = pUnkExtra;
	m_ownerSpread = static_cast<CPDSpreadImpl<IPDSpread>*>((IPDSpread*)spread.p);
	m_pDocument = m_ownerSpread->m_pDocument;

	_variant_t v;

	node->getAttribute(L"marginsAndColumnsOverriden", &v);
	m_marginsAndColumnsOverriden = (long)v;

	node->getAttribute(L"marginTop", &v);
	m_marginTop = v;

	node->getAttribute(L"marginBottom", &v);
	m_marginBottom = v;

	node->getAttribute(L"marginInside", &v);
	m_marginInside = v;

	node->getAttribute(L"marginOutside", &v);
	m_marginOutside = v;

	node->getAttribute(L"columnNumber", &v);
	m_columnNumber = v;

	node->getAttribute(L"columnGutter", &v);
	m_columnGutter = v;

	return S_OK;
}

STDMETHODIMP CPDPage::GetClassID(CLSID *pClassID)
{
	*pClassID = CLSID_PDPage;
	return S_OK;
}
