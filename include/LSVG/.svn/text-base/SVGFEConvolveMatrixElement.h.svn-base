#ifndef w3c_SVGFEConvolveMatrixElement_h
#define w3c_SVGFEConvolveMatrixElement_h

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGEXT SVGFEConvolveMatrixElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEConvolveMatrixElement>,
//	public CLElementEditASImpl<SVGFEConvolveMatrixElement>,
	public ElementEditVALImpl<SVGFEConvolveMatrixElement>,
	public SMILAnimationTargetImpl<SVGFEConvolveMatrixElement>,
//	public CLSVGFEElementImpl<SVGFEConvolveMatrixElement>,

//public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFEConvolveMatrixElement>,
	protected CNotifySendImpl<SVGFEConvolveMatrixElement>
{
public:
	CTOR SVGFEConvolveMatrixElement(NamedNodeMap* attributes);

#if 0
	STDMETHOD(get_in1)(/*[out, retval]*/ ILSVGAnimatedString* *pVal);
	STDMETHOD(get_type)(/*[out,retval]*/ ILSVGAnimatedEnumeration* *pVal);
	STDMETHOD(get_values)(/*[out,retval]*/ SVGAnimatedNumberList* *pVal);
#endif

	ISVGAnimatedString* get_in1();
	ISVGAnimatedInteger* get_orderX();
	ISVGAnimatedInteger* get_orderY();
	SVGAnimatedNumberList* get_kernelMatrix();
	ISVGAnimatedNumber* get_divisor();
	ISVGAnimatedNumber* get_bias();
	ISVGAnimatedInteger* get_targetX();
	ISVGAnimatedInteger* get_targetY();
	ISVGAnimatedEnumeration* get_edgeMode();
	ISVGAnimatedNumber* get_kernelUnitLengthX();
	ISVGAnimatedNumber* get_kernelUnitLengthY();
	ISVGAnimatedBoolean* get_preserveAlpha();

protected:

// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}

	CATXMLAttr2T<CreateInstanceT<CAnimatedClass<CValueTypeWrapper<CreateInstanceT<SVGOptionalTwoNumbersValue> > > >, CValueTypeWrapper<SVGOptionalTwoNumbersValue> >* m_order;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumberList>, CValueTypeWrapper<CreateInstanceT<SVGNumberList> > >* m_kernelMatrix;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedInteger>, CValueTypeWrapper<LongValue> >* m_targetX;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedInteger>, CValueTypeWrapper<LongValue> >* m_targetY;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<SVGNumberValue> >* m_divisor;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumber>, CValueTypeWrapper<SVGNumberValue> >* m_bias;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedBoolean>, CValueTypeWrapper<BooleanValue> >* m_preserveAlpha;
};

}	// Web
}	// System

#endif // w3c_SVGFEConvolveMatrixElement_h
