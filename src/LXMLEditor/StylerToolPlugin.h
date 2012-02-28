// StylerToolPlugin.h : Declaration of the CStylerToolPlugin

#ifndef __STYLERTOOLPLUGIN_H_
#define __STYLERTOOLPLUGIN_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CStylerToolPlugin;

class CStylerTool : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public ISVGTool
{
public:
	CStylerTool();
	~CStylerTool();

	CStylerToolPlugin* m_pAddin;

	int m_nTool;
	int m_dragging;
	int m_hit;

	LDraw::PointI m_startpt;
	LDraw::PointI m_oldpt;
	LDraw::PointD m_wstartpt;
	LDraw::PointD m_woldpt;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStylerTool)
	COM_INTERFACE_ENTRY(ISVGTool)
END_COM_MAP()
*/

public:
	ErrorCode Options(UI::Control* hParent);
	ErrorCode OnDeactivate(ILXMLEditorApp* app);
	ErrorCode OnActivate(ILXMLEditorApp* app);
	ErrorCode Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics);

	ErrorCode OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging);
	ErrorCode OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
};

/////////////////////////////////////////////////////////////////////////////
// CStylerToolPlugin
class CStylerToolPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CStylerToolPlugin, &CLSID_StylerToolPlugin>,
//	public IDispatchImpl<IStylerToolPlugin, &IID_IStylerToolPlugin, &LIBID_LXMLEDITORLib>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CStylerToolPlugin()
	{
	}

	/*
	int FinalConstruct()
	{
		HRESULT hr;

		return 0;
	}

	void FinalRelease()
	{
	}
	*/

	ILXMLEditorPluginClass* m_spAddinSite;

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_STYLERTOOLPLUGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStylerToolPlugin)
//	COM_INTERFACE_ENTRY(IStylerToolPlugin)
//	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILXMLEditorPlugin)
	COM_INTERFACE_ENTRY(ISVGToolFactory)
END_COM_MAP()
*/

// IStylerToolPlugin
public:
	ILXMLEditorPluginClass* GetSite()
	{
		return m_spAddinSite;
	}
	ErrorCode SetSite(ILXMLEditorPluginClass* pSite);

//	STDMETHODIMP Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	STDMETHODIMP Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	ErrorCode FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal);
};

}	// LXmlEdit
}

#endif //__StylerToolPlugin_H_
