#ifndef __EXMLDOCUMENT_H_
#define __EXMLDOCUMENT_H_

#include "resource.h"       // main symbols

#include "ErrorListImpl.h"
#include "ErrorHandler.h"
#include "WEUndoManager.h"

#include "../LXFramework/WebDocumentImpl.h"

#include "../LXUI/TextDocument.h"

#include "EElementImpl.h"

//class TextDocument;

namespace System
{
namespace LXmlEdit
{
//class DocumentType;
class CEXMLViewGroup;

class CTextBookmark : 
	public ITextBookmark
{
public:

	long get_offset()
	{
		return m_offset;
	}
	uint get_length()
	{
		return m_length;
	}

protected:

	friend class CEXMLDocument;

	System::StringW* m_name;
	long m_offset;
	long m_length;
};

class CTextBookmarkList : 
	public ITextBookmarkList
{
public:
	Array<CTextBookmark*> m_items;

	uint get_length()
	{
		return m_items.GetSize();
	}
	ITextBookmark* item(uint index)
	{
		return m_items[index];
	}
};

//class CLElementBehaviorFactory;

//class CEXMLDocument;

class CEElement;

/*
class CView
{
public:
	int m_ndlg;
	CDocumentSheet* m_pDocumentSheet;

//	IUIViewSheet* m_sheet;
};
*/

class LXMLEDITEXT CEXMLDocument : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEXMLDocument, &CLSID_EXMLDocument>,
//	public IConnectionPointContainerImpl<CEXMLDocument>,

//	public IEXMLDocument,

	public Node,

#if 0
	public ProcessTargetCommands,	// ILDOMEventListener
#endif

		/*
	public IPersistFile,	// IPersist
	public IPersistStream,	// IPersist
	public IPersistMoniker,

	public IUIActivatable,
	*/

#if 0
	public IHlinkTarget,	// Not sure if that should be on this object
	public IHlinkSite,
#endif

	public CEDocument,
	public CErrorList,//Impl<CEXMLDocument>,
	public CDOMErrorHandlerImpl<CEXMLDocument>,

