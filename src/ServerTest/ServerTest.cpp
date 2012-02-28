// ServerTest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "ServerTest.h"
#include "../LXUI/Remoting.h"

using namespace System;

#pragma comment(lib, "../LFC/Debug/LFC.lib")
//#pragma comment(lib, "../Draw/Debug/Draw.lib")
#pragma comment(lib, "../LXUI/Debug/LXUI.lib")

namespace System
{
namespace UI
{
LXUIEXT extern int g_nWindows;
}
}

int APIENTRY WinMain(MSWindows::HINSTANCE hInstance,
							MSWindows::HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	InitTypes();

//	LDraw::Init();

//	InitTypes();

	Remoting::ListenerSocket* pSocket = new Remoting::ListenerSocket;
	pSocket->Create(500);
	pSocket->Listen();

	UI::g_nWindows++;

	UI::MessageLoop loop;

	loop.Run();

	return 0;
}
