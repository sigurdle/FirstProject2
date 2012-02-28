// XMLGridView.h : Declaration of the CXMLGridView

#ifndef __XMLGRIDVIEW_H_
#define __XMLGRIDVIEW_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

/////////////////////////////////////////////////////////////////////////////
// CXMLGridView
class CXMLGridView : 
//	public CComCoClass<CXMLGridView, &CLSID_XMLGridView>,
public UI::ProcessTargetCommands,	// ILDOMEventListener

//	public CUIDialogImpl<CXMLGridView, CWindowImpl<CXMLGridView> >
public UI::Control

#if 0
	public IDispEventImpl<1, CXMLGridView, &DIID__IXMLGridCtlEvents, &LIBID_XMLEDITCTLSLib, 1, 0>,
	public IDispEventImpl<4, CXMLGridView, &DIID__ILXMLEditorAppEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
	CXMLGridView()
	{
		m_viewGroup = NULL;
	}

	/*
	int FinalConstruct()
	{
		HRESULT hr;

		hr = m_XmlGrid.CoCreateInstance(CLSID_XMLGridCtl);
		if (FAILED(hr)) return E_NOINTERFACE;

		return S_OK;
	}

	void FinalRelease()
	{
		m_XmlGrid.Release();
	}
	*/

//	CComQIPtr<IEXMLDocument> m_document;
	CEXMLViewGroup* m_viewGroup;

#if 0
	CAxWindow m_axXmlGrid;
	CComPtr<IXMLGridCtl> m_XmlGrid;
#endif

	void OnSize();

#if 0
BEGIN_SINK_MAP(CXMLGridView)
   SINK_ENTRY_EX(1, DIID__IXMLGridCtlEvents, /*dispid*/1, OnSelectNode)
	SINK_ENTRY_EX(4, DIID__ILXMLEditorAppEvents, /*dispid*/1, OnPrefsChange)
END_SINK_MAP()
#endif
void __stdcall OnSelectNode(System::Object * node);
	void __stdcall OnPrefsChange();

	long OnCreate();
	long OnDestroy();
	//long OnSize();

DECLARE_CMD_MAP(CXMLGridView)

	long OnInsertElement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertAttribute(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertText(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertCData(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertComment(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertProcessingInstruction(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnInsertDTDElement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnEditCopy(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnEditPaste(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditPasteUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnEditClearUpdate(long iid, UI::IUICmdUpdate* pCmdUI);
	long OnTableDisplayastable(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnTableDisplayastableUpdate(long iid, UI::IUICmdUpdate* pCmdUI);

// IXMLGridView
public:
	ErrorCode get_document(/*[out, retval]*/ CEXMLDocument* *pVal);
//	ErrorCode(put_document)(/*[in]*/ IWebXMLDocument* newVal);
// IUIDlg
	ErrorCode OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView);
	/*
	ErrorCode(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"XML Grid");
		return S_OK;
	}
	*/
// ICommandTarget
//	ErrorCode(OnCmdMsg)(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

}	// LXmlEdit
}

#endif //__XMLGRIDVIEW_H_
