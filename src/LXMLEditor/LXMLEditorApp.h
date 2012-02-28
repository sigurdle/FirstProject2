#ifndef __LXMLEDITORAPP_H_
#define __LXMLEDITORAPP_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{
class CEXMLDocument;

class CFormatColor
{
public:
	System::StringW* m_name;
	LDraw::Color m_fgColor;
	LDraw::Color m_bgColor;
	int m_fgAutomatic;
	int m_bgAutomatic;
};

class CFormatWindow
{
public:
	~CFormatWindow()
	{
		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			delete m_formatColors[i];
		}
		m_formatColors.RemoveAll();
	}

	System::StringW* m_name;
//	LOGFONT m_lf;

	Array<CFormatColor*> m_formatColors;

	CFormatWindow& operator = (CFormatWindow& window)
	{
		ASSERT(0);
#if 0
		m_name = window.m_name;
		m_lf = window.m_lf;

		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			delete m_formatColors[i];
		}
		m_formatColors.RemoveAll();

		for (i = 0; i < window.m_formatColors.GetSize(); i++)
		{
			CFormatColor* pColor = new CFormatColor;
			*pColor = *window.m_formatColors[i];
			m_formatColors.Add(pColor);
		}
#endif
		return *this;
	}

	void GetFormatColorValues(WCHAR* name, LDraw::Color *fgColor, LDraw::Color *bgColor)
	{
		ASSERT(0);
#if 0
		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			if (!wcscmp(name, m_formatColors[i]->m_name.c_str()))
			{
				if (fgColor)
				{
					if (m_formatColors[i]->m_fgColor==-1)
						*fgColor = GetSysColor(m_formatColors[i]->m_fgAutomatic);
					else
						*fgColor = m_formatColors[i]->m_fgColor;
				}

				if (bgColor)
				{
					if (m_formatColors[i]->m_bgColor==-1)
						*bgColor = GetSysColor(m_formatColors[i]->m_bgAutomatic);
					else
						*bgColor = m_formatColors[i]->m_bgColor;
				}

				return;
			}
		}
#endif
	}

	long RegisterFormatColor(System::StringW* name, LDraw::Color fgColor, LDraw::Color bgColor, int fgAutomatic, int bgAutomatic)
	{
		for (int i = 0; i < m_formatColors.GetSize(); i++)
		{
			if (!wcscmp(name->c_str(), m_formatColors[i]->m_name->c_str()))
			{
				return i;
			}
		}

		CFormatColor* pFormatColor = new CFormatColor;
		pFormatColor->m_name = name;
		pFormatColor->m_fgColor = fgColor;
		pFormatColor->m_bgColor = bgColor;
		pFormatColor->m_fgAutomatic = fgAutomatic;
		pFormatColor->m_bgAutomatic = bgAutomatic;

		int index = m_formatColors.Add(pFormatColor);

		return index;
	}
};

//CFormatWindow* RegisterFormatWindow(WCHAR* name);

#if 0
// XSLT documents class, Do I have a class for each kind of document ?
class ATL_NO_VTABLE CXSLTDocuments : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDocumentsClass
{
public:
	CXSLTDocuments()
	{
		m_pActiveDocument = NULL;
	}

	CEXMLDocument* m_pActiveDocument;

BEGIN_COM_MAP(CXSLTDocuments)
	COM_INTERFACE_ENTRY(IDocumentsClass)
END_COM_MAP()
};
#endif

class CPluginClass : 
	public ILXMLEditorPluginClass
{
public:
	CTOR CPluginClass()
	{
		m_app = NULL;
	}

	System::StringW* m_name;
//	CLSID	m_clsid;

	ILXMLEditorPlugin* m_p;

	ILXMLEditorApp* m_app;

	ILXMLEditorApp* GetApp()
	{
		return m_app;
	}

	System::StringW* GetName()
	{
		return m_name;
	}
};

class CTool
{
public:
	CTOR CTool()
	{
		m_id = 0;
	}

	//IUICommand> m_command;

	ISVGTool* m_tool;
	UI::Border* m_toolOptionsDlgSite;
	long m_id;
};

class CToolPreset
{
public:
	CTOR CToolPreset()
	{
		m_pTool = NULL;
		m_data = NULL;
	}

