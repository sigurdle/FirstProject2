namespace System
{

class PropertiesTable : public UI::Control
{
public:

	CTOR PropertiesTable(IObjectCollection* pCollection);

	void CreateColumns(const Type_Info* ti);

	void Build(IObjectCollection* pCollection, UI::ITreeParent* parent);

	//std::map<StringA, Property*> m_properties;
	vector<System::Property*> properties;
	UI::TreeControl* m_pTree;
//	UI::TreeItemChildren* m_pChildren;
	//ICollection* m_pCollection;

	//UI::TreeItemChildren* GetGroup(Property* pProperty, _Object* obj);
	UI::TreeItemChildren* GetGroup(UI::TreeItemChildren* group, System::Object* obj, int fieldind);

	vector<int> m_groupBy;

	class GroupItem : public System::Object
	{
	public:
		map<Comparable, UI::TreeItemChildren*> m_groups;
	};
};

}
