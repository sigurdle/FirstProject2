#include "Stdafx.h"
#include "Browser.h"
#include "BrowserFrame.h"

//#include "../LXUI/UIFrameImpl.h"	// TODO remove

//#include "../LFC/XmlData.h"

#include "PropertiesWindow.h"
#include "Properties.h"
//#include "PropertiesTable.h"

//#include "ViewOfCollection.h"

#include "ListView.h"
#include "ViewOfCollection2.h"

#include "EMFWriter.h"

#include "SWFWriter.h"

//#include "Histogram.h"
#include "HueSaturate.h"

/*
#include <iostream>
#include <algorithm>
*/

#include "HttpServer.h"

//using namespace System;
//using namespace IO;
//using namespace UI;

#if 0//WIN32
// Just for test purposes
#include <gl/gl.h>
#include <gl/glu.h>

#endif

namespace System
{

void GetDerived(ClassType* pType, vector<ClassType*> & arr)
{
	for (int i = 0; i < pType->m_derived.GetSize(); i++)
	{
		ClassType* pDerived = pType->m_derived[i];
		
		if (pDerived->m_derived.GetSize() > 0)
		{
			GetDerived(pDerived, arr);
		}
		
		arr.Add(pDerived);
	}
}
}

extern "C"
{

_CRTIMP void   __cdecl _makepath(char *, const char *, const char *, const char *,
        const char *);

}	// extern "C"

#if WIN32
#include "HGlobalStream.h"
#endif	// WIN32

#include "../LXUI/UndoManager.h"

#include "../LFC/zip.h"

#if 0//WIN32
#include "../LXMLEditor/Transition.h"
#include "../LXMLEditor/TransitionSettingsDlg.h"
#pragma comment(lib, "../LXMLEditor/Debug/LXMLEditor.lib")

//LXmlEdit::CTransitions g_transitions;
#endif

#if 0//WIN32
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")
#endif

#include "../LFC/RIFF.h"
//#pragma comment(lib, "../LAVI/Debug/LAVI.lib")

#include "wmf.h"
#include "../Draw/BasicCommands.h"

#if WIN32
#include "../SWF/swf.h"
#endif

#include "../LJPEG/JFIF.h"

#if WIN32
#include "../LPDF/LPDF.h"
//#include "../LPDF/PDFCosDoc.h"
//#include "../LPDF/PDFPDDoc.h"
#endif

#if 0
extern Workbook* m_pWorkbook;
#endif

#if 0//WIN32
#include "../LXML/LXML.h"
#endif

//#include "../LXML/parsecolor.h"

#include "../LXUI/Binder.h"

#include "Item.h"

#if 0//WIN32
#include "../LHTML/LHTML.h"
#include "../LXML/LDOMElement.h"
#include "../LHTML/LHTMLDocument.h"
#include "../LSVG/LSVG.h"
#include "../LSVG/LSVGDocument.h"
#include "../LSVG/LSVGSVGElement.h"
#include "../LSVG/LSVGEllipseElement.h"

#endif

#if WIN32
#include "../LMPEGVideo/LMPEGVideo.h"
//#include "../LMPEGVideo/VideoSequence.h"
//#include "../LMPEGVideo/Picture.h"

#include "../LMPEG4/LMPEG4.h"

#endif

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LMPEGVideo.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LMPEGVideo.lib")
#endif

#if _DEBUG
//#pragma comment(lib, "../../lib/Win32/Debug/LMPEG4.lib")
#else
//#pragma comment(lib, "../../lib/Win32/ReleaseMinSize/LMPEG4.lib")
#endif

/*
#if WIN32
#include "../LX3D/LX3DScene.h"
#include "../LX3D/LVRMLLoader.h"
#include "../LX3D/OGLSceneRenderer.h"
#include "../LX3D/SceneRenderFilter.h"
#endif
*/

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LX3D.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LX3D.lib")
#endif

#if WIN32
#include "../LVOC/VOCLoader.h"
#pragma comment(lib, "../../lib/Win32/Debug/LVOC.lib")

#include "dxfile.h"

#endif

#include "ColorPickerRGB.h"

/*
#include "../LMPEGAudio/AudioSequence.h"
#pragma comment(lib, "../LMPEGAudio/Debug/LMPEGAudio.lib");
*/

//#include "swfplayer.h"

#if 0
#if WIN32
#include "../LXImageEditor/LXImageEditor.h"

#ifdef _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXImageEditor.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXImageEditor.lib")
#endif

#endif
#endif

/*
namespace System
{
namespace UI
{
	class ColorAnimation
	{
	public:
		ColorAnimation()
		{
		}

		Color m_From;
		Color m_To;

		double m_Duration;

		DependencyObject* m_target;
		DependencyProperty* m_property;

		void put_From(Color from)
		{
			m_From = from;
		}

		void put_To(Color to)
		{
			m_To = to;
		}

		void put_Duration(double duration)
		{
			m_Duration = duration;
		}

		void On()
		{
		}
	};

vector<ColorAnimation*> m_animations;
}
}
*/

#include "View.h"

#include "../include/windows_header.h"

namespace System
{
namespace MSWindows
{
extern "C"
{

WINBASEAPI
DWORD
WINAPI
GetLogicalDriveStringsA(
    IN DWORD nBufferLength,
    OUT LPSTR lpBuffer
    );
WINBASEAPI
DWORD
WINAPI
GetLogicalDriveStringsW(
    IN DWORD nBufferLength,
    OUT LPWSTR lpBuffer
    );

WINBASEAPI
UINT
WINAPI
GetDriveTypeA(
    IN LPCSTR lpRootPathName
    );
WINBASEAPI
UINT
WINAPI
GetDriveTypeW(
    IN LPCWSTR lpRootPathName
    );

WINBASEAPI
BOOL
WINAPI
GetVolumeInformationA(
    IN LPCSTR lpRootPathName,
    OUT LPSTR lpVolumeNameBuffer,
    IN DWORD nVolumeNameSize,
    OUT LPDWORD lpVolumeSerialNumber,
    OUT LPDWORD lpMaximumComponentLength,
    OUT LPDWORD lpFileSystemFlags,
    OUT LPSTR lpFileSystemNameBuffer,
    IN DWORD nFileSystemNameSize
    );
WINBASEAPI
BOOL
WINAPI
GetVolumeInformationW(
    IN LPCWSTR lpRootPathName,
    OUT LPWSTR lpVolumeNameBuffer,
    IN DWORD nVolumeNameSize,
    OUT LPDWORD lpVolumeSerialNumber,
    OUT LPDWORD lpMaximumComponentLength,
    OUT LPDWORD lpFileSystemFlags,
    OUT LPWSTR lpFileSystemNameBuffer,
    IN DWORD nFileSystemNameSize
    );

#define DRIVE_UNKNOWN     0
#define DRIVE_NO_ROOT_DIR 1
#define DRIVE_REMOVABLE   2
#define DRIVE_FIXED       3
#define DRIVE_REMOTE      4
#define DRIVE_CDROM       5
#define DRIVE_RAMDISK     6

}	// extern "C"
}
}
namespace System
{

using namespace UI;

LONGLONG StreamCopy(IO::ISequentialByteStream* dest, IO::ISequentialByteStream* src)
{
	LONGLONG total = 0;
	uint8 buf[256];
	while (1)
	{
		long nRead = src->Read(buf, 256);
		if (nRead < 0) break;

		total += nRead;

		dest->Write(buf, nRead);
		if (nRead < 256)
			break;
	}

	return total;
}

class SelectTool : public UI::Control
{
public:

	UI::UIElement* m_Content;

	/*
	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize)
	{
		m_Content->Measure(availSize);
		return m_Content->get_DesiredSize();
	}

	virtual void OnArrange(LDraw::SizeD finalSize)
	{
		m_Content->Arrange(finalSize);
	}
	*/

	virtual void OnRender(UI::Graphics* pGraphics)
	{
		m_Content->Render(pGraphics);

		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		LDraw::Pen* pen = new LDraw::Pen(LDraw::Color(60, 60, 200), 1);

		pGraphics->MultiplyTransform(m_transform);

		pGraphics->DrawRectangle(pen, m_rect);

		pGraphics->SetSmoothingMode(oldSmoothingMode);
	}

	LDraw::RectD m_rect;
	LDraw::Matrix3f* m_transform;

#if 0
	virtual void handleEvent(System::Event* evt)
	{
		if (evt->get_eventPhase() == System::CAPTURING_PHASE)
		{
			/*
			if (evt->get_type() == WSTR("mousedown"))
			{
				evt->stopPropagation();
				MessageBeep(-1);
			}
			else if (evt->get_type() == WSTR("mouseup"))
			{
				evt->stopPropagation();
				MessageBeep(-1);
			}
			else
			*/
			if (*evt->get_type() == L"mousemove")
			{
				if (GetOwnerWindow()->GetCapture())
					return;

			//	evt->stopPropagation();

				UI::MouseEvent* mouseEvt = dynamic_cast<UI::MouseEvent*>(evt);

				EventTargetImpl* target = mouseEvt->get_target();
				UI::UIElement* pVisual = dynamic_cast<UI::UIElement*>(target);

				m_rect = pVisual->m_expandedBBox;
				m_rect.Translate(0.5, 0.5);

				LDraw::Matrix3f* transform = pVisual->GetParentToElementTransformMatrix();
				UI::UIElement* pParent = dynamic_cast<UIElement*>(pVisual->GetRParent());
				while (pParent)
				{
					UI::UIElement* pChild = pParent;
					if (pChild == this)
						break;
					transform = *pChild->GetParentToElementTransformMatrix() * *transform;

					pParent = dynamic_cast<UIElement*>(pChild->GetRParent());
				}

				m_transform = transform;

				Invalidate();
			}
		}
	}
#endif
};

#if 1
#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LXML.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LXML.lib")
#endif

#endif

int g_r = 200;
int g_g = 200;
int g_b = 200;
int g_a = 255;

#if AMIGA

void SetCursorPos(int X, int Y);

#endif

void DrawPathText(UI::Graphics* pGraphics, uint8* grid, int ncols, int nrows, LDraw::Brush* pBrush, LDraw::GraphicsPathF* pPath)
{
	if (pPath->m_types.GetSize() == 0)
		return;

	const LDraw::PointF* points = pPath->m_points.GetData();

	LDraw::PointF startpt;// = points[0];
	LDraw::PointF curpt(0,0);

//	LDraw::Font font(WSTR("Arial"), 14);
//	LDraw::Font smallfont(WSTR("Arial"), 12);

	int n = 0;

	for (int i = 0; i < pPath->m_types.GetSize(); i++)
	{
		uint8 type = pPath->m_types[i] & LDraw::PathPointTypePathTypeMask;

		if (type == LDraw::PathPointTypeStart)
		{
			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(100, 200, 60)), points[0].X-2, points[0].Y-2, 5, 5);

			/*
			int x = points[0].X / 14;
			int y = points[0].Y / 14;

			while (grid[y*ncols + x])
			{
				x++;
			}
			grid[y*ncols + x] = 1;

			char buf[16];
			sprintf(buf, "%d", n);

			pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			*/

			curpt = *points++;
			startpt = curpt;
		//	n++;
		}
		else if (type == LDraw::PathPointTypeLine)
		{
		//	pGraphics->DrawLine(pPen, curpt, points[0]);

			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(200, 0, 0)), points[0].X-1, points[0].Y-1, 2, 2);

			/*
			int x = points[0].X / 14;
			int y = points[0].Y / 14;

			while (grid[y*ncols + x])
			{
				x++;
			}
			grid[y*ncols + x] = 1;

			char buf[16];
			sprintf(buf, "%d", n);

			pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			*/

			curpt = *points++;
			n++;
		}
		else if (type == LDraw::PathPointTypeBezier3)
		{
			LDraw::CubicBezierF bezier(curpt, points[0], points[1], points[2]);

			LDraw::PointF pt0 = bezier.evaluate(0.5);
			/*

			for (double t = 0.05; t <= 1; t += 0.05)
			{
				LDraw::PointF pt = bezier.evaluate(t);

				pGraphics->DrawLine(pPen, pt0, pt);

				pt0 = pt;
			}

			if (pt0 != points[2])
			{
				pGraphics->DrawLine(pPen, pt0, points[2]);
			}
			*/

			double angle = bezier.GetAngleAt(0.5);

			/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();

		//	pGraphics->TranslateTransform(-pt0.X, -pt0.Y);
			pGraphics->TranslateTransform(pt0.X, pt0.Y);
			pGraphics->RotateTransform(angle);

			LDraw::PointF pts[4] =
			{
				LDraw::PointF(-6, -6),
				LDraw::PointF(6, 0),
				LDraw::PointF(-6, 6),
				LDraw::PointF(-2, 0),
			};

			pGraphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(200, 0, 0)), pts, 4);
			//pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 0)), pt0.X, pt0.Y, pt0.X);

			pGraphics->PopTransform();//oldTransform);

		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(200, 0, 0)), points[2].X-1, points[2].Y-1, 3, 3);

			/*
			{
				int x = points[0].X / 14;
				int y = points[0].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &smallfont, LDraw::PointF(x*14, y*14), &LDraw::SolidBrush(LDraw::Color(160, 60, 60)));
			
			}
			n++;

			{
				int x = points[1].X / 14;
				int y = points[1].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &smallfont, LDraw::PointF(x*14, y*14), &LDraw::SolidBrush(LDraw::Color(160, 60, 60)));
			}
			n++;

			{
				int x = points[2].X / 14;
				int y = points[2].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			}
			n++;
			*/

		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), curpt, points[0]);
		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), points[0], points[1]);
		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), points[1], points[2]);

			curpt = points[2];
			points += 3;
		}
		else
			ASSERT(0);
	}
	//pGraphics->DrawLine(pPen, curpt, startpt);
}

void DrawPathText(UI::Graphics* pGraphics, uint8* grid, int ncols, int nrows, LDraw::Brush* pBrush, LDraw::GraphicsPathD* pPath)
{
	if (pPath->m_types.GetSize() == 0)
		return;

	const LDraw::PointD* points = pPath->m_points.GetData();

	LDraw::PointD startpt;// = points[0];
	LDraw::PointD curpt(0,0);

//	LDraw::Font font(L"Arial", 14);
//	LDraw::Font smallfont(L"Arial", 12);

	int n = 0;

	for (int i = 0; i < pPath->m_types.GetSize(); i++)
	{
		uint8 type = pPath->m_types[i] & LDraw::PathPointTypePathTypeMask;

		if (type == LDraw::PathPointTypeStart)
		{
			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(100, 200, 60)), points[0].X-2, points[0].Y-2, 5, 5);

			/*
			int x = points[0].X / 14;
			int y = points[0].Y / 14;

			while (grid[y*ncols + x])
			{
				x++;
			}
			grid[y*ncols + x] = 1;

			char buf[16];
			sprintf(buf, "%d", n);

			pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			*/

			curpt = *points++;
			startpt = curpt;
		//	n++;
		}
		else if (type == LDraw::PathPointTypeLine)
		{
		//	pGraphics->DrawLine(pPen, curpt, points[0]);

			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(200, 0, 0)), points[0].X-1, points[0].Y-1, 2, 2);

			/*
			int x = points[0].X / 14;
			int y = points[0].Y / 14;

			while (grid[y*ncols + x])
			{
				x++;
			}
			grid[y*ncols + x] = 1;

			char buf[16];
			sprintf(buf, "%d", n);

			pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			*/

			curpt = *points++;
			n++;
		}
		else if (type == LDraw::PathPointTypeBezier3)
		{
			LDraw::CubicBezierD bezier(curpt, points[0], points[1], points[2]);

			LDraw::PointD pt0 = bezier.evaluate(0.5);
			/*

			for (double t = 0.05; t <= 1; t += 0.05)
			{
				LDraw::PointF pt = bezier.evaluate(t);

				pGraphics->DrawLine(pPen, pt0, pt);

				pt0 = pt;
			}

			if (pt0 != points[2])
			{
				pGraphics->DrawLine(pPen, pt0, points[2]);
			}
			*/

			double angle = bezier.GetAngleAt(0.5);

			/*LDraw::Matrix3f oldTransform =*/ pGraphics->PushTransform();

		//	pGraphics->TranslateTransform(-pt0.X, -pt0.Y);
			pGraphics->TranslateTransform(pt0.X, pt0.Y);
			pGraphics->RotateTransform(angle);

			LDraw::PointF pts[4] =
			{
				LDraw::PointF(-6, -6),
				LDraw::PointF(6, 0),
				LDraw::PointF(-6, 6),
				LDraw::PointF(-2, 0),
			};

			pGraphics->FillPolygon(new LDraw::SolidBrush(LDraw::Color(200, 0, 0)), pts, 4);
			//pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 0)), pt0.X, pt0.Y, pt0.X);

			pGraphics->PopTransform();//(oldTransform);

		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(200, 0, 0)), points[2].X-1, points[2].Y-1, 3, 3);

			/*
			{
				int x = points[0].X / 14;
				int y = points[0].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &smallfont, LDraw::PointF(x*14, y*14), &LDraw::SolidBrush(LDraw::Color(160, 60, 60)));
			
			}
			n++;

			{
				int x = points[1].X / 14;
				int y = points[1].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &smallfont, LDraw::PointF(x*14, y*14), &LDraw::SolidBrush(LDraw::Color(160, 60, 60)));
			}
			n++;

			{
				int x = points[2].X / 14;
				int y = points[2].Y / 14;

				while (grid[y*ncols + x])
				{
					x++;
				}
				grid[y*ncols + x] = 1;

				char buf[16];
				sprintf(buf, "%d", n);

				pGraphics->DrawString(buf, strlen(buf), &font, LDraw::PointF(x*14, y*14), pBrush);
			}
			n++;
			*/

		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), curpt, points[0]);
		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), points[0], points[1]);
		//	pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(200, 0, 200), 0.6), points[1], points[2]);

			curpt = points[2];
			points += 3;
		}
		else
			ASSERT(0);
	}
	//pGraphics->DrawLine(pPen, curpt, startpt);
}



class Brightness : public UI::UIElement
{
public:
	Brightness()
	{
		SetClipMode(false);

		m_brightness = 0;
	}

	void OnRender(UI::Graphics* pGraphics);

	double get_Brightness();
	void put_Brightness(double value);

	double m_brightness;
};

double Brightness::get_Brightness()
{
	return m_brightness;
}

void Brightness::put_Brightness(double value)
{
	m_brightness = value;
	GetRParent()->InvalidateRender();
}

void Brightness::OnRender(UI::Graphics* pGraphics)
{
	LDraw::ColorMatrixF colorTransform(
		1, 0, 0, 0, m_brightness,
		0, 1, 0, 0, m_brightness,
		0, 0, 1, 0, m_brightness,
		0, 0, 0, 1, 0);

	pGraphics->MultiplyColorTransform(colorTransform);

	GetRParent()->_OnRender(pGraphics);
}

