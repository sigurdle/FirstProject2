// WorkgroupDocument.h : Declaration of the CWorkgroupDocument

#if 0	// For now

#ifndef __WORKGROUPDOCUMENT_H_
#define __WORKGROUPDOCUMENT_H_

#include "resource.h"       // main symbols

class CProgressDlg;

/////////////////////////////////////////////////////////////////////////////
// CWorkgroupDocument
class ATL_NO_VTABLE CWorkgroupDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWorkgroupDocument, &CLSID_WorkgroupDocument>,
	public IConnectionPointContainerImpl<CWorkgroupDocument>,
	public IWorkgroupDocument
{
public:
	CWorkgroupDocument()
	{
	}

	XMILLWEBLib::IXmillWorkgroupPtr m_workgroup;
	XMILLWEBLib::ILFileSystemPtr m_filesystem;

	void ShowView();

	long CopyMoveFile(DWORD folder_id, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg);

DECLARE_REGISTRY_RESOURCEID(IDR_WORKGROUPDOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CWorkgroupDocument)
	COM_INTERFACE_ENTRY(IWorkgroupDocument)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CWorkgroupDocument)
END_CONNECTION_POINT_MAP()


// IWorkgroupDocument
public:
	STDMETHOD(CopyMoveFiles)(/*[in]*/ DWORD folder_id, /*[in]*/ SAFEARRAY* filepaths, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied);
};

#endif //__WORKGROUPDOCUMENT_H_

#endif