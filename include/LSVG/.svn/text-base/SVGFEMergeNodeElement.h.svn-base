#ifndef w3c_SVGFEMergeNodeElement_h
#define w3c_SVGFEMergeNodeElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFEMergeNodeElement : 

	public SVGElement,
//	public CLElementEditASImpl<SVGFEMergeNodeElement>,
	public ElementEditVALImpl<SVGFEMergeNodeElement>,
	public SMILAnimationTargetImpl<SVGFEMergeNodeElement>
//	public CLSVGFEElementImpl<SVGFEMergeNodeElement>,
/*
	protected CNotifyGetImpl<SVGFEMergeNodeElement>,
	protected CNotifySendImpl<SVGFEMergeNodeElement>
	*/
{
public:
	CTOR SVGFEMergeNodeElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_in1();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedString>, CValueTypeWrapper<CreateInstanceT<CStringValue> > >* m_in1;

	/*
// INotifyGet
	ErrorCode OnChanged(NotifyType type, System::Object *targetObject, System::Object *immtargetObject, long dispID)
	{
		AnimationTarget::OnChanged(type, targetObject, immtargetObject, dispID);

		FireOnChanged(type, targetObject, dispID);
		return Success;
	}
	*/
};

}	// w3c
}

#endif // w3c_SVGFEMergeNodeElement_h
