#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

Sphere::Sphere() : Geometry3D(get_Class())
{
}

DependencyClass* Sphere::get_Class()
{
	static DependencyClass depclass(typeid(Sphere), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_DataProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* Sphere::pClass(get_Class());

void Sphere::Render(ManagedRenderContext renderContext)
{
	ASSERT(0);
}

}	// Media3D
}	// Gui
}	// System
