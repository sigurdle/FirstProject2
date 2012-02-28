#ifndef w3c_SVGFETurbulenceElement_h
#define w3c_SVGFETurbulenceElement_h

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGEXT SVGFETurbulenceElement : 
	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFETurbulenceElement>,
//	public ElementEditASImpl<SVGFETurbulenceElement>,
	public ElementEditVALImpl<SVGFETurbulenceElement>,
//	public SVGFEElementImpl<SVGFETurbulenceElement>,
	public SMILAnimationTargetImpl<SVGFETurbulenceElement>,

//	public IElementEditVAL,	// ILNodeEditVAL

	public CNotifyGetImpl<SVGFETurbulenceElement>,
	public CNotifySendImpl<SVGFETurbulenceElement>
{
public:
	CTOR SVGFETurbulenceElement();

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<SVGOptionalTwoNumbersValue> > > >, CValueTypeWrapper<CreateInstanceT<SVGOptionalTwoNumbersValue> > >* m_baseFrequency;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedInteger>, CValueTypeWrapper<LongValue> >* m_numOctaves;

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	ISVGAnimatedNumber* get_baseFrequencyX();
	ISVGAnimatedNumber* get_baseFrequencyY();
	ISVGAnimatedInteger* get_numOctaves();
	ISVGAnimatedNumber* get_seed();
	ISVGAnimatedEnumeration* get_stitchTiles();
	ISVGAnimatedEnumeration* get_type();
};

}	// w3c
}

#endif // w3c_SVGFETurbulenceElement_h
