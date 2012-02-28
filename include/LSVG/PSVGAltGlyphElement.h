#ifndef Web_PSVGAltGlyphElement_h
#define Web_PSVGAltGlyphElement_h

#include "PSVGTextPositioningElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGAltGlyphElement : public PSVGTextPositioningElement
{
public:
	CTOR PSVGAltGlyphElement(SVGAltGlyphElement* element);

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual void CalculateDimensions(CHTMCalcContext* pC);
};

}	// Web
}

#endif // Web_PSVGAltGlyphElement_h
