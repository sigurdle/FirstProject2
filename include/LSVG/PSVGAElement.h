#ifndef Web_PSVGAElement_h
#define Web_PSVGAElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGAElement : public PSVGTransformableElement
{
public:
	CTOR PSVGAElement(SVGAElement* element);

	void CalculateBounds();

	virtual void RecalculateParentBounds()
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();
};

}	// Web
}	// System

#endif // Web_PSVGAElement_h
