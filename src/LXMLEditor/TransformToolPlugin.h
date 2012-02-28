#ifndef __TRANSFORMTOOLPLUGIN_H_
#define __TRANSFORMTOOLPLUGIN_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CTransformTool : 
	public ISVGTool
{
public:
	CTransformTool()
	{
		m_nTool = 0;
		m_startDragCursor = NULL;
		m_dragging = 0;
	}

	~CTransformTool()
	{
	}

	int m_nTool;
	int m_hit;

	long m_dragging;

	MSWindows::HCURSOR m_startDragCursor;

//	LDraw::PointD m_wstartpt;
	LDraw::PointD m_startpt;
	LDraw::PointD m_oldpt;

	LDraw::PointD m_offsetPt;
	LDraw::PointD m_pivotPt;

	LDraw::RectD m_objectsBoundingBox;

	Web::SVGMatrix* m_freeTransformMatrix;

	Array<Web::SVGMatrix*> m_initialMatrix;
//	CArray<ILSVGMatrix*,ILSVGMatrix*> m_currentMatrix;

	Array<Web::SVGTransform*> m_currentTransform;
	Array<IESelectedElement*> m_element;

	void CalculateObjectsBoundingBox(ISVGView* view);

	Web::SVGTransform* GetMatrixTransform(Web::SVGSVGElement* svgsvgElement, Web::ISVGTransformable* transformable);
	Web::SVGTransform* GetMatrixTransform(Web::SVGSVGElement* svgsvgElement, Web::SVGTransformList* basetransformlist);

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

class CTransformToolPlugin : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CTransformToolPlugin, &CLSID_TransformToolPlugin>,

	public ILXMLEditorPlugin,
	public ISVGToolFactory
{
public:
	CTOR CTransformToolPlugin()
	{
	}

	ILXMLEditorPluginClass * m_spAddinSite;

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

#endif //__TRANSFORMTOOLPLUGIN_H_
