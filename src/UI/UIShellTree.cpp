// UIShellTree.cpp : Implementation of CUIShellTree

#include "stdafx.h"
#include "UI.h"
#include "UIShellTree.h"

#include "winnls.h"
#include "mapinls.h"

/////////////////////////////////////////////////////////////////////////////
// CUIShellTree

LRESULT CUIShellTree::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_t.Create(m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 0, 1/*nID*/);

	EnableImages();
	PopulateTree();	// Have this here??

	return 0;
}

//	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
LRESULT CUIShellTree::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_t.MoveWindow(0, 0, client.right, client.bottom);
	return 0;
}

/****************************************************************************
*
*    FUNCTION: PopulateTree()
*
*    PURPOSE:  Processes the File.Fill/RefreshTree command
*
****************************************************************************/
STDMETHODIMP CUIShellTree::PopulateTree() 
{

    LPSHELLFOLDER lpsf=NULL;
    LPITEMIDLIST  lpi=NULL;
    HRESULT hr;
    TV_SORTCB      tvscb;
   
    // Get a pointer to the desktop folder.
    hr=SHGetDesktopFolder(&lpsf);

    if (SUCCEEDED(hr))
    {
       // Initialize the tree view to be empty.
       m_t.DeleteAllItems();

       // Fill in the tree view from the root.
       FillTreeView(lpsf,
                    NULL,
                    TVI_ROOT);
       // Release the folder pointer.
       lpsf->Release();
    }
    tvscb.hParent     = TVI_ROOT;
    tvscb.lParam      = 0;
    tvscb.lpfnCompare = TreeViewCompareProc;

    // Sort the items in the tree view
	m_t.SortChildrenCB(&tvscb/*, FALSE*/);
    
	HTREEITEM hItem;
	hItem = m_t.GetRootItem();
	m_t.Expand(hItem,TVE_EXPAND);

	return S_OK;
}

