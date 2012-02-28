namespace System
{
namespace Gui
{

class GUIEXT DependencyProperty : public Object
{
public:

	CTOR DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, const Variant& defaultValue, PropertyMetadata* metadata = nullptr);
	CTOR DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, const Expressive::expression& exp, PropertyMetadata* metadata = nullptr);
	CTOR DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, decltype(nullptr), PropertyMetadata* metadata = nullptr);

	String get_Name()
	{
		return &m_name;
	}

	String ToString() override
	{
		return get_OwnerClass()->GetClassType()->get_QName() + "." + get_Name();
	}

	DependencyClass* get_OwnerClass();

	Expressive::Expression* get_Expression()
	{
		return m_exp;
	}

	Variant get_DefaultValue() const
	{
		return m_defaultValue;
	}

	const Type_Info& get_Type() const
	{
		return m_typeInfo;
	}

	Type* GetPropertyType() const;

	PropertyMetadata* get_Metadata()
	{
		return m_metadata;
	}

//	bool CheckValueType(Object* value);

// TODO protected
	int m_localIndex;
	int m_globalUid;

protected:

	void CheckDefaultValueType();

	ImmutableString<WCHAR> m_name;
	const Type_Info& m_typeInfo;
	DependencyClass* m_ownerClass;
	Variant m_defaultValue;
	Expressive::Expression* m_exp;
	PropertyMetadata* m_metadata;
};

template<class propertyType>
class TypedDependencyProperty : public DependencyProperty
{
public:
	typedef propertyType property_type;

	// no default value
	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name) :
		DependencyProperty(ownerClass, name, typeid(propertyType), Variant(), nullptr)
	{
	}

#ifndef __LERSTAD__
	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name, decltype(nullptr), PropertyMetadata* metadata = nullptr) :
		DependencyProperty(ownerClass, name, typeid(propertyType), nullptr, metadata)
	{
	}
#endif

	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name, propertyType defaultValue, PropertyMetadata* metadata = nullptr) :
		DependencyProperty(ownerClass, name, typeid(propertyType), Variant(defaultValue), metadata)
	{
	}

	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Expressive::typed_expression<propertyType>& exp, PropertyMetadata* metadata = nullptr) :
		DependencyProperty(ownerClass, name, typeid(propertyType), exp, metadata)
	{
	}
};

/*
#ifndef __LERSTAD__

template<> class TypedDependencyProperty<String> : public DependencyProperty
{
public:
	typedef StringObject* propertyType;

	// no default value
	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name) :
		DependencyProperty(ownerClass, name, typeid(propertyType), NULL, NULL)
	{
	}

	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name, propertyType defaultValue, PropertyMetadata* metadata = NULL) :
		DependencyProperty(ownerClass, name, typeid(propertyType), defaultValue, metadata)
	{
	}

	CTOR TypedDependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Expressive::typed_expression<propertyType>& exp, PropertyMetadata* metadata = NULL) :
		DependencyProperty(ownerClass, name, typeid(propertyType), exp, metadata)
	{
	}
};

#endif
*/

}	// Gui
}	// System
