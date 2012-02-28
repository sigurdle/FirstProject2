#ifndef Web_SVGFEOffsetElement_h
#define Web_SVGFEOffsetElement_h

#include "PSVGFEOffsetElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGFEOffsetElement : 
	public SVGElement,
	public SVGFilterPrimitiveStandardAttributesImpl<SVGFEOffsetElement>,
//	public CLElementEditASImpl<SVGFEOffsetElement>,
	public ElementEditVALImpl<SVGFEOffsetElement>,
//	public CLSVGFEElementImpl<SVGFEOffsetElement>,
//	public SMILAnimationTargetImpl<SVGFEOffsetElement>

//	public ILSVGFilterPrimitiveStandardAttributes,	// ILSVGStylable
//	public IElementEditVAL,	// ILNodeEditVAL

	protected AnimatedAttributeT<SVGAnimatedNumber, 0>,
	protected AnimatedAttributeT<SVGAnimatedNumber, 1>,
	protected AnimatedAttributeT<SVGAnimatedString, 2>
{
public:

	CTOR SVGFEOffsetElement(NamedNodeMap* attributes);

	AnimatedAttributeT<SVGAnimatedNumber, 0>& dx_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedNumber, 0>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedNumber, 1>& dy_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedNumber, 1>*>(this);
	}

	AnimatedAttributeT<SVGAnimatedString, 2>& in1_attr()
	{
		return *static_cast<AnimatedAttributeT<SVGAnimatedString, 2>*>(this);
	}

	ISVGAnimatedNumber* get_dy();
	ISVGAnimatedNumber* get_dx();
	ISVGAnimatedString* get_in1();
};

}	// Web
}

#endif // Web_SVGFEOffsetElement_h
