#ifndef __Properties_h__
#define __Properties_h__

namespace System
{

class Properties : public UI::Control, public IViewOf
{
public:

	class PropertyListener// : public System::IEventListener
	{
	public:
		CTOR PropertyListener(Property* pProperty, Object* itemVisual);

		//virtual void handleEvent(System::Event* evt);

		Property* m_pProperty;
		UI::UIElement* m_ctledit;
		bool m_bDisplayAsTable;

		Object* m_itemVisual;
	};

	CTOR Properties()
	{
		m_bExpanded = false;
	}

	System::Object* m_itemVisual;
	UI::TreeItemChildren* children;

	UI::TreeControl* m_tree;
	vector<UI::TreeItem*, __gc_allocator> m_rows;
	bool m_bExpanded;

	System::Object* get_Viewable()
	{
		return NULL;
	}

	void set_Viewable(System::Object* pObject)
	{
	}

	void CreateRows(System::Object* itemVisual, UI::TreeControl* tree);
	void ExpandRows(UI::TreeControl* tree);

	/*
	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize)
	{
		return availSize;
	}
	*/

//	virtual void handleEvent(System::Event* evt);
};

}

#endif // __Properties_h__
