// PDObjectSymbolInstance.h : Declaration of the CPDObjectSymbolInstance

#ifndef __PDOBJECTSYMBOLINSTANCE_H_
#define __PDOBJECTSYMBOLINSTANCE_H_

#include "resource.h"       // main symbols

#include "PDObjectImpl.h"
#include "PDObjectTransformableImpl.h"
#include "PDObjectWithOpacityMaskImpl.h"
#include "PDObjectWithAppearanceImpl.h"
#include "PDOpacityAndBlendModeImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CPDObjectSymbolInstance
class ATL_NO_VTABLE CPDObjectSymbolInstance : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectSymbolInstance, &CLSID_PDObjectSymbolInstance>,
	public CPDObjectImpl<IPDObjectSymbolInstance>,
	public CPDObjectTransformableImpl<CPDObjectSymbolInstance>,
	public CPDObjectWithOpacityMaskImpl<CPDObjectSymbolInstance>,
	public CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>,
	public CPDOpacityAndBlendModeImpl<CPDObjectSymbolInstance>,
	public CNotifyGetImpl<CPDObjectSymbolInstance>,
	public CNotifySendImpl<CPDObjectSymbolInstance>
{
public:
	CPDObjectSymbolInstance()
	{
		m_x = 0;
		m_y = 0;
	}

	int FinalConstruct();
	void FinalRelease();

	double m_x;
	double m_y;
	CComPtr<IPDSymbol> m_symbol;

	virtual void CalculateBounds();
	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDObjectSymbolInstance, IPDObjectWithAppearance>::Render(pRenderer, pGraphics, scaleX, scaleY);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTSYMBOLINSTANCE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectSymbolInstance)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectSymbolInstance)
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
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// IPDObjectSymbolInstance
public:
	STDMETHOD(setxy)(/*[in]*/ double x, /*[in]*/ double y);
	STDMETHOD(get_y)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_x)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_symbol)(/*[out, retval]*/ IPDSymbol* *pVal);
	STDMETHOD(put_symbol)(/*[in]*/ IPDSymbol* newVal);
// IPDObject
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);

	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = OBJECT_SYMBOLINSTANCE;
		return S_OK;
	}
// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDObjectSymbolInstance;
		return S_OK;
	}
};

#endif //__PDOBJECTSYMBOLINSTANCE_H_
