#ifndef w3c_PSVGFECompositeElement_h
#define w3c_PSVGFECompositeElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFECompositeElement : public PSVGFEElement
{
public:
	CTOR PSVGFECompositeElement(SVGFECompositeElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // w3c_PSVGFECompositeElement_h
