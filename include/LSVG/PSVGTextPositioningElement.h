#ifndef Web_PSVGTextPositioningElement_h
#define Web_PSVGTextPositioningElement_h

#include "PSVGTextContentElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGTextPositioningElement : public PSVGTextContentElement
{
public:
	CTOR PSVGTextPositioningElement(SVGTextPositioningElementImpl* element) : PSVGTextContentElement(element)
	{
	}

//	virtual void LayoutText(CTextLayoutContext* tlc, bool bDoX, bool bDoY);
};

}	// Web
}	// System

#endif // Web_PSVGTextPositioningElement_h
