// PDSwatchPattern.cpp : Implementation of CPDSwatchPattern
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDSwatchPattern.h"

#include "PDSwatches.h"

/////////////////////////////////////////////////////////////////////////////
// CPDSwatchPattern

STDMETHODIMP CPDSwatchPattern::clone(/*[out,retval]*/ IPDSwatch* *pVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDSwatchPattern::get_objectGroup(IPDObjectGroup **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_objectGroup;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDSwatchPattern::put_objectGroup(IPDObjectGroup *newVal)
{
	m_objectGroup = newVal;
	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDSwatchPattern::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	CPDSwatchImpl<CPDSwatchPattern, IPDSwatchPattern>::Serialize(ar, node);
	node->putElement(L"objectGroup", m_objectGroup);

	return S_OK;
}

STDMETHODIMP CPDSwatchPattern::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CPDSwatchImpl<CPDSwatchPattern, IPDSwatchPattern>::Deserialize(ar, node, NULL);

	ATLASSERT(m_objectGroup == NULL);
	node->getElement(L"objectGroup", NULL, (IUnknown**)&m_objectGroup);

	return S_OK;
}
