#include "resource.h"

class CPDDocument;
class CObjectMap;
class CPDGuides;

#include "PDGuides.h"

#include "PDObjectGroupImpl.h"
#include "PDObjectLocatableImpl.h"

class ATL_NO_VTABLE CPDObjectLayerGroup : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectLayerGroup, &CLSID_PDObjectLayerGroup>,
	public CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>,
	public CPDObjectLocatableImpl<CPDObjectLayerGroup, IPDObjectLocatable>,
	public CNotifyGetImpl<CPDObjectLayerGroup>,
	public CNotifySendImpl<CPDObjectLayerGroup>
{
public:
	CPDObjectLayerGroup()
	{
		m_guides = NULL;

		m_enableBackground = 1;	// New
	}

	int FinalConstruct();
	void FinalRelease();

	CComObject<CPDGuides>*	m_guides;

	virtual IPDObjectUnknown* getObjectByUniqId(GUID guid)
	{
		IPDObjectUnknown* f;

		f = m_guides->getObjectByUniqId(guid);
		if (f) return f;

		f = CPDObjectUnknownImpl<IPDObjectLayerGroup>::getObjectByUniqId(this, guid);
		if (f) return f;

		return NULL;
	}

	virtual void CalculateBounds();
	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTLAYERGROUP)

BEGIN_COM_MAP(CPDObjectLayerGroup)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectGroup)
	COM_INTERFACE_ENTRY(IPDObjectLayerGroup)
	COM_INTERFACE_ENTRY(IPDObjectLocatable)
	COM_INTERFACE_ENTRY(IPDObjectWithChildren)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);
// CNotifySendImpl
	STDMETHODIMP FireOnChanged(NotifyType type, IUnknown* targetObject, /*IUnknown* immtargetObject,*/ DISPID dispID);

// IPDObjectLayerGroup
public:
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(get_guides)(/*[out, retval]*/ IPDGuides* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_guides;
		(*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = OBJECT_LAYERGROUP;
		return S_OK;
	}
	STDMETHOD(Scale)(/*[in]*/ double originx, /*[in]*/ double originy, /*[in]*/ double sx, /*[in]*/ double sy)
	{
		return S_OK;
	}
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy)
	{
		return CPDObjectGroupImpl<CPDObjectLayerGroup, IPDObjectLayerGroup>::Move(dx, dy);
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
