#ifndef Web_SVGGlyphRefElement_h
#define Web_SVGGlyphRefElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGGlyphRefElement : 

	public SVGElement,
//	public SVGTransformableImpl<CLSVGGlyphRefElement>,
	public SVGStylableImpl<SVGGlyphRefElement>,
	public ElementEditVALImpl<SVGGlyphRefElement>,
	public SMILAnimationTargetImpl<SVGGlyphRefElement>,
	public CSVGRenderElementImpl<SVGGlyphRefElement>,

	//public IElementEditVAL,	// ILNodeEditVAL

	protected CNotifyGetImpl<SVGGlyphRefElement>,
	protected CNotifySendImpl<SVGGlyphRefElement>
{
public:

	CTOR SVGGlyphRefElement(NamedNodeMap* attributes);

	String get_glyphRef();
	void set_glyphRef(StringIn newVal);
	String get_format();
	void set_format(StringIn newVal);
	double get_x();
	void set_x(double newVal);
	double get_y();
	void set_y(double newVal);
	double get_dx();
	void set_dx(double newVal);
	double get_dy();
	void set_dy(double newVal);
};

}	// Web
}

#endif // Web_SVGGlyphRefElement_h
