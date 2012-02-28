	
// WSSrv.h : Declaration of the CWSSrv

#ifndef __WSSRV_H_
#define __WSSRV_H_

#include "resource.h"       // main symbols
#include "WSSrvModCP.h"

//class CSiteDir;

/////////////////////////////////////////////////////////////////////////////
// CWSSrv
class ATL_NO_VTABLE CWSSrv : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CWSSrv, &CLSID_WSSrv>,
	public IConnectionPointContainerImpl<CWSSrv>,
	public IDispatchImpl<IWSSrv, &IID_IWSSrv, &LIBID_WSSRVMODLib>,
	public CProxy_IWSSrvEvents< CWSSrv >
{
public:
	CWSSrv()
	{
		//m_pUnkMarshaler = NULL;

//		m_pRootDir = NULL;
		m_homepageFileID = 0L;
	}

//	_bstr_t	m_rootPath;
//	CSiteDir* m_pRootDir;

	ADODB::_ConnectionPtr m_siteDataConnection;
	WCHAR m_connstr[512];


//	ADODB::_RecordsetPtr m_rsFiles;

	DWORD m_homepageFileID;

	void ScanFiles();
	void GetHomepageFileIdFromDB();
	_bstr_t GetFolderDisplayPathRecursive(DWORD folder_id, WCHAR* pathDelimiter);

	DWORD AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date);

	void RemoveFileFromDatabase(DWORD parent_id, DWORD id);

	void CreateTable_websettings(ADOX::_CatalogPtr catalog);
	void CreateTable_files(ADOX::_CatalogPtr catalog);
	void CreateTable_files_data(ADOX::_CatalogPtr catalog);
	void CreateTable_links(ADOX::_CatalogPtr catalog);
	void CreateTable_tasks(ADOX::_CatalogPtr catalog);

DECLARE_REGISTRY_RESOURCEID(IDR_WSSRV)
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWSSrv)
	COM_INTERFACE_ENTRY(IWSSrv)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
//	COM_INTERFACE_ENTRY_AGGREGATE(IID_IMarshal, m_pUnkMarshaler.p)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CWSSrv)
CONNECTION_POINT_ENTRY(DIID__IWSSrvEvents)
END_CONNECTION_POINT_MAP()


	HRESULT FinalConstruct()
	{
	/*
		return CoCreateFreeThreadedMarshaler(
			GetControllingUnknown(), &m_pUnkMarshaler.p);
			*/
	return S_OK;
	}

	void FinalRelease();

//	CComPtr<IUnknown> m_pUnkMarshaler;

// IWSSrv
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

#endif //__WSSRV_H_
