#ifndef w3c_SVGParElement_h
#define w3c_SVGParElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGParElement : 

	public SVGElement,
//	public CLSVGLocatableImpl<SVGParElement>,
//	public ElementTimeContainerImpl,//<SVGParElement>,
	public SMILAnimationTargetImpl<SVGParElement>,	// Not really
	public ElementEditVALImpl<SVGParElement>,
	public SVGTestsImpl<SVGParElement>,
	public CSVGRenderElementImpl<SVGParElement>,

//	public ILElementParallelTimeContainer,
//	public ILElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGParElement>,
	protected CNotifySendImpl<SVGParElement>
{
public:

	CTOR SVGParElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
	{
		m_timeContainerImpl = new ElementTimeContainerImpl(this);
	//	SetAllValues(this);	// ??
	}

// IElementTimeContainer
	String get_timeContainer()
	{
		return WSTR("par");
	}
	void set_timeContainer(StringIn newVal)
	{
		ASSERT(0);
	}

	ElementTimeContainerImpl* m_timeContainerImpl;
};

}	// Web
}

#endif // __SVGPARELEMENT_H
