#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGLineElement :
	public CESVGElementImpl,
	public IESVGSimpleShapeElement,
	public IESVGDrawOutline
{
public:
	CTOR CESVGLineElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(HDC hDC, Web::SVGMatrix* addmatrix);

	ErrorCode(SetShape)(double x1, double y1, double x2, double y2);

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

// IESVGSimpleShapeElement
	ErrorCode DrawPathSegList(Web::SVGPathElement* pathElement, Web::SVGPathSegList* seglist);
};

}	// LXmlEdit
}