/****************************************************************************
*
*  FUNCTION: FillTreeView( LPSHELLFOLDER lpsf,
*                          LPITEMIDLIST  lpifq,
*                          HTREEITEM     hParent)
*
*  PURPOSE: Fills a branch of the TreeView control.  Given the
*           shell folder, enumerate the subitems of this folder,
*           and add the appropriate items to the tree.
*
*  PARAMETERS:
*    lpsf         - Pointer to shell folder that we want to enumerate items 
*    lpifq        - Fully qualified item id list to the item that we are enumerating
*                   items for.  In other words, this is the PIDL to the item
*                   identified by the lpsf parameter.
*    hParent      - Parent node
*
*  COMMENTS:
*    This function enumerates the items in the folder identifed by lpsf.
*    Note that since we are filling the left hand pane, we will only add
*    items that are folders and/or have sub-folders.  We *could* put all
*    items in here if we wanted, but that's not the intent.
*
****************************************************************************/
void CUIShellTree::FillTreeView(LPSHELLFOLDER lpsf, LPITEMIDLIST  lpifq, HTREEITEM     hParent)
{
    TV_ITEM         tvi;                          // TreeView Item.
    TV_INSERTSTRUCT tvins;                        // TreeView Insert Struct.
    HTREEITEM       hPrev = NULL;                 // Previous Item Added.
    LPSHELLFOLDER   lpsf2=NULL;
    LPENUMIDLIST    lpe=NULL;
    LPITEMIDLIST    lpi=NULL, lpiTemp=NULL, lpifqThisItem;
    LPTVITEMDATA    lptvid=NULL;
    LPMALLOC        lpMalloc=NULL;
    ULONG           ulFetched;
    UINT            uCount=0;
    HRESULT         hr;
    char            szBuff[256];
    HWND            hwnd=::GetParent(m_t.m_hWnd);

    // Allocate a shell memory object. 
    hr=::SHGetMalloc(&lpMalloc);
    if (FAILED(hr))
       return;

    if (SUCCEEDED(hr))
    {
        // Get the IEnumIDList object for the given folder.
        hr=lpsf->EnumObjects(hwnd, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS, &lpe);

        if (SUCCEEDED(hr))
        {
            // Enumerate throught the list of folder and non-folder objects.
            while (S_OK==lpe->Next(1, &lpi, &ulFetched))
            {
                //Create a fully qualified path to the current item
                //The SH* shell api's take a fully qualified path pidl,
                //(see GetIcon above where I call SHGetFileInfo) whereas the
                //interface methods take a relative path pidl.
                ULONG ulAttrs = SFGAO_HASSUBFOLDER | SFGAO_FOLDER;

                // Determine what type of object we have.
                lpsf->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lpi, &ulAttrs);

                if (ulAttrs & (SFGAO_HASSUBFOLDER | SFGAO_FOLDER))
                {
                   //We need this next if statement so that we don't add things like
                   //the MSN to our tree.  MSN is not a folder, but according to the
                   //shell it has subfolders.
                   if (ulAttrs & SFGAO_FOLDER)
                   {
                      tvi.mask= TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;

                      if (ulAttrs & SFGAO_HASSUBFOLDER)
                      {
                         //This item has sub-folders, so let's put the + in the TreeView.
                         //The first time the user clicks on the item, we'll populate the
                         //sub-folders.
                         tvi.cChildren=1;
                         tvi.mask |= TVIF_CHILDREN;
                      }
                        
                      //OK, let's get some memory for our ITEMDATA struct
                      lptvid = (LPTVITEMDATA)lpMalloc->Alloc(sizeof(TVITEMDATA));
                      if (!lptvid)
                         goto Done;  // Error - could not allocate memory.
   
                      //Now get the friendly name that we'll put in the treeview.
                      if (!GetName(lpsf, lpi, SHGDN_NORMAL, szBuff))
                         goto Done; // Error - could not get friendly name.

                      tvi.pszText    = szBuff;
                      tvi.cchTextMax = MAX_PATH;
    
                      lpifqThisItem=ConcatPidls(lpifq, lpi);
      
                      //Now, make a copy of the ITEMIDLIST
                      lptvid->lpi=CopyITEMID(lpMalloc, lpi);
   
                      GetNormalAndSelectedIcons(lpifqThisItem, &tvi);
   
                      lptvid->lpsfParent=lpsf;    //Store the parent folders SF
                      lpsf->AddRef();

                      lptvid->lpifq=ConcatPidls(lpifq, lpi);
   
                      tvi.lParam = (LPARAM)lptvid;
   
                      // Populate the TreeVeiw Insert Struct
                      // The item is the one filled above.
                      // Insert it after the last item inserted at this level.
                      // And indicate this is a root entry.
                      tvins.item         = tvi;
                      tvins.hInsertAfter = hPrev;
                      tvins.hParent      = hParent;
   
                      // Add the item to the tree
                      hPrev = m_t.InsertItem(&tvins);
                   }
                   // Free this items task allocator.
                   lpMalloc->Free(lpifqThisItem);  
                   lpifqThisItem=0;
                }

                lpMalloc->Free(lpi);  //Free the pidl that the shell gave us.
                lpi=0;
            }
        }

    }
    else
       return;

Done:
 
    if (lpe)  
        lpe->Release();

    //The following 2 if statements will only be TRUE if we got here on an
    //error condition from the "goto" statement.  Otherwise, we free this memory
    //at the end of the while loop above.
    if (lpi && lpMalloc)           
        lpMalloc->Free(lpi);
    if (lpifqThisItem && lpMalloc) 
        lpMalloc->Free(lpifqThisItem);  

    if (lpMalloc) 
        lpMalloc->Release();
}

