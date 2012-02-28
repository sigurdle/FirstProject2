#pragma once

// Compare two objects for equivalence
bool IsUnknownEqualUnknown(IUnknown* pThis, IUnknown* pOther);

//#include "MenuItem.h"

//#include "UIDlgSite.h"

class ATL_NO_VTABLE CUICommand : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IUICommand, &IID_IUICommand/*, &LIBID_UILib*/>
{
public:
	long m_id;
	DWORD m_type;
	_bstr_t m_name;
	long m_bitmapIndex;
	HIMAGELIST m_hBitmap;
	long m_itemWidth;
	DWORD m_windowStyle;
	_bstr_t m_windowClassname;

	CArray<_bstr_t,_bstr_t> m_strings;

	CUICommand()
	{
		m_id = 0;
		m_hBitmap = NULL;
		m_bitmapIndex = -1;

		m_itemWidth = -1;
		m_windowStyle = 0L;

		m_type = 0;
	}

BEGIN_COM_MAP(CUICommand)
	COM_INTERFACE_ENTRY(IUICommand)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	STDMETHODIMP get_ID(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_id;
		return S_OK;
	}

	STDMETHODIMP get_type(DWORD *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_type;
		return S_OK;
	}

	STDMETHODIMP put_type(DWORD newVal)
	{
		m_type = newVal;
		return S_OK;
	}

	STDMETHODIMP get_itemWidth(/*[out, retval]*/ long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_itemWidth;
		return S_OK;
	}

	STDMETHODIMP put_itemWidth(/*[in]*/ long newVal)
	{
		m_itemWidth = newVal;
		return S_OK;
	}

	STDMETHODIMP get_windowStyle(/*[out, retval]*/ DWORD *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_windowStyle;
		return S_OK;
	}

	STDMETHODIMP put_windowStyle(/*[in]*/ DWORD newVal)
	{
		m_windowStyle = newVal;
		return S_OK;
	}

	STDMETHODIMP get_windowClassname(/*[out, retval]*/ BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_windowClassname.copy();
		return S_OK;
	}

	STDMETHODIMP put_windowClassname(/*[in]*/ BSTR newVal)
	{
		m_windowClassname = newVal;
		return S_OK;
	}

	STDMETHODIMP AddString(BSTR string)
	{
		if (string == NULL) return E_INVALIDARG;
		m_strings.Add(string);

		return S_OK;
	}

	STDMETHODIMP GetString(long index, BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		if (index >= 0 && index < m_strings.GetSize())
		{
			*pVal = m_strings[index].copy();
		}
		else
			*pVal = NULL;

		return S_OK;
	}

	STDMETHODIMP GetStringCount(long* pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_strings.GetSize();
		return S_OK;
	}

	STDMETHODIMP get_name(BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_name.copy();
		return S_OK;
	}

	STDMETHODIMP get_bitmap(DWORD *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = (DWORD)m_hBitmap;
		return S_OK;
	}

	STDMETHODIMP put_bitmap(DWORD newVal)
	{
		m_hBitmap = (HIMAGELIST)newVal;
		return S_OK;
	}

	STDMETHODIMP get_bitmapIndex(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_bitmapIndex;
		return S_OK;
	}

	STDMETHODIMP put_bitmapIndex(long newVal)
	{
		m_bitmapIndex = newVal;
		return S_OK;
	}
};

class ATL_NO_VTABLE CUICommandGroup :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IUICommandGroup, &IID_IUICommandGroup/*, &LIBID_UILib*/>
{
public:
	_bstr_t m_name;
	CArray<IUICommand*,IUICommand*> m_commands;

	void FinalRelease()
	{
		for (int i = 0; i < m_commands.GetSize(); i++)
		{
			m_commands[i]->Release();
		}
		m_commands.RemoveAll();
	}

BEGIN_COM_MAP(CUICommandGroup)
	COM_INTERFACE_ENTRY(IUICommandGroup)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	STDMETHODIMP get_name(BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_name.copy();
		return S_OK;
	}

	STDMETHODIMP get_length(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_commands.GetSize();
		return S_OK;
	}

	STDMETHODIMP item(long index, IUICommand **pResult)
	{
		if (pResult == NULL) return E_POINTER;

		if (index >= 0 && index < m_commands.GetSize())
		{
			*pResult = m_commands[index];
			(*pResult)->AddRef();
		}
		else
			*pResult = NULL;

		return S_OK;
	}

