namespace System
{
namespace Gui
{

class GUIEXT TextElement : public UIElement
{
public:

	CTOR TextElement();

	DEPENDENCY_PROPERTY(float, FontSize)
	DEPENDENCY_PROPERTY(FontFamily*, FontFamily)
	DEPENDENCY_PROPERTY(int, FontWeight)
	DEPENDENCY_PROPERTY(FontStyle, FontStyle)
	DEPENDENCY_PROPERTY(String, Text)
	DEPENDENCY_PROPERTY(ITextSource*, TextSource)
//	DEPENDENCY_PROPERTY(Geometry*, LayoutRect)
	DEPENDENCY_PROPERTY(Brush*, Brush)

	DEPENDENCY_CLASS(TextElement, UIElement)

//	static DependencyClass* get_Class();
//	static DependencyClass* pClass;
};

#if 0
class GUIEXT _TextElement : public _UIElement
{
public:

	CTOR _TextElement(Expressive::StaticObjectExpression* objectExp) : _UIElement(objectExp)
	{
	}

	Expressive::typed_expression<float> getFontSize() const
	{
		return getProperty(TextElement::get_FontSizeProperty());
	}

	/*
	Expressive::methodcall0<float> getWidth() const
	{
		return new Expressive::MethodCall0Expression(*this, GetDispatch(typeid(TextVisual).GetType()->GetClass())->GetMethod(ASTR("getWidth")));
	}

	Expressive::methodcall0<float> getWidthIncludingTrailingWhitespace() const
	{
		return new Expressive::MethodCall0Expression(*this, GetDispatch(typeid(TextVisual).GetType()->GetClass())->GetMethod(ASTR("getWidthIncludingTrailingWhitespace")));
	}

	Expressive::methodcall0<float> getHeight() const
	{
		return new Expressive::MethodCall0Expression(*this, GetDispatch(typeid(TextVisual).GetType()->GetClass())->GetMethod(ASTR("getHeight")));
	}

	Expressive::methodcall0<float> DetermineMinWidth() const
	{
		return new Expressive::MethodCall0Expression(*this, GetDispatch(typeid(TextVisual).GetType()->GetClass())->GetMethod(ASTR("DetermineMinWidth")));
	}
	*/
};
#endif

}	// Gui
}	// System
