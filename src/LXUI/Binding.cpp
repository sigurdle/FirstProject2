#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{
namespace Data
{

RoutedEvent* Binding::s_SourceUpdatedEvent = EventManager::RegisterRoutedEvent(WSTR("SourceUpdated"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, DataTransferEventArgs*>), typeid(Binding));
RoutedEvent* Binding::s_TargetUpdatedEvent = EventManager::RegisterRoutedEvent(WSTR("TargetUpdated"), RoutingStrategy_Bubble, typeid(stub_interface2<void, Object*, DataTransferEventArgs*>), typeid(Binding));

Binding::Binding()
{
}

Object* Binding::get_Source()
{
	return m_source;
}

void Binding::set_Source(Object* source)
{
	m_source = source;
}

PropertyPath* Binding::get_Path()
{
	return m_path;
}

void Binding::set_Path(PropertyPath* path)
{
	m_path = path;
}

bool Binding::get_NotifyOnSourceUpdated()
{
	return m_notifyOnSourceUpdated;
}

void Binding::set_NotifyOnSourceUpdated(bool notify)
{
	m_notifyOnSourceUpdated = notify;
}

bool Binding::get_NotifyOnTargetUpdated()
{
	return m_notifyOnTargetUpdated;
}

void Binding::set_NotifyOnTargetUpdated(bool notify)
{
	m_notifyOnTargetUpdated = notify;
}

//

PropertyPath::PropertyPath(StringW* path)
{
	/*
	if (*path == L"Adjustment")
	{
		MessageBeep(-1);
	}
	*/

	m_parsedPath = new PropertyName(path);
}

StringW* PropertyPath::get_Path()
{
	if (*m_parsedPath->m_name == L"Adjustment")
	{
		MessageBeep(-1);
	}

	return m_parsedPath->m_name;
}

void PropertyPath::set_Path(StringW* path)
{
	ASSERT(0);
}

//

void BindingExpressionBase::UpdateSource()
{
}

void BindingExpressionBase::UpdateTarget()
{
}

#if 0
Binding::Binding()
{
	m_recursive = 0;
}

StringA* Binding::get_Path()
{
	return m_Path;
}

void Binding::set_Path(StringA* strpath)
{
	m_Path = strpath;
}

union Value
{
	long m_long32;
	double m_float64;
	struct
	{
		int size;
		uint8* data;
	}
	object;
};

void Transfer(Object* sourceObject, Property* sourceProperty, Object* targetObject, Property* targetProperty)
{
	Type* pReturnType = sourceProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
	pReturnType = pReturnType->GetStripped();

#if WIN32
	void * _this = NULL;//__RTDynamicCast(sourceObject, 0, (void*)&typeid(sourceObject), (void*)sourceProperty->get_method->GetTypeInfo(), 0);
	ASSERT(0);
#else
	void * _this = NULL;
	VERIFY(0);
#endif

	ULONG_PTR func;
	if (sourceProperty->get_method->m_decl->m_offset != -1)
	{
		void* vtable = *(void**)_this;
		func = *(ULONG_PTR*)((uint8*)vtable + sourceProperty->get_method->m_decl->m_offset);
	}
	else
	{
		func = sourceProperty->get_method->m_func;
	}

	Value value;

#if WIN32
	switch (pReturnType->get_Kind())
	{
		case type_long_int:
		{
			//EditView* pView = new EditView(pProperty, obj);
			long _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				mov _result,eax
				pop ecx
			}

			/*
			WCHAR buf[64];
			swprintf(buf, L"%d", _result);
			pView->m_edit->put_Text(buf);
			//row->AppendColumnCell(visual);
			twoViews.smallView = pView;
			*/
			value.m_long32 = _result;
		}
		break;

		case type_long_long:
		{
			long _result0;
			long _result1;

			__asm
			{
				push eax
				push edx
				push ecx
				mov ecx,_this
				call func
				mov _result0,eax
				mov _result1,edx
				pop ecx
				pop edx
				pop eax
			}

			LONGLONG result64 = _result0 | (LONGLONG)_result1<<32;

			//var = Variant(VARKIND_INT64, result64);
#if 0
			EditView* pView = new EditView(pProperty, obj);

			WCHAR buf[64];
#if WIN32
			swprintf(buf, L"%I64d", result64);
#else
			swprintf(buf, L"%uld", _result0);
#endif
			//if (pProperty->put_decl)
			{
				pView->m_edit->put_Text(buf);

				twoViews.smallView = pView;
			}
			/*
			else
			{
				static_cast<UI::TextString*>(visual)->put_TextContent(buf);
			}
			*/
#endif
		}
		break;

		case type_double:
		{
			double _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				fstp qword ptr [_result]
				pop ecx
			}

			value.m_float64 = _result;
		}
		break;

		case type_class:
		{
			int size = pReturnType->get_sizeof();
			uint8* data = new uint8[size];

			__asm
			{
				push ecx
				mov ecx,_this
				push data
				call func
				pop ecx
			}

			value.object.size = size;
			value.object.data = data;
			/*
			if (pReturnType->GetClass()->m_name == "StringW")
			{
				pComparable = new FileTimeObject((_FILETIME*)object);
			}
			*/

			//delete[] object;
		}
		break;
#if 0
		case type_enum:
		{
			EnumView* pView = new EnumView(pProperty, obj);
			//UI::CLXUIMenuElement* pMenu = new UI::CLXUIMenuElement(new UI::TextString(WSTR("")));

			Enum* pEnum = pProperty->get_decl->m_pType->m_pFunction->m_pReturnType->m_pEnum;

			for (int i = 0; i < pEnum->m_deflist.size(); i++)
			{
				const EnumDef& enumDef = pEnum->m_deflist[i];
				pView->m_menu->AddItem(new UI::TextString(ConvertA2S(enumDef.m_name)), enumDef.m_value);
			}

			twoViews.smallView = pView;

			long _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				mov _result,eax
				pop ecx
			}

