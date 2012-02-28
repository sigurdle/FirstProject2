#include "stdafx.h"
#include "LDebugger.h"
#include "DebuggerFrame.h"
#include "SourceEditFrame.h"
#include "DisassemblyWnd.h"
#include "CallStackWnd.h"
#include "WatchWnd.h"
#include "DebugSession.h"

//#include "zip.h"

//#include "../ljavac/cppcompiler.h"
#include "../CodeComp/cpp_ast.h"

#if 0
#include "../LXML/ASXMLSchemaModel.h"

#define ASGRAPHEXT DECLSPEC_DLLIMPORT
#include "../ASEditCtlsMod/ASGraphCtl.h"
#pragma comment(lib, "../ASEditCtlsMod/Debug/ASEditCtlsMod.lib")
#endif

#if WIN32

#if 0
#include "aboutdlg.h"
#include "AttachProcessDlg.h"
#include "ThreadsDlg.h"
#include "ModulesDlg.h"
#include "BreakpointsDlg.h"
#endif

#include "WatchWnd.h"

#endif

namespace System
{
namespace Debugger
{
using namespace std;

extern Scope* pGlobalScope;

void DrawYellowArrow(UI::Graphics* pGraphics, double midy);

// Pretty a pathname
void FixPathName(char* dest, int numberOfElements, const char* src)
{
#if 0//_WINDOWS
	PathCanonicalize(dest, src);
	char* p = dest;
	while (*p)
	{
		if (*p == '\\')
		{
			*p = '/';
		}
		p++;
	}
#else
	strcpy_s(dest, numberOfElements, src);
#endif
}


#if WIN32

/*
class StyledXMLViewer : public Control
{
public:
};
*/


void CRegistersWnd::OnRender(UI::Graphics* pGraphics)
{
#if 0
	HFONT hOldFont = dc.SelectFont((HFONT)GetStockObject(ANSI_FIXED_FONT));

	if (g_pt)
	{
		char buf[64];

		sprintf(buf, "Eax: 0x%x", g_pt->m_context.Eax);
		dc.TextOut(0, 17*0, buf);

		sprintf(buf, "Ebx: 0x%x", g_pt->m_context.Ebx);
		dc.TextOut(116, 17*0, buf);

		sprintf(buf, "Ecx: 0x%x", g_pt->m_context.Ecx);
		dc.TextOut(0, 17*1, buf);

		sprintf(buf, "Edx: 0x%x", g_pt->m_context.Edx);
		dc.TextOut(116, 17*1, buf);

		sprintf(buf, "Ebp: 0x%x", g_pt->m_context.Ebp);
		dc.TextOut(0, 17*2, buf);

		sprintf(buf, "Eip: 0x%x", g_pt->m_context.Eip);
		dc.TextOut(116, 17*2, buf);

		sprintf(buf, "Esp: 0x%x", g_pt->m_context.Esp);
		dc.TextOut(0, 17*3, buf);
	}

	dc.SelectFont(hOldFont);
#endif
}

#endif	// WIN32

	/*
class PSDViewer : public Control
{
public:
	virtual void OnRender2(LDraw::Graphics* pGraphics)
	{
	}
};
*/

class LayerBitmap : public Object
{
public:
	LayerBitmap()
	{
		m_pBitmap = NULL;
	}

	StringA m_name;

	int m_width;
	int m_height;

	LDraw::Bitmap* m_pBitmap;
};

class LayersComposition : public UI::FrameworkElement
{
public:
	CTOR LayersComposition();

	double m_width;
	double m_height;

	vector<LayerBitmap*> m_subLayers;

	virtual void OnRender2(UI::Graphics* pGraphics)
	{

		/*
		pGraphics->DrawString("!", 1, font, LDraw::PointF(0, 16), &LDraw::SolidBrush(LDraw::Color::Black));

		pGraphics->ScaleTransform(10, 10);

		pGraphics->DrawString("!", 1, font, LDraw::PointF(0, 16), &LDraw::SolidBrush(LDraw::Color::Black));
		*/

		for (int i = 0; i < m_subLayers.size(); i++)
		{
			LayerBitmap* pLayerBitmap = m_subLayers[i];

			pGraphics->DrawImage(pLayerBitmap->m_pBitmap, 0, 0);
		}
	}

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize)
	{
		return LDraw::SizeD(m_width,  m_height);
	}
};

class TimelineController
{
public:

	UI::Media::Timeline* m_timeline;
};

class TimelineView : public UI::FrameworkElement
{
public:

	TimelineController* m_controller;
};


#if 0

#include "../PageDesigner/psd.h"
//#include "../Include/FileReader.h"

LayersComposition::LayersComposition()
{
	PSDFile* pPSDFile = new PSDFile;
	if (pPSDFile)
	{
		//HANDLE hFile = CreateFile("C:\\test.psd", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		FileByteStream file("C:\\test.psd");

		pPSDFile->Load(&file);

		{
			PSDHEADER hdr;
			pPSDFile->GetFileInfo(&hdr);

			m_width = hdr.cols;
			m_height = hdr.rows;

			long nlayers = pPSDFile->GetNumLayers();

			for (int i = 0; i < nlayers; i++)
			{
				LayerBitmap* pLayer = new LayerBitmap;

				ILayer* pFileLayer = pPSDFile->GetNLayer(i);

				pLayer->m_name = pFileLayer->GetName();

				LAYERINFO layerinfo;
				pFileLayer->GetLayerInfo(&layerinfo);

				int layerWidth = layerinfo.rect.right - layerinfo.rect.left;
				int layerHeight = layerinfo.rect.bottom - layerinfo.rect.top;
				pLayer->m_width = layerWidth;
				pLayer->m_height = layerHeight;

				pLayer->m_pBitmap = new LDraw::Bitmap(layerWidth, layerHeight/*, PixelFormat32bppARGB*/);
				if (pLayer->m_pBitmap)
				{
					LDraw::BitmapData bitmapData;

					bitmapData.Width = pLayer->m_pBitmap->GetWidth();
					bitmapData.Height = pLayer->m_pBitmap->GetHeight();
					bitmapData.Stride = pLayer->m_pBitmap->m_rowBytes;
					bitmapData.Scan0 = pLayer->m_pBitmap->m_bitmapData;

					/*
					if (pLayer->m_pBitmap->LockBits(
						&Gdiplus::Rect(0, 0, layerWidth, layerHeight),
						Gdiplus::ImageLockModeWrite,
						PixelFormat32bppARGB,
						&bitmapData) == Gdiplus::Ok)
						*/
					{
						// blue
						pFileLayer->ReadPSDLayerChannel(2, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+0);

						// green
						pFileLayer->ReadPSDLayerChannel(1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+1);

						// red
						pFileLayer->ReadPSDLayerChannel(0, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+2);

						// alpha
						pFileLayer->ReadPSDLayerChannel(-1, bitmapData.Stride, (LPBYTE)bitmapData.Scan0+3);

				//		pLayer->m_pBitmap->UnlockBits(&bitmapData);
					}

					// Premultiply
					{
						for (int y = 0; y < bitmapData.Height; y++)
						{
							uint8* dst = bitmapData.Scan0 + y * bitmapData.Stride;
							for (int x = 0; x < bitmapData.Width; x++)
							{
								dst[0] = (int)dst[0] * dst[3] / 255;
								dst[1] = (int)dst[1] * dst[3] / 255;
								dst[2] = (int)dst[2] * dst[3] / 255;

								dst += 4;
							}
						}
					}

				//	pLayer->m_parentGroup = m_imageLayerGroup;
					/*m_imageLayerGroup->*/m_subLayers.push_back(pLayer);
				}
			}
		}
	}
}

#include "../LXML/LDOMDocument.h"

#define FTPEXT __declspec(dllimport)
#include "../FTPMod/FTPBrowser.h"
#pragma comment(lib, "../FTPMod/Debug/FTPMod.lib")


class ImageViewer : public Control
{
public:
	ImageViewer()
	{
//		m_pBitmap = new LDraw::Bitmap(L"C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.pcx");
	//	m_pBitmap = new LDraw::Bitmap(L"C:\\Files\\IFF-ILBM\\Colourfa.ham6");
		m_pBitmap = new LDraw::Bitmap(L"C:\\Movies\\iffanim\\Voyager\\Voyager.sndanim");
	}

	LDraw::Bitmap* m_pBitmap;

