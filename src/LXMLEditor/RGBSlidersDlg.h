// RGBSlidersDlg.h : Declaration of the CRGBSlidersDlg

#ifndef __RGBSLIDERSDLG_H_
#define __RGBSLIDERSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CRGBSlidersDlg
class CRGBSlidersDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CRGBSlidersDlg>,
//	public IDispatchImpl<IRGBSlidersDlg, &IID_IRGBSlidersDlg, &LIBID_LXMLEDITORLib>,

	public UI::Control,//CUIDialogImpl<CRGBSlidersDlg, CAxDialogImpl<CRGBSlidersDlg> >,
	public IEColorPicker,
	public UI::ProcessTargetCommands	// ILDOMEventListener
//	public CUIEventHandlerImpl,
#if 0
	public IDispEventImpl<1, CRGBSlidersDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CRGBSlidersDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CRGBSlidersDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CRGBSlidersDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>
#endif
{
public:
	CRGBSlidersDlg()
	{
	}

	int FinalConstruct();
	void FinalRelease();

#if 0
	IUIColorSlider* m_slider[4];
#endif
	int m_channelValue[4];

	IEColorSite* m_site;

	enum { IDD = IDD_RGBSLIDERSDLG };

	void OnSliderPos(int channel, long nPos);

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CRGBSlidersDlg)
//	COM_INTERFACE_ENTRY(IRGBSlidersDlg)
	COM_INTERFACE_ENTRY(IEColorPicker)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CRGBSlidersDlg)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CRGBSlidersDlg)
   SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider0SetPos)
   SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider1SetPos)
   SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider2SetPos)
   SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider3SetPos)
END_SINK_MAP()
#endif
	ErrorCode __stdcall OnSlider0SetPos(long pos);
	ErrorCode __stdcall OnSlider1SetPos(long pos);
	ErrorCode __stdcall OnSlider2SetPos(long pos);
	ErrorCode __stdcall OnSlider3SetPos(long pos);

#if 0
BEGIN_MSG_MAP(CRGBSlidersDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
//	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
//	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
//	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
END_MSG_MAP()
#endif

//	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

DECLARE_CMD_MAP(CRGBSlidersDlg)

//	LRESULT OnColorInvert(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT OnColorComplement(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	void OnDeleteSelectionUpdate(long wID, IUICmdUpdate* pCmdUI);

// IRGBSlidersDlg
public:

// IEColorPicker
	ErrorCode GetSite(/*[out,retval]*/ IEColorSite* *pVal)
	{
		*pVal = m_site;
	//	if (*pVal) (*pVal)->AddRef();
		return Success;
	}
	ErrorCode SetSite(/*[in]*/ IEColorSite* newVal)
	{
		m_site = newVal;
		return Success;
	}
	ErrorCode SetRGBColorValue(/*[in]*/ long red, /*[in]*/ long green, /*[in]*/ long blue);
};

}	// LXmlEdit
}

#endif //__RGBSLIDERSDLG_H_
