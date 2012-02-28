// PDStroke.h : Declaration of the CPDObjectStroke

#ifndef __PDSTROKE_H_
#define __PDSTROKE_H_

#include "resource.h"       // main symbols

//#include "PDObjectImpl.h"
#include "PDOpacityAndBlendModeImpl.h"
#include "PDObjectWithBrushImpl.h"
//#include "PDObjectWithAppearanceImpl.h"

#include "PDStrokeSettingsImpl.h"

//class CPDObjectFrame;
//class CPDBrush;


/////////////////////////////////////////////////////////////////////////////
// CPDObjectStroke
class ATL_NO_VTABLE CPDObjectStroke : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDObjectStroke, &CLSID_PDObjectStroke>,
	public CPDObjectWithBrushImpl<CPDObjectStroke, IPDObjectStroke>,
	public CPDOpacityAndBlendModeImpl<CPDObjectStroke>,
	public CPDStrokeSettingsImpl<CPDObjectStroke>,
	public CNotifyGetImpl<CPDObjectStroke>,
	public CNotifySendImpl<CPDObjectStroke>
{
public:
	CPDObjectStroke()
	{
		/*
		m_strokeWeight = 1.0;
		m_strokeCap = 0;
		m_strokeJoin = 0;
		m_strokeMiterLimit = 4;

		m_dashValues[0] = 0;
		m_dashValues[1] = 0;
		m_dashValues[2] = 0;
		m_dashValues[3] = 0;
		m_dashValues[4] = 0;
		m_dashValues[5] = 0;
		*/
	}

	int FinalConstruct();
	void FinalRelease();

	/*
	double m_strokeWeight;
	long m_strokeCap;
	long m_strokeJoin;
	double m_strokeMiterLimit;

	double m_dashValues[6];
*/
	Gdiplus::Pen* GetGdipPen();

	RectD m_bounds;

	virtual void CalculateBounds();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
	{
		CPDObjectWithAppearanceImpl<CPDObjectStroke, IPDObjectWithAppearance>::Render(pRenderer, pGraphics, scaleX, scaleY);
	}

	STDMETHODIMP FireOnChanged(NotifyType type, IUnknown* targetObject, DISPID dispID)
	{
//		CalculateBounds();
		return CNotifySendImpl<CPDObjectStroke>::FireOnChanged(type, targetObject, dispID);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PDOBJECTSTROKE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDObjectStroke)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectStroke)
	COM_INTERFACE_ENTRY(IPDStrokeSettings)
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

// IPDStroke
public:
#if 0
	STDMETHOD(get_strokeMiterLimit)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_strokeMiterLimit)(/*[in]*/ double newVal);
	STDMETHOD(get_strokeJoin)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_strokeJoin)(/*[in]*/ long newVal);
	STDMETHOD(get_strokeCap)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_strokeCap)(/*[in]*/ long newVal);
	STDMETHOD(get_dashedCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(getDashedValue)(/*[in]*/ long index, /*[out,retval]*/ double* pVal);
	STDMETHOD(setDashedValue)(/*[in]*/ long index, /*[in]*/ double value);
	STDMETHOD(get_strokeWeight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_strokeWeight)(/*[in]*/ double newVal);
#endif
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY);
// IPDObject
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		*pVal = PATH_STROKE;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);
};

#endif //__PDSTROKE_H_
