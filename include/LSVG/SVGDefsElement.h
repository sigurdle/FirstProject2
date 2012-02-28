#ifndef w3c_SVGDefsElement_h
#define w3c_SVGDefsElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGDefsElement : 

	public SVGElement,
//	public SVGTransformableImpl<SVGDefsElement, ILSVGTransformable>,
	public SVGStylableImpl<SVGDefsElement>,
	public SVGLangSpaceImpl<SVGDefsElement>,
	//public SMILAnimationTargetImpl<SVGDefsElement>,
	public ElementEditVALImpl<SVGDefsElement>

//	protected CNotifyGetImpl<SVGDefsElement>,
//	protected CNotifySendImpl<SVGDefsElement>
{
public:
	CTOR SVGDefsElement(NamedNodeMap* attributes);
};

}	// w3c
}	// System

#endif // w3c_SVGDefsElement_h