	virtual void OnRender2(LDraw::Graphics* pGraphics)
	{
		#if 0
		if (false)
		{
			double angle = 270;

			LDraw::LinearGradientBrush brush;
			brush.m_interpolationPositions.push_back(0);
			brush.m_interpolationPositions.push_back(1);
			brush.m_interpolationColors.push_back(LDraw::Color(255, 0, 0));
			brush.m_interpolationColors.push_back(LDraw::Color(0, 0, 255));

			brush.m_transform = gmMatrix3::identity();
	//		brush.m_transform *= gmMatrix3::scale(m_computedSize.Height, 1);
	//		brush.m_transform *= gmMatrix3::rotate(90);

			brush.m_transform =
				gmMatrix3::translate(0, m_computedSize.Height) * gmMatrix3::rotate(angle*2) * gmMatrix3::scale(m_computedSize.Height, 1) * gmMatrix3::rotate(-angle);

	//		brush.m_transform *= gmMatrix3::translate(20, 0);

			pGraphics->FillRectangle(&brush, 0, 0, m_computedSize.Width, m_computedSize.Height);
		}
		else
#endif
		{
			LDraw::ColorMatrixF colorMatrix =
			{
				1, 0, 0, 0, 0,
				0, 1, 0, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 0, 1, 0,
				0, 0, 0, 0, 1,
			};

			pGraphics->DrawImage(m_pBitmap, 0, 0, &colorMatrix);
		}
	}

	virtual void OnMeasure(LDraw::SizeD viewBox)
	{
		m_availSize = viewBox;
		if (m_pBitmap)
		{
			m_desiredSize.Width = m_pBitmap->GetWidth();
			m_desiredSize.Height = m_pBitmap->GetHeight();
		}
		else
		{
			Control::OnMeasure(viewBox);
		}
	}
};





#endif	// WIN32

//#include "HttpServer.h"

#if AMIGA

//#include <clib/asl_protos.h>
//#include <clib/netlib_protos.h>
//#include "WinHD_C:/Amiga/netinclude/bsdsocket.h"
/*
#include <sys/socket.h>
#include <netdb.h>
*/
//#include <arpa/inet.h>

#define CLIB_USERGROUP_PROTOS_H

//#include <bsdsocket.h>

typedef int SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

//#define INADDR_NONE             0xffffffff

//#define IPPROTO_TCP	PF_INET	// ??

#endif

class XPathEvaluatorControl : public UI::Control
{
public:
	XPathEvaluatorControl()
	{
		m_tree = new UI::TreeControl;
		ASSERT(0);
#if 0
		m_tree->m_treeHeader->AddColumn(new UI::TextString(WSTR("Node")));
#endif

		set_VisualTree(m_tree);
	}

