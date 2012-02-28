#ifndef Web_PSVGRadialGradientElement_h
#define Web_PSVGRadialGradientElement_h

#include "PSVGGradientElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGRadialGradientElement : public PSVGGradientElement
{
public:
	CTOR PSVGRadialGradientElement(SVGRadialGradientElement* element);

	virtual Gui::Brush* CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGRadialGradientElement_h
