#ifndef Web_PSVGMaskElement_h
#define Web_PSVGMaskElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class PSVGMaskElement : public PSVGElement
{
public:
	CTOR PSVGMaskElement(SVGMaskElement* element);

	void Mask(PSVGElement* pReferencingElement, Graphics::Bitmap* pBitmap, gm::RectF filterRect, double scaleX, double scaleY);
	Graphics::Bitmap* GetOpacityMaskBitmap(gm::RectF filterRect, double scaleX, double scaleY);

	gm::RectD CalculateMaskRegion(PSVGElement* pReferencingElement);

	void CalculateBounds();

	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
};

}	// LSVG
}

#endif // Web_PSVGMaskElement_h
