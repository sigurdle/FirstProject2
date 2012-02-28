#ifndef w3c_PSVGTextElement_h
#define w3c_PSVGTextElement_h

#include "PSVGTextPositioningElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGTextElement : public PSVGTextPositioningElement
{
public:
	CTOR PSVGTextElement(SVGTextElement* element);

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();

	virtual void CalculateBounds() override;

	virtual void RecalculateParentBounds() override
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren() override
	{
		// NOTE: Not calling this: PSVGElement::CalculateBoundsAndChildren();	// Calculate children first

		CalculateBounds();	// Will layout all the text 
	}

	virtual bool HitTest(double x, double y, long pointerEvents);
	virtual bool HitText(gm::matrix3d matrix, gm::PointD pt, PNode** ppNode, long* poffset) override;
};

}	// Web
}	// System

#endif // Web_PSVGTextElement_h