	public System::IEventListener
{
public:
	CEXMLDocument();
	~CEXMLDocument();

//	int FinalConstruct();
//	void FinalRelease();

	Element* m_documentElement;

	CLXMLEditorApp* m_app;

	CTextBookmarkList* m_bookmarks;

//	CArray<CView,CView> m_views;

//	IDocumentsClass* m_documentClass;

	Web::CSSStyleDeclaration* m_defaultStyle;

	System::StringW* m_lastColor;
	/* Need this ??
	double m_defaultColorRed;
	double m_defaultColorGreen;
	double m_defaultColorBlue;
	*/

	System::StringW* m_lastGradient;

	long m_svgNextLayerIndex;

	DocumentType* get_doctype();

	virtual Node* appendChild(Node* child)
	{
		Element* element = dynamic_cast<Element*>(child);
		if (element)
			m_documentElement = element;

		return Node::appendChild(child);
	}

	Comment* createComment(System::StringW* data);
	Text* createTextNode(System::StringW* data);
	CDATASection* createCDATASection(System::StringW* data);
	ProcessingInstruction* createProcessingInstruction(System::StringW* target, System::StringW* data);
	EntityReference* createEntityReference(System::StringW* name);
	Attr* createAttributeNS(System::StringW* namespaceURI, System::StringW* qualifiedName);
	Element* createElementNS(System::StringW* namespaceURI, System::StringW* qualifiedName);

	Element* get_documentElement()
	{
		return m_documentElement;
	}

	Array<CEXMLViewGroup*> m_viewGroups;

//	CComQIPtr<ILSVGDocument>	m_xmldocPlaying;	// TODO remove
#if 0
	CComPtr<ILHTMLActiveDocument> m_document;
#endif

	Web::Document* m_document;
	System::TextDocument* m_textData;

//	CComPtr<ILDOMDocument> m_xmldocument;

	Web::IASXMLSchemaModel* m_schemaModel;	// TODO? remove

	CWEUndoManager* m_undoManager;

	void AddRenderBehavior();

	void UpdateTitles();

//	DWORD	m_activeTool;

//	CElementImpl* m_pActiveElement;
//	CElementImpl* m_pActiveSelection;

	Web::SVGElement* g_selectedSymbol;

	CEElement* m_pTree;

//	CArray<IUIViewSheet*,IUIViewSheet*> m_viewGroups;

//	CTagBase* m_pActiveAttr;

//	CComPtr<IUIViewSheet> m_spViewGroupSite;

#if 0
	CComPtr<IOleClientSite> m_spClientSite;
#endif

	int m_activeKey;
	int m_unnamedIndex;

	int m_bPlaying;
	
	int	m_videoTimeID;
	Web::AbstractView* m_svgView;	// am I using this (?)

	bool m_bSourceEditLast;

	int m_lockDOM;
	int m_lockSource;
	
	MSWindows::DWORD m_idThreadUpdateSource;
	HANDLE m_hThreadUpdateSource;

	void Prepare();
	ErrorCode CreateXMLDocumentFromTextData();

#if 0
	CComQIPtr<ILDOMDocument> GetDOMDocument()
	{
		if (!m_bPlaying)
		{
			//CComQIPtr<ILDOMDocument> document;
			return m_xmldocument;
			//ASSERT(0);
		//	m_xmlcnt->get_document(&document);
			//return document;
		}
		else
			return m_xmldocPlaying;
	}
#endif

	Element/*CElementImpl*/ * GetSvgElement();

	void OnActivate(bool bActivate);

//	void Close();

	int IsModified()
	{
		return m_modified;
	}

	void SetModified(bool bModified)
	{
		if (bModified)
			m_modified++;
		else
			m_modified = 0;
	}

	void RemoveViewGroup(CEXMLViewGroup* pViewGroup);

	void BuildElementChildren(Element* eElement);

#ifdef _DEBUG
	void ASSERT_NodeOffsets(Web::Node* node, Web::Node* exceptnode);
	void ASSERT_NodeOffsetsTextLen(Web::Node* node);
#endif

	System::StringW* GetTargetElementsXML();
	void CopyTargetElementsToClipboard();
	Element/*CElementImpl*/ * GetElementFromGUID(GUID& guid);
	void TextHasChangedReparseDOM();
	void NewWindow();
//	BOOL NewDocument();
	LONG OpenEnhancedMetaFile(LPCTSTR lpszPathName);
	void InsertSVGFragment(Web::SVGDocument* xmldoc, Web::Node* pParent, Web::Node* pBefore);
	void PasteFromClipboard();
//	CUString GetFilePart();
	void SetupEventListener();
	void RemoveEventListener();
	void TogglePlay();
//	void BuildTree();
	void InitTree();
	//Element* CreateElement(Element* domElement);

	ErrorCode GetXSLProcessingInstruction(Web::ProcessingInstruction** pVal);

	void UpdateSourceFromDOM();

	//void UpdateFrameTitles();

	/*
DECLARE_REGISTRY_RESOURCEID(IDR_WEBXMLDOCUMENT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEXMLDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEDocument)

//	COM_INTERFACE_ENTRY(IEDocumentExt)

	COM_INTERFACE_ENTRY(IEXMLDocument)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIActivatable)
	COM_INTERFACE_ENTRY(IErrorList)
	COM_INTERFACE_ENTRY(ILDOMErrorHandler)
	COM_INTERFACE_ENTRY(ILDOMEventListener)

	COM_INTERFACE_ENTRY(IHlinkTarget)
	COM_INTERFACE_ENTRY(IHlinkSite)

// Document server
//	COM_INTERFACE_ENTRY(IOleObject)
//	COM_INTERFACE_ENTRY(IOleDocument)
// Document container
	COM_INTERFACE_ENTRY(IOleDocumentSite)
	COM_INTERFACE_ENTRY(IOleClientSite)
//	COM_INTERFACE_ENTRY(IAdviseSink)

#if 0
	COM_INTERFACE_ENTRY(ILElementBehaviorFactory)
#endif
//
//	COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
//	COM_INTERFACE_ENTRY(IPersistFile)
//	COM_INTERFACE_ENTRY(IPersistStream)
	COM_INTERFACE_ENTRY(IPersistMoniker)

	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEXMLDocument)
CONNECTION_POINT_ENTRY(DIID__IEXMLDocumentEvents)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CEXMLDocument)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/1, OnTextDocumentContentChanged)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/2, OnTextDocumentInsertedText)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/3, OnTextDocumentDeletedText)
END_SINK_MAP()
#endif
	void OnTextDocumentContentChanged();
	void OnTextDocumentInsertedText(long offset, long len);
	void OnTextDocumentDeletedText(long offset, long len);

#if 0
DECLARE_CMD_MAP(CEXMLDocument)
#endif

	long OnFileSave(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFileSaveAs(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnFileReload(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnViewPreview(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnEditUndo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnEditRedo(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditUndoUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	void OnEditRedoUpdate(long id, UI::IUICmdUpdate* pCmdUI);

//	long OnViewCSSEditor(WORD wNotifyCode, WORD wID, UI::Control* hWndCtl, BOOL& bHandled);
	long OnAssignXSL(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnGotoXSL(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnGotoXSLUpdate(long id, UI::IUICmdUpdate* pCmdUI);

	long OnDocTypeSVG11(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	long OnSMILNewTopLayout(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnXPathQuery(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	System::ITextData* get_textData();
//	STDMETHOD(createEElementNS)(/*[in]*/ BSTR namespaceURI, /*[in]*/ BSTR localName, /*[out,retval]*/ Element* *pVal);

