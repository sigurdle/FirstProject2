#ifndef Web_PSVGFEComponentTransferElement_h
#define Web_PSVGFEComponentTransferElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFEComponentTransferElement : public PSVGFEElement
{
public:
	CTOR PSVGFEComponentTransferElement(SVGFEComponentTransferElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEComponentTransferElement_h
