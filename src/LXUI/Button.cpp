#include "stdafx.h"
#include "LXUI2.h"
#include "Button.h"

#include "CodeComp/ir.h"

#include "ActionScript.h"

#include "ecmascript_ast.h"

/*
namespace System
{
namespace MSWindows
{
#define STDAPI __stdcall
#define STDAPI_(name) __stdcall name

#define _INC_COMMCTRL
#define SPECSTRINGS_H
#include <uxtheme.h>
}
}
*/

extern "C"
{
namespace System
{
namespace MSWindows
{

DECLSPEC_DLLIMPORT BOOL WINAPI SetViewportOrgEx(
  HDC hdc,  // handle of device context
  int X,    // new x-coordinate of viewport origin
  int Y,    // new y-coordinate of viewport origin
  LPPOINT lpPoint 
            // address of structure receiving original origin
);

}
}
}

namespace System
{
namespace MSWindows
{

#define OPTIONAL

typedef HANDLE HTHEME;

typedef HTHEME  (STDAPICALLTYPE *fOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (STDAPICALLTYPE *fCloseThemeData)(HTHEME hTheme);
typedef HRESULT (STDAPICALLTYPE *fDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, OPTIONAL const RECT *pClipRect);

typedef HRESULT (STDAPICALLTYPE *fGetThemeTextExtent)(HTHEME hTheme,
    HDC hdc,
    int iPartId,
    int iStateId,
    LPCWSTR pszText,
    int iCharCount,
    DWORD dwTextFlags,
    LPCRECT pBoundingRect,
    LPRECT pExtentRect
);

fOpenThemeData uxOpenThemeData;
fCloseThemeData uxCloseThemeData;
fDrawThemeBackground uxDrawThemeBackground;
fGetThemeTextExtent uxGetThemeTextExtent;

/*
fOpenThemeData uxOpenThemeData;
fCloseThemeData uxCloseThemeData;
fDrawThemeBackground uxDrawThemeBackground;
*/

//
//  BUTTONSTYLE class parts and states 
//
#define VSCLASS_BUTTONSTYLE	L"BUTTONSTYLE"
#define VSCLASS_BUTTON	L"BUTTON"

enum BUTTONPARTS {
	BP_PUSHBUTTON = 1,
	BP_RADIOBUTTON = 2,
	BP_CHECKBOX = 3,
	BP_GROUPBOX = 4,
	BP_USERBUTTON = 5,
	BP_COMMANDLINK = 6,
	BP_COMMANDLINKGLYPH = 7,
};

#define BUTTONSTYLEPARTS BUTTONPARTS;

enum PUSHBUTTONSTATES {
	PBS_NORMAL = 1,
	PBS_HOT = 2,
	PBS_PRESSED = 3,
	PBS_DISABLED = 4,
	PBS_DEFAULTED = 5,
	PBS_DEFAULTED_ANIMATING = 6,
};

}
}

namespace System
{

namespace UI
{

MSWindows::HINSTANCE uxThemeDll;

//void ApplyStyle(Style* style, FrameworkElement* element);
//Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType);

__live_object_ptr<Style> ButtonStyle;

class XPThemeCommand : public LDraw::Command
{
public:
	CTOR XPThemeCommand(MSWindows::HTHEME hTheme, MSWindows::RECT rect);

	MSWindows::HTHEME m_hTheme;
	MSWindows::RECT m_rect;

	virtual void Render(LDraw::Graphics2D* pGraphics);
};

XPThemeCommand::XPThemeCommand(MSWindows::HTHEME hTheme, MSWindows::RECT rect) : m_hTheme(hTheme), m_rect(rect)
{
}

void Load_uxThemeDll()
{
	if (uxThemeDll == NULL)
	{
		uxThemeDll = MSWindows::LoadLibraryA("uxtheme.dll");

		MSWindows::uxOpenThemeData = (MSWindows::fOpenThemeData)MSWindows::GetProcAddress(uxThemeDll, "OpenThemeData");
		MSWindows::uxDrawThemeBackground = (MSWindows::fDrawThemeBackground)MSWindows::GetProcAddress(uxThemeDll, "DrawThemeBackground");
		MSWindows::uxGetThemeTextExtent = (MSWindows::fGetThemeTextExtent)MSWindows::GetProcAddress(uxThemeDll, "GetThemeTextExtent");
	}
}

void SetTransform(MSWindows::HDC hDC, LDraw::Graphics2D* pGraphics)
{
	const LDraw::matrix3f& transform = pGraphics->GetTransform()->m_matrix;

	int x = transform[2][0];
	int y = transform[2][1];

	MSWindows::SetViewportOrgEx(hDC, x, y, NULL);
}

void XPThemeCommand::Render(LDraw::Graphics2D* pGraphics)
{
	MSWindows::HDC hDC = pGraphics->GetDC();
	if (hDC)
	{
		SetTransform(hDC, pGraphics);

		MSWindows::uxDrawThemeBackground(m_hTheme, hDC, MSWindows::BP_PUSHBUTTON, MSWindows::PBS_NORMAL, &m_rect, NULL);

		pGraphics->ReleaseDC(hDC);
	}
}

XPThemeBackground::XPThemeBackground()
{
}

HANDLE XPThemeBackground::s_hTheme;

UIElement* XPThemeBackground::get_Content()
{
	return NULL;
}

void XPThemeBackground::set_Content(UIElement* content)
{
}

LDraw::SizeD XPThemeBackground::OnMeasure(LDraw::SizeD availSize)
{
	return LDraw::SizeD(0,0);
}

void XPThemeBackground::OnRender(Graphics* pGraphics)
{
	LDraw::GraphicsMetafile* pG = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p);

