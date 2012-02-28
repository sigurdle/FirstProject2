namespace System
{
namespace Gui
{

class GUIEXT Cursor : public DependencyObject
{
public:

	CTOR Cursor();
	CTOR Cursor(HCURSOR hCursor);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	virtual HCURSOR GetHCursor();

	DEPENDENCY_CLASS(Cursor, DependencyObject)

	DEPENDENCY_PROPERTY(Visual*, Image)
	DEPENDENCY_PROPERTY(float, HotspotX)
	DEPENDENCY_PROPERTY(float, HotspotY)

private:

	HCURSOR m_hCursor;
};

}	// Gui
}	// System
