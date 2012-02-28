#pragma once

#include "PDObjectImpl.h"
#include "PDObjectWithAppearanceImpl.h"
#include "PDBrush.h"

class CPDObjectFrame;

template <class T, class IBase> class ATL_NO_VTABLE CPDObjectWithBrushImpl : 
	public CPDObjectImpl<IBase>,
	public CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearance>
//	public CPDObjectWithBrush
{
public:
	CPDObjectWithBrushImpl()
	{
		m_brush = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectImpl<IBase>::FinalConstruct();
		if (FAILED(hr)) return hr;

		hr = CComObject<CPDBrush>::CreateInstance(&m_brush);
		if (FAILED(hr)) return hr;
		m_brush->AddRef();
		DWORD cookie;
		m_brush->Advise(static_cast<T*>(this), &cookie);

		return 0;
	}

	void FinalRelease()
	{
		if (m_brush)
		{
			m_brush->Unadvise(static_cast<T*>(this));
			m_brush->Release();
			m_brush = NULL;
		}

		CPDObjectImpl<IBase>::FinalRelease();
	}

	CComObject<CPDBrush>* m_brush;

	STDMETHOD(get_brush)(/*[out, retval]*/ IPDBrush* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_brush;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}

	STDMETHOD(put_brush)(/*[in]*/ IPDBrush* newVal)
	{
		CComPtr<IPDBrush> brush = m_brush;
		if (m_brush)
		{
			m_brush->Unadvise(static_cast<T*>(this));
		}

		m_brush = static_cast<CComObject<CPDBrush>*>(newVal);
		if (m_brush)
		{
			m_brush->AddRef();

			DWORD cookie;
			m_brush->Advise(static_cast<T*>(this), &cookie);
		}

		return S_OK;
	}

	STDMETHODIMP Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->serializeElement(L"brush", static_cast<IUnknown*>((IPDBrush*)m_brush));
		CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearance>::Serialize(ar, node);
		return S_OK;
	}

	STDMETHODIMP Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		node->deserializeElement(L"brush", static_cast<IUnknown*>((IPDBrush*)m_brush), NULL);
		CPDObjectWithAppearanceImpl<T, IPDObjectWithAppearance>::Deserialize(ar, node, pUnkExtra);
		return S_OK;
	}
};
