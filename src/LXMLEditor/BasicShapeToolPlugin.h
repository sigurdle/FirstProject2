// BasicShapeToolPlugin.h : Declaration of the CBasicShapeToolPlugin

#ifndef __BASICSHAPETOOLPLUGIN_H_
#define __BASICSHAPETOOLPLUGIN_H_

#include "resource.h"       // main symbols

#if 0
/////////////////////////////////////////////////////////////////////////////
// CBasicShapeToolPlugin
class CBasicShapeToolPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CBasicShapeToolPlugin, &CLSID_BasicShapeToolPlugin>,
//	public IDispatchImpl<IBasicShapeToolPlugin, &IID_IBasicShapeToolPlugin, &LIBID_LXMLEDITORLib>

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CBasicShapeToolPlugin()
	{
	}

	CComPtr<ILXMLEditorPluginClass> m_spAddinSite;

DECLARE_REGISTRY_RESOURCEID(IDR_BASICSHAPETOOLPLUGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CBasicShapeToolPlugin)
//	COM_INTERFACE_ENTRY(IBasicShapeToolPlugin)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILXMLEditorPlugin)
	COM_INTERFACE_ENTRY(ISVGToolFactory)
END_COM_MAP()

// IBasicShapeToolPlugin
public:

	STDMETHOD(GetSite)(ILXMLEditorPluginClass* *pVal)
	{
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXMLEditorPluginClass* pSite);

//	STDMETHODIMP Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	STDMETHODIMP Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	STDMETHODIMP FindTool(/*[in]*/ long id, IUnknown* *pdlg, /*[out,retval]*/ ISVGTool** pVal);
};
#endif

#endif //__BASICSHAPETOOLPLUGIN_H_