	STDMETHODIMP append(IUICommand *pCmd)
	{
		if (pCmd == NULL) return E_INVALIDARG;

		pCmd->AddRef();
		m_commands.Add(pCmd);

		return S_OK;
	}
};

class CMenuItem;

class CMenuResource
{
public:
	long m_id;
//	CComQIPtr<IMenuItem> m_menuItem;
	CComObject<CMenuItem>* m_menuItem;

	CMenuResource()
	{
		m_id = 0;
		m_menuItem = NULL;
	}
};

class CUIManagerImplImpl;

#if 0
class CRegisteredDialog :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IUIDlgClass
{
public:
	_bstr_t m_name;
//	CLSID	m_clsid;
	UINT m_nID;
	UINT m_nResourceID;
//	CUIManagerImplImpl/*<T>*/ * m_uiManager;
	IUIManager* m_uiManager;

	CArray<IUIDlg*,IUIDlg*> m_dialogs;
//	IUIDlg* m_dlg;

	CRegisteredDialog()
	{
		m_uiManager = NULL;

		m_nID = 0L;//GUID_NULL;
		m_nResourceID = 0L;

	//	m_dlg = NULL;

		m_pOwnerSheet = NULL;
	}

	CUIDlgSheet* m_pOwnerSheet;

BEGIN_COM_MAP(CRegisteredDialog)
	COM_INTERFACE_ENTRY(IUIDlgClass)
END_COM_MAP()

//	void RemoveDlg(IUIDlg* dlg);

public:
// IUIDlgClass
	STDMETHODIMP GetUIManager(/*[out,retval]*/ IUIManager* *pVal);
	STDMETHODIMP GetName(/*[out,retval]*/ BSTR *pVal);
	STDMETHODIMP CreateDlg(/*[out,retval]*/ IUIDlg* *pVal);

#if 0	// This should be in a CRegisteredToolbar
	STDMETHODIMP GetDialog(/*[out,retval]*/ IUIDlg* *pVal);
	STDMETHODIMP IsVisible(/*[out,retval]*/ BOOL *pVal);
	STDMETHODIMP GetOwnerSheet(/*[out,retval]*/ IUIDlgSheet* *pVal);
#endif
};

class CUISheetDlgClass :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IUIDlgClass
{
public:
	_bstr_t m_name;
//	CLSID	m_clsid;
//	UINT m_nID;
//	UINT m_nResourceID;
//	CUIManagerImplImpl/*<T>*/ * m_uiManager;
	IUIManager* m_uiManager;

	CArray<IUIDlg*,IUIDlg*> m_dialogs;
//	IUIDlg* m_dlg;

	CUISheetDlgClass()
	{
		m_uiManager = NULL;

//		m_nID = 0L;//GUID_NULL;
//		m_nResourceID = 0L;

	//	m_dlg = NULL;
//		m_pOwnerSheet = NULL;
	}

//	CUIDlgSheet* m_pOwnerSheet;

BEGIN_COM_MAP(CUISheetDlgClass)
	COM_INTERFACE_ENTRY(IUIDlgClass)
END_COM_MAP()

//	void RemoveDlg(IUIDlg* dlg);

public:
// IUIDlgClass
	STDMETHODIMP GetUIManager(/*[out,retval]*/ IUIManager* *pVal)
	{
		ATLASSERT(0);
		return S_OK;
	}
	STDMETHODIMP GetName(/*[out,retval]*/ BSTR *pVal)
	{
		*pVal = NULL;
		return S_OK;
	}
	STDMETHODIMP CreateDlg(/*[out,retval]*/ IUIDlg* *pVal)
	{
		CComObject<CUIDlgSheet>* p;
		CComObject<CUIDlgSheet>::CreateInstance(&p);
		if (p)
		{
			p->AddRef();
			m_dialogs.Add(p);
			*pVal = p;
			(*pVal)->AddRef();
		}

		return S_OK;
	}

#if 0	// This should be in a CRegisteredToolbar
	STDMETHODIMP GetDialog(/*[out,retval]*/ IUIDlg* *pVal);
	STDMETHODIMP IsVisible(/*[out,retval]*/ BOOL *pVal);
	STDMETHODIMP GetOwnerSheet(/*[out,retval]*/ IUIDlgSheet* *pVal);
#endif
};
#endif

