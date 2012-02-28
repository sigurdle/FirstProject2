#ifndef Web_PSVGClipPathElement_h
#define Web_PSVGClipPathElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGClipPathElement : public PSVGElement
{
public:
	CTOR PSVGClipPathElement(SVGClipPathElement* element);

//	void Mask(PSVGElement* pReferencingElement, Gdiplus::Bitmap* pBitmap, Gdiplus::RectF filterRect, double scaleX, double scaleY);
//	Gdiplus::Bitmap* GetOpacityMaskBitmap(Gdiplus::RectF filterRect, double scaleX, double scaleY);

//	RectD CalculateMaskRegion(PSVGElement* pReferencingElement);

	virtual void CalculateBounds();

	virtual void RecalculateParentBounds();

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

//	virtual void Render2(/*[in]*/ DWORD dwBitmap, DWORD dwGraphics, double scaleX, double scaleY);
};

}	// Web
}

#endif // Web_PSVGClipPathElement_h
