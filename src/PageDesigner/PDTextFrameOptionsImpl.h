#pragma once

template <class T> class ATL_NO_VTABLE CPDTextFrameOptionsImpl : 
	public IPDTextFrameOptions
{
public:
	CPDTextFrameOptionsImpl()
	{
		m_columnsNumber = 1;
		m_columnsGutter = 10;
		m_columnsWidth = 0;
		m_columnsFixedWidth = VARIANT_FALSE;

		m_insetTop = 6;
		m_insetBottom = 6;
		m_insetLeft = 6;
		m_insetRight = 6;

		m_ignoreTextWrap = VARIANT_FALSE;
	}

	long m_columnsNumber;
	double m_columnsGutter;
	double m_columnsWidth;
	VARIANT_BOOL m_columnsFixedWidth;

	double m_insetTop;
	double m_insetBottom;
	double m_insetLeft;
	double m_insetRight;

	VARIANT_BOOL m_ignoreTextWrap;

// IPDTextFrameOptions
public:
	STDMETHOD(copyFrom)(/*[in]*/ IPDTextFrameOptions* other)
	{
		if (other == NULL) return E_INVALIDARG;

		other->get_columnsNumber(&m_columnsNumber);
		other->get_columnsGutter(&m_columnsGutter);
		other->get_columnsWidth(&m_columnsWidth);
		other->get_columnsFixedWidth(&m_columnsFixedWidth);
		other->get_insetTop(&m_insetTop);
		other->get_insetBottom(&m_insetBottom);
		other->get_insetLeft(&m_insetLeft);
		other->get_insetRight(&m_insetRight);
		other->get_ignoreTextWrap(&m_ignoreTextWrap);

		return S_OK;
	}
	STDMETHOD(get_columnsNumber)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_columnsNumber;
		return S_OK;
	}
#if 0
	STDMETHOD(put_columnsNumber)(/*[in]*/ long newVal)
	{
		if (m_columnsNumber != newVal)
		{
			m_columnsNumber = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}

		return S_OK;
	}
#endif
	STDMETHOD(get_columnsGutter)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_columnsGutter;
		return S_OK;
	}
#if 0
	STDMETHOD(put_columnsGutter)(/*[in]*/ double newVal)
	{
		if (m_columnsGutter != newVal)
		{
			m_columnsGutter = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
#endif
	STDMETHOD(get_insetRight)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_insetRight;
		return S_OK;
	}
	STDMETHOD(put_insetRight)(/*[in]*/ double newVal)
	{
		if (m_insetRight != newVal)
		{
			m_insetRight = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
	STDMETHOD(get_insetLeft)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_insetLeft;
		return S_OK;
	}
	STDMETHOD(put_insetLeft)(/*[in]*/ double newVal)
	{
		if (m_insetLeft != newVal)
		{
			m_insetLeft = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
	STDMETHOD(get_insetBottom)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_insetBottom;
		return S_OK;
	}
	STDMETHOD(put_insetBottom)(/*[in]*/ double newVal)
	{
		if (m_insetBottom != newVal)
		{
			m_insetBottom = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
	STDMETHOD(get_insetTop)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_insetTop;
		return S_OK;
	}
	STDMETHOD(put_insetTop)(/*[in]*/ double newVal)
	{
		if (m_insetTop != newVal)
		{
			m_insetTop = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
	STDMETHOD(get_ignoreTextWrap)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_ignoreTextWrap;
		return S_OK;
	}
	STDMETHOD(put_ignoreTextWrap)(/*[in]*/ VARIANT_BOOL newVal)
	{
		if (m_ignoreTextWrap != newVal)
		{
			m_ignoreTextWrap = (newVal)? VARIANT_TRUE: VARIANT_FALSE;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}

		return S_OK;
	}
	STDMETHOD(get_columnsFixedWidth)(/*[out, retval]*/ VARIANT_BOOL *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_columnsFixedWidth;
		return S_OK;
	}
#if 0
	STDMETHOD(put_columnsFixedWidth)(/*[in]*/ VARIANT_BOOL newVal)
	{
		if (m_columnsFixedWidth != newVal)
		{
			m_columnsFixedWidth = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
#endif
	STDMETHOD(get_columnsWidth)(/*[out, retval]*/ double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_columnsWidth;
		return S_OK;
	}
#if 0
	STDMETHOD(put_columnsWidth)(/*[in]*/ double newVal)
	{
		if (m_columnsFixedWidth != newVal)
		{
			m_columnsWidth = newVal;
			static_cast<T*>(this)->OnChangedTextFrameOptions();
		}
		return S_OK;
	}
#endif
};
