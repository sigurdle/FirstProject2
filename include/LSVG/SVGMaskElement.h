#ifndef Web_SVGMaskElement_h
#define Web_SVGMaskElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGMaskElement : 
	public SVGElement,
	public SVGStylableImpl<SVGMaskElement>,
	public SVGLangSpaceImpl<SVGMaskElement>,
	public ElementEditVALImpl<SVGMaskElement>,
	public SMILAnimationTargetImpl<SVGMaskElement>,

	protected CNotifyGetImpl<SVGMaskElement>,
	protected CNotifySendImpl<SVGMaskElement>
{
public:
	CTOR SVGMaskElement(NamedNodeMap* attributes);

	ISVGAnimatedEnumeration* get_maskUnits();
	ISVGAnimatedEnumeration* get_maskContentUnits();
	ISVGAnimatedLength* get_x();
	ISVGAnimatedLength* get_y();
	ISVGAnimatedLength* get_width();
	ISVGAnimatedLength* get_height();

private:

	friend class PSVGMaskElement;

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_maskUnits;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationUnitTypeValue> >, CValueTypeWrapper<SVGEnumerationUnitTypeValue> >* m_maskContentUnits;
	SVGAnimatedLength* m_x;
	SVGAnimatedLength* m_y;
	SVGAnimatedLength* m_width;
	SVGAnimatedLength* m_height;
};

}	// Web
}

#endif // Web_SVGMaskElement_h
