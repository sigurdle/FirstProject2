// AttachProcessDlg.h : Declaration of the CAttachProcessDlg

#ifndef __ATTACHPROCESSDLG_H_
#define __ATTACHPROCESSDLG_H_

#include "resource.h"       // main symbols
#include <atlhost.h>

//typedef std::map<std::string, DWORD> typrocessmap;

/////////////////////////////////////////////////////////////////////////////
// CAttachProcessDlg
class CAttachProcessDlg : 
	public CAxDialogImpl<CAttachProcessDlg>
{
public:
	CAttachProcessDlg()
	{
	}

	~CAttachProcessDlg()
	{
	}

	DWORD m_dwProcessId;

	enum { IDD = IDD_ATTACHPROCESSDLG };

BEGIN_MSG_MAP(CAttachProcessDlg)
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
		CListBox list = GetDlgItem(IDC_PROCESSLIST);

		DWORD processIds[4000];
		DWORD cbNeeded;
		EnumProcesses(processIds, 4000*sizeof(DWORD), &cbNeeded);

		DWORD nProcesses = cbNeeded / sizeof(DWORD);

//		typrocessmap processmap;

		for (int i = 0; i < nProcesses; i++)
		{
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS/* | PROCESS_QUERY_INFORMATION | PROCESS_DUP_HANDLE*/, FALSE, processIds[i]);
			if (hProcess)
			{
				HMODULE hModules[400];

				EnumProcessModules(hProcess, hModules, 400*sizeof(HMODULE), &cbNeeded);
				DWORD nModules = cbNeeded / sizeof(HMODULE);

				for (int j =  0; j < 1/*nModules*/; j++)
				{
					char name[512] = {0};
					GetModuleBaseName(hProcess, hModules[j], name, 511);
				//	printf("%s", name);

					int index = list.AddString(name);
					list.SetItemData(index, processIds[i]);

			//		processmap.insert(typrocessmap::value_type(name, processIds[i]));
				}

				CloseHandle(hProcess);
			}
		}

		return 1;  // Let the system set the focus
	}

	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		CListBox list = GetDlgItem(IDC_PROCESSLIST);
		int index = list.GetCurSel();
		if (index == -1)
		{
			MessageBox("You must select a process", "LDebugger", MB_OK);
			return 0;
		}

		m_dwProcessId = list.GetItemData(index);
		
		EndDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		EndDialog(wID);
		return 0;
	}
};

#endif //__ATTACHPROCESSDLG_H_
