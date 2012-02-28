#include "stdafx.h"
#include "LXUI2.h"
#include "Storyboard.h"

namespace System
{
namespace UI
{
namespace Media
{

DependencyProperty* Storyboard::s_TargetPropertyProperty = RegisterProperty(WSTR("TargetProperty"), typeid(StringW), typeid(Storyboard), NULL, PropertyMetaData(None));
DependencyProperty* Storyboard::s_TargetNameProperty = RegisterProperty(WSTR("TargetName"), typeid(StringW), typeid(Storyboard), NULL, PropertyMetaData(None));

Storyboard::Storyboard()
{
}

void Storyboard::Begin(FrameworkElement* containingElement, bool isControllable)
{
}

void Storyboard::Begin(FrameworkElement* containingElement, HandoffBehavior handoffBehavior, bool isControllable)
{
}

}	// Media
}	// UI
}