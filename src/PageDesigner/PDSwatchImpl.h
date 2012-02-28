#pragma once

//class CPDSwatches;
#include "PDSwatches.h"

template <class IBase> class ATL_NO_VTABLE CPDSwatch :
	public IBase
{
public:
	CPDSwatch()
	{
		m_parent = NULL;
		m_nextSibling = NULL;
		m_previousSibling = NULL;
	}

	_bstr_t m_name;

	CPDSwatches* m_parent;
	CPDSwatch<IPDSwatch>* m_nextSibling;
	CPDSwatch<IPDSwatch>* m_previousSibling;
//	IPDSwatch* m_nextSibling;
//	IPDSwatch* m_previousSibling;
};

template<class T, class IBase> class ATL_NO_VTABLE CPDSwatchImpl : 
	public CPDSwatch<IBase>,
	public CNotifySendImpl<T>
{
public:
	CPDSwatchImpl()
	{
		m_canDelete = VARIANT_TRUE;
		m_canEdit = VARIANT_TRUE;
	}

	VARIANT_BOOL m_canDelete;
	VARIANT_BOOL m_canEdit;

// IPDSwatch
public:
	STDMETHOD(get_parent)(/*[out, retval]*/ IPDSwatches* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_parent;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_name)(BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
//		*pVal = m_name.copy();
		*pVal = SysAllocString(m_name);
		return S_OK;
	}
	STDMETHOD(put_name)(BSTR newVal)
	{
		m_name = newVal;
		static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);

		return S_OK;
	}
	STDMETHOD(get_canEdit)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_canEdit;
		return S_OK;
	}
	STDMETHOD(get_canDelete)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_canDelete;
		return S_OK;
	}
// IObjectSerializable
	STDMETHODIMP Serialize(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->putAttribute(L"name", _variant_t(m_name));
		return S_OK;
	}

	STDMETHODIMP Deserialize(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		_variant_t v;

		node->getAttribute(L"name", &v);
		m_name = _bstr_t(v).copy();

		return S_OK;
	}
};
