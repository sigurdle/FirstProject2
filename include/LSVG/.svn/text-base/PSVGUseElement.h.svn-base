#ifndef Web_PSVGUseElement_h
#define Web_PSVGUseElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGUseElement : public PSVGElement
{
public:
	CTOR PSVGUseElement(SVGUseElement* element);

	void CalculateBounds();

	virtual gm::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();
	virtual void CalculateBoundsAndChildren()
	{
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual PSVGElement* HitTestElement(gm::Matrix3d* matrix, gm::PointD pt);

	PSVGElement* m_pInstanceRoot;

	double m_computedX;
	double m_computedY;
	double m_computedWidth;
	double m_computedHeight;
};

}	// Web
}	// System

#endif // Web_PSVGUseElement_h
