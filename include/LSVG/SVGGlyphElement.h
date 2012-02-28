#ifndef w3c_SVGGlyphElement_h
#define w3c_SVGGlyphElement_h

//#include "resource.h"       // main symbols

#include "SVGGlyphAttributesImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGGlyphElement : 
	public SVGElement,
	public SVGStylableImpl<SVGGlyphElement>,
//	public CLElementEditASImpl<SVGGlyphElement>,
	public ElementEditVALImpl<SVGGlyphElement>,
	public SMILAnimationTargetImpl<SVGGlyphElement>,
	public SVGGlyphAttributesImpl,

	protected CNotifyGetImpl<SVGGlyphElement>,
	protected CNotifySendImpl<SVGGlyphElement>,
	protected ISVGPathSegListListener
{
public:

	CTOR SVGGlyphElement(NamedNodeMap* attributes);
	~SVGGlyphElement();

protected:

	virtual void OnPathSegListChange(SVGPathSegList* pSegList);

// EventTarget
	virtual ErrorCode dispatchEvent2(Event * evt, /*[in]*/ bool bCapture, /*[out,retval]*/ bool * doDefault);

};

}	// w3c
}

#endif // w3c_SVGGlyphElement_h
