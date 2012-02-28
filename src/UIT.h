//#include "..\UI\UI.h"

//#import "C:\MMStudio\Extras\UI\UI.tlb" raw_interfaces_only, raw_native_types, no_namespace, named_guids	//"Import typelib"

#pragma once

// TODO, Delete this file
#if 0
//
// Forward references and typedefs
//

struct __declspec(uuid("1bc5e2ec-5345-11d5-95f0-ed386645315a"))
/* interface */ IUIWnd;
struct __declspec(uuid("1bb4f475-1f4f-49cb-8ae3-13c785fc3004"))
/* interface */ IUIFrame;
struct __declspec(uuid("845b76e4-edd3-454c-aafa-a98ad0bf08dc"))
/* dual interface */ IMenuItem;
struct __declspec(uuid("6e44d980-3e56-4c03-a869-6b422b06a95e"))
/* dual interface */ IUIMenuDlg;
struct __declspec(uuid("c801152b-af9e-4006-ae61-59ff75b2c3b9"))
/* interface */ ICommandTarget;
struct __declspec(uuid("19741e30-50a7-46c0-953d-d24f679b1eb2"))
/* interface */ IUICmdUpdate;
struct __declspec(uuid("fbf9880a-080a-41a3-8e67-8aebc9a5511c"))
/* interface */ IUIDlg;
struct __declspec(uuid("16f080a4-ba3b-4e40-a140-ea9e4fbf5b1f"))
/* interface */ IUIDlgSheet;
struct __declspec(uuid("f4a86042-ed11-11d5-95f0-0002e3045703"))
/* interface */ IUIEventHandler;
struct __declspec(uuid("15cc6d5e-8807-4df9-b2a8-ddab3cb9bd85"))
/* dual interface */ IUIMenuBar;
struct __declspec(uuid("23800541-1c8c-11d6-95f0-0002e3045703"))
/* interface */ IUIDockBar;
#if 0
struct __declspec(uuid("078dcf3d-e8c5-4aa1-8d1d-e395bf2838a2"))
/* interface */ IUIMDIChild;
#endif
struct __declspec(uuid("1bc5e2ef-5345-11d5-95f0-ed386645315a"))
/* interface */ IUIMDIFrame;
struct __declspec(uuid("39D4DDBB-65DD-443c-A0C4-B4DB2C79B410"))
/* interface */ IUIDlgSite;
struct __declspec(uuid("C2CE0F34-B8F2-4ed1-AEEC-083A98E601C8"))
/* interface */ IUIToolbarDlg;

struct __declspec(uuid("1bc5e2ec-5345-11d5-95f0-ed386645315a"))
IUIWnd : IUnknown
{
	//
	// Raw methods provided by interface
	//
	
	virtual HRESULT __stdcall get_hwnd (HWND *pVal) = 0;
	virtual HRESULT __stdcall DestroyWindow () = 0;
	virtual HRESULT __stdcall ShowWindow (unsigned int nCmdShow) = 0;
};

struct __declspec(uuid("1bb4f475-1f4f-49cb-8ae3-13c785fc3004"))
IUIFrame : IUIWnd
{
    //
    // Raw methods provided by interface
    //

#if 0
	virtual HRESULT __stdcall get_menu (     struct IMenuItem * * pVal ) = 0;
#endif

//	virtual HRESULT __stdcall get_margins (     struct tagRECT * pVal ) = 0;
//	virtual HRESULT __stdcall put_margins (     struct tagRECT pVal ) = 0;
#if 0	// Test without
	virtual HRESULT __stdcall get_menuBar (     struct IUIMenuBar * * pVal ) = 0;
#endif
	virtual HRESULT __stdcall RecalcLayout ( ) = 0;
#if 0	// Test without
	virtual HRESULT __stdcall FloatControlBar (struct IUIDlgSite *pBar, struct tagPOINT point,unsigned long dwStyle ) = 0;
#endif
	virtual HRESULT __stdcall DockControlBar(struct IUIDlgSite *pBar, UINT nDockBarID/*=0*/, RECT *lpRect/*=NULL*/) = 0;
	virtual HRESULT __stdcall CanDock (  struct tagRECT rect, unsigned long dwDockStyle, struct IUIDockBar * * ppDockBar, unsigned long * pVal ) = 0;
	/*
	virtual HRESULT __stdcall RemoveDlgSheet(IUIDlgSheet * sheet ) = 0;
	virtual HRESULT __stdcall AddDlgSheet(IUIDlgSheet* sheet) = 0;
	*/
};

