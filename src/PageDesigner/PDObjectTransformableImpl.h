#pragma once

#include "PDMatrix.h"
#include "PDDocument.h"
#include "PDObjectLocatableImpl.h"

template <class T> class ATL_NO_VTABLE CPDObjectTransformableImpl :
	public CPDObjectLocatableImpl<T, IPDObjectTransformable>
{
public:
	CPDObjectTransformableImpl()
	{
		m_bounds.X = 0;
		m_bounds.Y = 0;
		m_bounds.Width = 0;
		m_bounds.Height = 0;

		m_xbounds.X = 0;
		m_xbounds.Y = 0;
		m_xbounds.Width = 0;
		m_xbounds.Height = 0;
	}

	int FinalConstruct()
	{
//		HRESULT hr;

		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(get_transformMatrix)(/*[out, retval]*/ IPDMatrix* *pVal)
	{
		*pVal = static_cast<T*>(this)->m_matrix;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_transformMatrix)(/*[in]*/ IPDMatrix *newVal)
	{
		CComQIPtr<IPDMatrix> matrix = static_cast<T*>(this)->m_matrix;

		static_cast<T*>(this)->m_matrix = static_cast<CComObject<CPDMatrix>*>(newVal);
		static_cast<T*>(this)->m_matrix->AddRef();

		static_cast<T*>(this)->TransformMatrixChanged();
		//static_cast<T*>(this)->CalculateBounds();	// ???
		//static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, NULL/*static_cast<T*>(this)->GetUnknown()*/, /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);

		return S_OK;
	}
	// IObjectSerializable
	STDMETHODIMP Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->putAttribute(L"matrix", _variant_t(static_cast<IUnknown*>((IPDMatrix*)static_cast<T*>(this)->m_matrix)));

		return S_OK;
	}
	STDMETHODIMP Deserialize(IArchive *ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		CComPtr<IArchiveElement> mNode;
		node->getAttributeNode(L"matrix", &mNode);
		if (mNode) static_cast<T*>(this)->m_matrix->Deserialize(ar, mNode, NULL);

		return S_OK;
	}
};