class DisplacementMap : public UI::UIElement
{
public:
	DisplacementMap()
	{
		SetClipMode(false);

		m_scalex = 10;
		m_in1 = NULL;
		m_in2 = NULL;
	}

	void OnRender(UI::Graphics* pGraphics);

	double get_ScaleX();
	void put_ScaleX(double value);

	double m_scalex;

	UI::UIElement* m_in1;
	UI::UIElement* m_in2;
};

double DisplacementMap::get_ScaleX()
{
	return m_scalex;
}

void DisplacementMap::put_ScaleX(double value)
{
	m_scalex = value;
	/*dynamic_cast<UIElement*>(GetRParent())->*/InvalidateRender();
}

void DisplacementMap::OnRender(UI::Graphics* pGraphics)
{
	LDraw::RectD RenderBounds = /*static_cast<UIElement*>(GetRParent())->*/m_expandedBBox;

	int width = ceil(RenderBounds.Width);
	int height = ceil(RenderBounds.Height);

	LDraw::Bitmap* bitmap = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGBAP_32);

	LDraw::Bitmap* bitmap1 = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGBAP_32);
	LDraw::Bitmap* bitmap2 = new LDraw::Bitmap(width, height, LDraw::PixelFormat_t::RGBAP_32);

	ASSERT(0);
#if 0
	{
		UI::Graphics* graphics = new UI::Graphics(new LDraw::GraphicsO(bitmap1));
		m_in1->_OnRender(graphics);
	}

	{
		UI::Graphics* graphics = new UI::Graphics(new LDraw::GraphicsO(bitmap2));
		m_in2->_OnRender(graphics);
	}
#endif

	LDraw::BitmapData dstdata;
	bitmap->LockBits(NULL, LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite, &dstdata);

	LDraw::BitmapData indata1;
	bitmap1->LockBits(NULL, LDraw::ImageLockModeRead, &indata1);

	LDraw::BitmapData indata2;
	bitmap2->LockBits(NULL, LDraw::ImageLockModeRead, &indata2);

	double scalex = m_scalex;
	double scaley = scalex;

	int xch = 1;
	int ych = 1;

	for (int y = 0; y < height; y++)
	{
		uint8* in2 = (uint8*)((uint8*)indata2.Scan0 + indata2.Stride*y);
		uint8* out = (uint8*)((uint8*)dstdata.Scan0 + dstdata.Stride*y);

		for (int x = 0; x < width; x++)
		{
		//	int x0 = x + (scalex * (((double)in2[xch])/255 - 0.5));
		//	int y0 = y + (scaley * (((double)in2[ych])/255 - 0.5));
			int x0 = x + (scalex * (((double)(in2[1] + in2[2] + in2[3])/3)/255 - 0.5));
			int y0 = y + (scaley * (((double)(in2[1] + in2[2] + in2[3])/3)/255 - 0.5));

			if (x0 >= 0 && y0 >= 0 && x0 < width && y0 < height)
			{
				uint8* in1 = (uint8*)((uint8*)indata1.Scan0 + indata1.Stride*y0 + x0*sizeof(uint32));

				*(uint32*)out = *(uint32*)in1;
			}
			else
			{
				*(uint32*)out = 0;
			}

			in2 += 4;
			out += 4;
		}
	}

	bitmap->UnlockBits(&dstdata);
	bitmap1->UnlockBits(&indata1);
	bitmap2->UnlockBits(&indata2);

	pGraphics->DrawImage(bitmap, 0, 0);
}

EditLines::EditLines()
{
	m_dragging = 0;
	m_pCurStroke = NULL;

#if 0
	if (false)
	{
		m_points.push_back(LDraw::PointF(240, 300));
		m_points.push_back(LDraw::PointF(100, 250));
		m_points.push_back(LDraw::PointF(100, 200));
		m_points.push_back(LDraw::PointF(250, 150));

		m_points.push_back(LDraw::PointF(50, 300));
		m_points.push_back(LDraw::PointF(200, 250));
		m_points.push_back(LDraw::PointF(200, 200));
		m_points.push_back(LDraw::PointF(60, 150));
	}
	else
	{
		m_points.push_back(LDraw::PointF(80, 200));
		m_points.push_back(LDraw::PointF(110, 100));
		m_points.push_back(LDraw::PointF(210, 300));
		m_points.push_back(LDraw::PointF(310, 100));

		m_points.push_back(LDraw::PointF(60, 100));
		m_points.push_back(LDraw::PointF(210, 100));
		m_points.push_back(LDraw::PointF(310, 300));
		m_points.push_back(LDraw::PointF(410, 100));
	}
#endif

	m_pCanvas = new Canvas;
	m_pCanvas->set_Width(600);
	m_pCanvas->set_Height(500);

	set_VisualTree(m_pCanvas);
}

#if 0
void EditLines::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

			UI::MouseEvent* mouseevt = dynamic_cast<UI::MouseEvent*>(evt);

			LDraw::PointD point = ScreenToClient(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

			m_startpoint = point;
			m_oldpoint = point;

			if (true)
			{
				UI::DropShadow* p = NULL;//new DropShadow;
				if (false)
				{
					UI::Shapes::Rectangle* pRect = new UI::Shapes::Rectangle();
					pRect->set_Fill(new SolidColorBrush(new Color(g_r, g_g, g_b, g_a)));
				//	pRect->m_computedLeft = m_startpoint.X;
				//	pRect->m_computedTop = m_startpoint.Y;

					UI::Canvas::SetLeft(pRect, m_startpoint.X);
					UI::Canvas::SetTop(pRect, m_startpoint.Y);
					pRect->set_Width(0.0);
					pRect->set_Height(0.0);

					m_pCurStroke = pRect;
				}
				else if (true)
				{
					UI::Shapes::Ellipse* pRect = new UI::Shapes::Ellipse();
					pRect->set_Fill(new SolidColorBrush(new Color(g_r, g_g, g_b, g_a)));
				//	pRect->m_computedLeft = m_startpoint.X;
				//	pRect->m_computedTop = m_startpoint.Y;
					UI::Canvas::SetLeft(pRect, m_startpoint.X);
					UI::Canvas::SetTop(pRect, m_startpoint.Y);
					pRect->set_Width(0.0);
					pRect->set_Height(0.0);

					m_pCurStroke = pRect;
				}
#if 0
				else if (false)
				{
					Line* pLine = new Line(new UI::Length(point.X), new UI::Length(point.Y), new Length(point.X), new Length(point.Y));
				//	p->put_Content(pLine);
					pLine->set_StrokeThickness(new Length(20.0));
					pLine->set_Stroke(new SolidColorBrush(new Color(g_r, g_g, g_b, g_a)));

					ColorAnimation* animation = new ColorAnimation;
					animation->m_target = pLine;
					animation->m_property = Shape::m_StrokeProperty;
					animation->put_Duration(10);
					animation->put_From(Color(0, 0, 0));
					animation->put_To(Color(255, 0, 0));

					m_animations.Add(animation);

					m_pCurStroke = pLine;
				}
#endif
				else
				{
					UI::TextString* pRect = new UI::TextString(WSTR("Hello there"));
					pRect->set_TextFill(new UI::SolidColorBrush(new UI::Color(g_r, g_g, g_b, g_a)));
					pRect->set_Width(0.0);
					pRect->set_Height(0.0);

					m_pCurStroke = pRect;
				}
				/*
				pStroke->m_points.push_back(point);
				pStroke->m_points.push_back(point);

				m_strokes.push_back(pStroke);
				*/
				if (p)
				{
					p->set_Content(m_pCurStroke);

					m_pCanvas->AddRChild(p);
					p->Measure(LDraw::SizeD(0,0));
				}
				else
				{
					m_pCanvas->AddRChild(m_pCurStroke);

					if (true)
					{
						MutationEvent* evt = new MutationEvent;
						evt->m_element = m_pCurStroke;
						evt->InitEvent(WSTR("InsertChild"), true, true);
						m_pCanvas->dispatchEvent(evt);
					}

				//	m_pCurStroke->Measure(LDraw::SizeD(0,0));
				}
			}
			else
			{
				m_points.Add(LDraw::PointF(point.X, point.Y));
			}

		//	Invalidate();

		//	m_points.push_back(LDraw::PointF(point.X, point.Y));

			m_dragging = 2;
			/*
			for (int i = 0; i < 8; i++)
			{
				if (fabs(m_points[i].X - point.X) < 6 && fabs(m_points[i].Y - point.Y) < 6)
				{
					m_dragging = i+1;
					break;
				}
			}
			*/

			//m_dragging = 1;

			if (m_dragging)
			{
				CaptureMouse();
			}
		}
		else if (*type == L"mouseup")
		{
			evt->stopPropagation();

			ReleaseMouseCapture();
			m_dragging = 0;
		}
		else if (*type == L"mousemove")
		{
			evt->stopPropagation();

			MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);

			LDraw::PointD point = ScreenToClient(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

			/*
			{
				LDraw::GraphicsPathF path;
				path.AddMove(m_points[4]);
				path.AddBezier(m_points[5], m_points[6], m_points[7]);
//					path.AddRectangle(LDraw::RectF(80, 80, 100, 100));

				if (LDraw::IsPointInside(&path, LDraw::PointF(point.X, point.Y)))
				{
					MessageBeep(-1);
				}
			}
			*/

			if (m_dragging)
			{

			//	m_pCurStroke->m_points.push_back(point);

				LDraw::PointF delta(point.X - m_oldpoint.X, point.Y - m_oldpoint.Y);

				/*
				if (m_dragging == 1)
				{
					m_points[m_dragging-1] += delta;
					m_points[m_dragging-0] += delta;
				}
				else if (m_dragging == 4)
				{
					m_points[m_dragging-1] += delta;
					m_points[m_dragging-2] += delta;
				}
				else
				*/
				{
			//		m_points[m_dragging-1] += delta;
				}

				m_oldpoint = point;

				if (true)
				{
					if (Shapes::Line* pLine = dynamic_cast<Shapes::Line*>(m_pCurStroke))
					{
						//MessageBeep(-1);
						pLine->set_X2(point.X);
						pLine->set_Y2(point.Y);
						/*
						pLine->SetLayoutOffset(0, 0);
						pLine->Measure(LDraw::SizeD(0, 0));
						pLine->InvalidateArrange();
						*/
						pLine->InvalidateMeasure();
					}
					/*
					else if (UI::Rectangle* pRect = dynamic_cast<UI::Rectangle*>(m_pCurStroke))
					{
						pRect->get_RectangleWidth().put_Value(point.X - m_startpoint.X);
						pRect->get_RectangleHeight().put_Value(point.Y - m_startpoint.Y);
					//	pRect->SetLayoutOffset(0, 0);
						pRect->InvalidateMeasure();
					}
					*/
					else
					{
#if 1
						m_pCurStroke->set_Width(point.X - m_startpoint.X);
						m_pCurStroke->set_Height(point.Y - m_startpoint.Y);
#endif
					//	m_pCurStroke->SetLayoutOffset(0, 0);
						
				//		m_pCurStroke->SetPositionAndSize(m_startpoint.X, m_startpoint.Y, point.X - m_startpoint.X, point.Y - m_startpoint.Y);
						
						//m_pCurStroke->InvalidateMeasure();
					}

					//InvalidateMeasure();
				}
				else
				{
					m_points.Add(LDraw::PointF(point.X, point.Y));
				}

				//Invalidate();
			}
		}
	}
}
#endif

// virtual
void EditLines::OnRender(UI::Graphics* pGraphics)
{
	ASSERT(0);
#if 0
	pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_computedSize.Width, m_computedSize.Height);

	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
	if (true)
	{
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);
		pGraphics->TranslateTransform(0.5, 0.5);
	}

#if 0
//	pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), m_points.begin(), m_points.size());
	pGraphics->DrawPolygon(&LDraw::Pen(LDraw::Color(0, 0, 0), 10), m_points.begin(), m_points.size());

	//pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), 30.5, 30.5, m_computedSize.Width-60, m_computedSize.Height-60);

	/*
	float x = 5;
	float width = 0.04;

	while (x+width < m_computedSize.Width - 5)
	{
		pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), x, 30, width, m_computedSize.Height-60);

		x += width+1.5;
		width *= 1.1f;
	}
	*/
	
#endif
	Control::OnRender(pGraphics);

	pGraphics->SetSmoothingMode(oldSmoothingMode);
	return;

	/*
	float emSize = 4;
	float y = 10;
	while (y + emSize < m_computedSize.Height-5)
	{
		LDraw::FontFamily family(L"Arial");
		LDraw::Font font(&family, emSize);
		sysstring str = L"Hello there, how are you?";
		pGraphics->DrawString(str.c_str(), str.length(), &font, LDraw::PointF(10, y), &LDraw::SolidBrush(LDraw::Color(0, 0, 0)));

		y += emSize+1.2;
		emSize *= 1.15;
	}
	*/
/*
	LDraw::Pen pen(LDraw::Color(0, 0, 0), 20);
	pen.SetLineJoin(LDraw::LineJoinBevel);
	pen.SetMiterLimit(1);

	pGraphics->DrawPolygon(&pen, m_points.begin(), m_points.size());
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 90, 80)), m_points[0].X-3, m_points[0].Y-3, 6, 6);
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 90, 80)), m_points[1].X-3, m_points[1].Y-3, 6, 6);
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 90, 80)), m_points[2].X-3, m_points[2].Y-3, 6, 6);
	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 90, 80)), m_points[3].X-3, m_points[3].Y-3, 6, 6);
*/

	if (0)
	{
		LDraw::CubicBezierF a;
		LDraw::CubicBezierF b;

		a.p0 = LDraw::PointF(20, 20);
		a.p1 = LDraw::PointF(20+180/3.0, 20);
		a.p3 = LDraw::PointF(200, 20);
		a.p2 = LDraw::PointF(200-180/3.0, 20);

		/*
		{
			LDraw::CubicBezierF b;
			LDraw::CubicBezierF c;
			a.SplitHalf(b, c);
		}
		*/

		for (double t = 0; t < 1; t += 0.1)
		{
			LDraw::PointF ev = a.evaluate(t);

			float x = 20 + 180*t;

			pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 0), 1), ev.X, 0, ev.X, 10);
			pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 0), 1), x, 11, x, 21);
		}

		a.ParameterSplitLeft(0.8, b);

		b.p0 = LDraw::PointF(70, 0);
		b.p3 = LDraw::PointF(90, 40);

		double xlk = a.p3.X - a.p0.X;
		double ylk = a.p3.Y - a.p0.Y;
		double xnm = b.p3.X - b.p0.X;
		double ynm = b.p3.Y - b.p0.Y;
		double xmk = b.p0.X - a.p0.X;
		double ymk = b.p0.Y - a.p0.Y;

		double det = xnm * ylk - ynm * xlk;
		if (1.0 + det == 1.0)
		{
			// the lines are parallel

			/*
			ASSERT(index < 9);

			parameters[0][index].t = t0;
			parameters[0][index].i = index;

			parameters[1][index].t = u0;
			parameters[1][index].i = index;
			index++;

			ASSERT(index < 9);

			parameters[0][index].t = t1;
			parameters[0][index].i = index;

			parameters[1][index].t = u1;
			parameters[1][index].i = index;
			index++;
			*/

		}
		else
		{
			double detinv = 1.0 / det;
			double s = (xnm * ymk - ynm*xmk) * detinv;
			double t = (xlk * ymk - ylk*xmk) * detinv;
			if ((s < 0.0) || (s > 1.0) || (t < 0.0) || (t > 1.0))
				;//return;

			/*
			parameters[0][index].t = t0 + s * (t1 - t0);
			parameters[0][index].i = index;

			parameters[1][index].t = u0 + t * (u1 - u0);
			parameters[1][index].i = index;
			index++;
			*/
		}
	}

	LDraw::GraphicsPathD path;
	path.AddRectangle(LDraw::RectD(m_points[0].X, m_points[0].Y, m_points[1].X, m_points[1].Y));
//	path.AddMove(m_points[0]);
//	path.AddBezier(m_points[1], m_points[2], m_points[3]);
	pGraphics->FillPath(LDraw::SolidBrush(LDraw::Color(0, 0, 0)), &path);

	LDraw::GraphicsPathD path2;
	path2.AddRectangle(LDraw::RectD(m_points[4].X, m_points[4].Y, m_points[5].X, m_points[5].Y));
