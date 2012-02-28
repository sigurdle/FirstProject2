#include "stdafx.h"
#include "Browser.h"
#include "Properties.h"
#include "ViewOfCollection2.h"

namespace System
{

Properties::PropertyListener::PropertyListener(Property* pProperty, Object* itemVisual)
{
	m_pProperty = pProperty;
	m_itemVisual = itemVisual;
	m_ctledit = NULL;
	m_bDisplayAsTable = false;
}

#if 0
// virtual
void Properties::PropertyListener::handleEvent(System::Event* evt)
{
#if WIN32
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = static_cast<UI::MouseEvent*>(evt);

			UI::CLXUIMenuElement* menu = new UI::CLXUIMenuElement();
		//	menu->SetRParent(m_ctledit);
			menu->SetOwnerWindow(mouseEvt->GetOwnerWindow());

			menu->addEventListener(WSTR("command"), this, false);

			if (false)
			{
				menu->AddItem(new UI::TextString(WSTR("Display As Table")), 100);
			}
			else
			{
				Type* pType = m_pProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;

				if (pType->get_Kind() == type_pointer && pType->GetPointerTo()->get_Kind() == type_class)
				{
					vector<ClassType*> list;
					GetDerived(pType->GetPointerTo()->GetClass(), list);

					for (int i = 0; i < list.GetSize(); i++)
					{
						ClassType* pDerived = list[i];
						if (pDerived->m_derived.GetSize() == 0)
						{
							menu->AddItem(new UI::TextString(pDerived->get_Name()->ToStringW()), (long)pDerived);
						}
					}
				}
			}

			menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
		}
		else if (*evt->get_type() == L"command")
		{
			if (false)
			{
				m_bDisplayAsTable = !m_bDisplayAsTable;
			}
			else
			{
				evt->stopPropagation();
				UI::CommandInvokeEvent* cmdEvt = dynamic_cast<UI::CommandInvokeEvent*>(evt);

				long param = cmdEvt->get_Command();
				ClassType* pDerivedType = (ClassType*)param;

				void* p = newobj(pDerivedType);
				if (p)
				{
					Type* pType = m_pProperty->set_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0].m_pType;
					pType = pType->GetStripped();
					void* value = DynamicCast(p, pDerivedType, pType->GetPointerTo()->GetClass());

					ASSERT(0);
					void *_this = NULL;//__RTDynamicCast(m_itemVisual, 0, (void*)&typeid(m_itemVisual), (void*)m_pProperty->set_method->GetTypeInfo(), 0);

				//	StringA str_type = pType->ToString();

					ULONG_PTR func;
					if (m_pProperty->set_method->m_decl->m_offset != -1)
					{
						void* vtable = *(void**)_this;
						func = *(ULONG_PTR*)((uint8*)vtable + m_pProperty->set_method->m_decl->m_offset);
					}
					else
					{
						func = m_pProperty->set_method->m_func;
					}

					__asm
					{
						push ecx
						mov ecx,_this
						push value
						call func
						pop ecx
					}
				}
			}
		}

