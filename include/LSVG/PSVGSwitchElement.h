#ifndef w3c_PSVGSwitchElement_h
#define w3c_PSVGSwitchElement_h

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGSwitchElement : public PSVGTransformableElement
{
public:
	CTOR PSVGSwitchElement(SVGSwitchElement* element);

//	void SelectElement();

	virtual void CalculateBounds();

	virtual gm::RectD GetScreenBBox();

	virtual bool NeedOffscreenBitmap();

	virtual void RecalculateParentBounds()
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	/*
	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}
	*/

	virtual PSVGElement* HitTestElement(gm::Matrix3d* matrix, gm::PointD pt);

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
//	virtual LDraw::Matrix3d* GetLocalAnimatedMatrix();

public:

	PSVGElement* m_pSelectedElement;
};

}	// w3c
}

#endif // w3c_PSVGSwitchElement_h
