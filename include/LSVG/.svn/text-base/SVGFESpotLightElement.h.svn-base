#ifndef w3c_SVGFESpotLightElement_h
#define w3c_SVGFESpotLightElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFESpotLightElement : 

	public SVGElement,
//	public ElementEditASImpl<SVGFESpotLightElement>,
	public ElementEditVALImpl<SVGFESpotLightElement>,
	public SMILAnimationTargetImpl<SVGFESpotLightElement>,

	public CNotifyGetImpl<SVGFESpotLightElement>,
	public CNotifySendImpl<SVGFESpotLightElement>
{
public:
	CTOR SVGFESpotLightElement(NamedNodeMap* attributes);

	ISVGAnimatedNumber* get_x();
	ISVGAnimatedNumber* get_y();
	ISVGAnimatedNumber* get_z();
	ISVGAnimatedNumber* get_pointsAtX();
	ISVGAnimatedNumber* get_pointsAtY();
	ISVGAnimatedNumber* get_pointsAtZ();
	ISVGAnimatedNumber* get_specularExponent();
	ISVGAnimatedNumber* get_limitingConeAngle();

public:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_x;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_y;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_z;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_pointsAtX;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_pointsAtY;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_pointsAtZ;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_specularExponent;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_limitingConeAngle;
};

}	// w3c
}

#endif // w3c_SVGFESpotLightElement_h
