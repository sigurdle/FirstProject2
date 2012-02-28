#ifndef __Web_PSVGMarkerElement_h__
#define __Web_PSVGMarkerElement_h__

//#include "PSVGElement.h"

namespace System
{
namespace Web
{

struct MarkerVertex
{
	double x, y;
	double tangent;
};

class SVGEXT PSVGMarkerElement : public PSVGElement
{
public:
	CTOR PSVGMarkerElement(SVGMarkerElement* element);

	void DrawMarker(CHTMRenderContext* pC, Gui::RenderContext* pGraphics, PSVGElement* pReferencingElement, MarkerVertex* vertex);

	void CalculateBounds();

	virtual void RecalculateParentBounds();

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}
};

}	// Web
}

#endif // __Web_PSVGMarkerElement_h__
