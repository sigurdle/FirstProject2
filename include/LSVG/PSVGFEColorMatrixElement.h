#ifndef w3c_PSVGFEColorMatrixElement_h
#define w3c_PSVGFEColorMatrixElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFEColorMatrixElement : public PSVGFEElement
{
public:
	CTOR PSVGFEColorMatrixElement(SVGFEColorMatrixElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// w3c
}

#endif // w3c_PSVGFEColorMatrixElement_h
