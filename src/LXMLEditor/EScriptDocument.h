#ifndef __ESCRIPTDOCUMENT_H_
#define __ESCRIPTDOCUMENT_H_

#include "resource.h"       // main symbols

#include "..\LXFramework\WebDocumentImpl.h"

#include "ErrorListImpl.h"

//#include <activscp.h>

namespace System
{
namespace LXmlEdit
{

class CEScriptDocument : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CEScriptDocument, &CLSID_EScriptDocument>,
//	public IConnectionPointContainerImpl<CEScriptDocument>,
//	public IPersistFile,	// IPersist
//	public IPersistMoniker,

	public UI::ProcessTargetCommands,	// ILDOMEventListener

	public CErrorList,//Impl<CEScriptDocument>,

//	public CProxy_IEXMLDocumentEvents<CEScriptDocument>,

//	public IActiveScriptSite,

//	public IEScriptDocument,// &IID_IEScriptDocument>,

//	public IExtScriptDocument
	public CEDocument//Impl<CEScriptDocument>

//	public IDispEventImpl<1, CEScriptDocument, &DIID__ITextDataEvents, &LIBID_TEXTDATAMODLib, 1, 0>
{
public:
	CEScriptDocument()
	{
	}

	int FinalConstruct();
	void FinalRelease();

	ILXMLEditorApp* m_app;

	System::Object* /*CComQIPtr<IActiveScript>*/ m_activeScript;

	System::ITextData* m_textData;

	//CComPtr<IMoniker> m_curMoniker;

	IWEUndoManager* m_undoManager;

	void TextChanged();
	void NewWindow(IEFrame* eframe);

	ErrorCode __stdcall OnTextDocumentContentChanged();
	ErrorCode __stdcall OnTextDocumentInsertedText(long offset, long len);
	ErrorCode __stdcall OnTextDocumentDeletedText(long offset, long len);

DECLARE_CMD_MAP(CEScriptDocument)

	long OnWindowNew(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

// IEScriptDocument
public:
// IEDocument
	ErrorCode Activate();
	ErrorCode NewDocument();
	ErrorCode CloseDocument()
	{
		return Success;
	}
	ErrorCode ShowViews(IEFrame* pFrame);
//	ErrorCode(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);
	ErrorCode get_undoManager(/*[out, retval]*/ IUndoManager* *pVal);

	/*
   ErrorCode(SetApp)(ILXAddin* pApp)
	{
		m_app = pApp;
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

// IPersistMoniker
	ErrorCode(Load)(/* [in] */ BOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	ErrorCode(Save)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ BOOL fRemember);  
	ErrorCode(SaveCompleted)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	ErrorCode(GetCurMoniker)(/* [out] */ IMoniker **ppimkName);

// IActiveScriptSite
	ErrorCode(GetLCID)(/* [out] */ LCID __RPC_FAR *plcid);
	ErrorCode(GetItemInfo)(/* [in] */ LPCOLESTR pstrName, /* [in] */ DWORD dwReturnMask,/* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppiunkItem,/* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppti);
	ErrorCode(GetDocVersionString)(/* [out] */ BSTR __RPC_FAR *pbstrVersion);
	ErrorCode(OnScriptTerminate)(/* [in] */ const VARIANT __RPC_FAR *pvarResult,/* [in] */ const EXCEPINFO __RPC_FAR *pexcepinfo);
	ErrorCode(OnStateChange)(/* [in] */ SCRIPTSTATE ssScriptState);
	ErrorCode(OnScriptError)(/* [in] */ IActiveScriptError __RPC_FAR *pscripterror);
	ErrorCode(OnEnterScript)( void);
	ErrorCode(OnLeaveScript)( void);
#endif
};

}	// LXmlEdit
}

#endif //__ESCRIPTDOCUMENT_H_
