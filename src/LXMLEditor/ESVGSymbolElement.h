#pragma once

#include "ESVGElementImpl.h"

namespace System
{
namespace LXmlEdit
{

class CESVGSymbolElement :
	public CESVGElementImpl,
	public IESVGDrawOutline
{
public:
	CESVGSymbolElement()
	{
	}

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
