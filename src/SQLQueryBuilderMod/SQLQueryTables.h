class CSQLTableWnd;

class CSQLQueryTables :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CSQLQueryTables>,
	public IUnknown

{
public:

	CArray<CComObject<CSQLTableWnd>*,CComObject<CSQLTableWnd>*> m_tables;

	void AddTable(ADOX::_TablePtr table);

BEGIN_COM_MAP(CSQLQueryTables)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

BEGIN_MSG_MAP(CSQLQueryTables)
//	CHAIN_MSG_MAP(CComControl<CSQLQueryBuilder>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
/*	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
*/
MESSAGE_HANDLER(WM_PAINT, OnPaint)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};


class CSQLQueryTablesScroll :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CSQLQueryTablesScroll>,

	public IUnknown,

	public IDispEventImpl<1, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>,
	public IDispEventImpl<2, CSQLQueryTablesScroll, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>
{
public:

	CSQLQueryTablesScroll()
	{
		m_wnd = NULL;
	}

	int FinalConstruct()
	{
		m_horz.CoCreateInstance(CLSID_UIScrollBar);
		m_horz->put_direction(0);

		m_vert.CoCreateInstance(CLSID_UIScrollBar);
		m_vert->put_direction(1);

		return S_OK;
	}

	void FinalRelease()
	{
	}

	CComObject<CSQLQueryTables>* m_wnd;

	CAxWindow m_axvert;
	CComQIPtr<IUIScrollBar> m_vert;

	CAxWindow m_axhorz;
	CComQIPtr<IUIScrollBar> m_horz;

	void OnSize();

BEGIN_COM_MAP(CSQLQueryTablesScroll)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

BEGIN_SINK_MAP(CSQLQueryTablesScroll)
   SINK_ENTRY_EX(1, DIID__IUIScrollBarEvents, /*dispid*/1, OnHorzScroll)
   SINK_ENTRY_EX(2, DIID__IUIScrollBarEvents, /*dispid*/1, OnVertScroll)
END_SINK_MAP()

	HRESULT __stdcall OnHorzScroll(long code, long pos);
	HRESULT __stdcall OnVertScroll(long code, long pos);

BEGIN_MSG_MAP(CSQLQueryTablesScroll)
//	CHAIN_MSG_MAP(CComControl<CSQLQueryBuilder>)
	DEFAULT_REFLECTION_HANDLER()
//	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};
