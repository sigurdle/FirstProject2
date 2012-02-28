#ifndef Web_SVGRadialGradientElement_h
#define Web_SVGRadialGradientElement_h

#include "SVGGradientElementImpl.h"

namespace System
{
namespace Web
{

class SVGEXT SVGRadialGradientElement : 

	public SVGGradientElementImpl<SVGRadialGradientElement>,
//	public ElementEditASImpl<SVGRadialGradientElement>,
	public ElementEditVALImpl<SVGRadialGradientElement>,
	public SMILAnimationTargetImpl<SVGRadialGradientElement>,

	protected CNotifyGetImpl<SVGRadialGradientElement>,
	protected CNotifySendImpl<SVGRadialGradientElement>
{
public:
	CTOR SVGRadialGradientElement(NamedNodeMap* attributes);

	ISVGAnimatedLength* get_cx();
	ISVGAnimatedLength* get_cy();
	ISVGAnimatedLength* get_r();
	ISVGAnimatedLength* get_fx();
	ISVGAnimatedLength* get_fy();

protected:

	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_cx;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_cy;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_r;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_fx;
	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLength> > >* m_fy;
};

}	// Web
}

#endif // Web_SVGRadialGradientElement_h
