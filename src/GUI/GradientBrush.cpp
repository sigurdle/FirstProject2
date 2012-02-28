#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(GradientStopCollection*, GradientBrush, Stops, nullptr)

DependencyClass* GradientBrush::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_StopsProperty(),
	};

	return &depclass;
}

//DependencyClass* GradientBrush::pClass(get_Class());

GradientBrush::GradientBrush(DependencyClass* depClass) : Brush(depClass)
{
}

ID2D1GradientStopCollection* GradientBrush::GetD2D1StopCollection(RenderContext* renderContext)
{
	// Create an array of gradient stops to put in the gradient stop 
	// collection that will be used in the linear gradient brush.
	D2D1_GRADIENT_STOP gradientStops[20];	// TODO
//	D2D1_GRADIENT_STOP* gradientStops = _[2];

	if (m_spGradientStopCollection == NULL)
	{
		GradientStopCollection* stops = get_Stops();
		if (stops)
		{
			ASSERT(stops->m_colors.size() == stops->m_offsets.size());

			UINT nstops = (UINT)stops->m_offsets.size();

			for (UINT i = 0; i < nstops; ++i)
			{
				gradientStops[i].color = *(D2D1_COLOR_F*)&stops->m_colors[i];//D2D1::ColorF(D2D1::ColorF::Yellow,1);
				gradientStops[i].position = stops->m_offsets[i];
			}

			renderContext->GetRT()->m_spRT->CreateGradientStopCollection(
				gradientStops,
				nstops, 
				D2D1_GAMMA_2_2,
				D2D1_EXTEND_MODE_CLAMP,
				&m_spGradientStopCollection);
		}
	}

	return m_spGradientStopCollection;
}

}	// Gui
}	// System
