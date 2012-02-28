#ifndef w3c_SVGFEDisplacementMapElement_h
#define w3c_SVGFEDisplacementMapElement_h

#include "SVGEnumerationChannelSelectorValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEDisplacementMapElement : 
	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEDisplacementMapElement>,
//	public CLElementEditASImpl<SVGFEDisplacementMapElement>,
	public ElementEditVALImpl<SVGFEDisplacementMapElement>,
//	public CLSVGFEElementImpl<SVGFEDisplacementMapElement>,
	public SMILAnimationTargetImpl<SVGFEDisplacementMapElement>,

	protected CNotifyGetImpl<SVGFEDisplacementMapElement>,
	protected CNotifySendImpl<SVGFEDisplacementMapElement>
{
public:
	CTOR SVGFEDisplacementMapElement(NamedNodeMap* attributes);

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<SVGNumberValue> >* m_scale;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationChannelSelectorValue> >, CValueTypeWrapper<SVGEnumerationChannelSelectorValue> >* m_xChannelSelector;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationChannelSelectorValue> >, CValueTypeWrapper<SVGEnumerationChannelSelectorValue> >* m_yChannelSelector;

	ISVGAnimatedNumber* get_scale();
	ISVGAnimatedEnumeration* get_xChannelSelector();
	ISVGAnimatedEnumeration* get_yChannelSelector();
};

}	// Web
}

#endif // w3c_SVGFEDisplacementMapElement_h
