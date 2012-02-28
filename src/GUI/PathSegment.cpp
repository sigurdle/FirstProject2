#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* PathSegment::get_Class()
{
	static DependencyClass depclass(typeid(PathSegment), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ClosedProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* PathSegment::pClass(get_Class());

PathSegment::PathSegment(DependencyClass* depClass) : DependencyObject(depClass)
{
}

}
}
