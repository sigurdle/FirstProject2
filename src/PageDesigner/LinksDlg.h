// LinksDlg.h : Declaration of the CLinksDlg

#ifndef __LINKSDLG_H_
#define __LINKSDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CLinksDlg
class ATL_NO_VTABLE CLinksDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLinksDlg, &CLSID_LinksDlg>,
	public ISupportErrorInfo,
	public IDispatchImpl<ILinksDlg, &IID_ILinksDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CLinksDlg, CWindowImpl<CLinksDlg> >,
	public CNotifyGetImpl<CLinksDlg>,
	public CUIEventHandlerImpl,
	public ProcessTargetCommands,
	public IDispEventImpl<1, CLinksDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CLinksDlg()
	{
		m_thumbSize = 1;	// Small
	}

	int FinalConstruct();

	CRect m_areaRect;

	CAxWindow m_axvert;
	CComPtr<IUIScrollBar> m_vert;

	int m_thumbSize;

	CComPtr<IPDDocument> m_document;

	void OnSize();

DECLARE_REGISTRY_RESOURCEID(IDR_LINKSDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLinksDlg)
	COM_INTERFACE_ENTRY(ILinksDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_SINK_MAP(CLinksDlg)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CLinksDlg)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CLinksDlg)

	LRESULT OnLinksPaletteOptions(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		CComQIPtr<IPDImage> image = targetObject;
		if (image)
		{
			if (m_hWnd)
			{
				OnSize();
				Invalidate();
			}
		}

		return S_OK;
	}

public:
// ILinksDlg
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Links");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__LINKSDLG_H_