#if 0
		void *_this = __RTDynamicCast(m_itemVisual, 0, (void*)&typeid(m_itemVisual), (void*)put_type_info(), 0);

		cpp::Type* pType = put_decl->m_pType->m_pFunction->m_parameters[0]->m_pType;
		StringA str_type = pType->toString();
		pType = pType->GetType();

		DWORD func;
		if (put_decl->m_offset != -1)
		{
			void* vtable = *(void**)_this;
			func = *(DWORD*)((uint8*)vtable + put_decl->m_offset);
		}
		else
		{
			func = put_func;
		}

		if (*evt->get_type() == L"contextmenu")
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			if (pType->m_type == cpp::type_pointer && pType->m_pPointerTo->m_type == cpp::type_class)
			{
				CLXUIMenuElement* menu = new CLXUIMenuElement();
				menu->SetRParent(m_ctledit);
				menu->SetOwnerWindow(m_ctledit->get_OwnerWindow());
				
				std::map<StringA, cpp::Type*>::iterator it = pD->m_namedTypes.begin();
				while (it != pD->m_namedTypes.end())
				{
					cpp::Type* pType2 = (*it).second;
					ASSERT(pType2);
					it++;

					if (pType2->m_type == cpp::type_class)
					{
						if (pType2->m_pClass->IsOfType(pType->m_pPointerTo->m_pClass))
						{
						//	pType2->m_pClass->IsOfType(pType->m_pPointerTo->m_pClass);
							menu->AddItem(new TextString(ConvertA2S(pType2->m_pClass->m_name)), (long)pType2);
						}
					}
				}

				menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
			}
		}
		else if (*evt->get_type() == L"command")
		{
			evt->stopPropagation();
			CommandInvokeEvent* cmdEvt = dynamic_cast<CommandInvokeEvent*>(evt);

			long param = cmdEvt->get_Command();

			if (pType->m_type == cpp::type_enum)
			{
				__asm
				{
					push ecx
					mov ecx,_this
					push param
					call func
					pop ecx
				}
			}
			else
			{
				cpp::Type* pType2 = (cpp::Type*)param;

				void* object = newobj(pType2->m_pClass);
				Type_Info* src = (Type_Info*)pD->LookupSymbol(DecorateName(pType2->m_pClass->m_name));
				Type_Info* dst = (Type_Info*)pD->LookupSymbol(DecorateName(pType->m_pPointerTo->m_pClass->m_name));

				void* param = __RTDynamicCast(object, 0, src, dst, 0);

				__asm
				{
					push ecx
					mov ecx,_this
					push param
					call func
					pop ecx
				}
			}
		}
		else if (*evt->get_type() == L"ValueChange")
		{
			evt->stopPropagation();
			ColorPickerRGB* pColorPicker = dynamic_cast<ColorPickerRGB*>(m_ctledit);
				int sz = pType->get_sizeof();

			int r = pColorPicker->m_slider[0]->get_pos()*255.0;
			int g = pColorPicker->m_slider[1]->get_pos()*255.0;
			int b = pColorPicker->m_slider[2]->get_pos()*255.0;

			UI::Color length(r, g, b);
			void* object = &length;

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

			length.Detach();
		}
		else if (*evt->get_type() == L"changed")
		{
			evt->stopPropagation();
			if (pType->m_type == cpp::type_double)
			{
				StringW str = static_cast<UI::TextEdit*>(m_ctledit)->get_Text();
				double value = atof(ConvertS2A(str).c_str());
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
			else if (pType->m_type == cpp::type_long)
			{
				StringW str = static_cast<UI::TextEdit*>(m_ctledit)->get_Text();
				long value = str2int(str.c_str());

				__asm
				{
					push ecx
					mov ecx,_this
					push value
					call func
					pop ecx
				}
			}
			else if (pType->m_type == cpp::type_class)
			{
				int sz = pType->get_sizeof();

				if (str_type == "class UI::Length")
				{
					StringW str = static_cast<UI::TextEdit*>(m_ctledit)->get_Text();
					double value = atof(ConvertS2A(str).c_str());

					UI::Length length(value);
					void* object = &length;

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

					length.Detach();
				}
				else if (str_type == "class StringW")
				{
					StringW str = static_cast<UI::TextEdit*>(m_ctledit)->get_Text();

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
				}
			}
		}
#endif
	}
#else
	ASSERT(0);
#endif
}
#endif

void Properties::ExpandRows(UI::TreeControl* tree/*, UI::ITreeParent* parentItem*/)
{
#if WIN32
	if (m_bExpanded)
		return;

	m_bExpanded = true;
	//m_itemVisual = itemVisual;

	Dispatch* dispatch = GetDispatch(m_itemVisual->GetType()->GetClass());
	Dispatch::propertymap_t& m_properties = dispatch->GetProperties();

	//UI::DockPanel* panel = new UI::DockPanel;

//	children = new UI::TreeItemChildren(tree);
//	put_VisualTree(children);

	//parentItem->put_Children(children);

	int i = 0;
	Dispatch::propertymap_t::iterator it = m_properties.begin();
	while (it != m_properties.end())
	{
		Property* pPropertyS = it->second;
		if (pPropertyS->get_method/* && (*it).second->put_decl*/)
		{
			PropertyListener* pProperty = new PropertyListener(pPropertyS, m_itemVisual);

			UI::TreeItem* row = m_rows[i++];//(UI::TreeItem*)children->new UI::TreeItem(tree);
		//	UI::DockPanel* row = new UI::DockPanel;
			{
			//	cpp::Type* pReturnType = pProperty->m_pProperty->get_decl->m_pType->m_pFunction->m_pReturnType;
			//	StringA str_returnType = pReturnType->GetType()->toString();
			//	pReturnType = pReturnType->GetType();

				{

					StringA* str;
				//	str = pReturnType->toString();
				//	str += " ";
					str = it->first;

					UI::TextString* name = new UI::TextString(str->ToStringW());
					row->AppendColumnCell(name);
				}

				{
					ASSERT(0);
#if 0
					row->addEventListener(WSTR("command"), pProperty, false);
					row->addEventListener(WSTR("contextmenu"), pProperty, false);
#endif

					ASSERT(0);
					void *_this = NULL;//__RTDynamicCast(m_itemVisual, 0, (void*)&typeid(m_itemVisual), (void*)pProperty->m_pProperty->get_method->GetTypeInfo(), 0);

					TwoViews twoViews = CreateView(pProperty->m_pProperty, m_itemVisual, tree);

					if (twoViews.smallView)
					{
						row->AppendColumnCell(twoViews.smallView);
					}

					if (twoViews.largerView)
					{
						row->set_Children(twoViews.largerView);
					}
				}
			}
		}

		++it;
	}
#else
	ASSERT(0);
#endif
}

