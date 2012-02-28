namespace System
{
namespace Gui
{

enum Dock
{
	Dock_Left = 1,
	Dock_Top = 2,
	Dock_Right = 3,
	Dock_Bottom = 4,
	Dock_Fill = 5
};

class GUIEXT DockPanel : public Panel
{
public:
	CTOR DockPanel();

//	void RemoveChildren();

	static Dock GetDock(DependencyObject* pObject);
	static void SetDock(DependencyObject* pObject, Dock dock);
	static void ClearDock(DependencyObject* pObject);

	DEPENDENCY_PROPERTY(Dock, Dock)
	DEPENDENCY_PROPERTY(bool, LastChildFill)

	DEPENDENCY_CLASS(DockPanel, Panel)

	/*
	static DependencyProperty* get_DockProperty()
	{
		return s_DockProperty;
	}

	static DependencyProperty* get_LastChildFillProperty()
	{
		return s_LastChildFillProperty;
	}
	*/

protected:

	virtual gm::SizeF MeasureOverride(gm::SizeF availSize);
	virtual gm::SizeF ArrangeOverride(gm::SizeF finalSize);

	/*
private:

	static DependencyProperty* s_DockProperty;
	static DependencyProperty* s_LastChildFillProperty;
	*/
};

}	// Gui
}	// System
