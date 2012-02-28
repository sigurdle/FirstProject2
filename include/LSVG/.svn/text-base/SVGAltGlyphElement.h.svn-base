#ifndef Web_SVGAltGlyphElement_h
#define Web_SVGAltGlyphElement_h

#include "PSVGTextPositioningElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGAltGlyphElement : 
	public SVGTextPositioningElementImpl,//<SVGAltGlyphElement>,
	public SVGTransformableImpl<SVGAltGlyphElement>,
	public SVGStylableImpl<SVGAltGlyphElement>,
	public ElementEditVALImpl<SVGAltGlyphElement>,
//	public SMILAnimationTargetImpl<SVGAltGlyphElement>,
	public CSVGRenderElementImpl<SVGAltGlyphElement>

//	protected CNotifyGetImpl<SVGAltGlyphElement>,
//	protected CNotifySendImpl<SVGAltGlyphElement>
{
public:

	CTOR SVGAltGlyphElement(NamedNodeMap* attributes);

	String get_glyphRef();
	void set_glyphRef(StringIn newVal);
	String get_format();
	void set_format(StringIn newVal);
};

}	// Web
}

#endif // Web_SVGAltGlyphElement_h
