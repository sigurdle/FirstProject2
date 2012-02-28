
#ifdef __LERSTAD__
#import "GUI/GUI.h"
#else
#include "GUI/GUI.h"
#endif

#ifdef __LERSTAD__
#import "CodeComp/CodeComp.h"
#else
#include "CodeComp/CodeComp.h"
#endif

/*
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/EcmaScript.typeinfo"
#else
#include "EcmaScript/EcmaScript.h"
#endif
*/

#ifndef __LERSTAD__
#include "EcmaScript/EcmaScript.h"
#endif

/*
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/X3D.typeinfo"
#else
#include "X3D/X3D.h"
#endif
*/

/*
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LSVG.typeinfo"
#else
#include "LSVG/LSVG.h"
#endif
*/

namespace System
{

DECLSPEC_DLLEXPORT void Search(StringIn str);

namespace Start
{

DECLSPEC_DLLEXPORT String GetFilename(Type* pType);
//DECLSPEC_DLLEXPORT int Execute(StringIn cmd);
DECLSPEC_DLLEXPORT void Load(StringIn filename);
DECLSPEC_DLLEXPORT void CreateBinding(StringIn varname, Gui::IBinding* binding);
DECLSPEC_DLLEXPORT void Speak(StringIn str);

class StartApp : public Gui::Application
{
public:
	static int Main(StringIn cmdline);

//	virtual bool DdeExecute(StringIn command) override;

	/*
	static PaintApp* get_Application()
	{
		return s_app;
	}
	*/
};

class DECLSPEC_DLLEXPORT MyPage : public Gui::UIElement
{
public:

	CTOR MyPage() : UIElement(get_Class())
	{
	}

	Expressive::Expression* m_expression;

	Gui::geometry m_geometry;
	Gui::pathgeometry m_cgeometry;

	vector<gm::PointF> m_points;

	DEPENDENCY_PROPERTY(float, BrushWidth)

	DEPENDENCY_CLASS(MyPage, Gui::UIElement)

protected:

	virtual void RenderRetained(Gui::ManagedRetainedRenderContext renderContext) override;

	virtual void OnMouseLeftButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseRightButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseRightButtonUp(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseMove(Gui::MouseEventArgs* args) override;
};

/*
struct ITest;

ComPtr<ITest> hk;
*/

class DECLSPEC_DLLEXPORT testclass
{
public:

	operator bool ()
	{
		return true;
	}

	operator bool () const
	{
		return true;
	}

	operator String ()
	{
		return "A";
	}

	operator String () const
	{
		return "A";
	}
};

extern "C" int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow);

}	// Start
}	// System

/**
@mainpage Start

@section section_toc Nice TOC Title

@section section_features Features

 <li>Reflection of c++</li>
 <li>Garbage collection</li>


 */