/****************************************************************************
*
*    FUNCTION: GetIcon(LPITEMIDLIST lpi, UINT uFlags)
*
*    PURPOSE:  Gets the index for the current icon.  Index is index into system
*              image list.
*
*  PARAMETERS:
*    lpi    - Fully qualified item id list for current item.
*    uFlags - Flags for SHGetFileInfo()
*
*  RETURN VALUE:
*    Icon index for current item.
****************************************************************************/
int CUIShellTree::GetIcon(LPITEMIDLIST lpi, UINT uFlags)
{
   SHFILEINFO    sfi;

   SHGetFileInfo((LPCSTR)lpi, 
                 0,
                 &sfi, 
                 sizeof(SHFILEINFO), 
                 uFlags);

   return sfi.iIcon;
}

/****************************************************************************
*
*    FUNCTION: GetNormalAndSelectedIcons(LPITEMIDLIST lpifq, LPTV_ITEM lptvitem)
*
*    PURPOSE:  Gets the index for the normal and selected icons for the current item.
*
*    PARAMETERS:
*    lpifq    - Fully qualified item id list for current item.
*    lptvitem - Pointer to treeview item we are about to add to the tree.
*
****************************************************************************/
void CUIShellTree::GetNormalAndSelectedIcons(LPITEMIDLIST lpifq,
                               LPTV_ITEM lptvitem)
{
   //Note that we don't check the return value here because if GetIcon()
   //fails, then we're in big trouble...

   lptvitem->iImage = GetIcon(lpifq, SHGFI_PIDL | 
                              SHGFI_SYSICONINDEX | 
                              SHGFI_SMALLICON);
   
   lptvitem->iSelectedImage = GetIcon(lpifq, SHGFI_PIDL | 
                                      SHGFI_SYSICONINDEX | 
                                      SHGFI_SMALLICON |
                                      SHGFI_OPENICON);
   
   return;
}

/****************************************************************************
*
*  FUNCTION: DoTheMenuThing(HWND hwnd, 
*                           LPSHELLFOLDER lpsfParent,
*                           LPITEMIDLIST  lpi,
*                           LPPOINT lppt)
*
*  PURPOSE: Displays a popup context menu, given a parent shell folder,
*           relative item id and screen location.
*
*  PARAMETERS:
*    hwnd       - Parent window handle
*    lpsfParent - Pointer to parent shell folder.
*    lpi        - Pointer to item id that is relative to lpsfParent
*    lppt       - Screen location of where to popup the menu.
*
*  RETURN VALUE:
*    Returns TRUE on success, FALSE on failure
*
****************************************************************************/
BOOL CUIShellTree::DoTheMenuThing(HWND hwnd, LPSHELLFOLDER lpsfParent,
     LPITEMIDLIST  lpi, LPPOINT lppt)
{
    LPCONTEXTMENU lpcm;
    HRESULT       hr;
    char          szTemp[64];
    CMINVOKECOMMANDINFO cmi;
    DWORD               dwAttribs=0;
    int                 idCmd;
    HMENU               hMenu;
    BOOL                bSuccess=TRUE;

    hr=lpsfParent->GetUIObjectOf(hwnd,
        1,  //Number of objects to get attributes of
        (const struct _ITEMIDLIST **)&lpi,
        IID_IContextMenu,
        0,
        (LPVOID *)&lpcm);
    if (SUCCEEDED(hr))  
    {
       hMenu = CreatePopupMenu();

       if (hMenu)
       {
          hr=lpcm->QueryContextMenu(hMenu, 0, 1, 0x7fff, CMF_EXPLORE);
          if (SUCCEEDED(hr))
          {
             idCmd=TrackPopupMenu(hMenu, 
                TPM_LEFTALIGN | TPM_RETURNCMD | TPM_RIGHTBUTTON, 
                lppt->x, lppt->y, 0, hwnd, NULL);

             if (idCmd)
             {
                cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
                cmi.fMask  = 0;
                cmi.hwnd   = hwnd;
                cmi.lpVerb = MAKEINTRESOURCE(idCmd-1);
                cmi.lpParameters = NULL;
      	        cmi.lpDirectory  = NULL;
                cmi.nShow        = SW_SHOWNORMAL;
                cmi.dwHotKey     = 0;
                cmi.hIcon        = NULL;
                hr=lpcm->InvokeCommand(&cmi);
                if (!SUCCEEDED(hr))  
                {
                   wsprintf(szTemp, "InvokeCommand failed. hr=%lx", hr);
                   MessageBox(szTemp);
                }
             }

          }
          else
             bSuccess = FALSE;

          DestroyMenu(hMenu);
       }
       else
          bSuccess = FALSE;

       lpcm->Release();
    } 
    else
    {
       wsprintf(szTemp, "GetUIObjectOf failed! hr=%lx", hr);
       MessageBox(szTemp );
       bSuccess = FALSE;
    }
    return bSuccess;
}

