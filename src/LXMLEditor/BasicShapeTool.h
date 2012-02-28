#pragma once

#include "resource.h"

namespace System
{
namespace LXmlEdit
{

class CBasicShapeToolPlugin;

class CBasicShapeTool : 
	public ISVGTool
{
public:
	CBasicShapeTool();
	~CBasicShapeTool();

	CBasicShapeToolPlugin* m_pAddin;

	UINT m_nTool;

	int m_dragging;
//	Gdiplus::Point m_startpt;
	LDraw::PointD m_wstartpt;
	LDraw::PointD m_woldpt;
	LDraw::PointD m_wpt;

	LDraw::RectD m_newObjectBounds;

// Rectangular Grid Tool
	int m_rectgridHorzDivs;
	int m_rectgridVertDivs;
	double m_rectgridHorzSkew;
	double m_rectgridVertSkew;
	bool m_outsideAsRect;

// Polar grid Tool
	int m_polargridConcentricDivs;
	int m_polargridRadialDivs;
	double m_polargridConcentricSkew;
	double m_polargridRadialSkew;

// Foreign Object tool
	CESVGElementImpl* m_elementToPlace;

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

}	// LXmlEdit
}
