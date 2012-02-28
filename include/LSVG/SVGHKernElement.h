#ifndef w3c_SVGHKernElement_h
#define w3c_SVGHKernElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGHKernElement : 

	public SVGElement,
//	public CLElementEditASImpl<SVGHKernElement>,
	public ElementEditVALImpl<SVGHKernElement>,

	protected CNotifyGetImpl<SVGHKernElement>,
	protected CNotifySendImpl<SVGHKernElement>
{
public:
	CTOR SVGHKernElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
	{
	}

};

}	// w3c
}	// System

#endif // w3c_SVGHKernElement_h
