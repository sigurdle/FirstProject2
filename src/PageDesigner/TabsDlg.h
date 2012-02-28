// TabsDlg.h : Declaration of the CTabsDlg

#ifndef __TABSDLG_H_
#define __TABSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

/////////////////////////////////////////////////////////////////////////////
// CTabsDlg
class ATL_NO_VTABLE CTabsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTabsDlg, &CLSID_TabsDlg>,
	public IDispatchImpl<ITabsDlg, &IID_ITabsDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CTabsDlg, CAxDialogImpl<CTabsDlg> >,
	public IDispEventImpl<1, CTabsDlg, &DIID__ITabsControlEvents, &LIBID_PAGEDESIGNERLib, 1, 0>,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands
{
public:
	CTabsDlg()
	{
		m_view = NULL;
	}
	
	int FinalConstruct();

	CComObject<CPDDocumentView>* m_view;

	CComPtr<IPDTextPara> m_textPara;
	CComPtr<IPDTextRange> m_range;

	CComPtr<ITabsControl> m_tabsCtl;

	HBITMAP m_hButtonBitmap[5];

	enum { IDD = IDD_TABSDLG };

	void OnSize();
	void SetX(long which);

DECLARE_REGISTRY_RESOURCEID(IDR_TABSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTabsDlg)
	COM_INTERFACE_ENTRY(ITabsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_SINK_MAP(CTabsDlg)
   SINK_ENTRY_EX(1, DIID__ITabsControlEvents, /*dispid*/1, OnTabsChanged)
   SINK_ENTRY_EX(1, DIID__ITabsControlEvents, /*dispid*/2, OnTabsChanging)
   SINK_ENTRY_EX(1, DIID__ITabsControlEvents, /*dispid*/3, OnTabsSelected)
END_SINK_MAP()

	void __stdcall OnTabsChanged();
	void __stdcall OnTabsChanging(long selected);
	void __stdcall OnTabsSelected(long selected);

BEGIN_MSG_MAP(CTabsDlg)
//	MESSAGE_HANDLER(WM_NCCREATE, OnNcCreate)
//	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	COMMAND_HANDLER(IDC_TABS_POSITIONABOVEFRAME, BN_CLICKED, OnPositionAboveTextFrame)
	COMMAND_HANDLER(IDC_TABS_X, EN_KILLFOCUS, OnChangedValueX)
	COMMAND_HANDLER(IDC_TABS_ALIGNLEFT, BN_CLICKED, OnTabAlign)
	COMMAND_HANDLER(IDC_TABS_ALIGNCENTER, BN_CLICKED, OnTabAlign)
	COMMAND_HANDLER(IDC_TABS_ALIGNRIGHT, BN_CLICKED, OnTabAlign)
	COMMAND_HANDLER(IDC_TABS_ALIGNDECIMAL, BN_CLICKED, OnTabAlign)
END_MSG_MAP()

	LRESULT OnPositionAboveTextFrame(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnChangedValueX(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTabAlign(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CTabsDlg)

	LRESULT OnTabsClearAll(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnTabsClearAllUpdate(long iid, IUICmdUpdate* pCmdUI);

// ITabsDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Tabs");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__TABSDLG_H_
