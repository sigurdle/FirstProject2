namespace System
{
namespace Gui
{

class GUIEXT DependencyObject : public DispatcherObject
{
protected:

	CTOR DependencyObject(DependencyClass* depClass);

public:

	Variant GetComputedValue(DependencyProperty* dp);

	virtual bool HasComputedPropertyValue(DependencyProperty* dp);
	virtual Variant GetComputedPropertyObjectValue2(DependencyProperty* dp);

	virtual bool HasLocalPropertyValue(PropertyValue* pPropertyVal);
	virtual Variant GetLocalPropertyValue(PropertyValue* pPropertyVal);
	virtual void ClearLocalPropertyValue(PropertyValue* pPropertyVal);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled);
	virtual void OnComputedPropertyValueChanging(PropertyValue* pPropertyVal, const Variant& oldValue, const Variant& newValue, bool handled);

	PropertyValue* GetProperty(DependencyProperty* dp);
	PropertyValue* GetExistingProperty(DependencyProperty* dp);

	Variant GetPropertyValue(DependencyProperty* dp);

	bool GetPropertyValueBool(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	unsigned char GetPropertyValueUByte(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	int GetPropertyValueInt(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	float GetPropertyValueFloat(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	double GetPropertyValueDouble(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	template<class T>
	T GetPropertyValueT(DependencyProperty* dp)
	{
		return GetPropertyValue(dp);
	}

	template<class T>
	void SetPropertyValue(DependencyProperty* dp, T* value)
	{
		SetPropertyValue(dp, Variant(value));
	}

	template<class T>
	void SetPropertyValue(DependencyProperty* dp, T value)
	{
		SetPropertyValue(dp, Variant(value));
	}

	void ClearPropertyValue(DependencyProperty* dp);

	void SetPropertyValue(DependencyProperty* dp, const Variant& value);
	void SetPropertyValue(DependencyProperty* dp, String value);

	void UpdatePropertyObjectValue(DependencyProperty* dp, const Variant& value);

	void SetPropertyBinding(DependencyProperty* dp, IBinding* binding)
	{
		GetProperty(dp)->SetInputBinding(binding);
	}

	template<class T> void UpdatePropertyValue(DependencyProperty* dp, T value)
	{
		UpdatePropertyObjectValue(dp, Variant(value));
	}

	virtual String ToString() override;
	String ToMLString();
	virtual IO::TextWriter& WriteMLString(IO::TextWriter& stream, map<Object*,int>& defs);

	void AddNotify(IObjectChangedNotify* callback);

	DependencyClass* GetClass();
	typedef DependencyObject thisClass;

	static DependencyClass* get_Class();

private:

	array<PropertyValue*> m_localProperties;
	map<int, PropertyValue*> m_attachedProperties;

	list<IObjectChangedNotify*> m_notifyList;

private:

	void CreateProperties(DependencyClass* depClass);
};

class GUIEXT _DependencyObject : public Expressive::_Object
{
public:
	CTOR _DependencyObject(const Expressive::expression& exp) : Expressive::_Object(exp)
	{
	}

	Expressive::expression getProperty(DependencyProperty* dp) const
	{
		return new GetDPByDPExpression(m_p, dp);
	}

#ifndef __LERSTAD__
	template<class T> Expressive::typed_expression<T> getProperty(TypedDependencyProperty<T>* dp) const
	{
		return new GetDPByDPExpression(m_p, dp);
	}
#endif
};

}	// Gui
}	// System
