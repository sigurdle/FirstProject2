#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

/*
IMP_DEPENDENCY_PROPERTY(float, Viewport, ExtentWidth, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, ExtentHeight, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, ScrollableWidth, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, ScrollableHeight, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, ViewportWidth, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, ViewportHeight, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, HorizontalOffset, 0)
IMP_DEPENDENCY_PROPERTY(float, Viewport, VerticalOffset, 0)
*/

DependencyClass* Viewport::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ExtentWidthProperty(),
		get_ExtentHeightProperty(),
		get_ScrollableWidthProperty(),
		get_ScrollableHeightProperty(),
		get_ViewportWidthProperty(),
		get_ViewportHeightProperty(),
		get_HorizontalOffsetProperty(),
		get_VerticalOffsetProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* Viewport::pClass(get_Class());

Viewport::Viewport() : ContentControl(get_Class())
{
}

}	// Gui
}	// System
