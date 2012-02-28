#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGGElement :
	public CESVGElementImpl,
	public IESVGDrawOutline
{
public:
	CTOR CESVGGElement()
	{
	}

	ErrorCode Move(ISVGView* view, double dx, double dy);

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
