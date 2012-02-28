#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGGradientElement.h"
#include "SVGGradientElementImpl.h"
#include "SVGStopElement.h"
#include "SVGURIReferenceImpl.h"

namespace System
{
namespace Web
{

void PSVGGradientElement::GetRefGradientElement()
{
	ASSERT(0);
#if 0
	if (m_pRefGradientElement)
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_pRefGradientElement->m_referencingElements.Find(this);
		ASSERT(pos);
		m_pRefGradientElement->m_referencingElements.RemoveAt(pos);
#endif
		m_pRefGradientElement = NULL;
	}

	ISVGURIReference* psvgUriReference = dynamic_cast<ISVGURIReference*>(m_pNode);

	String uriReference = psvgUriReference->get_href()->get_animVal();

	if (uriReference->Length() && uriReference->c_str()[0] == L'#')
	{
		System::StringW* id = new System::StringW(string_copy(uriReference->c_str() + 1, uriReference->Length()-1));
		//PSVGElement* pUriElement = (PSVGElement*)m_pWindow->m_htmTree->GetElementById(id);
		Element* pUriElement = m_pNode->m_ownerDocument->getElementById(id);

		if (pUriElement)
		{
			PSVGGradientElement* uriGradient = dynamic_cast<PSVGGradientElement*>(pUriElement->m_pNode);
			if (uriGradient)
			{
				m_pRefGradientElement = uriGradient;
				m_pRefGradientElement->m_referencingElements.push_back(this);
			}
		}
	}
#endif
}

SVGUnitType PSVGGradientElement::GetGradientUnits()
{
	SVGGradientElement* psvgElement = dynamic_cast<SVGGradientElement*>(m_pNode);

	if (psvgElement->m_gradientUnits->m_specified || m_pRefGradientElement == NULL)
		return psvgElement->m_gradientUnits->m_animated->m_animVal->m_value;
	else
		return m_pRefGradientElement->GetGradientUnits();
}

SVGSpreadMethodType PSVGGradientElement::GetSpreadMethod()
{
	SVGGradientElement* psvgElement = dynamic_cast<SVGGradientElement*>(m_pNode);

	if (psvgElement->m_spreadMethod->m_specified || m_pRefGradientElement == NULL)
		return psvgElement->m_spreadMethod->m_animated->m_animVal->m_value;
	else
		return m_pRefGradientElement->GetSpreadMethod();
}

void PSVGGradientElement::CreateGradientStops(
	vector<float>& offsets,
	vector<Graphics::Color>& colors)
{
	double last_offset = -1;

	vector<SVGStopElement::PSVGStopElement*> stops;

	for (size_t i = 0; i < m_rchildList.size(); ++i)
	{
		PNode* pNode = m_rchildList[i];

		SVGStopElement::PSVGStopElement* stop = dynamic_cast<SVGStopElement::PSVGStopElement*>(pNode);
		if (stop)
		{
			stops.Add(stop);
		}
	}

	if (stops.GetSize() > 0)
	{
		int last_red;
		int last_green;
		int last_blue;
		int last_alpha;

		for (size_t i = 0; i < stops.GetSize(); i++)
		{
			SVGStopElement::PSVGStopElement* pStop = stops[i];

			SVGStopElement* psvgStopElement = static_cast<SVGStopElement*>(pStop->m_pNode);
			ASSERT(0);
			double offset = 0;//psvgStopElement->m_offset->m_animVal;

			if (offset < 0) offset = 0;
			else if (offset > 1) offset = 1;

			if (offset < last_offset) offset = last_offset;

			int dest_red = pStop->m_computedStopColor.m_rgbColor[0];
			int dest_green = pStop->m_computedStopColor.m_rgbColor[1];
			int dest_blue = pStop->m_computedStopColor.m_rgbColor[2];
			int dest_alpha = pStop->m_computedStopOpacity*255;

			if (last_offset < 0)
			{
				last_offset = 0;
				last_red = dest_red;
				last_green = dest_green;
				last_blue = dest_blue;
				last_alpha = dest_alpha;

				colors.Add(Graphics::Color(last_alpha, last_red, last_green, last_blue));
				offsets.Add(0);
			}

			colors.Add(Graphics::Color(dest_alpha, dest_red, dest_green, dest_blue));
			offsets.Add(offset);

			last_red = dest_red;
			last_green = dest_green;
			last_blue = dest_blue;
			last_alpha = dest_alpha;
			last_offset = offset;
		}

	// Finish off to 100%
		if (last_offset < 1)
		{
			colors.Add(LDraw::Color(last_alpha, last_red, last_green, last_blue));
			offsets.Add(1);
		}
	}
	else if (m_pRefGradientElement)
	{
		m_pRefGradientElement->CreateGradientStops(offsets, colors);
	}
}

}	// Web
}	// System
