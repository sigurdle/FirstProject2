// RegisteredSnapinsDlg.cpp : Implementation of CRegisteredSnapinsDlg
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "RegisteredSnapinsDlg.h"

extern "C" GUID CATID_LXFrameworkPlugin;

#include "AddinsDlg.h"
#include "LXFrameworkFrame.h"

class CAvailItem
{
public:
	CString m_name;
	CLSID m_clsid;
};

/////////////////////////////////////////////////////////////////////////////
// CRegisteredSnapinsDlg

LRESULT CRegisteredSnapinsDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_list = GetDlgItem(IDC_SNAPINS_LIST);

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT;// | LVCF_SUBITEM;//nMask;
	lvc.fmt = LVCFMT_LEFT;//nFmt;
	lvc.pszText = (LPTSTR)_T("Name");
	lvc.cx = 140;//GetStringWidth(lvc.pszText) + 15;
	//if(nMask & LVCF_SUBITEM)
	lvc.iSubItem = 0;//(nSubItem != -1) ? nSubItem : nItem;
	m_list.InsertColumn(0/*nItem*/, &lvc);

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;//nMask;
	lvc.fmt = LVCFMT_LEFT;//nFmt;
	lvc.pszText = (LPTSTR)_T("Vendor");
	lvc.cx = 140;//GetStringWidth(lvc.pszText) + 15;
	//if(nMask & LVCF_SUBITEM)
	lvc.iSubItem = 1;//(nSubItem != -1) ? nSubItem : nItem;
	m_list.InsertColumn(1/*nItem*/, &lvc);

//	m_list.AddColumn("Name", 0);
//	m_list.AddColumn("Vendor", 1);

	{
		CComPtr<ICatInformation> catinfo;
		HRESULT hr = S_OK;
 
		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ICatInformation,
			(LPVOID*)&catinfo);

		if(SUCCEEDED(hr))
		{
			CRegKey clsidkey;
			clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

			CATID impl[1];
			impl[0] = CATID_LXFrameworkPlugin;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				/*
				CComObject<CPluginClass>* pPluginClass;

				CComObject<CPluginClass>::CreateInstance(&pPluginClass);
				if (pPluginClass)
				*/
				{
					CAvailItem* pItem = new CAvailItem;

					pItem->m_clsid = clsid;

				// Get name
					LPOLESTR clsidstr;
					StringFromCLSID(clsid, &clsidstr);

					CRegKey key;
					key.Open(clsidkey, _bstr_t(clsidstr));

					CoTaskMemFree(clsidstr);

					TCHAR name[256];
					DWORD n = 255;
					key.QueryValue(name, NULL, &n);

					pItem->m_name = name;

					/*
					pPluginClass->m_name = name;

					pPluginClass->m_clsid = clsid;
					pPluginClass->AddRef();
					m_plugins.Add(pPluginClass);
					*/

					LVITEM item;
					item.mask = LVIF_TEXT | LVIF_PARAM;
					item.iItem = 0;//nItem;
					item.iSubItem = 0;
					item.pszText = (LPTSTR)name;
					//item.state = nState;
					//item.stateMask = nStateMask;
					//item.iImage = nImage;
					item.lParam = (LPARAM)pItem;
					m_list.InsertItem(&item);
				}
			}
		}
	}

	return 1;  // Let the system set the focus
}

LRESULT CRegisteredSnapinsDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	LVITEM item;
	item.mask = LVIF_PARAM;
	m_list.GetSelectedItem(&item);

	CAvailItem* pItem = (CAvailItem*)item.lParam;

	CComObject<CLXFrameworkAddinSite>* pAddinSite;
	CComObject<CLXFrameworkAddinSite>::CreateInstance(&pAddinSite);
	if (pAddinSite)
	{
		pAddinSite->AddRef();

		if (SUCCEEDED(pAddinSite->m_p.CoCreateInstance(pItem->m_clsid)))
		{
			pAddinSite->AddRef();

			pAddinSite->m_clsid = pItem->m_clsid;
			pAddinSite->m_name = pItem->m_name;

			pAddinSite->SetFrame(m_pParent->m_pFrame);

			m_pParent->m_pFrame->m_addins.Add(pAddinSite);

			pAddinSite->m_p->SetSite(pAddinSite);

			m_pParent->m_list.DeleteAllItems();
			m_pParent->FillList();
		}
		else
		{
			MessageBox("Failed to load Add-in", "LXFramework", MB_OK);
		}

		pAddinSite->Release();
	}

	return 0;
}
