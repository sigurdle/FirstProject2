#pragma once

#include "resource.h"

class CPDDocument;

class ATL_NO_VTABLE CPDLayer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDLayer, &CLSID_PDLayer>,
	public IPDLayer,
	public IObjectSerializable,
	public CNotifySendImpl<CPDLayer>
{
public:
	CPDLayer()
	{
		m_name = L"";
		m_visible = VARIANT_TRUE;
		m_locked = VARIANT_FALSE;
		m_color = RGB(0,0,0);

		m_pDocument = NULL;
		m_nextSibling = NULL;
		m_previousSibling = NULL;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CoCreateGuid(&m_uniqID);
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	GUID m_uniqID;

	CPDDocument* m_pDocument;
	CComObject<CPDLayer>* m_nextSibling;
	CComObject<CPDLayer>* m_previousSibling;

	_bstr_t m_name;
	VARIANT_BOOL m_visible;
	VARIANT_BOOL m_locked;
	OLE_COLOR	m_color;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDLAYER)

BEGIN_COM_MAP(CPDLayer)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDLayer)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDLayer
public:
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ IPDLayer* *pVal);
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ IPDLayer* *pVal);
	STDMETHOD(get_uniqId)(/*[out, retval]*/ GUID *pVal);
	STDMETHOD(get_color)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_color)(/*[in]*/ OLE_COLOR newVal);
	STDMETHOD(get_name)(BSTR *pVal);
	STDMETHOD(put_name)(BSTR newVal);
	STDMETHOD(get_visible)(VARIANT_BOOL *pVal);
	STDMETHOD(put_visible)(VARIANT_BOOL newVal);
	STDMETHOD(get_locked)(VARIANT_BOOL *pVal);
	STDMETHOD(put_locked)(VARIANT_BOOL newVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
