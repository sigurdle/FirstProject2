#ifndef Web_PSVGFEOffsetElement_h
#define Web_PSVGFEOffsetElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFEOffsetElement : public PSVGFEElement
{
public:
	CTOR PSVGFEOffsetElement(SVGFEOffsetElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}

#endif // Web_PSVGFEOffsetElement_h
