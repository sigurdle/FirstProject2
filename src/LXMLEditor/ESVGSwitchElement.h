#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGSwitchElement :
	public CESVGElementImpl,
	public IESVGDrawOutline
{
public:
	CESVGSwitchElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);

// IESVGDrawOutline
ErrorCode DrawOutline(UI::Graphics* pGraphics, LDraw::Color& color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
