namespace System
{
namespace Gui
{

class GUIEXT Clipboard : public DependencyObject
{
public:

	CTOR Clipboard();

	/*
	static String get_Text();
	static void set_Text(typed<String> text);
	*/

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	static IDataObjectPtr GetDataObject();
	static void SetDataObject(IDataObjectPtr dataObject);

	static String GetText();
	static void SetText(StringIn text);

	static Clipboard* get_Current();

	DEPENDENCY_CLASS(Clipboard, DependencyObject)

	DEPENDENCY_PROPERTY(uint32, Format)
	DEPENDENCY_PROPERTY(String, FormatName)
	DEPENDENCY_PROPERTY(String, MimeType)
	DEPENDENCY_PROPERTY(String, Text)

	Event0 DataChanged;

private:

	static Clipboard* Current;
};

}	// Gui
}	// System
