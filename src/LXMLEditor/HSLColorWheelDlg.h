// HSLColorWheelDlg.h : Declaration of the CHSLColorWheelDlg

#ifndef __HSLCOLORWHEELDLG_H_
#define __HSLCOLORWHEELDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CHSLColorWheelDlg
class CHSLColorWheelDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CHSLColorWheelDlg>,
//	public IDispatchImpl<IHSLColorWheelDlg, &IID_IHSLColorWheelDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,//CUIDialogImpl<CHSLColorWheelDlg, CAxDialogImpl<CHSLColorWheelDlg> >,
	public IEColorPicker,
	public UI::ProcessTargetCommands	// ILDOMEventListener
//	public CUIEventHandlerImpl,

/*
	public IDispEventImpl<1, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CHSLColorWheelDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>
*/
{
public:
	CHSLColorWheelDlg()
	{
	}

	int FinalConstruct();
	void FinalRelease();

#if 0
	IUIHSLColorWheel* m_colorWheel;
#endif
	int m_channelValue[3];

	IEColorSite* m_site;

	enum { IDD = IDD_HSLCOLORWHEELDLG };

	void OnSliderPos(int channel, long nPos);
//	void UpdateSliders();

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CHSLColorWheelDlg)
//	COM_INTERFACE_ENTRY(IHSLColorWheelDlg)
	COM_INTERFACE_ENTRY(IEColorPicker)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ILDOMEventListener)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CHSLColorWheelDlg)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CHSLColorWheelDlg)
   SINK_ENTRY_EX(1, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider0SetPos)
   SINK_ENTRY_EX(2, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider1SetPos)
   SINK_ENTRY_EX(3, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider2SetPos)
   SINK_ENTRY_EX(4, DIID__IUIColorSliderEvents, /*dispid*/1, OnSlider3SetPos)
END_SINK_MAP()
#endif

/*
	HRESULT __stdcall OnSlider0SetPos(long pos);
	HRESULT __stdcall OnSlider1SetPos(long pos);
	HRESULT __stdcall OnSlider2SetPos(long pos);
	HRESULT __stdcall OnSlider3SetPos(long pos);
*/
//	void __stdcall OnColorChanged();

//	HRESULT __stdcall OnDOMEvent(ILDOMEvent* evt);

//	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
//	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

DECLARE_CMD_MAP(CHSLColorWheelDlg)

// IHSLColorWheelDlg
public:

// IEColorPicker
	ErrorCode GetSite(/*[out,retval]*/ IEColorSite* *pVal)
	{
		*pVal = m_site;
		//if (*pVal) (*pVal)->AddRef();
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

#endif //__HSLCOLORWHEELDLG_H_
