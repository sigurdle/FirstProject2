#ifndef w3c_SVGClipPathElement_h
#define w3c_SVGClipPathElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGClipPathElement : 
	public SVGTransformableElement,
	//public SVGTransformableImpl<SVGClipPathElement>,
	public SVGStylableImpl<SVGClipPathElement>,
	public SVGLangSpaceImpl<SVGClipPathElement>,
	public ElementEditVALImpl<SVGClipPathElement>,
	public SMILAnimationTargetImpl<SVGClipPathElement>

//	public ISVGTransformable,
//	public IElementEditVAL,	// ILNodeEditVAL
{
public:

	CTOR SVGClipPathElement(NamedNodeMap* attributes);
	~SVGClipPathElement();

	ISVGAnimatedEnumeration* get_clipPathUnits();

public:

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_clipPathUnits;

};

}	// w3c
}

#endif // w3c_SVGClipPathElement_h
