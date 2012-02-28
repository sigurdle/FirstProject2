#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGRectElement :
	public CESVGElementImpl,
	public IESVGSimpleShapeElement
{
public:
	CTOR CESVGRectElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability()
	{
		return 1;
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix);

// IESVGRectElement
	ErrorCode SetRectShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height);
	ErrorCode SetRoundRectShape(/*[in]*/ double x, /*[in]*/ double y, /*[in]*/ double width, /*[in]*/ double height, /*[in]*/ double rx, /*[in]*/ double ry);

// IESVGSimpleShapeElement
	ErrorCode DrawPathSegList(Web::SVGPathElement* pathElement, Web::SVGPathSegList* seglist);
};

}	// LXmlEdit
}
