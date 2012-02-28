#ifndef Web_PSVGImageElement_h
#define Web_PSVGImageElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGImageElement : public PSVGTransformableElement
{
public:
	CTOR PSVGImageElement(SVGImageElement* element);

	virtual Graphics::Bitmap* GetBitmap(Gui::RenderContext* renderContext, int m_scaledWidth, int m_scaledHeight, double m_scaleX, double m_scaleY);

	void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();

	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);

public:

	double m_computedX;
	double m_computedY;
	double m_computedWidth;
	double m_computedHeight;
};

}	// Web
}	// System

#endif // Web_PSVGImageElement_h