	Load_uxThemeDll();

	if (s_hTheme == NULL)
	{
		s_hTheme = MSWindows::uxOpenThemeData(NULL, L"Button");
	}

	LDraw::SizeD actualSize = get_ActualSize();
	MSWindows::RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = actualSize.Width;
	rect.bottom = actualSize.Height;

	ASSERT(0);
	//pG->m_pCommands->AddCommand(new XPThemeCommand(s_hTheme, rect));
}

XPThemeText::XPThemeText()
{
}

HANDLE XPThemeText::s_hTheme;

void XPThemeText::OnRender(Graphics* pGraphics)
{
}

LDraw::SizeD XPThemeText::OnMeasure(LDraw::SizeD availSize)
{
	Load_uxThemeDll();

	if (s_hTheme == NULL)
	{
		s_hTheme = MSWindows::uxOpenThemeData(NULL, L"Button");
	}

//	MSWindows::uxGetThemeTextExtent(s_hTheme);

	return LDraw::SizeD(0,0);
}

/*
void Button::alert(StringW* msg)
{
	MessageBoxA(NULL, msg->ToStringA()->c_str(), "", MB_OK);
}
*/

Button::Button()
{
	Init();
}

Button::Button(Object* Content)
{
	Init();
	set_Content(Content);
}

void Button::Init()
{
	if (ButtonStyle == NULL)
	{
		ButtonStyle = dynamic_cast<Style*>(FindResource(GetType()));

#if 0
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ButtonStyle.lxui");
		document->load(filename);

		Type* returnType;
		ButtonStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));

		/*
		ButtonStyle->Load(document->get_documentElement());
		*/
#endif
	}

