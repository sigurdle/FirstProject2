#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGUseElement :
	public CESVGElementImpl,
	public IESVGDrawOutline
{
public:
	CTOR CESVGUseElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);
	ErrorCode Resize(ISVGView* view, double x, double y, double width, double height);
	long GetResizability(/*[out,retval]*/ long* pVal)
	{
		return 1;
	}
// IESVGDrawOutline
	ErrorCode DrawOutline(UI::Graphics* pGraphics, LDraw::Color& color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
