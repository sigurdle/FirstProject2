#ifndef w3c_SVGAltGlyphDefElement_h
#define w3c_SVGAltGlyphDefElement_h

#include "SVGTextPositioningElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGAltGlyphDefElement : 
	public SVGElement,
//	public SVGTransformableImpl<CLSVGAltGlyphDefElement>,
	public SVGStylableImpl<SVGAltGlyphDefElement>,
	public ElementEditVALImpl<SVGAltGlyphDefElement>,
//	public SMILAnimationTargetImpl<SVGAltGlyphDefElement>,
	public CSVGRenderElementImpl<SVGAltGlyphDefElement>

//	protected CNotifyGetImpl<SVGAltGlyphDefElement>,
//	protected CNotifySendImpl<SVGAltGlyphDefElement>
{
public:
	CTOR SVGAltGlyphDefElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
	{
	}
};

}	// w3c
}

#endif // w3c_SVGAltGlyphDefElement_h