struct __declspec(uuid("1bc5e2ef-5345-11d5-95f0-ed386645315a"))
IUIMDIFrame : IUIFrame
{
    //
    // Raw methods provided by interface
    //
#if 0
	virtual HRESULT __stdcall WindowControlBar (struct IUIDlgSite *pBar, struct tagPOINT point ) = 0;
 	virtual HRESULT __stdcall CreateChildFrameDlgSite(IUIDlgSite* dlgSite, IUIMDIChild* *pVal) = 0;
// 	virtual HRESULT __stdcall CreateChildFrame(IUIMDIChild* *pVal) = 0;
#endif
	virtual HRESULT __stdcall get_hMDIClient(HWND *pVal ) = 0;
};

struct __declspec(uuid("845b76e4-edd3-454c-aafa-a98ad0bf08dc"))
IMenuItem : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall PopupMenu (struct ICommandTarget * pTarget,
        struct tagPOINT point,
        unsigned long flags,
        long * result ) = 0;
};

struct __declspec(uuid("c801152b-af9e-4006-ae61-59ff75b2c3b9"))
ICommandTarget : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall OnCmdMsg (
        long nID,
        long nCode,
        IUICmdUpdate * pCmdUI,
        BOOL * bHandled ) = 0;
};

/*
struct __declspec(uuid("19741e30-50a7-46c0-953d-d24f679b1eb2"))
IUICmdUpdate : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_dlg (struct IUIMenuDlg * * pVal ) = 0;
    virtual HRESULT __stdcall put_dlg (struct IUIMenuDlg * pVal ) = 0;
    virtual HRESULT __stdcall get_menuItem (struct IMenuItem * * pVal ) = 0;
    virtual HRESULT __stdcall put_menuItem (struct IMenuItem * pVal ) = 0;
    virtual HRESULT __stdcall get_controlItem (IUnknown * * pVal ) = 0;
    virtual HRESULT __stdcall put_controlItem (IUnknown * pVal ) = 0;
    virtual HRESULT __stdcall get_hwndControl (HWND * pVal ) = 0;
    virtual HRESULT __stdcall put_hwndControl (HWND pVal ) = 0;
    virtual HRESULT __stdcall Enable (BOOL bEnable ) = 0;
    virtual HRESULT __stdcall SetText (BSTR text ) = 0;
    virtual HRESULT __stdcall SetCheck (BOOL bCheck ) = 0;
};
*/

struct __declspec(uuid("fbf9880a-080a-41a3-8e67-8aebc9a5511c"))
IUIDlg : IUIWnd
{
    //
    // Raw methods provided by interface
    //

	virtual DWORD GetBarStyle() = 0;
	virtual void SetBarStyle(DWORD dwStyle) = 0;
	virtual HRESULT __stdcall GetDlgSite(IUIDlgSite* *pVal) = 0;
	virtual HRESULT __stdcall SetDlgSite(IUIDlgSite* newVal) = 0;
	virtual HRESULT __stdcall Create(HWND hWndParent) = 0;
	virtual HRESULT __stdcall OnActivate (BOOL bActivate, IUIDlg * pActivateView, IUIDlg * pDeactivateView ) = 0;
	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode) = 0;
	virtual HRESULT __stdcall CalcLayout (unsigned long dwMode, long nLength, SIZE * pVal ) = 0;
	virtual HRESULT __stdcall OnDragOut(IUIDockBar* dockBar) = 0;
	virtual HRESULT __stdcall OnDlgClose() = 0;
	virtual HRESULT __stdcall OnFrameActivate(long fActive) = 0;
};

