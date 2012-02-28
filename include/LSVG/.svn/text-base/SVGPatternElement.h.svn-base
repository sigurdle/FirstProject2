#ifndef w3c_SVGPatternElement_h
#define w3c_SVGPatternElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGPatternElement : 

	public SVGElement,
	public SVGStylableImpl<SVGPatternElement>,
	public SVGURIReferenceImpl<SVGPatternElement>,
//	public SVGFitToViewBoxImpl,//<SVGPatternElement, ISVGFitToViewBox>,
	public SVGLangSpaceImpl<SVGPatternElement>,
	public SMILAnimationTargetImpl<SVGPatternElement>,
//	public ElementEditASImpl<SVGPatternElement>,
	public ElementEditVALImpl<SVGPatternElement>,

	public ISVGFitToViewBox

//	protected ISingleObjectListener
//	protected CNotifyGetImpl<SVGPatternElement>,
//	protected CNotifySendImpl<SVGPatternElement>
{
public:

	CTOR SVGPatternElement(NamedNodeMap* attributes);
	~SVGPatternElement();

	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();
	ISVGAnimatedLength* get_width();
	ISVGAnimatedLength* get_height();
	ISVGAnimatedEnumeration* get_patternUnits();
	ISVGAnimatedEnumeration* get_patternContentUnits();
	SVGAnimatedTransformList* get_patternTransform();

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
//		return m_viewBoxAttr;
	}

	Attr* get_preserveAspectRatioAttr()
	{
		return NULL;
//		return m_preserveAspectRatioAttr;
	}

protected:

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_patternUnits;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_patternContentUnits;

	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
	SVGAnimatedTransformList* m_patternTransform;
};

}	// Web
}

#endif // w3c_SVGPatternElement_h