/****************************************************************************
*
*    FUNCTION: TreeViewCompareProc(LPARAM, LPARAM, LPARAM)
*
*    PURPOSE:  Callback routine for sorting the tree 
*
****************************************************************************/
int CALLBACK CUIShellTree::TreeViewCompareProc(LPARAM lparam1, 
    LPARAM lparam2, LPARAM lparamSort)
{
    LPTVITEMDATA lptvid1=(LPTVITEMDATA)lparam1;
    LPTVITEMDATA lptvid2=(LPTVITEMDATA)lparam2;
    HRESULT   hr;

    hr = lptvid1->lpsfParent->CompareIDs(0,lptvid1->lpi,lptvid2->lpi);

    if (FAILED(hr))
       return 0;

    return (short)SCODE_CODE(GetScode(hr));
}

// 
// FUNCTIONS THAT DEAL WITH PIDLs
//
/****************************************************************************
*
*    FUNCTION: Next(LPCITEMIDLIST pidl)
*
*    PURPOSE:  Gets the next PIDL in the list 
*
****************************************************************************/
LPITEMIDLIST CUIShellTree::Next(LPCITEMIDLIST pidl)
{
   LPSTR lpMem=(LPSTR)pidl;

   lpMem+=pidl->mkid.cb;

   return (LPITEMIDLIST)lpMem;
}

/****************************************************************************
*
*    FUNCTION: GetSize(LPCITEMIDLIST pidl)
*
*    PURPOSE:  Gets the size of the PIDL 
*
****************************************************************************/
UINT CUIShellTree::GetSize(LPCITEMIDLIST pidl)
{
    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);       // Null terminator
        while (pidl->mkid.cb)
        {
            cbTotal += pidl->mkid.cb;
            pidl = Next(pidl);
        }
    }

    return cbTotal;
}

/****************************************************************************
*
*    FUNCTION: CreatePidl(UINT cbSize)
*
*    PURPOSE:  Allocates a PIDL 
*
****************************************************************************/
LPITEMIDLIST CUIShellTree::CreatePidl(UINT cbSize)
{
    LPMALLOC lpMalloc;
    HRESULT  hr;
    LPITEMIDLIST pidl=NULL;

    hr=SHGetMalloc(&lpMalloc);

    if (FAILED(hr))
       return 0;

    pidl=(LPITEMIDLIST)lpMalloc->Alloc(cbSize);

    if (pidl)
        memset(pidl, 0, cbSize);      // zero-init for external task   alloc

    if (lpMalloc) lpMalloc->Release();

    return pidl;
}

/****************************************************************************
*
*    FUNCTION: ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
*
*    PURPOSE:  Concatenates two PIDLs 
*
****************************************************************************/
LPITEMIDLIST CUIShellTree::ConcatPidls(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
    LPITEMIDLIST pidlNew;
    UINT cb1;
    UINT cb2;

    if (pidl1)  //May be NULL
       cb1 = GetSize(pidl1) - sizeof(pidl1->mkid.cb);
    else
       cb1 = 0;

    cb2 = GetSize(pidl2);

    pidlNew = CreatePidl(cb1 + cb2);
    if (pidlNew)
    {
        if (pidl1)
           memcpy(pidlNew, pidl1, cb1);
        memcpy(((LPSTR)pidlNew) + cb1, pidl2, cb2);
    }
    return pidlNew;
}

