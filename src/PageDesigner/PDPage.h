#pragma once

#include "resource.h"

class CPDDocument;
class CPDSpread;
class CPDSpreadMaster;
class CPDSection;
template<class IBase> class CPDSpreadImpl;

class ATL_NO_VTABLE CPDPage : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDPage, &CLSID_PDPage>,
	public IPDPage,
	public IObjectSerializable
{
public:
	CPDPage()
	{
		m_pDocument = NULL;
		m_ownerSpread = NULL;
		m_baseMaster = NULL;

		m_marginsAndColumnsOverriden = FALSE;

		m_marginTop = 0;
		m_marginBottom = 0;
		m_marginInside = 0;
		m_marginOutside = 0;

		m_columnNumber = 1;
		m_columnGutter = 0;

		m_section = NULL;
	}

	CPDDocument* m_pDocument;
	CPDSpreadImpl<IPDSpread>* m_ownerSpread;
	CPDSpreadMaster* m_baseMaster;
	
	CComObject<CPDSection>* m_section;

	CPDPage* GetBasePage();

	BOOL m_marginsAndColumnsOverriden;

	double m_marginTop;
	double m_marginBottom;
	double m_marginInside;
	double m_marginOutside;

	long m_columnNumber;
	double m_columnGutter;

	bool IsLeftOfSpine();

	double GetMarginInside();
	double GetMarginOutside();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDPAGE)

BEGIN_COM_MAP(CPDPage)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDPage)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDPage
public:
	STDMETHOD(getPageRect)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(get_columnGutter)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_columnGutter)(/*[in]*/ double newVal);
	STDMETHOD(get_columnNumber)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_columnNumber)(/*[in]*/ long newVal);
	STDMETHOD(get_section)(/*[out, retval]*/ IPDSection* *pVal);
	STDMETHOD(put_section)(/*[in]*/ IPDSection* newVal);
	STDMETHOD(get_baseMaster)(/*[out, retval]*/ IPDSpreadMaster* *pVal);
	STDMETHOD(put_baseMaster)(/*[in]*/ IPDSpreadMaster* newVal);
	STDMETHOD(get_ownerSpread)(/*[out, retval]*/ IPDSpread* *pVal);
	STDMETHOD(get_marginRight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_marginLeft)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_marginBottom)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_marginTop)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_marginOutside)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_marginInside)(/*[out, retval]*/ double *pVal);
	STDMETHOD(setMarginsAndColumns)(double marginTop, double marginBottom, double marginInside, double marginOutside, long columnNumber, double columnGutter);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
