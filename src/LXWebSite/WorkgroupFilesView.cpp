// WorkgroupFilesView.cpp : Implementation of CWorkgroupFilesView
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "WorkgroupFilesView.h"

#include "WorkgroupDocument.h"

void com_error_Message(_com_error &e);

/////////////////////////////////////////////////////////////////////////////
// CWorkgroupFilesView

int CWorkgroupFilesView::FinalConstruct()
{
	HRESULT hr;

	hr = m_ctl.CoCreateInstance(CLSID_XMiLFilesControl);
	if (FAILED(hr)) return hr;

	return 0;
}

void CWorkgroupFilesView::FinalRelease()
{
}

LRESULT CWorkgroupFilesView::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc(0,0,0,0);
	IUnknown* p;

	m_ctl->SetFileSystemInterface(m_document->m_filesystem);
	m_ctl->SetRootFolderPath(L"");

	m_axctl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE);
	m_axctl.AttachControl(m_ctl, &p);
//	IDispEventImpl<4, CASElementsTreeView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

	CComPtr<IUITreeControl> treeCtl;
	m_ctl->GetTreeControl(&treeCtl);
	IDispEventImpl<4, CWorkgroupFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(treeCtl);

	return 0;
}

LRESULT CWorkgroupFilesView::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CComPtr<IUITreeControl> treeCtl;
	m_ctl->GetTreeControl(&treeCtl);
	IDispEventImpl<4, CWorkgroupFilesView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(treeCtl);

//	IDispEventImpl<4, CASElementsTreeView, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	return 0;
}

LRESULT CWorkgroupFilesView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_axctl.MoveWindow(0, 0, client.right, client.bottom);
	return 0;
}

HRESULT __stdcall CWorkgroupFilesView::OnItemDblClick(DWORD item)
{
//	CWebSite* pWebSite = ((CWebSite*)m_document.p);

	CComPtr<IUITreeControl> treeCtl;
	m_ctl->GetTreeControl(&treeCtl);

	DWORD active;
	treeCtl->GetSelectedItem(&active);

	if (active)
	{
//		CSiteItem* pItem;
//		treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		/*
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			SetRootFolderId(pDir->m_dbid);
		}
		else
		*/
		{
			DWORD parentitem;
			treeCtl->GetParentItem(active, &parentitem);

			DWORD child;

			treeCtl->GetFirstChildItem(parentitem, &child);
			while (child)
			{
				DWORD state;
				treeCtl->GetItemState(child, &state);

#if 0
				if (state & 1)
				{
					CSiteItem* pFile;
					treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

					VARIANT_BOOL success;
					pWebSite->OpenDocument(pFile->m_dbid, &success);
				}
#endif

				treeCtl->GetNextSiblingItem(child, &child);
			}
		}
	}

	return S_OK;
}

BEGIN_CMD_MAP(CWorkgroupFilesView)
	CMD_HANDLER(ID_FILE_PROPERTIES, OnFileProperties)
END_CMD_MAP()

#if 0
#include <Aclui.h>
#pragma comment(lib, "Aclui.lib")

#include <Aclapi.h>
#pragma comment(lib, "Advapi32.lib")

class ATL_NO_VTABLE CSecurityInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public ISecurityInformation
{
public:
	CSecurityInfo()
	{
		pSD = NULL;
	}

	XMILLWEBLib::ILFileSystemPtr m_filesystem;
	PSECURITY_DESCRIPTOR pSD;
	SI_ACCESS access[8];
	_bstr_t m_pathName;

