#pragma once

template <class T> class ATL_NO_VTABLE CPDOpacityAndBlendModeImpl :
	public IPDOpacityAndBlendMode
{
public:
	CPDOpacityAndBlendModeImpl()
	{
		m_blendmode = 0;	// Normal
		m_opacity = 1.0;
	}

	long m_blendmode;
	double m_opacity;

public:
	STDMETHODIMP get_opacity(/*[out, retval]*/ double* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_opacity;
		return S_OK;
	}

	STDMETHODIMP put_opacity(/*[in]*/ double newVal)
	{
		m_opacity = newVal;
		static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		return S_OK;
	}

	STDMETHODIMP get_blendmode(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_blendmode;
		return S_OK;
	}

	STDMETHODIMP put_blendmode(/*[in]*/ long newVal)
	{
		m_blendmode = newVal;
		static_cast<T*>(this)->FireOnChanged(NOTIFY_MODIFY, static_cast<T*>(this)->GetUnknown(), /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
		return S_OK;
	}
};
