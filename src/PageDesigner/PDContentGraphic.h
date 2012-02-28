class CPDDocument;
class CPDImage;

#include "PDObjectImpl.h"
#include "PDObjectTransformableImpl.h"
#include "PDObjectWithOpacityMaskImpl.h"
#include "PDObjectWithAppearanceImpl.h"
#include "PDOpacityAndBlendModeImpl.h"

class ATL_NO_VTABLE CPDContentGraphic : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDContentGraphic, &CLSID_PDContentGraphic>,
	public CPDObjectImpl<IPDContentGraphic>,
	public CPDObjectTransformableImpl<CPDContentGraphic>,
	public CPDObjectWithOpacityMaskImpl<CPDContentGraphic>,
	public CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>,
	public CPDOpacityAndBlendModeImpl<CPDContentGraphic>,
	public CNotifyGetImpl<CPDContentGraphic>,
	public CNotifySendImpl<CPDContentGraphic>
{
public:
	CPDContentGraphic()
	{
		m_x = 0;
		m_y = 0;
		m_image = NULL;
	}

	~CPDContentGraphic()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	double m_x;
	double m_y;
	CComObject<CPDImage>* m_image;

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* graphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDContentGraphic, IPDObjectWithAppearance>::Render(pRenderer, graphics, scaleX, scaleY);
	}

	virtual void CalculateBounds();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDCONTENTGRAPHIC)

BEGIN_COM_MAP(CPDContentGraphic)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDContentGraphic)
	COM_INTERFACE_ENTRY(IPDObjectLocatable)
	COM_INTERFACE_ENTRY(IPDObjectTransformable)
	COM_INTERFACE_ENTRY(IPDObjectWithOpacityMask)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDOpacityAndBlendMode)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
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
		CalculateBounds();	// TODO, not always nessecary
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDContentGraphic
public:
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(setxy)(/*[in]*/ double x, /*[in]*/ double y);
	STDMETHOD(get_y)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_x)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal);
	STDMETHOD(get_image)(/*[out, retval]*/ IPDImage* *pVal);
	STDMETHOD(put_image)(/*[in]*/ IPDImage* newVal);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDContentGraphic;
		return S_OK;
	}
};
