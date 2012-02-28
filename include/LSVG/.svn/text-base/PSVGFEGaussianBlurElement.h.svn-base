#ifndef Web_PSVGFEGaussianBlurElement_h
#define Web_PSVGFEGaussianBlurElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFEGaussianBlurElement : public PSVGFEElement
{
public:
	CTOR PSVGFEGaussianBlurElement(SVGFEGaussianBlurElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEGaussianBlurElement_h
