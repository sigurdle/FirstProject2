#ifndef w3c_PSVGPolygonElement_h
#define w3c_PSVGPolygonElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGPolygonElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGPolygonElement(SVGPolygonElement* element);

	virtual void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix() const;

	virtual gm::RectD GetScreenBBox();
	/*
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	*/

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);
};

}	// w3c
}

#endif // w3c_PSVGPolygonElement_h
