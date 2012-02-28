#include "stdafx.h"
#include "Browser.h"
#include "ViewOfCollection2.h"
#include "Properties.h"

namespace System
{

void ViewOfCollection2::Build()
{
	ASSERT(0);
#if 0
	UI::TreeControl* pTree = new UI::TreeControl;

	pTree->AddColumn(new UI::TextString(WSTR("Name")));
	//pTree->m_treeHeader->AddColumn(new UI::TextString(L"Value"));

	UI::TreeItemChildren* children = new UI::TreeItemChildren(pTree);
	unsigned long count = m_pCollection->GetCount();
	for (int i = 0; i < count; i++)
	{
		Object* child = m_pCollection->GetItem(i);

		StringA* classname = child->GetType()->m_qname;
		/*
		{
			void* vtable = *(void**)child.m_p;
			rti* p3 = ((rti**)vtable)[-1];

			int count = p3->m_classHierarchyDescriptor->count;
			BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

			Type_Info* ti = (Type_Info*)table[0]->typedesc;
			classname = ti->name() + strlen("class ");
		}
		*/

		UI::TreeItem* row = new UI::TreeItem(pTree);

		m_rows.Add(row);

		row->AppendColumnCell(new UI::TextString(classname->ToStringW()));

		children->AppendItem(row);
	}

	pTree->set_Children(children);

	set_VisualTree(pTree);
#endif
}

void ViewOfCollection2::ExpandRows(UI::TreeControl* tree)
{
	if (m_bExpanded) return;
	m_bExpanded = true;

	ASSERT(0);
#if 0
	unsigned long count = m_pCollection->GetCount();
	for (int i = 0; i < count; i++)
	{
		Object* child = m_pCollection->GetItem(i);

		// ??? TwoViews twoViews = CreateView(
		{
			Properties* pView = new Properties;
			pView->set_Visibility(UI::Collapsed);

			pView->CreateRows(child, tree);

		//	twoViews.largerView = pView;
			m_rows[i]->set_Children(dynamic_cast<UI::Control*>(pView));
		}
	}
#endif
}

}
