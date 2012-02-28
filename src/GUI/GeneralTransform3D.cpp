#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

DependencyClass* GeneralTransform3D::get_Class()
{
	static DependencyClass depclass(typeid(GeneralTransform3D), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_BoundsLeftProperty(),
		get_BoundsTopProperty(),
		get_BoundsWidthProperty(),
		get_BoundsHeightProperty(),
		get_FillAreaProperty(),
		get_ContourLengthProperty(),
	};
	*/

	return &depclass;
}

GeneralTransform3D::GeneralTransform3D(DependencyClass* depClass) : DependencyObject(depClass)
{
}

}
}
}
