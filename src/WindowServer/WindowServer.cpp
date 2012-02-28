// WindowServer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#define Array array
#include <windows.h>
//#include <ntgdityp.h>
//#include <ntgdi.h>

#include <gl/gl.h>

#include "../windows_header.h"

#include "WindowServer.h"

//#undef Array

#ifdef _DEBUG
#pragma comment(lib, "../LFC/Debug/LFC.lib")
#pragma comment(lib, "../LXUI/Debug/LXUI.lib")
#else
#pragma comment(lib, "../LFC/Release/LFC.lib")
#pragma comment(lib, "../LXUI/ReleaseMinSize/LXUI.lib")
#endif

using namespace System;

BOOL bSetupPixelFormat(HDC hdc)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(hdc, &pfd)) == 0 )
	{
		ASSERT(FALSE);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	return TRUE;
}

HGLRC m_hrc;

#pragma comment(lib, "opengl32.lib")

void CreateContext(HDC hdc, RECT& rc)
{
	PIXELFORMATDESCRIPTOR pfd;
//	GLfloat     fMaxObjSize, fAspect;
//	GLfloat     fNearPlane, fFarPlane;

	if (!bSetupPixelFormat(hdc))
		return;

#if 0
	CreateRGBPalette(hdc);

	::SelectPalette(hdc, m_hPal, FALSE);
	::RealizePalette(hdc);
#endif

	int n = ::GetPixelFormat(hdc);
	::DescribePixelFormat(hdc, n, sizeof(pfd), &pfd);


	m_hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, m_hrc);

#if 0
	glClearDepth(10.0f);
	glEnable(GL_DEPTH_TEST);

	if (rc.bottom)
		fAspect = (GLfloat)rc.right/rc.bottom;
	else    // don't divide by zero, not that we should ever run into that...
		fAspect = 1.0f;
	fNearPlane = 3.0f;
	fFarPlane = 20.0f;
	fMaxObjSize = 3.0f;
	m_fRadius = fNearPlane + fMaxObjSize / 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, fAspect, fNearPlane, fFarPlane);
	glMatrixMode(GL_MODELVIEW);
#endif
}

namespace System
{
namespace UI
{
LXUIEXT extern int g_nWindows;
}
}

namespace System
{
namespace WindowServer
{

void ClientSocket::OnReceive(int nErrorCode)
{
	uint16 cmd;
	int nread = Read(&cmd, 2);

	if (cmd == 1)
	{
		TRACE("Create Window\n");

		UI::WindowBase2* pBase2 = new UI::WindowBase2;
		m_pElement = pBase2;

		pBase2->set_Width(new UI::Length(400));
		pBase2->set_Height(new UI::Length(400));

		UI::CUIFrameImpl* frame = new UI::CUIFrameImpl;
		m_frame = frame;
		frame->SetClient(pBase2);
		frame->Show();

		uint8 msgid = 4;
		Send(&msgid, 1);
	}
	else if (cmd == 6)
	{
		LDraw::RectI rect;
		Read(&rect, sizeof(rect));

		m_pElement->m_pDrawCommands = new LDraw::Commands;
		LDraw::GraphicsMetafile graphics(m_pElement->m_pDrawCommands);

		LDraw::SolidBrush* pBrush = new LDraw::SolidBrush(LDraw::Color(255, 0, 0));

		graphics.FillRectangle(pBrush, rect.X, rect.Y, rect.Width, rect.Height);

		m_pElement->m_bRedraw = true;
		m_frame->m_redrawList = m_pElement;
		m_frame->m_invalidRegion = new LDraw::Region(LDraw::RectI(0, 0, 400, 400));
		//m_frame->m_invalidRegion->MakeInfinite();

		m_frame->Render();
	}

	/*
	TRACE("OnRead\n");

	char buf[512];
	int nRead = Receive(buf, 512);

//	::MessageBox(NULL, buf, NULL, MB_OK);
*/
}

void ListenerSocket::OnAccept(int nErrorCode)
{
	ClientSocket* pSocket = new ClientSocket;
	Accept(pSocket);
	if (pSocket->m_socket != INVALID_SOCKET)
	{
	}
	else
		delete pSocket;

	TRACE("OnAccept %d\n", (int)pSocket->m_socket);
}

}
}

typedef void* (__stdcall * NtGdiDdCreateDirectDrawObject)(void* hdc);

int APIENTRY WinMain(MSWindows::HINSTANCE hInstance,
                     MSWindows::HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	/*
	MSWindows::HINSTANCE os = MSWindows::LoadLibraryA("d3d8thk.dll");

	NtGdiDdCreateDirectDrawObject p = (NtGdiDdCreateDirectDrawObject)MSWindows::GetProcAddress(os, "OsThunkDdCreateDirectDrawObject");

	MSWindows::HDC hdc = MSWindows::GetDC(NULL);

	void* dd = p(hdc);
	*/

	InitTypes();

	LDraw::Init();

//	InitTypes();

	WindowServer::ListenerSocket* pSocket = new WindowServer::ListenerSocket;
	pSocket->Create(500);
	pSocket->Listen();

	{
		UI::WindowBase2* pBase2 = new UI::WindowBase2;
	//	m_pElement = pBase2;

		pBase2->set_Width(new UI::Length(400));
		pBase2->set_Height(new UI::Length(400));

		UI::CUIFrameImpl* frame = new UI::CUIFrameImpl;
		//m_frame = frame;
		frame->SetClient(pBase2);
		frame->Show();

		HDC hdc = GetDC((HWND)frame->m_hWnd);

		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = 0;
		rc.bottom = 0;
		CreateContext(hdc, rc);

		glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glEnd();
	}
	UI::g_nWindows++;

	UI::MessageLoop loop;

	loop.Run();

	return 0;
}
