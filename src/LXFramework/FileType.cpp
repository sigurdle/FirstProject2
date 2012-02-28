#include "stdafx.h"
//#include "LXFramework.h"

#include "FileType.h"

#define AFX_STATIC_DATA static

AFX_STATIC_DATA const TCHAR _afxShellOpenFmt[] = _T("%s\\shell\\open\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintFmt[] = _T("%s\\shell\\print\\%s");
AFX_STATIC_DATA const TCHAR _afxShellPrintToFmt[] = _T("%s\\shell\\printto\\%s");
AFX_STATIC_DATA const TCHAR _afxDefaultIconFmt[] = _T("%s\\DefaultIcon");
AFX_STATIC_DATA const TCHAR _afxShellNewFmt[] = _T("%s\\ShellNew");

#define DEFAULT_ICON_INDEX 0

AFX_STATIC_DATA const TCHAR _afxIconIndexFmt[] = _T(",%d");
AFX_STATIC_DATA const TCHAR _afxCommand[] = _T("command");
AFX_STATIC_DATA const TCHAR _afxOpenArg[] = _T(" \"%1\"");
AFX_STATIC_DATA const TCHAR _afxPrintArg[] = _T(" /p \"%1\"");
AFX_STATIC_DATA const TCHAR _afxPrintToArg[] = _T(" /pt \"%1\" \"%2\" \"%3\" \"%4\"");
AFX_STATIC_DATA const TCHAR _afxDDEArg[] = _T(" /dde");

AFX_STATIC_DATA const TCHAR _afxDDEExec[] = _T("ddeexec");
AFX_STATIC_DATA const TCHAR _afxDDEOpen[] = _T("[open(\"%1\")]");
AFX_STATIC_DATA const TCHAR _afxDDEPrint[] = _T("[print(\"%1\")]");
AFX_STATIC_DATA const TCHAR _afxDDEPrintTo[] = _T("[printto(\"%1\",\"%2\",\"%3\",\"%4\")]");

AFX_STATIC_DATA const TCHAR _afxShellNewValueName[] = _T("NullFile");
AFX_STATIC_DATA const TCHAR _afxShellNewValue[] = _T("");

BOOL _SetRegKey(LPCTSTR lpszKey, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL)
{
	if (lpszValueName == NULL)
	{
		if (::RegSetValue(HKEY_CLASSES_ROOT, lpszKey, REG_SZ,
			  lpszValue, lstrlen(lpszValue) * sizeof(TCHAR)) != ERROR_SUCCESS)
		{
			TRACE("Warning: registration database update failed for key '%s'.\n",
				lpszKey);
			return FALSE;
		}
		return TRUE;
	}
	else
	{
		HKEY hKey;

		if(::RegCreateKey(HKEY_CLASSES_ROOT, lpszKey, &hKey) == ERROR_SUCCESS)
		{
			LONG lResult = ::RegSetValueEx(hKey, lpszValueName, 0, REG_SZ,
				(CONST BYTE*)lpszValue, (lstrlen(lpszValue) + 1) * sizeof(TCHAR));

			if(::RegCloseKey(hKey) == ERROR_SUCCESS && lResult == ERROR_SUCCESS)
				return TRUE;
		}
		TRACE("Warning: registration database update failed for key '%s'.\n", lpszKey);
		return FALSE;
	}
}

#define _countof(array) (sizeof(array)/sizeof(array[0]))

BOOL _DeleteRegKey(LPCTSTR lpszKey)
{
	// copy the string
	LPTSTR lpszKeyCopy = _tcsdup(lpszKey);
	LPTSTR lpszLast = lpszKeyCopy + lstrlen(lpszKeyCopy);

	// work until the end of the string
	while (lpszLast != NULL)
	{
		*lpszLast = '\0';
		lpszLast = _tcsdec(lpszKeyCopy, lpszLast);

		// try to open that key
		HKEY hKey;
		if (::RegOpenKey(HKEY_CLASSES_ROOT, lpszKeyCopy, &hKey) != ERROR_SUCCESS)
			break;

		// enumerate the keys underneath
		TCHAR szScrap[_MAX_PATH+1];
		DWORD dwLen = _countof(szScrap);
		BOOL bItExists = FALSE;

		if (::RegEnumKey(hKey, 0, szScrap, dwLen) == ERROR_SUCCESS)
			bItExists = TRUE;
		::RegCloseKey(hKey);

		// found one?  quit looping
		if (bItExists)
			break;

		// otherwise, delete and find the previous backwhack
		::RegDeleteKey(HKEY_CLASSES_ROOT, lpszKeyCopy);
		lpszLast = _tcsrchr(lpszKeyCopy, '\\');
	}

	// release the string and return
	free(lpszKeyCopy);
	return TRUE;
}

#if 0
void CFileType::GetExtensionStringList(CStringList& extlist)
{
	for (int i = 0; i < m_extensions.GetSize(); i++)
	{
		extlist.Add(m_extensions[i]);
	}
/*
	ATLASSERT(!m_exts.IsEmpty());

	LPCTSTR exts = (LPCTSTR)m_exts;
	char* p = (char*)exts;

	while (*p != 0)
	{
		// skip *
		p += 1;

		TCHAR* p2 = p;
		while (*p2 != ';' && *p2 != 0) p2++;

		int len = p2-p;
		TCHAR buf[16] = {0};
		strncpy(buf, p, len); 
		extlist.Add(CUString(buf));

		if (*p2 == 0) break;
		p = p2+1;
	}
	*/
}
#endif

void CFileType::UpdateFileTypeRegisteredFromRegistry()
{
	CString strFileTypeId = "LXFrameWork." + m_id;

	int unregistered = 0;

//	POSITION pos = extlist.GetHeadPosition();
//	while (pos)
	for (int i = 0; i < m_extensions.GetSize(); i++)
	{
		CUString ext = m_extensions[i]->m_ext;//.GetNext(pos);

		TCHAR buf[256] = {0};
		long cb = sizeof(buf);

		m_extensions[i]->m_registeredFromRegistry = FALSE;

		if (RegQueryValue(HKEY_CLASSES_ROOT, ext, buf, &cb))
		{
			unregistered++;
			continue;
		}

		if (strcmp(strFileTypeId, buf) != 0)
		{
			unregistered++;
			continue;
		}

		m_extensions[i]->m_registeredFromRegistry = TRUE;
	}

	if (unregistered == 0)
		m_registeredFromRegistry = 1;	// All were registered by MMStudio
	else if (unregistered == m_extensions.GetSize())
		m_registeredFromRegistry = 0;	// None were registered by MMStudio
	else
		m_registeredFromRegistry = 2;	// Some, but not all were registered by MMStudio
}

void CFileType::SetFileTypeRegistered(int registered)
{
	m_registered = registered;
}

int CFileType::IsFileTypeRegistered()
{
	return m_registered;
}

/*
HKEY_CLASSES_ROOT 
   .doc=AWordProcessor 

The value name (.doc) specifies the file name extension, and the value (AWordProcessor) denotes the key name that contains the information about the application handling the file name extension. 

The application identifier key is the second registry entry made by an application handling files. 

HKEY_CLASSES_ROOT 
   AWordProcessor=A Word Processor 
*/

void AppWriteProfileString(LPCTSTR section, LPCTSTR key, LPCTSTR value)
{
	LPCTSTR fileName = "C:\\LXFramework.ini";
	WritePrivateProfileString(section, key, value, fileName);
}

CUString AppGetProfileString(LPCTSTR section, LPCTSTR key, LPCTSTR defvalue)
{
	LPCTSTR fileName = "C:\\LXFramework.ini";

	TCHAR buf[1024];
	GetPrivateProfileString(section, key, defvalue, buf, sizeof(buf), fileName);

	return buf;
}

BOOL CFileType::RegisterFileType()
{
//	CStringList extlist;
//	GetExtensionStringList(extlist);

	TCHAR pathname[512];
	GetModuleFileName(_Module.m_hInst, pathname, sizeof(pathname)); 
	CString strPathName = pathname;

	CUString strOpenCommandLine = strPathName;
	CUString strPrintCommandLine = strPathName;
	CUString strPrintToCommandLine = strPathName;
	CUString strDefaultIconCommandLine = strPathName;

	CUString strTemp;

	CUString strFileTypeId = "LXFrameWork." + m_id;
	CUString strFileTypeName = m_descr;

// Register class

	// first register the type ID of our server
	if (!_SetRegKey(strFileTypeId, strFileTypeName))
		return FALSE;       // just skip it

	// path\shell\open\ddeexec = [open("%1")]
	strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId,
		(LPCTSTR)_afxDDEExec);
	if (!_SetRegKey(strTemp, _afxDDEOpen))
		return FALSE;//continue;       // just skip it

	BOOL bCompat = TRUE;

	if (bCompat)
	{
		// path\shell\print\ddeexec = [print("%1")]
		strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId,
			(LPCTSTR)_afxDDEExec);
		if (!_SetRegKey(strTemp, _afxDDEPrint))
			return FALSE;//continue;       // just skip it

		// path\shell\printto\ddeexec = [printto("%1","%2","%3","%4")]
		strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId,
			(LPCTSTR)_afxDDEExec);
		if (!_SetRegKey(strTemp, _afxDDEPrintTo))
			return FALSE;//continue;       // just skip it

		// path\shell\open\command = path /dde
		// path\shell\print\command = path /dde
		// path\shell\printto\command = path /dde
		strOpenCommandLine += _afxDDEArg;
		strPrintCommandLine += _afxDDEArg;
		strPrintToCommandLine += _afxDDEArg;
	}
	else
	{
		strOpenCommandLine += _afxOpenArg;
	}

	// path\shell\open\command = path filename
	strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId,
		(LPCTSTR)_afxCommand);
	if (!_SetRegKey(strTemp, strOpenCommandLine))
		return FALSE;       // just skip it

	if (bCompat)
	{
		// path\shell\print\command = path /p filename
		strTemp.Format(_afxShellPrintFmt, (LPCTSTR)strFileTypeId,
			(LPCTSTR)_afxCommand);
		if (!_SetRegKey(strTemp, strPrintCommandLine))
			return FALSE;//continue;       // just skip it

		// path\shell\printto\command = path /pt filename printer driver port
		strTemp.Format(_afxShellPrintToFmt, (LPCTSTR)strFileTypeId,
			(LPCTSTR)_afxCommand);
		if (!_SetRegKey(strTemp, strPrintToCommandLine))
			return FALSE;//continue;       // just skip it
	}

