#ifndef w3c_SVGEllipseElement_h
#define w3c_SVGEllipseElement_h

//#include "PSVGEllipseElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGEllipseElement : 

	public SVGEllipticalShapeElement,
	public SVGStylableImpl<SVGEllipseElement>,
	public SVGTestsImpl<SVGEllipseElement>,
	public SVGLangSpaceImpl<SVGEllipseElement>,
	public ElementEditVALImpl<SVGEllipseElement>,
//	public SMILAnimationTargetImpl<SVGEllipseElement>,
	public CSVGRenderElementImpl<SVGEllipseElement>,

	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>
{
public:

	CTOR SVGEllipseElement();
	CTOR SVGEllipseElement(NamedNodeMap* attributes);

	ISVGAnimatedLength* get_ry();
	ISVGAnimatedLength* get_rx();

	Attr* get_ryAttr();
	Attr* get_rxAttr();

	inline PSVGEllipseElement* GetPElement()
	{
		return (PSVGEllipseElement*)m_pNode;
	}

	virtual Gui::EllipseGeometry* get_animatedGeometry() override;

protected:

	Gui::EllipseGeometry* m_geometry;

	friend class PSVGEllipseElement;

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>& rx_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>& ry_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>*>(this);
	}
};

}	// Web
}	// System

#endif // Web_SVGEllipseElement_h
