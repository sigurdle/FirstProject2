#pragma once

#include "PSVGElement.h"

namespace System
{
namespace Web
{

class CPSVGFlowRegionElement :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public PSVGElement
{
public:
	CPSVGFlowRegionElement(SVGElement* element) : PSVGElement(element)
	{
	}

	void CalculateBounds();

	virtual gm::RectD GetScreenBBox();

	virtual bool NeedOffscreenBitmap();

	virtual void RecalculateParentBounds()	// Called by a child that has changed
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren()	// Called by parent
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
	virtual gm::Matrix3d* GetLocalAnimatedMatrix();
};

}	// Web
}	// System
