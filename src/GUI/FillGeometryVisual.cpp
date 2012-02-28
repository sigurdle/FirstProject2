#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* FillGeometryVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	return &depclass;
}

DependencyClass* FillGeometryVisual::pClass(get_Class());

FillGeometryVisual::FillGeometryVisual() : RenderGeometryVisual(get_Class())
{
}

FillGeometryVisual::FillGeometryVisual(const geometry& pgeometry) : RenderGeometryVisual(get_Class(), pgeometry)
{
}

void FillGeometryVisual::Render(ManagedRenderContext renderContext)
{
	geometry geom = get_Geometry();

	Brush* brush = get_Brush();

	if (brush)
	{
		if (geom != nullptr)
		{
			geom.RenderFill(renderContext, brush);
		}
	}
}

UIElement* FillGeometryVisual::HitTest(gm::PointF point)
{
	geometry geom = get_Geometry();
	if (geom != nullptr)
	{
		if (geom.FillContains(point))
		{
			return this;
		}
	}

	return nullptr;
}

}	// Gui
}	// System
