#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGEllipseElement :
	public CESVGElementImpl,
	public IESVGSimpleShapeElement,
	public IESVGDrawOutline
{
public:
	CTOR CESVGEllipseElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}

//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(LDraw::Graphics* pGraphics, ILSVGMatrix* addmatrix);
	ErrorCode SetShape(/*[in]*/ double cx, /*[in]*/ double cy, /*[in]*/ double rx, /*[in]*/ double ry);

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

// IESVGSimpleShapeElement
	ErrorCode DrawPathSegList(/*[in]*/ Web::SVGPathElement* pathElement, /*[in]*/ Web::SVGPathSegList* seglist);
};

}	// LXmlEdit
}
