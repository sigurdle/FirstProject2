#include "resource.h"

class CPDColor;
class CPDGradient;

class ATL_NO_VTABLE CPDGradientStop : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDGradientStop, &CLSID_PDGradientStop>,
	public IPDGradientStop,
	public CNotifyGetImpl<CPDGradientStop>,
	public CNotifySendImpl<CPDGradientStop>,
	//public IPropertyNotifySink
	public IObjectSerializable
{
public:
	CPDGradientStop()
	{
		m_color = NULL;

		m_middle = 0.5;
		m_offset = 0;

		m_parent = NULL;
		m_previousSibling = NULL;
		m_nextSibling = NULL;
	}

//	int FinalConstruct();
	void FinalRelease();

	double m_middle;
	double m_offset;

	CComObject<CPDColor>* m_color;
	CComPtr<IPDSwatch> m_swatch;

	CComObject<CPDGradient>* m_parent;
	CComObject<CPDGradientStop>* m_previousSibling;
	CComObject<CPDGradientStop>* m_nextSibling;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDGRADIENTSTOP)

BEGIN_COM_MAP(CPDGradientStop)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDGradientStop)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
//	COM_INTERFACE_ENTRY(IPropertyNotifySink)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

/*
	STDMETHODIMP OnRequestEdit(
  DISPID dispID  //Dispatch identifier of the property that is about 
                 //to change
)
{
	ATLASSERT(0);
	return S_OK;
}
*/

// IPDGradientStop
public:
	STDMETHOD(getFinalColor)(/*[out,retval]*/ IPDColor* *pVal);
	STDMETHOD(get_swatch)(/*[out, retval]*/ IPDSwatch* *pVal);
	STDMETHOD(put_swatch)(/*[in]*/ IPDSwatch* newVal);
	STDMETHOD(get_nextSibling)(/*[out, retval]*/ IPDGradientStop* *pVal);
	STDMETHOD(get_previousSibling)(/*[out, retval]*/ IPDGradientStop* *pVal);
	STDMETHOD(get_parent)(/*[out, retval]*/ IPDGradient* *pVal);
	STDMETHOD(get_middle)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_middle)(/*[in]*/ double newVal);
	STDMETHOD(get_offset)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_offset)(/*[in]*/ double newVal);
	STDMETHOD(get_color)(/*[out, retval]*/ IPDColor* *pVal);
	STDMETHOD(setColorRGB)(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDGradientStop;
		return S_OK;
	}
};