//	path2.AddMove(m_points[4]);
//	path2.AddBezier(m_points[5], m_points[6], m_points[7]);
	pGraphics->FillPath(LDraw::SolidBrush(LDraw::Color(120, 120, 120)), &path2);

	DrawPathText(pGraphics, NULL, 400, 400, &LDraw::SolidBrush(LDraw::Color(60, 160, 60)), &path);
	DrawPathText(pGraphics, NULL, 400, 400, &LDraw::SolidBrush(LDraw::Color(60, 160, 60)), &path2);

	/*
	LDraw::GraphicsPathF path3;
	path3.AddRectangle(LDraw::RectF(40, 90, 100, 100));
	pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 120, 120)), &path3);
	*/

	{
		pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 200), 0.8), m_points[0], m_points[1]);
		pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 200), 0.8), m_points[3], m_points[2]);

		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[0].X-3, m_points[0].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[1].X-3, m_points[1].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[2].X-3, m_points[2].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[3].X-3, m_points[3].Y-3, 6, 6);
	}

	{
		pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 200), 0.8), m_points[4], m_points[5]);
		pGraphics->DrawLine(LDraw::Pen(LDraw::Color(0, 0, 200), 0.8), m_points[7], m_points[6]);

		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[4].X-3, m_points[4].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[5].X-3, m_points[5].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[6].X-3, m_points[6].Y-3, 6, 6);
		pGraphics->FillRectangle(LDraw::SolidBrush(LDraw::Color(200, 0, 0)), m_points[7].X-3, m_points[7].Y-3, 6, 6);
	}

	{
		uint8 grid[400*400];
		memset(grid, 0, 400*400);

		pGraphics->TranslateTransform(400, 0);

		//	path2.Reverse();
		{
			LDraw::GraphicsPathD result = path - path2;

			LDraw::GraphicsPathD result2 = result;// | path2;

			//LDraw::GraphicsPathF result2 = path & result;

	//	LDraw::GraphicsPathF result2 = result & LDraw::GraphicsPathF(LDraw::RectD(82, 402, 100, 98));

			pGraphics->FillPath(new LDraw::SolidBrush(LDraw::Color(0, 0, 0)), result2);
			LDraw::DrawPath(pGraphics, new LDraw::Pen(LDraw::Color(255, 0, 0), 1), result2);
			DrawPathText(pGraphics, grid, 400, 400, new LDraw::SolidBrush(LDraw::Color(60, 160, 60)), result2);

			pGraphics->TranslateTransform(0, 240);
		}

		if (false)
		{
			LDraw::GraphicsPathD result = path - path2;

			LDraw::GraphicsPathD result2 = result | path2;

		//	LDraw::GraphicsPathF result2 = result & path2;
		//	LDraw::GraphicsPathF result2 = result & LDraw::GraphicsPathF(LDraw::RectD(90, 210, 290, 90));
		//	LDraw::GraphicsPathF result2 = path & path;	// self intersect test

			pGraphics->FillPath(LDraw::SolidBrush(LDraw::Color(0, 0, 0)), &result2);
			LDraw::DrawPath(pGraphics, LDraw::Pen(LDraw::Color(0, 100, 200), 1), &result2);
			DrawPathText(pGraphics, grid, 400, 400, &LDraw::SolidBrush(LDraw::Color(60, 160, 60)), &result2);

			pGraphics->TranslateTransform(0, 100);
		}

		/*
		{
			LDraw::GraphicsPathF result2 = path - path2;

			//pGraphics->TranslateTransform(0, 200);
			pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), &result2);
			LDraw::DrawPath(pGraphics, &LDraw::Pen(LDraw::Color(0, 100, 200), 1), &result2);

			pGraphics->TranslateTransform(0, 100);
		}
		*/
	}
	/*
	{
		LDraw::GraphicsPathF result;
		LDraw::DifferencePath(&path, &path2, &result);

	//	LDraw::DrawPath(pGraphics, &LDraw::Pen(LDraw::Color(0, 100, 200), 1), &result);
		pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 100, 200)), &result);
	}
	*/

	/*
	{
		LDraw::BezierD a(LDraw::PointD(m_points[0].X, m_points[0].Y), LDraw::PointD(m_points[1].X, m_points[1].Y), LDraw::PointD(m_points[2].X, m_points[2].Y), LDraw::PointD(m_points[3].X, m_points[3].Y));
		LDraw::BezierD b(LDraw::PointD(m_points[4].X, m_points[4].Y), LDraw::PointD(m_points[5].X, m_points[5].Y), LDraw::PointD(m_points[6].X, m_points[6].Y), LDraw::PointD(m_points[7].X, m_points[7].Y));

		double aparameters[10];
		double bparameters[10];
		double* parameters[2] = {aparameters, bparameters};

		int count = FindIntersections(a, b, parameters);

		std::sort(aparameters, aparameters+count);
		std::sort(bparameters, bparameters+count);

		LDraw::BezierD** bezier = Intersect(a, b, parameters, count);

		for (int i = 0; i < count+1; i++)
		{
		//	LDraw::GraphicsPathF path;
		//	path.AddMove(bezier[0][i].p0);
		//	path.AddBezier(bezier[0][i].p1, bezier[0][i].p2, bezier[0][i].p3);

			LDraw::PointD pt0 = bezier[0][i].evaluate(0);

			for (double t = 0.01; t <= 1; t += 0.01)
			{
				LDraw::PointD pt = bezier[0][i].evaluate(t);

				pGraphics->DrawLine(&LDraw::Pen(LDraw::Color(0, 170, 200), 2), pt0, pt);

				pt0 = pt;
			}

		//	pGraphics->FillPath(&LDraw::SolidBrush(LDraw::Color(0, 200, 0)), &path);
		}

		delete[] bezier[0];
		delete[] bezier[1];
		delete bezier;

		for (i = 0; i < count; i++)
		{
			LDraw::PointD pt = a.evaluate(parameters[0][i]);

			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0, 0, 200)), pt.X-3, pt.Y-3, 6, 6);
		}
	}
	*/

	pGraphics->SetSmoothingMode(oldSmoothingMode);
	/*

	for (int i = 0; i < m_strokes.size(); i++)
	{
		Stroke* pStroke = m_strokes[i];

		pGraphics->DrawLine(&LDraw::Pen(pStroke->m_color, 30), pStroke->m_points[0], pStroke->m_points[1]);

	//	pGraphics->FillPolygon(&LDraw::SolidBrush(LDraw::Color(0, 0, 0)), pStroke->m_points.begin(), pStroke->m_points.size());
	//	pGraphics->DrawPolygon(&LDraw::Pen(LDraw::Color(64, 255, 90, 0), 10), pStroke->m_points.begin(), pStroke->m_points.size());
	}
	*/
#endif
}

class RGBSlidersView : public Control, public IViewOf
{
public:

	virtual Object* get_Viewable()
	{
		return m_pColor;
	}
	virtual void set_Viewable(Object* pViewable)
	{
		m_pColor = dynamic_cast<UI::Color*>(pViewable);

		m_ctl = new ColorPickerRGB;
		set_VisualTree(m_ctl);
	}

	UI::Color* m_pColor;
	ColorPickerRGB* m_ctl;
};



#if 0//WIN32

class OpenGLControl :
	public MSWindows::WindowImpl<OpenGLControl>,
public Control
{
public:

	HGLRC  m_hrc;
	DWORD m_style;
	RECT m_rect;
	HWND m_hOwner;
	WINBOOL bSetupPixelFormat(HDC hdc);
	void CreateContext(HDC hdc, const RECT& rc);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	virtual bool ProcessWindowMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		bool bHandled = true;

		switch (uMsg)
		{
		case WM_CREATE:
			lResult = OnCreate(uMsg, wParam, lParam, bHandled);
			break;

		case WM_DESTROY:
			lResult = OnDestroy(uMsg, wParam, lParam, bHandled);
			break;

		case WM_SIZE:
			lResult = OnSize(uMsg, wParam, lParam, bHandled);
			break;

		case WM_PAINT:
			lResult = OnPaint(uMsg, wParam, lParam, bHandled);
			break;

		default:
			bHandled = false;
		}

		return bHandled;
	}

	void OnArrange(LDraw::SizeD finalSize);

	void put_WindowStyle(/*[in]*/ long newVal)
	{
		m_style = newVal;
		if (m_hWnd)
		{
			SetWindowLong(GWL_STYLE, m_style);
		}
	}

	int put_Owner(/*[in]*/ HWND newVal)
	{
		if (newVal)
		{
			if (!::IsWindow((HWND)newVal))
				return E_FAIL;
		}

		m_hOwner = (HWND)newVal;

		if (m_hWnd == NULL)
		{
			HWND hWnd = Create(m_hOwner, m_rect, NULL, m_style, 0);
			if (hWnd == NULL)
				return -1;
		}
		else
		{
			::SetParent(m_hWnd, m_hOwner);
		}
		return 0;
	}

	void SetRect(/*[in]*/ RECT rect)
	{
		m_rect = rect;
		if (m_hWnd)
		{
			MoveWindow(&m_rect, TRUE);
		}
	}
};

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

LRESULT OpenGLControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	HDC hdc = GetDC(m_hWnd);
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	CreateContext(hdc, rc);

	/*
	const unsigned char* glVendor = glGetString(GL_VENDOR);
	const unsigned char* glRenderer = glGetString(GL_RENDERER);
	const unsigned char* glVersion = glGetString(GL_VERSION);
	const unsigned char*	extstrGL = glGetString(GL_EXTENSIONS);
	*/

//	MessageBox((char*)extstrGL, "", MB_OK);
	HRESULT hr;

//	ASSERT(0);
#if 0
	hr = DirectSoundCreate8(NULL, &m_scene->m_ds8, NULL);
	ASSERT(SUCCEEDED(hr));

	hr = m_scene->m_ds8->SetCooperativeLevel(m_hWnd, DSSCL_NORMAL);
	ASSERT(SUCCEEDED(hr));
	m_scene->GetListener(&m_scene->m_soundListener);
#endif

	//SetTimer(2, 1000/fps);
#if 0
	SetTimer(1, 33);
	joySetThreshold(JOYSTICKID1, 10);
	if (joySetCapture(m_hWnd, JOYSTICKID1, 30, TRUE) == JOYERR_NOERROR)
		m_bstrCaption = _T("Joystick Mode");
#endif

#if 0
	HDC hDC = GetDC();

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
			1,                     // version number
			//PFD_DRAW_TO_BITMAP |   // support window
			PFD_DRAW_TO_WINDOW |   // support window
			PFD_SUPPORT_OPENGL |   // support OpenGL
			0,      // not double buffered
			PFD_TYPE_RGBA,         // RGBA type
			24,                    // 32-bit color depth
			0, 0, 0, 0, 0, 0,      // color bits ignored
			0,                     // no alpha buffer
			0,                     // shift bit ignored
			0,                     // no accumulation buffer
			0, 0, 0, 0,            // accum bits ignored
			32,                    // 16// 32-bit z-buffer
			0,                     // no stencil buffer
			0,                     // no auxiliary buffer
			PFD_MAIN_PLANE,        // main layer
			0,                     // reserved
			0, 0, 0                // layer masks ignored
	};

	//m_hDC = GetDC();

	int  iPixelFormat;
	
	// get the device context's best-available-match pixel format
	iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	
	// make that the device context's current pixel format
	if (!SetPixelFormat(hDC, iPixelFormat, &pfd))
	{
		//AfxMessageBox("!SetPixelFormat()");
		//return;
		ASSERT(0);
	}
	
	// create a rendering context
	if (!(m_hglrc = wglCreateContext (hDC)))
	{
		//AfxMessageBox("!wglCreateContext()");
		//return;
		ASSERT(0);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);	// TODO
	//ASSERT(glGetError() == GL_NO_ERROR);

	ReleaseDC(hDC);
#endif

	return 0;
}

LRESULT OpenGLControl::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	::wglMakeCurrent(NULL,  NULL);

	if (m_hrc)
	{
		::wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}

	return 0;
}

WINBOOL OpenGLControl::bSetupPixelFormat(HDC hdc)
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

void OpenGLControl::CreateContext(HDC hdc, const RECT& rc)
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

LRESULT OpenGLControl::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	::wglMakeCurrent(NULL,  NULL);
	if (m_hrc)
	{
		::wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
	HDC hdc = GetDC(m_hWnd);
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	CreateContext(hdc, rc);
	glViewport(0, 0, rc.right, rc.bottom);

#if 0
	CRect client;
	GetClientRect(&client);

#if 0
	if (m_hglrc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}

	if (m_hBitmap)
	{
		SelectObject(m_hDC, m_hOldBitmap);
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}

	int w = client.Width();
	int h = client.Height();

	LPBITMAPINFO lpbmi = (LPBITMAPINFO)GlobalAlloc(GMEM_ZEROINIT, sizeof(BITMAPINFOHEADER)/*+sizeof(RGBQUAD)*256*/);
	lpbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	lpbmi->bmiHeader.biPlanes = 1;
	lpbmi->bmiHeader.biBitCount = 24;
	lpbmi->bmiHeader.biCompression = BI_RGB;
	lpbmi->bmiHeader.biWidth = w;
	lpbmi->bmiHeader.biHeight = h;

	LPBYTE bits;
	m_hBitmap = CreateDIBSection(NULL, lpbmi, DIB_RGB_COLORS, (void**)&bits, NULL, 0);

	if (m_hBitmap)
	{
		m_hOldBitmap = (HBITMAP)SelectObject(m_hDC, m_hBitmap);
		
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
				1,                     // version number
				PFD_DRAW_TO_BITMAP |   // support window
				//PFD_DRAW_TO_WINDOW |   // support window
				PFD_SUPPORT_OPENGL |   // support OpenGL
				0,      // not double buffered
				PFD_TYPE_RGBA,         // RGBA type
				24,                    // 32-bit color depth
				0, 0, 0, 0, 0, 0,      // color bits ignored
				0,                     // no alpha buffer
				0,                     // shift bit ignored
				0,                     // no accumulation buffer
				0, 0, 0, 0,            // accum bits ignored
				32,                    // 16// 32-bit z-buffer
				0,                     // no stencil buffer
				0,                     // no auxiliary buffer
				PFD_MAIN_PLANE,        // main layer
				0,                     // reserved
				0, 0, 0                // layer masks ignored
		};

		//m_hDC = GetDC();
	
		int  iPixelFormat;
		
		// get the device context's best-available-match pixel format
		iPixelFormat = ChoosePixelFormat(m_hDC, &pfd);
		
		// make that the device context's current pixel format
		if (!SetPixelFormat(m_hDC, iPixelFormat, &pfd))
		{
			//AfxMessageBox("!SetPixelFormat()");
			//return;
			ASSERT(0);
		}
		
		// create a rendering context
		if (!(m_hglrc = wglCreateContext (m_hDC)))
		{
			//AfxMessageBox("!wglCreateContext()");
			//return;
			ASSERT(0);
		}

#if 0
		// make it the calling thread's current rendering context
		if (!wglMakeCurrent (m_hDC, m_hglrc))
		{
			//AfxMessageBox("!wglMakeCurrent()");
			//return;
			ASSERT(0);
		}

		const GLubyte *extstrGL;

		extstrGL = glGetString(GL_EXTENSIONS);

		::MessageBox(NULL, (char*)extstrGL, "", MB_OK);
#endif
	}
#endif
#endif

	return 0;
}