	UI::TreeControl* m_tree;
};

void ExecutedHandler(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	MessageBoxA(NULL, "", "", MB_OK);
}

void CanExecuteHandler(Object* sender, UI::CanExecuteRoutedEventArgs* args)
{
	args->set_CanExecute(true);
}

void MouseMoveHandler(Object* sender, UI::MouseEventArgs* args)
{
//	MessageBoxA(NULL, "mousemove", "", MB_OK);
}

/*
void test(signal2<Object*, UI::ExecutedRoutedEventArgs*>::slot_function_type s)
{
}
*/

void OnClick(Object* sender, UI::RoutedEventArgs* args)
{
	UI::Window* wnd = new UI::Window;

	wnd->set_Title(WSTR("Title"));
	wnd->set_Content(WSTR("Content"));
	wnd->set_Opacity(0.75);

	wnd->Show();
}

/////////////////////////////////////////////////////////////////////////////////
// DebuggerFrame

DebuggerFrame::DebuggerFrame()
{

	m_pathName = NULL;
	m_list = NULL;
	m_messages = NULL;
	m_registersWnd = NULL;
	m_callStackWnd = NULL;
	m_watchWnd = NULL;
	m_buildOutputWnd = NULL;

#if 1
	{
//		const char* server = "www.lerstad.com";
//		int port = 80;

		{
#if 0
			fd_set fd = {1, temp};

			char* msg = "GET http://www.lerstad.com/index.html HTTP/1.1\r\n"
							"Host: www.lerstad.com\r\n"
						//	"Content-Length: 0\r\n"
							"\r\n";
			select(0, &fd, NULL, NULL, NULL);
			char buf[512];
			int nRead = recv(pSocket->m_socket, buf, 512, 0);

			select(0, NULL, &fd, NULL, NULL);
			int nSent = send(temp, msg, strlen(msg), 0);
#endif

		}

#if 0
		hostent* hp;
		unsigned int temp2 = inet_addr(server);
		if (temp2 == INADDR_NONE)
		{
			hp = gethostbyname(server);
		}
		else
		{
		//	unsigned int temp2 = inet_addr(server);
			hp = gethostbyaddr((char*)&temp2,sizeof(temp2),AF_INET);
		}

		if (hp)
		{
			sockaddr_in addr;
			memset(&addr, 0, sizeof(sockaddr_in));

			addr.sin_family=AF_INET;
			addr.sin_port=htons(port);
			addr.sin_addr.s_addr=*((unsigned long*)hp->h_addr);

			if (!connect(m_socket, (sockaddr*)&addr, sizeof(sockaddr_in)))
			{
				fd_set fd = {1, temp};

				char* msg = "GET http://www.lerstad.com/index.html HTTP/1.1\r\n"
								"Host: www.lerstad.com\r\n"
							//	"Content-Length: 0\r\n"
								"\r\n";

				select(0, NULL, &fd, NULL, NULL);
				int nSent = send(temp, msg, strlen(msg), 0);

				select(0, &fd, NULL, NULL, NULL);
				char buf[512];
				int nRead = recv(temp, buf, 512, 0);

				MessageBox(NULL, buf, NULL, MB_OK);
			}
		}

		closesocket(temp);

#endif
	}
#endif

	m_ctx = NULL;

	m_pLocation = NULL;

#if _WINDOWS
	m_watchWnd = NULL;
	m_registersWnd = NULL;
#endif

	m_callStackWnd = NULL;
	m_disassemblyWnd = NULL;



#if 0
	{
		//	CUIFloatingFrame* pFrame = new CUIFloatingFrame;
			CLXUIWindowElement* pFrame = new CLXUIWindowElement;
			{
				CUIDockBar* pDockbar = new CUIDockBar;
				{
					{
						Toolbar* pToolbar = new Toolbar;
						{
							Button* pButton = new Button;
							pButton->put_Content(new TextString(WSTR("Button0")));
							pToolbar->AddRChild(pButton);
						}

						{
							TextString* pText = new TextString(WSTR("Button1"));
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Button2"));
							pToolbar->AddRChild(pText);
						}
						pDockbar->DockControlBar(pToolbar);
					}

					{
						Toolbar* pToolbar = new Toolbar;
						{
							TextString* pText = new TextString(WSTR("Test0"));
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Test1"));
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Test2"));
							pToolbar->AddRChild(pText);
						}
						pDockbar->DockControlBar(pToolbar);
					}
				}
				pFrame->put_Content(pDockbar);
			}

			pFrame->SetRParent(this);
			this->m_popups.push_back(pFrame);
	}
#endif


//	LXML::Document* document = new LXML::Document;
//	document->loadXML(WSTR("<test></test>"));

#if WIN32
	set_Width(800.0);
	set_Height(600.0);
#else
	set_Width(600.0);
	set_Height(400.0);
#endif

#if 0
	if (false)
	{
	UI::DockPanel* p = new UI::DockPanel;
//	CLXUICanvas* p = new CLXUICanvas;
//	p->set_Width(new Length(320, UnitAbsolute));
//	p->set_Height(new Length(1, UnitAbsolute));
	{
		AddAccel(UI::Accel(FACCEL_CONTROL, 'o', ID_FILE_OPEN));
		AddAccel(UI::Accel(FACCEL_VIRT, VKEY_F5, ID_DEBUG_GO));
		AddAccel(UI::Accel(FACCEL_VIRT, VKEY_F10, ID_DEBUG_STEPINTO));

		{
			UI::CUIDockBar* pDockbar = new UI::CUIDockBar;
			{
				pDockbar->set_Background(new UI::SolidColorBrush(new UI::Color(236, 233, 216)));
				{
					//Gripper* pGripper = new Gripper;
				//	pGripper->set_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						UI::Toolbar* pToolbar = new UI::Toolbar;
					//	pToolbar->set_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						{

							UI::Menu* pMenu = new UI::Menu(new UI::TextString(WSTR("File")));
							{
								pMenu->AddItem(new UI::TextString(WSTR("Open")), ID_FILE_OPEN);
								pMenu->AddItem(new UI::TextString(WSTR("Save")));
								pMenu->AddItem(new UI::TextString(WSTR("Open Program")), ID_FILE_OPENPROGRAM);
								/*
								{
									UI::Menu* pMenu2 = new UI::Menu(new UI::TextString(WSTR("Debug")));
									*/
									pMenu->AddItem(new UI::TextString(WSTR("Go")), ID_DEBUG_GO);
									pMenu->AddItem(new UI::TextString(WSTR("Step Into")), ID_DEBUG_STEPINTO);
									/*
									pMenu->AddMenuItem(pMenu2);
								}
								*/
								{
									UI::Menu* pMenu2 = new UI::Menu(new UI::TextString(WSTR("Edit")));
									pMenu2->AddItem(new UI::TextString(WSTR("Cut")), ID_EDIT_CUT);
									pMenu2->AddItem(new UI::TextString(WSTR("Copy")), ID_EDIT_COPY);
									pMenu2->AddItem(new UI::TextString(WSTR("Paste")), ID_EDIT_PASTE);
									pMenu->AddMenuItem(pMenu2);
								}
								/*
								{
									Menu* pMenu2 = new Menu(new TextString(WSTR("Prefs2")));
									pMenu2->AddItem(new TextString(WSTR("Local")));
									pMenu2->AddItem(new TextString(WSTR("Global")));
									pMenu2->AddItem(new TextString(WSTR("Something")));
									{
										Menu* pMenu3 = new Menu(new TextString(WSTR("Prefs3")));
										pMenu3->AddItem(new TextString(WSTR("Local")));
										pMenu3->AddItem(new TextString(WSTR("Global")));
										pMenu3->AddItem(new TextString(WSTR("Something")));
										pMenu2->AddMenuItem(pMenu3);
									}

									pMenu->AddMenuItem(pMenu2);
								}
								*/
								pMenu->AddSeparator();
								pMenu->AddItem(new UI::TextString(WSTR("Exit")), ID_APP_EXIT);
							}
							pToolbar->AddRChild(pMenu);

#if 0
							Menu* pMenu = new Menu;
							pMenu->put_VisualTree(new Button(new TextString(WSTR("File"))));
							{
							//	CLXUIBorder* pBorder = new CLXUIBorder;
							//	pBorder->put_BackgroundBrush(new SolidColorBrush(new Color(255, 255, 255)));

								DockPanel* pPanel = new DockPanel;
								pPanel->AddRChild(new Button(new TextString(WSTR("Open"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Save"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Save As"))));
								pPanel->AddRChild(new Button(new TextString(WSTR("Exit"))));

							//	pBorder->put_Content(pPanel);
								pMenu->put_PopupContent(pPanel);
							}
							pToolbar->AddRChild(pMenu);
#endif
						}

						{
							UI::Button* pButton = new UI::Button;
							pButton->set_Content(new UI::TextString(WSTR("Save")));
							pToolbar->AddRChild(pButton);
						}

						{
							UI::Button* pButton = new UI::Button;
							pButton->set_Content(new UI::TextString(WSTR("Exit")));
							pToolbar->AddRChild(pButton);
						}

						/*
						{
							TextString* pText = new TextString(WSTR("Button0"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Button1"), font);
							pToolbar->AddRChild(pText);
						}

						{
							TextString* pText = new TextString(WSTR("Button2"), font);
							pToolbar->AddRChild(pText);
						}
						*/

						//pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
					//pDockbar->DockControlBar(pGripper);
				}

				{
				//	Gripper* pGripper = new Gripper;
				//	pGripper->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(255, 0, 0)));
					{
						UI::Toolbar* pToolbar = new UI::Toolbar;
					//	pToolbar->put_BackgroundBrush(new CLSolidColorBrush(new CLColor(0, 255, 0)));

						{
							UI::Button* pButton = new UI::Button;
							pButton->set_Content(new UI::TextString(WSTR("Cut")));
							pToolbar->AddRChild(pButton);
						}

						{
							UI::Button* pButton = new UI::Button;
							pButton->set_Content(new UI::TextString(WSTR("Copy")));
							pToolbar->AddRChild(pButton);
						}

						{
							UI::Button* pButton = new UI::Button;
							pButton->set_Content(new UI::TextString(WSTR("Paste")));
							pToolbar->AddRChild(pButton);
						}


				//		pGripper->put_Content(pToolbar);
						pDockbar->DockControlBar(pToolbar);
					}
				//	pDockbar->DockControlBar(pGripper);
				}

				/*
				{
					Toolbar* pToolbar = new Toolbar;
					{
						TextString* pText = new TextString(WSTR("Test0"), font);
						pToolbar->AddRChild(pText);
					}

					{
						TextString* pText = new TextString(WSTR("Test1"), font);
						pToolbar->AddRChild(pText);
					}

					{
						TextString* pText = new TextString(WSTR("Test2"), font);
						pToolbar->AddRChild(pText);
					}
					pDockbar->AddRChild(pToolbar);
				}
				*/
			}
			p->SetDock(pDockbar, UI::DockPanel::Top);
			p->AddRChild(pDockbar);
		}

		{
			UI::CUIDockBar* pDockbar = new UI::CUIDockBar;
			{
				pDockbar->set_Background(new UI::SolidColorBrush(new UI::Color(236, 233, 216)));
			}
			p->SetDock(pDockbar, UI::DockPanel::Bottom);
			p->AddRChild(pDockbar);
		}

		pCanvas = new UI::ChildWindowContainer;

#if 0
		if (false)
		{
			LZIP::Archive* zip = new LZIP::Archive;
			zip->Open(new FileByteStream("D:\\Program Files\\Java\\jre1.5.0_02\\lib\\javaws.jar"));

			//LZIP::File* file = zip->OpenFile("META-INF/MANIFEST.MF");
			//bool okay = zip->Check();

			DockPanel* panel = new DockPanel;

			int filecount = zip->GetFileCount();
			for (int i = 0; i < filecount; i++)
			{
				LZIP::File* file = zip->GetFile(i);//zip->OpenFile("META-INF/MANIFEST.MF");
				TextString* item = new TextString(file->GetName());
				panel->put_Dock(item, DockPanel::Top);
				panel->AddRChild(item);
			}

			{
				ChildWindow* pWindow = new ChildWindow;
				pWindow->set_Width(new Length(200, Length::UnitAbsolute));
				pWindow->set_Height(new Length(200, Length::UnitAbsolute));

				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->put_Content(panel);
				}
				pWindow->put_Content(pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->put_TitleText(WSTR("ZIP"));

				pCanvas->AddChild(pWindow);
			}
		}
#endif

#if 0
		{
			m_buildOutputWnd = new TextEdit;
			//m_buildOutputWnd->m_pFrame = this;
			{
				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(new Length(200, Length::UnitAbsolute));
				pWindow->put_Height(new Length(200, Length::UnitAbsolute));

				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->put_Content(m_buildOutputWnd);
				}
				pWindow->put_Content(pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->put_TitleText(WSTR("Build"));

				pCanvas->AddChild(pWindow);
			}
		}
#endif

		if (true)
		{
			m_callStackWnd = new CallStackWnd;
		//	m_callStackWnd->m_pFrame = this;
			{
				UI::ChildWindow* pWindow = new UI::ChildWindow;
				pWindow->set_Width(new UI::Length(200));
				pWindow->set_Height(new UI::Length(200));

				UI::ScrollViewer* pScroller = new UI::ScrollViewer;
				{
					pScroller->set_Content(m_callStackWnd);
				}
				pWindow->set_Content(pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->set_TitleText(WSTR("Call Stack"));

				pCanvas->AddChild(pWindow);
			}
		}

		{
			/*
			CFTPBrowser* ctl = new CFTPBrowser;
//			ctl->m_treeCtl->m_pFont = font;

			ctl->m_ServerName = WSTR("ftp://lerstad.com");
			ctl->m_UserName = WSTR("w00005125");
			ctl->m_Password = WSTR("A7h2GH");

			ctl->Connect();
			*/

#if 0
			{
#if 0
				LXML::DTDDocument* dtddoc = new LXML::DTDDocument;
				//dtddoc->Load(L"C:\\Dev\\DTD\\nitf-3-2-no-comments.dtd");
				dtddoc->Load(L"C:\\NITF\\2.5\\dtd\\nitf-2-5.dtd");

				LXML::CASDTDModel* pModel = new LXML::CASDTDModel;
				pModel->BuildFromDTDDocument(dtddoc);

				LXML::CLDOMDocument* document = new LXML::CLDOMDocument;
				document->load(WSTR("C:/Program Files/Altova/XMLSpy2005/Examples/address.xsd"));

				LXML::CASXMLSchemaModel* pModel = new LXML::CASXMLSchemaModel;
				pModel->BuildFromDocument(document);

				CASGraphCtl* ctl = new CASGraphCtl;
				ctl->put_asRootObject(dynamic_cast<IASDeclaration*>(pModel->get_elementDeclarations()->item(0)));
#endif

				XPathEvaluatorControl* ctl = new XPathEvaluatorControl;

				LXML::CLDOMDocument* pDocument = new LXML::CLDOMDocument;
				pDocument->loadXML(WSTR("<test><el att='1'/><el att='2'/><el/></test>"));

				LXML::XPathExpression* exp = pDocument->createExpression(L"child::test[attribute::att]", NULL);

				LXML::XPathResult* result = exp->evaluate(pDocument->get_documentElement(), ANY_TYPE, NULL);

				for (int i = 0; i < result->m_result->nodeList->get_length(); i++)
				{
					TreeItem* item = new TreeItem(ctl->m_tree);
					{
						item->AppendColumnCell(new TextString(result->m_result->nodeList->item(i)->get_nodeName()));
					}
					ctl->m_tree->get_Children()->AppendItem(item);
				}

				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(new Length(200, Length::UnitAbsolute));
				pWindow->put_Height(new Length(200, Length::UnitAbsolute));
				ScrollViewer* pScroller = new ScrollViewer;
				{
					pScroller->put_Content(ctl);
				}
				pWindow->put_Content(pScroller);
				pWindow->put_TitleText(WSTR("Test"));
				pCanvas->AddChild(pWindow);
			}
#endif
		}

			/*
			TreeControl* ctl = new TreeControl;
			ctl->m_pTree->m_pFont = font;
			{
				ctl->m_pTree->m_name = WSTR("Root");
				{
					TreeItem* pItem = new TreeItem;
					pItem->m_name = WSTR("Item 0");
					pItem->m_pFont = font;
					ctl->m_pTree->AppendItem(pItem);
				}

				{
					TreeItem* pItem = new TreeItem;
					pItem->m_name = WSTR("Item 1");
					pItem->m_pFont = font;
					ctl->m_pTree->AppendItem(pItem);
				}
			}

			ctl->m_pFont = font;
	*/

		if (true)
		{
			m_watchWnd = new WatchWnd;
		//	m_watchWnd->m_pFrame = this;
			{
				m_watchWnd->AddWatchExpression(new WatchExpression(ASTR("x")));
				/*
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("v1")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("x")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("x2")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("y")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("z")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("j")));
				m_watchWnd->m_watchList.Add(new WatchExpression(new StringA("x3")));
				*/
				/*
				m_watchWnd->m_watchList.push_back(new WatchExpression("myvar"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g1"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g2"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g3"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g4"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g5"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g6"));
				m_watchWnd->m_watchList.push_back(new WatchExpression("g7"));
				*/

				UI::ChildWindow* pWindow = new UI::ChildWindow;
				pWindow->set_Width(new UI::Length(240));
				pWindow->set_Height(new UI::Length(210));

				{
					UI::ScrollViewer* pScroller = new UI::ScrollViewer;
					{
						pScroller->set_Content(m_watchWnd);
					}
					pWindow->set_Content(pScroller);
				}

				pWindow->set_TitleText(WSTR("Watch"));

				pCanvas->AddChild(pWindow);
			}
		}

		p->SetDock(pCanvas, UI::DockPanel::Fill);
		p->AddRChild(pCanvas);
	}
	set_Content(p);
	set_TitleText(WSTR("LDebugger"));
	}
#endif

	UI::StackPanel* panel = new UI::StackPanel;

	if (true)
	{
		UI::MenuItem* pSubItem4 = new UI::MenuItem(WSTR("SubItem 4"));
		pSubItem4->get_Items()->Add(new UI::MenuItem(WSTR("Subyy 0")));
		pSubItem4->get_Items()->Add(new UI::MenuItem(WSTR("Subyy 1")));
		pSubItem4->get_Items()->Add(new UI::MenuItem(WSTR("Subyy 2")));
		pSubItem4->get_Items()->Add(new UI::MenuItem(WSTR("Subyy 3")));

		UI::MenuItem* pMenuItem = new UI::MenuItem(WSTR("MenuItem 0"));
		pMenuItem->get_Items()->Add(new UI::MenuItem(WSTR("SubItem 0")));
		pMenuItem->get_Items()->Add(new UI::MenuItem(WSTR("SubItem 1")));
		pMenuItem->get_Items()->Add(new UI::MenuItem(WSTR("SubItem 2")));
		pMenuItem->get_Items()->Add(new UI::MenuItem(WSTR("Close"), UI::ApplicationCommands::get_Close()));
		//pMenuItem->get_Items()->Add(pSubItem4);

		/*
		{
			pMenu->AddItem(new UI::TextString(WSTR("Open")), ID_FILE_OPEN);
			pMenu->AddItem(new UI::TextString(WSTR("Save")));
			pMenu->AddItem(new UI::TextString(WSTR("Open Program")), ID_FILE_OPENPROGRAM);
		}
		*/

		panel->AddChild(pMenuItem);

#if 0
		UI::Menu* pMenu = new UI::Menu(new UI::TextString(WSTR("File")));
		{
			pMenu->AddItem(new UI::TextString(WSTR("Open")), ID_FILE_OPEN);
			pMenu->AddItem(new UI::TextString(WSTR("Save")));
			pMenu->AddItem(new UI::TextString(WSTR("Open Program")), ID_FILE_OPENPROGRAM);
		}

		panel->AddChild(pMenu);
#endif
	}

	if (true)
	{
		UI::CUIDockBar* tray = new UI::CUIDockBar;

		UI::ToolBar* toolbar = new UI::ToolBar;
		toolbar->get_Items()->Add(new UI::Button(WSTR("Button0")));
		toolbar->get_Items()->Add(new UI::Button(WSTR("Button1")));

		tray->DockControlBar(toolbar);

		panel->AddChild(tray);
	}

	if (true)
	{
		UIElement* element = dynamic_cast<UIElement*>(UI::Application::LoadComponent(new Uri(WSTR("C:/mmstudio/test.xaml"))));
		if (element)
		{
			panel->AddChild(element);
		}
	}

	if (false)
	{
		UI::ListBox* listbox = new UI::ListBox;

		UI::ListBoxItem* item1 = new UI::ListBoxItem;
		item1->set_Content(WSTR("Item 1"));
		listbox->get_Items()->Add(item1);

		UI::ListBoxItem* item2 = new UI::ListBoxItem;
		item2->set_Content(WSTR("Item 2"));
		listbox->get_Items()->Add(item2);

		UI::ListBoxItem* item3 = new UI::ListBoxItem;
		item3->set_Content(WSTR("Item 3"));
		listbox->get_Items()->Add(item3);

		UI::ListBoxItem* item4 = new UI::ListBoxItem;
		item4->set_Content(WSTR("Item 4"));
		listbox->get_Items()->Add(item4);

		UI::ListBoxItem* item5 = new UI::ListBoxItem;
		item5->set_Content(WSTR("Item 5"));
		listbox->get_Items()->Add(item5);

		UI::ListBoxItem* item6 = new UI::ListBoxItem;
		item6->set_Content(WSTR("Item 6"));
		listbox->get_Items()->Add(item6);

		listbox->set_HorizontalAlignment(UI::HorizontalAlignment_Center);
		listbox->set_Height(80);

		panel->AddChild(listbox);
	}

	if (false)
	{
		UI::ChildWindowContainer* frame = new UI::ChildWindowContainer;

		UI::ChildWindow* child = new UI::ChildWindow;
		child->set_Title(WSTR("Hello"));
		child->set_Content(new UI::TextString(WSTR("Hello")));
//		container->AddChild(child);
		frame->get_Items()->Add(child);

		frame->set_Width(180);
		frame->set_Height(180);

		panel->AddChild(frame);
	}

	UI::CommandBinding* commandBinding = new UI::CommandBinding(
		UI::ApplicationCommands::get_Close(),
		&ExecutedHandler, &CanExecuteHandler);

	panel->get_CommandBindings()->Add(commandBinding);

	if (false)
	{
		//function2<Object*, UI::ExecutedRoutedEventArgs*> fun(ExecutedHandler);
		
	//	signal2<Object*, UI::ExecutedRoutedEventArgs*>::slot_function_type fun = ExecutedHandler;//UI::ExecutedRoutedEventArgs());

	//	test(signal2<Object*, UI::ExecutedRoutedEventArgs*>::slot_function_type(ExecutedHandler));
	//	test(ExecutedHandler);

		UI::Button* button1 = new UI::Button(WSTR("Button One"));
		button1->set_HorizontalAlignment(UI::HorizontalAlignment_Left);
		panel->AddChild(button1);

		button1->set_Command(UI::ApplicationCommands::get_Close());

	//	button1->get_MouseMove().connect(&MouseMoveHandler);
	}

	if (false)
	{
		UI::Button* button2 = new UI::Button(WSTR("Button Two"));
		button2->set_HorizontalAlignment(UI::HorizontalAlignment_Center);
		button2->set_Margin(new UI::Thickness(10));
		panel->AddChild(button2);
	}

	if (false)
	{
		UI::Button* button3 = new UI::Button(WSTR("Button Three"));
		button3->set_HorizontalAlignment(UI::HorizontalAlignment_Right);
		panel->AddChild(button3);

		UI::Button* button4 = new UI::Button(WSTR("Button Four"));
		button4->set_HorizontalAlignment(UI::HorizontalAlignment_Stretch);
		panel->AddChild(button4);
	}

	if (false)
	{
		UI::ScrollBar* scroll = new UI::ScrollBar(UI::Orientation_Horizontal);
		scroll->set_ViewportSize(0.5);
		panel->AddChild(scroll);
	}

	if (false)
	{
		UI::ScrollBar* scroll = new UI::ScrollBar(UI::Orientation_Vertical);
		scroll->set_ViewportSize(0.5);
		panel->AddChild(scroll);
	}

	if (true)
	{
		UI::ScrollBar* scroll = new UI::ScrollBar(/*UI::Orientation_Horizontal*/);
		scroll->set_Maximum(500);
		scroll->set_ViewportSize(30);
		scroll->set_Value(200);
		panel->AddChild(scroll);

#if 1

		UI::ScrollBar* scroll2 = new UI::ScrollBar(/*UI::Orientation_Horizontal*/);
		scroll2->set_ViewportSize(0.3);
		panel->AddChild(scroll2);
		if (true)
		{
			if (true)
			{
				UI::Button* button2 = new UI::Button(WSTR("Button Two"));
				button2->set_HorizontalAlignment(UI::HorizontalAlignment_Center);
				button2->set_Margin(new UI::Thickness(10));
				//button2->set_Width(300);
				panel->AddChild(button2);
			//	button2->AddHandler(UI::Button::get_ClickEvent(), OnClick);
				button2->get_Click().connect(OnClick);
				
				UI::Data::Binding* binding = new UI::Data::Binding;
				binding->set_Source(scroll);
				binding->set_Path(new UI::Data::PropertyPath(WSTR("Value")));
				button2->SetBinding(UI::FrameworkElement::get_WidthProperty(), binding);
				
			}
			else
			{
				UI::Data::Binding* binding = new UI::Data::Binding;
				binding->set_Source(scroll);
				binding->set_Path(new UI::Data::PropertyPath(WSTR("Value")));
				scroll2->SetBinding(UI::ScrollBar::get_ValueProperty(), binding);
			}
		}

		UI::ScrollBar* scroll3 = new UI::ScrollBar(UI::Orientation_Horizontal);
		scroll3->set_ViewportSize(0.1);
	//	scroll2->SetBinding(UI::ScrollBar::get_ValueProperty(), binding);
		panel->AddChild(scroll3);
#endif
	}

	if (false)
	{
		UI::Shapes::Ellipse* ellipse = new UI::Shapes::Ellipse;
		ellipse->set_Width(350);
		ellipse->set_Height(250);

		UI::Media::ColorAnimation* animation = new UI::Media::ColorAnimation;
		animation->set_Duration(1);
		animation->set_From(UI::Color::FromRgb(0, 0, 0));
		animation->set_To(UI::Color::FromRgb(255, 255, 255));

		UI::SolidColorBrush* brush = new UI::SolidColorBrush(UI::Color::FromRgb(0,0,0));
		ellipse->set_Fill(brush);

		brush->BeginAnimation(brush->get_ColorProperty(), animation);

		panel->AddChild(ellipse);

		/*
		UI::Storyboard* storyboard = new UI::Storyboard;
		storyboard->get_Children()->Add(animation);

		storyboard->Begin(ellipse);
		*/
	}

	if (true)
	{
		UI::ScrollViewer* viewer = new UI::ScrollViewer;

		/*
		UI::Shapes::Ellipse* ellipse = new UI::Shapes::Ellipse;
		ellipse->set_Fill(new UI::SolidColorBrush(new UI::Color(255, 0, 0, 128)));
		ellipse->set_Width(350);
		ellipse->set_Height(250);
		viewer->set_Content(ellipse);
		*/
		UI::Image* image = new UI::Image(new UI::FileImageSource(WSTR("C:/Documents and Settings/All Users/Documents/My Pictures/Sample Pictures/sunset.jpg")));
		viewer->set_Content(image);

		viewer->set_Width(300);
		viewer->set_Height(200);

		panel->get_Children()->Add(viewer);
	}

	if (true)
	{
		UI::TextEdit* edit = new UI::TextEdit();
		edit->set_Text(WSTR("This is a paragraph with some text, hello there,\nhow are you today my very good friend?"));
//		button2->set_HorizontalAlignment(UI::HorizontalAlignment_Center);
//		button2->set_Margin(new UI::Thickness(10));
		panel->get_Children()->Add(edit);
	}

	set_Content(panel);

//	set_Content(WSTR("Hello there, how are you?"));

	/*
#if _WINDOWS
	InitializeCriticalSection(&m_bufferCS);
#endif
	*/
	set_Title(WSTR("Debugger"));
}

DebuggerFrame::~DebuggerFrame()
{
}

#if 0//_WINDOWS


#if 0
LRESULT DebuggerFrame::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	gmMatrix3 transform = gmMatrix3::scale(30, 30);

