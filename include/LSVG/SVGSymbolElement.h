#ifndef w3c_SVGSymbolElement_h
#define w3c_SVGSymbolElement_h

#include "SVGFitToViewBoxImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGSymbolElement : 

	public SVGElement,
	public SVGStylableImpl<SVGSymbolElement>,
//	public SVGFitToViewBoxImpl,//<SVGSymbolElement, ISVGFitToViewBox>,
//	public ElementEditASImpl<SVGSymbolElement>,
	public ElementEditVALImpl<SVGSymbolElement>,
	public SMILAnimationTargetImpl<SVGSymbolElement>,

	public ISVGFitToViewBox
//	public IElementEditVAL,	// INodeEditVAL
{
public:

	class SVGEXT PSVGSymbolElement : public PSVGElement
	{
	public:
		CTOR PSVGSymbolElement(SVGSymbolElement* element) : PSVGElement(element)
		{
		}

		virtual void CalculateBounds();

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

		virtual void Render4(CHTMRenderContext* pC, Graphics::Bitmap* pBitmap, Gui::RenderContext* renderContext, double scaleX, double scaleY, bool bOffscreen, bool bDrawBehaviors);

	};

	CTOR SVGSymbolElement(NamedNodeMap* attributes);

// ISVGFitToViewBox
	virtual ISVGAnimatedRect* get_viewBox()
	{
		return NULL;
//		return m_viewBox;
	}
	virtual ISVGAnimatedPreserveAspectRatio* get_preserveAspectRatio()
	{
		return NULL;
//		return m_preserveAspectRatio;
	}

	Attr* get_viewBoxAttr()
	{
		return NULL;
		//return m_viewBoxAttr;
	}

	Attr* get_preserveAspectRatioAttr()
	{
		return NULL;
		//return m_preserveAspectRatioAttr;
	}
};

}	// w3c
}

#endif // w3c_SVGSymbolElement_h
