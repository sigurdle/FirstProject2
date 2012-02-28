#ifndef __ECOLORDLG_H_
#define __ECOLORDLG_H_

#include "resource.h"       // main symbols

class CView;

namespace System
{
namespace LXmlEdit
{

class CEColorDlg : 
	public UI::Control,
//	public CUIDialogImpl<CEColorDlg, CAxDialogImpl<CEColorDlg> >,
	public IEColorSite,
	public UI::ProcessTargetCommands
//	public CUIEventHandlerImpl,
#if 0
	public IDispEventImpl<1, CEColorDlg, &DIID__IUISliderEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<2, CEColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<3, CEColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<4, CEColorDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
//	public IDispEventImpl<5, CEColorDlg, &DIID__IUIManagerEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<6, CEColorDlg, &DIID__IEXMLDocumentEvents, &LIBID_LXMLEDITORLib, 1, 0>,
	public IDispEventImpl<7, CEColorDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
#endif
{
public:
	CEColorDlg()
	{
		m_app = NULL;

		m_nColorPicker = 1;	// RGB Sliders
		m_alpha = -1;
	}

	int FinalConstruct();
	void FinalRelease();

	UI::CView* m_view;
	CLXMLEditorApp* m_app;

	CEXMLViewGroup* m_viewGroup;

//	CComQIPtr<ILHTMLActiveDocument> m_htmlActiveDoc;
//	CComQIPtr<ILHTMLActiveView> m_htmlView;

//	CComPtr<IUIColorSlider> m_slider[4];
//	int m_channelValue[4];

//	CComPtr<IEColor> m_color;

	LDraw::BBoxi m_strokerc;
	LDraw::BBoxi m_fillrc;

	UI::Control* m_colorDlg;
	int m_nColorPicker;

#if 0
	CComPtr<IUISlider> m_alphaSlider;
#endif

	long m_alpha;

	enum { IDD = IDD_COLORDLG };

	void DrawFillPaint(UI::Graphics* dc, LDraw::BBoxi rc, WCHAR* fillStr);
	void DrawStrokePaint(UI::Graphics* dc, LDraw::BBoxi rc, WCHAR* strokeStr);

	void OnSize();

	UI::Control* CreateColorPicker(int nColorPicker);
	void SetColorPicker(int nColorPicker);
	void SetColorPickerColor();

//	void OnSliderPos(int channel, long nPos);
//	void UpdateSliders();

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEColorDlg)
	COM_INTERFACE_ENTRY(IEColorDlg)
	COM_INTERFACE_ENTRY(IEColorSite)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	//COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CEColorDlg)
END_CONNECTION_POINT_MAP()

BEGIN_SINK_MAP(CEColorDlg)
   SINK_ENTRY_EX(1, DIID__IUISliderEvents, /*dispid*/1, OnAlphaSliderPos)
  // SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider1SetPos)
//   SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider2SetPos)
  // SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider3SetPos)
//   SINK_ENTRY_EX(6, DIID__IWebXMLDocumentEvents, /*dispid*/1, OnDOMEvent)
	SINK_ENTRY_EX(7, DIID__IEXMLViewGroupEvents, /*dispid*/2, OnColorChanged)
END_SINK_MAP()
#endif

	void __stdcall OnAlphaSliderPos(long code, long pos);
/*
	HRESULT __stdcall OnSlider1SetPos(long pos);
	HRESULT __stdcall OnSlider2SetPos(long pos);
	HRESULT __stdcall OnSlider3SetPos(long pos);
*/

	void __stdcall OnColorChanged();

//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

	/*
BEGIN_MSG_MAP(CEColorDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()
*/

//	long OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CEColorDlg)

	long OnColorGrayscale(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnColorGrayscaleUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnColorRGBSliders(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnColorRGBSlidersUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnColorHSLWheel(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnColorHSLWheelUpdate(long id, UI::IUICmdUpdate* pCmdUI);
	long OnColorNamedColors(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	void OnColorNamedColorsUpdate(long id, UI::IUICmdUpdate* pCmdUI);

	long OnColorInvert(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
	long OnColorComplement(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
//	void OnDeleteSelectionUpdate(long wID, UI::IUICmdUpdate* pCmdUI);

// IEColorDlg
public:
// IEColorSite
	ErrorCode SetRGBColorValue(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue);

//	ErrorCode(SetColor)(/*[in]*/ IEColor* color);
// IUIEventHandler
//	ErrorCode(handleActivateObjectEvent)(IUnknown* object, long* cookie);
//	ErrorCode(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow);
};

}	// LXmlEdit
}

#endif //__ECOLORDLG_H_
