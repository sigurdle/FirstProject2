#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, X, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, Y, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, Vector3<T>, Z, T(0))

template<class T>
DependencyClass* Vector3<T>::get_Class()
{
	static DependencyClass depclass(typeid(Vector3<T>), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_XProperty(),
		get_YProperty(),
		get_ZProperty(),
	};

	return &depclass;
}

template<class T> DependencyClass* Vector3<T>::pClass(get_Class());

template class GUIEXT Vector3<int>;
template class GUIEXT Vector3<long long>;
template class GUIEXT Vector3<float>;
template class GUIEXT Vector3<double>;

}
}
