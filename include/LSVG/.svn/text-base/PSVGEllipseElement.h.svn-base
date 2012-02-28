#ifndef Web_PSVGEllipseElement_h
#define Web_PSVGEllipseElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGEllipseElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGEllipseElement(SVGEllipseElement* element);
	~PSVGEllipseElement();

	virtual void CalculateBounds();

//	LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();
	/*
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	*/

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual void RenderPath(Gui::Geometry* pGraphicsPathF);

	virtual bool HitTest(double x, double y, int pointerEvents);

public:

	double m_computedCx;
	double m_computedCy;
	double m_computedRx;
	double m_computedRy;
};

}	// Web
}	// System

#endif // Web_PSVGEllipseElement_h
