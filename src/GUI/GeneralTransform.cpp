#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* GeneralTransform::get_Class()
{
	static DependencyClass depclass(typeid(GeneralTransform), baseClass::get_Class());

	return &depclass;
}

GeneralTransform::GeneralTransform(DependencyClass* depClass) : DependencyObject(depClass)
{
}

}	// Gui
}	// System
