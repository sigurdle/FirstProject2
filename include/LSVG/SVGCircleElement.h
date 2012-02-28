#ifndef Web_SVGCircleElement_h
#define Web_SVGCircleElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGCircleElement : 
	public SVGEllipticalShapeElement,
	//public SVGTransformableImpl<SVGCircleElement>,
	public SVGStylableImpl<SVGCircleElement>,
	public SVGLangSpaceImpl<SVGCircleElement>,
	public SVGTestsImpl<SVGCircleElement>,
	public SVGExternalResourcesRequiredImpl<SVGCircleElement>,
//	public ElementEditASImpl<SVGCircleElement>,
	public ElementEditVALImpl<SVGCircleElement>,
//	public SMILAnimationTargetImpl<SVGCircleElement>,
	public CSVGRenderElementImpl<SVGCircleElement>,
	public AnimatedAttributeAffectsBoundsT<SVGAnimatedLength, 2>
{
public:
	CTOR SVGCircleElement();
	CTOR SVGCircleElement(NamedNodeMap* attributes);

	XMLANIMATEDATTR(SVGCircleElement, SVGAnimatedLength, ISVGAnimatedLength*, r, 2)

	ElementType* GetElementType() override;

	PSVGCircleElement* GetPElement() const
	{
		return (PSVGCircleElement*)m_pNode;
	}

protected:

	friend class PSVGCircleElement;

};

}	// Web
}	// System

#endif // Web_SVGCircleElement_h