/****************************************************************************
*
*    FUNCTION: CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
*
*    PURPOSE:  Copies the ITEMID 
*
****************************************************************************/
LPITEMIDLIST CUIShellTree::CopyITEMID(LPMALLOC lpMalloc, LPITEMIDLIST lpi)
{
   LPITEMIDLIST lpiTemp;

   lpiTemp=(LPITEMIDLIST)lpMalloc->Alloc(lpi->mkid.cb+sizeof(lpi->mkid.cb));
   CopyMemory((PVOID)lpiTemp, (CONST VOID *)lpi, lpi->mkid.cb+sizeof(lpi->mkid.cb));

   return lpiTemp;
}

/****************************************************************************
*
*    FUNCTION: GetName(LPSHELLFOLDER lpsf,LPITEMIDLIST  lpi,DWORD dwFlags,
*             LPSTR         lpFriendlyName)
*
*    PURPOSE:  Gets the friendly name for the folder 
*
****************************************************************************/
BOOL CUIShellTree::GetName(LPSHELLFOLDER lpsf,
             LPITEMIDLIST  lpi,
			 DWORD         dwFlags,
             LPSTR         lpFriendlyName)
{
   BOOL   bSuccess=TRUE;
   STRRET str;

   if (NOERROR==lpsf->GetDisplayNameOf(lpi,dwFlags, &str))
   {
      switch (str.uType)
      {
         case STRRET_WSTR:

            WideCharToMultiByte(CP_ACP,                 // CodePage
                                0,		               // dwFlags
                                str.pOleStr,            // lpWideCharStr
                                -1,                     // cchWideChar
                                lpFriendlyName,         // lpMultiByteStr
								MAX_PATH,
                                //sizeof(lpFriendlyName), // cchMultiByte, wrong. sizeof on a pointer, psk, psk
                                NULL,                   // lpDefaultChar,
                                NULL);                  // lpUsedDefaultChar

             break;

         case STRRET_OFFSET:

             lstrcpy(lpFriendlyName, (LPSTR)lpi+str.uOffset);
             break;

         case STRRET_CSTR:
             
             lstrcpy(lpFriendlyName, (LPSTR)str.cStr);
             break;

         default:
             bSuccess = FALSE;
             break;
      }
   }
   else
      bSuccess = FALSE;

   return bSuccess;
}

/****************************************************************************
*
*    FUNCTION: GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
*
*    PURPOSE:  Gets the Fully qualified Pidls for the folder 
*
****************************************************************************/
LPITEMIDLIST CUIShellTree::GetFullyQualPidl(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi)
{
   char szBuff[MAX_PATH];
   OLECHAR szOleChar[MAX_PATH];
   LPSHELLFOLDER lpsfDeskTop;
   LPITEMIDLIST  lpifq;
   ULONG ulEaten, ulAttribs;
   HRESULT hr;

   if (!GetName(lpsf, lpi, SHGDN_FORPARSING, szBuff))
      return NULL;

   hr=SHGetDesktopFolder(&lpsfDeskTop);

   if (FAILED(hr))
      return NULL;

   MultiByteToWideChar(CP_ACP,
					   MB_PRECOMPOSED,
					   szBuff,
					   -1,
					   (USHORT *)szOleChar,
					   sizeof(szOleChar));

   hr=lpsfDeskTop->ParseDisplayName(NULL,
									NULL,
									szOleChar,
									&ulEaten,
									&lpifq,
									&ulAttribs);

   lpsfDeskTop->Release();

   if (FAILED(hr))
      return NULL;

   return lpifq;
}



/////////////////////////////////////////////////////////////////////////////
// CUIShellTree message handlers

