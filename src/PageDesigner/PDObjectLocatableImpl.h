#pragma once

#include "PDMatrix.h"
#include "PDDocument.h"

template <class T, class IBase> class ATL_NO_VTABLE CPDObjectLocatableImpl :
	public IBase
{
public:
	CPDObjectLocatableImpl()
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
		return S_OK;
	}

	void FinalRelease()
	{
	}

	RectD	m_bounds;
	RectD m_xbounds;

public:
	STDMETHOD(get_bounds)(/*[out, retval]*/ RectD *pVal)
	{
		*pVal = m_bounds;
		return S_OK;
	}
	STDMETHOD(get_xbounds)(/*[out, retval]*/ RectD *pVal)
	{
		*pVal = m_xbounds;
		return S_OK;
	}
	STDMETHOD(Scale)(/*[in]*/ double originx, /*[in]*/ double originy, /*[in]*/ double sx, /*[in]*/ double sy)
	{
		return S_OK;
	}
#if 0
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy)
	{
		return S_OK;
	}
#endif
};
