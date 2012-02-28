// WebDAVBrowser.cpp : Implementation of CWebDAVBrowser

#include "stdafx.h"
#include "FTPMod.h"
//#include "WebDAVBrowser.h"

#include <wininet.h>

// these are defined by WININET.H

#define AFX_INET_SERVICE_FTP        INTERNET_SERVICE_FTP
#define AFX_INET_SERVICE_HTTP       INTERNET_SERVICE_HTTP
#define AFX_INET_SERVICE_GOPHER     INTERNET_SERVICE_GOPHER

// these are types that MFC parsing functions understand

#define AFX_INET_SERVICE_UNK        0x1000
#define AFX_INET_SERVICE_FILE       (AFX_INET_SERVICE_UNK+1)
#define AFX_INET_SERVICE_MAILTO     (AFX_INET_SERVICE_UNK+2)
#define AFX_INET_SERVICE_MID        (AFX_INET_SERVICE_UNK+3)
#define AFX_INET_SERVICE_CID        (AFX_INET_SERVICE_UNK+4)
#define AFX_INET_SERVICE_NEWS       (AFX_INET_SERVICE_UNK+5)
#define AFX_INET_SERVICE_NNTP       (AFX_INET_SERVICE_UNK+6)
#define AFX_INET_SERVICE_PROSPERO   (AFX_INET_SERVICE_UNK+7)
#define AFX_INET_SERVICE_TELNET     (AFX_INET_SERVICE_UNK+8)
#define AFX_INET_SERVICE_WAIS       (AFX_INET_SERVICE_UNK+9)
#define AFX_INET_SERVICE_AFS        (AFX_INET_SERVICE_UNK+10)
#define AFX_INET_SERVICE_HTTPS      (AFX_INET_SERVICE_UNK+11)

BOOL _AfxParseURLWorker(LPCTSTR pstrURL,
	LPURL_COMPONENTS lpComponents, DWORD& dwServiceType,
	INTERNET_PORT& nPort, DWORD dwFlags)
{
	// this function will return bogus stuff if lpComponents
	// isn't set up to copy the components

	ASSERT(lpComponents != NULL && pstrURL != NULL);
	if (lpComponents == NULL || pstrURL == NULL)
		return FALSE;
	ASSERT(lpComponents->dwHostNameLength == 0 ||
			lpComponents->lpszHostName != NULL);
	ASSERT(lpComponents->dwUrlPathLength == 0 ||
			lpComponents->lpszUrlPath != NULL);
	ASSERT(lpComponents->dwUserNameLength == 0 ||
			lpComponents->lpszUserName != NULL);
	ASSERT(lpComponents->dwPasswordLength == 0 ||
			lpComponents->lpszPassword != NULL);

//	ASSERT(AfxIsValidAddress(lpComponents, sizeof(URL_COMPONENTS), TRUE));

	LPTSTR pstrCanonicalizedURL;
	TCHAR szCanonicalizedURL[INTERNET_MAX_URL_LENGTH];
	DWORD dwNeededLength = INTERNET_MAX_URL_LENGTH;
	BOOL bRetVal;
	BOOL bMustFree = FALSE;
	DWORD dwCanonicalizeFlags = dwFlags &
		(ICU_NO_ENCODE | ICU_DECODE | ICU_NO_META |
		ICU_ENCODE_SPACES_ONLY | ICU_BROWSER_MODE);
	DWORD dwCrackFlags = dwFlags & (ICU_ESCAPE | ICU_USERNAME);

	bRetVal = InternetCanonicalizeUrl(pstrURL, szCanonicalizedURL,
		&dwNeededLength, dwCanonicalizeFlags);

	if (!bRetVal)
	{
		if (::GetLastError() != ERROR_INSUFFICIENT_BUFFER)
			return FALSE;

		pstrCanonicalizedURL = new TCHAR[dwNeededLength];
		bMustFree = TRUE;
		bRetVal = InternetCanonicalizeUrl(pstrURL, pstrCanonicalizedURL,
			&dwNeededLength, dwCanonicalizeFlags);
		if (!bRetVal)
		{
			delete [] pstrCanonicalizedURL;
			return FALSE;
		}
	}
	else
		pstrCanonicalizedURL = szCanonicalizedURL;

	// now that it's safely canonicalized, crack it

	bRetVal = InternetCrackUrl(pstrCanonicalizedURL, 0,
						dwCrackFlags, lpComponents);
	if (bMustFree)
		delete [] pstrCanonicalizedURL;

	// convert to MFC-style service ID

	if (!bRetVal)
		dwServiceType = AFX_INET_SERVICE_UNK;
	else
	{
		nPort = lpComponents->nPort;
		switch (lpComponents->nScheme)
		{
		case INTERNET_SCHEME_FTP:
			dwServiceType = AFX_INET_SERVICE_FTP;
			break;

		case INTERNET_SCHEME_GOPHER:
			dwServiceType = AFX_INET_SERVICE_GOPHER;
			break;

		case INTERNET_SCHEME_HTTP:
			dwServiceType = AFX_INET_SERVICE_HTTP;
			break;

		case INTERNET_SCHEME_HTTPS:
			dwServiceType = AFX_INET_SERVICE_HTTPS;
			break;

		case INTERNET_SCHEME_FILE:
			dwServiceType = AFX_INET_SERVICE_FILE;
			break;

		case INTERNET_SCHEME_NEWS:
			dwServiceType = AFX_INET_SERVICE_NNTP;
			break;

		case INTERNET_SCHEME_MAILTO:
			dwServiceType = AFX_INET_SERVICE_MAILTO;
			break;

		default:
			dwServiceType = AFX_INET_SERVICE_UNK;
		}
	}

	return bRetVal;
}

