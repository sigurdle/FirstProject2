// PathToolOptionsDlg.h : Declaration of the CPathToolOptionsDlg

#ifndef __PATHTOOLOPTIONSDLG_H_
#define __PATHTOOLOPTIONSDLG_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CPathToolOptionsDlg
class CPathToolOptionsDlg : 
//	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CPathToolOptionsDlg, &CLSID_PathToolOptionsDlg>,
//	public IDispatchImpl<IPathToolOptionsDlg, &IID_IPathToolOptionsDlg, &LIBID_LXMLEDITORLib>,

	public UI::Control
//	public CUIEventHandlerImpl,

//	public IDispEventImpl<2, CPathToolOptionsDlg, &DIID__IEXMLViewGroupEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CPathToolOptionsDlg()
	{
		m_app = NULL;
	}

	CLXMLEditorApp* m_app;

	enum { IDD = IDD_PATHTOOLOPTIONSDLG };

//	CComPtr<IEXMLViewGroup> m_viewGroup;


//	void __stdcall OnViewGroupSelectionChanged();

/*
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	long OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
*/

// IPathToolOptionsDlg
public:
};

}	// LXmlEdit
}

#endif //__PATHTOOLOPTIONSDLG_H_
