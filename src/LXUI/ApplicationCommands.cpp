#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

RoutedUICommand* ApplicationCommands::s_Cut = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Copy = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Paste = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Undo = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Redo = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Open = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Save = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_SaveAs = new RoutedUICommand;
RoutedUICommand* ApplicationCommands::s_Close = new RoutedUICommand;

}	// UI
}
