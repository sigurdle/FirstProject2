#ifndef w3c_SVGFEMergeElement_h
#define w3c_SVGFEMergeElement_h

namespace System
{
namespace Web
{

class SVGEXT PSVGFEMergeElement : public PSVGFEElement
{
public:

	CTOR PSVGFEMergeElement(SVGFEMergeElement* element);

	virtual int GetInCount();
	virtual Gui::CEffect* Filter(Gui::RenderTarget* rt, Gui::CEffect* inPinImage[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY);
};

class SVGEXT SVGFEMergeElement : 

	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEMergeElement>,
//	public CLElementEditASImpl<SVGFEMergeElement>,
	public ElementEditVALImpl<SVGFEMergeElement>
//	public SMILAnimationTargetImpl<SVGFEMergeElement>,
//	public CLSVGFEElementImpl<SVGFEMergeElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL

//	protected CNotifyGetImpl<SVGFEMergeElement>,
//	protected CNotifySendImpl<SVGFEMergeElement>
{
public:

	CTOR SVGFEMergeElement(NamedNodeMap* attributes) : SVGElement(new PSVGFEMergeElement(this), attributes)
	{
		SetAllValues(this);	// ???
	}

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
};

}	// w3c
}

#endif // w3c_SVGFEMergeElement_h
