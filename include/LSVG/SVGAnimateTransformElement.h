#ifndef w3c_SVGAnimateTransformElement_h
#define w3c_SVGAnimateTransformElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGAnimateTransformElement : 
	public SVGAnimationElement,//<SVGAnimateTransformElement>,
//	public ElementAnimateImpl,//<SVGAnimateTransformElement>,
	public ElementEditVALImpl<SVGAnimateTransformElement>,

	//public IElementEditVAL,	// ILNodeEditVAL
//	public IElementAnimate,	//ILAnimationElement,	//ILElementTime,

//	public AnimationElementImpl<SVGAnimateTransformElement>,
//	public ElementEditASImpl<SVGAnimateTransformElement>

	protected CNotifyGetImpl<SVGAnimateTransformElement>,
	protected CNotifySendImpl<SVGAnimateTransformElement>
{
public:
	CTOR SVGAnimateTransformElement(NamedNodeMap* attributes);

	virtual void SetValuesFromAttributes();
//	virtual void DoAnimationForElement(ILDOMElement* target);
	virtual void DoAnimationForElement(CATAttr* pAnimatedAttr);
};

}	// w3c
}

#endif // w3c_SVGAnimateTransformElement_h
