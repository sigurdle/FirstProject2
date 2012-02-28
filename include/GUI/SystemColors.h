namespace System
{
namespace Gui
{

class GUIEXT SystemColors
{
public:

	static SolidColorBrush* get_ActiveBorderBrush();
	static SolidColorBrush* get_ActiveCaptionBrush();
	static SolidColorBrush* get_ActiveCaptionTextBrush();
	static SolidColorBrush* get_AppWorkspaceBrush();

	/*
	ActiveWindowBorder
	ActiveWindowCaption
*/

private:

	CTOR SystemColors();
};

}	// Gui
}	// System
