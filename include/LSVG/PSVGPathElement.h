#ifndef Web_PSVGPathElement_h
#define Web_PSVGPathElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGPathElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGPathElement(SVGPathElement* element);
	~PSVGPathElement();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	void CalculateBounds();

	virtual gm::RectD GetScreenBBox();
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	virtual void RecalculateParentBounds();

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors) override;
	virtual void RenderPath(Gui::Geometry* pGraphicsPathF);
	virtual bool HitTest(double x, double y, int pointerEvents) override;

	Gui::Geometry* m_pGdipGraphicsPathF;	// Cached GraphicsPathF
};

}	// Web
}	// System

#endif // Web_PSVGPathElement_h
