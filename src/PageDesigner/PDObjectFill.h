// PDFill.h : Declaration of the CPDObjectFill

#ifndef __PDFILL_H_
#define __PDFILL_H_

#include "resource.h"       // main symbols

#include "PDObjectWithBrushImpl.h"
#include "PDOpacityAndBlendModeImpl.h"

//#include "PDBrush.h"

/////////////////////////////////////////////////////////////////////////////
// CPDObjectFill
class ATL_NO_VTABLE CPDObjectFill : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectFill, &CLSID_PDObjectFill>,
	public CPDObjectWithBrushImpl<CPDObjectFill, IPDObjectFill>,
	public CPDOpacityAndBlendModeImpl<CPDObjectFill>,
	public CNotifyGetImpl<CPDObjectFill>,
	public CNotifySendImpl<CPDObjectFill>
{
public:
	CPDObjectFill()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	virtual void CalculateBounds();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDObjectFill, IPDObjectWithAppearance>::Render(pRenderer, pGraphics, scaleX, scaleY);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTFILL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectFill)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectFill)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDObjectWithBrush)
	COM_INTERFACE_ENTRY(IPDOpacityAndBlendMode)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDFill
public:
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
// IPDObject
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		*pVal = PATH_FILL;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};

#endif //__PDFILL_H_