BOOL AfxParseURL(LPCTSTR pstrURL, DWORD& dwServiceType,
	CString& strServer, CString& strObject, INTERNET_PORT& nPort)
{
	dwServiceType = AFX_INET_SERVICE_UNK;

	ASSERT(pstrURL != NULL);
	if (pstrURL == NULL)
		return FALSE;

	URL_COMPONENTS urlComponents;
	memset(&urlComponents, 0, sizeof(URL_COMPONENTS));
	urlComponents.dwStructSize = sizeof(URL_COMPONENTS);

	urlComponents.dwHostNameLength = INTERNET_MAX_URL_LENGTH;
	urlComponents.lpszHostName = strServer.GetBuffer(INTERNET_MAX_URL_LENGTH+1);
	urlComponents.dwUrlPathLength = INTERNET_MAX_URL_LENGTH;
	urlComponents.lpszUrlPath = strObject.GetBuffer(INTERNET_MAX_URL_LENGTH+1);

	BOOL bRetVal = _AfxParseURLWorker(pstrURL, &urlComponents,
					dwServiceType, nPort, ICU_BROWSER_MODE);

	strServer.ReleaseBuffer();
	strObject.ReleaseBuffer();
	return bRetVal;
}

#if 0

void WinError(HWND hParent, DWORD lastError);

