#include "stdafx.h"
#include "LSVG.h"

namespace System
{
namespace Web
{

PSVGFEMergeElement::PSVGFEMergeElement(SVGFEMergeElement* element) : PSVGFEElement(element)
{
}

//virtual
int PSVGFEMergeElement::GetInCount()
{
	return -1;
}

//virtual
Gui::CEffect* PSVGFEMergeElement::Filter(Gui::RenderTarget* rt, Gui::CEffect* inEffect[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	ASSERT(0);
	return NULL;
}

}
}