LRESULT OpenGLControl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	PAINTSTRUCT ps;
	BeginPaint(m_hWnd, &ps);

	ASSERT(m_hrc);

	wglMakeCurrent(ps.hdc, m_hrc);

	RECT rc;
	GetClientRect(m_hWnd, &rc);

	int w = rc.right;
	int h = rc.bottom;

	if (m_hrc)
	{
		glClearColor(
			0,//lpbmi->bmiColors[0].rgbRed/256.0,
			0,//lpbmi->bmiColors[0].rgbGreen/256.0, 
			0,//lpbmi->bmiColors[0].rgbBlue/256.0,
			0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	glClear(GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	// Rem?

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
	//
		double fov;
		fov = M_PI/4;

		if (true)
		{
			gluPerspective(gmDegrees(fov), (GLfloat)w / (GLfloat)h, 0.08, 1000.0);
		}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//glLoadMatrixf((float*)modelm);

		glEnable(GL_DEPTH_TEST);
	//	glEnable(GL_LIGHTING);

		glEnable(GL_NORMALIZE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);	// This takes more time

		//bool headlight = true;
		glTranslatef(0, 0, -0.08);

		/*
		//if (headlight)
		{
			GLfloat light_direction[4] = { -1, 0, 0, 0};	// directional
			GLfloat color[4] = {1, 1, 1, 1};
			GLfloat ambient[4] = {0, 0, 0, 1};

			glEnable(GL_LIGHT0+0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
			glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
			//glLightfv(GL_LIGHT0, GL_SPECULAR , color);

		}

		{
			GLfloat light_direction[4] = { 2, 0, 0, 1};	// positional
			GLfloat color[4] = {1, 1, 1, 1};
			GLfloat ambient[4] = {0, 0, 0, 1};

			glEnable(GL_LIGHT1);
			glLightfv(GL_LIGHT1, GL_POSITION, light_direction);
			glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
			//glLightfv(GL_LIGHT0, GL_SPECULAR , color);

		}

	//		glRotate(gmDegrees(orientation->m_value.m_a), -norientation);

		{
			float diffuse[4] = {1, 1, 0, 1};
			float specular[4] = {1, 1, 1, 1};

			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, 0.08*128);

		GLUquadricObj* q = gluNewQuadric();
		//gluQuadricTexture(q, TRUE);
		gluSphere(q, 1, 12, 12);
		gluDeleteQuadric(q);
		}
		*/
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glVertex3f(-1, -1, 0);
		glVertex3f(1, -1, 0);
		glVertex3f(1, 1, 0);
		glVertex3f(-1, 1, 0);
		glEnd();
	}

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	EndPaint(m_hWnd, &ps);

	return 0;
}

void OpenGLControl::OnArrange(LDraw::SizeD finalSize)
{
//	CLXUIVisual::Arrange(finalSize);

#if 1
	UI::WindowBase2* pWindowBase = dynamic_cast<UI::WindowBase2*>(get_OwnerWindow());
	if (pWindowBase)
	{
		UI::CUIFrameImpl* pOwnerWindow = dynamic_cast<UI::CUIFrameImpl*>(pWindowBase->m_pSite);
		if (pOwnerWindow)
		{
			if (pOwnerWindow->GetHwnd())
			{
				put_WindowStyle(WS_CHILD | WS_VISIBLE);
				put_Owner(pOwnerWindow->GetHwnd());

				LDraw::RectD bounds = GetWindowBounds();

				RECT rect;
				rect.left = bounds.X;
				rect.top = bounds.Y;
				rect.right = bounds.GetRight();
				rect.bottom = bounds.GetBottom();

				SetRect(rect);
			}
		}
	}
#endif
}

#endif

__live_object_ptr<ScrollViewer> m_propertyPalette;

Display::Display(UIElement* visual)
{
	root = visual;

	m_tree = new UI::TreeControl;

	m_item = NULL;

	m_tree->AddColumn(new UI::TextString(WSTR("Element Name -----------------------")));
	m_tree->AddColumn(new UI::TextString(WSTR("Last Event")));

	BuildChildren(m_tree, root, m_tree);

	set_VisualTree(m_tree);
}

void Display::BuildChildren(UI::TreeControl* tree, UIElement* visual, ITreeParent* parent)
{
	ASSERT(0);
#if 0
	UI::TreeItemChildren* children = NULL;

	UI::UIElement* child = visual->get_VisualTree();
	if (child)
	{
		children = new UI::TreeItemChildren(tree);

		UI::TreeItem* item = new UI::TreeItem(tree);
		Item* item2 = new Item(this);
		item2->m_treeItem = item;
		item->m_userdata = item2;
		item2->m_Visual = child;
		child->m_userdata[WSTR("display_1")] = item2;

		EventTargetImpl* target = child;
		target->addEventListener(NULL, item2, false);

		item->AppendColumnCell(new UI::TextString(WSTR("VisualTree")));
		item->AppendColumnCell(item2->m_eventCtl);

		BuildChildren(tree, dynamic_cast<UIElement*>(child), item);

		children->AppendItem(item);
	}
	else
	{
		int ncount = visual->get_rchildList()->get_Size();
		for (int i = 0; i < ncount; i++)
		{
			if (children == NULL)
				children = new UI::TreeItemChildren(tree);

			UI::UIElement* child = (*visual->get_rchildList())[i];

			UI::TreeItem* item = new UI::TreeItem(tree);
			Item* item2 = new Item(this);
			item2->m_treeItem = item;
			item->m_userdata = item2;
			item2->m_Visual = child;
			child->m_userdata[WSTR("display_1")] = item2;

			EventTargetImpl* target = child;
			target->addEventListener(NULL, item2, false);

			StringA* classname = child->GetType()->m_qname;
			/*
			{
				void* vtable = *(void**)child;
				rti* p3 = ((rti**)vtable)[-1];

				int count = p3->m_classHierarchyDescriptor->count;
				BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

				Type_Info* ti = (Type_Info*)table[0]->typedesc;
				classname = ti->name() + strlen("class ");
			}
			*/

			item->AppendColumnCell(new UI::TextString(classname->ToStringW()));
			item->AppendColumnCell(item2->m_eventCtl);

			BuildChildren(tree, child, item);

			children->AppendItem(item);
		}
	}

	if (children)
		parent->set_Children(children);
#endif
}

/*
// virtual
LDraw::SizeD Display::MeasureOverride(LDraw::SizeD availSize)
{
	return Control::MeasureOverride(availSize);
}
*/

#if 0
// virtual
void Display::handleEvent(System::Event* evt)
{
	ASSERT(0);
#if 0

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"command")
		{
			if (true)
			{
#if 0
				UI::TreeControl* m_tree = new UI::TreeControl;

				m_tree->AddColumn(new UI::TextString(WSTR("Name")));
				m_tree->AddColumn(new UI::TextString(WSTR("Value")));

				Properties* properties = new Properties;
				properties->CreateRows(m_item->m_Visual, m_tree/*, m_tree*/);
				properties->ExpandRows(m_tree/*, m_tree*/);

				m_tree->put_Children(properties);
				m_propertyPalette->put_Content(m_tree);
#else
				PropertiesWindow* properties = new PropertiesWindow(m_item->m_Visual);
				m_propertyPalette->set_Content(properties);
#endif
			}
			else if (false)
			{
#if WIN32
				IO::ISequentialByteStream* stream = new IO::ByteStreamWriter(ASTR("C:\\test2.swf"));
			//	stream->AddRef();

				{
					SWF::Encoder* pEncoder = new SWF::Encoder;
					pEncoder->m_stream = stream;
				//	pEncoder->m_stream->AddRef();

					SWF::Rect rect(0, 600*20, 0, 600*20);
					pEncoder->WriteHeader();
					pEncoder->WriteMovieHeader(rect, 24*256, 1);

					pEncoder->WriteSetBackgroundColorTag(SWF::RGBColor(255, 255, 255));

					uint16 id = 2;
					swfWriteCommands(stream, LDraw::Matrix3f::GetIdentity(), m_item->m_Visual->m_pDrawCommands, &id);

					pEncoder->WriteShowFrameTag();
					pEncoder->WriteEndTag();

					pEncoder->Close();
				}

			//	stream->Release();
#endif
			}
			else if (true)
			{
				IO::ISequentialByteStream* stream = new IO::ByteStreamWriter(ASTR("C:\\test.emf"));
			//	stream->AddRef();

				wmf::EMFWriter emfwriter;

				wmf::EMFHEADER emfheader;
				emfheader.RecordType = wmf::emfHEADER;
				emfheader.RecordSize = sizeof(emfheader);
				emfheader.Signature = 0x464D4520;
				emfheader.Version = 65536;

				emfheader.BoundsLeft = 0;
				emfheader.BoundsTop = 0;
				emfheader.BoundsRight = 1200*20;
				emfheader.BoundsBottom = 1200*20;

				emfheader.FrameLeft = 0;
				emfheader.FrameTop = 0;
				emfheader.FrameRight = 1200*20;
				emfheader.FrameBottom = 1200*20;

				emfheader.NumPalEntries = 0;
				emfheader.WidthDevPixels = 1024;
				emfheader.HeightDevPixels = 768;
				emfheader.WidthDevMM = 320;
				emfheader.HeightDevMM = 240;
				emfheader.SizeOfDescrip = 0;
				emfheader.OffsOfDescrip = 0;
				emfheader.Reserved = 0;
				emfwriter.m_recs = 1;

				stream->Write(&emfheader, sizeof(emfheader));

				emfwriter.WriteSetMapMode(stream, MM_TEXT/*MM_ANISOTROPIC 8*/);
				emfwriter.WriteSetWindowOrgEx(stream, 0, 0);
				emfwriter.WriteSetViewportOrgEx(stream, 0, 0);
				emfwriter.WriteSetWindowExtEx(stream, 1200, 1200);
				emfwriter.WriteSetViewportExtEx(stream, 1200, 1200);

				// Create a NULL pen that is available for the rest of the commands
				wmf::LOGPEN lp;
				lp.lopnStyle = PS_NULL;
				lp.lopnWidth = 0;
				lp.lopnWidthY = 0;
				lp.lopnColor = 0;
				emfwriter.WriteCreatePen(stream, 1, lp);

				emfwriter.WriteSetBkMode(stream, TRANSPARENT);

				emfwriter.WriteCommands(stream, LDraw::matrix3f::getIdentity(), m_item->m_Visual->m_pDrawCommands);

				emfwriter.WriteEOF(stream);

				emfheader.NumOfRecords = emfwriter.m_recs;
				emfheader.NumOfHandles = emfwriter.m_handles+1;
				emfheader.Size = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
				stream->Seek(0, System::IO::STREAM_SEEK_SET);
				stream->Write(&emfheader, sizeof(emfheader));

			//	stream->Release();
			}
			else
			{
				EditTransform* p = new EditTransform;
			//	p->put_Width(200);
			//	p->put_Height(200);

			//	DropShadow* p = new DropShadow;
				UIElement* parent = m_item->m_Visual->GetRParent();
				if (m_item->m_Visual == dynamic_cast<UIElement*>(parent)->get_VisualTree())
				{
				//	parent->RemoveRChild(m_item->m_Visual);
					
					parent->set_VisualTree(NULL);
					p->set_Content(m_item->m_Visual);

					//p->Arrange(p->get_DesiredSize());

					parent->set_VisualTree(p);

					//p->InvalidateRender();

					p->Measure(LDraw::SizeD(0, 0));
					p->InvalidateMeasure();
				/*
					UIElement* parentparent = dynamic_cast<UIElement*>(parent)->GetRParent();
					parentparent->RemoveRChild(dynamic_cast<UIElement*>(parent));
					parentparent->AddRChild(dynamic_cast<UIElement*>(parent));
					*/
				//dynamic_cast<UIElement*>(parent)->InvalidateRender();
				/*
				p->Invalidate();
				m_item->m_Visual->InvalidateMeasure();
				m_item->m_Visual->Invalidate();
				*/
				}
				else
				{
					parent->RemoveRChild(m_item->m_Visual);
					p->set_Content(m_item->m_Visual);
					parent->AddRChild(p);
				}


			//	BuildChildren(m_tree, root, m_tree);
			//	BuildChildren(m_tree, 
			//	put_Children(
				/*
				UI::TreeControl* tree = new UI::TreeControl;

				tree->m_treeHeader->AddColumn(new UI::TextString(WSTR("Element")));
				tree->m_treeHeader->AddColumn(new UI::TextString(WSTR("Last Event")));

				BuildChildren(tree, root, tree);

				put_VisualTree(tree);
				*/

				//parent->InvalidateMeasure();
			}
		}
		else if (*evt->get_type() == L"contextmenu")	// ItemStateChanging
		{
			evt->stopPropagation();
			UI::MouseEvent* mouseEvt = dynamic_cast<MouseEvent*>(evt);

			UI::TreeItem* item;
			UI::UIElement* target = dynamic_cast<UI::UIElement*>(evt->get_target());
			while (target)
			{
				item = dynamic_cast<UI::TreeItem*>(target);
				if (item) break;

				target = dynamic_cast<UI::UIElement*>(target->GetRParent());
			}

			m_item = dynamic_cast<Item*>(item->m_userdata);

			CLXUIMenuElement* menu = new CLXUIMenuElement();
			menu->SetRParent(this);
			menu->SetOwnerWindow(GetOwnerWindow());

			{
				menu->AddItem(new TextString(WSTR("Undo")), 100);
				menu->AddItem(new TextString(WSTR("Redo")), 101);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Cut")), 102);
				menu->AddItem(new TextString(WSTR("Copy")), 103);
				menu->AddItem(new TextString(WSTR("Paste")), 104);
				menu->AddItem(new TextString(WSTR("Delete")), 105);
				menu->AddItem(new TextString(WSTR("Trim")), 106);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("View All")), 114);
				menu->AddItem(new TextString(WSTR("View Selection")), 115);
				menu->AddItem(new TextString(WSTR("Zoom In")), 116);
				menu->AddItem(new TextString(WSTR("Zoom Out")), 117);
				menu->AddItem(new TextString(WSTR("1:1")), 118);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Mute")), 120);
				menu->AddItem(new TextString(WSTR("Insert Silence")), 121);
				menu->AddItem(new TextString(WSTR("Reverse")), 122);
				menu->AddSeparator();
				menu->AddItem(new TextString(WSTR("Play / Stop")), 130);
				menu->AddItem(new TextString(WSTR("Controls")), 131);
			}

			/*
			menu->AddSeparator();
			menu->AddItem(new TextString(WSTR("Insert/Remove Breakpoint")), ID_DEBUG_TOGGLEBREAKPOINT);
			*/

			menu->GetMenuPopup()->Popup(menu, LDraw::PointI(mouseEvt->get_ScreenX(), mouseEvt->get_ScreenY()));
		}
		else if (*evt->get_type() == L"ActivateItem")	// 
		{
			evt->stopPropagation();
			
			UI::TreeItem* item = dynamic_cast<UI::TreeItem*>(evt->get_target());

			m_item = dynamic_cast<Item*>(item->m_userdata);

			if (true)
			{
				PropertiesWindow* properties = new PropertiesWindow(m_item->m_Visual);
				m_propertyPalette->set_Content(properties);

#if 0
				for (int i = 0; i < m_document->m_selectedObjects.GetSize(); i++)
				{
					m_document->m_selectedObjects[i]->m_object->m_bSelected = false;
				}
				m_document->m_selectedObjects.RemoveAll();

				SelectedObject* pSelectedObject = new SelectedObject;
				pSelectedObject->m_object = m_item->m_Visual;
				pSelectedObject->m_object->m_bSelected = true;

				m_document->m_selectedObjects.Add(pSelectedObject);

				m_document->Invalidate();
#endif

#if 0
				UI::TreeControl* m_tree = new UI::TreeControl;

				m_tree->AddColumn(new UI::TextString(WSTR("Name")));
				m_tree->AddColumn(new UI::TextString(WSTR("Value")));

				Properties* properties = new Properties;
				properties->CreateRows(m_item->m_Visual, m_tree/*, m_tree*/);
				properties->ExpandRows(m_tree/*, m_tree*/);

				m_tree->put_Children(properties);

				m_propertyPalette->put_Content(m_tree);
#endif
			}
		}
	}
#endif
}
#endif

#if 0
void Display::Item::handleEvent(System::Event* evt)
{
	//if (evt->get_eventPhase() == CAPTURING_PHASE)
	{
		StringW* type = evt->get_type();
		if (*type == L"InsertChild")
		{
			MutationEvent* mutEvt = static_cast<MutationEvent*>(evt);

			UIElement* child = mutEvt->m_element;

			Item* parentItem = (Item*)child->GetRParent()->m_userdata[WSTR("display_1")];

			UI::TreeItemChildren* children = dynamic_cast<UI::TreeItemChildren*>(parentItem->m_treeItem->get_Children());
			if (children == NULL)
			{
				children = new UI::TreeItemChildren(m_root->m_tree);
				parentItem->m_treeItem->set_Children(children);
			}

			UI::TreeItem* item = new UI::TreeItem(m_root->m_tree);
			Item* item2 = new Item(m_root);
			item2->m_treeItem = item;
			item->m_userdata = item2;
			item2->m_Visual = child;
			child->m_userdata[WSTR("display_1")] = item2;

			EventTargetImpl* target = child;
			target->addEventListener(NULL, item2, false);

			StringA* classname = child->GetType()->m_qname;
			item->AppendColumnCell(new UI::TextString(classname->ToStringW()));
			item->AppendColumnCell(item2->m_eventCtl);

			m_root->BuildChildren(m_root->m_tree, child, item);

			children->AppendItem(item);
			/*

			if (child->GetRParent()->get_Children() == NULL)
			{
			}

			m_root->BuildChildren(m_root->m_tree, mutEvt->m_element, m_treeItem);

			m_root->InvalidateMeasure();
			*/
		}
	}
//	m_eventCtl->put_TextContent(evt->get_type());
	//m_treeItem->
}
#endif

#if WIN32

class EditAffineTransformImage : public Control
{
public:
	EditAffineTransformImage()
	{
		dragging = 0;

	//	m_bitmap = LDraw::Bitmap(WSTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.pcx"));
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(ASTR("C:\\test.pcx"));
		m_bitmap = loader->GetBitmap();

		destPoints[0] = LDraw::PointF(1, 1);
		destPoints[1] = LDraw::PointF(m_bitmap->GetWidth(), 0);
		destPoints[2] = LDraw::PointF(0, m_bitmap->GetHeight());

		/*
		destPoints[0] = LDraw::PointF(10.25, 0);
		destPoints[1] = LDraw::PointF(10, 40);
		destPoints[2] = LDraw::PointF(40, 40);
		*/

		SetClipMode(false);

		m_srcx = 0;
		m_srcy = 0;
		m_srcwidth = m_bitmap->GetWidth();
		m_srcheight = m_bitmap->GetHeight();

//		m_wrapMode = LDraw::WrapModeTile;
		m_wrapMode = LDraw::WrapModeClamp;
	}

	LDraw::Bitmap* m_bitmap;
	LDraw::PointF destPoints[3];

	double m_srcx;
	double m_srcy;
	double m_srcwidth;
	double m_srcheight;

	LDraw::WrapMode m_wrapMode;

	double get_SrcX();
	void put_SrcX(double srcx);

	double get_SrcY();
	void put_SrcY(double srcy);

	double get_SrcWidth();
	void put_SrcWidth(double srcwidth);

	double get_SrcHeight();
	void put_SrcHeight(double srcheight);

	LDraw::WrapMode get_WrapMode();
	void put_WrapMode(LDraw::WrapMode wrapMode);

	int dragging;

	LDraw::PointD m_oldpoint;

	virtual void OnRender(Graphics* pGraphics);

#if 0
void handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);

			LDraw::PointD point = ScreenToClient(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

			m_oldpoint = point;

			dragging = 0;

			for (int i = 0; i < 3; i++)
			{
				LDraw::PointF point2 = destPoints[i];

				if (fabs(point2.X - point.X) < 16 && fabs(point2.Y - point.Y) < 16)
				{
					dragging = i+1;
					MessageBeep(-1);
					break;
				}
			}

			dragging = 1;
			CaptureMouse();

			evt->stopPropagation();
		}
		else if (*type == L"mouseup")
		{
			ReleaseMouseCapture();
			evt->stopPropagation();
			dragging = 0;
		}
		else if (*type == L"mousemove")
		{
			MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);

			if (dragging)
			{
				LDraw::PointD point = ScreenToClient(mouseevt->get_ScreenX(), mouseevt->get_ScreenY());

				TRACE("%f, %f\n", point.X, point.Y);

				destPoints[dragging-1].X += (point.X-m_oldpoint.X);// / 8.0;
				destPoints[dragging-1].Y += (point.Y-m_oldpoint.Y);// / 8.0;

				/*
				destPoints[0].X += (point->get_X()-m_oldpoint.X) / 3.0;
				destPoints[0].Y += (point->get_Y()-m_oldpoint.Y) / 3.0;
				destPoints[1].X = destPoints[0].X + m_pBitmap->GetWidth()/2;//(point->get_X()-m_oldpoint.X) / 5.0;
				destPoints[1].Y = destPoints[0].Y;//(point->get_Y()-m_oldpoint.Y) / 5.0;
				destPoints[2].X = destPoints[0].X;//(point->get_X()-m_oldpoint.X) / 5.0;
				destPoints[2].Y = destPoints[0].Y + m_pBitmap->GetHeight()/2;//(point->get_Y()-m_oldpoint.Y) / 5.0;
				*/

				/*
				destPoints[0] = LDraw::PointF(60+point->get_X()/10, 0);
				destPoints[1] = LDraw::PointF(200+point->get_X()/10, 0);
				destPoints[2] = LDraw::PointF(60+point->get_X()/10, 200);
				*/

				m_oldpoint.X = point.X;
				m_oldpoint.Y = point.Y;

				Invalidate();
			}
			evt->stopPropagation();
		}
	}
}
#endif

};

LDraw::WrapMode EditAffineTransformImage::get_WrapMode()
{
	return m_wrapMode;
}

void EditAffineTransformImage::put_WrapMode(LDraw::WrapMode wrapMode)
{
	m_wrapMode = wrapMode;
	InvalidateRender();
}

double EditAffineTransformImage::get_SrcX()
{
	return m_srcx;
}

void EditAffineTransformImage::put_SrcX(double srcx)
{
	m_srcx = srcx;
	InvalidateRender();
}

double EditAffineTransformImage::get_SrcY()
{
	return m_srcy;
}

void EditAffineTransformImage::put_SrcY(double srcy)
{
	m_srcy = srcy;
	InvalidateRender();
}

double EditAffineTransformImage::get_SrcWidth()
{
	return m_srcwidth;
}

void EditAffineTransformImage::put_SrcWidth(double srcwidth)
{
	m_srcwidth = srcwidth;
	InvalidateRender();
}

double EditAffineTransformImage::get_SrcHeight()
{
	return m_srcheight;
}

void EditAffineTransformImage::put_SrcHeight(double srcheight)
{
	m_srcheight = srcheight;
	InvalidateRender();
}

void EditAffineTransformImage::OnRender(UI::Graphics* pGraphics)
{
	pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(255, 0, 0)), 0, 0, m_computedSize.Width, m_computedSize.Height);

#if 0

	LDraw::Color colors[3] =
	{
		LDraw::Color(255, 0, 0),
		LDraw::Color(0, 255, 0),
		LDraw::Color(0, 0, 255),
	};

//	pGraphics->FillTriangle(destPoints, colors);

#else
	//HBITMAP hbm = (HBITMAP)LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

		LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
		pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

	//	pGraphics->RotateTransform(20);
//		pGraphics->TranslateTransform(destPoints[0].X, destPoints[0].Y);

#if 0
		LDraw::TextureBrush brush(&m_bitmap, m_wrapMode, LDraw::RectF(m_srcx, m_srcy, m_srcwidth, m_srcheight));
	//	brush.TranslateTransform(0, 0);

		pGraphics->FillEllipse(brush, destPoints[0].X, destPoints[0].Y, m_computedSize.Width - destPoints[0].X, m_computedSize.Height - destPoints[0].Y);