/****************************************************************************
*
*	FUNCTION:	OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
*
*	PURPOSE:	Reponds to an TVN_ITEMEXPANDING message in order to fill up
*				subdirectories. Pass the parameters from OnItemExpanding() to 
*				this function. You need to do that or your folders won't
*				expand.
*
*	OTHER:		It can also be used to update a corresponding listview. Seem MFCENUM
*
*	MESSAGEMAP:	TVN_ITEMEXPANDING
*
****************************************************************************/
void CUIShellTree::FolderExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPTVITEMDATA   lptvid;  //Long pointer to TreeView item data
	HRESULT        hr;
	LPSHELLFOLDER  lpsf2=NULL;
	static char    szBuff[MAX_PATH];
	TV_SORTCB      tvscb;

	NM_TREEVIEW* pnmtv = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    if ((pnmtv->itemNew.state & TVIS_EXPANDEDONCE))
         return;
		
    lptvid=(LPTVITEMDATA)pnmtv->itemNew.lParam;
    if (lptvid)
       {
            hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
                0, IID_IShellFolder,(LPVOID *)&lpsf2);

            if (SUCCEEDED(hr))
            {
                FillTreeView(lpsf2,
                       lptvid->lpifq,
                       pnmtv->itemNew.hItem);
            }

            tvscb.hParent     = pnmtv->itemNew.hItem;
            tvscb.lParam      = 0;
            tvscb.lpfnCompare = TreeViewCompareProc;

            m_t.SortChildrenCB(&tvscb /*, FALSE*/);
    }	
	
	*pResult = 0;
}

/****************************************************************************
*
*	FUNCTION:	FolderPopup(NMHDR* pNMHDR, LRESULT* pResult) 
*
*	PURPOSE:	Diplays a popup menu for the folder selected. Pass the
*				parameters from Rclick() to this function.
*
*	MESSAGEMAP:	NM_RCLICK;
*
****************************************************************************/
void CUIShellTree::FolderPopup(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POINT			pt;
	LPTVITEMDATA	lptvid;  //Long pointer to TreeView item data
	LPSHELLFOLDER	lpsf2=NULL;
	static char		szBuff[MAX_PATH];
	TV_HITTESTINFO	tvhti;
	TV_ITEM			tvi;

	// TODO: Add your control notification handler code here
	::GetCursorPos((LPPOINT)&pt);
	m_t.ScreenToClient(&pt);
	tvhti.pt=pt;
    m_t.HitTest(&tvhti);
    m_t.SelectItem(tvhti.hItem);
	if (tvhti.flags & (TVHT_ONITEMLABEL|TVHT_ONITEMICON))
	{
		m_t.ClientToScreen(&pt);
		tvi.mask=TVIF_PARAM;
		tvi.hItem=tvhti.hItem;
		
        if (!m_t.GetItem(&tvi)){
			return;
		}
		
		lptvid=(LPTVITEMDATA)tvi.lParam;
		
		DoTheMenuThing(::GetParent(m_t.m_hWnd),
		lptvid->lpsfParent, lptvid->lpi, &pt);
	}	
	
	*pResult = 0;
}

