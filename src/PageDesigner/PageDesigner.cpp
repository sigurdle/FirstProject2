// PageDesigner.cpp : main source file for PageDesigner.exe
//

#include "stdafx.h"

//#include <atlframe.h>
//#include <atlctrls.h>
//#include <atldlgs.h>


#include "resource.h"

// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f PageDesignerps.mk in the project directory.
#include "initguid.h"
#include "PageDesigner.h"

#include "PageDesigner2.h"

//#include "..\UIT\UIT.h"

#include "PageDesigner_i.c"

#include "..\UI\UI_i.c"
//#include "..\LDOM\LDOM_i.c"
#include "..\LHTML\LHTML_i.c"
#include "..\TextDataMod\TextDataMod_i.c"

#define DEFINE_GUIDXXX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        EXTERN_C const GUID CDECL name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUIDXXX(IID_ITextDocument,0x8CC497C0,0xA1DF,0x11CE,0x80,0x98, 0x00,0xAA,0x00,0x47,0xBE,0x5D);

//#include "aboutdlg.h"
//#include "ChildFrm.h"
//#include "MainFrm.h"

#include "ObjectMap.h"
#include "PDLayer.h"
#include "PDDocument.h"
#include "PDObjectLayerGroup.h"
#include "PagesDlg.h"
#include "LayersDlg.h"
#include "PDRenderer.h"
#include "PDMatrix.h"
#include "PDGradient.h"
#include "SwatchesDlg.h"
#include "NavigatorDlg.h"
#include "GradientDlg.h"
#include "StrokeDlg.h"
#include "SwatchesList.h"
#include "ColorDlg.h"
#include "GradientEdit.h"
#include "ToolsDlg.h"
#include "TabsControl.h"
#include "TabsDlg.h"
#include "SwatchLibraryDlg.h"
#include "LinksDlg.h"
#include "TransparencyDlg.h"
#include "FilterGraphDlg.h"
#include "FEGaussianBlur.h"
#include "FEOffset.h"
#include "FEComposite.h"
#include "PluginFiltersDlg.h"
#include "StylesDlg.h"
#include "FEFreeTransform.h"
#include "Archive.h"
#include "PDContentText.h"
#include "PDContentGraphic.h"
#include "PDObjectShape.h"
#include "PDObjectGroup.h"
#include "PDPage.h"
#include "PDSpreadMaster.h"
#include "PDSpreadDocument.h"
#include "PDAppearance.h"
#include "PDFilterPrimitive.h"
#include "PDObjectStroke.h"
#include "PDObjectFill.h"
#include "AppearanceDlg.h"
#include "PDSwatchColor.h"
#include "PDSwatchGradient.h"
#include "PDSwatchPattern.h"
#include "PDSwatchNone.h"
#include "PDGradientStop.h"
#include "SymbolsDlg.h"
#include "PDSymbol.h"
#include "PDObjectSymbolInstance.h"
#include "PDObjectSymbolInstanceSet.h"

CServerAppModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_PagesDlg, CPagesDlg)
OBJECT_ENTRY(CLSID_LayersDlg, CLayersDlg)
OBJECT_ENTRY(CLSID_PDRenderer, CPDRenderer)
OBJECT_ENTRY(CLSID_SwatchesDlg, CSwatchesDlg)
OBJECT_ENTRY(CLSID_NavigatorDlg, CNavigatorDlg)
OBJECT_ENTRY(CLSID_PDMatrix, CPDMatrix)
OBJECT_ENTRY(CLSID_PDGradient, CPDGradient)
OBJECT_ENTRY(CLSID_GradientDlg, CGradientDlg)
OBJECT_ENTRY(CLSID_StrokeDlg, CStrokeDlg)
OBJECT_ENTRY(CLSID_SwatchesList, CSwatchesList)
OBJECT_ENTRY(CLSID_ColorDlg, CColorDlg)
OBJECT_ENTRY(CLSID_GradientEdit, CGradientEdit)
OBJECT_ENTRY(CLSID_ToolsDlg, CToolsDlg)
OBJECT_ENTRY(CLSID_TabsControl, CTabsControl)
OBJECT_ENTRY(CLSID_TabsDlg, CTabsDlg)
OBJECT_ENTRY(CLSID_SwatchLibraryDlg, CSwatchLibraryDlg)
OBJECT_ENTRY(CLSID_LinksDlg, CLinksDlg)
OBJECT_ENTRY(CLSID_TransparencyDlg, CTransparencyDlg)
OBJECT_ENTRY(CLSID_FilterGraphDlg, CFilterGraphDlg)
OBJECT_ENTRY(CLSID_FEGaussianBlur, CFEGaussianBlur)
OBJECT_ENTRY(CLSID_FEOffset, CFEOffset)
OBJECT_ENTRY(CLSID_FEComposite, CFEComposite)
OBJECT_ENTRY(CLSID_PluginFiltersDlg, CPluginFiltersDlg)
OBJECT_ENTRY(CLSID_StylesDlg, CStylesDlg)
OBJECT_ENTRY(CLSID_FEFreeTransform, CFEFreeTransform)
OBJECT_ENTRY(CLSID_Archive, CArchive)
OBJECT_ENTRY(CLSID_PDContentText, CPDContentText)
OBJECT_ENTRY(CLSID_PDContentGraphic, CPDContentGraphic)
OBJECT_ENTRY(CLSID_PDLayer, CPDLayer)
OBJECT_ENTRY(CLSID_PDPage, CPDPage)
OBJECT_ENTRY(CLSID_PDSpreadMaster, CPDSpreadMaster)
OBJECT_ENTRY(CLSID_PDSpreadDocument, CPDSpreadDocument)
OBJECT_ENTRY(CLSID_PDObjectLayerGroup, CPDObjectLayerGroup)
OBJECT_ENTRY(CLSID_PDObjectGroup, CPDObjectGroup)
OBJECT_ENTRY(CLSID_PDObjectFrame, CPDObjectFrame)
OBJECT_ENTRY(CLSID_PDAppearance, CPDAppearance)
OBJECT_ENTRY(CLSID_PDFilterPrimitive, CPDFilterPrimitive)
OBJECT_ENTRY(CLSID_PDDocument, CPDDocument)
OBJECT_ENTRY(CLSID_PDObjectStroke, CPDObjectStroke)
OBJECT_ENTRY(CLSID_PDObjectFill, CPDObjectFill)
OBJECT_ENTRY(CLSID_AppearanceDlg, CAppearanceDlg)
OBJECT_ENTRY(CLSID_PDSwatchColor, CPDSwatchColor)
OBJECT_ENTRY(CLSID_PDSwatchGradient, CPDSwatchGradient)
OBJECT_ENTRY(CLSID_PDSwatchPattern, CPDSwatchPattern)
OBJECT_ENTRY(CLSID_PDSwatchNone, CPDSwatchNone)
OBJECT_ENTRY(CLSID_PDGradientStop, CPDGradientStop)
OBJECT_ENTRY(CLSID_SymbolsDlg, CSymbolsDlg)
OBJECT_ENTRY(CLSID_PDSymbol, CPDSymbol)
OBJECT_ENTRY(CLSID_PDObjectSymbolInstance, CPDObjectSymbolInstance)
OBJECT_ENTRY(CLSID_PDObjectSymbolInstanceSet, CPDObjectSymbolInstanceSet)
END_OBJECT_MAP()

extern int Run(bool bAutomation, LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT);

#if 0
int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMainFrame wndMain;

	if(wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	_Module.Lock();
	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}
#endif

// {8001A204-F8A9-4773-815B-B9584F2C20B7}
/*
const GUID CATID_PageDesignerEffects = 
{ 0x8001a204, 0xf8a9, 0x4773, { 0x81, 0x5b, 0xb9, 0x58, 0x4f, 0x2c, 0x20, 0xb7 } };
*/

// {8001A204-F8A9-4773-815B-B9584F2C20B7}
DEFINE_GUID(CATID_PageDesignerEffects, 
0x8001a204, 0xf8a9, 0x4773, 0x81, 0x5b, 0xb9, 0x58, 0x4f, 0x2c, 0x20, 0xb7);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
   HRESULT hRes = OleInitialize(NULL);

//	HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	ATLASSERT(SUCCEEDED(hRes));

#if (_WIN32_IE >= 0x0300)
	INITCOMMONCONTROLSEX iccx;
	iccx.dwSize = sizeof(iccx);
	iccx.dwICC = ICC_BAR_CLASSES;	// change to support other controls
	BOOL bRet = ::InitCommonControlsEx(&iccx);
	bRet;
	ATLASSERT(bRet);
