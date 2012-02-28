#pragma once

#include "PDPath.h"
//#include "PDMatrix.h"

template <class T> class ATL_NO_VTABLE CPDObjectWrappableImpl :
	public IPDObjectWrappable
{
public:
	CPDObjectWrappableImpl()
	{
		m_textWrap = TEXTWRAP_NONE;
		m_editedWrapPath = FALSE;

		m_wrapPath = NULL;

		m_topOffset = 10;
		m_leftOffset = 10;
		m_bottomOffset = 10;
		m_rightOffset = 10;
	}

	int FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	PDTextWrap m_textWrap;
//	CComPtr<IPDPath> m_wrapPath;
	CComObject<CPDPath>* m_wrapPath;
	BOOL m_editedWrapPath;

	double m_topOffset;
	double m_leftOffset;
	double m_bottomOffset;
	double m_rightOffset;

	void RecreateWrapPath()
	{
		ATLASSERT(0);	// ??
	}

public:
	STDMETHOD(get_textWrap)(/*[out, retval]*/ PDTextWrap *pVal)
	{
		if (pVal == NULL) return NULL;
		*pVal = m_textWrap;
		return S_OK;
	}
	STDMETHOD(get_wrapPath)(/*[out, retval]*/ IPDPath* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_wrapPath;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(put_wrapPath)(/*[in]*/ IPDPath* newVal)
	{
		ATLASSERT(0);
		return S_OK;
	}

	STDMETHODIMP get_editedWrapPath(BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_editedWrapPath;
		return S_OK;
	}

	STDMETHODIMP put_editedWrapPath(BOOL newVal)
	{
		m_editedWrapPath = newVal;
		return S_OK;
	}

	STDMETHODIMP get_topOffset(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_topOffset;
		return S_OK;
	}

	STDMETHODIMP put_topOffset(double newVal)
	{
		m_topOffset = newVal;
		static_cast<T*>(this)->RecreateWrapPath();
		return S_OK;
	}

	STDMETHODIMP get_leftOffset(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_leftOffset;
		return S_OK;
	}

	STDMETHODIMP put_leftOffset(double newVal)
	{
		m_leftOffset = newVal;
		static_cast<T*>(this)->RecreateWrapPath();
		return S_OK;
	}

	STDMETHODIMP get_bottomOffset(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_bottomOffset;
		return S_OK;
	}

	STDMETHODIMP put_bottomOffset(double newVal)
	{
		m_bottomOffset = newVal;
		static_cast<T*>(this)->RecreateWrapPath();
		return S_OK;
	}

	STDMETHODIMP get_rightOffset(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rightOffset;
		return S_OK;
	}

	STDMETHODIMP put_rightOffset(double newVal)
	{
		m_rightOffset = newVal;
		static_cast<T*>(this)->RecreateWrapPath();
		return S_OK;
	}

// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node)
	{
		node->putAttribute(L"wrap-text", _variant_t((long)m_textWrap));
		node->putAttribute(L"wrap-topOffset", _variant_t(m_topOffset));
		node->putAttribute(L"wrap-leftOffset", _variant_t(m_leftOffset));
		node->putAttribute(L"wrap-bottomOffset", _variant_t(m_bottomOffset));
		node->putAttribute(L"wrap-rightOffset", _variant_t(m_rightOffset));

		if (m_editedWrapPath)
		{
			ATLASSERT(m_wrapPath != NULL);
			node->putAttribute(L"wrap-path", _variant_t((IPDPath*)m_wrapPath));
		}

		return S_OK;
	}

	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra)
	{
		_variant_t v;

		node->getAttribute(L"wrap-text", &v);
		m_textWrap = (PDTextWrap)(long)v;

		node->getAttribute(L"wrap-topOffset", &v);
		m_topOffset = v;

		node->getAttribute(L"wrap-leftOffset", &v);
		m_leftOffset = v;

		node->getAttribute(L"wrap-bottomOffset", &v);
		m_bottomOffset = v;

		node->getAttribute(L"wrap-rightOffset", &v);
		m_rightOffset = v;

		ATLASSERT(m_wrapPath == NULL);

		if (m_textWrap == TEXTWRAP_SHAPE || m_textWrap == TEXTWRAP_BBOX)
		{
			CComObject<CPDPath>::CreateInstance(&m_wrapPath);
			if (m_wrapPath)
			{
				m_wrapPath->AddRef();

				CComPtr<IArchiveElement> pathNode;
				node->getAttributeNode(L"wrapPath-path", &pathNode);
				if (pathNode)
				{
					m_wrapPath->Deserialize(ar, pathNode, NULL);

					m_editedWrapPath = VARIANT_TRUE;
				}
				else
				{
					static_cast<T*>(this)->RecreateWrapPath();

					m_editedWrapPath = VARIANT_FALSE;
				}

				CComQIPtr<INotifySend> cp = m_wrapPath;
				DWORD cookie;
				cp->Advise(static_cast<T*>(this), &cookie);
			}
			else
				return E_OUTOFMEMORY;
		}

		return S_OK;
	}
};
