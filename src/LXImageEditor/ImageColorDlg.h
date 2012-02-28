// ImageColorDlg.h : Declaration of the CImageColorDlg

#ifndef __ImageColorDlg_H_
#define __ImageColorDlg_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageColorDlg
class ATL_NO_VTABLE CImageColorDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectionPointContainerImpl<CImageColorDlg>,
	public IDispatchImpl<IImageColorDlg, &IID_IImageColorDlg, &LIBID_LXIMAGEEDITORLib>,

	public CUIDialogImpl<CImageColorDlg, CAxDialogImpl<CImageColorDlg> >,
	public ProcessTargetCommands,
	public CUIEventHandlerImpl,

	public IDispEventImpl<1, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CImageColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>
//	public IDispEventImpl<5, CImageColorDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<6, CImageColorDlg, &DIID__IEXMLDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>,
//	public IDispEventImpl<7, CImageColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
{
public:
	CImageColorDlg()
	{
//		m_pElement = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	CComPtr<IUIColorSlider> m_slider[4];
	int m_channelValue[4];

	CComPtr<IImageView> m_view;

//	CComPtr<IEColor> m_color;

	CRect m_strokerc;
	CRect m_fillrc;

	enum { IDD = IDD_IMAGECOLORDLG };

	void DrawFillPaint(CDC& dc, CRect rc, WCHAR* fillStr);
	void DrawStrokePaint(CDC& dc, CRect rc, WCHAR* strokeStr);

	void OnSliderPos(int channel, long nPos);
	void UpdateSliders();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CImageColorDlg)
	COM_INTERFACE_ENTRY(IImageColorDlg)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	//COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CImageColorDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CImageColorDlg)
   SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider0SetPos)
   SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider1SetPos)
   SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider2SetPos)
   SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider3SetPos)
//   SINK_ENTRY_EX(6, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
//	SINK_ENTRY_EX(7, DIID__IEXMLViewGroupEvents, /*dispid*/2, OnColorChanged)
END_SINK_MAP()

	HRESULT __stdcall OnSlider0SetPos(long pos);
	HRESULT __stdcall OnSlider1SetPos(long pos);
	HRESULT __stdcall OnSlider2SetPos(long pos);
	HRESULT __stdcall OnSlider3SetPos(long pos);

	void __stdcall OnColorChanged();

//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

BEGIN_MSG_MAP(CImageColorDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CImageColorDlg)

	LRESULT OnColorInvert(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnColorComplement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	void OnDeleteSelectionUpdate(long wID, IUICmdUpdate* pCmdUI);

// IImageColorDlg
public:
//	STDMETHOD(SetColor)(/*[in]*/ IEColor* color);
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__ImageColorDlg_H_