struct __declspec(uuid("39D4DDBB-65DD-443c-A0C4-B4DB2C79B410"))
IUIDlgSite : IUnknown
#if 0
 : IUIWnd
#endif
{
public:

	DWORD m_dwDockStyle;
	IUIDockBar* m_pDockBar;
	IUIFrame* m_pDockSite;

	DWORD m_dwMRUFloatStyle;
	CPoint m_ptMRUFloatPos;
	CRect m_rectMRUDockPos;

	virtual void SetMRUWidth(int value) = 0;
	virtual int GetMRUWidth() = 0;

	virtual HRESULT __stdcall GetDockSite(IUIFrame* *pVal) = 0;
	virtual HRESULT __stdcall SetDockSite(IUIFrame* newVal) = 0;

	virtual DWORD GetBarStyle() = 0;
	virtual void SetBarStyle(DWORD dwStyle) = 0;
	virtual HRESULT __stdcall GetDlg(IUIDlg* *pVal) = 0;

	virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode) = 0;
//	virtual HRESULT __stdcall CalcLayout (unsigned long dwMode, long nLength, SIZE * pVal ) = 0;

	virtual HRESULT __stdcall IsVisible () = 0;
};

#if 0
struct __declspec(uuid("16f080a4-ba3b-4e40-a140-ea9e4fbf5b1f"))
IUIDlgSheet : IUIDlg
{
    //
    // Raw methods provided by interface
    //
	virtual HRESULT __stdcall AddDialog (struct IUIDlg * pSheet) = 0;

//    virtual HRESULT __stdcall Dock (short side,long x,long y ) = 0;	// TODO remove
//    virtual HRESULT __stdcall GetDocked (short * side ) = 0;	// TODO remove
//    virtual HRESULT __stdcall get_canGroup (BOOL * pVal ) = 0;	// TODO remove
//    virtual HRESULT __stdcall put_canGroup (BOOL newVal ) = 0;	// TODO remove
	virtual HRESULT __stdcall GetTabbed(BOOL *pVal) = 0;
	virtual HRESULT __stdcall SetTabbed(BOOL newVal) = 0;
	virtual HRESULT __stdcall ShowTabs(BOOL bShow) = 0;
	//virtual HRESULT __stdcall SetTabbed(BOOL newVal) = 0;
	virtual HRESULT __stdcall GetMinimized(BOOL *pVal) = 0;
	virtual HRESULT __stdcall SetMinimized(BOOL newVal) = 0;

	virtual HRESULT __stdcall GetPageCount(long *pVal) = 0;
	virtual HRESULT __stdcall GetPage(long index, IUIDlgSite* *pVal) = 0;
	virtual HRESULT __stdcall SetActivePage(IUIDlgSite* dlgSite) = 0;
};
#endif

struct __declspec(uuid("6e44d980-3e56-4c03-a869-6b422b06a95e"))
IUIMenuDlg : IUIDlg
{
    //
    // Raw methods provided by interface
    //

	virtual HRESULT __stdcall get_menuItem (struct IMenuItem * * pVal ) = 0;
	virtual HRESULT __stdcall CreateForMenuItem (struct IMenuItem * menuItem,HWND hParent,struct ICommandTarget * pCmdWnd, unsigned long orientation ) = 0;
	virtual HRESULT __stdcall GetItemRect (struct IMenuItem * item,struct tagRECT * rect ) = 0;
#if 0
	virtual HRESULT __stdcall InitMenu(IMenuItem* menuItem, ICommandTarget* target, int orientation) = 0;
#endif
};

struct __declspec(uuid("C2CE0F34-B8F2-4ed1-AEEC-083A98E601C8"))
IUIToolbarDlg : IUIDlg
{
    //
    // Raw methods provided by interface
    //
	virtual HRESULT __stdcall SetCommandTarget(ICommandTarget* pCmdTarget) = 0;
	virtual HRESULT __stdcall SetImageList(HIMAGELIST hImageList) = 0;
	virtual HRESULT __stdcall AddButton(long idCommand, long bitmapIndex, BSTR text) = 0;
	virtual HRESULT __stdcall SetButtonState(long idCommand, DWORD fsState) = 0;
};

