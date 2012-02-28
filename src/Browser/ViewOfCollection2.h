#pragma once

namespace System
{

class ViewOfCollection2 : public UI::Control, public IViewOf
{
public:
	ViewOfCollection2(IObjectCollection* pCollection)
	{
		m_pCollection = pCollection;
		m_bExpanded = false;

		Build();
	}

	virtual System::Object* get_Viewable()
	{
		return dynamic_cast<System::Object*>(m_pCollection);
	}

	virtual void set_Viewable(System::Object* pViewable)
	{
	}

	bool m_bExpanded;
	vector<UI::TreeItem*> m_rows;

	void Build();

	void ExpandRows(UI::TreeControl* tree);

	IObjectCollection* m_pCollection;
};

}