ILDOMElement* FindByTagNameNS(ILDOMElement* parent, BSTR ns, BSTR tagName, BOOL bDeep/* = TRUE*/)
{
	CComQIPtr<ILDOMNode>	child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		CComQIPtr<ILDOMElement> element = child;
		if (element)
		{
			CComBSTR ens;
			element->get_namespaceURI(&ens);

			if (!cmpbstr(ens, ns))
			{
				CComBSTR etagName;
				element->get_localName(&etagName);
				if (SysStringLen(etagName) == 0)
				{
					etagName.Empty();
					element->get_tagName(&etagName);
				}

				if (!wcscmp(etagName, tagName))
				{
					return element;
				}
			}

		// Recurse
			if (bDeep)
			{
				CComPtr<ILDOMElement> element2 = FindByTagNameNS(element, ns, tagName, TRUE);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}

static const char *szAccept[] = {"*/*", NULL};

#define PANE_NAME		0
#define PANE_STATUS	1
#define PANE_SIZE		2
#define PANE_DATE		3

static int m_titleHeight = 20;

CWebDAVBrowser::CSiteDir::CSiteDir()
{
	m_type = 1;
	m_bPopulated = FALSE;
}

CWebDAVBrowser::CSiteDir::~CSiteDir()
{
	/*
	while (!m_childList.IsEmpty())
	{
		CSiteItem* pItem = (CSiteItem*)m_childList.RemoveHead();
		delete pItem;
	}
	*/
}

CComBSTR CWebDAVBrowser::CSiteItem::GetFullPathName()
{
	CSiteDir* pParentDir = m_parent;

	if (pParentDir)
	{
		WCHAR pathName[_MAX_PATH];
		swprintf(pathName, L"%s/%s", (BSTR)pParentDir->GetFullPathName(), (BSTR)m_displayName);

		return pathName;
	}
	else
	{
		return m_displayName;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWebDAVBrowser

int CWebDAVBrowser::FinalConstruct()
{
	HRESULT hr;

	hr = m_editCtl.CoCreateInstance(CLSID_UIEdit);
	if (FAILED(hr)) return E_NOINTERFACE;

	hr = m_buttonsCtl.CoCreateInstance(CLSID_UIToolbarButtons);
	if (FAILED(hr)) return E_NOINTERFACE;

	hr = m_treeCtl.CoCreateInstance(CLSID_UITreeControl);
	if (FAILED(hr)) return E_NOINTERFACE;
	m_treeCtl->SetSite(this);
	m_treeCtl->InsertColumn(PANE_NAME, L"Name", 140, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_STATUS, L"Status", 80, TRUE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_SIZE, L"Size", 60, FALSE, TRUE, NULL);
	m_treeCtl->InsertColumn(PANE_DATE, L"Date", 80, FALSE, TRUE, NULL);

	return S_OK;
}

void CWebDAVBrowser::FinalRelease()
{
}

LRESULT CWebDAVBrowser::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SHFILEINFO	ssfi;	//get a handle to the system small icon list 

	m_hFileIcons = (HIMAGELIST)::SHGetFileInfo(
		(LPCTSTR)_T("C:\\"),
		0,
		&ssfi, sizeof(SHFILEINFO),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	m_hButtonsBitmap = LoadBitmap(_Module.m_hInstResource, MAKEINTRESOURCE(IDB_FTPBROWSER_BUTTONS));

	IUnknown* p;
	CRect rc(0,0,0,0);

	m_axeditCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axeditCtl.AttachControl(m_editCtl, &p);

	m_axbuttonsCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axbuttonsCtl.AttachControl(m_buttonsCtl, &p);
	m_buttonsCtl->SetBitmap((struct _userHBITMAP *)m_hButtonsBitmap, 16);
	m_buttonsCtl->AddButton(1, 0);
	m_buttonsCtl->AddButton(2, 1);
	IDispEventImpl<3, CWebDAVBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_buttonsCtl);

	m_axtreeCtl.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_DISABLED);
	m_axtreeCtl.AttachControl(m_treeCtl, &p);
	m_treeCtl->put_hImageList((DWORD)m_hFileIcons);
	IDispEventImpl<4, CWebDAVBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_treeCtl);

//	::RegisterDragDrop(m_hWnd, this);

	return 0;
}

LRESULT CWebDAVBrowser::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	IDispEventImpl<3, CWebDAVBrowser, &DIID__IUIToolbarButtonsEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_buttonsCtl);
	IDispEventImpl<4, CWebDAVBrowser, &DIID__IUITreeControlEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_treeCtl);

	if (m_hButtonsBitmap)
	{
		DeleteObject(m_hButtonsBitmap);
		m_hButtonsBitmap = NULL;
	}

//	::RevokeDragDrop(m_hWnd);

	return 0;
}

