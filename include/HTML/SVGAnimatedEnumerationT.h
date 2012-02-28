#ifndef w3c_SVGAnimatedEnumerationT_h
#define w3c_SVGAnimatedEnumerationT_h

namespace System
{
namespace Web
{

template<class T>
class ValueHandlerT : public IValueHandler
{
public:
	virtual Object* Create() const
	{
		return new T;
	}
	virtual void ParseString(Object* value, StringIn str) const
	{
		ASSERT(0);
	}

	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t)
	{
		ASSERT(0);
	}

	static ValueHandlerT<T> s_valueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_valueHandler;
	}
};

template <class T> class SVGAnimatedEnumerationT :
	public Object,
	public ISVGAnimatedEnumeration
{
public:
	CTOR SVGAnimatedEnumerationT()
	{
		m_baseVal = new T;
		m_animVal = m_baseVal;
	}

	typedef T t_baseType;
	typedef ValueHandlerT<T> t_valueHandler;

//	CATXMLAttr* m_pAttr;

	int get_baseVal()
	{
		return GetAsInt(m_baseVal);
	}

	void set_baseVal(int baseVal)
	{
		ASSERT(0);
		/*
		m_baseVal = (T)baseVal;
		if (m_owner)
		{
			m_owner->BaseValChanged();
		}
		*/
	}

	int get_animVal()
	{
		return GetAsInt(m_animVal);
	}

	void SetAnimVal(T* value)
	{
		m_animVal = value;
		// TODO??
	}

	void SetBaseValAsString(StringIn str)
	{
		SetAsString(m_baseVal, str);
	}

	IAnimatedOwner<SVGAnimatedEnumerationT<T> >* m_owner;

	T* m_baseVal;
	T* m_animVal;
};

}	// Web
}

#endif // w3c_SVGAnimatedEnumerationT_h
