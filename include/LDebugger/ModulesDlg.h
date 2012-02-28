// ModulesDlg.h : Declaration of the CModulesDlg

#ifndef __MODULESDLG_H_
#define __MODULESDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

/////////////////////////////////////////////////////////////////////////////
// CModulesDlg
class CModulesDlg : 
	public CAxDialogImpl<CModulesDlg>
{
public:
	CModulesDlg()
	{
	}

	~CModulesDlg()
	{
	}

	HANDLE m_hProcess;

	enum { IDD = IDD_MODULESDLG };

BEGIN_MSG_MAP(CModulesDlg)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_ID_HANDLER(IDOK, OnOK)
	COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CListViewCtrl list(GetDlgItem(IDC_MODULELIST));

		list.InsertColumn(0, "Module", 0, 100, 0);
		list.InsertColumn(1, "Address", 0, 124, 0);
		list.InsertColumn(2, "Path", 0, 220, 0);
		list.InsertColumn(3, "Order", 0, 42, 0);

		HMODULE hModules[1000];

		DWORD cbNeeded;
		EnumProcessModules(m_hProcess, hModules, 1000*sizeof(HMODULE), &cbNeeded);
		DWORD nModules = cbNeeded / sizeof(HMODULE);

		for (int j =  0; j < nModules; j++)
		{
			char name[512];
			name[0] = 0;
			GetModuleBaseName(m_hProcess, hModules[j], name, 511);
		//	printf("%s", name);

			char filename[1024];
			filename[0] = 0;
			GetModuleFileNameEx(m_hProcess, hModules[j], filename, 1023);

			MODULEINFO mi;
			GetModuleInformation(m_hProcess, hModules[j], &mi, sizeof(mi));

			//std::strstream strstream;
			//strstream << (DWORD)mi.lpBaseOfDll << " " << (DWORD)mi.lpBaseOfDll + mi.SizeOfImage;
			char address[256];
			sprintf(address, "%8.8X - %8.8X", (DWORD)mi.lpBaseOfDll, (DWORD)mi.lpBaseOfDll+mi.SizeOfImage);

			char order[6];
			sprintf(order, "%d", j+1);

			list.AddItem(j, 0, name);
			list.AddItem(j, 1, address);
			list.AddItem(j, 2, filename);
			list.AddItem(j, 3, order);

		//	list.SetItemData(index, processIds[i]);

	//		processmap.insert(typrocessmap::value_type(name, processIds[i]));
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__MODULESDLG_H_