LRESULT CWebDAVBrowser::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	OnSize();
	InvalidateRect(NULL, TRUE);
	return 0;
}

void CWebDAVBrowser::OnSize()
{
	CRect	client;
	GetClientRect(&client);

	int top = m_titleHeight;

	int cx = client.Width();
	int cy = client.Height();

	m_axeditCtl.MoveWindow(0, 1, cx-38, top-2, TRUE);
	m_axbuttonsCtl.MoveWindow(cx-38, 0, 38, top, TRUE);
	m_axtreeCtl.MoveWindow(0, top, cx, cy-top, TRUE);
}

void CWebDAVBrowser::PopulateFolder(IUITreeItem* parentItem, CSiteDir* pParentDir, bool bCheckExisting)
{
	ATLASSERT(pParentDir);

	pParentDir->m_bPopulated = VARIANT_TRUE;

#if 0
	if (bCheckExisting)
	{
	// Mark all files as not found on disk (yet)
		DWORD child;
		m_treeCtl->GetFirstChildItem(parentItem, &child);
		while (child)
		{
			CSiteItem* pItem;
			m_treeCtl->GetItemInfo(child, (DWORD*)&pItem, NULL, NULL);
			pItem->m_bFoundOnDisk = false;

			m_treeCtl->GetNextSiblingItem(child, &child);
		}
	}
#endif

	//CString strObject = "webdav/demoSite/";

	CString strObject = pParentDir->GetFullPathName();

	HINTERNET hRequest = HttpOpenRequest(
		m_hInternetHttp,
		"PROPFIND",
		strObject,
		"1.1",	// Version
		NULL,	// Referrer
		szAccept,
		INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION | m_dwSecureFlag,
		0// context
		);

	if (hRequest)
	{
		CString headers =
		//"PROPFIND /davroot/ HTTP/1.1\r\n"
		"Host: mattpo-nt5\r\n"
		"Depth: 1\r\n"
		"Content-Type: text/xml\r\n";
		//"Content-Length: xxxx\r\n";

		if (HttpAddRequestHeaders(hRequest, headers, -1/*headers.GetLength()*/, HTTP_ADDREQ_FLAG_ADD))
		{
			CString optional = 
				"<?xml version='1.0' ?>\r\n"
				"<a:propfind xmlns:a='DAV:'>\r\n"
				"    <a:prop>\r\n"
				"        <a:displayname />\r\n"
				"        <a:getcontentlength />\r\n"
				"			<a:resourcetype />\r\n"
				"			<a:creationdate />\r\n"
				"			<a:getlastmodified />\r\n"
				"    </a:prop>\r\n"
				"</a:propfind>\r\n";

			if (HttpSendRequest(hRequest, NULL, 0, (void*)(LPCTSTR)optional, optional.GetLength()))
			{
				//char buffer[20000];
				//DWORD bufferLength = 20000;

				DWORD dwIndex = 0;

				/*
				if (HttpQueryInfo(hRequest, HTTP_QUERY_RAW_HEADERS_CRLF, buffer, &bufferLength, &dwIndex))
				{
					::MessageBox(NULL, buffer, "", MB_OK);
				}
				*/

				TCHAR contentLength[8];
				DWORD dwBytes = 8;
				if (HttpQueryInfo(hRequest, HTTP_QUERY_CONTENT_LENGTH, contentLength, &dwBytes, &dwIndex))
				{
				}
				else
				{
					//WinError(NULL, GetLastError());
				}

				INTERNET_BUFFERS internet_buffers = {0};
				internet_buffers.dwStructSize = sizeof(internet_buffers);
				if (HttpEndRequest(hRequest, &internet_buffers, HSR_SYNC, 0))
				{
				}
				else
				{
					//WinError(NULL, GetLastError());
				}

				{
					char buffer[8000] = {0};
					DWORD nRead;
					InternetReadFile(hRequest, buffer, 8000, &nRead);

					CComPtr<ILDOMDocument> xmldocument;
					xmldocument.CoCreateInstance(CLSID_LDOMDocument);
					if (xmldocument)
					{
						VARIANT_BOOL success;
						xmldocument->loadXML(A2BSTR(buffer), &success);

						::MessageBox(NULL, buffer, "", MB_OK);

						CComPtr<ILDOMElement> documentElement;
						xmldocument->get_documentElement(&documentElement);

						if (documentElement)
						{
							CComPtr<ILDOMNode> node;
							documentElement->get_firstChild(&node);
							while (node)
							{
								CComQIPtr<ILDOMElement> element = node;
								if (element)
								{
									CComBSTR namespaceURI;
									element->get_namespaceURI(&namespaceURI);
									if (namespaceURI.Length() && !wcscmp(namespaceURI, L"DAV:"))
									{
										CComBSTR tagName;
										element->get_localName(&tagName);
										if (!wcscmp(tagName, L"response"))
										{
											ILDOMElement* resourcetype = FindByTagNameNS(element, L"DAV:", L"resourcetype", TRUE);
											if (resourcetype)
											{
												CSiteItem* pItem;

												ILDOMElement* collection = FindByTagNameNS(resourcetype, L"DAV:", L"collection", FALSE);
												if (collection)
												{
													CSiteDir* pDir = new CSiteDir;
													pItem = pDir;
												}
												else
												{
													CSiteFile* pFile = new CSiteFile;
													pItem = pFile;

													ILDOMElement* getcontentlength = FindByTagNameNS(element, L"DAV:", L"getcontentlength", TRUE);
													if (getcontentlength)
													{
														CComBSTR textContent;
														getcontentlength->get_textContent(&textContent);

														pFile->m_contentLength = atoi(_bstr_t(textContent));
													}
												}

												if (pItem)
												{
													pItem->m_parent = pParentDir;

													ILDOMElement* creationdate = FindByTagNameNS(element, L"DAV:", L"creationdate", TRUE);
													if (creationdate)
													{
														CComBSTR textContent;
														creationdate->get_textContent(&textContent);

														VarDateFromStr(textContent, 0, 0, &pItem->m_creationDate);
													}

													ILDOMElement* getlastmodified = FindByTagNameNS(element, L"DAV:", L"getlastmodified", TRUE);
													if (getlastmodified)
													{
														CComBSTR textContent;
														getlastmodified->get_textContent(&textContent);

														VarDateFromStr(textContent, 0, 0, &pItem->m_lastModifiedDate);
													}

													ILDOMElement* displayname = FindByTagNameNS(element, L"DAV:", L"displayname", TRUE);
													if (displayname)
													{
														displayname->get_textContent(&pItem->m_displayName);

														SHFILEINFO sfi;
														::SHGetFileInfo(
															_bstr_t(pItem->m_displayName),	// TODO, don't use _bstr_t
															(pItem->m_type == 1)? FILE_ATTRIBUTE_DIRECTORY: FILE_ATTRIBUTE_NORMAL,
															&sfi,
															sizeof(SHFILEINFO),
															SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
														pItem->m_iIcon = sfi.iIcon;

														m_treeCtl->InsertItem((DWORD)pItem, parentItem, NULL, NULL/*name*/, pItem->m_iIcon, (pItem->m_type == 1)? 1: 0, &pItem->m_treeItem);
													}
												}
											}
										}
									}

									CComPtr<ILDOMNode> nextSibling;
									node->get_nextSibling(&nextSibling);
									node = nextSibling;
								}
							}
						}
					}
				}
			}
			else
			{
				WinError(NULL, GetLastError());
			}
		}
		else
		{
			WinError(NULL, GetLastError());
		}

		InternetCloseHandle(hRequest);
	}
}

void CWebDAVBrowser::SetDirectory()
{
	m_treeCtl->ResetContent(NULL);
	m_axtreeCtl.EnableWindow(TRUE);

	m_axbuttonsCtl.EnableWindow(TRUE);

	m_axeditCtl.EnableWindow(TRUE);
	m_editCtl->SetText(m_Directory);

	m_pRootDir = new CSiteDir;
	m_pRootDir->m_displayName = (BSTR)m_Directory;
	m_treeCtl->SetRootItem((DWORD)m_pRootDir, &m_pRootDir->m_treeItem);

	PopulateFolder(m_pRootDir->m_treeItem, m_pRootDir, false);
}

HRESULT __stdcall CWebDAVBrowser::OnToolbarButtonClick(long buttonid)
{
	switch (buttonid)
	{
	case 1:	// One level up
		{
			if (m_pRootDir)
			{
			// Get parent directory path
				WCHAR newpath[1024];
				wcscpy(newpath, m_pRootDir->GetFullPathName());

				int len = wcslen(newpath);

				WCHAR* p = newpath + len-1;
				while (len >= 0)
				{
					if (*p == L'/')
					{
						*p = 0;	// End the string here
						break;
					}

					p--;
					len--;
				}

				put_Directory(newpath);
			}
		}
		break;

	case 2:	// New Folder
		{
			if (m_hInternetHttp)
			{
				CSiteDir* pParent;

				CComPtr<IUITreeItem> active;
				m_treeCtl->GetSelectedItem(&active);

				if (active)
				{
					CSiteItem* pItem;
					m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);

					if (pItem->m_type == 1)
						pParent = (CSiteDir*)pItem;
					else
						pParent = pItem->m_parent;
				}
				else
				{
					pParent = m_pRootDir;
				}

				ATLASSERT(pParent);

				CSiteDir* pNewDir = new CSiteDir;
				//pNewDir->m_wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
				pNewDir->m_displayName = L"New Folder";
				pNewDir->m_parent = pParent;
				pNewDir->m_bNew = true;

				SHFILEINFO sfi;
				::SHGetFileInfo(
					_bstr_t(pNewDir->m_displayName),
					(pNewDir->m_type == 1)? FILE_ATTRIBUTE_DIRECTORY: FILE_ATTRIBUTE_NORMAL,
					&sfi,
					sizeof(SHFILEINFO),
					SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_USEFILEATTRIBUTES);
				pNewDir->m_iIcon = sfi.iIcon;

				m_treeCtl->InsertItem((DWORD)pNewDir, pParent->m_treeItem, NULL, NULL/*name*/, pNewDir->m_iIcon, (pNewDir->m_type == 1)? 1: 0, &pNewDir->m_treeItem);
				m_treeCtl->EditLabel(pNewDir->m_treeItem, NULL);
			}
		}
		break;
	}

	return S_OK;
}

