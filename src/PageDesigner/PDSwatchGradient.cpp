#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "PDSwatchGradient.h"
#include "PDGradient.h"
#include "PDSwatches.h"


/////////////////////////
// CPDSwatchGradient

int CPDSwatchGradient::FinalConstruct()
{
	HRESULT hr;

	hr = CComObject<CPDGradient>::CreateInstance(&m_gradient);
	if (FAILED(hr)) return hr;
	m_gradient->AddRef();
	return S_OK;
}

void CPDSwatchGradient::FinalRelease()
{
	if (m_gradient)
	{
		m_gradient->Release();
		m_gradient = NULL;
	}
}

STDMETHODIMP CPDSwatchGradient::get_gradient(IPDGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_gradient;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CPDSwatchGradient::put_gradient(IPDGradient *newVal)
{
	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDSwatchGradient::clone(IPDSwatch **pVal)
{
	ATLASSERT(0);
	// TODO: Add your implementation code here

	return S_OK;
}

// IObjectSerializable
STDMETHODIMP CPDSwatchGradient::Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
{
	CPDSwatchImpl<CPDSwatchGradient, IPDSwatchGradient>::Serialize(ar, node);
	node->serializeElement(L"gradient", (IPDGradient*)m_gradient);
	return S_OK;
}

STDMETHODIMP CPDSwatchGradient::Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
{
	CPDSwatchImpl<CPDSwatchGradient, IPDSwatchGradient>::Deserialize(ar, node, NULL);
	node->deserializeElement(L"gradient", (IPDGradient*)m_gradient, NULL);
	return S_OK;
}

STDMETHODIMP CPDSwatchGradient::GetClassID(/*[out,retval]*/ CLSID* pClassID)
{
	*pClassID = CLSID_PDSwatchGradient;
	return S_OK;
}
