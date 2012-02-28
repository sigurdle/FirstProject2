#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGPolyElement :
	public CESVGElementImpl,
	public IESVGSimpleShapeElement,
	public IESVGDrawOutline
{
public:
	CESVGPolyElement()
	{
	}

	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, /*long tool,*/ _SVGHitData* hit);
	ErrorCode HitTest(Web::SVGPointList* points, ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, _SVGHitData* hit);

	ErrorCode CreateSelectedElement(CEXMLViewGroup* viewGroup, IESelectedElement* *pVal);

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(LDraw::Graphics* pGraphics, Web::SVGMatrix* addmatrix);

	ErrorCode get_pointCount(/*[out,retval]*/ long *pVal);
	ErrorCode IsClosed(/*[out,retval]*/ bool* pVal);
	ErrorCode SetClosed(/*[in]*/ bool bClosed, Element* *pVal);

// IESVGDrawOutline
	ErrorCode DrawOutline(Web::SVGPointList* points, UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

// IESVGSimpleShapeElement
	ErrorCode DrawPathSegList(/*[in]*/ Web::SVGPathElement* pathElement, /*[in]*/ Web::SVGPathSegList* seglist);
};

}	// LXmlEdit
}
