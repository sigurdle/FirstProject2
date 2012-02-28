// TransparencyDlg.h : Declaration of the CTransparencyDlg

#ifndef __TRANSPARENCYDLG_H_
#define __TRANSPARENCYDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

class CPDDocumentView;

/////////////////////////////////////////////////////////////////////////////
// CTransparencyDlg
class ATL_NO_VTABLE CTransparencyDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTransparencyDlg, &CLSID_TransparencyDlg>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITransparencyDlg, &IID_ITransparencyDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CTransparencyDlg, CAxDialogImpl<CTransparencyDlg> >,
	public CNotifyGetImpl<CTransparencyDlg>,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands
{
public:
	CTransparencyDlg()
	{
		m_view = NULL;
	}

	int FinalConstruct();

	CComObject<CPDDocumentView>* m_view;

	CArray<IUnknown*,IUnknown*> m_targetObjects;

	CRect m_thumbRect;
	CRect m_bitmapRect;
	CRect m_maskRect;

	CComPtr<IPDObjectWithOpacityMask> m_objectWithOpacityMask;
	BOOL m_bHasOpacityMask;

	void SetFromTargetView();

	void OnSize();
	void SetControlValues();

	enum { IDD = IDD_TRANSPARENCYDLG };

DECLARE_REGISTRY_RESOURCEID(IDR_TRANSPARENCYDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CTransparencyDlg)
	COM_INTERFACE_ENTRY(ITransparencyDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_MSG_MAP(CTransparencyDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	COMMAND_HANDLER(IDC_TRANSP_OPACITY, EN_KILLFOCUS, OnOpacityChange)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	LRESULT OnOpacityChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

DECLARE_CMD_MAP(CTransparencyDlg)

//	LRESULT OnLinksPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
/*		CComQIPtr<IPDImage> image = targetObject;
		if (image)
		{
			if (m_hWnd)
			{
				//OnSize();
				Invalidate();
			}
		}
*/
		SetFromTargetView();
		if (m_hWnd)
		{
			InvalidateRect(&m_thumbRect);
		}

		return S_OK;
	}

public:
// ITransparencyDlg
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Transparency");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
// ICommandTarget
	STDMETHODIMP OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled);
};

#endif //__TRANSPARENCYDLG_H_
