#ifndef Web_PSVGGlyphElement_h
#define Web_PSVGGlyphElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGGlyphElement : public PSVGElement
{
public:
	CTOR PSVGGlyphElement(SVGGlyphElement* element);

//	double m_computedX;
//	double m_computedY;
//	double m_computedWidth;	// Defined as CSS properties ??
//	double m_computedHeight;

//	virtual RectD GetViewBox();

	void CalculateBounds();

	virtual void RecalculateParentBounds()
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();
		CalculateBounds();
	}

#if 0
	virtual void DistributeWithinBlock(CHTMFlowBlockContext* pC, double parentwidth);
	virtual void Render4(CHTMRenderContext* pC, LDraw::Bitmap* pBitmap, UI::Graphics* pGraphics, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
#endif
};

}	// Web
}

#endif // Web_PSVGGlyphElement_h
