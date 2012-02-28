#include "stdafx.h"
#include "GUI2.h"

namespace System
{

// static
String KnownFolders::GetPathOf(const KNOWNFOLDERID& folderid)
{
#if 1

	// Vista, Windows 7
	CoString str;
	HRESULT hr = SHGetKnownFolderPath(folderid, KF_FLAG_DONT_VERIFY | KF_FLAG_DONT_UNEXPAND,
		nullptr,
		&str);

	return str.data();

	int csidl;

		 if (folderid == FOLDERID_AdminTools)		csidl = CSIDL_ADMINTOOLS;
	else if (folderid == FOLDERID_Documents)			csidl = CSIDL_MYDOCUMENTS;
	else if (folderid == FOLDERID_Pictures)			csidl = CSIDL_MYPICTURES;
	else if (folderid == FOLDERID_Videos)			csidl = CSIDL_MYVIDEO;
	else if (folderid == FOLDERID_Music)				csidl = CSIDL_MYMUSIC;
	else if (folderid == FOLDERID_Favorites)			csidl = CSIDL_FAVORITES;
	else if (folderid == FOLDERID_History)			csidl = CSIDL_HISTORY;
	else if (folderid == FOLDERID_Startup)			csidl = CSIDL_STARTUP;
	else if (folderid == FOLDERID_SendTo)			csidl = CSIDL_SENDTO;
	else if (folderid == FOLDERID_ComputerFolder)	csidl = CSIDL_DRIVES;
	else if (folderid == FOLDERID_NetworkFolder)		csidl = CSIDL_COMPUTERSNEARME;
	else if (folderid == FOLDERID_Recent)			csidl = CSIDL_RECENT;
	else if (folderid == FOLDERID_PrintersFolder)	csidl = CSIDL_PRINTERS;
	else if (folderid == FOLDERID_Templates)			csidl = CSIDL_TEMPLATES;
	else if (folderid == FOLDERID_RecycleBinFolder)	csidl = CSIDL_BITBUCKET;
	else if (folderid == FOLDERID_ProgramFiles)		csidl = CSIDL_PROGRAM_FILES;
	else if (folderid == FOLDERID_Windows)			csidl = CSIDL_WINDOWS;
	else if (folderid == FOLDERID_CommonAdminTools)	csidl = CSIDL_COMMON_ADMINTOOLS;
	else if (folderid == FOLDERID_CommonTemplates)	csidl = CSIDL_COMMON_TEMPLATES;
	else if (folderid == FOLDERID_PublicDocuments)	csidl = CSIDL_COMMON_DOCUMENTS;
	else if (folderid == FOLDERID_PublicPictures)	csidl = CSIDL_COMMON_PICTURES;
	else if (folderid == FOLDERID_PublicVideos)		csidl = CSIDL_COMMON_VIDEO;
	else if (folderid == FOLDERID_PublicMusic)		csidl = CSIDL_COMMON_MUSIC;
	else
	{
		return nullptr;
	}

	WCHAR path[512];
	ThrowHr(::SHGetFolderPath(nullptr, csidl, nullptr, 0, path));
	return path;

#else
	ComPtr<IKnownFolderManager> knownFolderManager;
	knownFolderManager.CoCreateInstance(CLSID_KnownFolderManager);
	SHGetSpecialFolder(
	ComPtr<IKnownFolder> folder;
	knownFolderManager->GetFolder(folderid, &folder);

	CoString wstr;
	folder->GetPath(KF_FLAG_DONT_VERIFY, &wstr);

	return wstr.data();
#endif
}

}	// System