#else
		pGraphics->DrawImage(m_bitmap, LDraw::RectF(destPoints[0].X, destPoints[0].Y, m_srcwidth, m_srcheight), m_srcx, m_srcy, m_srcwidth, m_srcheight, m_wrapMode);
	//	pGraphics->DrawImage(&m_bitmap, LDraw::RectF(destPoints[0].X, destPoints[0].Y, m_bitmap.GetWidth(), m_bitmap.GetHeight()), m_srcx, m_srcy, m_srcwidth, m_srcheight);
#endif

	//	LDraw::Font font(L"Arial", 20);

	//	pGraphics->DrawString("ABC", &font, LDraw::PointF(10, 10), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
	//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0,0,0)), 20, 20, 100, 100);

		pGraphics->SetSmoothingMode(oldSmoothingMode);

	{
	//	LDraw::Bitmap bitmap(hbm, NULL);

//			pGraphics->ScaleTransform(8, 8);
	//	destPoints[0] = LDraw::PointF(0, 0);
	//	destPoints[1] = LDraw::PointF(pBitmap->GetWidth()/4, 50);
	//	destPoints[2] = LDraw::PointF(destPoints[2].X, pBitmap->GetHeight());

//		pGraphics->DrawImage(m_pBitmap, destPoints, 0, 0, m_pBitmap->GetWidth(), m_pBitmap->GetHeight());
	}
	//DeleteObject(hbm);
#endif
}

#endif

#if 0

class DocumentFrame : public Control, public IBindCallback
{
public:
	Object* m_object;
	//std::string m_url;

	HRESULT OnObjectAvailable(Object* /*object*/, const sysstring& url)
	{
		m_object = new LXML::CHTMLWindow;
		dynamic_cast<LXML::CHTMLWindow*>(m_object)->Load(url);

		put_VisualTree(dynamic_cast<Control*>(m_object));
		InvalidateArrange();
		Invalidate();
		return S_OK;
	}

	virtual HRESULT OnDataAvailable(ULONG cbSize, ISequentialByteStream* stream)
	{
		return dynamic_cast<IBindCallback*>(m_object)->OnDataAvailable(cbSize, stream);
	}

	virtual HRESULT OnDone()
	{
		return dynamic_cast<IBindCallback*>(m_object)->OnDone();
	}
};
#endif

#if WIN32

StringW* PictureType[4] =
{
	WSTR("I"),
	WSTR("P"),
	WSTR("B"),
	WSTR("D"),
};

class MpegFrameItem : public IItem
{
public:
	IntegerField* m_type;
	IntegerField* m_groupIndex;
	LongLongField* m_displayNr;
	LongLongField* m_encodedNr;

	virtual FieldData* GetFieldData(int ind)
	{
		if (ind == 0)
			return m_displayNr;
		else if (ind == 1)
			return m_encodedNr;
		else if (ind == 2)
			return m_type;
		else if (ind == 3)
			return m_groupIndex;
		else
			return NULL;
	}
	virtual UIElement* GetFieldUI(int ind)
	{
		if (ind == 0)
		{
			WCHAR buf[16];
			swprintf_s(buf, L"%d", m_displayNr->m_value);
			return new TextString(new StringW(string_copy(buf)));
		}
		else if (ind == 1)
		{
			WCHAR buf[16];
			swprintf_s(buf, L"%d", m_encodedNr->m_value);
			return new TextString(new StringW(string_copy(buf)));
		}
		else if (ind == 2)
		{
			return new TextString(PictureType[m_type->m_value-1]);
		}
		else if (ind == 3)
		{
			WCHAR buf[16];
			swprintf_s(buf, L"%d", m_groupIndex->m_value);
			return new TextString(new StringW(string_copy(buf)));
		}
		return NULL;
	}
};

#endif

/*
std::multimap<StringA, const Type_Info*> m_viewtypes;

void RegisterView(const Type_Info& objectType, const Type_Info& viewType)
{
	m_viewtypes.insert(std::multimap<StringA, const Type_Info*>::value_type(objectType, &viewType));
}
*/


#if 0
inline char getchar(ISequentialByteStream* stream)
{
	char v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}
#endif


/*
class ThumbnailOf : public UIElement
{
public:
	ThumbnailOf(ISequential
};
*/
class DirEntry
{
public:
	DirEntry()
	{
		name = NULL;
		displayName = NULL;
	}

	StringA* name;
	StringA* displayName;
	LONGLONG size;
	ULONG dwFileAttributes;
	WIN_FILETIME ftCreationTime;
	WIN_FILETIME ftLastAccessTime;
	WIN_FILETIME ftLastWriteTime;
};

/*
WIN_FILETIME operator = (WIN_FILETIME& x, FILETIME& y)
{
	WIN_FILETIME f;
	return f;
}
*/

void GetDir(StringA* dirName, vector<DirEntry> & names)
{
#if WIN32

	if (*dirName == "/")	// root
	{
		char buffer[1024];
		MSWindows::GetLogicalDriveStringsA(1024, buffer);

		char* p = buffer;
		while (*p)
		{
			TRACE("%s\n", p);

			char volumeName[512];
			MSWindows::DWORD filenamelength;
			MSWindows::DWORD flags;

			UINT driveType = MSWindows::GetDriveTypeA(p);

			DirEntry direntry;
			direntry.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
			direntry.name = new StringA(string_copy(p));

			if (MSWindows::GetVolumeInformationA(p, volumeName, 511, NULL, &filenamelength, &flags, NULL, NULL))
			{
				direntry.displayName = new StringA(string_copy(volumeName));
			}
			else
			{
				if (driveType == DRIVE_CDROM)
				{
					direntry.displayName = ASTR("DVD/CD Drive");
				}
				else
				{
					ASSERT(0);
				}
			}

			// append the drivename in parantheses
			char* driveName = p;

			while (*p)
			{
				p++;
			}

			// Remove the tailing backslash
			if (p[-1] == '\\')
				p[-1] = 0;

			ASSERT(0);
#if 0
			direntry.displayName += " (";
			direntry.displayName += driveName;
			direntry.displayName += ")";
#endif

			names.Add(direntry/*fullpath*/);

			p++;
		}

		TRACE("\n");
	}
	else
	{
		char searchPath[512];
		_makepath(searchPath, NULL, dirName->c_str(), "*", NULL);

	//	sprintf(searchPath, "%s/*", directoryName);
		MSWindows::WIN32_FIND_DATAA wfd;
		HANDLE hFindFile = MSWindows::FindFirstFileA(searchPath, &wfd);
		if (hFindFile != MSWindows::Invalid_Handle_Value)
		{
			do
			{
				/*
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					// Maybe recurse ??
				}
				else
				*/
				{
				//	int len = strlen(wfd.cFileName);
				//	if (len >= 4 && !stricmp(wfd.cFileName+len-4, ".ttf"))
					{
					//	char fullpath[512];
					//	sprintf(fullpath, "%s\\%s", dirName.c_str(), wfd.cFileName);

						DirEntry direntry;
						direntry.dwFileAttributes = wfd.dwFileAttributes;
						direntry.size = wfd.nFileSizeLow | ((LONGLONG)wfd.nFileSizeHigh<<32);
						direntry.name = new StringA(string_copy(wfd.cFileName));

						*(ULONGLONG*)&direntry.ftCreationTime = *(ULONGLONG*)&wfd.ftCreationTime;
						*(ULONGLONG*)&direntry.ftLastAccessTime = *(ULONGLONG*)&wfd.ftLastAccessTime;
						*(ULONGLONG*)&direntry.ftLastWriteTime = *(ULONGLONG*)&wfd.ftLastWriteTime;

					//	AddFile(fullpath);
						names.Add(direntry/*fullpath*/);
					}
				}
			}
			while (MSWindows::FindNextFileA(hFindFile, &wfd));

			MSWindows::FindClose(hFindFile);
		}
	}

#else

	if (dirName == "/")	// root
	{
		DosList* dl = LockDosList(LDF_READ | LDF_VOLUMES);
		if (dl)
		{
			while (dl = NextDosEntry(dl, LDF_READ | LDF_VOLUMES))
			{
				DirEntry direntry;
				direntry.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

				direntry.name = (const char*)BADDR(dl->dol_Name);

				names.Add(direntry/*fullpath*/);
			}

			UnLockDosList(LDF_READ | LDF_VOLUMES);
		}
	}
	else
	{
		struct FileInfoBlock* fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
		BPTR lock;

		if (fib != NULL)
		{
			lock = dosLock(DOSBase, const_cast<char*>(dirName.c_str()), ACCESS_READ);
			if (lock != NULL)
			{
				Examine(lock, fib);

			//	char* fullpath = new char[1024];

				while (ExNext(lock, fib) != 0)
				{
			//		int len = strlen(fib->fib_FileName);

				//	strcpy(fullpath, dirName);
				//	AddPart(fullpath, fib->fib_FileName, 1024);

					DirEntry direntry;

					if (fib->fib_DirEntryType > 0)	// directory
						direntry.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
					else
						direntry.dwFileAttributes = 0;

					direntry.name = fib->fib_FileName;
				//	AddFile(fullpath);
					names.Add(direntry/*fullpath*/);

					/*
					CDispLRegFilter* p = new CDispLRegFilter;
					if (p)
					{
						XmlData::Document* document = new XmlData::Document;
						if (document)
						{
							bool success = document->load(ConvertA2S(fullpath));

							XmlData::Element* documentElement = document->get_documentElement();

							if (documentElement)
							{
								p->BuildRegFilter(documentElement);
							}
						}

						m_RegFilters.push_back(p);
					}
					*/
				}

				//delete[] fullpath;

				if (IoErr() != ERROR_NO_MORE_ENTRIES)
				{
					//MessageBox(NULL, "dos Error", "", MB_OK);
				}
				dosUnLock(DOSBase, lock);
			}

			FreeDosObject(DOS_FIB, fib);
		}
	}

#endif
}

class LDrawTest : public Control
{
public:

	LDraw::Bitmap* m_bitmap;

	virtual void OnRender(Graphics* pGraphics)
	{
#if 0
		if (0)
		{
			LDraw::Region rgn1(LDraw::Rect(10, 10, 50, 50));
			LDraw::Region rgn2(LDraw::Rect(40, 40, 50, 50));
			LDraw::Region rgn3(LDraw::Rect(40, 40, 50, 50));

		//	LDraw::Region rgn = rgn2 | rgn1;
			LDraw::Region rgn = rgn2 | rgn1;
			//rgn3) - rgn3;

		//	rgn -= rgn3;

		//	LDraw::FillRegion(pGraphics, &LDraw::SolidBrush(LDraw::Color(255,0,0)), &rgn1);
		//	LDraw::FillRegion(pGraphics, &LDraw::SolidBrush(LDraw::Color(0,255,0)), &rgn2);

			LDraw::FillRegion(pGraphics, new LDraw::SolidBrush(LDraw::Color(0,0,0)), &rgn);

			LDraw::Rect rect;
			rgn.GetRegionRect(&rect);

			pGraphics->DrawRectangle(new LDraw::Pen(LDraw::Color(255, 0, 0), 2), rect);
		}
		else if (0)
		{
			/*
			LDraw::Font font(L"Courier New", 14);

			pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, m_computedSize.Width, m_computedSize.Height);

			pGraphics->DrawString("M", &font, LDraw::PointF(5, 5), &LDraw::SolidBrush(LDraw::Color(0, 0, 0)));
			*/
		}
		else if (0)
		{
			pGraphics->RotateTransform(15);
			pGraphics->TranslateTransform(100, 100);
			LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
			pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

			pGraphics->FillRectangle(new LDraw::SolidBrush(LDraw::Color(0, 0, 0)), -40, -40, 80, 80);

			pGraphics->SetSmoothingMode(oldSmoothingMode);
		}
		else
		{
		//	pGraphics->DrawImage(&m_bitmap, 0, 0);

			LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
			pGraphics->SetSmoothingMode(LDraw::SmoothingModeAntiAlias);

		//	pGraphics->RotateTransform(20);
			pGraphics->TranslateTransform(80.5, 80);

			LDraw::TextureBrush* brush = new LDraw::TextureBrush(m_bitmap, LDraw::WrapModeTile, LDraw::RectF(0, 0, 100, 100));
			brush->TranslateTransform(0, 0);

			pGraphics->FillRectangle(brush, 0.5, 0, m_computedSize.Width-40, m_computedSize.Height-40);

		//	LDraw::Font font(L"Arial", 20);

		//	pGraphics->DrawString("ABC", &font, LDraw::PointF(10, 10), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
		//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0,0,0)), 20, 20, 100, 100);

			pGraphics->SetSmoothingMode(oldSmoothingMode);
		}
#endif
	}
};

class ThumbnailViewer : public Control
{
public:
	ThumbnailViewer()
	{
		GetDir(ASTR("c:/program files/grabit/download/alt.binaries.nospam.breasts.natural"), m_dir);

	//	m_lock.Init();

#if WIN32
		MSWindows::DWORD threadID;
		MSWindows::CreateThread(NULL, 0, tf, this, 0, &threadID);
#else
		ASSERT(0);
#endif
	}

	vector<DirEntry> m_dir;

#if WIN32
	static MSWindows::DWORD WINAPI tf(void* lpParameter)
	{
		((ThumbnailViewer*)lpParameter)->Thread();
		return 0;
	}
#endif

	CriticalSection m_lock;

	LDraw::Bitmap* m_bitmap;

	virtual void OnRender(Graphics* pGraphics)
	{
		m_lock.Lock();
		if (m_bitmap != NULL)
		{
			pGraphics->DrawImage(m_bitmap, LDraw::RectF(0, 0, m_computedSize.Width, m_computedSize.Height), 0, 0, m_bitmap->GetWidth(), m_bitmap->GetHeight());
		}
		m_lock.Unlock();
	}

	void Thread()
	{
		for (int i = 0; i < m_dir.GetSize(); i++)
		{
			Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
			loader->Load(m_dir[i].name);
			LDraw::Bitmap* bitmap = loader->GetBitmap();

			m_lock.Lock();
			m_bitmap = bitmap;
			m_lock.Unlock();
			Invalidate();

#if WIN32
			MSWindows::Sleep(0);
#endif
		}
	}
};

/*
class Object
{
public:
};
*/

vector<IViewOf*> m_views;

FileObject::FileObject()
{
	m_Size = 0;
	m_FileAttributes = 0;
//	m_children = NULL;
}

/*
DirectoryObject* FileObject::get_Children()
{
	return m_children;
}
*/

StringA* FileObject::get_Name()
{
	return m_Name;
}

void FileObject::set_Name(StringA* name)
{
	m_Name = name;
}

LONGLONG FileObject::get_Size()
{
	return m_Size;
}

WIN_FILETIME FileObject::get_CreationTime()
{
	return m_CreationTime;
}

WIN_FILETIME FileObject::get_LastAccessTime()
{
	return m_LastAccessTime;
}

WIN_FILETIME FileObject::get_LastWriteTime()
{
	return m_LastWriteTime;
}

#if 0

class ZipArchiveView : public IViewOf, public Control
{
public:
	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	class ZipEntryItem : public IItem, public _ObjectImpl
	{
	public:
		StringField* m_name;
		/*
		IntegerField* m_type;
		IntegerField* m_groupIndex;
		LongLongField* m_displayNr;
		LongLongField* m_encodedNr;
		*/

		virtual FieldData* GetFieldData(int ind)
		{
			if (ind == 0)
				return m_name;
			/*
			else if (ind == 1)
				return m_encodedNr;
			else if (ind == 2)
				return m_type;
			else if (ind == 3)
				return m_groupIndex;
			else
			*/
				return NULL;
		}
		virtual UIElement* GetFieldUI(int ind)
		{
			if (ind == 0)
			{
				//OLECHAR buf[16];
				//swprintf(buf, WSTR("%d"), m_displayNr->m_value);
				return new TextString(m_name->m_value);
			}
			/*
			else if (ind == 1)
			{
				OLECHAR buf[16];
				swprintf(buf, WSTR("%d"), m_encodedNr->m_value);
				return new TextString(buf);
			}
			else if (ind == 2)
			{
				return new TextString(PictureType[m_type->m_value-1]);
			}
			else if (ind == 3)
			{
				OLECHAR buf[16];
				swprintf(buf, WSTR("%d"), m_groupIndex->m_value);
				return new TextString(buf);
			}
			*/
			return NULL;
		}
	};

	ZIP::Archive* m_pZipArchive;

	ZipArchiveView(FileObject* pFile)
	{
		m_pFile = pFile;

		TreeControlContainer* ctl2 = new TreeControlContainer;
		ctl2->AddField(WSTR("Name"));
	//	ctl2->AddField(WSTR("Compressed Size"));
	//	ctl2->AddField(WSTR("Compressed Size"));
//		ctl2->AddField(WSTR("Type"));
//		ctl2->AddField(WSTR("Group"));

		m_pZipArchive = new ZIP::Archive;
		m_pZipArchive->Open(new FileByteStream(pFile->m_Fullname));

		ULONG nfiles = m_pZipArchive->GetFileCount();
		for (int i = 0; i < nfiles; i++)
		{
			ZIP::File* pFile = m_pZipArchive->GetFile(i);

			ZipEntryItem* item = new ZipEntryItem;

			item->m_name = new StringField(ConvertA2S(pFile->GetName()));
			/*
			item->m_encodedNr = new LongLongField(i);
			item->m_type = new IntegerField(pic->m_picture_coding_type);
			item->m_groupIndex = new IntegerField(pic->m_iGroup);
			*/

			ctl2->AddItem(item);
		}

		put_VisualTree(ctl2);
	}

	virtual void handleEvent(System::Event* evt)
	{
		if (evt->get_eventPhase() != System::CAPTURING_PHASE)
		{
			if (evt->get_type() == WSTR("Activate"))
			{
				evt->stopPropagation();

				IItemSite* itemsite = dynamic_cast<IItemSite*>(evt->get_target());
				ZipEntryItem* zipFile = dynamic_cast<ZipEntryItem*>(itemsite->GetItem());
			}
		}
	}
};

#endif

void DirectoryObject::SetDir(FileObject* pFile)
{
	m_dirName = pFile->m_Fullname;//dirName;

	vector<DirEntry> files;
	GetDir(m_dirName, files);

	for (int i = 0; i < files.GetSize(); i++)
	{
		FileObject* p = new FileObject;
	//	p->AddRef();

		p->m_Name = files[i].name;

		if (*m_dirName == "/")
		{
			p->m_Fullname = p->m_Name;
		}
		else
		{
			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << *m_dirName << "/" << *p->m_Name;
			p->m_Fullname = buffer.DetachToString();
		}
		p->m_Size = files[i].size;
		p->m_FileAttributes = files[i].dwFileAttributes;
		p->m_CreationTime = files[i].ftCreationTime;
		p->m_LastAccessTime = files[i].ftLastAccessTime;
		p->m_LastWriteTime = files[i].ftLastWriteTime;
		m_files.Add(p);
	}
}