#else
	::InitCommonControls();
#endif

	MessageBox(NULL, "", "PageDesigner", MB_OK);

	hRes = _Module.Init(ObjectMap, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	AtlAxWinInit();

	int nRet = 0;
	TCHAR szTokens[] = _T("-/");
	bool bRun = true;
	bool bAutomation = false;

	LPCTSTR lpszToken = _Module.FindOneOf(::GetCommandLine(), szTokens);
	while(lpszToken != NULL)
	{
		if(lstrcmpi(lpszToken, _T("UnregServer")) == 0)
		{
         _Module.UpdateRegistryFromResource(IDR_PAGEDESIGNER, FALSE);
			nRet = _Module.UnregisterServer(TRUE);
			bRun = false;
			break;
		}
		else if(lstrcmpi(lpszToken, _T("RegServer")) == 0)
		{
         _Module.UpdateRegistryFromResource(IDR_PAGEDESIGNER, TRUE);
			nRet = _Module.RegisterServer(TRUE);

			// SL Added this
			{
				//register the component as insertable and a document object
				ICatRegister   *pcr;
				HRESULT        hr = S_OK ;
    
				hr = CoCreateInstance(  CLSID_StdComponentCategoriesMgr, 
					NULL, 
					CLSCTX_INPROC_SERVER, 
					IID_ICatRegister, 
					(LPVOID*)&pcr);
				
				if(SUCCEEDED(hr))
				{
					CATEGORYINFO catinfo[1];
					catinfo[0].catid = CATID_PageDesignerEffects;//{ 0x8001a204, 0xf8a9, 0x4773, { 0x81, 0x5b, 0xb9, 0x58, 0x4f, 0x2c, 0x20, 0xb7 } },
					catinfo[0].lcid = 0;
					wcscpy(catinfo[0].szDescription, L"PageDesigner Effects");
					
					hr = pcr->RegisterCategories(sizeof(catinfo)/sizeof(CATEGORYINFO), catinfo);
					
					pcr->Release();
				}
			}

			// SL Added this
			{
				//register the component as insertable and a document object
				ICatRegister   *pcr;
				HRESULT        hr = S_OK ;
    
				hr = CoCreateInstance(  CLSID_StdComponentCategoriesMgr, 
					NULL, 
					CLSCTX_INPROC_SERVER, 
					IID_ICatRegister, 
					(LPVOID*)&pcr);
				
				if(SUCCEEDED(hr))
				{
					CATID rgcatid[1];
					
					rgcatid[0] = CATID_PageDesignerEffects;
					
					hr = pcr->RegisterClassImplCategories(CLSID_FEComposite, 1, rgcatid);
					hr = pcr->RegisterClassImplCategories(CLSID_FEGaussianBlur, 1, rgcatid);
					hr = pcr->RegisterClassImplCategories(CLSID_FEOffset, 1, rgcatid);
					
					pcr->Release();
				}
			}

			// SL Added this
			{
				//register the component as insertable and a document object
				ICatRegister   *pcr;
				HRESULT        hr = S_OK ;
    
				hr = CoCreateInstance(  CLSID_StdComponentCategoriesMgr, 
					NULL, 
					CLSCTX_INPROC_SERVER, 
					IID_ICatRegister, 
					(LPVOID*)&pcr);
				
				if(SUCCEEDED(hr))
				{
					CATID rgcatid[2];
					
					rgcatid[0] = CATID_Insertable;
					rgcatid[1] = CATID_DocObject;
					
					hr = pcr->RegisterClassImplCategories(CLSID_PDDocument, 2, rgcatid);
					
					pcr->Release();
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

		/*
		if(bAutomation)
		{
			MessageBox(NULL, "Automation", "", MB_OK);
			CMessageLoop theLoop;
			nRet = theLoop.Run();
		}
		else
		*/
		{
			nRet = Run(bAutomation, lpstrCmdLine, nCmdShow);
		}

		Gdiplus::GdiplusShutdown(gdiplusToken);

		_Module.RevokeClassObjects();
		::Sleep(_Module.m_dwPause);
	}

	_Module.Term();
	::OleUninitialize();
//	::CoUninitialize();

	return nRet;
}
