#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, LinearGradientBrush, X1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LinearGradientBrush, Y1, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LinearGradientBrush, X2, 0.0f)
IMP_DEPENDENCY_PROPERTY(float, LinearGradientBrush, Y2, 0.0f)

DependencyClass* LinearGradientBrush::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_X1Property(),
		get_Y1Property(),
		get_X2Property(),
		get_Y2Property(),
	};

	return &depclass;
}

DependencyClass* LinearGradientBrush::pClass(get_Class());

LinearGradientBrush::LinearGradientBrush() : GradientBrush(get_Class()), m_spLinearGradientBrush(NULL)
{
}

LinearGradientBrush::LinearGradientBrush(Point startPoint, Point endPoint, ColorF startColor, ColorF endColor) : GradientBrush(get_Class()), m_spLinearGradientBrush(NULL)
{
	set_X1(startPoint.X);
	set_Y1(startPoint.Y);

	set_X2(endPoint.X);
	set_Y2(endPoint.Y);

	set_Stops(new GradientStopCollection(startColor, endColor));
}

ID2D1LinearGradientBrush* LinearGradientBrush::Create(RenderContext* renderContext, Visual* refVisual)
{
	if (m_spLinearGradientBrush == nullptr)
	{
		ID2D1GradientStopCollection* spGradientStopCollection = GetD2D1StopCollection(renderContext);
		if (spGradientStopCollection)
		{
			renderContext->GetRT()->m_spRT->CreateLinearGradientBrush(
				D2D1::LinearGradientBrushProperties(cnv(get_Start()), cnv(get_End())),
				spGradientStopCollection,
				&m_spLinearGradientBrush);
		}
	}

	return m_spLinearGradientBrush;
}

gm::PointF LinearGradientBrush::get_Start()
{
	return gm::PointF(get_X1(), get_Y1());
}

gm::PointF LinearGradientBrush::get_End()
{
	return gm::PointF(get_X2(), get_Y2());
}

}	// Gui
}	// System
