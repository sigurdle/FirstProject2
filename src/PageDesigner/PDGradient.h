#include "resource.h"

class CObjectMap;
class CPDGradientStop;

class ATL_NO_VTABLE CPDGradient : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDGradient, &CLSID_PDGradient>,
	public IPDGradient,
	public IObjectSerializable,
	public CNotifyGetImpl<CPDGradient>,
	public CNotifySendImpl<CPDGradient>
{
public:
	CPDGradient()
	{
		m_type = GRADIENT_LINEAR;

		m_stops = NULL;

		m_firstChild = NULL;
		m_lastChild = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	PDGradientType m_type;

	CComObject<CObjectMap>* m_stops;
	CComObject<CPDGradientStop>* m_firstChild;
	CComObject<CPDGradientStop>* m_lastChild;

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDGRADIENT)

BEGIN_COM_MAP(CPDGradient)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDGradient)
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

// IPDGradient
public:
	STDMETHOD(copy)(/*[in]*/ IPDGradient* gradient);
	STDMETHOD(get_type)(/*[out, retval]*/ PDGradientType *pVal);
	STDMETHOD(put_type)(/*[in]*/ PDGradientType newVal);
	STDMETHOD(clone)(/*[out,retval]*/ IPDGradient* *pVal);
	STDMETHOD(Equals)(/*[in]*/ IPDGradient* gradient, /*[out,retval]*/ VARIANT_BOOL* pVal);
	STDMETHOD(get_lastChild)(/*[out, retval]*/ IPDGradientStop* *pVal);
	STDMETHOD(get_firstChild)(/*[out, retval]*/ IPDGradientStop* *pVal);
	STDMETHOD(removeStop)(/*[in]*/ IPDGradientStop* stop);
	STDMETHOD(createStop)(/*[out,retval]*/ IPDGradientStop* *pVal);
	STDMETHOD(append)(/*[in]*/ IPDGradientStop* stop);
	STDMETHOD(get_stops)(/*[out,retval]*/ IObjectMap* *pVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDGradient;
		return S_OK;
	}
};
