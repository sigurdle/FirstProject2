#include "stdafx.h"
#include "GUI2.h"

namespace MS
{
namespace Windows
{
namespace Shell
{

using namespace System;
using namespace System::Gui;

IMP_DEPENDENCY_PROPERTY(double, TaskbarItemInfo, ProgressValue, 0.0)
IMP_DEPENDENCY_PROPERTY(TaskbarItemProgressState, TaskbarItemInfo, ProgressState, TaskbarItemProgressState_None)

DependencyClass* TaskbarItemInfo::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_ProgressValueProperty(),
		get_ProgressStateProperty(),
	};

	return &depclass;
}

DependencyClass* TaskbarItemInfo::pClass(get_Class());

TaskbarItemInfo::TaskbarItemInfo() : DependencyObject(get_Class())
{
}

}
}
}