HRESULT __stdcall CWebDAVBrowser::OnItemDblClick(IUITreeItem* item)
{
	CComPtr<IUITreeItem> active;
	m_treeCtl->GetSelectedItem(&active);

	if (active)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(active, (DWORD*)&pItem, NULL, NULL);
		if (pItem->m_type == 1)	// Double-clicking on folder sets it as new root-folder
		{
			CSiteDir* pDir = (CSiteDir*)pItem;
			put_Directory(pDir->GetFullPathName());
		}
		else
		{
			/*
			DWORD parentitem;
			m_treeCtl->GetParentItem(active, &parentitem);

			DWORD child;

			m_treeCtl->GetFirstChildItem(parentitem, &child);
			while (child)
			{
				DWORD state;
				m_treeCtl->GetItemState(child, &state);

				if (state & 1)
				{
					CSiteItem* pFile;
					m_treeCtl->GetItemInfo(child, (DWORD*)&pFile, NULL);

					VARIANT_BOOL success;
					pWebSite->OpenDocument(pFile->m_dbid, &success);
				}

				m_treeCtl->GetNextSiblingItem(child, &child);
			}
	*/
		}
	}

	return S_OK;
}

HRESULT __stdcall CWebDAVBrowser::OnItemExpanding(IUITreeItem* item, VARIANT_BOOL bExpanding, BOOL* bCancel)
{
	CSiteDir* pDir;
	m_treeCtl->GetItemInfo(item, (DWORD*)&pDir, NULL, NULL);

	if (pDir->m_type == 1)	// Expanding Folder
	{
		if (bExpanding)
		{
			if (!pDir->m_bPopulated)
				PopulateFolder(item, pDir, false);
		}
	}

	return S_OK;
}

