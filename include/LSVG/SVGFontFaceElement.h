#ifndef w3c_SVGFontFaceElement_h
#define w3c_SVGFontFaceElement_h

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGEXT SVGFontFaceElement : 

	public SVGElement,
//	public ElementEditASImpl<CLSVGFontFaceElement>,
	public ElementEditVALImpl<SVGFontFaceElement>,

//	public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGFontFaceElement>,
	protected CNotifySendImpl<SVGFontFaceElement>
{
public:
	CTOR SVGFontFaceElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
	{
	}

public:
// Extenions
	double get_unitsPerEm();
	double get_xHeight();
	double get_capHeight();
	double get_ascent();
	double get_descent();
};

}	// w3c
}

#endif // w3c_SVGFontFaceElement_h