unsigned int DirectoryObject::GetCount()
{
	return m_files.GetSize();
}

Object* DirectoryObject::GetItem(unsigned int index)
{
	return m_files[index];
}

#if WIN32

class MPEGFrames : public Object
{
public:

	MediaShow::CVideoSequence* m_videoSequence;

	MPEGFrames(MediaShow::FilterGraph* filterGraph)
	{
	//	LMedia::FilterGraph* filterGraph = ctl->m_Video->get_FilterGraph();
		for (int i = 0; i < filterGraph->m_Filters->m_items.GetSize(); i++)
		{
			MediaShow::IBaseFilter* mediaFilter = filterGraph->m_Filters->m_items[i];
			MediaShow::MPEGVideoDecoder* mpeg = dynamic_cast<MediaShow::MPEGVideoDecoder*>(mediaFilter);
			if (mpeg)
			{
				m_videoSequence = mpeg->m_pVideo->m_p;
			}
		}
	}
};

class ViewOfMPEGFrames : public Control, public IViewOf
{
public:
	Object* get_Viewable()
	{
		return m_pObject;
	}

	virtual void put_Viewable(Object* pViewable)
	{
	}

	MPEGFrames* m_pObject;

	ViewOfMPEGFrames(MPEGFrames* pFrames)
	{
		m_pObject = pFrames;

		TreeControlContainer* ctl2 = new TreeControlContainer;
		ctl2->AddField(WSTR("Display #"));
		ctl2->AddField(WSTR("Encoded #"));
		ctl2->AddField(WSTR("Type"));
		ctl2->AddField(WSTR("Group"));

		/*
		LMedia::FilterGraph* filterGraph = ctl->m_Video->get_FilterGraph();
		for (int i = 0; i < filterGraph->m_Filters->m_items.size(); i++)
		{
			LMedia::ILBaseFilter* mediaFilter = filterGraph->m_Filters->m_items[i];
			LMedia::CLMPEGVideoDecoder* mpeg = dynamic_cast<LMedia::CLMPEGVideoDecoder*>(mediaFilter);
			if (mpeg)
			{
			*/
				int i = 0;
				ASSERT(0);
#if 0
				std::vector<LMedia::Picture*>::iterator pos = m_pObject->m_videoSequence->m_pictures.begin();//GetHeadPosition();
				while (pos != m_pObject->m_videoSequence->m_pictures.end())//for (int i = 0; i < m_pObject->m_videoSequence->m_pictures.GetCount(); i++)
				{
					LMedia::Picture* pic = (LMedia::Picture*)*pos++;//m_pObject->m_videoSequence->m_pictures.GetNext(pos);

					MpegFrameItem* item = new MpegFrameItem;

					item->m_displayNr = new LongLongField(pic->m_temporal_reference_abs);
					item->m_encodedNr = new LongLongField(i);
					item->m_type = new IntegerField(pic->m_picture_coding_type);
					item->m_groupIndex = new IntegerField(pic->m_iGroup);

					ctl2->AddItem(item);
					i++;
				}
#endif

				/*
				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(new Length(200, Length::UnitAbsolute));
				pWindow->put_Height(new Length(200, Length::UnitAbsolute));

			//	ScrollViewer* pScroller = new ScrollViewer;
				{
			//		pScroller->put_Content(ctl);
				}
				pWindow->put_Content(ctl2);//pScroller);
				//	pWindow->put_Content(m_callStackWnd);

				pWindow->put_TitleText(WSTR("Test"));

				m_pWindowContainer->AddChild(pWindow);
				*/

			//}
		//}

				set_VisualTree(ctl2);
	}
};

class FilterGraphObject : public Control, public IViewOf
{
public:
	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	UI::ChildWindowContainer* m_pCanvas;

	MediaShow::FilterGraph* pFilterGraph;

	FilterGraphObject(FileObject* pFile)
	{
		m_pFile = pFile;

		pFilterGraph = new MediaShow::FilterGraph;
		pFilterGraph->LoadURL(m_pFile->m_Fullname->ToStringW());
	}

#if 0
	virtual void handleEvent(System::Event* evt)
	{
		if (evt->get_eventPhase() != System::CAPTURING_PHASE)
		{
			if (*evt->get_type() == L"mousedown")
			{
				evt->stopPropagation();

				MPEGFrames* pObject = new MPEGFrames(pFilterGraph);

				ASSERT(0);
#if 0
				ViewOfMPEGFrames* pView = new ViewOfMPEGFrames(pObject);

				ChildWindow* pWindow = new ChildWindow;
				pWindow->put_Width(Length(200, Length::UnitAbsolute));
				pWindow->put_Height(Length(200, Length::UnitAbsolute));

				pWindow->put_Content(dynamic_cast<Control*>(pView));//pScroller);

				m_m_pWindowContainer->AddChild(pWindow);
#endif
			}
		}
	}
#endif
};

#endif

class TextEditView : public Control, public IViewOf
{
public:
	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	TextEdit* m_edit;

	TextEditView(FileObject* pFile)
	{
		m_pFile = pFile;

		IO::FileByteStream* stream = new IO::FileByteStream(pFile->m_Fullname);
		//stream->AddRef();
		StringA* string;
		ASSERT(0);
#if 0
		string.MakeRoom(stream->GetSize());
#endif
		stream->Read(string->begin(), stream->GetSize());
		//stream->Release();

		m_edit = new TextEdit(string->ToStringW());

		ScrollViewer* pScroller = new ScrollViewer;
		{
			pScroller->set_Content(m_edit);
		}

		set_VisualTree(pScroller);
	}
};

#if WIN32

class Filmstrip : public Control, public IViewOf
{
public:

	class FilmstripContent : public Control, public IScrollContent
	{
	public:
		FilmstripContent(FileObject* pFile)
		{
			m_videoSequence = new MediaShow::MpegVideoSequenceFormat;
			m_videoSequence->Open(new IO::CByteStream(new IO::FileByteStream(pFile->m_Fullname)));

			m_videoSequence->video_sequence();

			pSeq = new MediaShow::CVideoSequence;
			pSeq->m_mpeg_video = m_videoSequence;
			pSeq->Scan();

			pBitmap = new LDraw::Bitmap(m_videoSequence->GetWidth(), m_videoSequence->GetHeight(), LDraw::PixelFormat_t::RGB_24);

			m_bitmaps.SetSize(pSeq->m_displayPictures.GetSize());
		}

		MediaShow::MpegVideoSequenceFormat* m_videoSequence;
		MediaShow::CVideoSequence* pSeq;
		vector<LDraw::Bitmap*> m_bitmaps;

		LDraw::Bitmap* pBitmap;

		virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize)
		{
			return LDraw::SizeD(m_bitmaps.GetSize()*64, 64);
		}

		virtual void OnRender(Graphics* pGraphics)
		{
			//LDraw::Matrix transform = pGraphics->GetTransform();
			//gmMatrix3 t = transform;
			//pGraphics->ScaleTransform(64.0, 1);

			LDraw::RectF clipBounds;
			pGraphics->GetClipBounds(&clipBounds);

			int first = clipBounds.X/64;
			int last = clipBounds.GetRight()/64;

			if (first < 0) first = 0;
			if (last > m_bitmaps.GetSize()-1) last = m_bitmaps.GetSize()-1;

			int x = first*64;
			for (int i = first; i <= last; i++)
			{
				if (m_bitmaps[i] == NULL)
				{
					LDraw::BitmapData bitmapData;
					pBitmap->LockBits(NULL, LDraw::ImageLockModeWrite, &bitmapData);

					MediaShow::LSampleData sampledata;
					sampledata.bitcount = 24;
					sampledata.rowbytes = bitmapData.Stride;
					sampledata.idata = bitmapData.Scan0;
					sampledata.width = bitmapData.Width;
					sampledata.height = bitmapData.Height;

					pSeq->SeekFrame(i);

					pSeq->SetSampleRGBData(pSeq->m_displayPictures[i]->m_decoder, &sampledata);

					pBitmap->UnlockBits(&bitmapData);

					LDraw::Bitmap* pBitmap2 = new LDraw::Bitmap(64, 64, LDraw::PixelFormat_t::RGB_32);
					{
						ASSERT(0);
#if 0
						Graphics* graphics = new Graphics(new LDraw::GraphicsO(pBitmap2));
						graphics->DrawImage(pBitmap, LDraw::RectF(0, 0, 64, 64), 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
#endif
					}
					m_bitmaps[i] = pBitmap2;
				}

				LDraw::Bitmap* pBitmap = m_bitmaps[i];

				pGraphics->DrawImage(pBitmap, x, 0);//LDraw::RectF(x, 0, 1, 64), 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());

				x += 64;
			}
		}

		//IScrollContent
		LDraw::PointD OnSetPos(LDraw::PointD pos)
		{
			pos.X = ((int)pos.X) / 64 * 64;
			return pos;
		}
	};

	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	virtual void set_Viewable(Object* pViewable)
	{
		SetFile(static_cast<FileObject*>(pViewable));
	}

	Filmstrip();

	void SetFile(FileObject* pFile)
	{
		m_pFile = pFile;
		
		pContent = new FilmstripContent(pFile);

		ScrollViewer* pScroller = new ScrollViewer;
		{
			pScroller->set_Content(pContent);
		}

		set_VisualTree(pScroller);

		/*
		for (int frame = 0; frame < 80; frame++)
		{

			m_bitmaps.push_back(pBitmap2);
		}
		*/
	}

	FilmstripContent* pContent;
};

Filmstrip::Filmstrip()
{
	m_pFile = NULL;
}

class ViewOfMedia : public Control, public IViewOf
{
public:
	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	ViewOfMedia(FileObject* pFile)
	{
		m_pFile = pFile;
	//	m_pbitmap = LDraw::Bitmap(m_pFile->m_filename.ToStringW().c_str());

		UI::MediaElement* video = new UI::MediaElement;
		video->set_Source(m_pFile->m_Fullname->ToStringW());

		m_pMediaPlayer = new UI::MediaPlayer(dynamic_cast<MediaShow::IMediaSeeking*>(video->get_FilterGraph()), video);

		set_VisualTree(m_pMediaPlayer);
	}

	MediaPlayer* m_pMediaPlayer;
};

#endif

/*
class ViewOfViewOfMedia : public Control, public IViewOf
{
public:
	ViewOfMedia* m_pView;

	virtual Object* get_Viewable()
	{
		return m_pView;
	}

	ViewOfViewOfMedia(ViewOfMedia* pView)
	{
		m_pView = pView;
	}

	virtual void OnRender(
};
*/

class ViewOfBitmap : public Control, public IViewOf
{
public:
	FileObject* m_pFile;

	virtual Object* get_Viewable()
	{
		return m_pFile;
	}

	ViewOfBitmap(FileObject* pFile)
	{
		m_pFile = pFile;
		Imaging::BitmapLoader* loader = new Imaging::BitmapLoader;
		loader->Load(m_pFile->get_Name());
		m_bitmap = loader->GetBitmap();
	}

	LDraw::Bitmap* m_bitmap;

	virtual void OnRender(Graphics* pGraphics)
	{
//			m_lock.Lock();
		if (m_bitmap != NULL)
		{
			pGraphics->DrawImage(m_bitmap, LDraw::RectF(0, 0, m_computedSize.Width, m_computedSize.Height), 0, 0, m_bitmap->GetWidth(), m_bitmap->GetHeight());
		}
//			m_lock.Unlock();
	}
};

class Group : public System::Object
{
public:
	map<StringA*, Group*, Ref_Less<StringA> > m_items;
};


/*
class TreeItemEx : public TreeItem
{
};
*/



namespace LDraw
{
DrawExt FontFamilyCollection* GetSystemFonts();
}

EditView::EditView(System::Property* pProperty, System::Object* itemVisual)
{
	m_pProperty = pProperty;
	m_itemVisual = itemVisual;

	m_edit = new UI::TextEdit;

	set_VisualTree(m_edit);
}

#if 0
void EditView::handleEvent(System::Event* evt)
{
	//ASSERT(0);

	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"changed")
		{
			StringW* str = static_cast<UI::TextEdit*>(m_edit)->get_Text();

			Type* pType = m_pProperty->get_SetType();

			uint8 data[256];
			unsigned size;

			switch (pType->get_Kind())
			{
			case type_pointer:
				{
					if (pType->GetPointerTo()->get_Kind() == type_class)
					{
						Type* pType2 = pType->GetPointerTo();
						
						if (pType2 == typeid(UI::Length).GetType())
						{
							double value = getfnumber(str->c_str());
							
							*(UI::Length**)data = new UI::Length(value);
							size = sizeof(UI::Length*);
						}
					}
					else
						ASSERT(0);
				}
				break;

			case type_float:
				{
					float value = getfnumber(str->c_str());
					
					*(float*)data = value;
					size = 4;
				}
				break;
				
			case type_double:
				{
					double value = getfnumber(str->c_str());
					
					*(double*)data = value;
					size = 8;
				}
				break;

			case type_int:
			case type_unsigned_int:
			case type_long_int:
			case type_unsigned_long_int:
				{
					int value = str2int(str->c_str());
					
					*(int*)data = value;
					size = 4;
				}
				break;
				
			default:
				ASSERT(0);
			}

			ClassType* pClassType = m_itemVisual->GetType();

			pClassType->m_pDispatch->void_Invoke(m_itemVisual, m_pProperty->get_SetMethod(), data, size);

#if 0
			void *_this = __RTDynamicCast(m_itemVisual, 0, (void*)&typeid(m_itemVisual), (void*)m_pProperty->put_method->GetTypeInfo(), 0);

			StringA* str_type = pType->ToString();
			pType = pType->GetType();

			DWORD func;
			if (m_pProperty->put_method->m_decl->m_offset != -1)
			{
				void* vtable = *(void**)_this;
				func = *(DWORD*)((uint8*)vtable + m_pProperty->put_method->m_decl->m_offset);
			}
			else
			{
				func = m_pProperty->put_method->m_func;
			}

			evt->stopPropagation();
			if (pType->m_type == type_double)
			{
				StringW* str = static_cast<UI::TextEdit*>(m_edit)->get_Text();
				double value = getfnumber(str->c_str());
				long v0 = (*(__int64*)&value) >> 32;
				long v1 = (*(__int64*)&value) & 0xFFFFFFFF;

				__asm
				{
					push ecx
					mov ecx,_this
					push v0
					push v1
					call func
					pop ecx
				}
			}
			else if (pType->m_type == type_float)
			{
				StringW str = static_cast<UI::TextEdit*>(m_edit)->get_Text();
				float value = getfnumber(str->c_str());
				long v0 = *(long*)&value;

				__asm
				{
					push ecx
					mov ecx,_this
					push v0
					call func
					pop ecx
				}
			}
			else if (pType->m_type == type_long_int ||
						pType->m_type == type_unsigned_long_int ||
						pType->m_type == type_int ||
						pType->m_type == type_unsigned_int)
			{
				StringW* str = static_cast<UI::TextEdit*>(m_edit)->get_Text();
				long value = str2int(str->c_str());

				__asm
				{
					push ecx
					mov ecx,_this
					push value
					call func
					pop ecx
				}
			}
			else if (pType->m_type == type_class)
			{
				int sz = pType->get_sizeof();

				if (str_type == "class UI::Length")
				{
					StringW* str = static_cast<UI::TextEdit*>(m_edit)->get_Text();
					double value = getfnumber(str->c_str());

					UI::Length* length = new UI::Length(value);
					void* object = &length;

					/*
					if (false)
					{
						reinterpret_cast<UI::UIElement*>(_this)->put_Height(length);
					}
					*/

					__asm
					{
						push ecx
						push esi
						push edi

						mov   ecx, sz       // get size of buffer
						mov   esi, object     // get buffer
						sub   esp, ecx      // allocate stack space
						mov   edi, esp      // start of destination stack frame
						shr   ecx, 2        // make it dwords
						rep   movsd         // copy params to real stack

						mov ecx,_this
						call func

						pop edi
						pop esi
						pop ecx
					}

					length.Detach();
				}
				else if (*str_type == "class StringW")
				{
					StringW* str = static_cast<UI::TextEdit*>(m_edit)->get_Text();

					//UI::Length length(value);
					void* object = &str;

					/*
					if (false)
					{
						reinterpret_cast<UI::UIElement*>(_this)->put_Height(length);
					}
					*/
					__asm
					{
						push ecx
						push esi
						push edi

						mov   ecx, sz       // get size of buffer
						mov   esi, object     // get buffer
						sub   esp, ecx      // allocate stack space
						mov   edi, esp      // start of destination stack frame
						shr   ecx, 2        // make it dwords
						rep   movsd         // copy params to real stack

						mov ecx,_this
						call func

						pop edi
						pop esi
						pop ecx
					}

					str.Detach();
				}
			}
#endif
		}
	}
}
#endif

EnumView::EnumView(System::Property* pProperty, System::Object* itemVisual)
{
	m_pProperty = pProperty;
	m_itemVisual = itemVisual;

	ASSERT(0);
#if 0
	m_menu = new UI::MenuItem(new UI::TextString(WSTR("")));
#endif

	set_VisualTree(m_menu);
}

#if 0
void EnumView::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"command")
		{
			evt->stopPropagation();

			CommandInvokeEvent* cmdEvt = static_cast<CommandInvokeEvent*>(evt);
			long param = cmdEvt->get_Command();

#if 0
			void *_this = __RTDynamicCast(m_itemVisual, 0, (void*)&typeid(m_itemVisual), (void*)m_pProperty->put_method->GetTypeInfo(), 0);

			System::Type* pType = m_pProperty->put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
			StringA str_type = pType->ToString();
			pType = pType->GetType();

			DWORD func;
			if (m_pProperty->put_method->m_decl->m_offset != -1)
			{
				void* vtable = *(void**)_this;
				func = *(DWORD*)((uint8*)vtable + m_pProperty->put_method->m_decl->m_offset);
			}
			else
			{
				func = m_pProperty->put_method->m_func;
			}

			__asm
			{
				push ecx
				mov ecx,_this
				push param
				call func
				pop ecx
			}
#endif
		}
	}
}
#endif