HRESULT __stdcall CWebDAVBrowser::OnEndLabelEdit(IUITreeItem* item, BSTR text)
{
	if (m_hInternetHttp)
	{
		CSiteItem* pItem;
		m_treeCtl->GetItemInfo(item, (DWORD*)&pItem, NULL, NULL);

		if (pItem->m_bNew)
		{
			pItem->m_bNew = false;
			pItem->m_displayName = text;

			if (pItem->m_type == 1)
			{
				BOOL success = FALSE;

				HINTERNET hRequest = HttpOpenRequest(
					m_hInternetHttp,
					"MKCOL",
					_bstr_t(pItem->GetFullPathName()),
					"1.1",	// Version
					NULL,	// Referrer
					szAccept,
					INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION | m_dwSecureFlag,
					0// context
					);

				if (hRequest)
				{
#if 0
					CString headers =
					//"PROPFIND /davroot/ HTTP/1.1\r\n"
					"Host: mattpo-nt5\r\n"
					"Depth: 1\r\n"
					"Content-Type: text/xml\r\n";
					//"Content-Length: xxxx\r\n";
#endif
					if (HttpSendRequest(hRequest, NULL, 0, (void*)(LPCTSTR)NULL, 0/*optional.GetLength()*/))
					{
						success = TRUE;
					}

					InternetCloseHandle(hRequest);
				}

			/*
				BOOL success = FtpCreateDirectory(m_hInternetFtp, pItem->GetFullPathName());
				if (!success)
				{
					DWORD dw;
					TCHAR msg[1024];
					DWORD len = 1024;
					InternetGetLastResponseInfo(&dw, msg, &len);

					CUString str;
					str.Format("Couldn't create directory \"%s\"\n\n%s", pItem->GetFullPathName(), msg);
					MessageBox(str, "FTP", MB_OK);
				}
				*/

				if (success)
				{
					PopulateFolder(pItem->m_parent->m_treeItem, pItem->m_parent, true);
				}
				else
				{
					WinError(m_hWnd, GetLastError());
				}
			}
			else
			{
			}
		}
#if 0
		else
		{
			if (wcscmp(_bstr_t(pItem->m_wfd.cFileName), text) != 0)
			{
				CUString parentPath = pItem->m_parent->GetFullPathName();
				_bstr_t atext = text;

				char newPathName[_MAX_PATH];
				_makepath(newPathName, NULL, parentPath, atext, NULL);

				BOOL bSuccess = FtpRenameFile(m_hInternetFtp, pItem->GetFullPathName(), newPathName);
				if (!bSuccess)
				{
					WinError(m_hWnd, GetLastError());
				}
			}
		}
#endif
	}

	return S_OK;
}