		//	WCHAR buf[64];
		//	swprintf(buf, L"%d", _result);
		//	static_cast<UI::CLXUIMenuPopupElement*>(visual)->put_Text(buf);
#if 0
			row->AppendColumnCell(visual);
#endif
		}
		break;
#endif
	}

	{
		Type* pTargetType = targetProperty->set_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0].m_pType;
		pTargetType = pTargetType->GetStripped();

		ASSERT(0);
		void*_this = NULL;//__RTDynamicCast(targetObject, 0, (void*)&typeid(targetObject), (void*)targetProperty->set_method->GetTypeInfo(), 0);

		ULONG_PTR func;
		if (targetProperty->set_method->m_decl->m_offset != -1)
		{
			void* vtable = *(void**)_this;
			func = *(ULONG_PTR*)((uint8*)vtable + targetProperty->set_method->m_decl->m_offset);
		}
		else
		{
			func = targetProperty->set_method->m_func;
		}

		switch (pTargetType->get_Kind())
		{
		case type_double:
			{
				if (pReturnType->get_Kind() == type_class && *pReturnType->GetClass()->m_qname == "System::StringW")
				{
					StringW* pString = (StringW*)value.object.data;

					double value = getfnumber(pString->c_str());
					long v0 = (*(__int64*)&value) >> 32;
					long v1 = (*(__int64*)&value) & 0xFFFFFFFF;

					__asm
					{
						push ecx
						mov ecx,_this
						push v0
						push v1
						call func
						pop ecx
					}
				}
				else
					ASSERT(0);
			}
			break;

		case type_class:
			{
				int sz = pTargetType->get_sizeof();

				if (*pTargetType->GetClass()->m_qname == "System::StringA")
				{
					ASSERT(0);
#if 0
					StringA str;
					if (pReturnType->m_type == type_double)
					{
						char buf[64];
						sprintf(buf, "%g", value.m_float64);
						str = buf;
					}
					else
						ASSERT(0);

					//	StringW str = static_cast<UI::TextEdit*>(m_edit)->get_Text();

						//UI::Length length(value);
					void* object = &str;

					/*
					if (false)
					{
						reinterpret_cast<UI::IVisualChild*>(_this)->put_Height(length);
					}
					*/
					__asm
					{
						push ecx
						push esi
						push edi

						mov   ecx, sz       // get size of buffer
						mov   esi, object     // get buffer
						sub   esp, ecx      // allocate stack space
						mov   edi, esp      // start of destination stack frame
						shr   ecx, 2        // make it dwords
						rep   movsd         // copy params to real stack

						mov ecx,_this
						call func

						pop edi
						pop esi
						pop ecx
					}

					str.Detach();
#endif
				}
				else if (*pTargetType->GetClass()->m_qname == "System::StringW")
				{
					ASSERT(0);
#if 0
					StringW str;
					if (pReturnType->m_type == type_long_int)
					{
						WCHAR buf[64];
						swprintf(buf, L"%ld", value.m_long32);
						str = buf;
					}
					else if (pReturnType->m_type == type_double)
					{
						WCHAR buf[64];
						swprintf(buf, L"%g", value.m_float64);
						str = buf;
					}
					else
						ASSERT(0);

					//	StringW str = static_cast<UI::TextEdit*>(m_edit)->get_Text();

						//UI::Length length(value);
					void* object = &str;

					/*
					if (false)
					{
						reinterpret_cast<UI::IVisualChild*>(_this)->put_Height(length);
					}
					*/
					__asm
					{
						push ecx
						push esi
						push edi

						mov   ecx, sz       // get size of buffer
						mov   esi, object     // get buffer
						sub   esp, ecx      // allocate stack space
						mov   edi, esp      // start of destination stack frame
						shr   ecx, 2        // make it dwords
						rep   movsd         // copy params to real stack

						mov ecx,_this
						call func

						pop edi
						pop esi
						pop ecx
					}

					str.Detach();
#endif
				}
				else
					ASSERT(0);
			}
			break;
		}
	}
#endif
}

void Binding::OnSourceChanged()
{
	if (m_recursive == 0)
	{
		m_recursive++;
		/*
		if (false)
			Transfer(targetObject, targetProperty, sourceObject, sourceProperty);
		else
		*/
		{
			Dispatch* dispatch = GetDispatch(sourceObject->GetType());
		//	Dispatch::propertymap_t properties;
		//	dispatch->GetProperties(properties);

			Property* sourceProperty = dispatch->GetProperty(m_Path);//properties[m_Path];

			Transfer(sourceObject, sourceProperty, targetObject, targetProperty);
		}

		m_recursive--;
	}
}

void Binding::handleEvent(System::Event* evt)
{
	OnSourceChanged();
}
#endif

}	// Data
}	// UI
}	// System
