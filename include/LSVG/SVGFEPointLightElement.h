#ifndef w3c_SVGFEPointLightElement_h
#define w3c_SVGFEPointLightElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFEPointLightElement : 
	public SVGElement,
//	public CLElementEditASImpl<SVGFEPointLightElement>,
	public ElementEditVALImpl<SVGFEPointLightElement>,
	public SMILAnimationTargetImpl<SVGFEPointLightElement>,

//	public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEPointLightElement>,
	protected CNotifySendImpl<SVGFEPointLightElement>
{
public:

	CTOR SVGFEPointLightElement(NamedNodeMap* attributes);

	ISVGAnimatedNumber* get_x();
	ISVGAnimatedNumber* get_y();
	ISVGAnimatedNumber* get_z();

public:
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_x;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_y;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber >, CValueTypeWrapper<SVGNumberValue> >* m_z;
};

}	// w3c
}

#endif // w3c_SVGFEPointLightElement_h
