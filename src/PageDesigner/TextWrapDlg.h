// TextWrapDlg.h : Declaration of the CTextWrapDlg

#ifndef __TEXTWRAPDLG_H_
#define __TEXTWRAPDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

#if 0
/////////////////////////////////////////////////////////////////////////////
// CTextWrapDlg
class CTextWrapDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTextWrapDlg, &CLSID_TextWrapDlg>,
	public IDispatchImpl<ITextWrapDlg, &IID_ITextWrapDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CTextWrapDlg, CAxDialogImpl<CTextWrapDlg> >,

	public CUIEventHandlerImpl,

	public IDispEventImpl<1, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<5, CTextWrapDlg, &DIID__IUIButtonEvents, &LIBID_UILib, 1, 0>
{
public:
	CTextWrapDlg()
	{
		m_hImageList = NULL;
	}

	~CTextWrapDlg()
	{
		if (m_hImageList)
		{
			ImageList_Destroy(m_hImageList);
			m_hImageList = NULL;
		}
	}

	HIMAGELIST m_hImageList;

	CComPtr<IUIButton> m_wrapCtl[5];

	CArray<IPDObject*,IPDObject*> m_targetObjects;

	enum { IDD = IDD_TEXTWRAPDLG };

	void SetControlValues();
	void SetTextWrap(PDTextWrap wrap);

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_TEXTWRAPDLG)

BEGIN_COM_MAP(CTextWrapDlg)
	COM_INTERFACE_ENTRY(ITextWrapDlg)
	COM_INTERFACE_ENTRY(IDispatch)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
END_COM_MAP()

BEGIN_SINK_MAP(CTextWrapDlg)
   SINK_ENTRY_EX(1, DIID__IUIButtonEvents, /*dispid*/1, OnClickNone)
   SINK_ENTRY_EX(2, DIID__IUIButtonEvents, /*dispid*/1, OnClickBBox)
   SINK_ENTRY_EX(3, DIID__IUIButtonEvents, /*dispid*/1, OnClickShape)
   SINK_ENTRY_EX(4, DIID__IUIButtonEvents, /*dispid*/1, OnClickObject)
   SINK_ENTRY_EX(5, DIID__IUIButtonEvents, /*dispid*/1, OnClickColumn)
END_SINK_MAP()

	void __stdcall OnClickNone();
	void __stdcall OnClickBBox();
	void __stdcall OnClickShape();
	void __stdcall OnClickObject();
	void __stdcall OnClickColumn();

BEGIN_MSG_MAP(CTextWrapDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

// ITextWrapDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Text Wrap");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif

#endif //__TEXTWRAPDLG_H_
