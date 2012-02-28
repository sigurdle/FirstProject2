#pragma once

#include "resource.h"

#include "ObjectMap.h"
class CPDFilterPrimitive;

class ATL_NO_VTABLE CPDAppearance : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDAppearance, &CLSID_PDAppearance>,
	public IPDAppearance,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDAppearance>,
	public CNotifySendImpl<CPDAppearance>
{
public:
	CPDAppearance()
	{
		m_firstChild = NULL;
		m_lastChild = NULL;
		m_children = NULL;

		m_cItems[0] = NULL;
		m_cItems[1] = NULL;
		m_cItems[2] = NULL;
		m_cItems[3] = NULL;
		m_cItems[4] = NULL;

		m_expandedRect.X = 0xcacaca;
		m_expandedRect.Y = 0xcacaca;
		m_expandedRect.Width = 0xcacaca;
		m_expandedRect.Height = 0xcacaca;
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CObjectMap>* m_children;
	IPDFilterPrimitive* m_firstChild;
	IPDFilterPrimitive* m_lastChild;
	CComObject<CPDFilterPrimitive>* m_cItems[5];

	RectD m_expandedRect;

	BOOL SetupChildrenLayers(IPDObjectWithAppearance* refObject);
	Gdiplus::Bitmap* ProcessEffects(IPDObjectWithAppearance* refObject, double x_sampling, double y_sampling);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDAPPEARANCE)

BEGIN_COM_MAP(CPDAppearance)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDAppearance)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

public:
	STDMETHOD(clone)(/*[out,retval]*/ IPDAppearance* *pVal);
	STDMETHOD(IsEqual)(/*[in]*/ IPDAppearance *appearance);
	STDMETHODIMP get_filterEffects(IObjectMap* *pVal);
	STDMETHODIMP get_firstChild(IPDFilterPrimitive* *pVal);
	STDMETHODIMP get_lastChild(IPDFilterPrimitive* *pVal);
	STDMETHODIMP insertEffect(IPDFilterPrimitive* object, IPDFilterPrimitive* before);
	STDMETHODIMP removeEffect(IPDFilterPrimitive* object);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDAppearance;
		return S_OK;
	}
};
