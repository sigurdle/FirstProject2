#pragma once

#include "resource.h"

namespace System
{
namespace LXmlEdit
{

class CESelectedSVGPathElement;

class CPathEditTool : 
	public UI::ProcessTargetCommands,	// ILDOMEventListener
	public ISVGTool
{
public:
	CPathEditTool()
	{
		m_nTool = 0;
		m_dragging = 0;

		m_pActivePath = NULL;

		m_curveDir = 0;

		m_segType = ID_SEGTYPE_CUBICBEZIER;
	}

	~CPathEditTool()
	{
	}

	int m_nTool;

	int m_dragging;
	long m_curveCp;
	long m_curveCtl;
	long m_curveDir;
	//_SVGHitData m_hitdata;

	int m_segType;

	LDraw::PointD m_woldpt;
	LDraw::PointD m_wstartpt;

	double m_lastx;
	double m_lasty;
	double m_x;
	double m_y;
	double m_x1;
	double m_y1;
	double m_x2;
	double m_y2;
	double m_x3;
	double m_y3;

	Array<LDraw::PointD> m_points;

	UI::Toolbar* m_dlg;

	//CComQIPtr<IESVGElement> m_pActivePath;
	CESelectedSVGPathElement* m_pActivePath;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathEditTool)
	COM_INTERFACE_ENTRY(ISVGTool)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
END_COM_MAP()
*/

DECLARE_CMD_MAP(CPathEditTool)

long OnSegType(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

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

#if 0
class ATL_NO_VTABLE CPathEditPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CPathEditPlugin, &CLSID_PathEditPlugin>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CPathEditPlugin()
	{
	}

	~CPathEditPlugin()
	{
	}

	CComPtr<ILXMLEditorPluginClass> m_spAddinSite;

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_PATHEDITPLUGIN)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPathEditPlugin)
	COM_INTERFACE_ENTRY(ILXMLEditorPlugin)
	COM_INTERFACE_ENTRY(ISVGToolFactory)
END_COM_MAP()
*/
public:

	ErrorCode(GetSite)(ILXMLEditorPluginClass* *pVal)
	{
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	ErrorCode(SetSite)(ILXMLEditorPluginClass* pSite);

//	ErrorCode Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	ErrorCode Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	ErrorCode FindTool(/*[in]*/ long id, IUnknown* *dlg, /*[out,retval]*/ ISVGTool** pVal);
};
#endif

}	// LXmlEdit
}
