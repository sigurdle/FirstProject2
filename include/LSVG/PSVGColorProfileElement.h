#ifndef Web_PSVGColorProfileElement_h
#define Web_PSVGColorProfileElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGColorProfileElement : public PSVGElement
{
public:
	CTOR PSVGColorProfileElement(SVGColorProfileElement* element);

// Slight Misuse of BuildChildren method
	virtual void BuildChildren();
};

}	// Web
}

#endif // Web_PSVGColorProfileElement_h
