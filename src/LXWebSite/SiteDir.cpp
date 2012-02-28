#include "stdafx.h"
#include "LXWebSite.h"
#include "LXWebSite2.h"
#include "WebSite.h"
#include "SiteFilesView.h"

#if 0
void CSiteDir::ScanFTPFiles(BOOL bCheckExisting/* = FALSE*/)
{
	ATLASSERT(0);
	HINTERNET hFindFile;
	WIN32_FIND_DATA	wfd;

	TCHAR	search[MAX_PATH];
	wsprintf(search, "*.*", m_pathName);

	if (bCheckExisting)
	{
// Assume that all files have been deleted
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
			pItem->m_bFoundOnDisk = FALSE;
		}
	}

	if ((hFindFile = FtpFindFirstFile(
		m_pWebSite->m_hInternetFtp,
		search,
		&wfd,
		INTERNET_FLAG_RELOAD,
		0/*dwContext*/)) != NULL/*INVALID_HANDLE_VALUE*/)
	{
		do
		{
			if (wfd.cFileName[0] != '.')
			{
				CSiteItem* pExistingItem = NULL;

				if (bCheckExisting)
				{
					pExistingItem = FileExists(wfd.cFileName, (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)? 1: 2);
					if (pExistingItem)
					{
						pExistingItem->m_bFoundOnDisk = TRUE;
					}
				}

				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					CSiteDir* pDir;

					if (pExistingItem)
					{
						pDir = (CSiteDir*)pExistingItem;
					}
					else
					{
						pDir = new CSiteDir;
						pDir->m_pWebSite = m_pWebSite;

						_makepath(pDir->m_pathName.GetBuffer(512), NULL, m_pathName, wfd.cFileName, NULL);
						pDir->m_pathName.ReleaseBuffer();
//						pDir->m_name = wfd.cFileName;
						pDir->m_wfd = wfd;
						pDir->m_bFoundOnDisk = TRUE;

						AddChildTail(pDir);

						pDir->AddSiteItemToDatabase();
					}

				//	pDir->ScanFiles(bCheckExisting);
				}
				else
				{
					if (pExistingItem)
					{
						CSiteFile* pFile = (CSiteFile*)pExistingItem;

						if (pFile->m_wfd.nFileSizeLow != wfd.nFileSizeLow ||
							pFile->m_wfd.nFileSizeHigh != wfd.nFileSizeHigh ||							
							pFile->m_wfd.dwFileAttributes != wfd.dwFileAttributes ||
							memcmp(&pFile->m_wfd.ftLastWriteTime, &wfd.ftLastWriteTime, sizeof(FILETIME)) ||
							memcmp(&pFile->m_wfd.ftCreationTime, &wfd.ftCreationTime, sizeof(FILETIME)))
						{
							pFile->m_wfd = wfd;
						}
					}
					else
					{
						CSiteFile* pFile = new CSiteFile;
						pFile->m_pWebSite = m_pWebSite;

						pFile->m_bFoundOnDisk = TRUE;
//						pFile->m_name = wfd.cFileName;	// ??
						pFile->m_wfd = wfd;

						AddChildTail(pFile);
					}
				}
			}
		}
		while (InternetFindNextFile(hFindFile, &wfd));

		InternetCloseHandle(hFindFile);
	}

//	DWORD lastError = GetLastError();
//	if (lastError) WinError(lastError);

	if (bCheckExisting)
	{
	// Traverse all items, and remove the files that no longer exist on disk
		UPOSITION pos = m_childList.GetHeadPosition();
		while (pos)
		{
			UPOSITION pos2 = pos;
			CSiteItem* pItem = (CSiteItem*)m_childList.GetNext(pos);
			if (!pItem->m_bFoundOnDisk)
			{
			//	if (*pActive == pItem) *pActive = NULL;

				//pItem->RemoveFromDatabase();

				pItem->m_parent->m_childList.RemoveAt(pos2);
				delete pItem;
			}
		}
	}
}
#endif