class ATL_NO_VTABLE CUIManagerImpl :
	public IUIManager
{
public:

	CArray<IUIDlgClass*,IUIDlgClass*> m_dialogClasses;
	CArray<IUIDlgSite*,IUIDlgSite*> m_dialogs;

	CUIManagerImpl()
	{
		m_bDesignMode = FALSE;

		m_hImageListCommands = NULL;

		m_pSite = NULL;
	}

	~CUIManagerImpl()
	{
		if (m_hImageListCommands)
		{
			ImageList_Destroy(m_hImageListCommands);
			m_hImageListCommands = NULL;
		}
	}

	IUIManagerSite* m_pSite;

	_bstr_t m_pathName;

	CArray<IUICommandGroup*,IUICommandGroup*> m_commandGroups;
	CArray<IUICommand*,IUICommand*> m_commands;

	CArray<CMenuResource*,CMenuResource*> m_menuResources;

//	CComQIPtr<IUIMenuDlg> m_activeDlg;
//	CComQIPtr<IMenuItem> m_activeItem;

//	IUIFrame* m_pFrame;

	BOOL m_bDesignMode;

	HIMAGELIST m_hImageListCommands;

#if 0
   STDMETHODIMP CreateMenuDlg(IUIMenuDlg* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		CComObject<CUIMenuDlg>* pMenuDlg;
		CComObject<CUIMenuDlg>::CreateInstance(&pMenuDlg);
		if (pMenuDlg)
		{
			pMenuDlg->AddRef();

			*pVal = pMenuDlg;
		}

		return S_OK;
	}

   STDMETHODIMP CreateButtonsDlg(IUIToolbarDlg* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		CComObject<CUIToolbarDlg>* pMenuDlg;
		CComObject<CUIToolbarDlg>::CreateInstance(&pMenuDlg);
		if (pMenuDlg)
		{
			pMenuDlg->AddRef();

			*pVal = pMenuDlg;
		}

		return S_OK;
	}
#endif

#if 0
	STDMETHODIMP CreateDlgSheet(LPWSTR name, /*[out,retval]*/ IUIDlgSheet* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		CComObject<CRegisteredDialog>* pDialog;
		CComObject<CRegisteredDialog>::CreateInstance(&pDialog);
		if (pDialog)
		{
			pDialog->AddRef();
			pDialog->AddRef();	// TODO remove

			pDialog->m_uiManager = this;
			pDialog->m_name = name;
			pDialog->m_nID = 0;//(UINT)nID;

			CComObject<CUIDlgSheet>* sheet;
			CComObject<CUIDlgSheet>::CreateInstance(&sheet);
			if (sheet)
			{
				sheet->AddRef();	// TODO remmve
				pDialog->m_dlg = sheet;
				sheet->m_pOwnerRegisteredDlg = pDialog;
#if 0
				sheet->m_pDockSite = GetFrame();//static_cast<CUIFrame*>((IUIFrame*)static_cast<T*>(m_uiManager));//->m_pDlgManager;
#endif

				sheet->m_dwStyle = CBRS_SIZE_DYNAMIC;

				/*
				sheet->AddRef();
				static_cast<T*>(this)->m_pSheets.AddTail(sheet);
				*/
#if 0
				GetFrame()->AddDlgSheet(sheet);
#endif

			//	static_cast<CWindowImpl<CDlgSheet>*>(sheet)->Create(static_cast<T*>(this)->m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);

				*pVal = sheet;
				(*pVal)->AddRef();
			}
		}

		return S_OK;
	}
#endif

#if 0
	virtual HRESULT CreateDlg(CRegisteredDialog* rdlg, IUIDlg* *pVal)
	{
		ATLASSERT(0);
#if 0
		ATLASSERT(pVal != NULL);
		if (pVal == NULL) return E_POINTER;

		*pVal = NULL;

	//	ATLASSERT(rdlg->m_dlg == NULL);

		CComQIPtr<IUIDlg> dlg;

#if 0
		if (rdlg->m_nResourceID)
		{
			CComObject<CUIMenuDlg>* menuDlg;
			CComObject<CUIMenuDlg>::CreateInstance(&menuDlg);

			CComPtr<IMenuItem> menuItem;
			FindMenu(_Module.GetResourceInstance(), rdlg->m_nResourceID, &menuItem);

			CComPtr<IMenuItem> menuItem0;
			menuItem->GetSubMenu(0, &menuItem0);

			menuDlg->InitMenu(menuItem0, NULL/*CComQIPtr<ICommandTarget>(GetFrame())*/, -1);
			/*
			*/

			dlg = menuDlg;	// Will AddRef
		}
		else
#endif
		{
			m_pSite->CreateDlg(rdlg->m_nID, &dlg);
			//dlg.CoCreateInstance(rdlg->m_clsid);
		}

		if (dlg != NULL)
		{
			rdlg->m_dialogs.Add(dlg);
			//dlg->AddRef();

			dlg->SetUIManager(this);
			dlg->SetRegisteredDlg(rdlg);

#if 0
			CComObject<CDlgSheet>* sheet;
			CComObject<CDlgSheet>::CreateInstance(&sheet);
			sheet->AddRef();
			sheet->m_pDockSite = static_cast<IUIFrame*>(static_cast<T*>(this));//static_cast<CUIFrame*>((IUIFrame*)static_cast<T*>(m_uiManager));//->m_pDlgManager;

			if (rdlg->m_nResourceId) sheet->m_bShowTabs = FALSE;

		//	static_cast<T*>(m_uiManager)->m_pDlgManager->m_pSheets.AddTail(sheet);
			static_cast<T*>(this)->m_pSheets.AddTail(sheet);


			sheet->AddPage(dlg, NULL);

			static_cast<CWindowImpl<CDlgSheet>*>(sheet)->Create(static_cast<T*>(this)->m_hWnd, CRect(0,0,0,0), NULL, WS_CHILD | WS_VISIBLE);

			sheet->m_dwStyle = CBRS_SIZE_DYNAMIC;
			sheet->m_pDockSite->FloatControlBar(sheet, CPoint(0, 0), CBRS_SIZE_DYNAMIC);
#endif

			*pVal = dlg;
			dlg.Detach();//Release();	// Since we added it to m_dialogs

			(*pVal)->AddRef();
		}
#endif

		return S_OK;
	}
#endif

	struct _AtlToolBarData
	{
		WORD wVersion;
		WORD wWidth;
		WORD wHeight;
		WORD wItemCount;
		//WORD aItems[wItemCount]

		WORD* items()
			{ return (WORD*)(this+1); }
	};

	STDMETHODIMP AddToolbarCommands(HINSTANCE hInst, long nResourceID)
	{
		if (m_hImageListCommands == NULL)
		{
			m_hImageListCommands = ImageList_Create(17, 17, ILC_COLOR8 | ILC_MASK, 0, 10);
		}

		HBITMAP hBitmap = LoadBitmap((HINSTANCE)hInst, MAKEINTRESOURCE(nResourceID));
		if (hBitmap == NULL)
			return NULL;

		HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(nResourceID), RT_TOOLBAR);
		if (hRsrc == NULL)
			return NULL;

		HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc);
		if (hGlobal == NULL)
			return NULL;

		_AtlToolBarData* pData = (_AtlToolBarData*)::LockResource(hGlobal);
		if (pData == NULL)
			return NULL;
		ATLASSERT(pData->wVersion == 1);

		WORD* pItems = pData->items();
		int nItems = pData->wItemCount;

		for (int i = 0; i < nItems; i++)
		{
			WORD nID = pItems[i];

			CComPtr<IUICommand> command;
			FindCommand(nID, &command);
			if (command)
			{
				command->put_bitmap((DWORD)m_hImageListCommands);
				command->put_bitmapIndex(ImageList_GetImageCount(m_hImageListCommands)+i);
			}
		}

		ImageList_AddMasked(m_hImageListCommands, hBitmap, RGB(192, 192, 192));

		DeleteObject(hBitmap);

		return S_OK;
	}

	/*
	HRESULT AddToolbarCommands(UINT nResourceID)
	{
		return AddToolbarCommands(_Module.GetResourceInstance(), nResourceID);
	}
	*/

	STDMETHODIMP CreateCommandGroup(BSTR name, IUICommandGroup **pResult)
	{
		if (pResult == NULL) return E_POINTER;

		CComObject<CUICommandGroup>* cmdgroup;
		CComObject<CUICommandGroup>::CreateInstance(&cmdgroup);
		cmdgroup->m_name = name;

		*pResult = cmdgroup;
		(*pResult)->AddRef();

		return S_OK;
	}

	STDMETHODIMP AppendCommandGroup(IUICommandGroup *pCmdGroup)
	{
		pCmdGroup->AddRef();
		m_commandGroups.Add(pCmdGroup);

		return S_OK;
	}

	STDMETHODIMP AddCommandID(long ID, BSTR name, IUICommandGroup *pGroup, IUICommand **pResult)
	{
		CComObject<CUICommand>* cmd;
		CComObject<CUICommand>::CreateInstance(&cmd);
		cmd->m_id = ID;
		cmd->m_name = name;

		if (pGroup)
		{
			pGroup->append(cmd);
		}

		cmd->AddRef();
		m_commands.Add(cmd);

		if (pResult)
		{
			*pResult = cmd;
			(*pResult)->AddRef();
		}

		return S_OK;
	}

