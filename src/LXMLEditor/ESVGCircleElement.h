#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGCircleElement :
	public CESVGElementImpl,
	public IESVGSimpleShapeElement
{
public:
	CTOR CESVGCircleElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);
	long GetResizability()
	{
		return 2;	// Proportional only
	}
//	virtual void Scale(double cx, double cy, double sx, double sy);
//	virtual void DrawPathCurve(HDC hDC, ILSVGMatrix* addmatrix);
	ErrorCode SetShape(/*[in]*/ double cx, /*[in]*/ double cy, /*[in]*/ double r);

// IESVGSimpleShapeElement
	ErrorCode DrawPathSegList(Web::SVGPathElement* pathElement, Web::SVGPathSegList* seglist);
};

}	// LXmlEdit
}