	int FinalConstruct()
	{
		DWORD dwRes;//, dwDisposition;
		PSID pEveryoneSID = NULL, pAdminSID = NULL;
		PACL pACL = NULL;
		EXPLICIT_ACCESS ea[2];
		SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
		SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;
		//SECURITY_ATTRIBUTES sa;
//		LONG lRes;
		
		// Create a well-known SID for the Everyone group.
		
		if(! AllocateAndInitializeSid( &SIDAuthWorld, 1,
			SECURITY_WORLD_RID,
			0, 0, 0, 0, 0, 0, 0,
			&pEveryoneSID) ) {
			//printf( "AllocateAndInitializeSid Error %u\n", GetLastError() );
			//return;
		}
		
		// Initialize an EXPLICIT_ACCESS structure for an ACE.
		// The ACE will allow Everyone read access to the key.
		
		ZeroMemory(&ea, 2 * sizeof(EXPLICIT_ACCESS));
		ea[0].grfAccessPermissions = KEY_READ;
		ea[0].grfAccessMode = SET_ACCESS;
		ea[0].grfInheritance= NO_INHERITANCE;
		ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
		ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;
		
		// Create a SID for the BUILTIN\Administrators group.
		
		if(! AllocateAndInitializeSid( &SIDAuthNT, 2,
			SECURITY_BUILTIN_DOMAIN_RID,
			DOMAIN_ALIAS_RID_ADMINS,
			0, 0, 0, 0, 0, 0,
			&pAdminSID) ) {
			//printf( "AllocateAndInitializeSid Error %u\n", GetLastError() );
			//goto Cleanup; 
		}
		
		// Initialize an EXPLICIT_ACCESS structure for an ACE.
		// The ACE will allow the Administrators group full access to the key.
		
		ea[1].grfAccessPermissions = KEY_ALL_ACCESS;
		ea[1].grfAccessMode = SET_ACCESS;
		ea[1].grfInheritance= NO_INHERITANCE;
		ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
		ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
		ea[1].Trustee.ptstrName  = (LPTSTR) pAdminSID;
		
		// Create a new ACL that contains the new ACEs.
		
		dwRes = SetEntriesInAcl(2, ea, NULL, &pACL);
		if (ERROR_SUCCESS != dwRes) {
			//printf( "SetEntriesInAcl Error %u\n", GetLastError() );
			//goto Cleanup;
		}
		
		// Initialize a security descriptor.  
		
		pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, 
			SECURITY_DESCRIPTOR_MIN_LENGTH); 
		if (pSD == NULL) { 
			//printf( "LocalAlloc Error %u\n", GetLastError() );
			//goto Cleanup; 
		} 
		
		if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION)) {  
			//printf( "InitializeSecurityDescriptor Error %u\n", 
			//	GetLastError() );
			//goto Cleanup; 
		} 
		
		// Add the ACL to the security descriptor. 
		
		if (!SetSecurityDescriptorDacl(pSD, 
			TRUE,     // fDaclPresent flag   
			pACL, 
			FALSE))   // not a default DACL 
		{  
			//printf( "SetSecurityDescriptorDacl Error %u\n", GetLastError() );
			//goto Cleanup; 
		} 

		return 0;
	}

BEGIN_COM_MAP(CSecurityInfo)
//	COM_INTERFACE_ENTRY(ISecurityInformation)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()

