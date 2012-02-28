#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DependencyProperty* ContentControl::s_ContentProperty = RegisterProperty(WSTR("Content"), typeid(Object), typeid(ContentControl), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* ContentControl::s_ContentTemplateProperty = RegisterProperty(WSTR("ContentTemplate"), typeid(FrameworkTemplate), typeid(ContentControl), NULL, PropertyMetaData(AffectsMeasure));

ContentControl::ContentControl()
{
}

Object* ContentControl::get_Content()
{
	return GetValue(get_ContentProperty());

//	printf("ContentControl::get_Content = %p\n", m_Content);
//	return m_Content;
}

void ContentControl::set_Content(Object* content)
{
	SetValue(get_ContentProperty(), content);

//	printf("ContentControl::set_Content(0x%x)\n", newVal);
//	m_Content = newVal;
//	PropertyChanged(ASTR("Content"));

	//SetV

	//EnsureVisuals();

	/*
	m_Border0 = new Border(Thickness(Length(1), Length(1.0), Length(1.0), Length(1.0)));
	m_Border0->put_Background(new SolidColorBrush(Color(0, 0, 0)));

	m_Border1 = new Border(Thickness(Length(1), Length(1.0), Length(1.0), Length(1.0)));
	m_Border1->put_Background(new LinearGradientBrush(Color(240, 240, 240), Color(180, 180, 180), Point(0, 0), Point(0, 1)));

	m_Border2 = new Border(Thickness(Length(1), Length(1.0), Length(1.0), Length(1.0)));
	m_Border2->put_Background(new LinearGradientBrush(Color(180, 180, 180), Color(240, 240, 240), Point(0, 0), Point(0, 1)));

	m_Border3 = new Border(Thickness(Length(0.0), Length(0.0), Length(1.0), Length(1.0)));
	m_Border3->put_Content(m_Content);
	m_Border2->put_Content(m_Border3);
	m_Border1->put_Content(m_Border2);
	m_Border0->put_Content(m_Border1);

	put_VisualTree(m_Border0);
	*/
}

FrameworkTemplate* ContentControl::get_ContentTemplate()
{
	return static_cast<FrameworkTemplate*>(GetValue(get_ContentTemplateProperty()));
}

void ContentControl::set_ContentTemplate(FrameworkTemplate* contentTemplate)
{
	SetValue(get_ContentTemplateProperty(), contentTemplate);
}

}	// UI
}
