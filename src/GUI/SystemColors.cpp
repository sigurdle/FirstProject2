#include "stdafx.h"
#include "GUI2.h"
//#include "wmf.h"

namespace System
{
namespace Gui
{

SolidColorBrush* SystemColors::get_ActiveBorderBrush()
{
	static SolidColorBrush ActiveBorderBrush(ColorF::FromCOLORREF(GetSysColor(COLOR_ACTIVEBORDER)));
	return &ActiveBorderBrush;
}

SolidColorBrush* SystemColors::get_ActiveCaptionBrush()
{
	static SolidColorBrush ActiveCaptionBrush(ColorF::FromCOLORREF(GetSysColor(COLOR_ACTIVECAPTION)));
	return &ActiveCaptionBrush;
}

SolidColorBrush* SystemColors::get_ActiveCaptionTextBrush()
{
	static SolidColorBrush ActiveCaptionTextBrush(ColorF::FromCOLORREF(GetSysColor(COLOR_CAPTIONTEXT)));
	return &ActiveCaptionTextBrush;
}

SolidColorBrush* SystemColors::get_AppWorkspaceBrush()
{
	static SolidColorBrush AppWorkspaceBrush(ColorF::FromCOLORREF(GetSysColor(COLOR_APPWORKSPACE)));
	return &AppWorkspaceBrush;
}

}	// Gui
}	// System