TwoViews CreateView(Property* pProperty, Object* obj, UI::TreeControl* tree)
{
	TwoViews twoViews;
#if WIN32
	Type* pReturnType = pProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
	pReturnType = pReturnType->GetStripped();

	ASSERT(0);
	void*_this = NULL;//__RTDynamicCast(obj, 0, (void*)&typeid(obj), (void*)pProperty->get_method->GetTypeInfo(), 0);

	ULONG_PTR func;
	if (pProperty->get_method->m_decl->m_offset != -1)
	{
		void* vtable = *(void**)_this;
		func = *(ULONG_PTR*)((uint8*)vtable + pProperty->get_method->m_decl->m_offset);
	}
	else
	{
		func = pProperty->get_method->m_func;
	}
	
	if (func == NULL)
		return twoViews;
	
	//StringA* str_returnType = pReturnType->GetType()->ToString();

	switch (pReturnType->get_Kind())
	{
		case type_int:
		case type_unsigned_int:
		case type_long_int:
		case type_unsigned_long_int:
		{
			EditView* pView = new EditView(pProperty, obj);
			long _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				mov _result,eax
				pop ecx
			}

			WCHAR buf[64];
			swprintf_s(buf, L"%d", _result);
			pView->m_edit->set_Text(new StringW(string_copy(buf)));
			//row->AppendColumnCell(visual);
			twoViews.smallView = pView;
		}
		break;

		case type_long_long:
		{
			long _result0;
			long _result1;

			__asm
			{
				push eax
				push edx
				push ecx
				mov ecx,_this
				call func
				mov _result0,eax
				mov _result1,edx
				pop ecx
				pop edx
				pop eax
			}

			EditView* pView = new EditView(pProperty, obj);

			LONGLONG result64 = _result0 | (LONGLONG)_result1<<32;
			WCHAR buf[64];
#if WIN32
			swprintf_s(buf, L"%I64d", result64);
#else
			std::swprintf(buf, L"%uld", _result0);
#endif
			//if (pProperty->put_decl)
			{
				pView->m_edit->set_Text(new StringW(string_copy(buf)));

				twoViews.smallView = pView;
			}
			/*
			else
			{
				static_cast<UI::TextString*>(visual)->put_TextContent(buf);
			}
			*/
		}
		break;

		case type_enum:
		{
			EnumView* pView = new EnumView(pProperty, obj);
			//UI::CLXUIMenuElement* pMenu = new UI::CLXUIMenuElement(new UI::TextString(WSTR("")));

			EnumType* pEnum = (EnumType*)pProperty->get_method->m_decl->m_pType->GetFunction()->m_pReturnType;

			for (int i = 0; i < pEnum->m_deflist.GetSize(); i++)
			{
				EnumDef& enumDef = pEnum->m_deflist[i];
				ASSERT(0);
#if 0
				pView->m_menu->AddItem(new UI::TextString(enumDef.m_name->ToStringW()), enumDef.m_value);
#endif
			}

			twoViews.smallView = pView;

			long _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				mov _result,eax
				pop ecx
			}

		//	WCHAR buf[64];
		//	swprintf(buf, L"%d", _result);
		//	static_cast<UI::CLXUIMenuPopupElement*>(visual)->put_Text(buf);
#if 0
			row->AppendColumnCell(visual);
#endif
		}
		break;

		case type_double:
		{
			EditView* pView = new EditView(pProperty, obj);
			double _result;

			__asm
			{
				push ecx
				mov ecx,_this
				call func
				fstp qword ptr [_result]
				pop ecx
			}

			WCHAR buf[64];
			swprintf_s(buf, L"%g", _result);
			pView->m_edit->set_Text(new StringW(string_copy(buf)));
			//row->AppendColumnCell(visual);
			twoViews.smallView = pView;
		}
		break;

		case type_class:
		{
			/*
			if (false)//str_returnType == "class UI::Length")
			{
				Length length = ((UI::UIElement*)_this)->get_Height();
				length.get_Value();
			}
			else
			*/
			{
				uint8* object = new uint8[pReturnType->get_sizeof()];

				__asm
				{
					push ecx
					mov ecx,_this
					push object
					call func
					pop ecx
				}

				//StringA* name = pReturnType->GetClass()->m_qname;
				if (pReturnType->GetClass()->GetType() == typeid(WIN_FILETIME).GetType())
				{
					MSWindows::SYSTEMTIME systime;
					MSWindows::FileTimeToSystemTime((MSWindows::FILETIME*)object, &systime);

					WCHAR buf[64];
					swprintf_s(buf, L"%d.%d.%d", systime.wDay, systime.wMonth, systime.wYear);

					EditView* pView = new EditView(pProperty, obj);
					//visual->addEventListener(WSTR("changed"), pProperty, false);
					pView->m_edit->set_Text(new StringW(string_copy(buf)));

					twoViews.smallView = pView;
				}
#if 0
				else if (pReturnType->GetClass()->GetType() == typeid(UI::Length).GetType())
				{
					UI::Length* pLength = (UI::Length*)object;
					WCHAR buf[64];
					if (pLength != NULL)
					{
						double value = pLength->get_Value();

						if (pLength->get_UnitType() == UI::LengthUnits::Percentage)
							std::swprintf(buf, L"%g%%", value);
						else
							std::swprintf(buf, L"%g", value);
					}
					else
					{
						buf[0] = 0;
					}

					EditView* pView = new EditView(pProperty, obj);
					//visual->addEventListener(WSTR("changed"), pProperty, false);
					pView->m_edit->set_Text(new StringW(string_copy(buf)));

					twoViews.smallView = pView;
					//row->AppendColumnCell(visual);
				}
#endif
				else if (pReturnType->GetClass()->GetType() == typeid(System::StringW).GetType())
				{
					StringW* pString = (StringW*)object;

					EditView* pView = new EditView(pProperty, obj);
					//visual->addEventListener(WSTR("changed"), pProperty, false);
					pView->m_edit->set_Text(pString);
					//row->AppendColumnCell(visual);
					twoViews.smallView = pView;
				}
				else if (pReturnType->GetClass()->GetType() == typeid(System::StringA).GetType())
				{
					StringA* pString = (StringA*)object;

					EditView* pView = new EditView(pProperty, obj);
					//visual->addEventListener(WSTR("changed"), pProperty, false);
					pView->m_edit->set_Text(pString->ToStringW());
					//row->AppendColumnCell(visual);
					twoViews.smallView = pView;
				}
				else if (pReturnType->GetClass()->GetType() == typeid(UI::Color).GetType())
				{
					UI::Color* pColor = (UI::Color*)object;

					/*
					StringW* pString = (StringW*)object;

					visual = new UI::TextEdit();
					visual->addEventListener(WSTR("changed"), pProperty, false);
					static_cast<UI::TextEdit*>(visual)->put_Text(*pString);
					*/
					RGBSlidersView* pView = new RGBSlidersView;
					pView->m_ctl = new ColorPickerRGB;
					pView->set_VisualTree(pView->m_ctl);

					pView->m_ctl->m_slider[0]->set_pos(pColor->get_R()/255.0);
					pView->m_ctl->m_slider[1]->set_pos(pColor->get_G()/255.0);
					pView->m_ctl->m_slider[2]->set_pos(pColor->get_B()/255.0);

					pView->set_Width(256);
				//	pView->put_Height(256);

					pView->m_ctl->UpdateControls();

					//visual = pColorPicker;
					//visual->addEventListener(WSTR("ValueChange"), pProperty, false);
				//	row->put_Children(visual);
				//	twoViews.largerView = pView;
					twoViews.largerView = pView;
				}

				delete[] object;
			}
		}
		break;

		case type_pointer:
		{
			if (pReturnType->GetPointerTo()->get_Kind() == type_class)
			{
				ClassType* pClassType = pReturnType->GetPointerTo()->GetClass();

				void* vobject;

				__asm
				{
					push eax
					push ecx
					mov ecx,_this
					call func
					mov vobject,eax
					pop ecx
					pop eax
				}

				if (vobject)
				{
					StringA* classname;
					Object* propertyobj;
					//{
#if 0
						void* vtable = *(void**)vobject;
						rti* p3 = ((rti**)vtable)[-1];

						int count = p3->m_classHierarchyDescriptor->count;
						BaseClassDescriptor** table = p3->m_classHierarchyDescriptor->m_baseClassArray;

						Type_Info* ti = (Type_Info*)table[0]->typedesc;
						classname = ti->name() + strlen("class ");

						propertyobj = (Object*)__RTDynamicCast(vobject, 0, ti, (void*)&typeid(Object), 0);
#endif
						classname = GetType(vobject)->m_qname;
						propertyobj = (Object*)DynamicCast(vobject, GetType(vobject)->GetClass(), typeid(Object).GetType()->GetClass());
					//}
						if (propertyobj)
						{

#if 0
					if (classname == "UI::_Color")
					{
						visual = new ColorPickerRGB;
						row->put_Children(visual);
					}
					else
#endif
#if 0
					if (pClassType == typeid(UI::Length).GetType())
					{
						UI::Length* pLength = (UI::Length*)vobject;
						WCHAR buf[64];
						if (pLength != NULL)
						{
							double value = pLength->get_Value();

							if (pLength->get_UnitType() == UI::LengthUnits::Percentage)
								std::swprintf(buf, L"%g%%", value);
							else
								std::swprintf(buf, L"%g", value);
						}
						else
						{
							buf[0] = 0;
						}

						EditView* pView = new EditView(pProperty, obj);
						//visual->addEventListener(WSTR("changed"), pProperty, false);
						pView->m_edit->set_Text(new StringW(string_copy(buf)));

						twoViews.smallView = pView;
						//row->AppendColumnCell(visual);
					}
					else
#endif
						if (pClassType == typeid(UI::Color).GetType())
					{
						UI::Color* pColor = (UI::Color*)vobject;

						/*
						StringW* pString = (StringW*)object;

						visual = new UI::TextEdit();
						visual->addEventListener(WSTR("changed"), pProperty, false);
						static_cast<UI::TextEdit*>(visual)->put_Text(*pString);
						*/
						RGBSlidersView* pView = new RGBSlidersView;
						pView->m_ctl = new ColorPickerRGB;
						pView->set_VisualTree(pView->m_ctl);

						pView->m_ctl->m_slider[0]->set_pos(pColor->get_R()/255.0);
						pView->m_ctl->m_slider[1]->set_pos(pColor->get_G()/255.0);
						pView->m_ctl->m_slider[2]->set_pos(pColor->get_B()/255.0);

						pView->set_Width(256);
					//	pView->put_Height(256);

						pView->m_ctl->UpdateControls();

						//visual = pColorPicker;
						//visual->addEventListener(WSTR("ValueChange"), pProperty, false);
					//	row->put_Children(visual);
					//	twoViews.largerView = pView;
						twoViews.largerView = pView;
					}
					else if (pClassType == typeid(UI::FontFamily).GetType())
					{
					//	visual = new ComboBox;
					//	row->put_Children(visual);

						LDraw::FontFamilyCollection* obj2 = LDraw::GetSystemFonts();

						/*
						DockPanel* panel = new DockPanel;

						tyfamilymap::const_iterator it = pSystemFonts->Items();
						*/
						ListView* p = new ListView(pProperty, obj);
						ViewOfCollection* pView = new ViewOfCollection();
						pView->set_Viewable(obj2);
						p->set_VisualTree(pView);
						p->m_view = pView;
						twoViews.largerView = p;
					}
					else if (*classname == "Histogram")
					{
						ASSERT(0);
#if 0
						Histogram* hist = dynamic_cast<Histogram*>(propertyobj);
						HistogramView* view = new HistogramView;
						view->m_pHistogram = hist;
						hist->m_views.push_back(view);
						twoViews.largerView = view;
#endif
					}
					else if (false && *classname == "HueSaturate")
					{
						HueSaturate* hue = dynamic_cast<HueSaturate*>(propertyobj);
						HueRotateView* view = new HueRotateView;
						view->m_hue = hue;
						//hist->m_views.push_back(view);
						twoViews.largerView = view;
					}
					else
					if (IObjectCollection* pCollection = dynamic_cast<IObjectCollection*>(propertyobj))//classname == "UI::PointCollection")	// TODO, any collection
					{
						if (false)
						{
							ViewOfCollection2* pView = new ViewOfCollection2(pCollection);
							pView->set_Visibility(Collapsed);
							twoViews.largerView = pView;
						}
						else
						{
						//	visual = new PropertiesTable(pCollection);
							ViewOfCollection* pView = new ViewOfCollection();
							pView->set_Viewable(propertyobj);
							twoViews.largerView = pView;
						//	twoViews.smallView = pView;
							//row->put_Children(visual);
						}
					}
					else
					{
					//	ASSERT(0);
						Properties* pView = new Properties;
						pView->set_Visibility(Collapsed);

						pView->CreateRows(propertyobj, tree);

						{
							UI::Border* pBorder = new UI::Border;
							UI::TextString* pText = new UI::TextString(classname->ToStringW());
							pBorder->set_Background(new SolidColorBrush(Color::FromRgb(236, 233, 216)));
							pBorder->set_Child(pText);

							twoViews.smallView = pBorder;
						}

						twoViews.largerView = pView;
					}
						}
				}
			}
		}
		break;
	}
#else
	ASSERT(0);
#endif

	return twoViews;
}

/*
class Properties2 : public IViewOf, public UI::TreeItemChildren
{
public:
};
*/




/////////////////////////////////////////////////////////////////
// DataTemplate

//void* CreateElement(const cpp::_Type* pType, XmlData::Node* node, const cpp::_Type** pReturnType);



class TestObjectKK :public System::Object
{
public:
	TestObjectKK();
	long value;

	long get_Value();
};

TestObjectKK::TestObjectKK()
{
	value = 10;
}

long TestObjectKK::get_Value()
{
	return value;
}

class ApplyTemplate : public Control
{
public:
	ApplyTemplate();

	Object* get_Object();
	void put_Object(Object* object);

	DataTemplate* get_Template();
	void put_Template(DataTemplate* templaten);

	Object* m_object;
	DataTemplate* m_templaten;
};

ApplyTemplate::ApplyTemplate()
{
	m_object = NULL;
	m_templaten = NULL;
}

Object* ApplyTemplate::get_Object()
{
	return m_object;
}
void ApplyTemplate::put_Object(Object* object)
{
	m_object = object;
}

DataTemplate* ApplyTemplate::get_Template()
{
	return m_templaten;
}

void ApplyTemplate::put_Template(DataTemplate* templaten)
{
	ASSERT(0);
#if 0 
	m_templaten = templaten;
	if (m_object)
	{
		Type* pRealType;
		UI::UIElement* visual = (UI::UIElement*)DynamicCast(m_templaten->m_RootNode->Create(m_object, &pRealType), m_templaten->m_RootNode->m_pType, typeid(UI::UIElement).GetType());
		set_VisualTree(visual);
	}
#endif
}


#if 0
float ctrlpoints[4][3] =
{
	{-4*20, -4*20, 0*20}, {-2*20, 4*20, 0*20},
	{2*20, -4*20, 0*20 }, {4*20, 4*20, 0*20}
};

float ctrlpoints2[4][4][3] =
{
	{{-1.5*20, -1.5*20, 0*5}, {-0.5*20, -1.5*20, 0*5}, {0.5*20, -1.5*20, 2*5 }, {1.5*20, -1.5*20, 8*5}},
	{{-1.5*20, -0.5*20, 0*5}, {-0.5*20, -0.5*20, 0*5}, {0.5*20, -0.5*20, 2*5}, {1.5*20, -0.5*20, 8*5}},
	{{-1.5*20, 0.5*20, 0*5}, {-0.5*20, 0.5*20, 0*5}, {0.5*20, 0.5*20, 2*5}, {1.5*20, 0.5*20, 8*5}},
	{{-1.5*20, 1.5*20, 0*5}, {-0.5*20, 1.5*20, 0*5}, {0.5*20, 1.5*20, 2*5}, {1.5*20, 1.5*20, 8*5}}

	/*
	{{-1.5*20, -1.5*20, 4*5}, {-0.5*20, -1.5*20, 2*5}, {0.5*20, -1.5*20, -1*5 }, {1.5*20, -1.5*20, 2*5}},
	{{-1.5*20, -0.5*20, 1*5}, {-0.5*20, -0.5*20, 3*5}, {0.5*20, -0.5*20, 0*5}, {1.5*20, -0.5*20, -1*5}},
	{{-1.5*20, 0.5*20, 4*5}, {-0.5*20, 0.5*20, 0*5}, {0.5*20, 0.5*20, 3*5}, {1.5*20, 0.5*20, 4*5}},
	{{-1.5*20, 1.5*20, -2*5}, {-0.5*20, 1.5*20, -2*5}, {0.5*20, 1.5*20, 0*5}, {1.5*20, 1.5*20, -1*5}}
	*/
};
#endif

void grid_shader(LDraw::ShaderData* data)
{
	float x = (data->varying.gl_TexCoord[0][0] / data->varying.gl_TexCoord[0][3]);
	float y = (data->varying.gl_TexCoord[0][1] / data->varying.gl_TexCoord[0][3]);

	data->gl_FragColor[0] = -0.5 + data->varying.gl_Color[0] + (int(x*5) + int(y*5) & 1? 1: 0);
	data->gl_FragColor[1] = -0.5 + data->varying.gl_Color[1] + (int(x*5) + int(y*5) & 1? 1: 0);
	data->gl_FragColor[2] = -0.5 + data->varying.gl_Color[2] + (int(x*5) + int(y*5) & 1? 1: 0);//data->varying.gl_TexCoord[0][2] / data->varying.gl_TexCoord[0][3];
}

/*
double _z(double z, double c)
{
	if (fabs(z) > 1) return z;
	double nz = _z(z,c);
	nz = nz * nz;
	z= nz + c;
	return z;
}
*/

double IntNoise(long x)
{
    x = (x<<13) ^ x;
   return (1.0-((x*(x*x*15731+789221)+1376312589)& 0x7fffffff)/1073741824.0);
}

