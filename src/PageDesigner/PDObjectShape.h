#include "resource.h"

#include "PDObjectImpl.h"

#include "PDObjectTransformableImpl.h"
#include "PDObjectWrappableImpl.h"
#include "PDObjectWithOpacityMaskImpl.h"
#include "PDObjectWithAppearanceAndStrokeFillImpl.h"
#include "PDOpacityAndBlendModeImpl.h"

class CPDBrush;
class CPDDocument;
class CPDPath;
class CPDAppearance;

class ATL_NO_VTABLE CPDObjectFrame : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectFrame, &CLSID_PDObjectFrame>,
	public CPDObjectImpl<IPDObjectFrame>,
	public CPDObjectWrappableImpl<CPDObjectFrame>,
	public CPDObjectTransformableImpl<CPDObjectFrame>,
	public CPDObjectWithOpacityMaskImpl<CPDObjectFrame>,
	public CPDObjectWithAppearanceAndStrokeFillImpl<CPDObjectFrame>,
	public CPDOpacityAndBlendModeImpl<CPDObjectFrame>,
	public CNotifyGetImpl<CPDObjectFrame>,
	public CNotifySendImpl<CPDObjectFrame>,
	public IUIActivatable
{
public:
	CPDObjectFrame()
	{
		m_path = NULL;

		m_content = NULL;
		m_pathText = NULL;

		m_gdppath = NULL;

		m_activeStroke = NULL;
		m_activeFill = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	Gdiplus::GraphicsPath* m_gdppath;

	CComObject<CPDPath>* m_path;

	IPDObject* m_content;
	IPDPathText* m_pathText;

	IPDObjectStroke* m_activeStroke;
	IPDObjectFill* m_activeFill;

	virtual Gdiplus::RectF	GetBounds();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDObjectFrame, IPDObjectWithAppearanceAndStrokeFill>::Render(pRenderer, pGraphics, scaleX, scaleY);
	}

	virtual void CalculateBounds();

	void RecreateWrapPath();

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTFRAME)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectFrame)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectFrame)
	COM_INTERFACE_ENTRY(IPDObjectWrappable)
	COM_INTERFACE_ENTRY(IPDObjectLocatable)
	COM_INTERFACE_ENTRY(IPDObjectTransformable)
	COM_INTERFACE_ENTRY(IPDObjectWithOpacityMask)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearanceAndStrokeFill)
	COM_INTERFACE_ENTRY(IPDOpacityAndBlendMode)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IPDObjectWithChildren)
	COM_INTERFACE_ENTRY(IUIActivatable)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// Called by IPDObjectTransformableImpl
	void TransformMatrixChanged()
	{
	// CalculateBounds is called in our overrided FireOnChanged (maybe it shouldn't be)
		FireOnChanged(NOTIFY_MODIFY, NULL, DISPID_UNKNOWN);
	}

// CNotifySendImpl
	STDMETHODIMP FireOnChanged(NotifyType type, IUnknown* targetObject/*, IUnknown* immtargetObject*/, DISPID dispID);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// IUIActivatable
	STDMETHODIMP OnActivate(IUIManager* uiManager)
	{
		//if (m_activeStroke) uiManager->ActivateObject(GetUnknown(), m_activeStroke);
		//if (m_activeFill) uiManager->ActivateObject(GetUnknown(), m_activeFill);

		return S_OK;
	}

	STDMETHODIMP OnDeactivate(IUIManager* uiManager)
	{
		return S_OK;
	}

// IPDObjectFrame
public:
//	STDMETHOD(copyAppearanceFrom)(/*[in]*/ IPDObjectWithAppearanceAndStrokeFill* other);
//	STDMETHOD(get_activeFill)(/*[out, retval]*/ IPDObjectFill* *pVal);
//	STDMETHOD(put_activeFill)(/*[in]*/ IPDObjectFill* newVal);
//	STDMETHOD(get_activeStroke)(/*[out, retval]*/ IPDObjectStroke* *pVal);
//	STDMETHOD(put_activeStroke)(/*[in]*/ IPDObjectStroke* newVal);
//	STDMETHOD(removeSubObject)(/*[in]*/ IPDObjectWithBrush* object);
	STDMETHOD(appendSubObject)(/*[in]*/ IPDObjectWithBrush* object);
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(IsPointOverStrokeOutline)(/*[in]*/ PointD pt, /*[out,retval]*/ BOOL* pVal);
	STDMETHOD(get_content)(/*[out, retval]*/ IPDObject* *pVal);
	STDMETHOD(put_content)(/*[in]*/ IPDObject* newVal);
	STDMETHOD(get_path)(/*[out, retval]*/ IPDPath* *pVal);
	STDMETHOD(put_path)(/*[in]*/ IPDPath* newVal);
	STDMETHOD(get_pathText)(/*[out, retval]*/ IPDPathText* *pVal);
	STDMETHOD(put_pathText)(/*[in]*/ IPDPathText* newVal);
// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
#if 0
// IPDObjectWithAppearanceAndStrokeFill
	STDMETHOD(get_subObjects)(/*[out, retval]*/ IObjectMap* *pVal);
#endif
// IPDObject
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal);
// IPDObjectTransformable
	STDMETHOD(Scale)(/*[in]*/ double originx, /*[in]*/ double originy, /*[in]*/ double sx, /*[in]*/ double sy);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);
	STDMETHOD(removeObject)(/*[in]*/ IPDObjectUnknown* object);
// IPDObjectWrappable
	STDMETHOD(IsRectangular)(/*[out,retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_textWrap)(/*[in]*/ PDTextWrap newVal);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};
