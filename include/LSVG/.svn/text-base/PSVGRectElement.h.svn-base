#ifndef Web_PSVGRectElement_h
#define Web_PSVGRectElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGRectElement :
	public PSVGShapeElement
{
public:
	CTOR PSVGRectElement(SVGRectElement* element);
	~PSVGRectElement();

	virtual void CalculateBounds();

//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();
	/*
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}
	*/

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
//	virtual void RenderPath(LDraw::GraphicsPathF* pGraphicsPathF);
	virtual bool HitTest(double x, double y, int pointerEvents);

	//LDraw::GraphicsPathF* m_pGdipGraphicsPathF;	// Cached GraphicsPathF
	Gui::Geometry* m_pGdipGraphicsPathF;

	double m_computedX;
	double m_computedY;
	double m_computedWidth;
	double m_computedHeight;
	double m_computedRx;
	double m_computedRy;
};

}	// Web
}	// System

#endif // Web_PSVGRectElement_h
