// WebSite.h : Declaration of the CWebSite

#ifndef __WEBSITE_H_
#define __WEBSITE_H_

#include "resource.h"       // main symbols

#include "item.h"

class CWebSite;

class CSiteItem// : public C2Obj
{
public:
	int m_type;

	CSiteItem()
	{
		m_pWebSite = NULL;
		m_dbid = 0;
	}
	
	CSiteItem* m_parent;
	CUPtrList m_childList;
	UPOSITION AddChildTail(CSiteItem* pChild)
	{
		pChild->m_parent = this;
		UPOSITION pos = m_childList.AddTail(pChild);
		return pos;
	}

	BOOL	m_bFoundOnDisk;
	DWORD	m_dbid;

	CWebSite* m_pWebSite;
	WIN32_FIND_DATA	m_wfd;

	void DeselectAll();

	void AddSiteItemToDatabase();
	void UpdateDatabase();

	virtual CUString GetFullPathName() = 0;
};

class CSiteDir : public CSiteItem
{
public:
	CSiteDir()
	{
		m_type = 1;
	}

	CUString	m_pathName;

	void ScanFiles(BOOL bCheckExisting = FALSE, BOOL bUpdateDB = FALSE, CSiteItem** pActive = NULL);
	void ScanFTPFiles(BOOL bCheckExisting = FALSE);

	CSiteItem* FileExists(LPCTSTR pathname, int type);

	CSiteItem* FindFilePathName(LPCTSTR pathName, int type);

	CSiteItem* FindItemByID(DWORD id, int type);

	void UpdateOutLinks();

	void BuildFromDatabase();

	virtual CUString GetFullPathName()
	{
		return m_pathName;
	}

};

class CSiteFile : public CSiteItem
{
public:
	CSiteFile()
	{
		m_type = 2;

		m_ownerDocument_id = 0;
	}

	DWORD m_ownerDocument_id;

	void UpdateOutLinks();
	void SaveDOMElementToDatabase(IDOMElement* parent, int parentNode_id, int index);

//	void UpdateDatabase();
	void RemoveFromDatabase();

	virtual CUString GetFullPathName()
	{
		CSiteDir* pDir = (CSiteDir*)m_parent;

		TCHAR pathName[_MAX_PATH];
		_makepath(pathName, NULL, pDir->m_pathName, m_wfd.cFileName, NULL);

		return pathName;
	}
};

#include "CmdHandler.h"
#include "WebEditorCP.h"

/////////////////////////////////////////////////////////////////////////////
// CWebSite
class ATL_NO_VTABLE CWebSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWebSite, &CLSID_WebSite>,
	public IConnectionPointContainerImpl<CWebSite>,
	public IDispatchImpl<IWebSite, &IID_IWebSite, &LIBID_WEBEDITORLib>,
	public ProcessTargetCommands,
	public CProxy_IWebSiteEvents< CWebSite >
{
public:
	CWebSite()
	{
		m_pRootDir = NULL;
		m_dwChangeThreadID = 0L;
		m_hChangeThread = NULL;

		m_pFTPRootDir = NULL;
		m_hInternet = NULL;
		m_hInternetFtp = NULL;

		m_homepageFileID = 0L;
		m_pFileHomepage = NULL;
	}

	void FinalRelease();

// File system
	CSiteDir* m_pRootDir;
	DWORD m_dwChangeThreadID;
	HANDLE m_hChangeThread;
	_bstr_t	m_rootPath;

// FTP files
	CSiteDir* m_pFTPRootDir;
	HINTERNET m_hInternet;
	HINTERNET m_hInternetFtp;

//
	CSiteFile* m_pFileHomepage;
	DWORD m_homepageFileID;

	_bstr_t m_ftpServerName;
	_bstr_t m_ftpDirectory;
	_bstr_t m_ftpUsername;
	_bstr_t m_ftpPassword;

//	CComQIPtr<ISiteFilesView> m_filesView;

	ADODB::_ConnectionPtr m_siteDataConnection;
	WCHAR m_connstr[512];

	void QuitFileThread();
	void ScanFiles();
	void GetHomepageFileIdFromDB();

	void CreateTable_websettings(ADOX::_CatalogPtr catalog);
	void CreateTable_files(ADOX::_CatalogPtr catalog);
	void CreateTable_links(ADOX::_CatalogPtr catalog);
	void CreateTable_tasks(ADOX::_CatalogPtr catalog);

DECLARE_REGISTRY_RESOURCEID(IDR_WEBSITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWebSite)
	COM_INTERFACE_ENTRY(IWebSite)
	COM_INTERFACE_ENTRY2(IDispatch, IWebSite)
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CWebSite)
CONNECTION_POINT_ENTRY(DIID__IWebSiteEvents)
END_CONNECTION_POINT_MAP()

	DECLARE_CMD_MAP(CWebSite)

	void OnRescan(GUID* iid);

	void OnFTPConnect(GUID* iid);
	void OnFTPDisconnect(GUID* iid);

// IWebSite
public:
	STDMETHOD(GetHomepageFileId)(/*[out,retval]*/ unsigned long* file_id);
	STDMETHOD(SetHomepageFileId)(/*[in]*/ unsigned long file_id);
	STDMETHOD(get_ftpPassword)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpPassword)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpUsername)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpUsername)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpDirectory)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpDirectory)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ftpServerName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ftpServerName)(/*[in]*/ BSTR newVal);
	STDMETHOD(LoadDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ BOOL* success);
	STDMETHOD(ShowViews)();
	STDMETHOD(get_rootPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_rootPath)(/*[in]*/ BSTR newVal);
};

#endif //__WEBSITE_H_
