namespace System
{

class PropertiesTable;

class ViewOfCollection : public UI::Control, public IViewOf
{
public:

	CTOR ViewOfCollection();//DirectoryObject* pDir);

	static const Type_Info& GetType()
	{
		return typeid(IObjectCollection);
	}

	virtual System::Object* get_Viewable()
	{
		return dynamic_cast<System::Object*>(m_pCollection);
	}

	virtual void set_Viewable(System::Object* pViewable)
	{
		Refresh(dynamic_cast<IObjectCollection*>(pViewable));
	}

	void Refresh(IObjectCollection* pCollection);

	//FileObject* m_pSelectedFile;
	//int m_selection;

	//UI::ChildWindowContainer* m_pCanvas;

//	virtual void handleEvent(System::Event* evt);

public:
	IObjectCollection* m_pCollection;
	const Type_Info* m_ti;
	PropertiesTable* m_table;
	UI::TreeItem* m_pSelectedItem;
};

}