void myshader(LDraw::ShaderData* data)
{
//	float x = acos(data->varying.gl_TexCoord[0][0] / data->varying.gl_TexCoord[0][3]);
//	float y = asin(data->varying.gl_TexCoord[0][1] / data->varying.gl_TexCoord[0][3]);

	float x = data->varying.gl_TexCoord[0][0] / data->varying.gl_TexCoord[0][3];
	float y = data->varying.gl_TexCoord[0][1] / data->varying.gl_TexCoord[0][3];

//	x = (int(x * 1000) % 500)/500.0;
//	y = (int(y * 1000) % 500)/500.0;
	x *= 8;
	y *= 8;
#if 0

/*
	x *= 4;
	y *= 4;
	x -= 1;
	y -= 1;

	float d = sqrt(x*x + y*y);
	*/

//	if (x < 5)
//		x = cos((10-x) * sin(x * y)) * 0.8;
	/*
	else if (y < 5)
		x = cos(x * (1 - sin(x * y))) * 0.8;
		*/
//	else
	/*
	float d = cos(x * sin(x * y)) * 0.8;

	d += cos((8-y) * sin(y * (8-x))) * 0.8;
*/
	float d = sin(cos(x)*y);

	d += cos(sin(y)*x);

	d += (8-x) * y / 8.0;
#endif
//	double d = _z(0, x*y);

//	srand(x*20 + y*20);
//	d += ;

//	double d = sin(cos(sin(cos(cos(x*M_PI) + sin(y*M_PI) + x*9) + y*3) - y*5) - x*10);
	double d = sin((cos(x*5) + cos(y*5)) * 3);

#if 0
	double d = 0;
	{
     double      zr = 0.0;
      double      zi = 0.0;
      double      cr = 0 + x * 2 - 1;

      double      ci = y * 2 - 1;//TOP + y * (BOTTOM - TOP) / SIZE;
      double      rsquared = zr * zr;
      double      isquared = zi * zi;

            for (int count = 0; rsquared + isquared <= 4.0
                            && count < 6; count++)
            {
                zi = zr * zi * 2;
                zi += ci;

                zr = rsquared - isquared;
                zr += cr;

                rsquared = zr * zr;
                isquared = zi * zi;
            }
	d = rsquared * isquared;
}
#endif

	data->gl_FragColor[0] = data->varying.gl_Color[0] + d * 0.9;
	data->gl_FragColor[1] = data->varying.gl_Color[1] + d;
	data->gl_FragColor[2] = data->varying.gl_Color[2] + d * 0.7;
}

/*
class Geometry
{
public:
	Geometry()
	{
		m_points.push_back(gmVector3f(-90, 90, -60));
		m_points.push_back(gmVector3f(-90, 0, -90));
		m_points.push_back(gmVector3f(90, 0, -60));
	}

	std::vector<gmVector3f> m_points;
};
*/

#include "View3D.h"

double Noise1(int x)
{
	x = (x<<13) ^ x;
	return ( 1.0 - ( (x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);    
}

double Noise1(int x, int y)
{
	int n = x + y * 57;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double Noise2(int x, int y)
{
	int n = x + y * 4397 ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 4373 + 78283 ) + 12055513 ) & 0x7fffffff) / 1073741824.0);
}

double Noise3(int x, int y)
{
	int n = x + y * 4817 ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 4831  + 82651 ) + 16111493 ) & 0x7fffffff) / 1073741824.0);
}
 
double Noise4(int x, int y)
{
	int n = x + y * 4493  ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 7853   + 9887  ) + 10151  ) & 0x7fffffff) / 1073741824.0);
}

double Noise1(int x, int y, int z)
{
	int n = x + y * 57 + z*70199 ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double Noise2(int x, int y, int z)
{
	int n = x + y * 4397 + z*800143 ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 4373 + 78283 ) + 12055513 ) & 0x7fffffff) / 1073741824.0);
}

double Noise3(int x, int y, int z)
{
	int n = x + y * 4817 + z *712961 ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 4831  + 82651 ) + 16111493 ) & 0x7fffffff) / 1073741824.0);
}
 
double Noise4(int x, int y, int z)
{
	int n = x + y * 4493 + z*6779  ;
	n = (n<<13) ^ n;
	return ( 1.0 - ( (n * (n * n * 7853   + 9887  ) + 10151  ) & 0x7fffffff) / 1073741824.0);
}

double Interpolate(double v0, double v1, double t)
{
	if (true)
	{
		double ft = t * 3.1415927;
		double f = (1 - cos(ft)) * .5;

		return  v0*(1-f) + v1*f;
	}
	else
	{
		return v0 + (v1 - v0)*t;
	}
}

class PerlinNoise2D
{
public:

double (*Noise)(int x, int y);

double SmoothNoise_1(int x, int y)
{
//	return Noise(x, y);

	double corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
	double sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8;
	double center  =  Noise(x, y) / 4;
	return corners + sides + center;
}

double InterpolatedNoise_1(double x, double y)
{
	int integer_X    = floor(x);
	double fractional_X = x - integer_X;
	
	int integer_Y    = floor(y);
	double fractional_Y = y - integer_Y;
	
	double v1 = SmoothNoise_1(integer_X,     integer_Y);
	double v2 = SmoothNoise_1(integer_X + 1, integer_Y);
	double v3 = SmoothNoise_1(integer_X,     integer_Y + 1);
	double v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);
	
	double i1 = Interpolate(v1, v2, fractional_X);
	double i2 = Interpolate(v3, v4, fractional_X);
	
	return Interpolate(i1 , i2 , fractional_Y);
}

};

float PerlinNoise_2D(float x, float y)
{
	const int Number_Of_Octaves = 4;
//	const double persistence = 0.5;
	const double persistence = 1;
	
	double total = 0;
	double p = persistence;
	int n = Number_Of_Octaves - 1;

	PerlinNoise2D perlin;

	for (int i = 0; i <= n; i++)
	{
		double frequency = 1<<i;
		double amplitude = pow(p, i);
		switch (i)
		{
		case 0:
			perlin.Noise = Noise1;
			break;
		case 1:
			perlin.Noise = Noise2;
			break;
		case 2:
			perlin.Noise = Noise3;
			break;
		case 3:
			perlin.Noise = Noise4;
			break;
		}
		
		total = total + perlin.InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;
	}
	
   return total;
}

class PerlinNoise3D
{
public:

double (*Noise)(int x, int y, int z);

double SmoothNoise_1(int x, int y, int z)
{
	return Noise(x, y, z);

	/*
	double corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
	double sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +Noise(x, y-1)  +Noise(x, y+1) ) /  8;
	double center  =  Noise(x, y) / 4;
	return corners + sides + center;
	*/
}

double InterpolatedNoise_1(double x, double y, double z)
{
	int integer_X    = floor(x);
	double fractional_X = x - integer_X;
	
	int integer_Y    = floor(y);
	double fractional_Y = y - integer_Y;

	int integer_Z    = floor(z);
	double fractional_Z = z - integer_Z;
	
	double v1 = SmoothNoise_1(integer_X,     integer_Y,		integer_Z);
	double v2 = SmoothNoise_1(integer_X + 1, integer_Y,		integer_Z);
	double v3 = SmoothNoise_1(integer_X,     integer_Y + 1,	integer_Z);
	double v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1,	integer_Z);

	double v1z = SmoothNoise_1(integer_X,     integer_Y,		integer_Z + 1);
	double v2z = SmoothNoise_1(integer_X + 1, integer_Y,		integer_Z + 1);
	double v3z = SmoothNoise_1(integer_X,     integer_Y + 1, integer_Z + 1);
	double v4z = SmoothNoise_1(integer_X + 1, integer_Y + 1, integer_Z + 1);

	double i1 = Interpolate(v1, v2, fractional_X);
	double i2 = Interpolate(v3, v4, fractional_X);

	double i1z = Interpolate(v1z, v2z, fractional_X);
	double i2z = Interpolate(v3z, v4z, fractional_X);

	double i1y = Interpolate(i1 , i2, fractional_Y);
	double i2y = Interpolate(i1z , i2z, fractional_Y);

	return Interpolate(i1y , i2y, fractional_Z);
}

};

float PerlinNoise_3D(float x, float y, float z)
{
	const int Number_Of_Octaves = 2;
//	const double persistence = 0.5;
	const double persistence = 1;
	
	PerlinNoise3D perlin;

	double total = 0;
	double p = persistence;
	int n = Number_Of_Octaves - 1;

	for (int i = 0; i <= n; i++)
	{
		double frequency = 1<<(i);
		double amplitude = pow(p, i);
		switch (i)
		{
		case 0:
			perlin.Noise = Noise1;
			break;
		case 1:
			perlin.Noise = Noise2;
			break;
		case 2:
			perlin.Noise = Noise3;
			break;
		case 3:
			perlin.Noise = Noise4;
			break;
		}
		
		total = total + perlin.InterpolatedNoise_1(x * frequency, y * frequency, z * frequency) * amplitude;
	}
	
   return total;
}

/*
int getchar()
{
	char c;
	stream->Read(&c, 1);

	return c;
}
*/

/*
LFCEXT double getfrac(const OLECHAR** s)
{
	double dig = 0.1;
	double val = 0;

	const OLECHAR* p = *s;

	while (*p && iswdigit(*p))
	{
		WCHAR c = *p;
		val += dig * (c - L'0');

		dig = 0.1 * dig;

		p++;
	}

	*s = p;

	return val;
}
*/

/*
enum XTokenType
{
	TOKEN_NAME = 1,
	TOKEN_STRING,
	TOKEN_INTEGER,
//	TOKEN_FLOAT,
	TOKEN_GUID,

	TOKEN_OBRACE = 10,
	TOKEN_CBRACE,
	TOKEN_OPAREN,
	TOKEN_CPAREN,
	TOKEN_OBRACKET,
	TOKEN_CBRACKET,
	TOKEN_OANGLE,
	TOKEN_CANGLE,
	TOKEN_COMMA,
	TOKEN_DOT,
	TOKEN_SEMICOLON,
	TOKEN_WORD,
	TOKEN_DWORD,
	TOKEN_FLOAT,
	TOKEN_DOUBLE,
	TOKEN_CHAR,
	TOKEN_UCHAR,
	TOKEN_SWORD,
	TOKEN_SDWORD,
	TOKEN_LPSTR,
	TOKEN_UNICODE,
	TOKEN_CSTRING,
	TOKEN_ARRAY,
	TOKEN_TEMPLATE,
};
*/

/*
class Token
{
public:
	TokenType m_type;

	StringA m_name;
	union
	{
		int m_integer;
		float m_float;
	};
};
*/

#if 0
class XParser
{

public:

Token m_curtok;
const char* m_buffer;
const char* m_p;
ULONG m_size;

void eat(int token)
{
	if (m_curtok.m_type != token)
	{
		throw -1;
	}
	nexttoken();
}

StringA name()
{
	if (m_curtok.m_type == TOKEN_NAME)
	{
		StringA name = m_curtok.m_name;
		nexttoken();
		return name;
	}
	else
		throw -1;
}

void nexttoken()
{
	const char* &p = m_p;

	int c = *p;

	Token& token = m_curtok;
	token.m_name = StringA();

	if (isalpha(c) || c == '_')
	{
		token.m_name += c;
		p++;

		c = *p;
		while (isalnum(c) || c == '_')
		{
			p++;
			token.m_name += c;
			c = *p;
		}

		if (token.m_name == "template")
		{
			token.m_type = TOKEN_TEMPLATE;
		}
		else if (token.m_name == "CHAR")
		{
			token.m_type = TOKEN_CHAR;
		}
		else if (token.m_name == "WORD")
		{
			token.m_type = TOKEN_WORD;
		}
		else if (token.m_name == "DWORD")
		{
			token.m_type = TOKEN_DWORD;
		}
		else if (token.m_name == "SWORD")
		{
			token.m_type = TOKEN_SWORD;
		}
		else if (token.m_name == "SDWORD")
		{
			token.m_type = TOKEN_SDWORD;
		}
		else if (token.m_name == "FLOAT")
		{
			token.m_type = TOKEN_DOUBLE;
		}
		else if (token.m_name == "DOUBLE")
		{
			token.m_type = TOKEN_FLOAT;
		}
		else if (token.m_name == "array")
		{
			token.m_type = TOKEN_ARRAY;
		}
		else
		{
			token.m_type = TOKEN_NAME;
		}
	}
	else if (c == '{')
	{
		token.m_type = TOKEN_OBRACE;
		p++;
	}
	else if (c == '}')
	{
		token.m_type = TOKEN_CBRACE;
		p++;
	}
	else if (c == '[')
	{
		token.m_type = TOKEN_OBRACKET;
		p++;
	}
	else if (c == ']')
	{
		token.m_type = TOKEN_CBRACKET;
		p++;
	}
	else if (c == '<')
	{
		// TODO
		token.m_type = TOKEN_OANGLE;
		p++;
		while (*p != '>')
		{
			p++;
		}
		p++;
	}
	else if (c == '>')
	{
		//token.m_type = tok_cbrace;
	}
	else if (c == ';')
	{
		token.m_type = TOKEN_SEMICOLON;
		p++;
	}
	else if (c == ',')
	{
		token.m_type = TOKEN_COMMA;
		p++;
	}
	else if (c == '.')
	{
		token.m_type = TOKEN_DOT;
		p++;
	}
	else if (isdigit(c) || c == '-')
	{
	// get sign
		int sign = 1;

		if ((c == '-') || (c == L'+'))
		{
			if (c == L'-') sign = -1;
			p++;
		}

	// get number
		long integer = _getnumber(&p);

	// get fraction
		double fraction;
		if (*p == '.')
		{
			p++;
			fraction = getfrac(&p);

			int exp = 0;
			/*
		// get exp
			exp = lookexp(&p);
			*/

			token.m_type = TOKEN_FLOAT;
			double value = makeflt(integer, fraction, exp);
			if (sign == -1) value = -value;

			token.m_float = value;
		}
		else
		{
			token.m_type = TOKEN_INTEGER;
			token.m_integer = integer;

	//		fraction = 0;

		//	double specifiedValue = makeflt(integer, fraction, exp);
		//	if (sign == -1) specifiedValue = -specifiedValue;
		}
	}
	else
		throw -1;

	while (isspace(*p))
	{
		p++;
	}
}

void array_data_type()
{
	if (m_curtok.m_type == TOKEN_NAME)
	{
		nexttoken();
	}
	else if (m_curtok.m_type == TOKEN_WORD ||
				m_curtok.m_type == TOKEN_DWORD ||
				m_curtok.m_type == TOKEN_FLOAT ||
				m_curtok.m_type == TOKEN_DOUBLE ||
				m_curtok.m_type == TOKEN_CHAR ||
				m_curtok.m_type == TOKEN_UCHAR ||
				m_curtok.m_type == TOKEN_SWORD ||
				m_curtok.m_type == TOKEN_SDWORD ||
				m_curtok.m_type == TOKEN_LPSTR ||
				m_curtok.m_type == TOKEN_UNICODE ||
				m_curtok.m_type == TOKEN_CSTRING)
	{
		nexttoken();
	}
	else
		throw -1;
}

void dimension()
{
	eat(TOKEN_OBRACKET);

	// number
	if (m_curtok.m_type == TOKEN_INTEGER)
	{
	}
	else if (m_curtok.m_type == TOKEN_NAME)
	{
	}
	else
		throw -1;

	nexttoken();

	eat(TOKEN_CBRACKET);
}

void template_members()
{
	if (m_curtok.m_type == TOKEN_ARRAY)
	{
		nexttoken();

		array_data_type();

		name();

		do
		{
			dimension();
		}
		while (m_curtok.m_type == TOKEN_OBRACKET);

		eat(TOKEN_SEMICOLON);
	}
	else if (m_curtok.m_type == TOKEN_NAME)	// reference
	{
		nexttoken();

		if (m_curtok.m_type == TOKEN_NAME)
		{
			nexttoken();
		}

		eat(TOKEN_SEMICOLON);
	}
	else if (m_curtok.m_type == TOKEN_WORD ||
				m_curtok.m_type == TOKEN_DWORD ||
				m_curtok.m_type == TOKEN_FLOAT ||
				m_curtok.m_type == TOKEN_DOUBLE ||
				m_curtok.m_type == TOKEN_CHAR ||
				m_curtok.m_type == TOKEN_UCHAR ||
				m_curtok.m_type == TOKEN_SWORD ||
				m_curtok.m_type == TOKEN_SDWORD ||
				m_curtok.m_type == TOKEN_LPSTR ||
				m_curtok.m_type == TOKEN_UNICODE ||
				m_curtok.m_type == TOKEN_CSTRING)
	{
		// primitive             : primitive_type optional_name TOKEN_SEMICOLON
		nexttoken();
		if (m_curtok.m_type == TOKEN_NAME)
		{
			nexttoken();
		}

		eat(TOKEN_SEMICOLON);
	}
	else
	{
		throw -1;
	}
}

	void template_option_list()
	{
								/*
template_option_list  : template_option_part
                      | template_option_list template_option_part

template_option_part  : name optional_class_id
*/
		while (m_curtok.m_type == TOKEN_NAME)
		{
			nexttoken();

			if (m_curtok.m_type == TOKEN_OANGLE)
			{
				nexttoken();
			}
		}
	}

	void parse()
	{
		while (isspace(*m_p))
		{
			m_p++;
		}

		nexttoken();

		while (m_p - m_buffer < m_size)
		{
			if (m_curtok.m_type == TOKEN_TEMPLATE)
			{
				nexttoken();
				StringA name = m_curtok.m_name;

				nexttoken();
				eat(TOKEN_OBRACE);

				// GUID
				;

				nexttoken();

				if (m_curtok.m_type == TOKEN_OBRACKET)
				{
					nexttoken();

					if (m_curtok.m_type == TOKEN_DOT)
					{
						eat(TOKEN_DOT);
						eat(TOKEN_DOT);
						eat(TOKEN_DOT);
					}
					else
					{
						template_option_list();
					}

					eat(TOKEN_CBRACKET);
				}
				else
				{
					do
					{
						template_members();

						if (m_curtok.m_type == TOKEN_OBRACKET)
						{
							nexttoken();
							if (m_curtok.m_type == TOKEN_DOT)
							{
								eat(TOKEN_DOT);
								eat(TOKEN_DOT);
								eat(TOKEN_DOT);
							}
							else
							{
								template_option_list();
							}

							eat(TOKEN_CBRACKET);
							break;
						}
					}
					while (m_curtok.m_type != TOKEN_CBRACE);
				}

				eat(TOKEN_CBRACE);
			}
			else if (m_curtok.m_type == TOKEN_NAME)
			{
				nexttoken();

				if (m_curtok.m_type == TOKEN_NAME)
				{
					nexttoken();
				}

				eat(TOKEN_OBRACE);
				eat(TOKEN_CBRACE);
			}
			else
			{
				throw -1;
			}
		}
	}
};
#endif


enum AnimationKeyType
{
	Rotation = 0,	// Quaternion
	Scale = 1,
	Translation = 2,
	Matrix = 4,
};

//#include "dvd.h"

template<class key_t, class value_t> void print(int level, red_black_node<key_t, value_t>* x)
{
	TRACE("level %d, x: %d ", level, x->item.first);
	if (x->left) TRACE("left: %d ", ((red_black_node<key_t, value_t>*)x->left)->item.first);
	if (x->right) TRACE("right: %d ", ((red_black_node<key_t, value_t>*)x->right)->item.first);

	TRACE("\n");

	if (x->left) print(level+1, (red_black_node<key_t, value_t>*)x->left);
	if (x->right) print(level+1, (red_black_node<key_t, value_t>*)x->right);
}

}
