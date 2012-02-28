namespace System
{
namespace Gui
{

enum TextAlignment
{
	TextAlignment_Left,
	TextAlignment_Right,
	TextAlignment_Center,
	TextAlignment_Justify
};

enum VerticalAlignment
{
	VerticalAlignment_Top,
	VerticalAlignment_Bottom,
	VerticalAlignment_Center,
};

enum TextWrapping
{
	TextWrapping_Wrap,
	TextWrapping_NoWrap,
};

enum TextTrimming
{
	TextTrimming_None
};

class GUIEXT TextVisual : public UIElement
{
public:

	CTOR TextVisual();
	CTOR TextVisual(typed<String> text, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight);
	CTOR TextVisual(typed<String> text, typed<ITextSource*> textsource, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight);

	virtual void Render(ManagedRenderContext renderContext);
	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	virtual void OnMouseLeftButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseMove(Gui::MouseEventArgs* args) override;
	virtual void OnKey(KeyEventArgs* args) override;
	virtual void OnTextComposition(TextCompositionEventArgs* args) override;

	DEFINE_THIS(_TextVisual)

	DEPENDENCY_PROPERTY(String, FontFamily)
	DEPENDENCY_PROPERTY(float, FontSize)
	DEPENDENCY_PROPERTY(int, FontWeight)
	DEPENDENCY_PROPERTY(FontStyle, FontStyle)

	DEPENDENCY_PROPERTY(TextAlignment, TextAlignment)
	DEPENDENCY_PROPERTY(TextWrapping, TextWrapping)
	DEPENDENCY_PROPERTY(TextTrimming, TextTrimming)
	DEPENDENCY_PROPERTY(VerticalAlignment, VerticalAlignment)

	DEPENDENCY_PROPERTY(String, Text)
	DEPENDENCY_PROPERTY(ITextSource*, TextSource)
	DEPENDENCY_PROPERTY(Geometry*, LayoutRect)
	DEPENDENCY_PROPERTY(Brush*, Brush)
	DEPENDENCY_PROPERTY(int, CursorPosition)
	DEPENDENCY_PROPERTY(int, CursorLine)
	DEPENDENCY_PROPERTY(int, CursorColumn)
	DEPENDENCY_PROPERTY_RO(int, LineCount)

	// Computed properties
	DEPENDENCY_PROPERTY_RO(float, WidthIncludingTrailingWhitespace)	// read-only
	DEPENDENCY_PROPERTY_RO(float, TextMinWidth)	// read-only

	DEPENDENCY_CLASS(TextVisual, UIElement)

	void OnTextSourceContentChanged(ITextSource*, TextSourceChangeEventArgs args);

	float getWidth();
	float getHeight();
	float DetermineMinWidth();

	float getWidthIncludingTrailingWhitespace();

	uint GetTextLength();

protected:

	virtual gm::SizeF MeasureOverride(gm::SizeF availSize) override;
	virtual gm::SizeF ArrangeOverride(gm::SizeF size) override;

	bool EnsureDWriteTextFormat();

private:

	bool EnsureLayout();
	void EnsureFormatted(ManagedRenderContext renderContext);

	ComPtr<IDWriteTextFormat> m_DWriteTextFormat;
	ComPtr<IDWriteTextLayout> m_DWriteTextLayout;
	bool m_formatted;

	// TODO
	// DWRITE_TEXT_METRICS m_textMetrics;
};

class GUIEXT _TextVisual : public _UIElement
{
public:

	CTOR _TextVisual(Expressive::StaticObjectExpression* objectExp) : _UIElement(objectExp)
	{
	}

	Expressive::typed_expression<float> getFontSize() const
	{
		return getProperty(TextVisual::get_FontSizeProperty());
	}

	Expressive::methodcall0<float> getWidth() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(TextVisual).GetType()->AsClass())->GetMethod("getWidth"));
	}

	Expressive::methodcall0<float> getWidthIncludingTrailingWhitespace() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(TextVisual).GetType()->AsClass())->GetMethod("getWidthIncludingTrailingWhitespace"));
	}

	Expressive::methodcall0<float> getHeight() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(TextVisual).GetType()->AsClass())->GetMethod("getHeight"));
	}

	Expressive::methodcall0<float> DetermineMinWidth() const
	{
		return new Expressive::MethodCall0Expression<float>(*this, GetDispatch(typeid(TextVisual).GetType()->AsClass())->GetMethod("DetermineMinWidth"));
	}
};

}	// Gui
}	// System