#if 0
	STDMETHODIMP RegisterDlgClass(long nID, /*BSTR name,*/ DWORD flags, IUIDlgClass** pVal)
	{
		CComObject<CRegisteredDialog/*<T>*/ >* pDialog;
		CComObject<CRegisteredDialog/*<T>*/ >::CreateInstance(&pDialog);
		if (pDialog)
		{
			pDialog->AddRef();

			pDialog->m_uiManager = this;
			//pDialog->m_name = name;
			pDialog->m_nID = (UINT)nID;

			m_dialogClasses.Add(pDialog);

			if (pVal)
			{
				*pVal = pDialog;
				(*pVal)->AddRef();
			}
		}
		else
		{
			if (pVal)
			{
				*pVal = NULL;
			}
		}

		return S_OK;
	}

   STDMETHODIMP UnregisterDlg(long clsid)
	{
		ATLASSERT(0);
#if 0
		for (int i = 0; i < m_dialogs.GetSize(); i++)
		{
			if (m_dialogs[i]->m_nID == (UINT)clsid)
			{
			// TODO, destroy m_dlg ?
				m_dialogs[i]->m_uiManager = NULL;
				m_dialogs[i]->Release();
				m_dialogs.RemoveAt(i);
				return S_OK;
			}
		}
#endif

		ATLASSERT(0);
		return E_FAIL;
	}

	STDMETHODIMP RegisterMenuDlg(long nID, /*[in]*/ long nResourceID, /*[in]*/ BSTR name, /*[in]*/ DWORD flags, IUIDlgClass** pVal)
	{
		CComObject<CRegisteredDialog/*<T>*/ >* pDialog;
		CComObject<CRegisteredDialog/*<T>*/ >::CreateInstance(&pDialog);
		if (pDialog)
		{
			pDialog->AddRef();

			pDialog->m_uiManager = this;
			pDialog->m_name = name;
			pDialog->m_nID = (UINT)nID;
			pDialog->m_nResourceID = (UINT)nResourceID;

			m_dialogClasses.Add(pDialog);

			if (pVal)
			{
				*pVal = pDialog;
				(*pVal)->AddRef();
			}
		}
		else
		{
			if (pVal)
			{
				*pVal = NULL;
			}
		}

		return S_OK;
	}

	STDMETHODIMP GetDialogBar(/*[in]*/ long index, /*[out,retval]*/ IUIDlgSite* *pVal)
	{
		if (index >= 0 && index < m_dialogs.GetSize())
		{
			*pVal = m_dialogs[index];
			(*pVal)->AddRef();
		}
		else
			*pVal = NULL;

		return S_OK;
	}