void Properties::CreateRows(Object* itemVisual, UI::TreeControl* tree)
{
	m_tree = tree;
	m_itemVisual = itemVisual;

	Dispatch* dispatch = GetDispatch(m_itemVisual->GetType()->GetClass());
	Dispatch::propertymap_t& m_properties = dispatch->GetProperties();

	//UI::DockPanel* panel = new UI::DockPanel;

	children = new UI::TreeItemChildren(tree);
	set_VisualTree(children);

	//parentItem->put_Children(children);

	Dispatch::propertymap_t::iterator it = m_properties.begin();
	while (it != m_properties.end())
	{
		Property* pPropertyS = it->second;
		if (pPropertyS->get_method)
		{
			PropertyListener* pProperty = new PropertyListener(pPropertyS, m_itemVisual);

			UI::TreeItem* row = new UI::TreeItem(tree);

			m_rows.Add(row);
		//	UI::DockPanel* row = new UI::DockPanel;
			{
			//	cpp::Type* pReturnType = pProperty->m_pProperty->get_decl->m_pType->m_pFunction->m_pReturnType;
			//	StringA str_returnType = pReturnType->GetType()->toString();
			//	pReturnType = pReturnType->GetType();

#if 0
				{

					StringA str;
				//	str = pReturnType->toString();
				//	str += " ";
					str += (*it).first;

					UI::TextString* name = new UI::TextString(ConvertA2S(str));
				//	UI::DockPanel::put_Dock(name, UI::DockPanel::Left);
				//	row->AddRChild(name);
					row->AppendColumnCell(name);
				}

				{
					UI::UIElement* visual = NULL;

					if (pProperty->m_pProperty->put_class)
					{
						StringA fullname = pProperty->m_pProperty->put_class->m_name;
						fullname += "::";
						fullname += pProperty->m_pProperty->put_decl->m_name;
						cpp::Scope* pScope = pD->LookupProc(fullname);
						if (pScope)
							pProperty->m_pProperty->put_func = pScope->m_startAddress;
						else
							pProperty->m_pProperty->put_func = NULL;
					}

					{
						StringA fullname = pProperty->m_pProperty->get_class->m_name;
						fullname += "::";
						fullname += pProperty->m_pProperty->get_decl->m_name;
						cpp::Scope* pScope = pD->LookupProc(fullname);
						if (pScope)
							pProperty->m_pProperty->get_func = pScope->m_startAddress;
						else
							pProperty->m_pProperty->get_func = NULL;
					}

					/*
					switch (pReturnType->m_type)
					{
					}
					*/

					row->addEventListener(WSTR("command"), pProperty, false);
					row->addEventListener(WSTR("contextmenu"), pProperty, false);

					void *_this = __RTDynamicCast(itemVisual, 0, (void*)&typeid(itemVisual), (void*)pProperty->m_pProperty->get_Type_Info(), 0);

					/*
					TwoViews twoViews = CreateView(pProperty->m_pProperty, itemVisual, tree);

					if (twoViews.smallView)
					{
						row->AppendColumnCell(dynamic_cast<Control*>(twoViews.smallView));
					}

					if (twoViews.largerView)
					{
						row->put_Children(dynamic_cast<Control*>(twoViews.largerView));
					}

					pProperty->m_ctledit = visual;
					*/

					/*
					if (visual)
					{
					//	UI::DockPanel::put_Dock(visual, UI::DockPanel::Fill);
					//	row->AddRChild(visual);
						row->AppendColumnCell(visual);
					}
					*/
				}
#endif
			}

			//panel->AddRChild(row);
			children->AppendItem(row);
		}

		++it;
	}

//	put_VisualTree(m_tree);
//	InvalidateMeasure();

/*
	TwoViews twoViews;
	twoViews.largerView = 
	return twoViews;
	*/
}

#if 0
void Properties::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"ItemExpanding")
		{
			evt->stopPropagation();

			UI::TreeItem* row = static_cast<UI::TreeItem*>(evt->get_target());
			if (Properties* p = dynamic_cast<Properties*>(row->get_Children()))
			{
				p->ExpandRows(m_tree);
			}
			else if (ViewOfCollection2* p = dynamic_cast<ViewOfCollection2*>(row->get_Children()))
			{
				p->ExpandRows(m_tree);
			}
		}
	}
}
#endif

}
