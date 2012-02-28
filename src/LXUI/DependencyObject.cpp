#include "stdafx.h"
#include "LXUI2.h"
#include "DependencyObject.h"

#include "SolidColorBrush.h"	// TODO remove

//#include <functional>

//using namespace System;

namespace System
{
namespace UI
{

DepState* depstate;

//static int gindex = 0;
//std::vector<DependencyProperty*> g_dependencyProperties;
//static __live_object_ptr<DependencyProperty> g_dependencyProperties[256];// = new __live_object_ptr<DependencyProperty>[256];

UIEXT unsigned int GetPropertyCount()
{
	return depstate->gindex;
}

UIEXT DependencyProperty* GetProperty(unsigned int index)
{
	ASSERT(depstate);

	if (index >= depstate->gindex)
	{
		ASSERT(0);
		return NULL;
	}

	return depstate->g_dependencyProperties[index];
}

UIEXT DependencyProperty* GetProperty(ClassType* ownerType, StringW* name)
{
	unsigned int count = depstate->g_dependencyProperties.size();
	for (unsigned int i = 0; i < count; i++)
	{
		DependencyProperty* p = depstate->g_dependencyProperties[i];
		ASSERT(p);

		if (p->m_ownerType.GetType())	// TODO remove this test
		{
			if (ownerType->IsDerivedFrom(p->m_ownerType.GetType()->GetClass()) && *name == *depstate->g_dependencyProperties[i]->m_name)
				return depstate->g_dependencyProperties[i];
		}
	}
	return NULL;
}

UIEXT DependencyProperty* GetProperty(StringW* name)
{
	for (unsigned int i = 0; i < depstate->g_dependencyProperties.size(); i++)
	{
		if (*name == *depstate->g_dependencyProperties[i]->m_name)
			return depstate->g_dependencyProperties[i];
	}
	return NULL;
}

UIEXT int GetPropertyIndex(StringW* name)
{
	for (int i = 0; i < (int)depstate->g_dependencyProperties.size(); i++)
	{
		if (*name == *depstate->g_dependencyProperties[i]->m_name)
			return i;
	}
	return -1;
}

//__live_object_ptr<Object> UnsetValue = new Object;

#if 0
class Local
{
public:
	multimap<StringA*,DependencyProperty*, Ref_Less<StringA>, __gc_allocator> m_localProperties;
};

Local* plocal;
#endif

#if 0
UIEXT DependencyProperty* RegisterProperty(StringW* name, const Type_Info& propertytype, const Type_Info& classtype)
{
	TRACE("RegisterProperty() TODO\n");

//	ASSERT(0);
#if 0
	DependencyProperty* pProperty = new DependencyProperty(propertytype);
	pProperty->m_name = name;
	//pProperty->gindex = gindex;
//	pProperty->m_defaultValue = defaultValue;
//	pProperty->m_bInherits = bInherits;

	if (plocal == NULL)
		plocal = new Local;

	plocal->m_localProperties.insert(/*plocal->m_localProperties.begin(),*/ multimap<StringA*,DependencyProperty*>::value_type(classtype.name(), pProperty));
	return pProperty;
#endif
	return NULL;
}
#endif

UIEXT DependencyProperty* RegisterAttached(StringW* name, const Type_Info& type, const Type_Info& ownerType, Object* defaultValue, const PropertyMetaData& metadata)
{
	// TODO, different

	return RegisterProperty(name, type, ownerType, defaultValue, metadata);
}

UIEXT DependencyProperty* RegisterProperty(StringW* name, const Type_Info& type, const Type_Info& ownerType, Object* defaultValue, const PropertyMetaData& metadata)
{
	TRACE("RegisterProperty...%s\n", name->ToStringA()->c_str());

	if (depstate == NULL)
	{
		depstate = new DepState;
		AddPersistentLiveRoot((void**)&depstate);
	}
	ASSERT(depstate);
	ASSERT(depstate->gindex < 256);

	DependencyProperty* pProperty = new DependencyProperty(type, ownerType, metadata);
	pProperty->m_name = name;
	pProperty->gindex = depstate->gindex;
	pProperty->m_defaultValue = defaultValue;
	//pProperty->m_bInherits = bInherits;

//	g_dependencyProperties.push_back(pProperty);

	depstate->g_dependencyProperties.push_back(pProperty);

	depstate->gindex++;

	//ASSERT(g_dependencyProperties.size() == gindex);

//	printf("done\n");

	return pProperty;
}

//SolidColorBrush* brush;

#if 0

template<class F> class binder1_1st_t
{
public:
	CTOR binder1_1st_t(const F& f, typename F::argument1_type arg1) : m_f(f), m_arg1(arg1)
	{
	}

	void operator () (typename F::argument2_type arg2, typename F::argument3_type arg3) const
	{
		m_f(m_arg1, arg2, arg3);
	}

	F m_f;
	typename F::argument1_type m_arg1;
};

#ifndef __LERSTAD__	// TODO remove
template<class F> function2<typename F::argument2_type, typename F::argument3_type> bind1_1st(F f, typename F::argument1_type arg1)
{
	return binder1st_t<F>(f, arg1);
}
#endif

#endif

DependencyObject::DependencyObject()
{
	ASSERT(depstate);

	/*
	if (depstate == NULL)
	{
		 depstate = new DepState;
	}
	*/

//	ASSERT(UnsetValue != NULL);

//	printf("DependencyObject::DependencyObject() gindex=%d\n", depstate->gindex);

	m_isValidProperties.resize(depstate->gindex);
	m_computedProperties.resize(depstate->gindex);
	m_specifiedProperties.resize(depstate->gindex);
	m_deps.resize(depstate->gindex);

	m_dp_connections.resize(depstate->gindex);

	m_depPropertyChangedHandlers.resize(depstate->gindex);

	m_bindings.resize(depstate->gindex);

	m_isDpSetting.resize(depstate->gindex);

	//int i = 0;
//	std::vector<DependencyProperty*>::iterator it = g_dependencyProperties.begin();
//	while (it != g_dependencyProperties.end())
	for (int i = 0; i < depstate->gindex; i++)
	{
		DependencyProperty* pProperty = depstate->g_dependencyProperties[i];

		m_specifiedProperties[i] = DependencyProperty::get_UnsetValue();//ComputeProperty(pProperty);

		// Hack
		if (pProperty->m_defaultValue == (Object*)1)
		{
			pProperty->m_defaultValue = NULL;
			pProperty->m_defaultValue = new SolidColorBrush(Color::FromRgb(0,0,0));
		}

	//	DependencyProperty* pProperty = g_dependencyProperties[i];//*it;
		if (true)	// ??
		{
			m_computedProperties[i] = pProperty->m_defaultValue;
			m_isValidProperties[i] = true;

			// listen to Freezable ?

			Freezable* p = dynamic_cast<Freezable*>(m_computedProperties[i]);
			if (p)
			{
			//	m_dp_connections[pProperty->gindex] = p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this));
				m_dp_connections[pProperty->gindex] = p->ChangedSignal.connect(bind1st_of_2(mem_fun(&DependencyObject::OnChanged), this));
			}
		}
		else
			m_computedProperties[i] = DependencyProperty::get_UnsetValue();//ComputeProperty(pProperty);

	//	ASSERT(m_specifiedProperties[i] == NULL);

		/*
		if (pProperty->m_defaultValue)
		{
			m_computedProperties[pProperty->gindex] = pProperty->m_defaultValue;
		}
		else
		{
			m_computedProperties[pProperty->gindex] = NULL;
		}
		*/
	//	i++;
	//	it++;
	}

	m_font = NULL;

//	printf("done\n");
}

DependencyObject::~DependencyObject()
{
	;//new test;
}

DependencyObjectType* DependencyObject::get_DependencyObjectType()
{
	DependencyObjectType* p = static_cast<DependencyObjectType*>(GetType()->m_classUserData[0]);

	return p;
}

#if 1
// virtual
void DependencyObject::OnChanged(Object* object)
{
	// A subobject has changed

	// Act like the property itself has changed

	for (int i = 0; i < m_computedProperties.size(); i++)
	{
		if (m_computedProperties[i] == object)
		{
#if 1
			DependencyPropertyChangedEventArgs args;
			args.m_property = depstate->g_dependencyProperties[i];
			args.m_newValue = object;
			args.m_oldValue = object;

			OnPropertyChanged(args);
#endif
		}
	}

}
#endif

/*
	Object* DependencyObject::ComputeProperty(DependencyProperty* pProperty)
	{
		return NULL;
	}
*/

/*
void DependencyObject::ComputeProperties()
{
}
*/

Object* DependencyObject::ReadLocalValue(DependencyProperty* pProperty)
{
	return m_specifiedProperties[pProperty->gindex];
}

#if 0
void DependencyObject::AddObserver(INotifiable* observer)
{
//	printf("AddObserver %x %x\n", this, observer);
	m_observers.push_back(observer);
}

void DependencyObject::RemoveObserver(INotifiable* observer)
{
	printf("RemoveObserver %x %x\n", this, observer);

	for (int i = 0; i < m_observers.size(); i++)
	{
		if (m_observers[i] == observer)
		{
			m_observers.RemoveAt(i);
			return;
		}
	}

	ASSERT(0);
}
#endif

void DependencyObject::ValidateValue(DependencyProperty* pProperty, Object* pValue)
{
	if (pProperty->m_type == typeid(bool))
	{
	//	printf("typeid bool\n");

		if (pValue)
		{
			if (dynamic_cast<BoolObject*>(pValue) == NULL)
			{
				ASSERT(0);
			}
		}
	}
	else if (pProperty->m_type == typeid(int))
	{
	//	printf("typeid int\n");

		if (pValue)
		{
			if (dynamic_cast<IntObject*>(pValue) == NULL)
			{
				ASSERT(0);
			}
		}
	}
	else if (pProperty->m_type == typeid(unsigned int))
	{
	//	printf("typeid unsigned int\n");

		if (pValue)
		{
			if (dynamic_cast<IntObject*>(pValue) == NULL)
			{
				ASSERT(0);
			}
		}
	}
	else if (pProperty->m_type == typeid(float))
	{
		if (pValue)
		{
			if (dynamic_cast<FloatObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(double))
	{
	//	printf("typeid double\n");

		if (pValue)
		{
			if (dynamic_cast<DoubleObject*>(pValue) == NULL)
			{
				ASSERT(0);
			}
		}
	}
	else
	{
		if (pProperty->m_type.GetType())	// TODO, remove this test, could currently happen if we get here before types have been loaded
		{
			ASSERT(pProperty->m_type.GetType());
		//	printf("%s\n", ((NamedType*)pProperty->m_type.GetType())->m_qname->c_str());

			if (pProperty->m_type.GetType()->get_Kind() == type_enum)
			{
				if (pValue)
				{
					if (dynamic_cast<IntObject*>(pValue) == NULL)
					{
						ASSERT(0);
					}
				}
			}
		}
	}
}

Object* DependencyObject::GetValue(DependencyProperty* pProperty)
{
	ASSERT(m_computedProperties[pProperty->gindex] != DependencyProperty::get_UnsetValue());

	if (!m_isValidProperties[pProperty->gindex])
//	if (m_computedProperties[pProperty->gindex] == DependencyProperty::get_UnsetValue())
	{
		InvalidateProperty(pProperty);	// ??

#if 0
		Object* pValue = ComputeProperty(pProperty);
		ValidateValue(pProperty, pValue);

		Freezable* p = dynamic_cast<Freezable*>(pValue);
		if (p)
		{
		//	connections_type::iterator it = m_connections.find(p);
		//	if (p == m_connections.end())
			{
			//	mem_fun(&DependencyObject::OnChanged);

				m_dp_connections[pProperty->gindex] = p->ChangedSignal.connect(bind1st_of_2(mem_fun(&DependencyObject::OnChanged), this));
			//	m_dp_connections[pProperty->gindex] = p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this));

				//	m_connections.insert(connections_type::value_type(p, p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this))));
			}
	//		p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this));
		}

		m_isValidProperties[pProperty->gindex] = true;
		m_computedProperties[pProperty->gindex] = pValue;
#endif
	}

	return m_computedProperties[pProperty->gindex];
}

// Sets the local value
void DependencyObject::SetValue(DependencyProperty* pProperty, Object* pValue)
{
//	printf("DependencyObject::SetValue:%x:(%s(index: %d), %x)\n", this, pProperty->m_name->ToStringA()->c_str(), pProperty->gindex, pValue);

	if (pProperty->m_type == typeid(bool))
	{
		if (pValue)
		{
			if (dynamic_cast<BoolObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(signed char))
	{
		// TODO
		ASSERT(0);
	}
	else if (pProperty->m_type == typeid(unsigned char))
	{
		if (pValue)
		{
			if (dynamic_cast<UByteObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(int))
	{
		if (pValue)
		{
			if (dynamic_cast<IntObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(unsigned int))
	{
		if (pValue)
		{
			if (dynamic_cast<IntObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(float))
	{
		if (pValue)
		{
			if (dynamic_cast<FloatObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else if (pProperty->m_type == typeid(double))
	{
		if (pValue)
		{
			if (dynamic_cast<DoubleObject*>(pValue) == NULL)
			{
				ASSERT(0);
				throw new Exception(WSTR("Invalid argument"));
			}
		}
	}
	else
	{
		if (pProperty->m_type.GetType())	// TODO, remove this test, could currently happen if we get here before types have been loaded
		{
			ASSERT(pProperty->m_type.GetType());
		//	printf("%s\n", ((NamedType*)pProperty->m_type.GetType())->m_qname->c_str());

			if (pProperty->m_type.GetType()->get_Kind() == type_enum)
			{
			//	printf("enum\n");

				if (pValue)
				{
					if (dynamic_cast<IntObject*>(pValue) == NULL)
					{
						ASSERT(0);
						throw new Exception(WSTR("Invalid argument"));
					}
				}
			}
			else
			{
			//	printf("class or typedef\n");
			}
		}
	}

	// If the new value is the same as the one already set, just return
	if (m_specifiedProperties[pProperty->gindex] == pValue)
		return;

	Object* prevSpecifiedValue = m_specifiedProperties[pProperty->gindex];

	/*
	{
		DependencyObject* p = dynamic_cast<DependencyObject*>(m_computedProperties[pProperty->gindex]);
		if (p)
		{
			p->RemoveObserver(this);
		}
	}
	*/

	m_specifiedProperties[pProperty->gindex] = pValue;
//	m_computedProperties[pProperty->gindex] = pValue;

	InvalidateProperty(pProperty);

	/*
	{
		DependencyObject* p = dynamic_cast<DependencyObject*>(m_computedProperties[pProperty->gindex]);
		if (p)
		{
			p->AddObserver(this);
		}
	}
	*/

	if (pProperty->m_metadata.m_handler)
	{
		pProperty->m_metadata.m_handler->OnChanged(this, pProperty, prevSpecifiedValue, pValue);
	}

	/*
		{
			for (int i = 0; i < depstate->g_dependencyProperties.size(); i++)
			{
				printf("%s, %d\t", depstate->g_dependencyProperties[i]->m_name->ToStringA()->c_str(), depstate->g_dependencyProperties[i]->gindex);
				if (m_specifiedProperties[i] != NULL)
				{
					if (m_specifiedProperties[i] != UnsetValue)
						printf("0x%x, %s,%s", m_specifiedProperties[i], m_specifiedProperties[i]->GetType()->m_qname->c_str(), typeid(*m_specifiedProperties[i]).name());
					else
						printf("--UnsetValue--");
				}
				else
					printf("null");

				printf(", ");

				if (m_computedProperties[i] != NULL)
				{
					if (m_computedProperties[i] != UnsetValue)
						printf("0x%x, %s,%s", m_computedProperties[i], m_computedProperties[i]->GetType()->m_qname->c_str(), typeid(*m_computedProperties[i]).name());
					else
						printf("--UnsetValue--");
				}
				else
					printf("null");

				fprintf(stdout, "\n");
			}
		}
		*/

	// TODO animations ??

	/*
	// TODO !!!! not like this
	if (dynamic_cast<UIElement*>(this))
	{
		dynamic_cast<UIElement*>(this)->InvalidateMeasure();
	}
	*/

	/*
	// Clear the dependant (those that inherits this value), so that they're recalculated the next time they're asked for

	list<DependencyObject*>::iterator it = m_deps[pProperty->gindex].begin();
	while (it != m_deps[pProperty->gindex].end())
	{
		(*it)->InvalidateProperty(pProperty);
		++it;
	}
	*/

#if 0
	for (int i = 0; i < m_attachedProperties.GetSize(); i++)
	{
		if (m_attachedProperties[i]->m_Property == property)
		{
			m_attachedProperties[i]->m_Value = newVal;
			return S_OK;
		}
	}

	CAttachedProperty* p = new CAttachedProperty;
	p->m_Property = property;
	p->m_Value = newVal;

	m_attachedProperties.Add(p);

	return S_OK;
#endif
}

DependencyObject::DepCookie* DependencyObject::AddDependant(DependencyProperty* pProperty, DependencyObject* object)
{
	DepCookie* cookie = new DepCookie;
	cookie->m_it = m_deps[pProperty->gindex].insert(m_deps[pProperty->gindex].end(), object);
	return cookie;
}

void DependencyObject::RemoveDependant(DependencyProperty* pProperty, DepCookie* cookie)
{
	m_deps[pProperty->gindex].erase(cookie->m_it);
	delete cookie;
}

/*
void DependencyObject::InvalidateOnlyProperty(DependencyProperty* pProperty)
{
}
*/

// Re-evaluate the effective value
void DependencyObject::InvalidateProperty(DependencyProperty* dp)
{
	Object* oldValue = m_computedProperties[dp->gindex];

	ASSERT(oldValue != DependencyProperty::get_UnsetValue());
	/*
	if (oldValue == DependencyProperty::get_UnsetValue())	// Can only happen once
	{
		oldValue = ComputeProperty(pProperty);
		ValidateValue(pProperty, oldValue);
	}
	else
	// ??
	//if (oldValue != DependencyProperty::get_UnsetValue())
	{
#if 0
		Freezable* p = dynamic_cast<Freezable*>(oldValue);
		if (p)
		{
			p->ChangedSignal.disconnect(m_connections.find(p)->second);
		}
#endif
		m_computedProperties[pProperty->gindex] = DependencyProperty::get_UnsetValue();
	}
	*/
	//m_computedProperties[pProperty->gindex] = DependencyProperty::get_UnsetValue();

	Object* newValue = ComputeProperty(dp);
	ValidateValue(dp, newValue);

#if 0
		Freezable* p = dynamic_cast<Freezable*>(newVal);
		if (p)
		{
			m_connections.insert(connections_type::value_type(p, p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this))));
		//	p->ChangedSignal.connect(std::bind1st(std::mem_fun1(&DependencyObject::OnChanged), this));
		}
#endif
	m_isValidProperties[dp->gindex] = true;
	m_computedProperties[dp->gindex] = newValue;

	DependencyPropertyChangedEventArgs args;
	args.m_property = dp;
	args.m_newValue = newValue;
	args.m_oldValue = oldValue;

	OnPropertyChanged(args);	// The effective value has changed

	list<DependencyObject*>::iterator it = m_deps[dp->gindex].begin();
	while (it != m_deps[dp->gindex].end())
	{
		(*it)->InvalidateProperty(dp);
		++it;
	}

	Data::BindingExpression* bindingExp = m_bindings[dp->gindex];
	if (bindingExp)
	{
		// Update source

		// TODO, hm.. check that the source didn't initiate the property change

		Data::PropertyPath* path = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Path();
		Object* source = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Source();

		Dispatch* dispatch = GetDispatch(source->GetType());

		Property* prop = dispatch->GetProperty(path->get_Path()->ToStringA());

		if (prop->get_SetMethod())
		{
			dispatch->SetValue(source, prop->get_SetMethod(), newValue, NULL/*Types::type_double*/);
		}
	}
}

// virtual
void DependencyObject::OnPropertyChanged(DependencyPropertyChangedEventArgs args)	// The effective value has changed
{
	m_depPropertyChangedHandlers[args.get_Property()->gindex](this, args);

#if 0
	for (int i = 0; i < m_observers.size(); i++)
	{
		m_observers[i]->OnChanged(this);
	}
#endif
}

DependencyObject* DependencyObject::GetDependencyParent()
{
	return NULL;
}

// Clears the local value
void DependencyObject::ClearValue(DependencyProperty* pProperty)
{
	if (m_specifiedProperties[pProperty->gindex] != DependencyProperty::get_UnsetValue())
	{
		m_specifiedProperties[pProperty->gindex] = DependencyProperty::get_UnsetValue();

		InvalidateProperty(pProperty);
	}

//	OnPropertyChanged(pProperty);	//
}

Object* DependencyObject::ComputeProperty(DependencyProperty* pProperty)
{
//	DependencyObject* pParent;

	if (m_specifiedProperties[pProperty->gindex] != DependencyProperty::get_UnsetValue())
	{
		/*
		if (m_depCookies[pProperty->gindex] != NULL)
		{
			pParent = GetDependencyParent();

			pParent->RemoveDependant(pProperty, m_depCookies[pProperty->gindex]);
			m_depCookies[pProperty->gindex] = NULL;
		}
		*/

		return m_specifiedProperties[pProperty->gindex];
	}
	/*
	else if ((pProperty->m_metadata.m_flags & ChildInherits) && (pParent = GetDependencyParent()) != NULL)
	{
		if (m_depCookies[pProperty->gindex] == NULL)
			m_depCookies[pProperty->gindex] = pParent->AddDependant(pProperty, this);

		return pParent->ComputeProperty(pProperty);
	}
	else
	*/
	{
		return pProperty->m_defaultValue;
	}
}

}	// UI
}
