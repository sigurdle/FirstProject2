// PDRenderer.h : Declaration of the CPDRenderer

#ifndef __PDRENDERER_H_
#define __PDRENDERER_H_

#include "resource.h"       // main symbols

template<class T> class CPDSpreadImpl;

/////////////////////////////////////////////////////////////////////////////
// CPDRenderer
class ATL_NO_VTABLE CPDRenderer : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDRenderer, &CLSID_PDRenderer>,
	public IDispatchImpl<IPDRenderer, &IID_IPDRenderer, &LIBID_PAGEDESIGNERLib>
{
public:
	CPDRenderer()
	{
		m_pGraphics = NULL;
		m_magnify = 1.0;
	}

	~CPDRenderer()
	{
	//	delete m_pGraphics;
	}

	CComPtr<IPDCustomRenderer> m_customRenderer;

	Gdiplus::Graphics* m_pGraphics;
	double m_magnify;

	void RenderDocumentGrid(CPDSpreadImpl<IPDSpread>* spread, double left, double top, double width, double height);
	void RenderGuides(CPDSpreadImpl<IPDSpread>* spread, double left, double top, double width, double height);

DECLARE_REGISTRY_RESOURCEID(IDR_PDRENDERER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDRenderer)
	COM_INTERFACE_ENTRY(IPDRenderer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IPDRenderer
public:
	STDMETHOD(RenderObject)(/*[in]*/ IPDObject* object);
	STDMETHOD(AddCustomRenderer)(/*[in]*/ IPDCustomRenderer* customRenderer);
	STDMETHOD(RenderSpreadBackground)(/*[in]*/ IPDSpread* ispread);
	STDMETHOD(get_magnify)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_magnify)(/*[in]*/ double newVal);
	STDMETHOD(RenderGuide)(/*[in]*/ IPDSpread* spread, /*[in]*/ IPDGuide* guide, DWORD color, double left, double top, double width, double height);
	STDMETHOD(RenderSpread)(/*[in]*/ IPDSpread* spread, double left, double top, double width, double height);
	STDMETHOD(get_targetHDC)(/*[out, retval]*/ HDC *pVal);
	STDMETHOD(put_targetHDC)(/*[in]*/ HDC newVal);
};

#endif //__PDRENDERER_H_