STDMETHODIMP CWebDAVBrowser::get_Directory(BSTR *pVal)
{
	return m_Directory.CopyTo(pVal);
}

STDMETHODIMP CWebDAVBrowser::put_Directory(BSTR newVal)
{
	m_Directory = newVal;
	if (m_hInternetHttp)
	{
		SetDirectory();
	}

	return S_OK;
}

STDMETHODIMP CWebDAVBrowser::Connect(VARIANT_BOOL *pSuccess)
{
	if (pSuccess == NULL) return E_POINTER;

	*pSuccess = VARIANT_FALSE;

	m_ServerName = "http://213.115.18.110:1102/";
	m_UserName = "admin";
	m_Password = "admin";
	m_Directory = "webdav/demoSite";

	CString m_Url = (BSTR)m_ServerName;//"http://213.115.18.110:1102/webdav/demoSite";

	INTERNET_PORT nPort;
	DWORD dwServiceType;
	CString strServer;
	CString strObject;

    AfxParseURL( m_Url, dwServiceType, strServer, strObject, nPort );
    if  ( (dwServiceType != AFX_INET_SERVICE_HTTP) &&
           (dwServiceType != AFX_INET_SERVICE_HTTPS) )
    {
        ATLTRACE ("Unsupported scheme\n");
        //cstr_LastError = "Unsupported scheme";
        return FALSE;
    }
    m_dwSecureFlag = ( dwServiceType == AFX_INET_SERVICE_HTTP) 
                    ? ( 0 ) : ( INTERNET_FLAG_SECURE);      

//	if (!m_pRootDir)
	{
		m_hInternet = InternetOpen(
			"WebEditor",//LPCTSTR lpszAgent,
			INTERNET_OPEN_TYPE_DIRECT,//DWORD dwAccessType,
			NULL,//LPCTSTR lpszProxyName,
			NULL,//LPCTSTR lpszProxyBypass,
			0//INTERNET_FLAG_ASYNC,//DWORD dwFlags
			);
		
		if (m_hInternet)
		{
			m_hInternetHttp = InternetConnect(
				m_hInternet,
				strServer,
				nPort,//21,//INTERNET_PORT nServerPort,
				m_UserName,//LPCTSTR lpszUsername,
				m_Password,//LPCTSTR lpszPassword,
				dwServiceType,//INTERNET_SERVICE_HTTP,//DWORD dwService,
				0,//INTERNET_FLAG_PASSIVE,//DWORD dwFlags,
				(DWORD)this// dwContext
				);

			if (m_hInternetHttp)
			{
				SetDirectory();

				*pSuccess = VARIANT_TRUE;
				return S_OK;
			}

			InternetCloseHandle(m_hInternet);
			m_hInternet = NULL;
		}
	}

	return S_OK;
}

