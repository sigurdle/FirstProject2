class CColumn
{
public:
	int m_width;
	bool m_bApply;

	_bstr_t m_tableName;
	_bstr_t m_fieldName;
	int m_sort;
	bool m_bShow;

	CColumn()
	{
		m_bApply = false;
		m_sort = 0;
		m_bShow = false;
		m_width = 160;
	}
};

class CSQLQueryFields :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CSQLQueryFields>,
	public IDropTarget
{
public:

	CSQLQueryFields()
	{
		m_npane = -1;
		m_dragging = 0;

		m_curSel = -1;
		m_startSel = -1;
		m_endSel = -1;

		for (int i = 0; i < 4; i++)
		{
			CColumn* pColumn = new CColumn;
			m_columns.Add(pColumn);
		}
	}

	int m_curSel;
	int m_startSel;
	int m_endSel;

	int m_dragging;
	int m_npane;
	POINT m_oldpt;
	int m_oldwidth;

	CArray<CColumn*,CColumn*> m_columns;

BEGIN_COM_MAP(CSQLQueryFields)
	COM_INTERFACE_ENTRY(IDropTarget)
END_COM_MAP()

BEGIN_MSG_MAP(CSQLQueryFields)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
// IDropTarget
	STDMETHOD(DragEnter)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragOver)(DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	STDMETHOD(DragLeave)();
	STDMETHOD(Drop)(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
};
