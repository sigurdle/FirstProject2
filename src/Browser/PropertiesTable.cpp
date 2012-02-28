#include "stdafx.h"
#include "Browser.h"
//#include "PropertiesTable.h"

namespace System
{
using namespace UI;

PropertiesTable::PropertiesTable(IObjectCollection* pCollection)
{
	m_pTree = new UI::TreeControl;

	CreateColumns(&pCollection->GetItemType());

	Build(pCollection, m_pTree);

	set_VisualTree(m_pTree);
}

void PropertiesTable::CreateColumns(const Type_Info* ti)
{
//	const char* name = ti->name();

	Type* pType = ti->GetType();//pD->LookupNamedType(name + 6);

	//if (strncmp(name, "class ", 6) == 0)
	if (pType->get_Kind() == type_class)
	{
		/*
		Type* pType = pD->LookupNamedType(name + 6);
		if (pType == NULL)
			THROW(-1);

		pType = pType->GetType();
		ASSERT(pType->m_type == type_class);
		*/

	//	m_pTree->AddColumn(new UI::TextString(L""));

		Dispatch* dispatch = GetDispatch(pType->GetClass());

		Dispatch::propertymap_t& m_properties = dispatch->GetProperties();

		Dispatch::propertymap_t::iterator it = m_properties.begin();
		while (it != m_properties.end())
		{
			Property* pProperty = it->second;

			if (pProperty->get_method)
			{
				Type* pReturnType = pProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
				StringA* str_returnType = pReturnType->GetStripped()->ToString();
				pReturnType = pReturnType->GetStripped();

				StringA* str = it->first;

				m_pTree->AddColumn(new UI::TextString(str->ToStringW()));

				properties.Add(pProperty);
			}

			++it;
		}

	}
	/*
	else if (pType->m_type == cpp::type_int)
	{
		pTree->m_treeHeader->AddColumn(new UI::TextString(OLESTR("int")));
	}
	*/
	else
		ASSERT(0);
}

UI::TreeItemChildren* PropertiesTable::GetGroup(UI::TreeItemChildren* group, Object* obj, int fieldind)
{
#if WIN32
	//m_pGroup->m_items

	if (fieldind < m_pTree->get_GroupHeaderList()->m_columns.GetSize())
	{
		GroupItem* groupItem = dynamic_cast<GroupItem*>(group->m_userdata);
		Property* pProperty = properties[m_pTree->get_GroupHeaderList()->m_columns[fieldind]->m_def->m_index];
		UI::TreeItemChildren* subgroup;

		ASSERT(0);
		void*_this = NULL;//__RTDynamicCast(obj, 0, (void*)&typeid(obj), (void*)pProperty->get_method->GetTypeInfo(), 0);

		ULONG_PTR func;
		if (pProperty->get_method->m_decl->m_offset != -1)
		{
			void* vtable = *(void**)_this;
			func = *(ULONG_PTR*)((uint8*)vtable + pProperty->get_method->m_decl->m_offset);
		}
		else
		{
			func = pProperty->get_method->m_func;
		}

		Type* pReturnType = pProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;

		IComparable* pComparable;

		if (pReturnType->get_Kind() == type_long_long)
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

			pComparable = new LongLongObject(result64);
		}
		else if (pReturnType->get_Kind() == type_class)
		{
			uint8* object = new uint8[pReturnType->get_sizeof()];

			__asm
			{
				push ecx
				mov ecx,_this
				push object
				call func
				pop ecx
			}

			if (*pReturnType->GetClass()->m_qname == "WIN_FILETIME")
			{
				pComparable = new FileTimeObject((WIN_FILETIME*)object);
			}

			delete[] object;
		}

		map<Comparable, UI::TreeItemChildren*>::iterator it = groupItem->m_groups.find(pComparable);
		if (it == groupItem->m_groups.end())
		{
			UI::TreeItem* row = new UI::TreeItem(m_pTree);
			subgroup = new UI::TreeItemChildren(m_pTree);

			UI::Border* pBorder = new UI::Border();
			pBorder->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
			row->m_Span = pBorder;
			ASSERT(0);
#if 0
			row->AddChild(row->m_Span);
#endif
			GroupItem* pSubGroupItem = new GroupItem;
			subgroup->m_userdata = pSubGroupItem;

			row->set_Children(subgroup);
			group->AppendItem(row);

			it = groupItem->m_groups.insert(/*groupItem->m_groups.begin(),*/ map<Comparable, UI::TreeItemChildren*>::value_type(pComparable, subgroup)).first;
		}

		subgroup = (*it).second;

			// Search for sub parent on next group by field
		//return pGroup->GetGroup(pItem, lv, fieldind+1);

		return GetGroup(subgroup, obj, fieldind+1);
	}

