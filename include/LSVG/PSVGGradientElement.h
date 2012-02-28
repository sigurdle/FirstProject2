#ifndef Web_PSVGGradientElement_h
#define Web_PSVGGradientElement_h

//#include "PSVGElement.h"

namespace System
{
namespace Web
{

class SVGEXT PSVGGradientElement : public PSVGElement
{
public:
	CTOR PSVGGradientElement(SVGElement* element) : PSVGElement(element)
	{
		m_pRefGradientElement = NULL;
	}

	SVGUnitType GetGradientUnits();
	SVGSpreadMethodType GetSpreadMethod();
	void CreateGradientStops(vector<float>& offsets, vector<Graphics::Color>& colors);
	void GetRefGradientElement();

	virtual void CalculateBoundsAndChildren()
	{
		GetRefGradientElement();
	}

	virtual void ReferenceInvalid(PElementBase/*PSVGElement*/ * pPElement)
	{
		if (pPElement == m_pRefGradientElement)
		{
			m_pRefGradientElement = NULL;
		}
		else
		{
			PElementBase::ReferenceInvalid(pPElement);
		}
	}

protected:

	PSVGGradientElement* m_pRefGradientElement;
};

}	// Web
}	// System

#endif // Web_PSVGGradientElement_h
