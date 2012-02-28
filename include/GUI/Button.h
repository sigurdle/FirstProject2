namespace System
{
namespace Gui
{

/** \addtogroup GUI
@{
*/

/**
Represents the baseclass for gui button-like controls
*/

class GUIEXT ButtonBase : public ContentControl
{
public:
	CTOR ButtonBase(DependencyClass* depClass);
	CTOR ButtonBase(DependencyClass* depClass, Object* content);

	DEPENDENCY_CLASS_ABSTRACT(ButtonBase, ContentControl)
};

/**
Represents a gui button control
*/

class GUIEXT Button : public ButtonBase
{
public:

/**
Initializes a new instance of the button control
*/
	CTOR Button();
/**
Initializes a new instance of the button control
@param content to set the content of the button
*/
	CTOR Button(Object* content);

	DEPENDENCY_CLASS(Button, ButtonBase)

	DEFINE_THIS(_Button)

	ROUTEDEVENT(RoutedEventArgs, Click) {}

protected:

	virtual void OnMouseLeftButtonDown(MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(MouseButtonEventArgs* args) override;

	void Init();
};

class GUIEXT _Button : public _ContentControl
{
public:

	CTOR _Button(Expressive::ObjectExpression* objectExp) : _ContentControl(objectExp)
	{
	}

	Expressive::typed_expression<Object*> getContent() const
	{
		return getProperty(Button::get_ContentProperty());
	}
};

/** @} */

}	// Gui
}	// System