/****************************************************************************
*
*	FUNCTION:	FolderSelected(NMHDR* pNMHDR, LRESULT* pResult, CString &szFolderPath) 
*
*	PURPOSE:	Call this function if for example you want to put the path of the folder
*				selected inside a combobox or an edit window. You would pass the
*				parameters from OnSelChanged() to this function along with a CString object
*				that will hold the folder path. If the path is not
*				in the filesystem(eg MyComputer) it returns false.
*
*	MESSAGEMAP:	TVN_SELCHANGED
*
****************************************************************************/
BOOL CUIShellTree::FolderSelected(NMHDR* pNMHDR, LRESULT* pResult, CString &szFolderPath) 
{
	// TODO: Add your control notification handler code here
	POINT			pt;
	LPTVITEMDATA	lptvid;  //Long pointer to TreeView item data
	LPSHELLFOLDER	lpsf2=NULL;
	static char		szBuff[MAX_PATH];
	TV_HITTESTINFO	tvhti;
	TV_ITEM			tvi;
	HRESULT			hr;
	BOOL			bRet=false;

	// TODO: Add your control notification handler code here
	::GetCursorPos((LPPOINT)&pt);
	m_t.ScreenToClient(&pt);
	tvhti.pt=pt;
    m_t.HitTest(&tvhti);
    m_t.SelectItem(tvhti.hItem);
	if (tvhti.flags & (TVHT_ONITEMLABEL|TVHT_ONITEMICON))
	{
		m_t.ClientToScreen(&pt);
		tvi.mask=TVIF_PARAM;
		tvi.hItem=tvhti.hItem;
		
        if (!m_t.GetItem(&tvi))
		return false;
		
		lptvid=(LPTVITEMDATA)tvi.lParam;

		if (lptvid && lptvid->lpsfParent && lptvid->lpi)
		{
			hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
					 0,IID_IShellFolder,(LPVOID *)&lpsf2);

			if (SUCCEEDED(hr))
				{
					ULONG ulAttrs = SFGAO_FILESYSTEM;

					// Determine what type of object we have.
					lptvid->lpsfParent->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lptvid->lpi, &ulAttrs);

					if (ulAttrs & (SFGAO_FILESYSTEM))
					{
						if(SHGetPathFromIDList(lptvid->lpifq,szBuff)){
							szFolderPath = szBuff;
							bRet = true;
						}
					}
				}

		}
		if(lpsf2)
			lpsf2->Release();
		
	}	
	*pResult = 0;
	return bRet;
}

/****************************************************************************
*
*	FUNCTION:	EnableImages()
*
*	PURPOSE:	Obtains a handle to the system image list and attaches it
*				to the tree control. DO NOT DELETE the imagelist
*
*	MESSAGEMAP:	NONE
*
****************************************************************************/
void CUIShellTree::EnableImages()
{
	// Get the handle to the system image list, for our icons
    HIMAGELIST  hImageList;
    SHFILEINFO    sfi;

    hImageList = (HIMAGELIST)SHGetFileInfo((LPCSTR)"C:\\", 
                                           0,
                                           &sfi, 
                                           sizeof(SHFILEINFO), 
                                           SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

    // Attach ImageList to TreeView
    if (hImageList)
        ::SendMessage(m_t.m_hWnd, TVM_SETIMAGELIST, (WPARAM) TVSIL_NORMAL,
            (LPARAM)hImageList);
}

/****************************************************************************
*
*	FUNCTION:	GetSelectedFolderPath(CString &szFolderPath)
*
*	PURPOSE:	Retrieves the path of the currently selected string.
*				Pass a CString object that will hold the folder path. 
*				If the path is not in the filesystem(eg MyComputer) 
*				or none is selected it returns false.
*
*	MESSAGEMAP:	NONE
*
****************************************************************************/
BOOL CUIShellTree::GetSelectedFolderPath(CString &szFolderPath)
{
	LPTVITEMDATA	lptvid;  //Long pointer to TreeView item data
	LPSHELLFOLDER	lpsf2=NULL;
	static char		szBuff[MAX_PATH];
	HTREEITEM		hItem;
	HRESULT			hr;
	BOOL			bRet=false;

	if((hItem = m_t.GetSelectedItem()))
	{
		lptvid=(LPTVITEMDATA)m_t.GetItemData(hItem);

		if (lptvid && lptvid->lpsfParent && lptvid->lpi)
		{
			hr=lptvid->lpsfParent->BindToObject(lptvid->lpi,
					 0,IID_IShellFolder,(LPVOID *)&lpsf2);

			if (SUCCEEDED(hr))
				{
					ULONG ulAttrs = SFGAO_FILESYSTEM;

					// Determine what type of object we have.
					lptvid->lpsfParent->GetAttributesOf(1, (const struct _ITEMIDLIST **)&lptvid->lpi, &ulAttrs);

					if (ulAttrs & (SFGAO_FILESYSTEM))
					{
						if(SHGetPathFromIDList(lptvid->lpifq,szBuff)){
							szFolderPath = szBuff;
							bRet = true;
						}
					}
				}

		}
		if(lpsf2)
			lpsf2->Release();
	}
	return bRet;
}