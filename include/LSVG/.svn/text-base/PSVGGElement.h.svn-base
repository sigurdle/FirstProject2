#ifndef Web_PSVGGElement_h
#define Web_PSVGGElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGGElement : public PSVGTransformableElement
{
public:
	CTOR PSVGGElement(SVGGElement* element);

	virtual void CalculateBounds();
	virtual gm::RectD GetScreenBBox();
	virtual bool NeedOffscreenBitmap();

	virtual void RecalculateParentBounds()	// Called by a child that has changed
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren()	// Called by parent
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors) override;
	//virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();
};

}	// Web
}	// System

#endif // Web_PSVGGElement_h
