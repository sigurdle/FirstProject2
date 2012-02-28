#include "stdafx.h"

typedef WINSHELLAPI BOOL (WINAPI *fnPickIconDlg)(HWND hWndParent, LPTSTR pszFilename, LPDWORD pdwBufferSize, LPDWORD pdwIndex);

BOOL SelectIconA(HWND hWndParent, LPSTR lpszFilename, DWORD dwBufferSize, DWORD *pdwIndex)
{
	BOOL result = FALSE;
	OSVERSIONINFO versioninfo;
	versioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&versioninfo);
	HMODULE hShell32 = ::LoadLibrary(_T("shell32.dll"));
	if (hShell32)
	{
		fnPickIconDlg PickIconDlg = (fnPickIconDlg)::GetProcAddress(hShell32, (LPCSTR)62);
		if (PickIconDlg)
		{
			if (versioninfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
			{
				LPWSTR pszWideName = new WCHAR[dwBufferSize];
				::MultiByteToWideChar(CP_ACP, 0, lpszFilename, -1, pszWideName, dwBufferSize);
				result = PickIconDlg(hWndParent, (LPTSTR)pszWideName, &dwBufferSize, pdwIndex);
				WideCharToMultiByte(CP_ACP, 0, pszWideName, -1, lpszFilename, dwBufferSize, NULL, NULL);
				delete[] pszWideName;
			}
			else
			{
				result = PickIconDlg(hWndParent, (LPTSTR)lpszFilename, &dwBufferSize, pdwIndex);
			}
		}
		FreeLibrary(hShell32);
	}
	return result;
}


BOOL SelectIconW(HWND hWndParent, LPWSTR lpszFilename, DWORD dwBufferSize, DWORD *pdwIndex)
{
	BOOL result = FALSE;
	OSVERSIONINFO versioninfo;
	versioninfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&versioninfo);
	HMODULE hShell32 = ::LoadLibrary(_T("shell32.dll"));
	if (hShell32)
	{
		fnPickIconDlg PickIconDlg = (fnPickIconDlg)::GetProcAddress(hShell32, (LPCSTR)62);
		if (PickIconDlg)
		{
			if (versioninfo.dwPlatformId != VER_PLATFORM_WIN32_NT)
			{
				LPSTR pszMBName = new CHAR[dwBufferSize];
				WideCharToMultiByte(CP_ACP, 0, lpszFilename, -1, pszMBName, dwBufferSize, NULL, NULL);
				result = PickIconDlg(hWndParent, (LPTSTR)pszMBName, &dwBufferSize, pdwIndex);
				MultiByteToWideChar(CP_ACP, 0, pszMBName, -1, lpszFilename, dwBufferSize);
				delete[] pszMBName;
			}
			else
			{
				result = PickIconDlg(hWndParent, (LPTSTR)lpszFilename, &dwBufferSize, pdwIndex);
			}
		}
		FreeLibrary(hShell32);
	}
	return result;
}


