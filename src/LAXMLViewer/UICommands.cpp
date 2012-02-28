#include "stdafx.h"
#include "LAXMLViewer.h"
#include "..\LXML\LXML2.h"
#include "LHTMLActiveDocument.h"

#if 0
#include "..\eSellerate\esellerate.h"
#pragma comment(lib, "..\\eSellerate\\eSellerateLibrary.lib")

#define STRINGLENGTH 64

char serialNumber [STRINGLENGTH];
char versionTitle [STRINGLENGTH];

int versionNumber = 0;

enum {
  Good,
  NotActivated,
  NoSerialNumber
};

extern "C"
{
typedef eSellerate_ErrorCode   (__stdcall *eSellerate_Purchase_def)
 (                  /* call on the Engine to perform a purchase ******************/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                         */
  eSellerate_InputString esellerID,    /* eSeller ID code (always needed)                           */
  eSellerate_InputString previewID,    /* preview certificate ID code                               */
  eSellerate_InputString errorURL,     /* URL to show in case of error                              */
  eSellerate_InputString openingTitle, /* custom title of the opening page of the Wizard            */
  eSellerate_InputString openingText,  /* custom first paragraph of the opening page of the Wizard  */
  eSellerate_TrueOrFalse showFolder,   /* have the Engine open a window to display downloaded files */
  eSellerate_InputString trackingID,   /* tracking ID code                                          */
  eSellerate_InputString affiliateID,  /* affiliate ID code                                         */
  eSellerate_InputString couponID,     /* coupon ID code                                            */
  eSellerate_InputString activationID, /* activation ID code, to activate serial number             */
  eSellerate_InputString extraData,    /* extra information, for instance for custom serial numbers */
  eSellerate_ResultData* resultData    /* handle to memory to be allocated and filled by the Engine */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_Reinstall_def) (                 /* call on the Engine to reinstall a previous purchase *******/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                         */
  eSellerate_InputString esellerID,    /* eSeller ID code (always needed)                           */
  eSellerate_InputString previewID,    /* preview certificate ID code                               */
  eSellerate_InputString errorURL,     /* URL to show in case of error                              */
  eSellerate_InputString openingTitle, /* custom title of the opening page of the Wizard            */
  eSellerate_InputString openingText,  /* custom first paragraph of the opening page of the Wizard  */
  eSellerate_TrueOrFalse showFolder,   /* have the Engine open a window to display downloaded files */
  eSellerate_InputString trackingID,   /* tracking ID code                                          */
  eSellerate_InputString activationID, /* activation ID code, to activate serial number             */
  eSellerate_ResultData* resultData    /* handle to memory to be allocated and filled by the Engine */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_CheckForUpdate_def) (            /* call on the Engine to check if an update is available *****/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                         */
  eSellerate_InputString esellerID,    /* eSeller ID code (always needed)                           */
  eSellerate_InputString previewID,    /* preview certificate ID code                               */
  eSellerate_InputString errorURL,     /* URL to show in case of error                              */
  eSellerate_InputString openingTitle, /* custom title of the opening page of the Wizard            */
  eSellerate_InputString openingText,  /* custom first paragraph of the opening page of the Wizard  */
  eSellerate_TrueOrFalse showFolder,   /* have the Engine open a window to display downloaded files */
  eSellerate_InputString trackingID,   /* tracking ID code                                          */
  eSellerate_InputString affiliateID,  /* affiliate ID code                                         */
  eSellerate_InputString couponID,     /* coupon ID code                                            */
  eSellerate_InputString activationID, /* activation ID code, to activate serial number             */
  eSellerate_InputString extraData,    /* extra information, for instance for custom serial numbers */
  eSellerate_ResultData* resultData    /* handle to memory to be allocated and filled by the Engine */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_SilentCheckForUpdate_def) (      /* check for an update without invoking the Wizard ***/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                 */
  eSellerate_InputString esellerID,    /* eSeller ID code (always needed)                   */
  eSellerate_InputString previewID,    /* preview certificate ID code                       */
  eSellerate_TrueOrFalse askToConnect, /* ask to connect when no active connection is found */
  eSellerate_InputString trackingID    /* tracking ID code                                  */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_LaunchUpdate_def) (              /* call on the Engine to launch an update ********/
  eSellerate_FileLocation updaterFile, /* location of file to launch (always needed)    */
  eSellerate_FileLocation fileToUpdate /* location of file to which to apply the update */
);

typedef eSellerate_ArraySize (__stdcall
*eSellerate_IndexShoppingCartData_def) (          /* build array access to product ID codes output by the Engine **/
  eSellerate_ResultData   resultData,       /* handle to the output from call to the Engine (always needed) */
  eSellerate_OutputString productIDArray[], /* array to be filled for access to product ID codes            */
  eSellerate_OutputString skuIDArray[],     /* array to be filled for access to SKU ID codes                */
  eSellerate_ArraySize    arraySize         /* size of arrays provided                                      */
);

typedef eSellerate_ArraySize (__stdcall
*eSellerate_IndexSerialNumberData_def) (             /* build array access to serial numbers output by the Engine ****/
  eSellerate_ResultData   resultData,          /* handle to the output from call to the Engine (always needed) */
  eSellerate_OutputString productIDArray[],    /* array to be filled for access to product ID codes            */
  eSellerate_OutputString serialNumberArray[], /* array to be filled for access to associated serial numbers   */
  eSellerate_OutputString nameBasedKeyArray[], /* array to be filled for access to associated name-based keys  */
  eSellerate_ArraySize    arraySize            /* size of arrays provided                                      */
);

typedef eSellerate_ArraySize (__stdcall
*eSellerate_IndexFileLocationData_def) (             /* build array access to file locations output by the Engine ****/
  eSellerate_ResultData   resultData,          /* handle to the output from the call to Engine (always needed) */
  eSellerate_OutputString productIDArray[],    /* array to be filled for access to product ID codes            */
  eSellerate_FileLocation fileLocationArray[], /* array to be filled for access to file locations              */
  eSellerate_ArraySize    arraySize            /* size of array provided                                       */
);

typedef void (__stdcall
*eSellerate_DeleteResultData_def) (      /* free memory allocated by the Engine */
  eSellerate_ResultData resultData /* handle to the allocated memory      */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_ActivateSerialNumber_def) (      /* confirm origin of serial number and lock it to hardware ************/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                                  */
  eSellerate_InputString activationID, /* activation ID code to associate with serial number (always needed) */
  eSellerate_InputString serialNumber, /* serial number (always needed)                                      */
  eSellerate_TrueOrFalse askToConnect  /* ask to connect when no active connection is found                  */
);
/* additional failure codes:
 * -25000: unknown activationID
 * -25001: unknown serialNumber
 * -25002: publisherID/serialNumber mismatch
 * -25003: blacklisted serialNumber
 * -25004: invalid order
 * -25005: activation limit met
 * -25009: non-unique serialNumber
 */

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_ValidateActivation_def) (        /* verify that serial number is activated and locked to hardware ****/
  eSellerate_InputString publisherID,  /* publisher ID code (always needed)                                */
  eSellerate_InputString activationID, /* activation ID code associated with serial number (always needed) */
  eSellerate_InputString serialNumber  /* serial number (always needed)                                    */
);
/* additional failure codes:
 * -25006: unknown activationKey
 * -25007: activationKey/hardware mismatch
 * -25008: invalid activationKey
 */

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_InstallEngine_def) ( /* install the Engine from resource to its proper system location */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_InstallEngineFrom_def) ( /* install the Engine from resource to its proper system location  */
  HINSTANCE ownerModule        /* handle to the executable module that has the Engine as resource */
);

