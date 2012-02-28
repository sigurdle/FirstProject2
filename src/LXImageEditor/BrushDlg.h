// BrushDlg.h : Declaration of the CBrushDlg

#ifndef __BRUSHDLG_H_
#define __BRUSHDLG_H_

#include "resource.h"       // main symbols

class CBrushDlg : 
//	public CComCoClass<CBrushDlg, &CLSID_BrushDlg>,
//	public IDispatchImpl<IBrushDlg, &IID_IBrushDlg, &LIBID_WEBEDITORLib>,

	public Control,
	public CUIEventHandlerImpl,

//	public IDispEventImpl<1, CBrushDlg, &DIID__IEXMLViewGroupEvents, &LIBID_WEBEDITORLib, 1, 0>
	public IDispEventImpl<1, CBrushDlg, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:
	CBrushDlg()
	{
	}

	int FinalConstruct();
	void FinalRelease();

//	enum { IDD = IDD_BRUSHDLG };

	CRect m_areaRect;

	CAxWindow m_axvert;
	CComQIPtr<IUIScrollBar> m_vert;


	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//	LRESULT OnBrushSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

};

#endif //__BRUSHDLG_H_
