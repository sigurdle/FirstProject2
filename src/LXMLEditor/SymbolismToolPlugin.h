// SymbolismToolPlugin.h : Declaration of the CSymbolismToolPlugin

#ifndef __SYMBOLISMTOOLPLUGIN_H_
#define __SYMBOLISMTOOLPLUGIN_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CSymbolInstance
{
public:
	LDraw::PointD m_position;
	Web::SVGUseElement* m_element;
	Web::SVGMatrix* m_matrix;
};

class CSymbolismTool : 
	public ISVGTool
{
public:
	CSymbolismTool()
	{
		m_nTool = 0;

		m_dragging = 0;
		m_hit = 0;

		m_bBrushSizeVisible = false;
	}

	~CSymbolismTool()
	{
	}

	int m_nTool;
	int m_dragging;
	int m_hit;
	LDraw::PointD m_brushSize;

	uint m_counter;

	LDraw::PointI m_startpt;
	LDraw::PointI m_oldpt;
	LDraw::PointD m_wstartpt;
	LDraw::PointD m_woldpt;

	Array<CSymbolInstance*> m_instances;
	double m_minX;
	double m_minY;
	double m_maxX;
	double m_maxY;

	Element* m_symbolSetGElement;

	bool m_bBrushSizeVisible;

	void DrawBrushOutline(ISVGView* view, MSWindows::HDC hDC, LDraw::PointI point);
	void EraseBrushOutline(ISVGView* view);

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

class CSymbolismToolPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CSymbolismToolPlugin, &CLSID_SymbolismToolPlugin>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CSymbolismToolPlugin()
	{
	}

	ILXMLEditorPluginClass * m_spAddinSite;

public:
//	ErrorCode Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
//	ErrorCode Shutdown(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app);
	ILXMLEditorPluginClass* GetSite()
	{
		return m_spAddinSite;
	}
	ErrorCode SetSite(ILXMLEditorPluginClass* pSite);
	ErrorCode FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal);
};

}	// LXmlEdit
}

#endif //__SYMBOLISMTOOLPLUGIN_H_
