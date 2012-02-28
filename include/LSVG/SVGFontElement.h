#ifndef w3c_SVGFontElement_h
#define w3c_SVGFontElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGFontElement : 
	public SVGElement,
//	public ElementEditASImpl<SVGFontElement>,
	public ElementEditVALImpl<SVGFontElement>

//	public SVGStylableImpl<SVGFontElement>,

//	protected SMILAnimationTargetImpl<SVGFontElement>,
//	protected CNotifyGetImpl<SVGFontElement>,
//	protected CNotifySendImpl<SVGFontElement>
{
public:

	CTOR SVGFontElement(NamedNodeMap* attributes);

// Extensions
	double get_horizOriginX();
	double get_horizOriginY();
	double get_vertOriginX();
	double get_vertOriginY();

protected:

	CXMLAttr2T<CreateInstanceT<CValueTypeWrapper<LongValue> > >* m_horiz_adv_x;
};

}	// w3c
}

#endif // w3c_SVGFontElement_h
