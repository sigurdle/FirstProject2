class CWSSrv;

//#import "..\DOMCOREMODLib\DOMCOREMODLib.tlb" raw_interfaces_only

class CSiteItem
{
public:
	BYTE m_type;
	BYTE m_bFoundOnDisk;
	DWORD	m_dbid;
	CSiteItem* m_parent;
	CWSSrv* m_pWebSite;
	WIN32_FIND_DATA	m_wfd;

	CSiteItem()
	{
		m_pWebSite = NULL;
		m_dbid = 0;
		m_parent = NULL;
		memset(&m_wfd, 0, sizeof(m_wfd));
	}

	virtual ~CSiteItem()
	{
	}
	
	void AddSiteItemToDatabase();
	void UpdateDatabase();

	CUString GetFullPathName();

//	virtual CUString GetFullPathName() = 0;
	virtual void RemoveFromDatabase();
};

class CSiteDir : public CSiteItem
{
public:
	CSiteDir();
	virtual ~CSiteDir();

	DWORD m_dwChangeThreadID;
	HANDLE m_hChangeThread;

//	CUString	m_pathName;

	CUPtrList m_childList;
	UPOSITION AddChildTail(CSiteItem* pChild)
	{
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);
		return pos;
	}

	void ScanFiles(BOOL bCheckExisting = FALSE, BOOL bUpdateDB = FALSE, BOOL bRecursive = TRUE, CSiteItem** pActive = NULL);
	void ScanFTPFiles(BOOL bCheckExisting = FALSE);

	void ListenToChanges();

	CSiteItem* FileExists(LPCTSTR pathname, int type);
	CSiteItem* FindFilePathName(LPCTSTR pathName, int type);
	CSiteItem* FindItemByID(DWORD id, int type);

	void QuitFileThread();
	void UpdateOutLinks();
	void BuildFromDatabase();

	virtual void RemoveFromDatabase();
/*
	virtual CUString GetFullPathName()
	{
		return m_pathName;
	}
*/
};

class CSiteFile : public CSiteItem
{
public:
	DWORD m_ownerDocument_id;

	CSiteFile()
	{
		m_type = 2;
		m_ownerDocument_id = 0;
	}

	void UpdateOutLinks();
	void SaveDOMElementToDatabase(ILDOMElement* parent, int parentNode_id, int index);

	virtual void RemoveFromDatabase();
/*
virtual CUString GetFullPathName()

	{
		CSiteDir* pDir = (CSiteDir*)m_parent;

		TCHAR pathName[_MAX_PATH];
		_makepath(pathName, NULL, pDir->GetFullPathName(), m_wfd.cFileName, NULL);

		return pathName;
	}
	*/
};
