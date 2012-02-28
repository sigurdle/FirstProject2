#ifndef __LSVGFECOMPONENTTRANSFERELEMENT_H_
#define __LSVGFECOMPONENTTRANSFERELEMENT_H_

//#include "resource.h"       // main symbols


namespace System
{
namespace Web
{

class SVGEXT SVGFEComponentTransferElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEComponentTransferElement>,
//	public CLElementEditASImpl<SVGFEComponentTransferElement>,
	public ElementEditVALImpl<SVGFEComponentTransferElement>,
	public SMILAnimationTargetImpl<SVGFEComponentTransferElement>,
//	public CLSVGFEElementImpl<SVGFEComponentTransferElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

// Internal interfaces
	public CNotifyGetImpl<SVGFEComponentTransferElement>,
	public CNotifySendImpl<SVGFEComponentTransferElement>
{
public:

	CTOR SVGFEComponentTransferElement();

	SVGAnimatedString* get_in1();

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
};

}	// LSVG
}

#endif //__LSVGFECOMPONENTTRANSFERELEMENT_H_
