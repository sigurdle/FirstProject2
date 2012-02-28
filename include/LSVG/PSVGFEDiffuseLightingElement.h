#ifndef w3c_PSVGFEDiffuseLightingElement_h
#define w3c_PSVGFEDiffuseLightingElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFEDiffuseLightingElement : public PSVGFEElement
{
public:
	CTOR PSVGFEDiffuseLightingElement(SVGFEDiffuseLightingElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// w3c
}

#endif // w3c_PSVGFEDiffuseLightingElement_h