	ErrorCode Modify();

	Element* GetEElementFromDOMElement(Web::Element* domElement);
	ErrorCode SetElementID(Web::Element* element, /*[out,retval]*/ System::StringW** pVal);
	ErrorCode FindOrCreateSVGDefs(Web::SVGElement* * pVal);

	ITextBookmarkList* get_bookmarks()
	{
		return m_bookmarks;
	}

	ITextBookmark* addBookmark(/*[in]*/ System::StringW* name, /*[in]*/ long offset, /*[in]*/ long length)
	{
		CTextBookmark* pBookmark = new CTextBookmark;
	//	CComObject<CTextBookmark>::CreateInstance(&pBookmark);
	//	pBookmark->AddRef();

		pBookmark->m_name = name;
		pBookmark->m_offset = offset;
		pBookmark->m_length = length;

		m_bookmarks->m_items.Add(pBookmark);

	//	(*pVal = pBookmark)->AddRef();

		return pBookmark;
	}

// Saving
	ErrorCode SaveDocument(System::StringW* pathName)
	{
		ASSERT(0);
		return 0;
#if 0
		CComPtr<ITextData> textData;
		get_textData(&textData);

		ErrorCode hr = textData->save(pathName);
		if (SUCCEEDED(hr))
		{
			m_pathName = pathName;
			m_fileTitle = PathFindFileName(m_pathName);
		}

		return hr;
#endif
	}

	ErrorCode Save()
	{
		return SaveDocument(m_pathName);
	}

	Web::NodeType get_nodeType() const
	{
		return Web::NODE_DOCUMENT;
	}

	System::StringW* get_nodeName()
	{
		return WSTR("#document");
	}

	CEXMLViewGroup* GetActiveViewGroup();
	Web::Document* get_DOMDocument();
// IEDocument
	ErrorCode Activate();
	ErrorCode get_undoManager(/*[out, retval]*/ IUndoManager* *pVal);
	ErrorCode NewDocument();
	ErrorCode CloseDocument();
//	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
#if 1
	int ShowViews(IEFrame* pFrame);
#endif

	/*
   STDMETHOD(SetApp)(ILXAddin* pApp)
	{
		m_app = pApp;
		return S_OK;
	}
	*/

   CLXMLEditorApp* get_Application()
	{
		return m_app;
	}

	void handleEvent(System::Event* evt);

// IUIActivatable
//	STDMETHOD(OnActivate)(IUIActiveManager *uiManager);
//	STDMETHOD(OnDeactivate)(IUIActiveManager *uiManager);

// ILElementBehaviorFactory
//	STDMETHODIMP FindBehavior(BSTR bstrBehavior, BSTR bstrBehaviorUrl, ILElementBehaviorSite* pSite, ILElementBehavior** ppBehavior);

#if 0
// IPersist
	STDMETHOD(GetClassID)(CLSID __RPC_FAR *pClassID);

// IPersistFile
	STDMETHOD(IsDirty)( void);
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR __RPC_FAR *ppszFileName);

// IPersistMoniker
	STDMETHOD(Load)(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	STDMETHOD(Save)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember);
	STDMETHOD(SaveCompleted)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	STDMETHOD(GetCurMoniker)(/* [out] */ IMoniker **ppimkName);

// IPersistStream
	virtual ErrorCode STDMETHODCALLTYPE Load( 
		/* [unique][in] */ IStream *pStm);
		
