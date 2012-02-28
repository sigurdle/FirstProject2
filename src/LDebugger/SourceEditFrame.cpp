#include "stdafx.h"
#include "LDebugger.h"
#include "SourceEditFrame.h"

namespace System
{
namespace Debugger
{

SourceEditFrame::SourceEditFrame()
{
	m_edit = new SourceEdit;
	m_edit->m_pFrame = this;
	m_edit->set_LineNumbers(true);
	ASSERT(0);
#if 0
	m_edit->set_Background(new UI::SolidColorBrush(new UI::Color(255, 255, 255)));
#endif

	UI::ScrollViewer* scrollViewer = new UI::ScrollViewer;

	scrollViewer->set_Content(m_edit);

	set_VisualTree(scrollViewer);

//	set_VisualTree(pEdit);
}

#if 0
LRESULT MDIChildWnd::OnBuildCompile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
//	pEdit->m_pFrame->m
	{
		STARTUPINFO si;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESTDHANDLES;

		SECURITY_ATTRIBUTES sa;
		// Set up the security attributes struct.
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;

		HANDLE hOutputRead;
		HANDLE hOutputWrite;
		CreatePipe(&hOutputRead, &hOutputWrite, &sa, 0);

		HANDLE hErrorWrite;

// Create a duplicate of the output write handle for the std error
      // write handle. This is necessary in case the child application
      // closes one of its std output handles.
      if (!DuplicateHandle(GetCurrentProcess(),hOutputWrite,
                           GetCurrentProcess(),&hErrorWrite,0,
                           TRUE,DUPLICATE_SAME_ACCESS))
									::MessageBox(NULL, "DuplicateHandle", "", MB_OK);

		HANDLE hInputWrite;
		HANDLE hInputRead;
		CreatePipe(&hInputRead, &hInputWrite, &sa, 0);

		/*
      if (!DuplicateHandle(GetCurrentProcess(),GetStdHandle(STD_INPUT_HANDLE),
                           GetCurrentProcess(),&hInputRead,0,
                           TRUE,DUPLICATE_SAME_ACCESS))
									::MessageBox(NULL, "DuplicateHandle", "", MB_OK);
									*/

		// = GetStdHandle(STD_ERROR_HANDLE);
		si.hStdOutput = hOutputWrite;
		si.hStdError = hErrorWrite;
		si.hStdInput = hInputRead;

		PROCESS_INFORMATION pi;
		ZeroMemory( &pi, sizeof(pi) );

		// Start the child process. 
		if( !CreateProcess(
		//	"C:\\WINNT\\Microsoft.NET\\Framework\\v1.1.4322\\csc.exe",
			NULL,
		//	"/debug+ /out:C:\\HelloCS.exe \"C:\\Program Files\\Microsoft.NET\\SDK\\v1.1\\Samples\\Tutorials\\PlatformIntroduction\\HelloWorld\\CS\\helloCS.cs\"", // Command line. 
			"c:\\MinGW\\bin\\gcc.exe c:\\test.cpp",

			NULL,             // Process handle not inheritable. 
			NULL,             // Thread handle not inheritable. 
			TRUE,            // Set handle inheritance to TRUE. 
			CREATE_NEW_CONSOLE,                // No creation flags. 
			NULL,             // Use parent's environment block. 
			NULL,             // Use parent's starting directory. 
			&si,              // Pointer to STARTUPINFO structure.
			&pi )             // Pointer to PROCESS_INFORMATION structure.
			) 
		{
			::MessageBox(NULL, "CreateProcess failed.", "", MB_OK);
		}

// Close pipe handles (do not continue to modify the parent).
		// You need to make sure that no handles to the write end of the
		// output pipe are maintained in this process or else the pipe will
		// not close when the child process exits and the ReadFile will hang.
		if (!CloseHandle(hOutputWrite)) ::MessageBox(NULL, "CloseHandle", "", MB_OK);
      if (!CloseHandle(hInputRead )) ::MessageBox(NULL, "CloseHandle", "", MB_OK);
      if (!CloseHandle(hErrorWrite)) ::MessageBox(NULL, "CloseHandle", "", MB_OK);

		// Wait until child process exits.
		WaitForSingleObject(pi.hProcess, INFINITE);

		std::string str;

		while (TRUE)
		{
			char buf[60];
			ULONG nRead;
			if (!ReadFile(hOutputRead, buf, 60, &nRead, NULL) || nRead == 0)
			{
				if (GetLastError() == ERROR_BROKEN_PIPE)
					break; // pipe done - normal exit path.
				else
					::MessageBox(NULL, "ReadFile", "", MB_OK); // Something bad happened.
			}

			str += std::string(buf, nRead);
		}
		
		// Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		ASSERT(0);
#if 0
		pEdit->m_pFrame->m_pFrame->m_wndMessages.SetWindowText(str);
#endif

	//	tabpanels->appendChild(p, NULL);
	}

	return 0;
}

LRESULT MDIChildWnd::OnEditLineWrap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	pEdit->put_WordWrap(!pEdit->get_WordWrap());
	return 0;
}

LRESULT MDIChildWnd::OnViewLineNumbers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	pEdit->put_LineNumbers(!pEdit->get_LineNumbers());
	return 0;
}

#endif

}
}