	gmMatrix3 mat = transform;

	mat = gmMatrix3::translate(5, 14) * mat;
	mat = gmMatrix3::scale(1.0/64.0, 1.0/64.0) * mat;
	mat = gmMatrix3::scale(1, -1) * mat;

//	gmVector2 mousexpt = mat.inverse.transform(gmVector2(point.x, point.y));

	CClientDC dc(m_hWnd);

	dc.FillSolidRect(0, 0, 160, 60, RGB(255, 255, 255));

	int y = 0;

	int n = 0;
	for (int c = 0; c < pGlyph2->Desc.numberOfContours; c++)
	{
		for (; n <= pGlyph2->data.endPtsOfContours[c]; n++)
		{
			gmVector2 xpt = mat.transform(gmVector2(pGlyph2->data.points[n].X, pGlyph2->data.points[n].Y));

			if (abs(point.x - xpt[0]) < 2 && abs(point.y - xpt[1]) < 2)
			{
				char str[256];
				sprintf(str, "%d(%.2f,%.2f)", n, vm->newpoints[1][n].X / 64.0, vm->newpoints[1][n].Y / 64.0);
				dc.TextOut(16, 16+y, str, strlen(str));

				if (vm->orgpoints[1][n].X != vm->orgpoints[1][n].X ||
					vm->orgpoints[1][n].Y != vm->orgpoints[1][n].Y)
				{
					char str[256];
					sprintf(str, "%d(%.2f,%.2f)", n, vm->orgpoints[1][n].X / 64.0, vm->orgpoints[1][n].Y / 64.0);
					dc.TextOut(80, 16+y, str, strlen(str));
				}

				y += 14;
			}
			/*
			if (pGlyph2->data.flags[n] & 1)	// on-curve
			{
				dc.SelectPen(red);
				dc.Rectangle(xpt[0]-2, xpt[1]-2, xpt[0]+3, xpt[1]+3);
			}
			else
			{
				dc.SelectPen(gray);
				dc.Ellipse(xpt[0]-1, xpt[1]-1, xpt[0]+3, xpt[1]+3);
			}
			*/
		}
	}

