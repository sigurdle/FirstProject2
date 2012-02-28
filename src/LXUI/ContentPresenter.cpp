#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* ContentPresenter::s_ContentProperty = RegisterProperty(WSTR("Content"), typeid(Object), typeid(ContentPresenter), NULL, PropertyMetaData(AffectsMeasure));

__live_object_ptr<FrameworkTemplate> pStringTemplate;

Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

ContentPresenter::ContentPresenter()
{
	m_visualTree = NULL;
}

StringW* ContentPresenter::get_Name()
{
	return m_Name;
}

void ContentPresenter::set_Name(StringW* name)
{
	m_Name = name;
}

unsigned int ContentPresenter::get_VisualChildrenCount()
{
	/*
	if ((int)get_Width() > 510)
	{
		MessageBeep(-1);
		get_Content();
	}
	*/

	/*
	if (m_visualTree == NULL)
	{
		MessageBeep(-1);
		get_Content();
	}
	*/

	return m_visualTree? 1: 0;
}

Visual* ContentPresenter::GetVisualChild(unsigned int index)
{
	get_Content();
	return m_visualTree;
}

LDraw::SizeD ContentPresenter::MeasureOverride(LDraw::SizeD availSize)
{
	get_Content();

	if (m_visualTree)
	{
		m_visualTree->Measure(availSize);
		return m_visualTree->get_DesiredSize();
	}
	return LDraw::SizeD(0,0);
}

LDraw::SizeD ContentPresenter::ArrangeOverride(LDraw::SizeD finalSize)
{
	if (m_visualTree)
	{
		m_visualTree->Arrange(LDraw::RectD(0, 0, finalSize.Width, finalSize.Height));
	}
	return finalSize;
}

Object* ContentPresenter::get_Content()
{
	return GetValue(get_ContentProperty());
}

void ContentPresenter::OnPropertyChanged(DependencyPropertyChangedEventArgs args)
{
	FrameworkElement::OnPropertyChanged(args);

	if (args.get_Property() == get_ContentProperty())
	{
		if (args.get_OldValue() != args.get_NewValue())
		{
			Apply();
		}
	}
}

void ContentPresenter::set_Content(Object* content)
{
	SetValue(get_ContentProperty(), content);
}

void ContentPresenter::set_VisualTree(UIElement* visualTree)
{
	if (m_visualTree)
	{
		RemoveVisualChild(m_visualTree);
		/*
		m_visualTree->SetRParent(NULL);
		m_visualTree->SetOwnerWindow(NULL);
		*/
	}

	m_visualTree = visualTree;

	if (m_visualTree)
	{
		AddVisualChild(m_visualTree);
		/*
		m_visualTree->SetRParent(this);
		m_visualTree->SetOwnerWindow(GetOwnerWindow());
		*/
	}
}

void ContentPresenter::Apply()
{
	/*
	if (get_Width() > 590)
	{
		MessageBeep(-1);
	}
	*/

	if (get_Content() == NULL)
	{
		set_VisualTree(NULL);
		return;
	}

	// Find the template to use
	FrameworkTemplate* pTemplate = NULL;

	UIElement* uielement = dynamic_cast<UIElement*>(get_Content());
	if (uielement)
	{
	//	if (uielement->GetOwnerWindow())
	//		ASSERT(GetOwnerWindow() == uielement->GetOwnerWindow());

		ASSERT(m_objectpropertymap.size() == 0);

		set_VisualTree(uielement);
		return;
	}
	else
	{
		pTemplate = dynamic_cast<FrameworkTemplate*>(TryFindResource(get_Content()->GetType()));
		if (pTemplate == NULL)
		{
			if (pStringTemplate == NULL)
			{
				XmlData::Document* document = new XmlData::Document;

				StringW* filename = MakeFilePath(_Module, L"../../../StringTemplate.lxui");
				document->load(filename);

				Type* returnType;
				pStringTemplate = dynamic_cast<FrameworkTemplate*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
			}

			pTemplate = pStringTemplate;
		}
	}

	if (pTemplate)
	{
		Type* pRealType;
		Object* obj = pTemplate->get_VisualTree()->Create4(get_Content(), &pRealType, this/*???*/, m_objectpropertymap);
		set_VisualTree(dynamic_cast<UIElement*>(obj));

		Do(get_Content());
	//	UpdatedVisualTree();
	}
}

}	// UI
}
