#ifndef __Item_h__
#define __Item_h__

//using namespace UI;

namespace System
{

class FieldData
{
public:
	virtual ~FieldData()
	{
	}
};

class StringField : public FieldData
{
public:
	CTOR StringField(System::StringW* value)
	{
		m_value = value;
	}
	System::StringW* m_value;
};

class IntegerField : public FieldData
{
public:
	CTOR IntegerField()
	{
		m_value = 0;
	}

	CTOR IntegerField(long value)
	{
		m_value = value;
	}

	long m_value;
};

class LongLongField : public FieldData
{
public:
	CTOR LongLongField()
	{
		m_value = 0;
	}

	CTOR LongLongField(LONGLONG value)
	{
		m_value = value;
	}

	LONGLONG m_value;
};

class SHA1DigestField : public FieldData
{
public:
	CTOR SHA1DigestField(const uint8* buffer)
	{
		std::memcpy(m_buffer, buffer, 20);
	}

	uint8 m_buffer[20];
};

class IPField : public FieldData
{
public:
	CTOR IPField(uint32 address, uint16 port)
	{
		m_address = address;
		m_port = port;
	}

	uint32 m_address;
	uint16 m_port;
};

class IItem
{
public:
	virtual FieldData* GetFieldData(int ind) = 0;
	virtual UI::UIElement* GetFieldUI(int ind) = 0;
};

class IItemSite
{
public:
	virtual ~IItemSite()
	{
	}

