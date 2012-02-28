#ifndef Web_PSVGForeignObjectElement_h
#define Web_PSVGForeignObjectElement_h

//#include "PSVGElement.h"

namespace System
{
namespace Web
{
//class CHTMBlockBox;

class PSVGForeignObjectElement : public PSVGTransformableElement
{
public:
	CTOR PSVGForeignObjectElement(SVGForeignObjectElement* element);

	//virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

	virtual void CalculateBounds();
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	//	PSVGElement::CalculateBoundsAndChildren();
	}
	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual bool HitTest(double x, double y, int pointerEvents);
	virtual bool HitText(gm::matrix3d* matrix, gm::PointD pt, PNode** ppNode, long* poffset);

	virtual gm::RectD GetScreenBBox()
	{
		gm::RectD bbox;
		PSVGElement::GetScreenBBoxFromBounds(m_bounds, &bbox);

		return bbox;
	}

	bool OnButtonDown(gm::PointI point, PElementBase* *pVal);

public:

	double m_computedX;
	double m_computedY;
//	double m_computedWidth;	// Defined in CSS properties ?
//	double m_computedHeight;
};

}	// Web
}

#endif // Web_PSVGForeignObjectElement_h
