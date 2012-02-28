#include "stdafx.h"
#include "LXUI2.h"
#include "GradientStopCollection.h"
#include "GradientStop.h"

namespace System
{
namespace UI
{

GradientStopCollection::GradientStopCollection()
{
}

const Type_Info& GradientStopCollection::GetItemType() const
{
	return typeid(GradientStop*);
}

unsigned int GradientStopCollection::GetCount()
{
	return m_items.size();
}

void GradientStopCollection::Clear()
{
	m_items.clear();
	OnChanged();
}

void GradientStopCollection::AddObject(Object* element)
{
	GradientStop* stop = dynamic_cast<GradientStop*>(element);
	if (stop == NULL) throw new Exception(WSTR("Invalid object"));
	Add(stop);
}

void GradientStopCollection::Add(GradientStop* element)
{
	m_items.push_back(element);
	OnChanged();
}

GradientStop* GradientStopCollection::get_Item(unsigned int index)
{
	if (index < m_items.size())
	{
		return m_items[index];
	}
	else
	{
		throw new ArgumentOutOfRangeException();
	}
}

void GradientStopCollection::set_Item(unsigned int index, GradientStop* element)
{
	if (index < m_items.size())
	{
		m_items[index] = element;
		OnChanged();
	}
	else
	{
		throw new ArgumentOutOfRangeException();
	}
}

void GradientStopCollection::CreateGradientStops(
	vector<float>& offsets,
	vector<LDraw::Color>& colors)
{
	double last_offset = -1;

#if 0
	CArray<GradientStop*,GradientStop*> stops;

	//CComQIPtr<ILDOMElement> gradient = m_pNode;

#if 0
	UPOSITION pos = m_childList.GetHeadPosition();
	while (pos)
	{
		CPSVGElementImpl* pElement = (CPSVGElementImpl*)m_childList.GetNext(pos);

		CComQIPtr<ILSVGStopElement> stop = pElement->m_pNode;
		if (stop)
		{
			stops.Add((CPSVGStopElement*)pElement);
		}
	}
#endif

	for (int i = 0; i < m_childNodes->m_items.size(); i++)
	{
		//CComQIPtr<ILGradientStop, &IID_ILGradientStop> gradientStop = (IUnknown*)m_childNodes->m_items[i];
		CLGradientStop* gradientStop = dynamic_cast<CLGradientStop*>(m_childNodes->m_items[i]);

		if (gradientStop)
		{
			stops.Add(gradientStop);
		}
	}
#endif

	//if (stops.GetSize() > 0)
	{
		int last_red;
		int last_green;
		int last_blue;
		int last_alpha;

		for (unsigned int i = 0; i < m_items.GetSize(); i++)
		{
			GradientStop* pStop = m_items[i];

			//CLSVGStopElement* psvgStopElement = static_cast<CLSVGStopElement*>(pStop->m_pNode);
			double offset = pStop->get_Offset();

			if (offset < 0) offset = 0;
			else if (offset > 1) offset = 1;

			if (offset < last_offset) offset = last_offset;

			Color color = pStop->get_Color();

			int dest_red = color.get_R();
			int dest_green = color.get_G();
			int dest_blue = color.get_B();
			int dest_alpha = color.get_A();

			if (last_offset < 0)
			{
				last_offset = 0;
				last_red = dest_red;
				last_green = dest_green;
				last_blue = dest_blue;
				last_alpha = dest_alpha;

				colors.Add(LDraw::Color(last_alpha, last_red, last_green, last_blue));
				offsets.Add(0);
			}

			colors.Add(LDraw::Color(dest_alpha, dest_red, dest_green, dest_blue));
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
	/*
	else if (m_pRefGradientElement)
	{
		m_pRefGradientElement->CreateGradientStops(offsets, colors);
	}
	*/
}

}	// UI
}
