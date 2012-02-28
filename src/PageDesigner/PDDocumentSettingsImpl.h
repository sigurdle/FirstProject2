#pragma once

template <class T> class ATL_NO_VTABLE CPDDocumentSettingsImpl : 
	public IPDDocumentSettings
{
public:
	CPDDocumentSettingsImpl()
	{
		m_rasterResolution = 300;

		m_horizontalRulerUnits = UNIT_PT;
		m_verticalRulerUnits = UNIT_IN;

		m_gridsInBack = VARIANT_TRUE;
		m_verticalGridSubdivisions = 8;
		m_horizontalGridSubdivisions = 8;
		m_verticalGridlineEvery = 60.0;
		m_horizontalGridlineEvery = 60.0;

		m_transpGridSizeX = 8;
		m_transpGridSizeY = 8;
		m_transpGridColor0 = RGB(255, 255, 255);
		m_transpGridColor1 = RGB(194, 194, 194);
	}

	long m_rasterResolution;

	PDUnit m_horizontalRulerUnits;
	PDUnit m_verticalRulerUnits;

	VARIANT_BOOL m_gridsInBack;
	long m_horizontalGridSubdivisions;
	long m_verticalGridSubdivisions;
	double m_horizontalGridlineEvery;
	double m_verticalGridlineEvery;

	OLE_COLOR m_transpGridColor0;
	OLE_COLOR m_transpGridColor1;
	long m_transpGridSizeX;
	long m_transpGridSizeY;

DECLARE_PROTECT_FINAL_CONSTRUCT()

// IPDDocumentSettings
public:
	STDMETHOD(get_rasterResolution)(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_rasterResolution;
		return S_OK;
	}
	STDMETHOD(put_rasterResolution)(/*[in]*/ long newVal)
	{
		m_rasterResolution = newVal;
		return S_OK;
	}
	STDMETHODIMP get_verticalRulerUnits(/*[out, retval]*/ PDUnit *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_verticalRulerUnits;
		return S_OK;
	}
	STDMETHODIMP put_verticalRulerUnits(/*[in]*/ PDUnit newVal)
	{
		m_verticalRulerUnits = newVal;
		return S_OK;
	}
	STDMETHODIMP get_horizontalRulerUnits(/*[out, retval]*/ PDUnit *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_horizontalRulerUnits;
		return S_OK;
	}
	STDMETHODIMP put_horizontalRulerUnits(/*[in]*/ PDUnit newVal)
	{
		m_horizontalRulerUnits = newVal;
		return S_OK;
	}
	STDMETHODIMP get_horizontalGridlineEvery(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_horizontalGridlineEvery;
		return S_OK;
	}

	STDMETHODIMP put_horizontalGridlineEvery(double newVal)
	{
		m_horizontalGridlineEvery = newVal;
		return S_OK;
	}

	STDMETHODIMP get_verticalGridlineEvery(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_verticalGridlineEvery;
		return S_OK;
	}

	STDMETHODIMP put_verticalGridlineEvery(double newVal)
	{
		m_verticalGridlineEvery = newVal;
		return S_OK;
	}

	STDMETHODIMP get_horizontalGridSubdivisions(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_horizontalGridSubdivisions;
		return S_OK;
	}

	STDMETHODIMP put_horizontalGridSubdivisions(long newVal)
	{
		m_horizontalGridSubdivisions = newVal;
		return S_OK;
	}

	STDMETHODIMP get_verticalGridSubdivisions(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_verticalGridSubdivisions;
		return S_OK;
	}

	STDMETHODIMP put_verticalGridSubdivisions(long newVal)
	{
		m_verticalGridSubdivisions = newVal;
		return S_OK;
	}

// Transparency Grid
	STDMETHODIMP get_transpGridColor0(OLE_COLOR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transpGridColor0;
		return S_OK;
	}

	STDMETHODIMP get_transpGridColor1(OLE_COLOR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transpGridColor1;
		return S_OK;
	}

	STDMETHODIMP get_transpGridSizeX(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transpGridSizeX;
		return S_OK;
	}

	STDMETHODIMP get_transpGridSizeY(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_transpGridSizeY;
		return S_OK;
	}

	STDMETHODIMP setTranspGrid(long transpGridSizeX, long transpGridSizeY, OLE_COLOR transpGridColor0, OLE_COLOR transpGridColor1)
	{
		m_transpGridSizeX = transpGridSizeX;
		m_transpGridSizeY = transpGridSizeY;
		m_transpGridColor0 = transpGridColor0;
		m_transpGridColor1 = transpGridColor1;

		return S_OK;
	}

	STDMETHODIMP copyDocumentSettingsFrom(/*[in]*/ IPDDocumentSettings* other)
	{
	//	VARIANT_BOOL m_gridsInBack;

		other->get_horizontalRulerUnits(&m_horizontalRulerUnits);
		other->get_verticalRulerUnits(&m_verticalRulerUnits);
		other->get_horizontalGridlineEvery(&m_horizontalGridlineEvery);
		other->get_verticalGridlineEvery(&m_verticalGridlineEvery);
		other->get_horizontalGridSubdivisions(&m_horizontalGridSubdivisions);
		other->get_verticalGridSubdivisions(&m_verticalGridSubdivisions);

		other->get_transpGridSizeX(&m_transpGridSizeX);
		other->get_transpGridSizeY(&m_transpGridSizeY);
		other->get_transpGridColor0(&m_transpGridColor0);
		other->get_transpGridColor1(&m_transpGridColor1);

		return S_OK;
	}
};
