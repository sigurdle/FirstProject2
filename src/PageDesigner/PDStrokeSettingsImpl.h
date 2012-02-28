#pragma once

template <class T> class CPDStrokeSettingsImpl :
	public IPDStrokeSettings
{
public:
	CPDStrokeSettingsImpl()
	{
		m_strokeWeight = 1.0;
		m_strokeCap = 0;
		m_strokeJoin = 0;
		m_strokeMiterLimit = 4;

		m_dashValues[0] = 0;
		m_dashValues[1] = 0;
		m_dashValues[2] = 0;
		m_dashValues[3] = 0;
		m_dashValues[4] = 0;
		m_dashValues[5] = 0;
	}

	double m_strokeWeight;
	long m_strokeCap;
	long m_strokeJoin;
	double m_strokeMiterLimit;

	double m_dashValues[6];

	STDMETHODIMP get_strokeWeight(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_strokeWeight;
		return S_OK;
	}

	STDMETHODIMP put_strokeWeight(double newVal)
	{
		m_strokeWeight = newVal;
//		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
		return S_OK;
	}

	STDMETHODIMP get_strokeCap(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_strokeCap;
		return S_OK;
	}

	STDMETHODIMP put_strokeCap(long newVal)
	{
		m_strokeCap = newVal;
//		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
		return S_OK;
	}

	STDMETHODIMP get_strokeJoin(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_strokeJoin;
		return S_OK;
	}

	STDMETHODIMP put_strokeJoin(long newVal)
	{
		m_strokeJoin = newVal;
//		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
		return S_OK;
	}

	STDMETHODIMP get_strokeMiterLimit(double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_strokeMiterLimit;
		return S_OK;
	}

	STDMETHODIMP put_strokeMiterLimit(double newVal)
	{
		m_strokeMiterLimit = newVal;
//		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);
		return S_OK;
	}

	STDMETHODIMP setDashedValue(long index, double value)
	{
		m_dashValues[index] = value;

//		FireOnChanged(NOTIFY_MODIFY, GetUnknown(), DISPID_UNKNOWN);

		return S_OK;
	}

	STDMETHODIMP getDashedValue(long index, double *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_dashValues[index];
		return S_OK;
	}

	STDMETHODIMP get_dashedCount(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		for (int i = 0; i < 6; i++)
		{
			if (m_dashValues[i] <= 0)
				break;
		}

		*pVal = i;

		return S_OK;
	}
};