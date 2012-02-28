#ifndef Web_SVGTextPathElement_h
#define Web_SVGTextPathElement_h

#include "SVGTextPositioningElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGTextPathElement : 
	public SVGTextContentElementImpl,//<SVGTextPathElement>,
	public SVGURIReferenceImpl<SVGTextPathElement>,
	public SVGTransformableImpl<SVGTextPathElement>,
	public SVGStylableImpl<SVGTextPathElement>,
	public ElementEditVALImpl<SVGTextPathElement>,
	public SMILAnimationTargetImpl<SVGTextPathElement>,
	public CSVGRenderElementImpl<SVGTextPathElement>,

	protected CNotifyGetImpl<SVGTextPathElement>,
	protected CNotifySendImpl<SVGTextPathElement>
{
public:
	CTOR SVGTextPathElement(NamedNodeMap* attributes);

	SVGAnimatedLength* get_startOffset();
	ISVGAnimatedEnumeration* get_method();
	ISVGAnimatedEnumeration* get_spacing();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_startOffset;
};

}	// Web
}

#endif // Web_SVGTextPathElement_h
