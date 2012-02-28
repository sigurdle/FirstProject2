// EDTDDocument.h : Declaration of the CEDTDDocument

#ifndef __EDTDDocument_H_
#define __EDTDDocument_H_

#include "resource.h"       // main symbols


#include "ErrorListImpl.h"
#include "ErrorHandler.h"

#include "..\LXFramework\WebDocumentImpl.h"

namespace System
{
namespace LXmlEdit
{

class CDTDViewGroup;

class CEDTDDocument : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEDTDDocument, &CLSID_EDTDDocument>,
//	public IConnectionPointContainerImpl<CEDTDDocument>,
//	public IEDTDDocument,

	public CEDocument,//Impl<CEDTDDocument>,

//	public CProxy_IEXMLDocumentEvents< CEDTDDocument >,

	public CErrorList,//Impl<CEDTDDocument>,
	public CDOMErrorHandlerImpl<CEDTDDocument>,

	public UI::ProcessTargetCommands	// ILDOMEventListener
//	public IPersistFile	// IPersist

//	public IDispEventImpl<1, CEDTDDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>
#if 0
	,

	public IDispEventImpl<2, CEDTDDocument, &DIID__IDTDModelEvents, &LIBID_ASDTDMODLib, 1, 0>
#endif
{
public:
	CEDTDDocument();

	int FinalConstruct();
	void FinalRelease();

	IWEUndoManager* m_undoManager;

	System::ITextData* m_textData;

#if 0
	Web::ILDTDDocument* m_dtdDocument;
#endif
	Web::IASModel* m_dtdModel;
#if 0
	CComQIPtr<IASModel> m_dtdModel;
#endif

	Array<CDTDViewGroup*> m_viewGroups;

	bool m_bSourceEditLast;

	int m_lockDOM;
	int m_lockSource;

	void Prepare();
	void NewWindow();

	void TextHasChangedReparse();
	void UpdateSourceFromDOM();

#if 0
DECLARE_REGISTRY_RESOURCEID(IDR_EDTDDOCUMENT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDTDDocument)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IEDocument)
	COM_INTERFACE_ENTRY(IEDTDDocument)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ILDOMErrorHandler)
	COM_INTERFACE_ENTRY(IErrorList)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEDTDDocument)
CONNECTION_POINT_ENTRY(DIID__IEXMLDocumentEvents)
END_CONNECTION_POINT_MAP()


BEGIN_SINK_MAP(CEDTDDocument)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/1, OnTextDocumentContentChanged)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/2, OnTextDocumentInsertedText)
   SINK_ENTRY_EX(1, DIID__ITextDataEvents, /*dispid*/3, OnTextDocumentDeletedText)
#if 0
   SINK_ENTRY_EX(2, DIID__IDTDModelEvents, /*dispid*/1, OnModelChanged)
#endif
#if 0
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/1, cnt_insertedNode)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/2, cnt_beforeRemovedNode)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/3, cnt_afterRemovedNode)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/4, cnt_changedAttribute)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/5, cnt_changedTextContentNode)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/6, cnt_setDocument)
   SINK_ENTRY_EX(2, DIID__IDOMDocumentContainerEvents, /*dispid*/7, cnt_beforesetDocument)
#endif
END_SINK_MAP()
#endif

	void __stdcall OnModelChanged();

	ErrorCode __stdcall OnTextDocumentContentChanged();
	ErrorCode __stdcall OnTextDocumentInsertedText(long offset, long len);
	ErrorCode __stdcall OnTextDocumentDeletedText(long offset, long len);

DECLARE_CMD_MAP(CEDTDDocument)

	long OnWindowNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IEDTDDocument
public:
//	ErrorCode(GetDocumentsClass)(/*[out,retval]*/ IDocumentsClass* *pVal);
	ErrorCode GetModified(/*[out,retval]*/ long* pVal);
	ErrorCode Activate();

// IWebDocument
	ErrorCode NewDocument();
	ErrorCode ShowViews(IEFrame* pFrame);
	ErrorCode CloseDocument()
	{
		return Success;
	}
//	ErrorCode(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	ErrorCode get_undoManager(/*[out, retval]*/ IUndoManager* *pVal);

	/*
   ErrorCode(SetApp)(ILXAddin* pApp)
	{
		return S_OK;
	}
	*/

#if 0
// IPersist
	ErrorCode(GetClassID)(CLSID __RPC_FAR *pClassID);

// IPersistFile
	ErrorCode(IsDirty)( void);
	ErrorCode(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	ErrorCode(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	ErrorCode(SaveCompleted)(LPCOLESTR pszFileName);
	ErrorCode(GetCurFile)(LPOLESTR __RPC_FAR *ppszFileName);
#endif
};

}	// LXmlEdit
}

#endif //__EDTDDocument_H_
