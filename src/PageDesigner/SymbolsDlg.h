// SymbolsDlg.h : Declaration of the CSymbolsDlg

#ifndef __SYMBOLSDLG_H_
#define __SYMBOLSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

/////////////////////////////////////////////////////////////////////////////
// CSymbolsDlg
class ATL_NO_VTABLE CSymbolsDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSymbolsDlg, &CLSID_SymbolsDlg>,
	public IDispatchImpl<ISymbolsDlg, &IID_ISymbolsDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CSymbolsDlg, CWindowImpl<CSymbolsDlg> >,
	public CUIEventHandlerImpl,
	public CNotifyGetImpl<CSymbolsDlg>,
	public ProcessTargetCommands
{
public:
	CSymbolsDlg()
	{
		m_view = NULL;
		m_selectedSymbolIndex = -1;
	}

	int FinalConstruct();

	CComObject<CPDDocumentView>* m_view;

	int m_selectedSymbolIndex;
	CArray<IPDSymbol*,IPDSymbol*> m_selectedSymbols;

	bool IsSymbolSelected(IPDSymbol* symbol)
	{
		for (int i = 0; i < m_selectedSymbols.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedSymbols[i], symbol))
			{
				return true;
			}
		}

		return false;
	}

	void SelectSymbol(IPDSymbol* symbol)
	{
		ATLASSERT(!IsSymbolSelected(symbol));
		m_selectedSymbols.Add(symbol);
	}

	void DeselectSymbol(IPDSymbol* symbol)
	{
		for (int i = 0; i < m_selectedSymbols.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_selectedSymbols[i], symbol))
			{
				m_selectedSymbols.RemoveAt(i);
				return;
			}
		}
	}

	void DeselectAll()
	{
		m_selectedSymbols.RemoveAll();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SYMBOLSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSymbolsDlg)
	COM_INTERFACE_ENTRY(ISymbolsDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_MSG_MAP(CSymbolsDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CSymbolsDlg)

	LRESULT OnSymbolsRedefineSymbol(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnPlaceSymbolInstance(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnSymbolOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnSymbolOptionsUpdate(long iid, IUICmdUpdate* pCmdUI);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		CComQIPtr<IPDSymbol> symbol = targetObject;
		if (symbol)
		{
			if (m_hWnd)
			{
//				OnSize();
				Invalidate();
			}
		}

		return S_OK;
	}

// ISymbolsDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Symbols");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ICommandTarget
	STDMETHODIMP OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__SYMBOLSDLG_H_
