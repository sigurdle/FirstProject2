// PDObjectSymbolInstanceSet.cpp : Implementation of CPDObjectSymbolInstanceSet
#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDObjectSymbolInstanceSet.h"

/////////////////////////////////////////////////////////////////////////////
// CPDObjectSymbolInstanceSet

int CPDObjectSymbolInstanceSet::FinalConstruct()
{
	HRESULT hr;

	hr = CPDObjectImpl<IPDObjectSymbolInstanceSet>::FinalConstruct();
	if (FAILED(hr)) return hr;

	return 0;
}

void CPDObjectSymbolInstanceSet::FinalRelease()
{
	CPDObjectImpl<IPDObjectSymbolInstanceSet>::FinalRelease();
}

//virtual
void CPDObjectSymbolInstanceSet::CalculateBounds()
{
}

//virtual
void CPDObjectSymbolInstanceSet::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* graphics, double scaleX, double scaleY)
{
}

// IObjectSerializable
STDMETHODIMP CPDObjectSymbolInstanceSet::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstanceSet::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstanceSet::get_document(IPDDocument **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstanceSet::put_document(IPDDocument *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDObjectSymbolInstanceSet::getExpandedBBox(RectD *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
