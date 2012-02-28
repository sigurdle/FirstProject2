// StylerToolPlugin.cpp : Implementation of CStylerToolPlugin
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "StylerToolPlugin.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////
// CStylerTool

CStylerTool::CStylerTool()
{
	m_pAddin = NULL;
}

CStylerTool::~CStylerTool()
{
}

ErrorCode CStylerTool::Options(UI::Control* hParent)
{
	return Success;
}

ErrorCode CStylerTool::OnDeactivate(ILXMLEditorApp* app)
{
	return Success;
}

ErrorCode CStylerTool::OnActivate(ILXMLEditorApp* app)
{
	return Success;
}

ErrorCode CStylerTool::Paint(/*[in]*/ ISVGView* view, /*[in]*/ long dragging, UI::Graphics* pGraphics)
{
	return Success;
}

ErrorCode CStylerTool::OnButtonDown(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse, /*[out,retval]*/ long* pdragging)
{
	return Success;
}

ErrorCode CStylerTool::OnButtonUp(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	return Success;
}

ErrorCode CStylerTool::OnMouseMove(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	return Success;
}

ErrorCode CStylerTool::OnSetCursor(/*[in]*/ ISVGView* view, /*[in]*/ SVGMouse* mouse)
{
	return Success;
}


// Plugin
ErrorCode CStylerToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
	m_spAddinSite = self;
	ASSERT(0);
#if 0

	if (m_spAddinSite)
	{
		CComPtr<ILXMLEditorApp> app;
		self->GetApp(&app);

		CComQIPtr<ILXAddin> lxapp = app;

		CComQIPtr<ILXAddinSite> site;
		lxapp->GetSite(&site);

		ATLASSERT(0);
#if 0
		CComPtr<IUIManager> uiManager;
		site->GetUIManager((IUnknown**)&uiManager);

		app->AddTool(self, this, NULL, ID_SVGTOOL_EYEDROPPER, L"Eyedropper", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_PAINTBUCKET, L"Paint Bucket", L"tool_ellipse.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_STYLERTOOLS);
#endif
	}
#endif
	return Success;
}

ErrorCode CStylerToolPlugin::FindTool(/*[in]*/ long id, System::Object* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{
	*pVal = NULL;

	CStylerTool* pTool = new CStylerTool;
	if (pTool)
	{
	//	pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}

	return Success;
}

}	// LXmlEdit
}