// Register each extension belonging to the class
//	POSITION pos = extlist.GetHeadPosition();
//	while (pos)
//	{
//		CString ext = extlist.GetNext(pos);
	for (int i = 0; i < m_extensions.GetSize(); i++)
	{
		CUString ext = m_extensions[i]->m_ext;//.GetNext(pos);

	// Get previous class of this extension
		TCHAR buf[256] = {0};
		long cb = sizeof(buf);
		if (!RegQueryValue(HKEY_CLASSES_ROOT, ext, buf, &cb))
		{
			if (strcmp(strFileTypeId, buf) != 0)
			{
				AppWriteProfileString("OldFileTypes", ext, buf);
			}
		}

	// Register the extension
		if (!_SetRegKey(ext, strFileTypeId))
				continue;       // just skip it
	}

	return TRUE;
}

void CFileType::UnRegisterFileType()
{
//	CStringList extlist;
//	GetExtensionStringList(extlist);

//	TCHAR pathname[512];
//	GetModuleFileName(AfxGetInstanceHandle(),pathname, sizeof(pathname)); 
//	CString strPathName = pathname;

//	CString strOpenCommandLine = strPathName;
//	CString strPrintCommandLine = strPathName;
//	CString strPrintToCommandLine = strPathName;
//	CString strDefaultIconCommandLine = strPathName;
//	strOpenCommandLine += _afxOpenArg;

	CUString strTemp;

	CUString strFileTypeId = "LXFrameWork." + m_id;
	CUString strFileTypeName = m_descr;

/*
	// first register the type ID of our server
	if (!_SetRegKey(strFileTypeId, strFileTypeName))
		return FALSE;       // just skip it

	// path\shell\open\command = path filename
	strTemp.Format(_afxShellOpenFmt, (LPCTSTR)strFileTypeId,
		(LPCTSTR)_afxCommand);
	if (!_SetRegKey(strTemp, strOpenCommandLine))
		return FALSE;       // just skip it
*/

// UnRegister each extension belonging to this filetype
//	POSITION pos = extlist.GetHeadPosition();
//	while (pos)
//	{
//		CString ext = extlist.GetNext(pos);
	for (int i = 0; i < m_extensions.GetSize(); i++)
	{
		CUString ext = m_extensions[i]->m_ext;//.GetNext(pos);

	// Get previous registered class of this extension
		CUString strPrevClass;
		strPrevClass = AppGetProfileString("OldFileTypes", ext, "");

		if (!strPrevClass.IsEmpty())
		{
			// Register the old extension class
			_SetRegKey(ext, strPrevClass);
		}
		else	// No previous registration, just delete the key
		{
			_DeleteRegKey(ext);
		}
	}
}

void CFileTypes::UpdateFromRegistry()
{
	for (int i = 0; i < m_fileTypes.GetSize(); i++)
	{
		m_fileTypes[i]->UpdateFileTypeRegisteredFromRegistry();
		m_fileTypes[i]->m_registered = m_fileTypes[i]->m_registeredFromRegistry;
	}
}

void CFileTypes::UpdateToRegistry()
{
	for (int i = 0; i < m_fileTypes.GetSize(); i++)
	{
		m_fileTypes[i]->UpdateFileTypeRegisteredFromRegistry();	// Just in case

		if (m_fileTypes[i]->m_registered == 1)
		{
			m_fileTypes[i]->RegisterFileType();
		}
	}

	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, 0, 0);
}
