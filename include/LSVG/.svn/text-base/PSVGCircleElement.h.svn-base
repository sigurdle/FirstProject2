#ifndef Web_PSVGCircleElement_h
#define Web_PSVGCircleElement_h

//#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGCircleElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGCircleElement(SVGCircleElement* element);

	void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();

	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual void RenderPath(Gui::Geometry* pGraphicsPathF);
	virtual bool HitTest(double x, double y, int pointerEvents);

public:

	double m_computedCx;
	double m_computedCy;
	double m_computedR;
};

}	// Web
}

#endif // Web_PSVGCircleElement_h