		virtual ErrorCode STDMETHODCALLTYPE Save( 
		/* [unique][in] */ IStream *pStm,
		/* [in] */ BOOL fClearDirty)
	{
		return S_OK;
	}
		
		virtual ErrorCode STDMETHODCALLTYPE GetSizeMax( 
		/* [out] */ ULARGE_INTEGER *pcbSize)
	{
			return S_OK;
	}
#endif

#if 0
// IHlinkSite
	STDMETHOD(QueryService)(DWORD dwSiteData, REFGUID guidService,
		REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk);     
	STDMETHOD(GetMoniker)(DWORD dwSiteData, DWORD dwAssign,
		DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk);     
	STDMETHOD(ReadyToNavigate)(DWORD dwSiteData, DWORD dwReserved); 
	STDMETHOD(OnNavigationComplete)(DWORD dwSiteData, DWORD dwreserved,
		ErrorCode hrError, LPCWSTR pwzError);

// IHlinkTarget
	STDMETHOD(SetBrowseContext)(IHlinkBrowseContext* pihlbc);
	STDMETHOD(GetBrowseContext)(IHlinkBrowseContext** ppihlbc);
	STDMETHOD(Navigate)(DWORD grfHLNF, LPCWSTR pwzJumpLocation);
	STDMETHOD(GetMoniker)(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation);
	STDMETHOD(GetFriendlyName)(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName);
#endif

	bool Load(System::StringW* url);

#if 0
// IOleClientSite
        virtual ErrorCode STDMETHODCALLTYPE SaveObject( void)
	{
		  ::MessageBox(NULL, "SaveObject", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE GetMoniker( 
            /* [in] */ DWORD dwAssign,
            /* [in] */ DWORD dwWhichMoniker,
            /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	{
    return E_NOTIMPL;
	 ::MessageBox(NULL, "GetMoniker", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE GetContainer( 
            /* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer)
	{
	  		*ppContainer=NULL;
//		 MessageBox(NULL, "GetContainer", "", MB_OK);
		 return S_OK;
	}
        
        virtual ErrorCode STDMETHODCALLTYPE ShowObject( void)
	{
			  return S_OK;
			  ::MessageBox(NULL, "ShowObject", "", MB_OK);
		 return S_OK;
	}

        virtual ErrorCode STDMETHODCALLTYPE OnShowWindow( 
            /* [in] */ BOOL fShow)
	{
			  return S_OK;
			  ::MessageBox(NULL, "OnShowWindow", "", MB_OK);
		 return S_OK;
	}

        virtual ErrorCode STDMETHODCALLTYPE RequestNewObjectLayout( void)
	{
	    return E_NOTIMPL;
		 ::MessageBox(NULL, "RequestNewObjectLayout", "", MB_OK);
		 return S_OK;
	}

// IOleDocumentSite
	  virtual ErrorCode STDMETHODCALLTYPE ActivateMe( 
            /* [in] */ IOleDocumentView __RPC_FAR *pViewToActivate);


// IOleObject
     virtual ErrorCode STDMETHODCALLTYPE SetClientSite( 
         /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite)
	  {
		  m_spClientSite = pClientSite;

		//  CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->SetClientSite(pClientSite);
		  return S_OK;
	  }
     
     virtual ErrorCode STDMETHODCALLTYPE GetClientSite( 
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite)
	  {
		  *ppClientSite = m_spClientSite;
		  if (*ppClientSite) (*ppClientSite)->AddRef();
		  return S_OK;

		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  //return spOleObject->GetClientSite(ppClientSite);
	  }

     virtual ErrorCode STDMETHODCALLTYPE SetHostNames( 
         /* [in] */ LPCOLESTR szContainerApp,
         /* [unique][in] */ LPCOLESTR szContainerObj)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->SetHostNames(szContainerApp, szContainerObj);
	  }

     virtual ErrorCode STDMETHODCALLTYPE Close( 
         /* [in] */ DWORD dwSaveOption)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->Close(dwSaveOption);
	  }
     
     virtual ErrorCode STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->SetMoniker(dwWhichMoniker, pmk);
	  }

#if 0
     virtual ErrorCode STDMETHODCALLTYPE GetMoniker( 
         /* [in] */ DWORD dwAssign,
         /* [in] */ DWORD dwWhichMoniker,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->GetMoniker(dwAssign, dwWhichMoniker, ppmk);
	  }
#endif

     virtual ErrorCode STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->InitFromData(pDataObject, fCreation, dwReserved);
	  }

     virtual ErrorCode STDMETHODCALLTYPE GetClipboardData( 
         /* [in] */ DWORD dwReserved,
         /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->GetClipboardData(dwReserved, ppDataObject);
	  }

     virtual ErrorCode STDMETHODCALLTYPE DoVerb( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ UI::Control* hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->DoVerb(iVerb, lpmsg, pActiveSite, lindex, hwndParent, lprcPosRect);
	  }

     virtual ErrorCode STDMETHODCALLTYPE EnumVerbs( 
         /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->EnumVerbs(ppEnumOleVerb);
	  }

     virtual ErrorCode STDMETHODCALLTYPE Update( void)
  	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->Update();
	  }