public:
    // *** ISecurityInformation methods ***
   STDMETHOD(GetObjectInformation) (THIS_ PSI_OBJECT_INFO pObjectInfo )
	{
		pObjectInfo->dwFlags = SI_ADVANCED;
		pObjectInfo->hInstance = _Module.GetResourceInstance();
		pObjectInfo->pszServerName = L"213.115.5.45";//NULL;
		pObjectInfo->pszObjectName = L"ObjectName";
		pObjectInfo->pszPageTitle = NULL;
		pObjectInfo->guidObjectType = GUID_NULL;
		
		return S_OK;
	}

	STDMETHOD(GetSecurity) (THIS_ SECURITY_INFORMATION RequestedInformation,
		PSECURITY_DESCRIPTOR *ppSecurityDescriptor,
		BOOL fDefault )
	{
		try
		{
			_variant_t vsd = m_filesystem->GetPathSecurityDescriptor(m_pathName);

			SECURITY_DESCRIPTOR* self;
			SafeArrayAccessData(vsd.parray, (void**)&self);

			DWORD absSize = 0;
			DWORD daclSize = 0;
			DWORD saclSize = 0;
			DWORD ownerSize = 0;
			DWORD primGroupSize = 0;
			MakeAbsoluteSD(self, NULL, &absSize, NULL, &daclSize, NULL, &saclSize, NULL, &ownerSize, NULL, &primGroupSize);

			pSD = LocalAlloc(0, absSize);
			MakeAbsoluteSD(self,
				pSD, &absSize,
				/*pSD->Dacl =*/ (PACL)LocalAlloc(0, daclSize), &daclSize,
				/*pSD->Sacl =*/ (PACL)LocalAlloc(0, saclSize), &saclSize,
				/*pSD->Owner =*/ (PSID)LocalAlloc(0, ownerSize), &ownerSize,
				/*pSD->Group =*/ (PSID)LocalAlloc(0, primGroupSize), &primGroupSize);
			
			SafeArrayUnaccessData(vsd.parray);
		}
		catch (_com_error &e)
		{
			com_error_Message(e);
		}

		*ppSecurityDescriptor = pSD;

		return S_OK;
	}

	STDMETHOD(SetSecurity) (THIS_ SECURITY_INFORMATION SecurityInformation,
		PSECURITY_DESCRIPTOR pSecurityDescriptor )
	{
		DWORD bufferLength = 0;
		MakeSelfRelativeSD(pSecurityDescriptor, NULL, &bufferLength);

		SAFEARRAY* sdArray = SafeArrayCreateVector(VT_UI1, 0, bufferLength);
		if (sdArray)
		{
			MakeSelfRelativeSD(pSecurityDescriptor, (sdArray)->pvData, &bufferLength);

			try
			{
				m_filesystem->SetPathSecurityDescriptor(m_pathName, sdArray);
			}
			catch (_com_error &e)
			{
				com_error_Message(e);
			}

			SafeArrayDestroy(sdArray);
		}

		return S_OK;
	}

	STDMETHOD(GetAccessRights) (THIS_ const GUID* pguidObjectType,
		DWORD dwFlags, // SI_EDIT_AUDITS, SI_EDIT_PROPERTIES
		PSI_ACCESS *ppAccess,
		ULONG *pcAccesses,
		ULONG *piDefaultAccess )
	{
		access[0].pguid = NULL;
		access[0].mask = (1<<0);
		access[0].pszName = L"Read";
		access[0].dwFlags = SI_ACCESS_GENERAL;

		*ppAccess = access;
		*pcAccesses = 1;

		*piDefaultAccess = 0;

		return S_OK;
	}
	
	STDMETHOD(MapGeneric) (THIS_ const GUID *pguidObjectType,
		UCHAR *pAceFlags,
		ACCESS_MASK *pMask)
	{
		GENERIC_MAPPING mapping;
		mapping.GenericRead = 1<<0;
		mapping.GenericWrite = 1<<1;
		mapping.GenericExecute = 1<<2;
		mapping.GenericAll = 7;
		MapGenericMask(pMask, &mapping);
		return S_OK;
	}
	
	STDMETHOD(GetInheritTypes) (THIS_ PSI_INHERIT_TYPE *ppInheritTypes,
		ULONG *pcInheritTypes )
	{
		return E_NOTIMPL;
	}
	
	STDMETHOD(PropertySheetPageCallback)(THIS_ HWND hwnd, UINT uMsg, SI_PAGE_TYPE uPage )
	{
		return E_NOTIMPL;
	}
};
#endif

LRESULT CWorkgroupFilesView::OnFileProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	CComPtr<IUITreeControl> treeCtl;
	m_ctl->GetTreeControl(&treeCtl);

	DWORD active;
	treeCtl->GetSelectedItem(&active);

	DWORD pItem;
	treeCtl->GetItemInfo(active, &pItem, NULL, NULL);

	BSTR bfullpathName;
	m_ctl->GetItemFullPathName(pItem, &bfullpathName);
	_bstr_t fullpathName = _bstr_t(bfullpathName, false);

	CComObject<CSecurityInfo>* pSecurityInfo;
	CComObject<CSecurityInfo>::CreateInstance(&pSecurityInfo);
	pSecurityInfo->AddRef();

	pSecurityInfo->m_filesystem = m_document->m_filesystem;
	pSecurityInfo->m_pathName = fullpathName;

	CPropertySheet sheet("Object", 0);

	HPROPSHEETPAGE hSecurityPage = CreateSecurityPage(pSecurityInfo);

	sheet.AddPage(hSecurityPage);

	sheet.DoModal();

	pSecurityInfo->Release();
/*

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

		DWORD parentitem;
		m_treeCtl->GetParentItem(active, &parentitem);

		DWORD child;

		m_treeCtl->GetFirstChildItem(parentitem, &child);
		while (child)
		{
			DWORD state;
			m_treeCtl->GetItemState(child, &state);

			DWORD nextSibling;
			m_treeCtl->GetNextSiblingItem(child, &nextSibling);

			if (state & 1)
			{
				CSiteItem* pFile;
				m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL, NULL);

				pWebSite->m_webSite->DeleteFilePermanently(pFile->m_dbid);
			}

			child = nextSibling;
		}
	}
*/
#endif
	return 0;
}
