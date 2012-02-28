#include "stdafx.h"
#include "LXUI2.h"
#include "Style.h"

namespace System
{
namespace UI
{

//Object* CreateElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

//

TriggerCollection::TriggerCollection()
{
}

//

void ApplyStyle(Style* style, FrameworkElement* element)
{
//	element->m_objectpropertymap.clear();	// ??

	element->set_Script(style->get_Script());

	ClassType* pType = element->GetType();

	element->m_userdata[WSTR("Timeline0")] = style->m_object;	// TODO

	Setters* setters = style->get_Setters();

	element->m_style_depproperties.clear();

	for (int i = 0; i < setters->m_items.size(); i++)
	{
		Setter* setter = setters->m_items[i];

		int depPropertyIndex = setter->get_Property()->gindex;
		element->m_style_depproperties[depPropertyIndex] = setter;

		element->m_isValidProperties[setter->get_Property()->gindex] = false;

		// TODO, check if locally set, don't need to do anything


#if 0
		Property* pProperty = pType->m_pDispatch->GetProperty(property->m_name);
#endif
#if 0
		Object* child;
			
		if (true)
		{
			child = property->m_value;
		}
		else
		{
		Type* pRealType;
			ASSERT(0);
			//property->m_value->Create4(element, &pRealType, element->m_objectpropertymap);
		}

		/*
		if (*property->m_name == L"VisualTree")
		{
			dynamic_cast<UIElement*>(element)->set_VisualTree(dynamic_cast<UIElement*>(child);
		}
		else
		*/
		{

		property->m_computedValue = child;
		}
#endif

		// hmm.
#if 0
		element->InvalidateProperty(setter->get_Property());
#endif
	//	element->ClearValue(GetProperty(property->m_depPropertyIndex));

	//	element->SetValue(GetProperty(property->m_depPropertyIndex), child);
	//	SetValue(pType->m_pDispatch, element/*obj*/, pProperty->set_method, child, pRealType);

	//	property->m_value->SetProperties(element, element, element->m_objectpropertymap);
	}

	// hmm.. ??
	for (int i = 0; i < setters->m_items.size(); i++)
	{
		Setter* setter = setters->m_items[i];
		DependencyProperty* pDepProperty = setter->get_Property();
		if (!element->m_isValidProperties[pDepProperty->gindex])
		{
			element->InvalidateProperty(pDepProperty);
		}
	}

	// Triggers
	if (style)
	{
		TriggerCollection* triggers = style->get_Triggers();
		if (triggers)
		{
			unsigned int count = triggers->GetCount();
			for (unsigned int i = 0; i < count; i++)
			{
				Trigger* trigger = dynamic_cast<Trigger*>(triggers->get_Item(i));

			//	if (trigger->get_Property() == args.get_Property())
				{
					Object* triggerValue = trigger->get_Value();

					Object* value = element->GetValue(trigger->get_Property());

					if (value->Equals(triggerValue))
					{
						/*
						TRACE("trigger property: %S", trigger->get_Property()->GetName()->c_str());
						if (BoolObject* boolObj = dynamic_cast<BoolObject*>(value))
						{
							TRACE("= %s", boolObj->GetValue()? "true": "false");
						}
						TRACE("\n");
						*/

						Setters* setters = trigger->get_Setters();

						for (unsigned int i = 0; i < setters->GetCount(); i++)
						{
							Setter* setter = setters->get_Item(i);
							DependencyProperty* pDepProperty = setter->get_Property();
							int depPropertyIndex = pDepProperty->gindex;

							element->m_style_depproperties[depPropertyIndex] = setter;
							element->m_isValidProperties[depPropertyIndex] = false;

							// TODO, check if locally set, don't need to do anything

					//		this->InvalidateProperty(setter->get_Property());
						}

						for (unsigned int i = 0; i < setters->GetCount(); i++)
						{
							Setter* setter = setters->get_Item(i);
							DependencyProperty* pDepProperty = setter->get_Property();

							if (!element->m_isValidProperties[pDepProperty->gindex])
							{
								element->InvalidateProperty(pDepProperty);
							}
						}
					}
				}
			}
		}
	}
}

Style::Style()
{
	m_basedOn = NULL;
	m_script = NULL;
	m_object = NULL;	// ??

	m_triggers = new TriggerCollection;

	m_resources = new ResourceDictionary;
}

#if 0
void Style::Load(XmlData::Element* element)
{
	// TargetType
	StringW* targetType = element->getAttribute(WSTR("TargetType"));

	ClassType* pType = (ClassType*)pD->LookupNamedType(targetType->ToStringA());
	ASSERT(pType);

	XmlData::NodeList* childNodes = element->get_childNodes();
	unsigned int nchildren = childNodes->get_length();

	for (unsigned int i = 0; i < nchildren; i++)
	{
		XmlData::Node* childnode = childNodes->item(i);
		if (childnode->get_nodeType() == XmlData::NODE_ELEMENT)
		{
			XmlData::Element* childelement = static_cast<XmlData::Element*>(childnode);
			if (*childelement->get_tagName() == L"Script")
			{
				m_script = new Script;
				m_script->set_Code(childelement->get_firstChild()->get_textContent());
			}
			else if (*childelement->get_tagName() == L"Objects")
			{
				XmlData::Node* firstChild = dynamic_cast<XmlData::Node*>(childelement->get_firstChild());

				DataTemplate* data = new DataTemplate;
				DataTemplateNode* node = data->CreateElement2(NULL/*??*/, firstChild);

				Type* pRealType;
				map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator> objectpropertymap;
				System::Object* value = node->Create4(NULL/*sourceObject*/, &pRealType, objectpropertymap);

				m_object = value;

			//	MessageBeep(-1);
			}
			else if (*childelement->get_tagName() == L"Setter")
			{
				XmlData::Element* setter = (XmlData::Element*)childnode;

				StringW* propertyName = setter->getAttribute(WSTR("Property"));
				ASSERT(propertyName);
				if (propertyName == NULL)
					throw -1;

				//Property* pProperty = pType->m_pDispatch->GetProperty(propertyName->ToStringA());
				int depPropertyIndex = GetPropertyIndex(propertyName);
				ASSERT(depPropertyIndex != -1);

				XmlData::Node* firstChild = dynamic_cast<XmlData::Node*>(setter->get_firstChild());

				if (true)
				{
					Type* returnType;
					Object* obj = CreateElement(NULL, firstChild, &returnType);
				}
				else
				{
					DataTemplate* data = new DataTemplate;

					PropertyValue* pValue = new PropertyValue;

					pValue->m_name = propertyName;//pProperty->get_PropertyName();
					pValue->m_value = data->CreateElement2(NULL/*??*/, firstChild);
					pValue->m_depPropertyIndex = depPropertyIndex;

					m_depproperties[depPropertyIndex] = pValue;

					m_properties.push_back(pValue);
				}

			//	Type* pRealType;
			//	map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator> objectpropertymap;
			//	System::Object* value = pObject2->Create4(NULL/*sourceObject*/, &pRealType, objectpropertymap);
			}

	#if 0

		//	StringW* valueString = childelement->getAttribute(WSTR("Value"));

			if (pProperty && pProperty->set_method)
			{
				Type* ArgType = pProperty->get_SetType();//put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
				ArgType = ArgType->GetStripped();

				Type* pReturnType = NULL;
				Object* pChild = CreateElement(typeid(System::Object).GetType(), element, &pReturnType);
				if (pChild)

				/*
				Type* pReturnType = NULL;
				Object* pObject = CreateElement(ArgType, attr->get_firstChild(), &pReturnType);
				if (pObject)
				{

				//	SetValue(pDispatch, object, pProperty->set_method, pObject, pReturnType);
				}
				*/
			}
			else if (UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(pVisual))
			{
				ASSERT(0);
			}
	#endif
		}
	}
}
#endif

Type* Style::get_TargetType()
{
	return m_targetType;
}

void Style::set_TargetType(Type* type)
{
	m_targetType = type;
}

Setters* Style::get_Setters()
{
	return m_setters;
}

void Style::set_Setters(Setters* setters)
{
	m_setters = setters;
}

TriggerCollection* Style::get_Triggers()
{
	return m_triggers;
}

void Style::set_Triggers(TriggerCollection* triggers)
{
	m_triggers = triggers;
}

ResourceDictionary* Style::get_Resources()
{
	return m_resources;
}

void Style::set_Resources(ResourceDictionary* resources)
{
	m_resources = resources;
}

//////////////////////////////
// BeginStoryboard

BeginStoryboard::BeginStoryboard()
{
}

Media::Storyboard* BeginStoryboard::get_Storyboard()
{
	return NULL;
	//return static_cast<Storyboard*>(GetValue(get_StoryboardProperty()));
}

void BeginStoryboard::set_Storyboard(Media::Storyboard* storyboard)
{
//	SetValue(get_StoryboardProperty(), storyboard);
}

}
}