	return group;
#else
	VERIFY(0);
	return NULL;
#endif
}

void PropertiesTable::Build(IObjectCollection* pCollection, UI::ITreeParent* parent)
{
	ASSERT(0);
#if 0

	{
		UI::TreeItemChildren* m_pChildren = new UI::TreeItemChildren(m_pTree);
		GroupItem* pSubGroupItem = new GroupItem;
		m_pChildren->m_userdata = pSubGroupItem;

		unsigned int count = pCollection->GetCount();

		/*
		std::map<StringA, Property*>::iterator it = m_properties.begin();
		while (it != m_properties.end())
		{
			Property* pProperty = (*it).second;

			if (pProperty->get_decl)
			{
				properties.push_back(pProperty);
			}

			it++;
		}
		*/

		for (unsigned int i = 0; i < count; i++)
		{
			Object* obj = pCollection->GetItem(i);

		//	UI::TreeItemChildren* pChildren = m_pChildren;//GetGroup(properties[1], obj.m_p);
			UI::TreeItemChildren* pChildren = GetGroup(m_pChildren, obj, 0);

			UI::TreeItem* row = new UI::TreeItem(m_pTree);
			row->m_userdata = obj;

			//row->SetExpandButton(1);

		//	row->AppendColumnCell(new TextString(L" "));

		//	std::map<StringA, Property*>::iterator it = m_properties.begin();
		//	while (it != m_properties.end())
			for (int j = 0; j < properties.GetSize(); j++)
			{
				Property* pProperty = properties[j];//(*it).second;

				//if (pProperty->get_decl)
				{
					TwoViews twoViews = CreateView(pProperty, obj, NULL);

					if (twoViews.smallView)
					{
						row->AppendColumnCell(dynamic_cast<Control*>(twoViews.smallView));
					}
					else
					{
					//	row->AppendColumnCell(new UI::TextString(L""));
						TreeItem* item = new TreeItem(NULL);
						item->set_Children(twoViews.largerView);

						row->AppendColumnCell(item);
					}

	#if 0
					cpp::Type* pReturnType = pProperty->get_decl->m_pType->m_pFunction->m_pReturnType;
					StringA str_returnType = pReturnType->GetType()->toString();
					pReturnType = pReturnType->GetType();

					{
						UI::Visual* visual = NULL;

						/*
						{
							StringA fullname = pProperty->put_class->m_name;
							fullname += "::";
							fullname += pProperty->put_decl->m_name;
							cpp::Scope* pScope = pD->LookupProc(fullname);
							if (pScope)
								pProperty->put_func = pScope->m_startAddress;
							else
								pProperty->put_func = NULL;
						}
						*/

						// TODO, elsewhere
						{
							StringA fullname = pProperty->get_class->m_name;
							fullname += "::";
							fullname += pProperty->get_decl->m_name;
							cpp::Scope* pScope = pD->LookupProc(fullname);
							if (pScope)
								pProperty->get_func = pScope->m_startAddress;
							else
								pProperty->get_func = NULL;
						}

						switch (pReturnType->m_type)
						{
						case cpp::type_long_long:
						case cpp::type_long_int:
						case cpp::type_double:
							{
								if (pProperty->put_decl)
								{
									visual = new UI::TextEdit();
	#if 0
								visual->addEventListener(OLESTR("changed"), pProperty, false);
	#endif
								}
								else
								{
									visual = new UI::TextString();
								}
							}
							break;

						case cpp::type_enum:
							{
						//	visual = new UI::CLXUIMenuPopupElement();
								UI::CLXUIMenuElement* pMenu = new UI::CLXUIMenuElement(new UI::TextString(OLESTR("")));

								cpp::Enum* pEnum = pProperty->get_decl->m_pType->m_pFunction->m_pReturnType->m_pEnum;

								for (int i = 0; i < pEnum->m_deflist.size(); i++)
								{
									const cpp::EnumDef& enumDef = pEnum->m_deflist[i];
									pMenu->AddItem(new UI::TextString(ConvertA2S(enumDef.m_name)), enumDef.m_value);
								}

								visual = pMenu;
							}
							break;
						}

	#if 0
						row->addEventListener(OLESTR("command"), pProperty, false);
						row->addEventListener(OLESTR("contextmenu"), pProperty, false);
	#endif
						void*_this = __RTDynamicCast(obj.m_p, 0, (void*)&typeid(obj.m_p), (void*)pProperty->get_Type_Info(), 0);

						DWORD func;
						if (pProperty->get_decl->m_offset != -1)
						{
							void* vtable = *(void**)_this;
							func = *(DWORD*)((uint8*)vtable + pProperty->get_decl->m_offset);
						}
						else
						{
							func = pProperty->get_func;
						}

						if (func)
						{
						//	pProperty->get_func = pScope->m_startAddress;

							switch (pReturnType->m_type)
							{
								case cpp::type_long_int:
								{
									long _result;

									__asm
									{
										push eax
										push ecx
										mov ecx,_this
										call func
										mov _result,eax
										pop ecx
										pop eax
									}

									WCHAR buf[64];
									swprintf(buf, L"%d", _result);
									if (pProperty->put_decl)
									{
										static_cast<UI::TextEdit*>(visual)->put_Text(buf);
									}
									else
									{
										static_cast<UI::TextString*>(visual)->put_TextContent(buf);
									}
								}
								break;

								case cpp::type_long_long:
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
									WCHAR buf[64];
	#if WIN32
									swprintf(buf, L"%I64d", result64);
	#else
									swprintf(buf, L"%uld", _result0);
	#endif
									if (pProperty->put_decl)
									{
										static_cast<UI::TextEdit*>(visual)->put_Text(buf);
									}
									else
									{
										static_cast<UI::TextString*>(visual)->put_TextContent(buf);
									}
								}
								break;

								case cpp::type_enum:
								{
									long _result;

									__asm
									{
										push eax
										push ecx
										mov ecx,_this
										call func
										mov _result,eax
										pop ecx
										pop eax
									}

								//	WCHAR buf[64];
								//	swprintf(buf, L"%d", _result);
								//	static_cast<UI::CLXUIMenuPopupElement*>(visual)->put_Text(buf);
								}
								break;

								case cpp::type_double:
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

									WCHAR buf[64];
									swprintf(buf, L"%g", _result);
									static_cast<UI::TextEdit*>(visual)->put_Text(buf);
								}
								break;

								case cpp::type_class:
								{
									/*
									if (false)//str_returnType == "class UI::Length")
									{
										Length length = ((UI::Visual*)_this)->get_Height();
										length.get_Value();
									}
									else
									*/
									{
										uint8* object = new uint8[pReturnType->get_sizeof()];

										__asm
										{
											push ecx
											mov ecx,_this
											push object
											call func
											pop ecx
										}

										if (str_returnType == "class UI::Length")
										{
											UI::Length* pLength = (UI::Length*)object;
											WCHAR buf[64];
											if (*pLength != UI::Length())
											{
												double value = pLength->get_Value();

												if (pLength->get_UnitType() == UI::Length::UnitPercentage)
													swprintf(buf, L"%g%%", value);
												else
													swprintf(buf, L"%g", value);
											}
											else
											{
												buf[0] = 0;
											}

											visual = new UI::TextEdit();
										//	visual->addEventListener(OLESTR("changed"), pProperty, false);
											static_cast<UI::TextEdit*>(visual)->put_Text(buf);
										}
										else if (str_returnType == "class StringA")
										{
											StringA* pString = (StringA*)object;

											visual = new UI::TextEdit();
										//	visual->addEventListener(OLESTR("changed"), pProperty, false);
											static_cast<UI::TextEdit*>(visual)->put_Text(ConvertA2S(*pString));
										}
										else if (str_returnType == "class StringW")
										{
											StringW* pString = (StringW*)object;

											visual = new UI::TextEdit();
										//	visual->addEventListener(OLESTR("changed"), pProperty, false);
											static_cast<UI::TextEdit*>(visual)->put_Text(*pString);
										}
										else if (str_returnType == "class UI::Color")
										{
											UI::Color* pColor = (UI::Color*)object;

											/*
											StringW* pString = (StringW*)object;

											visual = new UI::TextEdit();
											visual->addEventListener(OLESTR("changed"), pProperty, false);
											static_cast<UI::TextEdit*>(visual)->put_Text(*pString);
											*/
											ColorPickerRGB* pColorPicker = new ColorPickerRGB;

											pColorPicker->m_slider[0]->put_pos(pColor->get_R()/255.0);
											pColorPicker->m_slider[1]->put_pos(pColor->get_G()/255.0);
											pColorPicker->m_slider[2]->put_pos(pColor->get_B()/255.0);

											pColorPicker->put_Width(256);

											pColorPicker->UpdateControls();

											visual = pColorPicker;
										//	visual->addEventListener(OLESTR("ValueChange"), pProperty, false);
										}

										delete[] object;
									}
								}
								break;

								case cpp::type_pointer:
								{
									if (pReturnType->m_pPointerTo->m_type == cpp::type_class)
									{
										void* vobject;

										__asm
										{
											push eax
											push ecx
											mov ecx,_this
											call func
											mov vobject,eax
											pop ecx
											pop eax
										}

										if (vobject)
										{
											StringA classname;
											_Object* obj;
											//{
												void* vtable = *(void**)vobject;
												rti* p3 = ((rti**)vtable)[-1];

												int count = p3->m_classHierarchyDescriptor->count;
												BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

												Type_Info* ti = (Type_Info*)table[0]->typedesc;
												classname = ti->name() + strlen("class ");

												obj = (_Object*)__RTDynamicCast(vobject, 0, ti, (void*)&typeid(_Object), 0);
											//}

											if (classname == "UI::_Color")
											{
												visual = new ColorPickerRGB;
											}
											else
											{

												ASSERT(0);
												/*
												ICollection* otherCollection = dynamic_cast<ICollection*>(obj);
												if (otherCollection && strcmp(otherCollection->GetType()->name(), pCollection->GetType()->name()) == 0)	// same type
												{
													Build(otherCollection, item);
												}
												else
												{
													ASSERT(0);
												}
											//	Properties* properties = new Properties;
												//properties->SetItem(obj, parentItem);
											//	visual = properties;
											*/
											}
										}
									}
								}
								break;
							}
						}

					//	pProperty->m_ctledit = visual;

						if (visual)
						{
						//	UI::DockPanel::put_Dock(visual, UI::DockPanel::Fill);
						//	row->AddRChild(visual);
							item->AppendColumnCell(visual/*new UI::TextString(OLESTR("VisualTree"))*/);
						}
						else
						{
							item->AppendColumnCell(new UI::TextString(OLESTR("")));
						}
					}
	#endif
				}
//				it++;
			}

			pChildren->AppendItem(row);
		}

		parent->set_Children(m_pChildren);
	}

#if 0
	Dispatch dispatch(m_itemVisual);
	std::map<StringA, Property*> m_properties;
	GetProperties(m_itemVisual, dispatch, m_properties);

	std::map<StringA, Property*>::iterator it = m_properties.begin();
	while (it != m_properties.end())
	{
		if ((*it).second->get_decl &&  (*it).second->put_decl)
		{
			cpp::Type* pReturnType = pProperty->get_decl->m_pType->m_pFunction->m_pReturnType;
			StringA str_returnType = pReturnType->GetType()->toString();
			pReturnType = pReturnType->GetType();

			StringA str;
			str = (*it).first;

			m_tree->m_treeHeader->AddColumn(new UI::TextString(ConvertA2S(str)));
		}

		it++;
	}
#endif
#endif
}

}
