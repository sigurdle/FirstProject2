namespace System
{
namespace Gui
{

class GUIEXT ScrollViewer : public ContentControl
{
public:
	CTOR ScrollViewer();

	DEPENDENCY_PROPERTY(float, ExtentWidth)
	DEPENDENCY_PROPERTY(float, ExtentHeight)
	DEPENDENCY_PROPERTY(float, ScrollableWidth)
	DEPENDENCY_PROPERTY(float, ScrollableHeight)
	DEPENDENCY_PROPERTY(float, ViewportWidth)
	DEPENDENCY_PROPERTY(float, ViewportHeight)
	DEPENDENCY_PROPERTY(float, HorizontalOffset)
	DEPENDENCY_PROPERTY(float, VerticalOffset)

	DEPENDENCY_CLASS(ScrollViewer, ContentControl)
};

}	// Gui
}	// System
