#ifndef Web_PSVGFESpecularLightingElement_h
#define Web_PSVGFESpecularLightingElement_h

//#include "PSVGFEElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGSpecularLightingEffect : public Gui::CEffect
{
public:
	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);
	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	Gui::IEffect* m_input;

	gm::vector4f m_lightPosition;
	gm::vector4f m_lightColor;
	float m_specularConstant;
	float m_specularExponent;
	float m_surfaceScale;
};

class SVGEXT PSVGFESpecularLightingElement : public PSVGFEElement
{
public:
	CTOR PSVGFESpecularLightingElement(SVGFESpecularLightingElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGFESpecularLightingElement_h
