#ifndef Web_PSVGLineElement_h
#define Web_PSVGLineElement_h

namespace System
{
namespace Web
{

class PSVGLineElement :
	public PSVGShapeElement
	//public PSVGBasicShape
{
public:
	CTOR PSVGLineElement(SVGLineElement* element);

	void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);

protected:

	double m_computedX1;
	double m_computedY1;
	double m_computedX2;
	double m_computedY2;
};

}	// Web
}	// System

#endif // Web_PSVGLineElement_h
