class ATL_NO_VTABLE CPDColor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDColor,
	public IObjectSerializable,
	public CNotifySendImpl<CPDColor>
{
public:
	CPDColor()
	{
		m_colorMode = (PDColorMode)COLORMODE_RGB;

		m_channel[0] = 0;
		m_channel[1] = 0;
		m_channel[2] = 0;
		m_channel[3] = 0;
	}

	PDColorMode m_colorMode;
	double m_channel[4];

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDColor)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDColor)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

#if 0
BEGIN_PROP_MAP(CPDColor)
/*
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
*/
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()
#endif

// IPDColor
public:
	STDMETHOD(get_colorMode)(PDColorMode *pVal);
	STDMETHOD(put_colorMode)(PDColorMode newVal);
	STDMETHOD(copy)(/*[in]*/ IPDColor* color);
	STDMETHOD(clone)(/*[out,retval]*/ IPDColor* *pVal);
	STDMETHOD(setRGB)(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue);
	STDMETHOD(putChannel)(long n, double value);
	STDMETHOD(getChannel)(long n, double* pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_NULL;
		return S_OK;
	}
};
