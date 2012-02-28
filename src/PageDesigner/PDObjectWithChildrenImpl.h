#pragma once

template <class T> class CPDObjectWithChildrenImpl : public IPDObjectWithChildren
{
public:
	STDMETHOD(get_children)(/*[out, retval]*/ IObjectMap* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = static_cast<T*>(this)->m_children;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_firstChild)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = static_cast<T*>(this)->m_firstChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_lastChild)(/*[out, retval]*/ IPDObjectUnknown* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = static_cast<T*>(this)->m_lastChild;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
};