typedef eSellerate_ErrorCode (__stdcall
*eSellerate_ApplicationLocation_def) (      /* determine file location of the application */
  eSellerate_FileLocation application /* file location to be filled as result       */
);

typedef eSellerate_ArraySize (__stdcall
*eSellerate_WebStoreURL_def) (                   /* retrieve URL stored by eSellerate SalesTrac Technology */
  eSellerate_InputString  publisherID,     /* publisher ID code (always needed)                      */
  eSellerate_InputString  skuRefNum,       /* sku RefNum code (always needed)                        */
  eSellerate_OutputString resultBuffer,    /* buffer to be filled as result                          */
  eSellerate_ArraySize    resultBufferSize /* size of buffer provided                                */
);
}

/*
eSellerate_Purchase_def	eSellerate_Purchase;
eSellerate_DeleteResultData_def eSellerate_DeleteResultData;
eSellerate_IndexSerialNumberData_def eSellerate_IndexSerialNumberData;
*/

//////////////////////////////////////////////////

static
BOOL SetRegistryKey (
  char* keyPath,
  char* keyName,
  char* keyData
) {
  HKEY  key;
  long  error;
  DWORD disposition;

  error = RegCreateKeyEx(
  HKEY_CURRENT_USER, keyPath, 0, NULL, REG_OPTION_NON_VOLATILE,
    KEY_ALL_ACCESS, NULL, &key, &disposition);
  if ( error ) return FALSE;

  error = RegSetValueEx(
    key, keyName, 0, REG_SZ, (BYTE*) keyData, lstrlen(keyData) + 1);
  RegCloseKey(key);
  if ( error ) return FALSE;

  return TRUE;
}

