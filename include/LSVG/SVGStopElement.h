#ifndef w3c_SVGStopElement_h
#define w3c_SVGStopElement_h

#include "PSVGGradientElement.h"

namespace System
{
namespace Web
{

class SVGEXT SVGStopElement : 
	public SVGElement,
	public SVGStylableImpl<SVGStopElement>,
//	public ElementEditASImpl<SVGStopElement>,
	public ElementEditVALImpl<SVGStopElement>,
	public SMILAnimationTargetImpl<SVGStopElement>
{
public:

	class SVGEXT PSVGStopElement : public PSVGElement
	{
	public:
		CTOR PSVGStopElement(SVGStopElement* element) : PSVGElement(element)
		{
		}
	};

	CTOR SVGStopElement(NamedNodeMap* attributes);

	Attr* get_offsetAttr();
	ISVGAnimatedNumber* get_offset();

	inline PSVGStopElement* GetPElement()
	{
		return (PSVGStopElement*)m_pNode;
	}

protected:

	friend class PSVGStopElement;
	friend class PSVGGradientElement;

//	friend void offsetBaseValChanged(Object* obj);

//	Attr* m_offsetAttr;
//	SVGAnimatedNumber* m_offset;
//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedNumberT<SVGNumberOrPercentageValue> >, CValueTypeWrapper<SVGNumberOrPercentageValue> >* m_offset;
};

}	// w3c
}

#endif // w3c_SVGStopElement_h
