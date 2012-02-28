// LXFramework.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f LXFrameworkps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "LXFramework.h"

#include "LXFramework2.h"

//#include "..\UIT\UIT.h"

#include "LXFramework_i.c"
#include "..\UI\UI_i.c"
#include "..\LHTML\LHTML_i.c"
#include "..\LXUI\LXUI_i.c"

#include "LXFrameworkApp.h"
//#include "EScoreDocument.h"

CServerAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_LXFrameworkApp, CLXFrameworkApp)
//OBJECT_ENTRY(CLSID_EScoreDocument, CEScoreDocument)
END_OBJECT_MAP()

LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
    while (p1 != NULL && *p1 != NULL)
    {
        LPCTSTR p = p2;
        while (p != NULL && *p != NULL)
        {
            if (*p1 == *p)
                return CharNext(p1);
            p = CharNext(p);
        }
        p1 = CharNext(p1);
    }
    return NULL;
}

//extern void Run();

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT);

#include "FileType.h"

// {8767A8F7-5D49-474b-AB44-4AE2D3A50BE9}
DEFINE_GUID(CATID_LXFrameworkPlugin, 
0x8767a8f7, 0x5d49, 0x474b, 0xab, 0x44, 0x4a, 0xe2, 0xd3, 0xa5, 0xb, 0xe9);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	//HRESULT hRes = ::CoInitialize(NULL);
   HRESULT hRes = OleInitialize(NULL);

// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_WIN95_CLASSES;///*ICC_COOL_CLASSES |*/ ICC_BAR_CLASSES;
	BOOL bRet = ::InitCommonControlsEx(&iccx);
//	bRet;
//	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	hRes = _Module.Init(ObjectMap, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	//MessageBox(NULL, "lx", "", MB_OK);

	int nRet = 0;
	TCHAR szTokens[] = _T("-/");
	bool bRun = true;
	bool bAutomation = false;
	bool bDDE = false;

//	MessageBox(NULL, ::GetCommandLine(), "", MB_OK);

	LPCTSTR lpszToken = _Module.FindOneOf(::GetCommandLine(), szTokens);
	while(lpszToken != NULL)
	{
		if(lstrcmpi(lpszToken, _T("UnregServer")) == 0)
		{
			nRet = _Module.UnregisterServer(TRUE);
			bRun = false;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("RegServer")) == 0)
		{
			nRet = _Module.RegisterServer(TRUE);

			/*
			{
				CFileTypes* pFileTypes = new CFileTypes;

				{
					CFileType* pFileType = new CFileType;
					pFileType->m_id = "LXFramework";
					pFileType->m_descr = "LXFramework";
					pFileType->AddFileExtension(".lxf");
					pFileTypes->m_fileTypes.Add(pFileType);

					pFileType->m_registered = 1;//RegisterFileType();
				}

				pFileTypes->UpdateToRegistry();

				delete pFileTypes;
			}
			*/

			{
				{
					ICatRegister   *pcr;
					HRESULT        hr = S_OK;

					hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
						NULL, 
						CLSCTX_INPROC_SERVER, 
						IID_ICatRegister, 
						(LPVOID*)&pcr);
					
					if(SUCCEEDED(hr))
					{
						CATEGORYINFO catinfo[1];
						catinfo[0].catid = CATID_LXFrameworkPlugin;
						catinfo[0].lcid = 0;
						wcscpy(catinfo[0].szDescription, L"LXFramework Plugin");
						
						hr = pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
						
						pcr->Release();
					}
				}
			}

			bRun = false;
			break;
		}
		else if((lstrcmpi(lpszToken, _T("Automation")) == 0) ||
			(lstrcmpi(lpszToken, _T("Embedding")) == 0))
		{
			bAutomation = true;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("dde")) == 0)
		{
			bDDE = true;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if(bRun)
	{
		_Module.StartMonitor();
		hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
		ATLASSERT(SUCCEEDED(hRes));
		hRes = ::CoResumeClassObjects();
		ATLASSERT(SUCCEEDED(hRes));

		static ULONG_PTR gdiplusToken;

		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

#if 0
		xThemeInit();
#endif

		if (bAutomation)
		{
			CMessageLoop theLoop;
			nRet = theLoop.Run();
		}
		else
		{
			nRet = Run(lpstrCmdLine, nCmdShow);
		}

		Gdiplus::GdiplusShutdown(gdiplusToken);

		_Module.RevokeClassObjects();
		::Sleep(_Module.m_dwPause);
	}

	_Module.Term();
	//::CoUninitialize();
	::OleUninitialize();

	return nRet;
}
