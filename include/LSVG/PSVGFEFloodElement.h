#ifndef w3c_PSVGFEFloodElement_h
#define w3c_PSVGFEFloodElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFloodEffect : public Gui::CEffect
{
public:
	CTOR SVGFloodEffect();

	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);

	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	gm::vector4f get_Color();
	void set_Color(gm::vector4f color);

protected:

	gm::vector4f m_color;
};

class SVGEXT PSVGFEFloodElement : public PSVGFEElement
{
public:
	CTOR PSVGFEFloodElement(SVGFEFloodElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}

#endif // w3c_PSVGFEFloodElement_h
