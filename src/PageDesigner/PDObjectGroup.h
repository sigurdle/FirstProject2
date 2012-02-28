#include "resource.h"

class CPDDocument;
class CObjectMap;

#include "PDObjectGroupImpl.h"
#include "PDObjectWrappableImpl.h"
#include "PDObjectWithAppearanceImpl.h"
#include "PDOpacityAndBlendModeImpl.h"

class ATL_NO_VTABLE CPDObjectGroup : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectGroup, &CLSID_PDObjectGroup>,
	public CPDObjectGroupImpl<CPDObjectGroup, IPDObjectGroup>,
	public CPDObjectWrappableImpl<CPDObjectGroup>,
	public CPDObjectWithAppearanceImpl<CPDObjectGroup, IPDObjectWithAppearance>,
	public CPDObjectTransformableImpl<CPDObjectGroup>,
	public CPDOpacityAndBlendModeImpl<CPDObjectGroup>,
	public CNotifyGetImpl<CPDObjectGroup>,
	public CNotifySendImpl<CPDObjectGroup>
{
public:
	CPDObjectGroup()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	virtual void CalculateBounds();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDObjectGroup, IPDObjectWithAppearance>::Render(pRenderer, pGraphics, scaleX, scaleY);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTGROUP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectGroup)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectGroup)
	COM_INTERFACE_ENTRY(IPDObjectWithChildren)
	COM_INTERFACE_ENTRY(IPDObjectLocatable)
	COM_INTERFACE_ENTRY(IPDObjectTransformable)
	COM_INTERFACE_ENTRY(IPDObjectWrappable)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDOpacityAndBlendMode)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// Called by IPDObjetcTransformableImpl
	void TransformMatrixChanged()
	{
		CalculateBounds();
		FireOnChanged(NOTIFY_MODIFY, NULL, DISPID_UNKNOWN);
	}

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		CalculateBounds();

		FireOnChanged(type, targetObject, dispID);

		return S_OK;
	}

// IPDObjectGroup
public:
	STDMETHOD(IsRectangular)(/*[out,retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
// IPDObject
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal);
// IPDObjectTransformable
	STDMETHOD(Scale)(/*[in]*/ double originx, /*[in]*/ double originy, /*[in]*/ double sx, /*[in]*/ double sy);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy)
	{
		return CPDObjectGroupImpl<CPDObjectGroup, IPDObjectGroup>::Move(dx, dy);
	}
// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
// IPDObjectWrappable
	STDMETHOD(put_textWrap)(/*[in]*/ PDTextWrap newVal);
};