//////////////////////////////////////////////////

static
BOOL GetRegistryKey (
  char* keyPath,
  char* keyName,
  char* keyData
) {
  HKEY  key;
  long  error;
  char  content[1024];
  DWORD type = REG_SZ;
  DWORD size = 1024;

  error = RegOpenKeyEx(
    HKEY_CURRENT_USER, keyPath, 0, KEY_ALL_ACCESS, &key); 
  if ( error ) return FALSE;

  error = RegQueryValueEx(
    key, keyName, NULL, &type, (BYTE*) content, &size );
  RegCloseKey(key);
  if ( error ) return FALSE;

  lstrcpy(keyData, content);
  return TRUE;
}

static void eSellerPurchase(HWND appWindow)
{
/// Set up:
///  resultData, for holding all data retrieved by the eSellerate wizard
///  serialNumberCount, for telling how many serial numbers are retrieved
///  serialNumberArray, for accessing these serial numbers
  eSellerate_ResultData   resultData     = NULL;
  eSellerate_OutputString serialNumberArray [1]; // just one serial number expected
  eSellerate_ArraySize    serialNumberCount = 0;

/*2*  PURCHASE example  */
/// Invoke the eSellerate wizard by calling eSellerate_Purchase().
  eSellerate_ErrorCode result = eSellerate_Purchase (
    "PUB666614790",                     // Publisher ID
    "ES9426101760",                      // Integrated eSeller RefNum
    "",//"PC938610000-1311",                 // Preview Certificate
    "http://www.lerstad.com/", // URL to contact in case of error
    NULL,                               // custom first page title, not needed here
    NULL,                               // custom first page text, not needed here
    eSellerate_FALSE,                   // display download folder, not needed
    NULL,                               // Tracking ID, not needed here
    NULL,                               // Affiliate ID, not needed here
    NULL,                               // Coupon ID, not needed here
    "",//"ACT071700125",//"ACT979610220",                     // Activation Set ID, to activate serial number
    NULL,                               // extra data, not needed here
    &resultData                         // address of holder for data retrieved
  );

  switch ( result )
  {
    case eSellerate_NOENGINE:
      MessageBox (
        appWindow, "eSellerateEngine not found",
        "ERROR", MB_OK | MB_ICONEXCLAMATION
      );
      break;

    case eSellerate_SUCCESS:

/// Let serialNumberCount note if serial numbers are retrieved.
/// Let serialNumberArray then refer to these serial numbers.
      serialNumberCount = eSellerate_IndexSerialNumberData (
        resultData, // data to be referenced
        NULL, // no Product ID needed, since just one serial number is expected
        serialNumberArray, // reference array
        NULL, // no Name-Based Key expected, since None set in the Sales Manager
        1     // size of reference array
      );

/// In this application, the serial number is written to the Windows registry.
      if ( serialNumberCount ) {
        versionNumber = 1;
        strcpy(versionTitle,"VERSION 1.0");
/// Here serialNumberArray[0] is the serial number retrieved by the wizard.
/// Make a copy of it before it is lost at eSellerate_DeleteResultData().
        strcpy(serialNumber,serialNumberArray[0]);
#if 0
        AdjustMenu();
        InvalidateRect(appWindow, NULL, TRUE);
        UpdateWindow(appWindow);
#endif
/// In this application, the serial number is written to the Windows registry.
        SetRegistryKey("Software\\LXFramework", "SerialNumber", serialNumber);
      }
      break;

	 case eSellerate_FAILURE:
		 {
			MessageBox(appWindow, "Failure in eSellerate\nPlease Contact Author", "LXViewer", MB_OK);
		 }
		 break;
  }

/// Remember to release memory allocated by eSellerate_Purchase().
  eSellerate_DeleteResultData(resultData);
}

