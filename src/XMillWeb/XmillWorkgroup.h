// XmillWorkgroup.h : Declaration of the CXmillWorkgroup

#ifndef __XMILLWORKGROUP_H_
#define __XMILLWORKGROUP_H_

#include "resource.h"       // main symbols
#include <mtx.h>

typedef enum _LogActionType
{
	LTSaveFile = 1,
	LTOpenFile,
	LTDeleteFile,
}
LogActionType;

/////////////////////////////////////////////////////////////////////////////
// CXmillWorkgroup
class ATL_NO_VTABLE CXmillWorkgroup : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CXmillWorkgroup, &CLSID_XmillWorkgroup>,
	public IObjectControl,
	public IDispatchImpl<IXmillWorkgroup, &IID_IXmillWorkgroup, &LIBID_XMILLWEBLib>,
	public ILFileSystem
{
public:
	CXmillWorkgroup()
	{
	}

	ADODB::_ConnectionPtr m_conn;

	DWORD AddNewFile(DWORD parent_id, long type, BSTR filename, DWORD file_size, double file_date);
	_bstr_t GetFolderDisplayPathRecursive(long folder_id, WCHAR* pathDelimiter);
	void RemoveFileFromDatabase(long parent_id, long id);

	long GetFileNameID(long parent_id, BSTR filePath);
	long GetPathFileNameID(BSTR filePath);

	long SaveNodeName(BSTR nodeName);
	long SaveNamespaceURI(BSTR namespaceURI);
	HRESULT SaveXMLNode(long document_id, long parentNode_id, long nodeIndex, LHTMLLib::ILDOMNodePtr node);
	HRESULT SaveXMLDocument(long file_id, LHTMLLib::ILDOMDocumentPtr document);

	_bstr_t GetNodeName(long id);
	_bstr_t GetNamespaceURI(long id);
	LHTMLLib::ILDOMNodePtr LoadXMLNode(ADODB::_RecordsetPtr nodeRs, LHTMLLib::ILDOMDocumentPtr document);

	HRESULT AddLogAction(LogActionType type, LHTMLLib::ILDOMElementPtr element);

DECLARE_REGISTRY_RESOURCEID(IDR_XMILLWORKGROUP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_NOT_AGGREGATABLE(CXmillWorkgroup)

BEGIN_COM_MAP(CXmillWorkgroup)
	COM_INTERFACE_ENTRY(IXmillWorkgroup)
	COM_INTERFACE_ENTRY(IObjectControl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ILFileSystem)
END_COM_MAP()

// IObjectControl
public:
	STDMETHOD(Activate)();
	STDMETHOD_(BOOL, CanBePooled)();
	STDMETHOD_(void, Deactivate)();

	CComPtr<IObjectContext> m_spObjectContext;

// IXmillWorkgroup
public:
	STDMETHOD(GetPathSecurityDescriptor)(/*[in]*/ BSTR pathName, /*[out,retval]*/ VARIANT* pVal);
	STDMETHOD(SetPathSecurityDescriptor)(/*[in]*/ BSTR pathName, /*[in]*/ SAFEARRAY* sdArray);
	STDMETHOD(NewWebSite)(/*[in]*/ BSTR websitexml, /*[out,retval]*/ long* pVal);
	STDMETHOD(GetWebSiteList)(/*[out,retval]*/ BSTR* pVal);
	STDMETHOD(TestMethod)(/*[in]*/ BSTR testString, /*[out,retval]*/ BSTR* pVal);

// ILFileSystem
	STDMETHOD(GetFolderDirectoryList)(/*[in]*/ BSTR pathName, /*[out,retval]*/ BSTR* pVal);
	STDMETHOD(RenameFile)(/*[in]*/ long file_id, /*[in]*/ BSTR name, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(CreateFolder)(/*[in]*/ long parent_id, /*[in]*/ BSTR name, /*[in]*/ BSTR user, /*[out,retval]*/ long* pfolder_id);
	STDMETHOD(DeleteFilePermanently)(/*[in]*/ long file_id, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
	STDMETHOD(FindOrCreateFolder)(/*[in]*/ BSTR pathName, /*[in]*/ BSTR user, /*[out,retval]*/ long* folder_id);
	STDMETHOD(GetParentFolderId)(/*[in]*/ long folder_id, /*[out,retval]*/ long* pVal);
	STDMETHOD(GetFolderDisplayPath)(/*[in]*/ long folder_id, /*[out,retval]*/ BSTR* displayName);
	STDMETHOD(OpenFileAsArray)(/*[in] long file_id*/ /*[in]*/ BSTR filePath, /*[out,retval]*/ SAFEARRAY** dataArray);
	STDMETHOD(SaveArrayAsFile)(/*[in] long folder_id*/ /*[in]*/ BSTR filePath, /*[in]*/ SAFEARRAY* dataArray, /*[in]*/ BSTR user, /*[in,out]*/ long* file_id, /*[out,retval]*/ VARIANT_BOOL* pSuccess);
};

#endif //__XMILLWORKGROUP_H_
