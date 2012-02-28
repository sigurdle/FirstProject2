#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

//IMP_USE_DEPENDENCY_PROPERTY(float, Brush, Visual, Opacity)
IMP_DEPENDENCY_PROPERTY(float, Brush, BrushOpacity, 1)

DependencyClass* Brush::get_Class()
{
	static DependencyClass depclass(typeid(Brush), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BrushOpacityProperty(),
		//get_Object3DProperty(),
	};

	return &depclass;
}

Brush::Brush(DependencyClass* depClass) : DependencyObject(depClass)
{
}

Brush::Brush(DependencyClass* depClass, float opacity) : DependencyObject(depClass)
{
	set_BrushOpacity(opacity);
}

}	// Gui
}
