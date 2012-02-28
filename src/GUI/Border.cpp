#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* Border::get_Class()
{
	static DependencyClass depclass(typeid(Border), Decorator::get_Class());
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

DependencyClass* Border::pClass(get_Class());

Border::Border() : Decorator(get_Class())
{
}

}
}
