#ifndef Web_SVGLineElement_h
#define Web_SVGLineElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGLineElement : 
	public SVGTransformableElement,
	//public SVGTransformableImpl<SVGLineElement>,
	public SVGStylableImpl<SVGLineElement>,
	public SVGLangSpaceImpl<SVGLineElement>,
//	public ElementEditASImpl<SVGLineElement>,
	public ElementEditVALImpl<SVGLineElement>,
//	public SMILAnimationTargetImpl<SVGLineElement>,
	public CSVGRenderElementImpl<SVGLineElement>,

	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>,
	protected AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>
{
public:

	CTOR SVGLineElement(NamedNodeMap* attributes);

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>& x1_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 0>*>(this);
	}
	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>& y1_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 1>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>& x2_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>*>(this);
	}

	AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>& y2_attr()
	{
		return *static_cast<AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 3>*>(this);
	}

	ISVGAnimatedLength* get_x1();
	ISVGAnimatedLength* get_y1();
	ISVGAnimatedLength* get_x2();
	ISVGAnimatedLength* get_y2();

protected:

	friend class PSVGLineElement;

	/*
	SVGAnimatedLength* m_x1;
	SVGAnimatedLength* m_y1;
	SVGAnimatedLength* m_x2;
	SVGAnimatedLength* m_y2;

	Attr* m_x1Attr;
	Attr* m_y1Attr;
	Attr* m_x2Attr;
	Attr* m_y2Attr;
	*/
};

}	// Web
}	// System

#endif // Web_SVGLineElement_h
