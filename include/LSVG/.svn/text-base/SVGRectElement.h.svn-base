#ifndef Web_SVGRectElement_h
#define Web_SVGRectElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGRectElement : 

	public SVGShapeElement,
	public SVGStylableImpl<SVGRectElement>,
	public SVGLangSpaceImpl<SVGRectElement>,
	public SVGTestsImpl<SVGRectElement>,
	public ElementEditVALImpl<SVGRectElement>,
	public SMILAnimationTargetImpl<SVGRectElement>,
	public CSVGRenderElementImpl<SVGRectElement>,

	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 4>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 5>
{
public:

	CTOR SVGRectElement(NamedNodeMap* attributes);
	~SVGRectElement();

	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();
	ISVGAnimatedLength* get_width();
	ISVGAnimatedLength* get_height();
	ISVGAnimatedLength* get_rx();
	ISVGAnimatedLength* get_ry();

	Attr* get_xAttr();
	Attr* get_yAttr();
	Attr* get_widthAttr();
	Attr* get_heightAttr();
	Attr* get_rxAttr();
	Attr* get_ryAttr();

	inline PSVGRectElement* GetPElement()
	{
		return (PSVGRectElement*)m_pNode;
	}

protected:

	friend class PSVGRectElement;

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>& x_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>& y_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>& width_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>& height_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 4>& rx_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 4>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 5>& ry_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 5>*>(this);
	}
};

}	// Web
}

#endif // Web_SVGRectElement_h
