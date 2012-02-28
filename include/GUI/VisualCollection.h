namespace System
{
namespace Gui
{

class GUIEXT VisualCollection : public Object, public ICollection<Visual*>
{
public:

	CTOR VisualCollection();
	CTOR VisualCollection(Object* owner);

	virtual const Type_Info& GetItemType() const override;
	virtual size_t GetCount() override;
	virtual void Clear() override;
	virtual void AddObject(Object* element) override;
	virtual void Add(Visual* element) override;
	virtual void Insert(UIElement* before, UIElement* child);
	virtual Object* get_ObjectItem(size_t index) override;

	virtual String ToString() override;

	Object* m_owner;
	vector<Visual*> m_items;
};

}	// Gui
}	// System
