#include "stdafx.h"
#include "Browser.h"
#include "PropertiesWindow.h"
#include "Properties.h"

namespace System
{

PropertiesWindow::PropertiesWindow(System::Object* pObject)
{
	UI::TreeControl* m_tree = new UI::TreeControl;

	m_tree->AddColumn(new UI::TextString(WSTR("Name")));
	m_tree->AddColumn(new UI::TextString(WSTR("Value")));

	Properties* properties = new Properties;
	properties->CreateRows(pObject, m_tree/*, m_tree*/);
	properties->ExpandRows(m_tree/*, m_tree*/);

	m_tree->set_Children(properties);

	set_VisualTree(m_tree);
}

}
