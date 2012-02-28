namespace System
{
namespace Gui
{

class AnimationClock;

class _Clock;

class GUIEXT Timeline : public DependencyObject
{
public:
	CTOR Timeline(DependencyClass* depClass);

	DEPENDENCY_CLASS(Timeline, DependencyObject)

	DEPENDENCY_PROPERTY(double, Duration)
};

class GUIEXT Clock : public DependencyObject
{
public:

	CTOR Clock(DependencyClass* depClass) : DependencyObject(depClass)
	{
	}

	DEFINE_THIS(_Clock)

//	double m_time;
//	signal1<Clock*> Frame;

	virtual Timeline* get_Timeline() = 0;

//	bool get_IsPaused();
//	Clock* get_Parent();

	/*
	Nullable<double> get_CurrentTime();
	Nullable<double> get_CurrentProgress();
	Nullable<int> get_CurrentIteration();
	*/

	/*
	PropertyValue* get_CurrentTimeBinding()
	{
		return GetProperty(&CurrentTimeProperty);
	}

	PropertyValue* get_CurrentProgressBinding()
	{
		return GetProperty(&CurrentProgressProperty);
	}

	PropertyValue* get_CurrentIterationBinding()
	{
		return GetProperty(&CurrentIterationProperty);
	}
	*/

	DEPENDENCY_CLASS(Clock, DependencyObject)

	DEPENDENCY_PROPERTY(double, CurrentTime)
	DEPENDENCY_PROPERTY(double, CurrentProgress)
	DEPENDENCY_PROPERTY(int, CurrentIteration)

	DEPENDENCY_PROPERTY(Clock*, Parent)
//	static TypedDependencyProperty<Timeline*> TimelineProperty;

//	virtual void SetTime(double _time) = 0;

//	Clock* m_parent;
	bool m_isPaused;
};

class GUIEXT AnimationTimeline : public Timeline
{
public:

	CTOR AnimationTimeline(DependencyClass* depClass);

	virtual Type* get_TargetPropertyType() const = 0;
	virtual Object* GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock) = 0;

	DEPENDENCY_CLASS(AnimationTimeline, Timeline)

	DEPENDENCY_PROPERTY(bool, IsAdditive)
	DEPENDENCY_PROPERTY(bool, IsCumulative)
};

class GUIEXT MediaClock : public Clock
{
public:
	CTOR MediaClock() : Clock(get_Class())
	{
	}

	virtual Timeline* get_Timeline()
	{
		return NULL;
	}

	DEPENDENCY_CLASS(MediaClock, Clock)
};

class GUIEXT AnimationClock : public Clock//, public IBinding
{
public:

	/*
	CTOR AnimationClock(AnimationTimeline* animation) : Clock(&s_Class), m_animation(animation)
	{
	}
	*/

	CTOR AnimationClock() : Clock(get_Class())
	{
	}

	/*
	virtual Object* GetOutput(IBinding* caller);
	virtual int SetOutput(IBinding* caller, Object* value);
	virtual int SetInput(IBinding* caller, Object* value);
	virtual void* Connect(IBinding* binding);
*/

	DEPENDENCY_CLASS(AnimationClock, Clock)

		/*
protected:

	Object* m_computedValue;

	int SendComputedValueDownStream();

	list<IBinding*> m_outBindings;
	*/
};

template<class T>
class TypedAnimation : public AnimationTimeline
{
public:

	CTOR TypedAnimation() : AnimationTimeline(get_Class())
	{
	}

	virtual Type* get_TargetPropertyType() const
	{
		return typeid(T);
	}

	virtual Object* GetCurrentValue(Object* defaultOriginValue, Object* defaultDestinationValue, AnimationClock* animationClock);

	/*
	Nullable<T> get_From();
	void set_From(Nullable<T> from);

	Nullable<T> get_To();
	void set_To(Nullable<T> to);

	Nullable<T> get_By();
	void set_By(Nullable<T> by);
	*/

	DEPENDENCY_CLASS(TypedAnimation<T>, AnimationTimeline)

	DEPENDENCY_PROPERTY(T, From)
	DEPENDENCY_PROPERTY(T, To)
	DEPENDENCY_PROPERTY(T, By)
};

class _Clock : public _DependencyObject
{
public:
	CTOR _Clock(const Expressive::expression& exp) : _DependencyObject(exp)
	{
	}

	Expressive::typed_expression<double> getCurrentTime() const
	{
		return getProperty(Clock::get_CurrentTimeProperty());
	}
};

/*
class _TypedAnimationClock
{
public:
	_TypedAnimationClock() : _Clock()
	{
	}

	Expressive::typed_expression<double> getCurrentTime() const
	{
		getProperty(CurrentTimeProperty);
	}
};
*/

template<class T>
class TypedAnimationClock : public AnimationClock
{
public:

	CTOR TypedAnimationClock(TypedAnimation<T>* animation) : m_animation(animation)
	{
	}

	virtual TypedAnimation<T>* get_Timeline()
	{
		return m_animation;
	}

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal);

	DEPENDENCY_CLASS(TypedAnimationClock<T>, AnimationClock)

	DEPENDENCY_PROPERTY(T, CurrentValue)

protected:

	TypedAnimation<T>* m_animation;
};

typedef TypedAnimation<int> IntAnimation;
typedef TypedAnimation<int64> Int64Animation;
typedef TypedAnimation<float> FloatAnimation;
typedef TypedAnimation<double> DoubleAnimation;

typedef TypedAnimationClock<int> IntAnimationClock;
typedef TypedAnimationClock<int64> Int64AnimationClock;
typedef TypedAnimationClock<float> FloatAnimationClock;
typedef TypedAnimationClock<double> DoubleAnimationClock;

#ifndef GUI_EXPORTS
#ifndef __LERSTAD__

template class DECLSPEC_DLLIMPORT TypedAnimation<unsigned char>;
template class DECLSPEC_DLLIMPORT TypedAnimation<int>;
template class DECLSPEC_DLLIMPORT TypedAnimation<int64>;
template class DECLSPEC_DLLIMPORT TypedAnimation<float>;
template class DECLSPEC_DLLIMPORT TypedAnimation<double>;

template class DECLSPEC_DLLIMPORT TypedAnimationClock<unsigned char>;
template class DECLSPEC_DLLIMPORT TypedAnimationClock<int>;
template class DECLSPEC_DLLIMPORT TypedAnimationClock<int64>;
template class DECLSPEC_DLLIMPORT TypedAnimationClock<float>;
template class DECLSPEC_DLLIMPORT TypedAnimationClock<double>;

#endif
#endif

}
}
