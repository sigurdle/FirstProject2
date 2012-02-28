#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

DependencyClass* Cylinder::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_DataProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* Cylinder::pClass(get_Class());

Cylinder::Cylinder() : Geometry3D(get_Class())
{
}

void Cylinder::Render(ManagedRenderContext renderContext)
{
	ASSERT(0);
}

}	// Media3D
}	// Gui
}	// System
