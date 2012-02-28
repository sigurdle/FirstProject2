class CPDDocument;

class ATL_NO_VTABLE CPDImage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IPDImage,
	public IObjectSerializable
{
public:
	CPDImage()
	{
		m_pDocument = NULL;
		m_image = NULL;
	}

	~CPDImage()
	{
		if (m_image)
		{
			delete m_image;
			m_image = NULL;
		}
	}

	int FinalConstruct()
	{
		return S_OK;
	}

	DWORD m_userdata;

	CPDDocument* m_pDocument;

	_bstr_t m_pathName;
	Gdiplus::Image* m_image;

	void Render(Gdiplus::Graphics* graphics, Gdiplus::RectF& destRect);

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDImage)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDImage)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDImage
public:
	STDMETHOD(GetProp)(/*[in]*/ BSTR name, /*[out,retval]*/ DWORD* pVal);
	STDMETHOD(SetProp)(/*[in]*/ BSTR name, /*[in]*/ DWORD value);
	STDMETHOD(get_height)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_width)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_privateImage)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_privateImage)(/*[in]*/ DWORD newVal);
	STDMETHOD(get_pathName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_pathName)(/*[in]*/ BSTR newVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_NULL;//PDContentGraphic;
		return S_OK;
	}
};
