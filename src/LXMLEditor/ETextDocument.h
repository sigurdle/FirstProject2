#ifndef __ETEXTDOCUMENT_H_
#define __ETEXTDOCUMENT_H_

#include "resource.h"       // main symbols

#include "../LXFramework/WebDocumentImpl.h"

#include "WEUndoManager.h"

namespace System
{
namespace LXmlEdit
{

class CETextDocument : 
	public UI::ProcessTargetCommands,	// IDOMEventListener
//	public ITextDocument
	public CEDocument//Impl<CETextDocument>
{
public:
	CTOR CETextDocument()
	{
		m_undoManager = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CLXMLEditorApp* m_app;

	//CComPtr<IMoniker> m_curMoniker;

	System::ITextData* m_textData;

//	CComQIPtr<IWEUndoManager> m_undoManager;
	CWEUndoManager* m_undoManager;

	ErrorCode NewWindow(IEFrame* pFrame);

DECLARE_CMD_MAP(CETextDocument)

	long OnFileSave(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnFileSaveAs(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnEditUndo(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	long OnEditRedo(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnEditUndoUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	void OnEditRedoUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// ITextDocument
public:
	System::ITextData* get_textData()
	{
		return m_textData;
	}

	ErrorCode Activate();
// IWebDocument
	ErrorCode NewDocument();
	ErrorCode CloseDocument()
	{
		return Success;
	}
	ErrorCode ShowViews(IEFrame* pFrame);
	ErrorCode get_undoManager(/*[out, retval]*/ IUndoManager* *pVal);

// IPersistFile
	ErrorCode IsDirty( void);
	ErrorCode Load(System::StringW* pszFileName, uint dwMode);
	ErrorCode Save(System::StringW* pszFileName, bool fRemember);
	ErrorCode SaveCompleted(System::StringW* pszFileName);
	System::StringW* GetCurFile();
};

}	// LXmlEdit
}

#endif //__ETEXTDOCUMENT_H_
