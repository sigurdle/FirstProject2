#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(Brush*, RenderGeometryVisual, Brush, new SolidColorBrush(0,0,0)/*, new PropertyMetadata(true)*/);
IMP_DEPENDENCY_PROPERTY1(geometry, RenderGeometryVisual, Geometry, nullptr, new PropertyMetadata(true))

DependencyClass* RenderGeometryVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BrushProperty(),
		get_GeometryProperty(),
	};

	return &depclass;
}

//DependencyClass* RenderGeometryVisual::pClass(get_Class());

RenderGeometryVisual::RenderGeometryVisual(DependencyClass* depClass) : UIElement(depClass)
{
}

RenderGeometryVisual::RenderGeometryVisual(DependencyClass* depClass, const geometry& pgeometry) : UIElement(depClass)
{
	set_Geometry(pgeometry);
}

void RenderGeometryVisual::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_GeometryProperty())
	{
	}

	Visual::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

bool RenderGeometryVisual::IsFullyOpaque()
{
	Brush* brush = get_Brush();

	if (brush)
	{
		return brush->IsFullyOpaque();
	}
	else
	{
		return false;	// ??
	}
}

}	// Gui
}	// System