	return 0;
}

LRESULT DebuggerFrame::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (vm->m_ctx)
	{
//		MessageBeep(-1);
		vm->next();

	//	Render();
		::InvalidateRect(GetHwnd(), NULL, TRUE);
	}

	return 0;
}
#endif
#endif

//#pragma comment(lib, "../LHTML/Debug/LHTML.lib")
//#pragma comment(lib, "../LSVG/Debug/LSVG.lib")


#if 0

LRESULT DebuggerFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);
	// if UI is the last thread, no need to wait
	if(_Module.GetLockCount() == 1)
	{
		_Module.m_dwTimeOut = 0L;
		_Module.m_dwPause = 0L;
	}
	_Module.Unlock();
	return 0;
}

#endif

//void FromStab(DebuggerCtx* ctx, uint32 offaddr, nlist* stab, int nstabs);

void DebuggerFrame::OnDebugGo()
{
	printf("OnDebugGo()\n");
	fflush(stdout);

	if (m_pathName == NULL || m_pathName->Length() == 0)
	{
		return;
	}

	if (m_disassemblyWnd == NULL)
	{
		m_ctx = new DebuggerCtx;
		m_ctx->m_frame = this;

		m_watchWnd->set_Context(m_ctx);
		m_callStackWnd->set_Context(m_ctx);

		UI::ScrollViewer* pScroller = new UI::ScrollViewer;

		m_disassemblyWnd = new DisassemblyWnd(m_ctx);

		pScroller->set_Content(m_disassemblyWnd);

		pGlobalScope = new Scope;	// TODO, not here
		pGlobalScope->m_startAddress = 0;
		pGlobalScope->m_endAddress = 0xFFFFFFFF;

		m_ctx->Start();

	//	m_disassemblyWnd->SetActive(GetEip());

		if (true)
		{
			UI::ChildWindow* pWindow = new UI::ChildWindow;
			pWindow->m_computedLeft = 40;//put_Left(pWindow, new Length(100, UnitAbsolute));
			pWindow->m_computedTop = 40;//put_Top(new Length(100, UnitAbsolute));
			pWindow->set_Width(200.0);
			pWindow->set_Height(200.0);

			pWindow->set_Content(pScroller/*m_disassemblyWnd*/);

			pWindow->set_Title(WSTR("Disassembly"));

		//	pWindow->SetOwnerWindow(pCanvas->get_OwnerWindow());	// TODO, not here
			pCanvas->AddChild(pWindow);

#if 0
			{	// TODO, not here
				UI::CUIFrameImpl* pFrame = dynamic_cast<UI::CUIFrameImpl*>(pCanvas->GetOwnerWindow()->m_pSite);
				pFrame->CreateRegions();
			}
#endif
		}
	}
	else
	{
		m_ctx->Continue();
	}

#if 0
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOWDEFAULT;

	PROCESS_INFORMATION pi;
	if (CreateProcess(
		//"c:\\mmstudio\\extras\\testapp\\debug\\testapp.exe",	// lpApplicationName
		ctx->m_pathName,
		NULL,	// lpCommandLine
		NULL,	// lpProcessAttributes
		NULL,	// lpThreadAttributes
		FALSE,	// bInheritHandles
		DEBUG_PROCESS | CREATE_NEW_CONSOLE,	// dwCreationFlags
		NULL,	// lpEnvironment
		NULL,	// lpCurrentDirectory	
		&si,	// lpStartupInfo
		&pi))	// lpProcessInformation
	{
	}
	else
	{
#if 0
		switch( GetLastError() )
		{
		case ERROR_FILE_NOT_FOUND:
         MessageBox("This file does not exist.",  "Open File Error", MB_OK | MB_APPLMODAL | MB_SETFOREGROUND );
			break;
		case ERROR_ACCESS_DENIED:
			MessageBox(TEXT( "Access denied." ),           TEXT( "Open File Error" ), MB_OK | MB_APPLMODAL | MB_SETFOREGROUND );
         break;
		case ERROR_FILE_INVALID:
         MessageBox(TEXT( "Invalid file." ), TEXT( "Open File Error" ), MB_OK | MB_APPLMODAL | MB_SETFOREGROUND );
         break;

		case ERROR_FILE_CORRUPT:
         MessageBox(TEXT( "The file is corrupt." ),           TEXT( "Open File Error" ), MB_OK | MB_APPLMODAL | MB_SETFOREGROUND );
         break;

		case ERROR_BAD_EXE_FORMAT:
         MessageBox(TEXT( "The file has a bad format." ),           TEXT( "Open File Error" ), MB_OK | MB_APPLMODAL | MB_SETFOREGROUND );

		default:
			MessageBox("Failed", "LDebugger", MB_OK);
		}
#endif
	}
#endif
}

