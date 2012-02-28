#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* ButtonBase::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
	};
	*/

	return &depclass;
}

ButtonBase::ButtonBase(DependencyClass* depClass) : ContentControl(depClass)
{
}

ButtonBase::ButtonBase(DependencyClass* depClass, Object* content) : ContentControl(depClass, content)
{
}

}	// Gui
}	// System
