#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(float, StrokeGeometryVisual, Width, 1.0f)

DependencyClass* StrokeGeometryVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_WidthProperty(),
	};

	return &depclass;
}

DependencyClass* StrokeGeometryVisual::pClass(get_Class());

StrokeGeometryVisual::StrokeGeometryVisual() : RenderGeometryVisual(get_Class())
{
}

StrokeGeometryVisual::StrokeGeometryVisual(const geometry& pgeometry) : RenderGeometryVisual(get_Class(), pgeometry)
{
}

void StrokeGeometryVisual::Render(ManagedRenderContext renderContext)
{
	geometry pgeometry = get_Geometry();

	Brush* brush = get_Brush();

	if (brush)
	{
		if (pgeometry != nullptr)
		{
			pgeometry.RenderStroke(renderContext, brush, get_Width());
		}
	}
}

UIElement* StrokeGeometryVisual::HitTest(gm::PointF point)
{
	return nullptr;
}

}	// Gui
}	// System
