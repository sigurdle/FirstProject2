// NamedColorsDlg.h : Declaration of the CNamedColorsDlg

#ifndef __NAMEDCOLORSDLG_H_
#define __NAMEDCOLORSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CNamedColorsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public IConnectionPointContainerImpl<CNamedColorsDlg>,
//	public IDispatchImpl<INamedColorsDlg, &IID_INamedColorsDlg, &LIBID_LXMLEDITORLib>,

public UI::Control,
//	public CUIDialogImpl<CNamedColorsDlg, CWindowImpl<CNamedColorsDlg> >,
	public IEColorPicker
//	public ProcessTargetCommands
//	public CUIEventHandlerImpl,
//	public IDispEventImpl<1, CNamedColorsDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>

/*
	public IDispEventImpl<1, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<3, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<4, CNamedColorsDlg, &DIID__IUIColorSliderEvents, &LIBID_UILib, 1, 0>
*/
{
public:
	CNamedColorsDlg()
	{
		m_index = -1;
	}

	int FinalConstruct();
	void FinalRelease();

//	CComPtr<IUIHSLColorWheel> m_colorWheel;
//	int m_channelValue[3];

	LDraw::BBoxi m_areaRect;

//	CAxWindow m_axvert;
//	CComPtr<IUIScrollBar> m_vert;

	IEColorSite* m_site;

//	UI::ScrollBar * m_scroll;

	LDraw::Color m_color;
	int m_index;

//	enum { IDD = IDD_NamedColorsDlg };

//	void OnSliderPos(int channel, long nPos);
//	void UpdateSliders();

	int FindClosest(LDraw::Color clr);

#if 0
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNamedColorsDlg)
//	COM_INTERFACE_ENTRY(INamedColorsDlg)
	COM_INTERFACE_ENTRY(IEColorPicker)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
//	COM_INTERFACE_ENTRY(ICommandTarget)
//	COM_INTERFACE_ENTRY(IUIEventHandler)
//	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
#endif
/*
BEGIN_CONNECTION_POINT_MAP(CNamedColorsDlg)
END_CONNECTION_POINT_MAP()
*/
#if 0
BEGIN_SINK_MAP(CNamedColorsDlg)
//   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()
#endif
	void __stdcall OnVertScroll(long code, long pos);

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
*/

//DECLARE_CMD_MAP(CNamedColorsDlg)

// INamedColorsDlg
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

#endif //__NAMEDCOLORSDLG_H_