	virtual IItem* GetItem() = 0;
	virtual FieldData* GetFieldData(int ind) = 0;
	virtual UI::UIElement* GetFieldUI(int ind) = 0;
};

class IItemsContainer
{
public:
	virtual IItemSite* AddItem(IItem* item) = 0;
	virtual void RemoveItem(IItemSite* item) = 0;
	virtual void AddField(System::StringW* name) = 0;
	virtual unsigned int GetCount() = 0;
	virtual IItem* GetItem(unsigned int index) = 0;
};

class TreeControlContainer :
	public UI::Control,
	public IItemsContainer
{
public:
	TreeControlContainer()
	{
		m_TreeControl = new Tree;

		UI::ScrollViewer* pScroller = new UI::ScrollViewer;
		pScroller->set_Content(m_TreeControl);

		set_VisualTree(pScroller);
	}

	class ItemSite;

	typedef map<System::StringW*, ItemSite*, Ref_Less<System::StringW> > tymap;

	class MapParent
	{
	public:
		tymap m_map;
	};

	class Tree : public UI::TreeControl, public MapParent
	{
	};

	Tree* m_TreeControl;

	vector<System::StringW*> m_fields;

	class GroupItem : public System::Object, public IItem
	{
	public:

		vector<FieldData*> m_fieldData;
		vector<UI::TextString*> m_fieldUI;

		FieldData* GetFieldData(int ind)
		{
			return m_fieldData[ind];
		}

		UI::UIElement* GetFieldUI(int ind)
		{
			return m_fieldUI[ind];
		}
	};

	/*
	class GroupSite : public TreeItem
	{
	public:
		GroupItem(TreeControl* ownerTree) : TreeItem(ownerTree)
		{
		}
	};
	*/

	class ItemSite : public MapParent, public UI::TreeItem, public IItemSite
	{
	public:
		ItemSite(UI::TreeControl* ownerTree) : UI::TreeItem(ownerTree)
		{
		}

		IItem* m_item;

		virtual IItem* GetItem()
		{
			return m_item;
		}

		virtual FieldData* GetFieldData(int ind)
		{
			return m_item->GetFieldData(ind);
		}

		virtual UI::UIElement* GetFieldUI(int ind)
		{
			return m_item->GetFieldUI(ind);
		}

#if 0
		void handleEvent(System::Event* evt)
		{
			System::StringW* type = evt->get_type();

			System::EventPhaseType phase = evt->get_eventPhase();
			if (phase != System::CAPTURING_PHASE)
			{
				if (*type == L"ItemStateChanging")
				{
					evt->stopPropagation();

					System::Event* evt2 = new System::Event;
					evt2->InitEvent(WSTR("Activate"), true, true);
					dispatchEvent(evt2);
					return;
				}
			}
			TreeItem::handleEvent(evt);
		}
#endif
	};

	ItemSite* FindGroup(UI::ITreeParent* parent, UI::TextString* fielddata, int fieldind)
	{
		tymap::iterator it = dynamic_cast<MapParent*>(parent)->m_map.find(fielddata->get_TextContent());
		if (it != dynamic_cast<MapParent*>(parent)->m_map.end())
		{
			return (*it).second;
		}

		return NULL;
	}

	ItemSite* GetGroup(UI::ITreeParent* parent, UI::TextString* fielddata, int fieldind)
	{
		ItemSite* groupitem = FindGroup(parent, fielddata, fieldind);
		if (groupitem == NULL)
		{
			GroupItem* groupData = new GroupItem;
			{
				for (int i = 0; i < m_fields.GetSize(); i++)
				{
					groupData->m_fieldData.Add(NULL);
					groupData->m_fieldUI.Add(new UI::TextString(WSTR("")));
				}
			}
		//	groupData->m_field.push_back(new TextString(fielddata->get_textContent()));
		//	i++;

			groupitem = new ItemSite(m_TreeControl);
			groupitem->m_item = groupData;
			{
				for (int i = 0; i < m_fields.GetSize(); i++)
				{
					UI::UIElement* fieldUI = groupData->GetFieldUI(i);
				//	if (fieldUI)
					{
						groupitem->AppendColumnCell(fieldUI);
					}
					/*
					else
					{
						groupitem->AppendColumnCell(new TextString(L""));
					}
					*/
				}
			}

			dynamic_cast<MapParent*>(parent)->m_map.insert(tymap::value_type(fielddata->get_TextContent(), groupitem));
			ASSERT(0);
#if 0
			parent->get_Children()->AppendItem(groupitem);
#endif
		}

		return groupitem;
	}

	vector<int> m_groupBy;

	IItemSite* AddItem(IItem* item)
	{
		ItemSite* site = new ItemSite(m_TreeControl);
		site->m_item = item;

	//	site->m_treeitem = new TreeItem(m_TreeControl);
	//	site->m_treeitem->m_itemData = site;

		UI::ITreeParent* group = m_TreeControl;
		int i;

		for (i = 0; i < m_groupBy.GetSize(); i++)
		{
			UI::TextString* fielddata = dynamic_cast<UI::TextString*>(item->GetFieldUI(m_groupBy[i]));
			group = GetGroup(group, fielddata, m_groupBy[i]);
		}

		//UIControl* fieldUI = item->GetFieldUI(m_fields[groupBy[i]]);
		//temSite* pGroup = GetGroup(fieldUI

		for (i = 0; i < m_fields.GetSize(); i++)
		{
			UI::UIElement* fieldUI = item->GetFieldUI(i);
			if (fieldUI)
			{
				site->AppendColumnCell(fieldUI);
			}
			else
			{
				site->AppendColumnCell(new UI::TextString(WSTR("")));
			}
		}
//		site->/*m_treeitem->*/addEventListener(L"ItemStateChanging", site, false);

		{
			if (dynamic_cast<ItemSite*>(group))
			{
				for (int i = 0; i < m_fields.GetSize(); i++)
				{
					dynamic_cast<GroupItem*>(dynamic_cast<ItemSite*>(group)->m_item)->m_fieldData[i] = item->GetFieldData(i);
					dynamic_cast<UI::TextString*>(dynamic_cast<ItemSite*>(group)->m_item->GetFieldUI(i))->set_TextContent(dynamic_cast<UI::TextString*>(item->GetFieldUI(i))->get_TextContent());
				}
			}
		}

		ASSERT(0);
#if 0
		group->get_Children()->AppendItem(site);
#endif
	//	m_TreeControl->get_Children()->InvalidateMeasure();	// TODO remove

		m_items.Add(site);

		return site;
	}

	void RemoveItem(IItemSite* isite)
	{
		ItemSite* site = dynamic_cast<ItemSite*>(isite);
		m_TreeControl->get_Children()->RemoveRChild(site);
	}

	void AddField(System::StringW* name)
	{
		m_fields.Add(name);
		m_TreeControl->AddColumn(new UI::TextString(name));
	}

	unsigned int GetCount()
	{
		return m_items.GetSize();
	}
	
	IItem* GetItem(unsigned int index)
	{
		return m_items[index]->m_item;
	}

	vector<ItemSite*> m_items;
};

}

#endif // __Item_h__
