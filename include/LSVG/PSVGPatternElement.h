#ifndef Web_PSVGPatternElement_h
#define Web_PSVGPatternElement_h

namespace System
{
namespace Web
{

class PSVGPatternElement :
	public PSVGElement
{
public:
	CTOR PSVGPatternElement(SVGPatternElement* element);

	void CalculateBounds();

	virtual void RecalculateParentBounds();

	virtual void CalculateBoundsAndChildren()
	{
		PSVGElement::CalculateBoundsAndChildren();	// Calculate children first
		CalculateBounds();
	}

	virtual Gui::Brush* CreateBrush(PSVGElement* pReferencingElement, double scaleX, double scaleY);
};

}	// Web
}	// System

#endif // Web_PSVGPatternElement_h
