// BasicShapeToolPlugin.cpp : Implementation of CBasicShapeToolPlugin
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"

#include "BasicShapeToolPlugin.h"

#include "BasicShapeTool.h"

/////////////////////////////////////////////////////////////////////////////
// CBasicShapeToolPlugin

//STDMETHODIMP CBasicShapeToolPlugin::Startup(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ILXMLEditorApp* app)
STDMETHODIMP CBasicShapeToolPlugin::SetSite(ILXMLEditorPluginClass* self)
{
	ASSERT(0);
#if 0
	m_spAddinSite = self;

	if (m_spAddinSite)
	{
		CComPtr<ILXMLEditorApp> app;
		self->GetApp(&app);

		CComQIPtr<ILXAddin> lxapp = app;

		CComQIPtr<ILXAddinSite> site;
		lxapp->GetSite(&site);

		ASSERT(0);
#if 0
		CComPtr<IUIManager> uiManager;
		site->GetUIManager((IUnknown**)&uiManager);

//		app->AddTool(self, this, NULL, ID_SVGTOOL_SVGELEMENT, L"Viewport");
		app->AddTool(self, this, NULL, ID_SVGTOOL_ELLIPSE, L"Ellipse", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_CIRCLE, L"Circle", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_RECTANGLE, L"Rectangle", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_ROUNDEDRECTANGLE, L"Rounded Rectangle", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_LINE, L"Line", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_RECTANGULARGRID, L"Rectangular Grid", L"tool_ellipse.bmp");
		app->AddTool(self, this, NULL, ID_SVGTOOL_POLARGRID, L"Polar Grid", L"tool_ellipse.bmp");

		app->AddTool(self, this, NULL, ID_SVGTOOL_FOREIGNOBJECT, L"Foreign Object", L"tool_ellipse.bmp");

		app->AddTool(self, this, NULL, ID_SVGTOOL_CUSTOMSHAPE, L"Custom Shape", L"tool_ellipse.bmp");

		uiManager->AddToolbarCommands(_Module.GetResourceInstance(), IDR_BASICSHAPETOOLS);
#endif
	}
#endif
	return S_OK;
}

STDMETHODIMP CBasicShapeToolPlugin::FindTool(/*[in]*/ long id, IUnknown* *pdlg, /*[out,retval]*/ ISVGTool** pVal)
{
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;

	ASSERT(0);
#if 0
	CComObject<CBasicShapeTool>* pTool;
	CComObject<CBasicShapeTool>::CreateInstance(&pTool);
	if (pTool)
	{
		pTool->m_pAddin = this;

		pTool->AddRef();
		pTool->m_nTool = id;

		*pVal = pTool;
	}
#endif
	return S_OK;
}
