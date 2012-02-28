#pragma once

#include "resource.h"

class ATL_NO_VTABLE CPDFilterPrimitive : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDFilterPrimitive, &CLSID_PDFilterPrimitive>,
	public IPDFilterPrimitive,
	public IObjectSerializable,
	public CNotifySendImpl<CPDFilterPrimitive>
{
public:
	CPDFilterPrimitive()
	{
		m_nextSibling = NULL;
		m_previousSibling = NULL;
		m_parent = NULL;

		m_type = 0;

		for (int i = 0; i < 8; i++)
		{
			m_inpins[i] = NULL;
		}
	}

	int FinalConstruct()
	{
		m_effectRecord = new PFILTERRECORD;
		memset(m_effectRecord, 0, sizeof(PFILTERRECORD));

		return S_OK;
	}

	void FinalRelease()
	{
		delete m_effectRecord;
	}

	IPDAppearance* m_parent;
	IPDFilterPrimitive* m_nextSibling;
	IPDFilterPrimitive* m_previousSibling;

	CComPtr<IPluginFilter> m_pluginFilter;

	_bstr_t m_name;
//
	PFILTERRECORD*	m_effectRecord;
	long m_in_origin_x;
	long m_in_origin_y;
	long m_out_origin_x;
	long m_out_origin_y;
//


	CArray<int,int> m_subPoints;
	CArray<CDblPoint,CDblPoint> m_flatPoints;

	long m_type;
	IPDFilterPrimitive* m_inpins[8];

	void SetupEffectRecord();

	long GetInPinCount()
	{
		if (m_pluginFilter)
		{
			long n;
			m_pluginFilter->GetInPinCount(&n);
			return n;
		}
		return 0;
	}

	IPDFilterPrimitive* GetInPin(long n)
	{
		CComPtr<IPDFilterPrimitive> fp;
		GetInPin(n, &fp);
		return fp;
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDFILTERPRIMITIVE)

BEGIN_COM_MAP(CPDFilterPrimitive)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDFilterPrimitive)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

public:
	STDMETHOD(GetType)(/*[out,retval]*/ long* pVal);
	STDMETHOD(SetInPin)(/*[in]*/ long n, /*[in]*/ IPDFilterPrimitive* newVal);
	STDMETHOD(get_name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHODIMP get_nextSibling(/*[out, retval]*/ IPDFilterPrimitive* *pVal);
	STDMETHODIMP put_nextSibling(/*[in]*/ IPDFilterPrimitive* newVal);
	STDMETHODIMP get_previousSibling(/*[out, retval]*/ IPDFilterPrimitive* *pVal);
	STDMETHODIMP put_previousSibling(/*[in]*/ IPDFilterPrimitive* newVal);
	STDMETHODIMP get_parent(/*[out, retval]*/ IPDAppearance* *pVal);
	STDMETHODIMP put_parent(/*[in]*/ IPDAppearance* newVal);
	STDMETHODIMP get_pluginFilter(/*[out, retval]*/ IPluginFilter* *pVal);
	STDMETHODIMP put_pluginFilter(/*[in]*/ IPluginFilter* newVal);
	STDMETHODIMP GetInPin(/*[in]*/ long n, /*[out,retval]*/ IPDFilterPrimitive* *pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDFilterPrimitive;
		return S_OK;
	}
};