     virtual ErrorCode STDMETHODCALLTYPE IsUpToDate( void)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->IsUpToDate();
	  }
     
     virtual ErrorCode STDMETHODCALLTYPE GetUserClassID( 
         /* [out] */ CLSID __RPC_FAR *pClsid)
 	  {
		  //CComQIPtr<IOleObject> spOleObject = m_document;
		  return S_OK;
	  }

     virtual ErrorCode STDMETHODCALLTYPE GetUserType( 
         /* [in] */ DWORD dwFormOfType,
         /* [out] */ LPOLESTR __RPC_FAR *pszUserType)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->GetUserType(dwFormOfType, pszUserType);
	  }
     
     virtual ErrorCode STDMETHODCALLTYPE SetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ SIZEL __RPC_FAR *psizel)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->SetExtent(dwDrawAspect, psizel);
	  }

     virtual ErrorCode STDMETHODCALLTYPE GetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [out] */ SIZEL __RPC_FAR *psizel)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->GetExtent(dwDrawAspect, psizel);
	  }
     
#if 0
     virtual ErrorCode STDMETHODCALLTYPE Advise( 
         /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
         /* [out] */ DWORD __RPC_FAR *pdwConnection)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->Advise(pAdvSink, pdwConnection);
	  }

		virtual ErrorCode STDMETHODCALLTYPE Unadvise( 
         /* [in] */ DWORD dwConnection)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->Unadvise(dwConnection);
	  }

		virtual ErrorCode STDMETHODCALLTYPE EnumAdvise( 
         /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->EnumAdvise(ppenumAdvise);
	  }
#endif

     virtual ErrorCode STDMETHODCALLTYPE GetMiscStatus( 
         /* [in] */ DWORD dwAspect,
         /* [out] */ DWORD __RPC_FAR *pdwStatus)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->GetMiscStatus(dwAspect, pdwStatus);
	  }

     virtual ErrorCode STDMETHODCALLTYPE SetColorScheme( 
         /* [in] */ LOGPALETTE __RPC_FAR *pLogpal)
	  {
		  CComQIPtr<IOleObject> spOleObject = m_document;
		  return spOleObject->SetColorScheme(pLogpal);
	  }

// IOleDocument
	STDMETHOD(CreateView)(IOleInPlaceSite __RPC_FAR *pIPSite, IStream __RPC_FAR *pstm, DWORD dwReserved, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
	  CComQIPtr<IOleDocument> spOleDocument = m_document;
	  return spOleDocument->CreateView(pIPSite, pstm, dwReserved, ppView);
	}
	STDMETHOD(GetDocMiscStatus)(DWORD __RPC_FAR *pdwStatus)
	{
	  CComQIPtr<IOleDocument> spOleDocument = m_document;
	  return spOleDocument->GetDocMiscStatus(pdwStatus);
	}
	STDMETHOD(EnumViews)(IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView)
	{
	  CComQIPtr<IOleDocument> spOleDocument = m_document;
	  return spOleDocument->EnumViews(ppEnum, ppView);
	}
#endif
};

}	// LXmlEdit
}

#endif //__EXMLDOCUMENT_H_
