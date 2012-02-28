#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyProperty::DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, const Variant& defaultValue, PropertyMetadata* metadata) :
	m_ownerClass(ownerClass),
	m_name(name),
	m_typeInfo(typeInfo),
	m_defaultValue(defaultValue),
	m_exp(nullptr),
	m_metadata(metadata)
{
	if (ownerClass == nullptr) raise(ArgumentNullException());

	CheckDefaultValueType();

//	DependencyClass* depClass = DependencyClass::GetClass(ownerClass.GetType()->GetClass());

	ownerClass->RegisterProperty(this);
}

DependencyProperty::DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, const Expressive::expression& exp, PropertyMetadata* metadata) :
	m_ownerClass(ownerClass),
	m_name(name),
	m_typeInfo(typeInfo),
	m_exp(exp.m_p),
	m_metadata(metadata)
{
	//if (ownerClass == NULL) throw new ArgumentNullException();

	CheckDefaultValueType();

	//DependencyClass* depClass = DependencyClass::GetClass(ownerClass.GetType()->GetClass());

	ownerClass->RegisterProperty(this);
}

DependencyProperty::DependencyProperty(DependencyClass* ownerClass, const WCHAR* name, const Type_Info& typeInfo, decltype(nullptr), PropertyMetadata* metadata) :
	m_ownerClass(ownerClass),
	m_name(name),
	m_typeInfo(typeInfo),
	m_defaultValue(nullptr),
	m_metadata(metadata)
{
	//if (ownerClass == NULL) throw new ArgumentNullException();

	CheckDefaultValueType();

	//DependencyClass* depClass = DependencyClass::GetClass(ownerClass.GetType()->GetClass());

	ownerClass->RegisterProperty(this);
}

Type* DependencyProperty::GetPropertyType() const
{
	if (m_typeInfo.GetType() == nullptr)
	{
		IO::StringWriter str;
		str << "Type NULL for typeInfo rawname " << m_typeInfo.raw_name();
		raise(Exception(str.str()));
	}
	return m_typeInfo.GetType();
}

DependencyClass* DependencyProperty::get_OwnerClass()
{
	return m_ownerClass;
}

#if 0
bool DependencyProperty::CheckValueType(Object* value)
{
	bool ok = false;

	if (value)
	{
		if (m_typeInfo == typeid(bool))
		{
			ok = value->GetType() == typeid(BoolObject);
		}
		else if (m_typeInfo == typeid(signed char))
		{
			VERIFY(0);
		}
		else if (m_typeInfo == typeid(unsigned char))
		{
			ok = value->GetType() == typeid(UByteObject);
		}
		else if (m_typeInfo == typeid(short))
		{
			VERIFY(0);
		}
		else if (m_typeInfo == typeid(unsigned short))
		{
			VERIFY(0);
		}
		else if (m_typeInfo == typeid(int))
		{
			ok = value->GetType() == typeid(IntObject);
		}
		else if (m_typeInfo == typeid(unsigned int))
		{
			ok = value->GetType() == typeid(UIntObject);
		}
		else if (m_typeInfo == typeid(int64))
		{
			ok = value->GetType() == typeof(LongIntObject);
		}
		else if (m_typeInfo == typeid(uint64))
		{
			VERIFY(0);
		}
		else if (m_typeInfo == typeid(float))
		{
			ok = value->GetType() == typeid(FloatObject);
		}
		else if (m_typeInfo == typeid(double))
		{
			ok = value->GetType() == typeid(DoubleObject);
		}
		else
		{
			if (m_typeInfo.GetType() == NULL)
			{
				MessageBox(NULL, CStringw(String("m_typeInfo.GetType() ") + m_typeInfo.raw_name()), L"Gui", MB_ICONERROR);
				if (true)
				{
					RaiseException(0, EXCEPTION_NONCONTINUABLE, 0, NULL);
				}

				raise(ArgumentException(String("Typeinfo '") + m_typeInfo.raw_name() + "' lacks Type, make sure the class has a constructor in a source file"));
				ASSERT(0);
			}

			if (m_typeInfo.GetType()->get_Kind() == type_pointer && m_typeInfo.GetType()->GetPointerTo()->get_Kind() == type_class)
			{
				if (m_defaultValue != NULL)
				{
					ok = value->GetType()->IsDerivedFrom(m_typeInfo.GetType()->GetPointerTo()->GetClass());
				}
				else
					ok = true;
			}
			else if (m_typeInfo.GetType()->get_Kind() == type_enum)
			{
				// TODO
				ok = true;
			}
			else
			{
				ASSERT(0);
			}
		}

		return ok;
	}

	return true;
}
#endif

void DependencyProperty::CheckDefaultValueType()
{
	if (m_exp == nullptr)
	{
		/*
		bool ok = CheckValueType(m_defaultValue);
		if (!ok)
		{
			raise(ArgumentException(L"DependencyProperty Default value is not of correct type"));
			ASSERT(0);
		}
		*/
	}
}

}	// Gui
}	// System
