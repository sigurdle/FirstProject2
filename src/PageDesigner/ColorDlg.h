// ColorDlg.h : Declaration of the CColorDlg

#ifndef __COLORDLG_H_
#define __COLORDLG_H_

#include "resource.h"       // main symbols

#include "..\UIT\UIT.h"

/////////////////////////////////////////////////////////////////////////////
// CColorDlg
class ATL_NO_VTABLE CColorDlg : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CColorDlg, &CLSID_ColorDlg>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CColorDlg>,
	public IDispatchImpl<IColorDlg, &IID_IColorDlg, &LIBID_PAGEDESIGNERLib>,
	public CUIDialogImpl<CColorDlg, CAxDialogImpl<CColorDlg> >,
	public CUIEventHandlerImpl,

	public CNotifyGetImpl<CColorDlg>,
	public ProcessTargetCommands,

	public IDispEventImpl<1, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,

	public IDispEventImpl<5, CColorDlg, &DIID__IColorSpectrumEvents, &LIBID_UILib, 1, 0>
{
public:
	CColorDlg()
	{
		m_reentrance = 0;
		m_colorModel = 2;	// RGB

		m_strokeOrFill = 0;
	}

	int FinalConstruct();

	CComPtr<IColorSpectrum> m_spectrum;
	CComPtr<IUIColorSlider> m_slider[4];

//	CComPtr<IPDGradientStop> m_stop;
//	CArray<IUnknown*,IUnknown*> m_targetObjects;

//	CComPtr<IPDObjectSelection> m_object;
	CComPtr<IPDObjectWithAppearanceAndStrokeFill> m_object;
	CComPtr<IPDBrush> m_brush;
	long m_strokeOrFill;

	int m_reentrance;

	int m_colorModel;

	double m_tint;
	double m_channelValue[4];

	CRect m_rcStrokeFill;
	CRect m_rcNone;

	void SetColorOnTargets();
	void SetColorFromTargets();
	void SetChannels(int nchannels);

	void SetColorModel(long colorModel);

	void GetBrush();

	enum { IDD = IDD_COLORDLG };

DECLARE_REGISTRY_RESOURCEID(IDR_COLORDLG)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CColorDlg)
	COM_INTERFACE_ENTRY(IColorDlg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CColorDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CColorDlg)
	SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel0)
	SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel1)
	SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSetChannel2)

	SINK_ENTRY_EX(5, DIID__IColorSpectrumEvents, /*dispid*/1, OnSetColorRGB)
END_SINK_MAP()

	void __stdcall OnSetChannel0(long pos);
	void __stdcall OnSetChannel1(long pos);
	void __stdcall OnSetChannel2(long pos);

	void __stdcall OnSetColorRGB(long r, long g, long b);

BEGIN_MSG_MAP(CColorDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	COMMAND_HANDLER(IDC_SWATCH_CHANNELVALUE0, EN_KILLFOCUS, OnChannelValueChanged)
	COMMAND_HANDLER(IDC_SWATCH_CHANNELVALUE1, EN_KILLFOCUS, OnChannelValueChanged)
	COMMAND_HANDLER(IDC_SWATCH_CHANNELVALUE2, EN_KILLFOCUS, OnChannelValueChanged)
	COMMAND_HANDLER(IDC_SWATCH_CHANNELVALUE3, EN_KILLFOCUS, OnChannelValueChanged)
END_MSG_MAP()

	LRESULT OnChannelValueChanged(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CColorDlg)

	LRESULT OnColorGrayscale(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnColorGrayscaleUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnColorRGB(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnColorRGBUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnColorHSB(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnColorHSBUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnColorAddtoSwatches(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID);

// IColorDlg
public:
// IUIDlg
	STDMETHOD(get_title)(BSTR* pVal)
	{
		*pVal = SysAllocString(L"Color");
		return S_OK;
	}
// IUIEventHandler
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie);
	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

#endif //__COLORDLG_H_
