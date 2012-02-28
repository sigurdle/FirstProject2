// WorkgroupDocument.cpp : Implementation of CWorkgroupDocument
#include "stdafx.h"
#include "LXFramework.h"
#include "LXFramework2.h"
#include "WorkgroupDocument.h"

#include "LXFrameworkApp.h"
#include "LXFrameworkFrame.h"

extern CLXFrameworkApp* gApp;

#include "WorkgroupFilesView.h"

__int64 GetTotalSizeOfFiles(LPTSTR filepath);

/////////////////////////////////////////////////////////////////////////////
// CWorkgroupDocument

void CWorkgroupDocument::ShowView()
{
#if 0
	{
		CComObject<CUIMDIChild>* child;
		CComObject<CUIMDIChild>::CreateInstance(&child);
		child->AddRef();
		gApp->m_frame->QueryInterface(IID_IUnknown, (void**)&child->m_spFrame);

		{
			CComObject<CWorkgroupFilesView>* view;
			CComObject<CWorkgroupFilesView>::CreateInstance(&view);
			if (view)
			{
				gApp->m_frame->FindMenu(_Module.GetResourceInstance(), IDR_WORKGROUPFILESVIEW, &view->m_menu);
				view->m_document = this;
				child->AddPage(view, NULL);
			}
		}

		ATLASSERT(0);
	//	child->CreateEx(gApp->m_frame, gApp->m_frame->m_hWndClient);
		child->SetWindowText(_T("Workgroup"));
	}
#endif
}

//#include "ProgressDlg.h"

#if 0
long CWorkgroupDocument::CopyMoveFile(DWORD folder_id, _bstr_t filepath, VARIANT_BOOL bSilent, CProgressDlg* dlg)
{
	long nFilesCopied = 0;

	DWORD attributes = GetFileAttributes(filepath);
	char* filepart = PathFindFileName(filepath);

	if (attributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		folder_id = m_filesystem->FindOrCreateFolder(folder_id, filepart, L"");

		if (folder_id)
		{
			HANDLE hFindFile;
			WIN32_FIND_DATA	wfd;

			char	search[MAX_PATH];
			wsprintf(search, "%S\\*.*", (BSTR)filepath);

			if ((hFindFile = FindFirstFile(search, &wfd)) != INVALID_HANDLE_VALUE)
			{
				do
				{
					if (wfd.cFileName[0] != '.')
					{
						char pathName[_MAX_PATH];
						_makepath(pathName, NULL, filepath, wfd.cFileName, NULL);

						nFilesCopied += CopyMoveFile(folder_id, pathName, bSilent, dlg);

						if (dlg)
						{
							if (dlg->m_bCancel) break;
						}
					}
				}
				while (FindNextFile(hFindFile, &wfd));

				FindClose(hFindFile);
			}
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't create folder %S", (BSTR)filepath);
				MessageBox(NULL, str, "LXFramework", MB_OK);
			}
		}
	}
	else
	{
		SAFEARRAY* dataArray = NULL;
		long dataSize = 0;

		FILE* fp = fopen(filepath, "rb");
		if (fp)
		{
			fseek(fp, 0, SEEK_END);
			dataSize = ftell(fp);
			fseek(fp, 0, SEEK_SET);

			dataArray = SafeArrayCreateVector(VT_UI1, 0, dataSize);
			if (dataArray)
			{
				fread((dataArray)->pvData, 1, dataSize, fp);
			}

			fclose(fp);
		}
		else
		{
			if (!bSilent)
			{
				CUString str;
				str.Format("Couldn't open %S", (BSTR)filepath);
				MessageBox(NULL, str, "LXFramework", MB_OK);
			}
		}

		if (dataArray)
		{
			long file_id;
			VARIANT_BOOL success = m_filesystem->SaveArrayAsFile(folder_id, _bstr_t(filepart), dataArray, L"", &file_id);

			SafeArrayDestroy(dataArray);

			if (success)
			{
				nFilesCopied++;
			}
			else
			{
				if (!bSilent)
				{
					CUString str;
					str.Format("Failed to copy %s", filepart);
					MessageBox(NULL, str, "LXFramework", MB_OK);
				}
			}
		}

		if (dlg)
		{
			dlg->m_pos += dataSize/10;
			dlg->Invalidate();

			MSG msg;
			while (PeekMessage(&msg, dlg->m_hWnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
	return nFilesCopied;
}
#endif

STDMETHODIMP CWorkgroupDocument::CopyMoveFiles(/*[in]*/ DWORD folder_id, /*[in]*/ SAFEARRAY* sa, /*[in]*/ VARIANT_BOOL bSilent, /*[out,retval]*/ long* nFilesCopied)
{
	if (nFilesCopied == NULL) return E_POINTER;

//	CProgressDlg dlg;
//	dlg.Create(GetMainHwnd(), NULL);

	int i;

	__int64 nSize = 0;
	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

		nSize += GetTotalSizeOfFiles(_bstr_t(bstr));
	}

//	dlg.m_min = 0;
//	dlg.m_max = nSize/10;
//	dlg.m_pos = 0;

	for (i = 0; i < sa->rgsabound[0].cElements; i++)
	{
		long ix[1];
		ix[0] = i;

		BSTR bstr;
		SafeArrayGetElement(sa, ix, (void**)&bstr);

//		(*nFilesCopied) += CopyMoveFile(folder_id, _bstr_t(bstr), bSilent, NULL/*&dlg*/);
	}

//	dlg.DestroyWindow();

	return S_OK;
}
