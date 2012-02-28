#ifndef w3c_PSVGSolidColorElement_h
#define w3c_PSVGSolidColorElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGSolidColorElement : public PSVGElement
{
public:
	CTOR PSVGSolidColorElement(SVGElement* element);

	virtual LDraw::Brush* CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY);

};

}	// w3c
}

#endif // w3c_PSVGSolidColorElement_h
