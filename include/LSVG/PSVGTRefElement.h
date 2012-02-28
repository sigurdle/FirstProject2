#ifndef w3c_PSVGTRefElement_h
#define w3c_PSVGTRefElement_h

#include "PSVGTextPositioningElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGTRefElement : public PSVGTextPositioningElement
{
public:
	CTOR PSVGTRefElement(SVGTRefElement* element);

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual void CalculateDimensions(CHTMCalcContext* pC);
};

}	// Web
}

#endif // w3c_PSVGTRefElement_h
