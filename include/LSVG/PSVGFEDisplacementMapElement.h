#ifndef Web_PSVGFEDisplacementMapElement_h
#define Web_PSVGFEDisplacementMapElement_h

#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFEDisplacementMapElement : public PSVGFEElement
{
public:
	CTOR PSVGFEDisplacementMapElement(SVGFEDisplacementMapElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEDisplacementMapElement_h
