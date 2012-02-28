#include "stdafx.h"
#include "LXUI2.h"

#include "SolidColorBrush.h"

#include <windows.h>

namespace System
{
namespace UI
{

Color FromCOLORREF(COLORREF clr)
{
	return Color(GetRValue(clr), GetGValue(clr), GetBValue(clr));
}

// TODO, Frozen
SolidColorBrush SystemColors::s_ActiveBorderBrush(FromCOLORREF(GetSysColor(COLOR_ACTIVEBORDER)));
SolidColorBrush SystemColors::s_ActiveCaptionBrush(FromCOLORREF(GetSysColor(COLOR_ACTIVECAPTION)));
SolidColorBrush SystemColors::s_ActiveCaptionTextBrush(FromCOLORREF(GetSysColor(COLOR_CAPTIONTEXT)));
SolidColorBrush SystemColors::s_AppWorkspaceBrush(FromCOLORREF(GetSysColor(COLOR_APPWORKSPACE)));

ResourceKey* SystemColors::s_ActiveBorderColorKey;
ResourceKey* SystemColors::s_ActiveBorderBrushKey;

ResourceKey* SystemColors::s_ActiveCaptionColorKey;
ResourceKey* SystemColors::s_ActiveCaptionBrushKey;

ResourceKey* SystemColors::s_ActiveCaptionTextColorKey;
ResourceKey* SystemColors::s_ActiveCaptionTextBrushKey;

ResourceKey* SystemColors::s_AppWorkspaceColorKey;
ResourceKey* SystemColors::s_AppWorkspaceBrushKey;

Color SystemColors::get_ActiveBorderColor()
{
	return s_ActiveBorderBrush.get_Color();
}

SolidColorBrush* SystemColors::get_ActiveBorderBrush()
{
	return &s_ActiveBorderBrush;
}

Color SystemColors::get_ActiveCaptionColor()
{
	return s_ActiveCaptionBrush.get_Color();
}

SolidColorBrush* SystemColors::get_ActiveCaptionBrush()
{
	return &s_ActiveCaptionBrush;
}

Color SystemColors::get_ActiveCaptionTextColor()
{
	return s_ActiveCaptionTextBrush.get_Color();
}

SolidColorBrush* SystemColors::get_ActiveCaptionTextBrush()
{
	return &s_ActiveCaptionTextBrush;
}

Color SystemColors::get_AppWorkspaceColor()
{
	return s_AppWorkspaceBrush.get_Color();
}

SolidColorBrush* SystemColors::get_AppWorkspaceBrush()
{
	return &s_AppWorkspaceBrush;
}

}	// UI
}
