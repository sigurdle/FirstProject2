#ifndef w3c_SVGSetElement_h
#define w3c_SVGSetElement_h

//#include "SVGAnimationElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGSetElement : 
	public SVGAnimationElement,//<SVGSetElement>,
//	public SetElementImpl,//<SVGSetElement>,
	public ElementEditVALImpl<SVGSetElement>,

//	public ILElementEditVAL,	// ILNodeEditVAL
//	public IAnimationElement,	//ILElementTime,

//	public CLElementEditASImpl<SVGSetElement>

	protected CNotifyGetImpl<SVGSetElement>,
	protected CNotifySendImpl<SVGSetElement>
{
public:

	CTOR SVGSetElement(NamedNodeMap* attributes);

};

}	// w3c
}

#endif // w3c_SVGSetElement_h
