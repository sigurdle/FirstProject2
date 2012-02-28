#ifndef Web_PSVGPolylineElement_h
#define Web_PSVGPolylineElement_h

namespace System
{
namespace Web
{

class PSVGPolylineElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGPolylineElement(SVGPolylineElement* element);

	void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);

};

}	// Web
}	// System

#endif // Web_PSVGPolylineElement_h