	System::StringW* m_name;
	CTool* m_pTool;
	uint8 * m_data;
};


class CLXMLEditorApp;

class CToolOptionsDlg;

/////////////////////////////////////////////
// CLElementBehaviorFactory

#if 0
class ATL_NO_VTABLE CLElementBehaviorFactory :
	public CComObjectRootEx<CComSingleThreadModel>,
	public ILElementBehaviorFactory
{
public:
	CLElementBehaviorFactory()
	{
		m_pApp = NULL;
	}

//	CEXMLDocument* m_pDocument;
	CLXMLEditorApp* m_pApp;

BEGIN_COM_MAP(CLElementBehaviorFactory)
	COM_INTERFACE_ENTRY(ILElementBehaviorFactory)
END_COM_MAP()

public:
// ILElementBehaviorFactory
//	STDMETHODIMP FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorSite* pSite, ILElementBehavior** ppBehavior);
};
#endif

//class CLXMLEditorFrame;

class LXMLEDITEXT CLXMLEditorApp : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CLXMLEditorApp, &CLSID_LXMLEditorApp>,

//	public IConnectionPointContainerImpl<CLXMLEditorApp>,
//	public ILXMLEditorApp,// &IID_ILXMLEditorApp, &LIBID_LXMLEDITORLib>,
	public UI::CLXUIWindow,

//	public CUIActiveManagerImpl,

//	public ILXAddin,
//	public IUIManagerSite,
	public UI::ProcessTargetCommands,	// TODO ???

//	public ILDOMEventListener,

	public UI::CViewGroup

//	public CProxy_ILXMLEditorAppEvents< CLXMLEditorApp >
{
public:
	CTOR CLXMLEditorApp();
	~CLXMLEditorApp();

//	CArray<CDocumentSheet*,CDocumentSheet*> m_xmlDocumentSheet;

//	int FinalConstruct();
//	void FinalRelease();

//	CComPtr<ILXAddinSite> m_spAddinSite;
//	CLXMLEditorFrame* m_pFrame;

	UI::ChildWindowContainer* m_Canvas;

//	ILXUIDocument* m_appdocument;

//	CComPtr<IUIManager> m_uiManager;

	UI::Control* m_toolsElement;

	int m_strokeOrFill;	//0=stroke, 1=fill

#if 0
	CComObject<CLElementBehaviorFactory>* m_pElementBehaviorFactory;
#endif

//

//	IActiveCntDocument* m_ActiveDocument;

	Array<CPluginClass*> m_plugins;

	Array<CTool*> m_tools;

	Array<CToolPreset*> m_toolPresets;

	CTool* m_pActiveTool;
	CTool* m_pActiveSelectionTool;

	bool m_macroRecording;

	UI::CDocumentWorkspace m_appWorkspace;

	UI::CDocumentWorkspace m_xmlDocumentWorkspace;
	UI::CDocumentWorkspace m_layoutViewWorkspace;
	UI::CDocumentWorkspace m_cssDocumentWorkspace;
	UI::CDocumentWorkspace m_sceneDocumentWorkspace;

	Array<CEXMLDocument*> m_xmlDocuments;

//	CComPtr<IUIDlgSite> m_objectsBar;
//	CComPtr<IUIDlgSite> m_navigatorBar;
	/*CComPtr<IUIDlgSite>*/ UI::Control* m_svgToolsBar;
//	CComPtr<IUIDlgSite> m_scriptsBar;
//	CComPtr<IUIDlgSite> m_cssPropertiesBar;

	CToolOptionsDlg* m_pToolOptionsDlg;

//	CComObject<CXSLTDocuments>* m_xsltDocuments;

// Preferences

	int m_tabSize;
	int m_colorFormat;

	LDraw::Color m_transpGridColor0;
	LDraw::Color m_transpGridColor1;
	long m_transpGridSizeX;
	long m_transpGridSizeY;

	Array<CFormatWindow*> m_formatWindows;

	CFormatWindow* RegisterFormatWindow(WCHAR* name)
	{
		for (int i = 0; i < m_formatWindows.GetSize(); i++)
		{
			if (!wcscmp(m_formatWindows[i]->m_name->c_str(), name))
			{
				return m_formatWindows[i];
			}
		}

		return NULL;
	}

//

//	CArray<IActiveCntDocument*,IActiveCntDocument*> m_documents;

// CViewGroup
	virtual int OnGroupActivate(bool bActivate);
	virtual int OnGroupClose();

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_LXMLEDITORAPP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXMLEditorApp)
	COM_INTERFACE_ENTRY(ILXAddin)
	COM_INTERFACE_ENTRY(IUIManagerSite)
	COM_INTERFACE_ENTRY(ILXMLEditorApp)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IDispatch)
	//COM_INTERFACE_ENTRY(ICommandTarget)	// TODO remove
	COM_INTERFACE_ENTRY(ILDOMEventListener) // (ProcessTargetCommands inherits from this)
	//COM_INTERFACE_ENTRY(IUIActiveManager)	// TODO remove

	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CLXMLEditorApp)
	CONNECTION_POINT_ENTRY(DIID__ILXMLEditorAppEvents)
