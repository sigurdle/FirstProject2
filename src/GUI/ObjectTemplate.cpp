#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
#if 0

Object* ObjectTemplate::Create(Refs2* refs, map<int, Expressive::StaticObjectExpression*>& irefs, Window* ownerWindow, UIElement* templatedOwner, IRootVisual* rootVisual)
{
	Object* object = newobj(m_classType.GetType()->GetClass());
	if (object == NULL)
	{
		ASSERT(0);
		throw new Exception(WSTR("Failed to create object"));
	}

	// TODO differently
	IRootVisual* newroot = dynamic_cast<IRootVisual*>(object);
	if (newroot)
	{
		rootVisual = newroot;
	}
	ASSERT(rootVisual);

	UIElement* uielement = dynamic_cast<UIElement*>(object);
	if (uielement)
	{
//		uielement->set_OwnerWindow(ownerWindow);
		uielement->set_TemplatedOwner(templatedOwner);
	}

	map<ObjectTemplateBase*, int>::iterator objid = refs->m_objects2.find(this);
	if (objid != refs->m_objects2.end())
	{
		Expressive::StaticObjectExpression* exp = irefs[objid->second];
		if (exp == NULL)
		{
			exp = new Expressive::StaticObjectExpression;
			irefs[objid->second] = exp;
		}

		VERIFY(exp->m_obj == NULL);
		exp->m_obj = object;
	//	ASSERT(object->GetType()->IsDerivedFrom(exp->m_pType->GetPointerTo()->GetClass()));
	}

	DependencyObject* depObj = dynamic_cast<DependencyObject*>(object);

	if (m_setPropertyGroup)
	{
		for (unsigned int i = 0; i < m_setPropertyGroup->m_items.size(); i++)
		{
			SetProperty* p = m_setPropertyGroup->m_items[i];

			PropertyValue* pPropertyVal = depObj->GetProperty(p->m_dp);

			if (SetPropertyToConst* p2 = dynamic_cast<SetPropertyToConst*>(p))
			{
				pPropertyVal->SetLocalObjectValue(p2->m_value);

				/*
				// Setup to listen for changes to the object
				DependencyObject* depObj2 = dynamic_cast<DependencyObject*>(p2->m_value);
				if (depObj2)
				{
					depObj2->AddNotify(pPropertyVal);
				}
				*/
			}
			else if (SetPropertyToObjectTemplate* p2 = dynamic_cast<SetPropertyToObjectTemplate*>(p))
			{
				Object* obj = p2->m_objectTemplate->Create(refs, irefs, ownerWindow, templatedOwner, rootVisual);

				ASSERT(obj->GetType()->IsDerivedFrom(p2->m_objectTemplate->m_classType.GetType()->GetClass()));

				pPropertyVal->SetLocalObjectValue(obj);
			}
////////////////
			else if (SetPropertyToExpression* p2 = dynamic_cast<SetPropertyToExpression*>(p))
			{
				ExpressionBinding* expBinding = new ExpressionBinding(depObj, p2->m_exp);
				/*
				expBinding->m_this = depObj;

				Expressive::EvalContext evalContext;
				evalContext.m_this = depObj;
				evalContext.m_templateOwner = templatedOwner;
				evalContext.m_userObject = expBinding;
				p2->m_exp->TraceCallback(&evalContext, Expressive::ExpTrace(), NULL);
*/
				pPropertyVal->SetInputBinding(expBinding);
			}
			else
				ASSERT(0);
		}
	}

	// TODO, a different interface
	Visual* visual = dynamic_cast<Visual*>(object);
	if (visual)
	{
		visual->SetRoot(rootVisual);
	}

	if (uielement)
	{
		uielement->SetRoot(rootVisual);
	}

	return object;
}

Object* CollectionObjectTemplate::Create(Refs2* refs, map<int, Expressive::StaticObjectExpression*>& irefs, Window* ownerWindow, UIElement* templatedOwner, IRootVisual* rootVisual)
{
	ASSERT(rootVisual);

	Object* object = newobj(m_classType.GetType()->GetClass());
	if (object == NULL)
	{
		ASSERT(0);
		throw new Exception(WSTR("Failed to create object"));
	}

	// TODO differently
	IRootVisual* newroot = dynamic_cast<IRootVisual*>(object);
	if (newroot)
	{
		rootVisual = newroot;
	}

	UIElement* uielement = dynamic_cast<UIElement*>(object);
	if (uielement)
	{
	//	uielement->set_OwnerWindow(ownerWindow);
		uielement->set_TemplatedOwner(templatedOwner);
	}

	IObjectCollection* collection = dynamic_cast<IObjectCollection*>(object);
	if (collection == NULL)
	{
		ASSERT(0);
		throw new Exception(WSTR("Not a collection object"));
	}

	if (m_items)
	{
		list<ObjectTemplateBase*>::iterator it = m_items->m_items.begin();
		while (it != m_items->m_items.end())
		{
			ObjectTemplateBase* objTemplate = *it;
			++it;

			Object* childObject = objTemplate->Create(refs, irefs, ownerWindow, templatedOwner, rootVisual);
			ASSERT(childObject);

			collection->AddObject(childObject);
		}
	}

	// TODO, a different interface
	Visual* visual = dynamic_cast<Visual*>(object);
	if (visual)
	{
		visual->SetRoot(rootVisual);
	}

	if (uielement)
	{
		uielement->SetRoot(rootVisual);
	}

	return object;
}
#endif
}	// Gui
}
