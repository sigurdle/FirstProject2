#ifndef w3c_SVGFEBlendElement_h
#define w3c_SVGFEBlendElement_h

//#include "resource.h"       // main symbols

#include "SVGEnumerationBlendModeTypeValue.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEBlendElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEBlendElement>,
//	public CLElementEditASImpl<SVGFEBlendElement>,
	public ElementEditVALImpl<SVGFEBlendElement>,
	public SMILAnimationTargetImpl<SVGFEBlendElement>,
//	public CLSVGFEElementImpl<SVGFEBlendElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEBlendElement>,
	protected CNotifySendImpl<SVGFEBlendElement>
{
public:

	CTOR SVGFEBlendElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();
	SVGAnimatedString* get_in2();
	ISVGAnimatedEnumeration* get_mode();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in2;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationBlendModeTypeValue> >, CValueTypeWrapper<CreateInstanceT<SVGEnumerationBlendModeTypeValue> > >* m_mode;
};

}	// w3c
}

#endif // w3c_SVGFEBlendElement_h