static
long eSellerValidate (
) {
/// In this application, the serial number
/// is stored in the Windows registry.
  BOOL found = GetRegistryKey("Software\\GeckoSoft", "SerialNumber", serialNumber);
  if ( found == FALSE )
    return NoSerialNumber;

#if 0
/*5*  VALIDATE ACTIVATION example  */
  eSellerate_ErrorCode result = eSellerate_ValidateActivation (
    "PUB775527079", // Publisher ID
    "ACT979610220", // Activation Set ID used at activation
    serialNumber    // serial number that was activated
  );
  if ( result != eSellerate_SUCCESS )
    result = eSellerate_ActivateSerialNumber (
      "PUB775527079", // Publisher ID
      "ACT979610220", // Activation Set ID used at activation
      serialNumber,   // serial number that was activated
      eSellerate_TRUE // ask to connect, if need be
    );
  if ( result == eSellerate_SUCCESS )
#endif
    return Good;
//  else
  //  return NotActivated;
}
#endif

/////////////////////////////////////////////////////////////////////////
// CCommands

LRESULT CCommands::OnZoomIn(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pSVGElement)
	{
		CLSVGSVGElement* psvgsvgElement = static_cast<CLSVGSVGElement*>(m_pSVGElement->m_pNode);

		psvgsvgElement->put_currentScale(psvgsvgElement->m_currentScale*2);

		InvalidateRect(NULL);	// TODO remove
	}
#endif
	return 0;
}

LRESULT CCommands::OnZoomOut(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pSVGElement)
	{
		CLSVGSVGElement* psvgsvgElement = static_cast<CLSVGSVGElement*>(m_pSVGElement->m_pNode);

		psvgsvgElement->put_currentScale(psvgsvgElement->m_currentScale/2);

		InvalidateRect(NULL);	// TODO remove
	}
#endif

	return 0;
}

LRESULT CCommands::OnOriginalView(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	if (m_pSVGElement)
	{
		CLSVGSVGElement* psvgsvgElement = static_cast<CLSVGSVGElement*>(m_pSVGElement->m_pNode);

		psvgsvgElement->m_currentTranslate->put_x(0);
		psvgsvgElement->m_currentTranslate->put_y(0);
		psvgsvgElement->put_currentScale(1);

		InvalidateRect(NULL);	// TODO remove
	}
#endif

	return 0;
}

LRESULT CCommands::OnPlay(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	m_pActiveDocument->StartPlay();

	return 0;
}

LRESULT CCommands::OnEditCopy(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0
	CComBSTR xmltext;

	if (m_range && FALSE)	// Selection
	{
		CComPtr<ILDOMDocumentFragment> fragment;
		m_range->cloneContents(&fragment);

		fragment->get_textContent(&xmltext);
	}
	else
	{
		m_pView->m_document->saveXML(_variant_t(/*NULL*/), &xmltext);
	}

	HGLOBAL h = GlobalAlloc(GMEM_SHARE, xmltext.Length()*2+2);
	if (h)
	{
		LPBYTE p = (LPBYTE)GlobalLock(h);
		if (p)
		{
			CopyMemory(p, (BSTR)xmltext, xmltext.Length()*2+2);

			GlobalUnlock(h);

			CComObject<COleDataObject>* pDataObject;
			CComObject<COleDataObject>::CreateInstance(&pDataObject);
			if (pDataObject)
			{
				pDataObject->AddRef();

				STGMEDIUM stgm;
				stgm.tymed = TYMED_HGLOBAL;
				stgm.pUnkForRelease = NULL;
				stgm.hGlobal = h;

				FORMATETC etc = { CF_UNICODETEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};

				pDataObject->SetData(&etc, &stgm, TRUE);

				::OleSetClipboard(pDataObject);

				pDataObject->Release();
			}
		}
	}
#endif

	return 0;
}

LRESULT CCommands::OnViewSource(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	if (m_pActiveDocument->m_fileName.Length() == 0)
	{
		TCHAR temppath[MAX_PATH];
		GetTempPath(sizeof(temppath), temppath);

		TCHAR filename[MAX_PATH];
		GetTempFileName(temppath, "nn", 0, filename);

		m_pActiveDocument->m_fileName = A2W(filename);

		m_pActiveDocument->m_textData->save(m_pActiveDocument->m_fileName);
	}

	ShellExecute(NULL, "open", "notepad.exe", W2A(m_pActiveDocument->m_fileName), NULL, SW_SHOW);

	return 0;
}

