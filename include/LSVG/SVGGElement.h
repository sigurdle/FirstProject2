#ifndef w3c_SVGGElement_h
#define w3c_SVGGElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGGElement : 

	public SVGTransformableElement,
	//public SVGTransformableImpl<SVGGElement>,
	public SVGStylableImpl<SVGGElement>,
	public SVGLangSpaceImpl<SVGGElement>,
	public SVGTestsImpl<SVGGElement>,
	public ElementEditVALImpl<SVGGElement>,
	public SMILAnimationTargetImpl<SVGGElement>,
	public CSVGRenderElementImpl<SVGGElement>
//	public CLElementTimeContainerImpl<SVGGElement>,

//	public ILElementTimeContainer,	// ILElementTime

//	protected CNotifyGetImpl<SVGGElement>,
//	protected CNotifySendImpl<SVGGElement>
{
public:
	CTOR SVGGElement(NamedNodeMap* attributes);

	PSVGGElement* GetPElement() const
	{
		return (PSVGGElement*)m_pNode;
	}
};

}	// w3c
}

#endif // w3c_SVGGElement_h
