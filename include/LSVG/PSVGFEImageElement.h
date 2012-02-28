#ifndef Web_PSVGFEImageElement_h
#define Web_PSVGFEImageElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFEImageElement : public PSVGFEElement
{
public:
	CTOR PSVGFEImageElement(SVGFEImageElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEImageElement_h
