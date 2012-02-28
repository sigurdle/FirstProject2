class CSQLTableWnd :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CWindowImpl<CSQLTableWnd>,
	public IUnknown
{
protected:

	class CTableColumn
	{
	public:
		_bstr_t m_name;
		bool m_bSelected;
		long m_index;

		CTableColumn()
		{
			m_bSelected = false;
		}
	};

	CArray<CTableColumn*,CTableColumn*> m_columns;
	ADOX::_TablePtr	m_table;

public:
	CSQLTableWnd()
	{
		m_selectedIndex = -1;
	}

	~CSQLTableWnd()
	{
	}

	void FinalRelease()
	{
		if (m_table != NULL)
		{
			m_table.Release();
		}
	}

	long m_selectedIndex;

	ADOX::_TablePtr GetTable()
	{
		return m_table;
	}

	void SetTable(ADOX::_TablePtr table)
	{
		m_table = table;

		for (long i = 0; i < m_table->Columns->Count; i++)
		{
			CTableColumn* column = new CTableColumn;
			column->m_name = m_table->Columns->Item[_variant_t(i)]->Name;
			column->m_index = i;

			m_columns.Add(column);
		}
	}

BEGIN_COM_MAP(CSQLTableWnd)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

BEGIN_MSG_MAP(CSQLTableWnd)
//	CHAIN_MSG_MAP(CComControl<CSQLQueryBuilder>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_MOVING, OnMoving)
	MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
	MESSAGE_HANDLER(WM_CHILDACTIVATE, OnChildActivate)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnChildActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MessageBeep(-1);
		SetWindowPos(HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		return 0;
	}
};