#if 0
LRESULT DebuggerFrame::OnDebugAttachToProcess(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CAttachProcessDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		DebuggerCtx* ctx = new DebuggerCtx;

//		m_dwProcessId = dlg.m_dwProcessId;
		ctx->dwProcessId = dlg.m_dwProcessId;
		ctx->frame = this;

		m_ctx = ctx;
		m_hThread = CreateThread(NULL, 0, DebuggerStartProc, ctx, 0, &m_threadId);
	}
#endif

	return 0;
}

#endif 


void DebuggerFrame::OnDebugStepInto()
{
	if (m_ctx)
	{
		m_ctx->StepInto();
	}
}

#if 0

LRESULT DebuggerFrame::OnDebugBreak(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	if (m_ctx)
	{
		DebugProcess* pr = m_ctx->GetProcessById(m_ctx->m_dwProcessId);
		if (pr->m_bRunning)
		{
			tyhthreadmap::iterator ti = pr->m_threads.begin();
			while (ti != pr->m_threads.end())
			{
				(*ti).second->m_dwSuspendCount = SuspendThread((*ti).second->m_hThread);
				ti++;
			}
			pr->m_bRunning = false;
		}
	}

	return 0;
}

LRESULT DebuggerFrame::OnDebugThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	DebugProcess* pr = m_ctx->GetProcessById(m_ctx->dwProcessId);
	if (!pr->m_bRunning)	// Process must be suspended (meaning all threads in process)
	{
		CThreadsDlg dlg;
		dlg.m_pDebugProcess = pr;

		if (dlg.DoModal() == IDOK)
		{
		}
	}
#endif
	return 0;
}

LRESULT DebuggerFrame::OnDebugModules(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	if (m_ctx)
	{
		CModulesDlg dlg;
		dlg.m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_ctx->dwProcessId);//m_ctx->GetProcessById(m_dwProcessId);

		dlg.DoModal();

		CloseHandle(dlg.m_hProcess);
	}
#endif
	return 0;
}
#endif

//#include <locale>

#if _WINDOWS
#define t_isalpha	iswalpha
#else
#define t_isalpha	isalpha
#endif

static long COLOR_JSCRIPT_KEYWORD;
static long COLOR_JSCRIPT_STRING;
static long COLOR_JSCRIPT_COMMENT;

