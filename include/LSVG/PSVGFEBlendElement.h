#ifndef Web_PSVGFEBlendElement_h
#define Web_PSVGFEBlendElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGBlendEffect : public Gui::CEffect
{
public:
	CTOR SVGBlendEffect();

	virtual unsigned int GetInputCount();
	virtual CEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, CEffect* input);
	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	Gui::CEffect* m_input[2];
};

class SVGEXT PSVGFEBlendElement : public PSVGFEElement
{
public:
	CTOR PSVGFEBlendElement(SVGFEBlendElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFEBlendElement_h
