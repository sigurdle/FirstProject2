#include "ColumnDef.h"

//class CFootage;
//class CMMProject;

/////////////////////////////////////////////////////////////////////////////
// CResourceView view

class ATL_NO_VTABLE CProjectUI :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CUIDialogImpl<CProjectUI, CWindowImpl<CProjectUI> >,
	public ProcessTargetCommands
{
public:
	CComPtr<IProject> m_pPrj;

protected:

	CComPtr<IUIScrollBar>	m_vert;
	CComPtr<IUIScrollBar>	m_horz;
	CScrollBar	m_sizeGrip;

	BOOL m_dragging;
	int	m_whichPane;
	int	m_whichButton;
	CRect	m_buttonRect;
	BOOL	m_bWasInside;

	CFont	m_font;
	CBitmap	m_footageSymbol;
	CBitmap	m_expandedBitmap;
	CBitmap	m_audioBitmap;
	CBitmap	m_buttonsBitmap;

	CEdit	m_edit;

#if 0
	CWnd* m_dropWnd;
	COleDropTarget		m_dropTarget;
#endif

	int			m_numColumns;
	ColumnDef	m_column[12];
	int			m_columnOrder[12];

// Attributes
public:
	CProjectUI();
	virtual ~CProjectUI();

	void DrawColumn(CDC* pDC, CRect& rect, int nColumn);
	void DrawColumnHeader(CDC* pDC, CRect& rect, int nColumn);
	void DrawFootageInfo(CDC* pDC);

	IFootage* GetFootageUnderPoint(CPoint point);

	void EndEdit();

// Operations
public:

	void OnSize();
	void ResetVScrollSize();
	void ResetHScrollSize();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CProjectUI)
	COM_INTERFACE_ENTRY(IUIDlg)
	COM_INTERFACE_ENTRY(IUIWnd)
	COM_INTERFACE_ENTRY(ICommandTarget)
END_COM_MAP()

BEGIN_MSG_MAP(CProjectUI)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk);
//	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

//	IMETHOD BOOL OnCmdMsg(UINT nID, CICmdUIUpdate* pCmdUI);

#if 0
	IMETHOD DROPEFFECT OnDragEnter(LPDATAOBJECT lpDataObject, DWORD dwKeyState, POINT point);
	IMETHOD DROPEFFECT OnDragOver(LPDATAOBJECT lpDataObject, DWORD dwKeyState, POINT point);
	IMETHOD BOOL OnDrop(LPDATAOBJECT lpDataObject, DROPEFFECT dropEffect, POINT point);

	IMETHOD void OnDropFiles(HDROP hDropInfo);

	IMETHOD BOOL CanCloseFrame();

	IMETHOD long DispatchAction(LPCTSTR kEvent, int playInfo, int recordInfo, CIActionDescriptor* pDescr)
	{
		return SUB()->DispatchAction(kEvent, playInfo, recordInfo, pDescr);
	}

	IMETHOD void OnContextMenu(HWND hWnd, POINT point);

	IMETHOD long OnDispatchAction(LPCTSTR kEvent, int playInfo, int recordInfo, CIActionDescriptor* pDescr, CIActionDescriptor* pOutDescr)
	{
		return -1;
	}

	IMETHOD long OnTraverseDispatch(LPCTSTR kEvent, int playInfo, int recordInfo, CIActionDescriptor* pDescr)
	{
		return -1;
	}
#endif

DECLARE_CMD_MAP(CProjectUI)

	LRESULT OnEditDelete(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateEditDelete(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnResourceDuplicate(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateResourceDuplicate(long iid, IUICmdUpdate* pCmdUI);
//	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	LRESULT OnFootagepaneName(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepaneName(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFootagepanePathname(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepanePathname(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFootagepaneSize(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepaneSize(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFootagepaneType(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepaneType(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFootagepaneDuration(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepaneDuration(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnFootagepaneComment(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnUpdateFootagepaneComment(long iid, IUICmdUpdate* pCmdUI);
//	afx_msg void OnClose();
	LONG TWTransferDone(UINT, LONG);
};

