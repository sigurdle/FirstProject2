#include "resource.h"

class ATL_NO_VTABLE CPDSection : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CPDSection, &CLSID_PDGradient>,
	public IPDSection
{
public:
	CPDSection()
	{
		m_style = 0;
		m_pageNumbering = 0;
		m_pageNumberingStartAt = 0;
	}

	int FinalConstruct();
	void FinalRelease();

	long m_style;
	long m_pageNumbering;
	long m_pageNumberingStartAt;

DECLARE_PROTECT_FINAL_CONSTRUCT()

//DECLARE_REGISTRY_RESOURCEID(IDR_PDGRADIENT)

BEGIN_COM_MAP(CPDSection)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSection)
END_COM_MAP()

// IPDSection
public:
	STDMETHOD(get_style)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_style)(/*[in]*/ long newVal);
	STDMETHOD(get_pageNumbering)(long *pVal);
	STDMETHOD(put_pageNumbering)(long newVal);
	STDMETHOD(get_pageNumberingStartAt)(long *pVal);
	STDMETHOD(put_pageNumberingStartAt)(long newVal);
};