END_CONNECTION_POINT_MAP()
*/

DECLARE_CMD_MAP(CLXMLEditorApp)

	long OnFileOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFileOpenURL(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

//	long OnFilePrefs(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFileNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFileNewDefault(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnSwatchLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnSymbolLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFilterLibrariesOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnSVGTool(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnSVGToolUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnSVGToggleFillStroke(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnNewNewsItem(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnCustomize(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnOptions(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnConvertImportDatabaseData(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	void OnFontfaceUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnEditEmptyClipboard(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditEmptyClipboardUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

	long OnHelp(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
//	long OnAbout(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, bool& bHandled);

	long OnMacroRecord(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

//	long OnScanMediaFiles(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, bool& bHandled);

// ILXMLEditorApp
public:
//	STDMETHOD(get_ActiveDocument)(/*[out, retval]*/ IActiveCntDocument* *pVal);
	int get_tabSize();
#if 0
	STDMETHOD(CreateNewDocument)(/*[in]*/ BSTR filename, /*[out,retval]*/ IEDocument** pVal);
#endif
	ErrorCode OpenDocument(System::StringW* pathName, /*[out,retval]*/ System::Object* *pVal);
//	STDMETHOD(OpenDocument)(IUnknown* filesystem, BSTR pathName, VARIANT_bool *success);
//	STDMETHOD(get_uiManager)(/*[out, retval]*/ IUnknown* *pVal);
//	STDMETHOD(get_frame)(/*[out, retval]*/ IWebEditorFrame* *pVal);

	ErrorCode AddTool(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ ISVGToolFactory* factory, System::Object* pToolDlg, /*[in]*/ long toolId, /*[in]*/ System::StringW* name, System::StringW* imageFilename);
	ErrorCode RemoveTool(/*[in]*/ ILXMLEditorPluginClass* self, /*[in]*/ long toolId);
	ErrorCode GetActiveTool(/*[in]*/ bool bSelection, /*[out,retval]*/ ISVGTool* *pVal);
	ErrorCode SetActiveToolByID(/*[in]*/ long toolID);
	ErrorCode GetToolID(/*[in]*/ ISVGTool* tool, /*[out,retval]*/ long *pVal);

// ILXAddin
#if 0
	STDMETHOD(GetSite)(ILXAddinSite* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_spAddinSite;
		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(SetSite)(ILXAddinSite* pSite);
#endif

	/*
	STDMETHOD(Show)(ILXUIElement* element)
	{
		return E_NOTIMPL;
	}
	*/

	//STDMETHOD(OnCreateFrame)();
//	STDMETHOD(CreateDlg)(UINT nID, IUIDlg* *pVal);

#if 0
   STDMETHOD(SetUIManager)(IUIManager* newVal);
   STDMETHOD(GetUIManager)(IUIManager* *pVal)
	{
		*pVal = m_uiManager;
		(*pVal)->AddRef();
		return S_OK;
	}
#endif

#if 0
// ILDOMEventListener
	STDMETHOD(handleEvent)(ILDOMEvent* evt);
#endif
};

}	// LXmlEdit
}

#endif //__LXMLEDITORAPP_H_
