#pragma once

class CPDColor;
class CPDGradient;

class ATL_NO_VTABLE CPDBrush : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDBrush,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDBrush>,
	public CNotifySendImpl<CPDBrush>
{
public:
	CPDBrush()
	{
		m_brushType = (PDBrushType)0;

		m_x1 = 0;
		m_y1 = 0;
		m_x2 = 100;
		m_y2 = 100;

		m_gradient = NULL;
		m_color = NULL;

		m_colorTint = 1.0;
	}

	void FinalRelease();

	PDBrushType m_brushType;
	CComPtr<IPDSwatch> m_swatch;

	CComObject<CPDGradient>* m_gradient;
	CComObject<CPDColor>* m_color;
	double m_colorTint;

	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDBrush)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDBrush)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDBrush
public:
	STDMETHOD(getCommon)(/*[in]*/ IPDBrush* brush);
	STDMETHOD(setCommon)(/*[in]*/ IPDBrush* brush);
	STDMETHOD(IsEqual)(/*[in]*/ IPDBrush* brush);
	STDMETHOD(get_tintedColor)(/*[out, retval]*/ IPDColor* *pVal);
	STDMETHOD(clone)(/*[out,retval]*/ IPDBrush* *pVal);
	STDMETHOD(get_y2)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_y2)(/*[in]*/ double newVal);
	STDMETHOD(get_x2)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_x2)(/*[in]*/ double newVal);
	STDMETHOD(get_y1)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_y1)(/*[in]*/ double newVal);
	STDMETHOD(get_x1)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_x1)(/*[in]*/ double newVal);
	STDMETHOD(setColor)(/*[out,retval]*/ IPDColor* *pVal);
	STDMETHOD(setNone)();
	STDMETHOD(get_tintedRGBColor)(/*[out, retval]*/ IPDColor* *pVal);
	STDMETHOD(get_colorTint)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_colorTint)(/*[in]*/ double newVal);
	STDMETHOD(get_color)(/*[out, retval]*/ IPDColor* *pVal);
	STDMETHOD(get_gradient)(/*[out, retval]*/ IPDGradient* *pVal);
	STDMETHOD(setGradient)(/*[out,retval]*/ IPDGradient* *gradient);
	STDMETHOD(get_brushType)(PDBrushType *pVal);
	STDMETHOD(put_brushType)(PDBrushType newVal);
	STDMETHOD(get_swatch)(IPDSwatch* *pVal);
	STDMETHOD(put_swatch)(IPDSwatch* newVal);
//	STDMETHOD(saveAsXML)(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node);
//	STDMETHOD(loadXML)(/*[in]*/ IDOMNode* node);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_NULL;
		return S_OK;
	}
};