#endif

	STDMETHODIMP get_CommandGroupsCount(long *pVal)
	{
		*pVal = m_commandGroups.GetSize();
		return S_OK;
	}

	STDMETHODIMP GetCommandGroup(long index, IUICommandGroup **pCmdGroup)
	{
		if (pCmdGroup == NULL) return E_POINTER;

		if (index >= 0 && index < m_commandGroups.GetSize())
		{
			*pCmdGroup = m_commandGroups[index];
			(*pCmdGroup)->AddRef();
		}
		else
			*pCmdGroup = NULL;

		return S_OK;
	}

	STDMETHODIMP get_DesignMode(BOOL *pVal)
	{
		*pVal = m_bDesignMode;
		return S_OK;
	}

	STDMETHODIMP put_DesignMode(BOOL newVal)
	{
		m_bDesignMode = newVal;

		// TODO something here

		return S_OK;
	}

	void AddMenuResource(UINT nResourceID)
	{
#if 0
		HMENU hMenu = LoadMenu(_Module.GetResourceInstance(), MAKEINTRESOURCE(nResourceID));

		if (hMenu)
		{
			CMenuResource* pMenuRes = new CMenuResource;
			pMenuRes->m_id = nResourceID;

			CComObject<CMenuItem>::CreateInstance(&pMenuRes->m_menuItem);//.CoCreateInstance(CLSID_MenuItem);
			if (pMenuRes->m_menuItem)
			{
				pMenuRes->m_menuItem->AddRef();

				pMenuRes->m_menuItem->m_uiManager = this;

				BOOL b;
				pMenuRes->m_menuItem->BuildFromHMenu(hMenu, &b);

				m_menuResources.Add(pMenuRes);
			}

			DestroyMenu(hMenu);
		}
#endif
	}

	STDMETHODIMP Load(BSTR pathName)
	{
		m_pathName = pathName;

		TCHAR dir[260];
		TCHAR path[260];
		_splitpath(_bstr_t(pathName), dir, path, NULL, NULL);

		TCHAR pathonly[260];
		_makepath(pathonly, dir, path, NULL, NULL);

	// Load menus
#if 0
		CComQIPtr<ILDOMDocument> xmldoc;
		xmldoc.CoCreateInstance(CLSID_LDOMDocument);
		xmldoc->put_async(VARIANT_FALSE);

		VARIANT_BOOL bsuccess;
		xmldoc->load(m_pathName, &bsuccess);
		if (&bsuccess)
		{
			CComQIPtr<ILDOMElement> documentElement;

			xmldoc->get_documentElement(&documentElement);
			
			if (documentElement)
			{
				CComQIPtr<ILDOMNode> node;
				documentElement->get_firstChild(&node);

				while (node)
				{
					CComQIPtr<ILDOMElement> element = node;
					if (element)
					{
						BSTR btagName;
						element->get_tagName(&btagName);
						if (!wcscmp(btagName, L"menu"))
						{
							CMenuResource* pMenuRes = new CMenuResource;
							BSTR bid;
							element->getAttribute(L"id", &bid);
							if (bid)
							{
								pMenuRes->m_id = atol(_bstr_t(bid));
								//CLSIDFromString(bid, &pMenuRes->m_guid);

								BOOL success;
								CComObject<CMenuItem>::CreateInstance(&pMenuRes->m_menuItem);//.CoCreateInstance(CLSID_MenuItem);
								pMenuRes->m_menuItem->LoadMenuXML(this, element, &success);

								m_menuResources.Add(pMenuRes);

								SysFreeString(bid);
							}
						}
						SysFreeString(btagName);
					}

					CComQIPtr<ILDOMNode> nextSibling;
					node->get_nextSibling(&nextSibling);
					node = nextSibling;
				}
			}
		}
		else
		{
			MessageBox(NULL, "failed to load xml file", "UIManager", MB_OK);
		}
#endif

		return S_OK;
	}

	STDMETHODIMP Save(IStream* stream)
	{
		// TODO: Add your implementation code here

		return S_OK;
	}

