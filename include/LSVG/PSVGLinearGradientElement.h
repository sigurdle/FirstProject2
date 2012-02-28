#ifndef Web_PSVGLinearGradientElement_h
#define Web_PSVGLinearGradientElement_h

#include "PSVGGradientElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGLinearGradientElement : public PSVGGradientElement
{
public:
	CTOR PSVGLinearGradientElement(SVGLinearGradientElement* element);

	virtual Gui::Brush* CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY);
};

}	// Web
}

#endif // Web_PSVGLinearGradientElement_h
