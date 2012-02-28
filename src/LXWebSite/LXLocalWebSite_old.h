// LXLocalWebSite.h : Declaration of the CLXLocalWebSite

#ifndef __LXLOCALWEBSITE_H_
#define __LXLOCALWEBSITE_H_

#include "resource.h"       // main symbols
#include "LXWebSiteCP.h"

/////////////////////////////////////////////////////////////////////////////
// CLXLocalWebSite
class ATL_NO_VTABLE CLXLocalWebSite : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXLocalWebSite, &CLSID_LXLocalWebSite>,
	public IConnectionPointContainerImpl<CLXLocalWebSite>,
	public IDispatchImpl<ILXLocalWebSite, &IID_ILXLocalWebSite, &LIBID_LXWEBSITELib>,
	public CProxy_ILXLocalWebSiteEvents< CLXLocalWebSite >
{
public:
	CLXLocalWebSite()
	{
		m_homepageFileID = 0L;
	}

	void FinalRelease();

//	_bstr_t	m_rootPath;
//	CSiteDir* m_pRootDir;

	ADODB::_ConnectionPtr m_siteDataConnection;
	WCHAR m_connstr[512];


//	ADODB::_RecordsetPtr m_rsFiles;

	DWORD m_homepageFileID;

	void ScanFiles();
	HRESULT GetHomepageFileIdFromDB();
	_bstr_t GetFolderDisplayPathRecursive(DWORD folder_id, WCHAR* pathDelimiter);

	DWORD AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date);

	HRESULT RemoveFileFromDatabase(DWORD parent_id, DWORD id);

	void CreateTable_websettings(ADOX::_CatalogPtr catalog);
	void CreateTable_files(ADOX::_CatalogPtr catalog);
	void CreateTable_files_data(ADOX::_CatalogPtr catalog);
	void CreateTable_links(ADOX::_CatalogPtr catalog);
	void CreateTable_tasks(ADOX::_CatalogPtr catalog);

DECLARE_REGISTRY_RESOURCEID(IDR_LXLOCALWEBSITE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXLocalWebSite)
	COM_INTERFACE_ENTRY(ILXLocalWebSite)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CLXLocalWebSite)
CONNECTION_POINT_ENTRY(DIID__ILXLocalWebSiteEvents)
END_CONNECTION_POINT_MAP()


// ILXLocalWebSite
public:
	STDMETHOD(RenameFile)(/*[in]*/ DWORD file_id, /*[in]*/ BSTR name, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(CreateFolder)(/*[in]*/ DWORD parent_id, /*[in]*/ BSTR name, /*[in]*/ BSTR user, /*[out,retval]*/ DWORD* pfolder_id);
	STDMETHOD(DeleteFilePermanently)(/*[in]*/ unsigned long file_id, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(FindOrCreateFolder)(/*[in]*/ DWORD parent_id, /*[in]*/ BSTR name, /*[in]*/ BSTR user, /*[out,retval]*/ DWORD* folder_id);
	STDMETHOD(GetParentFolderId)(/*[in]*/ DWORD folder_id, /*[out,retval]*/ DWORD* pVal);
	STDMETHOD(GetFolderDisplayPath)(/*[in]*/ DWORD folder_id, /*[out,retval]*/ BSTR* displayName);
	STDMETHOD(OpenFileAsArray)(/*[in]*/ unsigned long file_id, /*[out,retval]*/ SAFEARRAY** dataArray);
	STDMETHOD(SaveArrayAsFile)(/*[in]*/ unsigned long folder_id, /*[in]*/ BSTR fileName, /*[in]*/ SAFEARRAY* dataArray, /*[in]*/ BSTR user, /*[in,out]*/ DWORD* file_id, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(get_rootPath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(GetDBConnection)(/*[out,retval]*/ IDispatch** pVal);
	STDMETHOD(NewDocument)(/*[in]*/ BSTR pathName, /*[in]*/ BSTR siteName);
	STDMETHOD(GetHomepageFileId)(/*[out,retval]*/ unsigned long* file_id);
	STDMETHOD(SetHomepageFileId)(/*[in]*/ unsigned long file_id);
	STDMETHOD(LoadDocument)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT_BOOL* success);
};

#endif //__LXLOCALWEBSITE_H_