void FormatJScript(UI::TextEdit* m_edit, const OLECHAR* data, int& pos, unsigned long length, bool bCDATA)
{
	long styleIndex = 0;

	if (!bCDATA)
	{
// Check for comment <!--

		// Skip spaces
		while (pos < length && isspace(data[pos])) pos++;

		int start = pos;

		if (
			(						 data[pos] == L'<') &&
			(pos < length-1 && data[pos+1] == L'!') &&
			(pos < length-2 && data[pos+2] == L'-') &&
			(pos < length-2 && data[pos+3] == L'-'))
		{
			pos += 4;

		// Comment out to end of line
			while (pos < length)
			{
				WCHAR c = data[pos++];
				if (c == L'\n') break;
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT/*, &styleIndex*/);
		}
	}

	// JavaScript
	while (pos < length)
	{
		if (bCDATA)
		{
#if 0
			if (
				(						 data[pos+0] == L']') &&
				(pos < length-1 && data[pos+1] == L']') &&
				(pos < length-2 && data[pos+2] == L'>'))
			{
				pos += 3;
				break;
			}
#endif
		}
		else
		{
			if (data[pos] == L'<')	// Start of new element
			{
				break;
			}
		}

		if (t_isalpha(data[pos]) || data[pos] == L'_')	// Start of keyword/identifier
		{
			int start = pos;
			const WCHAR* idstr = &data[pos];

			pos++;

			while (pos < length &&
				(isalnum(data[pos]) || data[pos] == L'_'))
			{
				pos++;
			}

			int len = pos-start;

#if 0	// TODO
			if (
				(len == 4 && !wcsncmp(idstr, L"void", 4)) ||
				(len == 4 && !wcsncmp(idstr, L"char", 4)) ||
				(len == 3 && !wcsncmp(idstr, L"int", 3)) ||
				(len == 4 && !wcsncmp(idstr, L"long", 4)) ||
				(len == 5 && !wcsncmp(idstr, L"short", 5)) ||
				(len == 6 && !wcsncmp(idstr, L"struct", 6)) ||

				(len == 2 && !wcsncmp(idstr, L"if", 2)) ||
				(len == 4 && !wcsncmp(idstr, L"else", 4)) ||
				(len == 5 && !wcsncmp(idstr, L"while", 5)) ||
				(len == 3 && !wcsncmp(idstr, L"for", 3)) ||
				(len == 2 && !wcsncmp(idstr, L"do", 2)) ||
				(len == 4 && !wcsncmp(idstr, L"goto", 4)) ||
				(len == 6 && !wcsncmp(idstr, L"return", 6)) ||
				(len == 5 && !wcsncmp(idstr, L"break", 5)) ||
				(len == 8 && !wcsncmp(idstr, L"continue", 8)) ||

				(len == 6 && !wcsncmp(idstr, L"switch", 6)) ||
				(len == 4 && !wcsncmp(idstr, L"case", 4)) ||
				(len == 7 && !wcsncmp(idstr, L"default", 7)) ||

				(len == 3 && !wcsncmp(idstr, L"try", 3)) ||
				(len == 5 && !wcsncmp(idstr, L"catch", 5)) ||
				// ?? (len == 5 && !wcsncmp(idstr, L"throw", 5)) ||

				(len == 3 && !wcsncmp(idstr, L"new", 3)) ||
				(len == 6 && !wcsncmp(idstr, L"delete", 6)) ||

				(len == 4 && !wcsncmp(idstr, L"true", 4)) ||
				(len == 5 && !wcsncmp(idstr, L"false", 5)))
			{
				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_KEYWORD/*, &styleIndex*/);
			}
			else	// Identifier
			{
			}
#endif
		}
		else if (data[pos] == L'"' || data[pos] == L'\'')	// String
		{
			int start = pos;
			OLECHAR delimiter = data[pos++];

			while (pos < length)
			{
				OLECHAR c = data[pos++];
				if (c == L'\\')
				{
					pos++;
				}
				else
				{
					if (c == delimiter)
						break;
				}
			}

			m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_STRING/*, &styleIndex*/);
		}
		else if (data[pos] == L'/')
		{
			int start = pos++;

			if (pos < length && data[pos] == L'/')	// One-line comment
			{
				pos++;

			// Comment out to end of line
				while (pos < length)
				{
					if (data[pos++] == L'\n')
					{
						break;
					}
				}

				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT/*, &styleIndex*/);
			}
			else if (pos < length && data[pos] == L'*')	// Multi-line comment
			{
				pos++;

			// Comment out until we reach '*/'
				while (pos < length)
				{
					if (data[pos++] == L'*')
					{
						if (pos < length)
						{
							if (data[pos++] == L'/')
								break;
						}
					}
				}

				m_edit->FormatRange(start, pos-start, COLOR_JSCRIPT_COMMENT/*, &styleIndex*/);
			}
			/*
			else
			{
				pos++;
			}
			*/
		}
		else
		{
			pos++;
		}
	}
}

//#include < functional >

/*
void DebuggerFrame::GotoFilePos(SourceLocation* sourceLocation)
{
	
	GotoFilePos(sourceLocation->
}
*/

void DebuggerFrame::GotoFilePos(StringA* filename, int line)
{
	SourceEditFrame* p = OpenFile(filename);
	if (p)
	{
		p->m_edit->setCursorPos(line-1, 0);
#if 0
		MDIActivate(p->m_hWnd);
		p->pEdit->SetFocus();
#endif
	}
}

void DebuggerFrame::OnException()
{
	// Try to find source file
//	TODO
	m_pLocation = m_ctx->FindSourceLocation(m_ctx->GetEip());

	if (m_pLocation)
	{
	//	SourceEditFrame* pSourceFrame = ctx->frame->OpenFile(pLocation->file->sourceFileName);
	//	pSourceFrame->ShowWindow(SW_SHOW);
//#if _WINDOWS
//		frame->PostMessage(WM_USER+2, pLocation->line, (LPARAM)strdup(pLocation->file->sourceFileName.c_str()));
//#else
		if (m_pLocation->file->m_filename)
		{
	/*	SourceEditFrame* sourceEdit =*/ GotoFilePos(m_pLocation->file->m_filename, m_pLocation->line);
		/*
		if (sourceEdit)
		{
			sourceEdit->m_sourceFile = m_pLocation->file;
			m_pLocation->file->m_userdata = sourceEdit;
		}
		*/
//#endif

	//	GotoFilePos(m_pLocation);

			TRACE("source file: %s # %d\n", m_pLocation->file->m_filename->c_str(), m_pLocation->line);
			m_disassemblyWnd->set_LinesOffset(m_pLocation->line);
		}

		//pLocation
	//	delete pLocation;
	}

	if (m_disassemblyWnd)
		m_disassemblyWnd->SetActive(m_ctx->GetEip());

#if WIN32
	if (m_registersWnd)
		m_registersWnd->Invalidate();
#endif

	if (m_callStackWnd)
		m_callStackWnd->Update();

	if (m_watchWnd)
		m_watchWnd->Update();
}

#if WIN32

MSWindows::LRESULT DebuggerFrame::OnLoadFile(UINT uMsg, MSWindows::WPARAM wParam, MSWindows::LPARAM lParam)
{
	OnException();

	/*
	LPCTSTR filename = (LPCTSTR)lParam;

	GotoFilePos(filename, (int)wParam-1);

	free(filename);
*/

	return 0;
}
#endif

