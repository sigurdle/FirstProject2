#pragma once

#include "PSVGElement.h"

#include "PSVGTextPositioningElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGFlowTextElement : public PSVGElement
{
public:
	PSVGFlowTextElement() : PSVGElement(NULL)
	{
	}

	~PSVGFlowTextElement()
	{
	}

	void CalculateBounds();

	virtual gm::Matrix3d* GetLocalAnimatedMatrix();

	virtual gm::RectD GetScreenBBox();

	virtual void RecalculateParentBounds()	// Called by a child that has changed
	{
		CalculateBounds();
		PSVGElement::RecalculateParentBounds();
	}

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

	virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);
//	virtual void RenderPath(Gdiplus::GraphicsPath* pGraphicsPath);
	virtual bool HitTest(double x, double y, int pointerEvents);
};

class SVGEXT PSVGFlowDivElement : public PSVGTextContentElement
{
public:
	PSVGFlowDivElement() : PSVGTextContentElement(NULL)
	{
	}

//	virtual gmMatrix3 GetLocalAnimatedMatrix();

};

}	// LSVG
}
