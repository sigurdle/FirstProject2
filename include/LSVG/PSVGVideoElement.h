#ifndef Web_PSVGVideoElement_h
#define Web_PSVGVideoElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGVideoElement : public PSVGElement
{
public:
	CTOR PSVGVideoElement(SVGVideoElement* element);

	void CalculateBounds();

	virtual gm::Matrix3d* GetLocalAnimatedMatrix();
	virtual gm::RectD GetScreenBBox();

	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);

protected:

	double m_computedX;
	double m_computedY;
	double m_computedWidth;
	double m_computedHeight;
};

}	// Web
}	// System

#endif // Web_PSVGVideoElement_h
