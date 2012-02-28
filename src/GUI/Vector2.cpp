#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY_T(T, T, Vector2<T>, X, 0)
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector2<T>, Y, 0)

template<class T>
DependencyClass* Vector2<T>::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_XProperty(),
		get_YProperty(),
	};

	return &depclass;
}

template<class T> DependencyClass* Vector2<T>::pClass(get_Class());

//template<class T>
//TypedDependencyProperty<T> Vector2<T>::YProperty(&Class, WSTR("Y"), 0);

template<> class GUIEXT Vector2<int>;
template<> class GUIEXT Vector2<float>;
template<> class GUIEXT Vector2<double>;

}
}
