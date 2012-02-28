#include "stdafx.h"
#include "LXUI2.h"

namespace System
{

Uri::Uri(StringW* uri)
{
	m_absolute = uri;
}

/*
CTOR Uri(Uri* baseUri, StringW* relative);
CTOR Uri(Uri* baseUri, Uri* relative);

StringW* get_Host();
int get_Port();
bool get_IsFile();
*/

namespace UI
{

//////////////////////////////////////////
// StaticResourceExtension

StaticResourceExtension::StaticResourceExtension()
{
}

StaticResourceExtension::StaticResourceExtension(Object* resourceKey)
{
	m_resourceKey = resourceKey;
}

Object* StaticResourceExtension::get_ResourceKey()
{
	return m_resourceKey;
}

void StaticResourceExtension::set_ResourceKey(Object* resourceKey)
{
	m_resourceKey = resourceKey;
}

ResourceDictionary* ThemeDictionary;

Object* StaticResourceExtension::ProvideValue(IServiceProvider* serviceProvider)
{
	ScopeProvider* scopeProvider = dynamic_cast<ScopeProvider*>(serviceProvider);
	ASSERT(scopeProvider);

	if (scopeProvider->m_element)
	{
		// TODO ??? FindResource

		// TODO, logical parent

		Visual* p = dynamic_cast<Visual*>(scopeProvider->m_element);
		while (p)
		{
			FrameworkElement* element = dynamic_cast<FrameworkElement*>(p);
			if (element)
			{
			//	Object* value = element->get_Resources()->get_Item(get_ResourceKey());
				Object* value = element->get_Resources()->get_Item(get_ResourceKey());
				if (value)
					return value;
			}

			p = p->GetRParent();
		}
	}
	else
	{
		for (unsigned int i = scopeProvider->m_scope.cont.size()-1; (int)i >= 0; i--)
		{
			Object* obj = scopeProvider->m_scope.cont[i];

			FrameworkElement* element = dynamic_cast<FrameworkElement*>(obj);
			if (element)
			{
			//	Object* value = element->get_Resources()->get_Item(get_ResourceKey());
				Object* value = element->get_Resources()->get_Item(get_ResourceKey());
				if (value)
					return value;
			}
			else if (ResourceDictionary* dict = dynamic_cast<ResourceDictionary*>(obj))
			{
				Object* value = dict->get_Item(get_ResourceKey());
				if (value)
					return value;
			}
		}
	}

	Application* app = Application::get_Current();
	if (app)
	{
		Object* value = app->TryFindResource(get_ResourceKey());
		if (value)
			return value;
	}

	if (ThemeDictionary == NULL)
	{
		ThemeDictionary = dynamic_cast<ResourceDictionary*>(Application::LoadComponent(new Uri(WSTR("C:/mmstudio/theme_dictionary.xaml"))));
	}

	if (ThemeDictionary)
	{
		Object* value = ThemeDictionary->get_Item(get_ResourceKey());
		if (value)
			return value;
	}

	return NULL;
}

//////////////////////////////////////////
// DynamicResourceExtension

DynamicResourceExtension::DynamicResourceExtension()
{
}

DynamicResourceExtension::DynamicResourceExtension(Object* resourceKey)
{
	m_resourceKey = resourceKey;
}

Object* DynamicResourceExtension::get_ResourceKey()
{
	return m_resourceKey;
}

void DynamicResourceExtension::set_ResourceKey(Object* resourceKey)
{
	m_resourceKey = resourceKey;
}

Object* DynamicResourceExtension::ProvideValue(IServiceProvider* serviceProvider)
{
	return NULL;
	/*
	ScopeProvider* scopeProvider = dynamic_cast<ScopeProvider*>(serviceProvider);
	ASSERT(scopeProvider);

	for (unsigned int i = scopeProvider->m_scope.cont.size()-1; (int)i >= 0; i--)
	{
		Object* obj = scopeProvider->m_scope.cont[i];

		FrameworkElement* element = dynamic_cast<FrameworkElement*>(obj);
		if (element)
		{
			Object* value = element->get_Resources()->get_Item(get_ResourceKey());
			if (value)
				return value;
		}
	}

	Application* app = Application::get_Current();
	if (app)
	{
		Object* value = app->TryFindResource(get_ResourceKey());
		if (value)
			return value;
	}

	return NULL;
	*/
}

/////////////////////////////////////////////////////
// ExitEventArgs

ExitEventArgs::ExitEventArgs()
{
}

int ExitEventArgs::get_ApplicationExitCode()
{
	return m_ApplicationExitCode;
}

void ExitEventArgs::set_ApplicationExitCode(int exitCode)
{
	m_ApplicationExitCode = exitCode;
}

/////////////////////////////////////////////////////
// Application

Application* Application::s_Current = NULL;

Application::Application()
{
}

// static
Application* Application::get_Current()
{
	return s_Current;
}

// static
Object* Application::LoadComponent(Uri* resourceLocator)
{
	XmlData::Document* document = new XmlData::Document;

	StringW* filename = resourceLocator->m_absolute;
	document->load(filename);

	Type* returnType;
	return CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType);
}

void LoadInto(Object* object, XmlData::Element* element);

// static
void Application::LoadComponent(Object* component, Uri* resourceLocator)
{
	XmlData::Document* document = new XmlData::Document;

	StringW* filename = resourceLocator->m_absolute;
	document->load(filename);

	LoadInto(component, document->get_documentElement());
}

Object* Application::TryFindResource(Object* resourceKey)
{
	// TODO
	return NULL;
}

Object* Application::FindResource(Object* resourceKey)
{
	Object* resource = TryFindResource(resourceKey);
	if (resource == NULL)
	{
		throw new ResourceReferenceKeyNotFoundException();
	}

	return resource;
}

ResourceDictionary* Application::get_Resources()
{
	return m_resources;
}

void Application::set_Resources(ResourceDictionary* resources)
{
	m_resources = resources;
}

void Application::OnActivated(EventArgs* args)
{
	Activated(this, args);
}

void Application::OnDeactivated(EventArgs* args)
{
	Deactivated(this, args);
}

void Application::OnExit(ExitEventArgs* args)
{
	Exit(this, args);
}

}	// UI
}
