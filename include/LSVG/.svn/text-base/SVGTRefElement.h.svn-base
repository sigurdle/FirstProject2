#ifndef w3c_SVGTRefElement_h
#define w3c_SVGTRefElement_h

#include "SVGTextPositioningElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGTRefElement : 

	public SVGTextPositioningElementImpl,//<SVGTRefElement>,
	public SVGURIReferenceImpl<SVGTRefElement>,
	public SVGTransformableImpl<SVGTRefElement>,
	public SVGStylableImpl<SVGTRefElement>,
	public ElementEditVALImpl<SVGTRefElement>,
	public SMILAnimationTargetImpl<SVGTRefElement>,
	public CSVGRenderElementImpl<SVGTRefElement>,

	public ISVGTransformable,
//	public IElementEditVAL,	// INodeEditVAL

	protected CNotifyGetImpl<SVGTRefElement>,
	protected CNotifySendImpl<SVGTRefElement>
{
public:

	CTOR SVGTRefElement(NamedNodeMap* attributes);

	virtual long getNumberOfChars();

protected:

	Element* m_refElement;
};

}	// w3c
}

#endif // w3c_SVGTRefElement_h