	set_Style(ButtonStyle);
/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

void UIElement::InitScript()
{
	Script* pScript = get_Script();

	if (pScript)
	{
		ActionScripting::VM vm;
		vm.m_global = this;

		ActionScripting::StackFrame* frame = new ActionScripting::StackFrame;
		frame->m_pContext = pScript->m_as_context;
		frame->m_instructionsData = pScript->GetCodeData();
		frame->m_instructionsLength = pScript->GetCodeLength();
		frame->m_variables[ASTR("this")] = this;

		vm.m_pFrame = frame;
		vm.m_pc = frame->m_instructionsData;

		while (vm.next())
			;

		pScript->m_root = frame;
	}
}

// TODO, OnMouseLeftButtonDown
void Button::OnMouseDown(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

	CaptureMouse();

	SetValue(get_IsPressedProperty(), BoolObject::get_True());
}

// TODO, OnMouseLeftButtonUp
void Button::OnMouseUp(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

	ReleaseMouseCapture();

	SetValue(get_IsPressedProperty(), BoolObject::get_False());

	if (get_IsMouseOver())
	{
		OnClick();
	}
}

void Button::OnClick()
{
	ButtonBase::OnClick();

//	RoutedCommand* pCommand = new RoutedCommand;
//	ICommand* get_Command();
//	RaiseEvent(

	ICommand* command = get_Command();
	if (command)
	{
		RoutedCommand* routedCommand = dynamic_cast<RoutedCommand*>(command);
		if (routedCommand)
		{
			IInputElement* commandTarget = get_CommandTarget();
			if (commandTarget == NULL) commandTarget = this;	// ??

			routedCommand->Execute(get_CommandParameter(), commandTarget);
		}
		else
		{
			command->Execute(get_CommandParameter());
		}
	}
}

#if 0
// virtual
void Button::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	System::EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (type == MouseEvent::mouseover)
		{
#if 0
			if (m_Border1)
			{
				/*
				m_Border1->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255), 1);
				m_Border1->m_TopBrush = new SolidColorBrush(Color(255, 255, 255), 1);
				m_Border1->m_RightBrush = new SolidColorBrush(Color(160, 160, 160), 1);
				m_Border1->m_BottomBrush = new SolidColorBrush(Color(160, 160, 160), 1);

				m_Border2->m_LeftBrush = new SolidColorBrush(Color(255, 255, 255), 0.4);
				m_Border2->m_TopBrush = new SolidColorBrush(Color(255, 255, 255), 0.4);
				m_Border2->m_RightBrush = new SolidColorBrush(Color(160, 160, 160), 0.4);
				m_Border2->m_BottomBrush = new SolidColorBrush(Color(160, 160, 160), 0.4);
				*/
			}
#endif

			InvalidateRender();
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseout)
		{
#if 0
			if (m_Border1)
			{
				/*
				m_Border1->m_LeftBrush = NULL;
				m_Border1->m_TopBrush = NULL;
				m_Border1->m_RightBrush = NULL;
				m_Border1->m_BottomBrush = NULL;
				m_Border2->m_LeftBrush = NULL;
				m_Border2->m_TopBrush = NULL;
				m_Border2->m_RightBrush = NULL;
				m_Border2->m_BottomBrush = NULL;
				*/
			}
#endif
			InvalidateRender();
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mousedown)
		{
			CaptureMouse();

			SetValue(get_IsPressedProperty(), BoolObject::get_True());

#if 0
			if (m_Border1)
			{
				/*
				m_Border1->m_RightBrush = new SolidColorBrush(Color(255, 255, 255));
				m_Border1->m_BottomBrush = new SolidColorBrush(Color(255, 255, 255));
				m_Border1->m_LeftBrush = new SolidColorBrush(Color(60, 60, 60));
				m_Border1->m_TopBrush = new SolidColorBrush(Color(60, 60, 60));

				m_Border2->m_RightBrush = new SolidColorBrush(Color(190, 190, 190));
				m_Border2->m_BottomBrush = new SolidColorBrush(Color(190, 190, 190));
				m_Border2->m_LeftBrush = new SolidColorBrush(Color(110, 110, 110));
				m_Border2->m_TopBrush = new SolidColorBrush(Color(100, 110, 110));
				*/

				m_Border3->set_BorderThickness(new Thickness(new Length(1), new Length(1), new Length(0), new Length(0)));
				/*
				m_Border3->get_BorderThickness().put_Left(Length(1.0));
				m_Border3->get_BorderThickness().put_Top(Length(1.0));
				m_Border3->get_BorderThickness().put_Right(Length(0.0));
				m_Border3->get_BorderThickness().put_Bottom(Length(0.0));
				*/
				m_Border3->InvalidateMeasure();
			}
		//	ATLASSERT(0);
#if 0
			OnMeasure(LDraw::SizeD(m_computedWidth, m_computedHeight));
			Arrange(LDraw::SizeD(m_desiredWidth, m_desiredHeight));
#endif
#endif

			InvalidateRender();
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
			ReleaseMouseCapture();

			SetValue(get_IsPressedProperty(), BoolObject::get_False());

#if 0
			if (m_Border1)
			{
				m_Border3->set_BorderThickness(new Thickness(new Length(0), new Length(0), new Length(1), new Length(1)));
				/*
				m_Border3->get_BorderThickness().put_Left(Length(0.0));
				m_Border3->get_BorderThickness().put_Top(Length(0.0));
				m_Border3->get_BorderThickness().put_Right(Length(1.0));
				m_Border3->get_BorderThickness().put_Bottom(Length(1.0));
				m_Border3->InvalidateMeasure();
				*/

				/*
				m_Border1->m_LeftBrush = NULL;
				m_Border1->m_TopBrush = NULL;
				m_Border1->m_RightBrush = NULL;
				m_Border1->m_BottomBrush = NULL;
				m_Border2->m_LeftBrush = NULL;
				m_Border2->m_TopBrush = NULL;
				m_Border2->m_RightBrush = NULL;
				m_Border2->m_BottomBrush = NULL;
				*/
			}
		//	ATLASSERT(0);
#endif
#if 0
			OnMeasure(LDraw::SizeD(m_computedWidth, m_computedHeight));
			Arrange(LDraw::SizeD(m_desiredWidth, m_desiredHeight));
			Invalidate();
#endif
			evt->stopPropagation();

			if (true)//m_bHover)
			{
				System::Event* evt = new System::Event;

				evt->InitEvent(WSTR("click"),
					true,	// bubbles
					true	// cancelable
					);

				dispatchEvent(evt);

				//delete evt;
			}
		}
	}
}
#endif

}	// UI
}
