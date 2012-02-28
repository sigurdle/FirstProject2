#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, RadiusX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, RadiusY, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, CenterX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, CenterY, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, OriginOffsetX, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, RadialGradientBrush, OriginOffsetY, 0.0f)

DependencyClass* RadialGradientBrush::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_RadiusXProperty(),
		get_RadiusYProperty(),
		get_CenterXProperty(),
		get_CenterYProperty(),
		get_OriginOffsetXProperty(),
		get_OriginOffsetYProperty(),
	};

	return &depclass;
}

DependencyClass* RadialGradientBrush::pClass(get_Class());

RadialGradientBrush::RadialGradientBrush() : GradientBrush(get_Class()), m_spRadialGradientBrush(NULL)
{
}

ID2D1RadialGradientBrush* RadialGradientBrush::Create(RenderContext* renderContext, Visual* refVisual)
{
	if (m_spRadialGradientBrush == NULL)
	{
		ID2D1GradientStopCollection* spGradientStopCollection = GetD2D1StopCollection(renderContext);
		if (spGradientStopCollection)
		{
			renderContext->GetRT()->m_spRT->CreateRadialGradientBrush(
				D2D1::RadialGradientBrushProperties(cnv(get_Center()), cnv(get_OriginOffset()), get_RadiusX(), get_RadiusY()),
				spGradientStopCollection,
				&m_spRadialGradientBrush);
		}
	}

	return m_spRadialGradientBrush;
}

}	// Gui
}	// System