SourceEditFrame* DebuggerFrame::OpenFile(StringA* rawfilename)
{
	printf("OpenFile(%s)\n", rawfilename->c_str());
	fflush(stdout);

	return NULL;

#if 0

	SourceEditFrame* pSourceFrame = NULL;

	char filename[512];
	FixPathName(filename, rawfilename->c_str());

	SourceDocument sourcedocument;

	pair<filesmap::iterator, bool> fi = m_files.insert(new StringA(string_copy(filename)));
	if (!fi.second)	// Inserted
	{
		pSourceFrame = (*fi).second;
	}
	else
	{
		System::IO::FileByteStream stream(new StringA(string_copy(filename)));

		/*
		FILE* fp = fopen(filename, "r");
		if (fp == NULL)
		{
			printf("Failed to open file '%s'\n", filename);
		}
		else
		*/
		{
			TextDocument* str = new TextDocument;
			str->ReadFromStream(&stream);
#if 0
			while (1)//!feof(fp))
			{
				char c;
				if (stream.Read(&c, 1) != 1)
					break;

				WCHAR wc = c;

				if (c == '\r')
				{
					char c2 = 0;
					stream.Read(&c2, 1);
					if (c2 == '\n')
					{
						wc = c2;
						str->AppendText(&wc, 1);
					}
					else
					{
						str->AppendText(&wc, 1);
					//	str += c;
					}
				}
				else
				{
					str->AppendText(&wc, 1);
				//	str += c;
				}
			}
#endif
		//	fclose(fp);
			stream.Close();

		//	printf("file length: %d\n", str->Length());
		//	fflush(stdout);

			pSourceFrame = new SourceEditFrame;
			pSourceFrame->m_pFrame = this;

			pSourceFrame->m_filename = new StringA(string_copy(filename));
			m_files.insert(filesmap::value_type(pSourceFrame->m_filename, pSourceFrame));

		//	printf("1\n");
		//	fflush(stdout);

		//	pSourceFrame->pEdit->m_tdp = new TextDocument;
			pSourceFrame->pEdit->set_TextDocument(str);

		//	printf("2\n");
		//	fflush(stdout);

		//	pSourceFrame->pEdit->put_vertScroll(1);
		//	pSourceFrame->pEdit->put_horzScroll(1);
			pSourceFrame->pEdit->set_MultiLine(true);

		//	printf("3\n");
		//	fflush(stdout);

			if (true)
			{
			//	pSourceFrame->pEdit->BuildRLineOffsets();
			//	pSourceFrame->pEdit->BuildLineOffsets();
			}

			printf("6\n");
			fflush(stdout);

		//	long style = pEdit->NewStyle();
			COLOR_JSCRIPT_KEYWORD = pSourceFrame->pEdit->NewStyle();
			COLOR_JSCRIPT_STRING = pSourceFrame->pEdit->NewStyle();
			COLOR_JSCRIPT_COMMENT = pSourceFrame->pEdit->NewStyle();

			pSourceFrame->pEdit->SetStyle(COLOR_JSCRIPT_KEYWORD, LDraw::Color(0,0,190), LDraw::Color(255, 255, 255));
			pSourceFrame->pEdit->SetStyle(COLOR_JSCRIPT_STRING, LDraw::Color(190,0,0), LDraw::Color(255, 255, 255));
			pSourceFrame->pEdit->SetStyle(COLOR_JSCRIPT_COMMENT, LDraw::Color(0,140,0), LDraw::Color(255, 255, 255));

			printf("7\n");
			fflush(stdout);

		//		pEdit->FormatRange(0, pEdit->GetTextLen(), style);
			int pos = 0;
			pSourceFrame->pEdit->ClearFormatting();
	#if 0	// TODO
			FormatJScript(pSourceFrame->pEdit, pSourceFrame->pEdit->GetTextData(), pos, pSourceFrame->pEdit->GetTextLen(), true);
	#endif

			if (false)	// TODO, have this
			{
				UI::ChildWindow* pWindow = new UI::ChildWindow;
				pWindow->set_Width(new UI::Length(200));
				pWindow->set_Height(new UI::Length(200));

				pWindow->set_Content(pSourceFrame);
				pWindow->set_TitleText(pSourceFrame->m_filename->ToStringW());

				pCanvas->AddChild(pWindow);

				{	// TODO, not here
					UI::CUIFrameImpl* pFrame = dynamic_cast<UI::CUIFrameImpl*>(pCanvas->get_OwnerWindow()->m_pSite);
					pFrame->CreateRegions();
				}
			}
		}
	}

	return pSourceFrame;
#endif
}

void DebuggerFrame::OnFileOpen()
{
	printf("OnFileOpen()\n");
	fflush(stdout);

	FileDialog dlg(true/*bOpenFileDialog*/);
	if (dlg.DoModal(this) == IDOK)
	{
		printf("After doModal()\n");

		if (true)
		{
			SourceEditFrame* pSourceFrame = OpenFile(dlg.GetFileName());
		}

		printf("After OpenFile\n");

#if 0
		else
		{
			CLXUIVideo* ctl = new CLXUIVideo;
			ctl->put_Source(ConvertA2S(buffer));
			ChildWindow* pWindow = new ChildWindow;
			pWindow->put_Width(new Length(200, Length::UnitAbsolute));
			pWindow->put_Height(new Length(200, Length::UnitAbsolute));
			pWindow->put_Content(ctl);//pScroller);
				//	pWindow->put_Content(m_callStackWnd);

			pWindow->put_TitleText(ConvertA2S(buffer));

			pCanvas->AddChild(pWindow);
		}
#endif

#if 0
		pSourceFrame->ShowWindow(SW_SHOW);
		MDIActivate(pSourceFrame->m_hWnd);
#endif

#if 0
		std::wstring str;
		FILE* fp = fopen(dlg.m_szFileName, "r");
		if (fp)
		{
			while (!feof(fp))
			{
				int c = fgetc(fp);
			
				str += c;
			}
			fclose(fp);
		}

		pEdit->m_tdp = new TextDocument;
		pEdit->m_tdp->put_data(str.c_str(), str.length());
		pEdit->set_multiLine(true);
		pEdit->set_vertScroll(1);
		pEdit->set_horzScroll(1);

	//	long style = pEdit->NewStyle();
		COLOR_JSCRIPT_KEYWORD = pEdit->NewStyle();
		COLOR_JSCRIPT_STRING = pEdit->NewStyle();
		COLOR_JSCRIPT_COMMENT = pEdit->NewStyle();

		pEdit->SetStyle(COLOR_JSCRIPT_KEYWORD, RGB(0,0,200), RGB(255, 255, 255));
		pEdit->SetStyle(COLOR_JSCRIPT_STRING, RGB(200,0,0), RGB(255, 255, 255));
		pEdit->SetStyle(COLOR_JSCRIPT_COMMENT, RGB(0,190,0), RGB(255, 255, 255));

//		pEdit->FormatRange(0, pEdit->GetTextLen(), style);
		int pos = 0;
		pEdit->ClearFormatting();
		FormatJScript(pEdit, pEdit->GetTextData(), pos, pEdit->GetTextLen(), true);

		pSourceFrame->Create(m_hWndMDIClient, CRect(0, 0, 160, 160), dlg.m_szFileName, WS_SYSMENU | WS_CAPTION | WS_THICKFRAME | WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE | WS_EX_MDICHILD);
#endif
	}

	printf("leaving OnFileOpen\n");
}

#if 0

LRESULT DebuggerFrame::OnEditBreakpoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CBreakpointsDlg dlg;
	dlg.m_pFrame = this;
	dlg.DoModal();
#endif

	return 0;
}

#endif

void DebuggerFrame::OnFileOpenProgram()
{
	printf("OnFileOpenProgram\n");
	fflush(stdout);

	FileDialog dlg(true/*bOpenFileDialog*/);
	if (dlg.DoModal(this) == IDOK)
	{
		m_pathName = dlg.GetFileName();

		printf("%s\n", m_pathName->c_str());

#if 0
		UIEnable(ID_DEBUG_GO, TRUE);
#endif
	}
}

#if 0
void DebuggerFrame::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*type == L"command")
		{
			UI::CommandInvokeEvent* cmdEvt = dynamic_cast<UI::CommandInvokeEvent*>(evt);

			if (cmdEvt->get_Command() == ID_FILE_OPEN)
			{
				OnFileOpen();
				return;
			}
			else if (cmdEvt->get_Command() == ID_FILE_OPENPROGRAM)
			{
				OnFileOpenProgram();
				return;
			}
			else if (cmdEvt->get_Command() == ID_DEBUG_STEPINTO)
			{
				OnDebugStepInto();
				return;
			}
			else if (cmdEvt->get_Command() == ID_DEBUG_GO)
			{
				OnDebugGo();
				return;
			}
		}
		else if (*type == L"keydown")
		{

#if 0
			printf("Step Into\n");
			OnDebugStepInto();
			return;
#endif
		}
		else if (*type == L"mousedown")
		{
		//	OnDebugStepInto();
		}
	}

	CLXUIWindow::handleEvent(evt);
}
#endif

#if 0
LRESULT DebuggerFrame::OnAppAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ASSERT(0);
#if 0
	CAboutDlg dlg;
	dlg.DoModal();
#endif
	return 0;
}
#endif

}	// System
}

#if AMIGA

extern ULONG ret_pc;
extern uint16 sr;
extern ULONG nSig;

namespace System
{

void DebuggerFrame::handleSignal(uint32 sigmask)
{
	if (sr & (1<<15))	// trace exception
	{
		printf("Trace %x\n", ret_pc);
	}
	else	// trap0 breakpoint
	{
		printf("Breakpoint %x\n", ret_pc);

		uint32 ExceptionAddress = ret_pc-2;

		tybreakpointmap::iterator bi = m_ctx->m_breakpoints.find(ExceptionAddress);
		if (bi != m_ctx->m_breakpoints.end())
		{
			// Write back the old word so the real instruction can be executed
			uint32 nWritten;
			InstrPlaceholder old_instruction = (*bi).second.m_oldbyte;
			WriteProcessMemory(NULL/*(*pri).second->m_hProcess*/, (LPVOID)ExceptionAddress, &old_instruction, 2, &nWritten);

		// Reset this so the old instruction will be executed
			ret_pc = ExceptionAddress;

			//(*thi).second->m_context.Eip = (DWORD)DebugEv.u.Exception.ExceptionRecord.ExceptionAddress;
		}
		else
			ASSERT(0);
	}

	m_Eip = ret_pc;

	OnException();
}

}	// System

#endif
