// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__53A72BCB_3514_47E3_A66B_7579C3087A29__INCLUDED_)
#define AFX_STDAFX_H__53A72BCB_3514_47E3_A66B_7579C3087A29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#include <atlbase.h>

#include <atlapp.h>	// I added this

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>

// My additions
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

#include <atlframe.h>

#include <AtlDlgs.h>
#include <AtlCtrls.h>
#include <AtlMisc.h>

#include <comdef.h>

#define ASSERT(x)	ATLASSERT(x)
#define TRACE	ATLTRACE
#define VERIFY(x)	(x)

#include "..\..\Utils\UPtrList.h"
#include "..\..\Utils\UPtrArray.h"
#include "..\..\Utils\UString.h"
#include "..\..\Utils\UArray.h"
#include "..\..\Utils\Draw.h"
#include "..\..\Utils\DblPoint.h"
//#include "..\..\Utils\Rect.h"
#include "..\..\Utils\IEnumfe.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\..\\Utils\\Debug\\Utils.lib")
#else
#pragma comment(lib, "..\\..\\Utils\\Release\\Utils.lib")
#endif

class COleDataObject
{
protected:
	LPDATAOBJECT m_pDataObject;

public:
	void Attach(LPDATAOBJECT dataObject)
	{
		m_pDataObject = dataObject;
	}
	
	HGLOBAL GetGlobalData(UINT nClipboardFormat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__53A72BCB_3514_47E3_A66B_7579C3087A29__INCLUDED)
