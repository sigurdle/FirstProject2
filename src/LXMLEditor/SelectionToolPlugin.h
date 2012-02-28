// SelectionToolPlugin.h : Declaration of the CSelectionToolPlugin

#ifndef __SELECTIONTOOLPLUGIN_H_
#define __SELECTIONTOOLPLUGIN_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSelectionTool : 
	public ISVGTool
{
public:
	CSelectionTool()
	{
		m_nTool = 0;
		m_dragging = 0;
		m_hit = 0;
	}

	~CSelectionTool()
	{
	}

	int m_nTool;
	int m_dragging;
	int m_hit;

	int HitTestActiveElement(ISVGView* view, SVGMouse* mouse, IESelectedElement* *pVal);

	Web::SVGMatrix* m_xmat;

	LDraw::PointD m_wstartpt;
	LDraw::PointD m_woldpt;

//	LDraw::PointD m_doldpt;

	LDraw::PointD m_startpt;
	LDraw::PointD m_oldpt;

	_SVGHitData m_hitdata;

// Hand tool
	double m_currentTranslateX;
	double m_currentTranslateY;

// Zoom tool
	LDraw::BBoxi m_zoomRect;
	void ZoomToRect2(ISVGView* view, double left, double top, double right, double bottom);

public:
	ErrorCode Options(UI::Control* hParent);
	ErrorCode OnDeactivate(ILXMLEditorApp* app);
	ErrorCode OnActivate(ILXMLEditorApp* app);
	ErrorCode Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, /*[in]*/ MSWindows::HDC hDC);

	ErrorCode OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging);
	ErrorCode OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
	ErrorCode OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse);
};

#if 0
/////////////////////////////////////////////////////////////////////////////
// CSelectionToolPlugin
class ATL_NO_VTABLE CSelectionToolPlugin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSelectionToolPlugin, &CLSID_SelectionToolPlugin>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CSelectionToolPlugin()
	{
	}

	CComPtr<ILXMLEditorPluginClass> m_spAddinSite;

DECLARE_REGISTRY_RESOURCEID(IDR_SELECTIONTOOLPLUGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSelectionToolPlugin)
//	COM_INTERFACE_ENTRY(ISelectionToolPlugin)
	COM_INTERFACE_ENTRY(ILXMLEditorPlugin)
	COM_INTERFACE_ENTRY(ISVGToolFactory)
END_COM_MAP()

// ISelectionToolPlugin
public:
//	ErrorCode Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	ErrorCode Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	ErrorCode(GetSite)(ILXMLEditorPluginClass* *pVal)
	{
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	ErrorCode(SetSite)(ILXMLEditorPluginClass* pSite);
	ErrorCode FindTool(/*[in]*/ long id, IUnknown* *pdlg, /*[out,retval]*/ ISVGTool** pVal);
};
#endif

}	// LXmlEdit
}

#endif //__SELECTIONTOOLPLUGIN_H_
