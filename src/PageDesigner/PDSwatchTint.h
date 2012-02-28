#include "PDSwatchImpl.h"

class ATL_NO_VTABLE CPDSwatchTint :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDSwatchImpl<CPDSwatchTint, IPDSwatchTint>
{
public:
	CPDSwatchTint()
	{
		m_tint = 1.0;
	}

	double m_tint;
	CComPtr<IPDSwatchColor> m_swatchColor;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSwatchTint)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSwatch)
	COM_INTERFACE_ENTRY(IPDSwatchTint)

	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDSwatchTint
public:
	STDMETHOD(get_finalColor)(/*[out, retval]*/ IPDColor* *pVal);
	STDMETHOD(clone)(/*[out,retval]*/ IPDSwatch* *pVal);
	STDMETHOD(get_tint)(double *pVal);
	STDMETHOD(put_tint)(double newVal);
	STDMETHOD(get_swatchColor)(IPDSwatchColor* *pVal);
	STDMETHOD(put_swatchColor)(IPDSwatchColor* newVal);
	STDMETHOD(get_swatchType)(PDSwatchType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = SWATCH_TINT;
		return S_OK;
	}
};