LRESULT CCommands::OnSaveAs(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	USES_CONVERSION;

	HWND hwnd = NULL;	// TODO
#if 0
	if (m_pUI)
		hwnd = m_pUI->m_hWnd;
	else
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
#endif

#if 0
	if (eSellerValidate() == Good)
	{
		TCHAR sbuffer[4096];

		LPOLESTR szDisplayName;
		m_pActiveDocument->m_curMoniker->GetDisplayName(NULL, NULL, &szDisplayName);

		TCHAR path[512];
		URL_COMPONENTS url_components = {0};
		url_components.dwStructSize = sizeof(url_components);
		url_components.dwUrlPathLength = 512;
		url_components.lpszUrlPath = path;
		InternetCrackUrl(W2A(szDisplayName), 0, ICU_DECODE | ICU_ESCAPE, &url_components);

		LPTSTR filename = PathFindFileName(path);

		if (filename)
			strcpy(sbuffer, filename);
		else
			sbuffer[0] = 0;

		OPENFILENAME	ofn = {0};
		ofn.lStructSize = sizeof(OPENFILENAME_NT4A);
		ofn.hwndOwner = hwnd;
		ofn.hInstance = _Module.m_hInst;
		ofn.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
		ofn.lpstrFile = sbuffer;
		ofn.nMaxFile = sizeof(sbuffer);
	//	ofn.lpstrInitialDir = curdir;
	//	ofn.lpstrFilter = FilesFilter;
	//	ofn.nFilterIndex = 2;
		
		if (::GetSaveFileName(&ofn))
		{
			URLDownloadToFile(m_pActiveDocument->m_spClientSite, W2A(szDisplayName), sbuffer, 0, NULL);
			/*
			HRESULT hr = SaveDocument(_bstr_t(sbuffer));
			if (SUCCEEDED(hr))
			{
			}
			*/
		}

		CoTaskMemFree(szDisplayName);
	}
	else
	{
		if (::MessageBox(hwnd, "This feature is only available if you purchase the program (US$20).\nDo you want to purchase it now?", "LXViewer", MB_YESNO) == IDYES)
		{
			OnPurchase();
		}
	}
#endif

	return 0;
}

#if 0
#include "PrefsLanguageDlg.h"
#include "PrefsConnectionDlg.h"
#endif

LRESULT CCommands::OnPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	ATLASSERT(0);
#if 0	// Had this
	HWND hwnd = NULL;	// TODO
	/*
	if (m_pUI)
		hwnd = m_pUI->m_hWnd;
	else
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
		*/

	CPropertySheet sheet("Preferences", 0, hwnd);
	sheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;

	g_preferences.ForceReload();	// We reload it just in case

	CPrefsLanguageDlg content;
	content.m_pPrefs = &g_preferences;

	CPrefsConnectionDlg conn;
	conn.m_pPrefs = &g_preferences;

	sheet.AddPage(content);
	sheet.AddPage(conn);

	if (sheet.DoModal() == IDOK)
	{
		g_preferences.Save();
	}
#endif

	return 0;
}

LRESULT CCommands::OnHelp(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	TCHAR filename[MAX_PATH];
	GetModuleFileName(_Module.m_hInst, filename, sizeof(filename));

	TCHAR dir[256];
	TCHAR path[256];
	_splitpath(filename, dir, path, NULL, NULL);

	_makepath(filename, dir, path, "LXViewerHelp.html", NULL);

	ShellExecute(NULL, "open", "iexplore.exe", filename, NULL, SW_SHOW);

	return 0;
}

LRESULT CCommands::OnAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HWND hwnd = NULL;	// TODO
	/*
	if (m_pUI)
		hwnd = m_pUI->m_hWnd;
	else
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
		*/

	MessageBox(hwnd, "LXViewer 0.8.0\nhttp://www.lerstad.com", "About", MB_OK);
	return 0;
}

void CCommands::OnPurchase()
{
	HWND hwnd = NULL;	// TODO
	/*
	if (m_pUI)
		hwnd = m_pUI->m_hWnd;
	else
		m_pActiveDocument->m_spInPlaceSite->GetWindow(&hwnd);
		*/

	/*
	TCHAR pathname[MAX_PATH];
	GetModuleFileName(NULL, pathname, sizeof(pathname));

	TCHAR dir[256];
	TCHAR path[MAX_PATH];
	_splitpath(pathname, dir, path, NULL, NULL);

	TCHAR libpath[MAX_PATH];
	_makepath(libpath, dir, path, "eSellerateEngine.dll", NULL);
	*/

#if 0
	eSellerPurchase(hwnd);
#endif
}

LRESULT CCommands::OnPurchase(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	OnPurchase();

	return 0;
}
