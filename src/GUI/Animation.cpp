#include "stdafx.h"
#include "GUI2.h"

#include "DXUT.h"

namespace System
{
namespace Gui
{

DependencyClass* Clock::get_Class()
{
	static DependencyClass depclass(typeid(Clock), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* MediaClock::get_Class()
{
	static DependencyClass depclass(typeid(MediaClock), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

////////////////////////////////////

IMP_DEPENDENCY_PROPERTY_T(T, T, TypedAnimation<T>, From, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, TypedAnimation<T>, To, T(0))
IMP_DEPENDENCY_PROPERTY_T(T, T, TypedAnimation<T>, By, T(0))

/*
template<class T>
GUIEXT TypedDependencyProperty<T> TypedAnimation<T>::ToProperty(&Class, WSTR("To"));

template<class T>
GUIEXT TypedDependencyProperty<T> TypedAnimation<T>::ByProperty(&Class, WSTR("By"));

template<class T>
Nullable<T> TypedAnimation<T>::get_From()
{
	return GetPropertyValueT<T>(&FromProperty);
}

template<class T>
void TypedAnimation<T>::set_From(Nullable<T> from)
{
	SetPropertyValue(&FromProperty, from);
}

template<class T>
Nullable<T> TypedAnimation<T>::get_To()
{
	return GetPropertyValueT<T>(&ToProperty);
}

template<class T>
void TypedAnimation<T>::set_To(Nullable<T> to)
{
	SetPropertyValue(&ToProperty, to);
}

template<class T>
Nullable<T> TypedAnimation<T>::get_By()
{
	return GetPropertyValueT<T>(&ByProperty);
}

template<class T>
void TypedAnimation<T>::set_By(Nullable<T> by)
{
	SetPropertyValue(&ByProperty, by);
}
*/

template<class T>
Object* TypedAnimation<T>::GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock)
{
	double t = animationClock->get_CurrentProgress();

	Nullable<T> from = get_From();
	Nullable<T> to = get_To();

	if (from.HasValue() && to.HasValue())
	{
		T value = T(from + (to - from) * t);
		return box_cast(value);
	}
	else if (to.HasValue())
	{
		ASSERT(0);
		return NULL;
	}
	else
	{
		return NULL;
	}
}

////////////////////
// Clock

IMP_DEPENDENCY_PROPERTY(double, Clock, CurrentTime, 0.0)
IMP_DEPENDENCY_PROPERTY(double, Clock, CurrentProgress, 0.0)
IMP_DEPENDENCY_PROPERTY(int, Clock, CurrentIteration, 0)
IMP_DEPENDENCY_PROPERTY(Clock*, Clock, Parent, nullptr)

////////////////////////////////////////////
// AnimationClock

DependencyClass* AnimationClock::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

////////////////////////////////////////////
// TypedAnimationClock

IMP_DEPENDENCY_PROPERTY_T(T, T, TypedAnimationClock<T>, CurrentValue, nullptr)

template<class T>
DependencyClass* TypedAnimationClock<T>::get_Class()
{
	static DependencyClass depclass(typeid(TypedAnimationClock<T>), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

template<class T> DependencyClass* TypedAnimationClock<T>::pClass(get_Class());

template<class T>
void TypedAnimationClock<T>::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal)
{
	if (pPropertyVal->m_dp == get_CurrentTimeProperty())
	{
		double currentTime = GetPropertyValueDouble(get_CurrentTimeProperty());

		double duration = get_Timeline()->get_Duration();

		SetPropertyValue(get_CurrentProgressProperty(), currentTime / duration);

		SetPropertyValue(get_CurrentValueProperty(), get_Timeline()->GetCurrentValue(NULL, NULL, this));
	}
}

//////////

template<class T>
DependencyClass* TypedAnimation<T>::get_Class()
{
	static DependencyClass depclass(typeid(TypedAnimation<T>), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

template<class T> DependencyClass* TypedAnimation<T>::pClass(get_Class());

//template class GUIEXT TypedAnimation<unsigned char>;
template class GUIEXT TypedAnimation<int>;
template class GUIEXT TypedAnimation<int64>;
template class GUIEXT TypedAnimation<float>;
template class GUIEXT TypedAnimation<double>;

//template class GUIEXT TypedAnimationClock<unsigned char>;
template class GUIEXT TypedAnimationClock<int>;
template class GUIEXT TypedAnimationClock<int64>;
template class GUIEXT TypedAnimationClock<float>;
template class GUIEXT TypedAnimationClock<double>;

//////

DependencyClass* Timeline::get_Class()
{
	static DependencyClass depclass(typeid(Timeline), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* AnimationTimeline::get_Class()
{
	static DependencyClass depclass(typeid(AnimationTimeline), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_ParentWindowProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
		get_AntialiasProperty(),
	};
	*/

	return &depclass;
}

AnimationTimeline::AnimationTimeline(DependencyClass* depClass) : Timeline(depClass)
{
}

}	// Gui
}	// System