STDMETHODIMP CWebDAVBrowser::Disconnect()
{
#if 0
	m_editCtl->SetText(L"");
	m_axeditCtl.EnableWindow(FALSE);

	m_axbuttonsCtl.EnableWindow(FALSE);

	m_treeCtl->ResetContent(NULL);
	m_axtreeCtl.EnableWindow(FALSE);

	m_pRootDir = NULL;
#endif

	if (m_hInternetHttp)
	{
		InternetCloseHandle(m_hInternetHttp);
		m_hInternetHttp = NULL;
	}

	if (m_hInternet)
	{
		InternetCloseHandle(m_hInternet);
		m_hInternet = NULL;
	}

	return S_OK;
}

STDMETHODIMP CWebDAVBrowser::GetItemText(ULONG itemdata, LONG column, BSTR *pVal)
{
	CSiteItem* pItem = (CSiteItem*)itemdata;

	*pVal = NULL;

	if (pItem->m_bNew)
	{
		switch (column)
		{
			case PANE_NAME:
				pItem->m_displayName.CopyTo(pVal);
			break;

			default:
				*pVal = NULL;//SysAllocString(L"");
		}
	}
	else
	{
		switch (column)
		{
		case PANE_NAME:
			pItem->m_displayName.CopyTo(pVal);
		break;

		case PANE_SIZE:
			if (pItem->m_type == 2)
			{
				WCHAR buf[64];
				int len;
				CSiteFile* pFile = (CSiteFile*)pItem;

				if (pFile->m_contentLength < 1024)
				{
					len = swprintf(buf, L"%d byte", pFile->m_contentLength);
				}
				else
				{
					len = swprintf(buf, L"%.1f kB", pFile->m_contentLength / 1024.0);
				}

				*pVal = SysAllocString(buf);
			}
			break;

		case PANE_DATE:
			{
			//	VarBstrFromDate(pItem->m_lastModifiedDate, 0, 0, pVal);
				VarBstrFromDate(pItem->m_creationDate, 0, 0, pVal);
			}
			break;
		}
	}

	return S_OK;
}

#endif