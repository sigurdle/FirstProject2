#pragma once

//class CPDDocument;
//class CPDLayer;
#include "PDDocument.h"
#include "PDLayer.h"

template <class IBase> class ATL_NO_VTABLE CPDObjectUnknownImpl :
	public IBase
{
public:
	CPDObjectUnknownImpl()
	{
		m_uniqId = GUID_NULL;

		m_pDocument = NULL;
		m_layer = NULL;
		m_spread = NULL;

		m_parent = NULL;
		m_nextSibling = NULL;
		m_previousSibling = NULL;
		m_firstChild = NULL;
		m_lastChild = NULL;

	}

	int FinalConstruct()
	{
		HRESULT hr;

		return S_OK;
	}

	void FinalRelease()
	{
	}

	GUID m_uniqId;
	CPDLayer* m_layer;
	CPDDocument* m_pDocument;

	IPDSpread* m_spread;

	CPDObjectUnknownImpl<IPDObjectUnknown>* m_parent;
	IPDObjectUnknown* m_previousSibling;
	IPDObjectUnknown* m_nextSibling;

	IPDObjectUnknown* m_firstChild;
	IPDObjectUnknown* m_lastChild;

	IPDObjectUnknown* getObjectByUniqId(IPDObjectUnknown* object, GUID guid)
	{
		GUID uniqId;
		object->get_uniqId(&uniqId);

		if (uniqId == guid)
			return object;

		CComQIPtr<IPDObjectWithChildren> objectWithChildren = object;
		if (objectWithChildren)
		{
			CComPtr<IObjectMap> children;
			objectWithChildren->get_children(&children);

			long nchildren;
			children->get_length(&nchildren);

			for (int i = 0; i < nchildren; i++)
			{
				CComPtr<IPDObjectUnknown> object2;
				children->item(i, (IUnknown**)&object2);

				IPDObjectUnknown* f = getObjectByUniqId(object2, guid);
				if (f)
					return f;
			}
		}

		return NULL;
	}

	virtual IPDObjectUnknown* getObjectByUniqId(GUID guid)
	{
		return getObjectByUniqId(this, guid);
	}

public:
	STDMETHOD(get_uniqId)(/*[out, retval]*/ GUID *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_uniqId;
		return S_OK;
	}
	STDMETHOD(get_document)(/*[out, retval]*/ IPDDocument* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pDocument;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_document)(/*[in]*/ IPDDocument* newVal)
	{
		m_pDocument = static_cast<CPDDocument*>(newVal);
		return S_OK;
	}
	STDMETHOD(get_layer)(/*[out, retval]*/ IPDLayer* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_layer;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_parent)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_parent;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_parent)(/*[in]*/ IPDObjectUnknown* newVal)
	{
		m_parent = static_cast<CPDObjectUnknownImpl<IPDObjectUnknown>*>(newVal);
		return S_OK;
	}
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = *pVal = m_nextSibling;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_nextSibling)(/*[out, retval]*/ IPDObjectUnknown* newVal)
	{
		m_nextSibling = newVal;
		return S_OK;
	}
	STDMETHOD(get_previousSibling)(/*[in]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = *pVal = m_previousSibling;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_previousSibling)(/*[in]*/ IPDObjectUnknown* newVal)
	{
		m_previousSibling = newVal;
		return S_OK;
	}
	STDMETHOD(get_spread)(/*[in]*/ IPDSpread* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spread;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_spread)(/*[in]*/ IPDSpread* newVal)
	{
		m_spread = newVal;
		return S_OK;
	}
	STDMETHOD(removeObject)(/*[in]*/ IPDObjectUnknown* object)
	{
		return E_FAIL;
	}
};
