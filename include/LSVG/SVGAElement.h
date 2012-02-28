#ifndef w3c_SVGAElement_h
#define w3c_SVGAElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGAElement : 
	public SVGTransformableElement,
	public SVGURIReferenceImpl<SVGAElement>,
//	public SVGTransformableImpl<SVGAElement>,
	public SVGStylableImpl<SVGAElement>,
	public SVGTestsImpl<SVGAElement>,
	public SVGLangSpaceImpl<SVGAElement>,
	public ElementEditVALImpl<SVGAElement>,
//	public SMILAnimationTargetImpl<SVGAElement>,
	public CSVGRenderElementImpl<SVGAElement>

//	protected CNotifyGetImpl<SVGAElement>,
//	protected CNotifySendImpl<SVGAElement>
{
public:

	CTOR SVGAElement(NamedNodeMap* attributes);

	SVGAnimatedString* get_target();

public:

	SVGAnimatedString* m_target;

	friend class PSVGAElement;
};

}	// w3c
}	// System

#endif // w3c_SVGAElement_h
