#ifndef Web_SVGFETileElement_h
#define Web_SVGFETileElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFETileElement :

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFETileElement>,
//	public ElementEditASImpl<CLSVGFETileElement>,
	public ElementEditVALImpl<SVGFETileElement>,
	public SMILAnimationTargetImpl<SVGFETileElement>
//	public SVGFEElementImpl<CLSVGFETileElement>,

	//public ILElementEditVAL,	// ILNodeEditVAL

	/*
	protected CNotifyGetImpl<SVGFETileElement>,
	protected CNotifySendImpl<SVGFETileElement>
	*/
{
public:
	CTOR SVGFETileElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();

protected:

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;
};

}	// Web
}	// System

#endif // Web_SVGFETileElement_h