struct __declspec(uuid("23800541-1c8c-11d6-95f0-0002e3045703"))
IUIDockBar : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_hwnd(HWND *pVal) = 0;
#if 0
   virtual HRESULT __stdcall DockControlBar(IUIDlgSite *pBar, RECT *lpRect) = 0;
   virtual HRESULT __stdcall RemoveControlBar(IUIDlgSite *pBar) = 0;
#endif
//    virtual HRESULT __stdcall Show(BOOL bShow) = 0;
//    virtual HRESULT __stdcall RecalcLayout() = 0;
    virtual HRESULT __stdcall CanDock(IUIDlgSite* pBar) = 0;
};

#if 0
struct __declspec(uuid("078dcf3d-e8c5-4aa1-8d1d-e395bf2838a2"))
IUIMDIChild : IUIFrame
{
    //
    // Raw methods provided by interface
    //

	/*
    virtual HRESULT __stdcall AddPage (
        struct IUIDlg * view,
        long * pindex ) = 0;
    virtual HRESULT __stdcall RemoveView (
        struct IUIDlg * view ) = 0;
    virtual HRESULT __stdcall RemoveTabIndex (
        long index ) = 0;
    virtual HRESULT __stdcall SetActiveTabIndex (
        long index ) = 0;
		  */
};
#endif

/*
struct __declspec(uuid("D7445CC1-664B-4dee-9959-878A4AEE8FB8"))
IUIViewSheet : IUIDlg
{
	virtual HRESULT __stdcall GetPageCount(long *pVal) = 0;
	virtual HRESULT __stdcall GetPage(long index, IUIDlgSite* *pVal) = 0;
	virtual HRESULT __stdcall SetActivePage(IUIDlgSite* dlgSite) = 0;
};
*/

#if 0	// Removed
struct __declspec(uuid("8C7B37AC-A11A-4b4c-8AF6-A07363FF3ED1"))
IEViewGroup : IUnknown
{
	virtual HRESULT __stdcall OnDlgActivate(BOOL bActive) = 0;
	virtual HRESULT __stdcall OnDlgClose() = 0;
	virtual HRESULT __stdcall OnDetachTab(IUIDlgSite* pDlgSite) = 0;
};
#endif

extern "C" const GUID __declspec(selectany) IID_IUIWnd =
    {0x1bc5e2ec,0x5345,0x11d5,{0x95,0xf0,0xed,0x38,0x66,0x45,0x31,0x5a}};
extern "C" const GUID __declspec(selectany) IID_IUIFrame =
    {0x1bb4f475,0x1f4f,0x49cb,{0x8a,0xe3,0x13,0xc7,0x85,0xfc,0x30,0x04}};
extern "C" const GUID __declspec(selectany) IID_IMenuItem =
    {0x845b76e4,0xedd3,0x454c,{0xaa,0xfa,0xa9,0x8a,0xd0,0xbf,0x08,0xdc}};
extern "C" const GUID __declspec(selectany) IID_IUIMenuDlg =
    {0x6e44d980,0x3e56,0x4c03,{0xa8,0x69,0x6b,0x42,0x2b,0x06,0xa9,0x5e}};
extern "C" const GUID __declspec(selectany) IID_ICommandTarget =
    {0xc801152b,0xaf9e,0x4006,{0xae,0x61,0x59,0xff,0x75,0xb2,0xc3,0xb9}};
extern "C" const GUID __declspec(selectany) IID_IUICmdUpdate =
    {0x19741e30,0x50a7,0x46c0,{0x95,0x3d,0xd2,0x4f,0x67,0x9b,0x1e,0xb2}};
extern "C" const GUID __declspec(selectany) IID_IUIDlg =
    {0xfbf9880a,0x080a,0x41a3,{0x8e,0x67,0x8a,0xeb,0xc9,0xa5,0x51,0x1c}};
