#ifndef Web_PSVGFEMorphologyElement_h
#define Web_PSVGFEMorphologyElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFEMorphologyElement : public PSVGFEElement
{
public:
	CTOR PSVGFEMorphologyElement(SVGFEMorphologyElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEMorphologyElement_h