#if 0
	STDMETHODIMP FindMenu(HINSTANCE hInst,long ID, IMenuItem **pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = NULL;

		if (TRUE)
		{
			HMENU hMenu = LoadMenu(hInst/*_Module.GetResourceInstance()*/, MAKEINTRESOURCE(ID));

			if (hMenu)
			{
				CComObject<CMenuItem>* pMenu;
				CComObject<CMenuItem>::CreateInstance(&pMenu);
				if (pMenu)
				{
					pMenu->AddRef();

					pMenu->m_uiManager = this;

					BOOL b;
					pMenu->BuildFromHMenu(hMenu, &b);

					*pVal = pMenu;
				}

				DestroyMenu(hMenu);
			}
		}
		else
		{
			for (int i = 0; i < 	m_menuResources.GetSize(); i++)
			{
				if (m_menuResources[i]->m_id == ID)
				{
					*pVal = m_menuResources[i]->m_menuItem;
					(*pVal)->AddRef();
					return S_OK;
				}
			}
		}

		return S_OK;
	}
#endif

	STDMETHODIMP FindCommand(long ID, IUICommand **pResult)
	{
		if (pResult == NULL) return E_POINTER;

		for (int i = 0; i < m_commands.GetSize(); i++)
		{
			CUICommand* command = (CUICommand*)m_commands[i];

			if (command->m_id == ID)
			{
				*pResult = command;
				(*pResult)->AddRef();
				return S_OK;
			}
		}

		*pResult = NULL;

		return S_OK;
	}

	STDMETHODIMP get_DlgCount(long *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_dialogs.GetSize();
		return S_OK;
	}

	STDMETHODIMP GetDlgName(long index, BSTR *pVal)
	{
		if (pVal == NULL) return E_POINTER;

		if (index >= 0 && index < m_dialogs.GetSize())
		{
		//	m_dialogs[index]->GetName(pVal);
		}
		else
			*pVal = NULL;

		return S_OK;
	}
};