//extern "C" const GUID __declspec(selectany) IID_IUIDlgSheet =
//    {0x16f080a4,0xba3b,0x4e40,{0xa1,0x40,0xea,0x9e,0x4f,0xbf,0x5b,0x1f}};
extern "C" const GUID __declspec(selectany) IID_IUIEventHandler =
    {0xf4a86042,0xed11,0x11d5,{0x95,0xf0,0x00,0x02,0xe3,0x04,0x57,0x03}};
extern "C" const GUID __declspec(selectany) IID_IUIMenuBar =
    {0x15cc6d5e,0x8807,0x4df9,{0xb2,0xa8,0xdd,0xab,0x3c,0xb9,0xbd,0x85}};
extern "C" const GUID __declspec(selectany) IID_IUIDockBar =
    {0x23800541,0x1c8c,0x11d6,{0x95,0xf0,0x00,0x02,0xe3,0x04,0x57,0x03}};

#if 0
extern "C" const GUID __declspec(selectany) IID_IUIMDIChild =
    {0x078dcf3d,0xe8c5,0x4aa1,{0x8d,0x1d,0xe3,0x95,0xbf,0x28,0x38,0xa2}};
#endif

extern "C" const GUID __declspec(selectany) IID_IUIMDIFrame =
    {0x1bc5e2ef,0x5345,0x11d5,{0x95,0xf0,0xed,0x38,0x66,0x45,0x31,0x5a}};

/////////////////////////////////////////////////////////////////////////////
// General style bits etc

// ControlBar styles
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
//#define CBRS_FLYBY          0x0020L
#define CBRS_STRETCH        0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define CBRS_GRIPPER        0x00400000L

#define CBRS_ORIENT_HORZ    (CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)
#define CBRS_ORIENT_VERT    (CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ORIENT_ANY     (CBRS_ORIENT_HORZ|CBRS_ORIENT_VERT)

#define CBRS_ALL            0x0040FFFFL

// the CBRS_ style is made up of an alignment style and a draw border style
//  the alignment styles are mutually exclusive
//  the draw border styles may be combined
#define CBRS_NOALIGN        0x00000000L
#define CBRS_LEFT           (CBRS_ALIGN_LEFT|CBRS_BORDER_RIGHT)
#define CBRS_TOP            (CBRS_ALIGN_TOP|CBRS_BORDER_BOTTOM)
#define CBRS_RIGHT          (CBRS_ALIGN_RIGHT|CBRS_BORDER_LEFT)
#define CBRS_BOTTOM         (CBRS_ALIGN_BOTTOM|CBRS_BORDER_TOP)

// Note: If your application supports docking toolbars, you should
//  not use the following IDs for your own toolbars.  The IDs chosen
//  are at the top of the first 32 such that the bars will be hidden
//  while in print preview mode, and are not likely to conflict with
//  IDs your application may have used succesfully in the past.

#define AFX_IDW_DOCKBAR_TOP             0xE81B
#define AFX_IDW_DOCKBAR_LEFT            0xE81C
#define AFX_IDW_DOCKBAR_RIGHT           0xE81D
#define AFX_IDW_DOCKBAR_BOTTOM          0xE81E
#define AFX_IDW_DOCKBAR_FLOAT           0xE81F

// Layout Modes for CalcDynamicLayout
#define LM_STRETCH  0x01    // same meaning as bStretch in CalcFixedLayout.  If set, ignores nLength
							// and returns dimensions based on LM_HORZ state, otherwise LM_HORZ is used
							// to determine if nLength is the desired horizontal or vertical length
							// and dimensions are returned based on nLength
#define LM_HORZ     0x02    // same as bHorz in CalcFixedLayout
#define LM_MRUWIDTH 0x04    // Most Recently Used Dynamic Width
#define LM_HORZDOCK 0x08    // Horizontal Docked Dimensions
#define LM_VERTDOCK 0x10    // Vertical Docked Dimensions
#define LM_LENGTHY  0x20    // Set if nLength is a Height instead of a Width
#define LM_COMMIT   0x40    // Remember MRUWidth

#define HORZF(dw) (dw & CBRS_ORIENT_HORZ)
#define VERTF(dw) (dw & CBRS_ORIENT_VERT)

#include "UIDialog.h"
#include "CmdHandler.h"

#endif