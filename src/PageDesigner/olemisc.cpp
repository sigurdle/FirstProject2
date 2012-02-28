#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// OLE utility functions (some borrowed from OLE2UI library)

HGLOBAL AFXAPI _AfxOleGetObjectDescriptorData(
	CLSID       clsid,
	DWORD       dwDrawAspect,
	SIZEL       sizel,
	POINTL      pointl,
	DWORD       dwStatus,
	LPCOLESTR   lpszFullUserTypeName,
	LPCOLESTR   lpszSrcOfCopy)
{
	HGLOBAL     hMem = NULL;
	LPOBJECTDESCRIPTOR lpOD;
	DWORD       dwObjectDescSize, dwFullUserTypeNameLen, dwSrcOfCopyLen;

	// Get the length of Full User Type Name; Add 1 for the null terminator
	dwFullUserTypeNameLen = lpszFullUserTypeName ?
		ocslen(lpszFullUserTypeName)+1 : 0;

	// Get the Source of Copy string and it's length;
	//  Add 1 for the null terminator
	if (lpszSrcOfCopy && lpszSrcOfCopy[0] != '\0')
	   dwSrcOfCopyLen = ocslen(lpszSrcOfCopy)+1;
	else
	{
	   // No src moniker so use user type name as source string.
	   lpszSrcOfCopy =  lpszFullUserTypeName;
	   dwSrcOfCopyLen = dwFullUserTypeNameLen;
	}

	// Allocate space for OBJECTDESCRIPTOR and the additional string data
	dwObjectDescSize = sizeof(OBJECTDESCRIPTOR);
	hMem = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT,
	   dwObjectDescSize + (dwFullUserTypeNameLen + dwSrcOfCopyLen) *
		sizeof(OLECHAR));
	if (!hMem)
		return NULL;

	lpOD = (LPOBJECTDESCRIPTOR)GlobalLock(hMem);

	// Set the FullUserTypeName offset and copy the string
	if (lpszFullUserTypeName)
	{
		lpOD->dwFullUserTypeName = dwObjectDescSize;
		ocscpy((LPOLESTR)((LPBYTE)lpOD+lpOD->dwFullUserTypeName), lpszFullUserTypeName);
	}
	else
		lpOD->dwFullUserTypeName = 0;  // zero offset indicates that string is not present

	// Set the SrcOfCopy offset and copy the string
	if (lpszSrcOfCopy)
	{
		lpOD->dwSrcOfCopy = dwObjectDescSize + dwFullUserTypeNameLen * sizeof(OLECHAR);
		ocscpy((LPOLESTR)((LPBYTE)lpOD+lpOD->dwSrcOfCopy), lpszSrcOfCopy);
	}
	else
		lpOD->dwSrcOfCopy = 0;  // zero offset indicates that string is not present

	// Initialize the rest of the OBJECTDESCRIPTOR
	lpOD->cbSize       = dwObjectDescSize +
		(dwFullUserTypeNameLen + dwSrcOfCopyLen) * sizeof(OLECHAR);
	lpOD->clsid        = clsid;
	lpOD->dwDrawAspect = dwDrawAspect;
	lpOD->sizel        = sizel;
	lpOD->pointl       = pointl;
	lpOD->dwStatus     = dwStatus;

	GlobalUnlock(hMem);
	return hMem;
}

HGLOBAL AFXAPI _AfxOleGetObjectDescriptorData(
	LPOLEOBJECT     lpOleObj,
	LPCOLESTR       lpszSrcOfCopy,
	DWORD           dwDrawAspect,
	POINTL          pointl,
	LPSIZEL         lpSizelHim)
{
	USES_CONVERSION;

	CLSID           clsid;
	LPOLESTR        lpszFullUserTypeName = NULL;
	CComPtr<IMoniker>/*LPMONIKER*/       lpSrcMonikerOfCopy;// = NULL;
	HGLOBAL         hObjDesc = NULL;
	CComPtr<IBindCtx>        pbc;// = NULL;
	SCODE           sc;
	SIZEL           sizelHim;
	BOOL            bFreeSrcOfCopy = FALSE;
	CComQIPtr<IViewObject2>/*LPVIEWOBJECT2*/   lpViewObj2;
	CComQIPtr<IOleLink>/*LPOLELINK*/       lpOleLink;
	BOOL            fIsLink;
	TCHAR           szLinkedTypeFmt[80];
	LPCOLESTR       lpszLinkedTypeFmt;
	LPOLESTR        lpszBuf = NULL;
	DWORD           dwStatus = 0;

	// query for IOleLink
	lpOleLink = /*QUERYINTERFACE(*/lpOleObj;//, IOleLink);
	fIsLink = lpOleLink != NULL;

	// query for IViewObject2
	lpViewObj2 = /*QUERYINTERFACE(*/lpOleObj;//, IViewObject2);

	// Get CLSID
	sc = lpOleObj->GetUserClassID(&clsid);
	if (sc != S_OK)
		clsid = CLSID_NULL;

	// Get FullUserTypeName
	sc = lpOleObj->GetUserType(USERCLASSTYPE_FULL, &lpszFullUserTypeName);

	MessageBox(NULL, _bstr_t(lpszFullUserTypeName), "FullUserName", MB_OK);


	// if object is a link, then expand usertypename to be "Linked %s"
	if (fIsLink && lpszFullUserTypeName != NULL)
	{
		// Note: If this LoadString call fails, it is likely that
		//  _AFX_NO_OLE_RESOURCES is defined in your .RC file.
		// To correct the situation remove the following line from your
		//  resource script:
		//      #define _AFX_NO_OLE_RESOURCES
		// This should be done using the Resource.Set Includes... command.

		//VERIFY(AfxLoadString(AFX_IDS_PASTELINKEDTYPE, szLinkedTypeFmt));
		strcpy(szLinkedTypeFmt, "Linked %s");

		lpszLinkedTypeFmt = T2COLE(szLinkedTypeFmt);
		lpszBuf = (LPOLESTR)CoTaskMemAlloc((ocslen(lpszFullUserTypeName) +
			ocslen(lpszLinkedTypeFmt) + 1) * sizeof(OLECHAR));
		if (lpszBuf != NULL)
		{
#ifdef OLE2ANSI
			sprintf(lpszBuf, lpszLinkedTypeFmt, lpszFullUserTypeName);
#else
			swprintf(lpszBuf, lpszLinkedTypeFmt, lpszFullUserTypeName);
#endif
			CoTaskMemFree(lpszFullUserTypeName);
			lpszFullUserTypeName = lpszBuf;
		}
	}

	// get source of copy
	if (fIsLink)
	{
		sc = lpOleLink->GetSourceDisplayName((LPOLESTR*)&lpszSrcOfCopy);
		bFreeSrcOfCopy = TRUE;
	}
	else if (lpszSrcOfCopy == NULL)
	{
		sc = lpOleObj->GetMoniker(
			OLEGETMONIKER_TEMPFORUSER, OLEWHICHMK_OBJFULL, &lpSrcMonikerOfCopy);
		if (sc == S_OK)
		{
			CreateBindCtx(0, &pbc);
			lpSrcMonikerOfCopy->GetDisplayName(pbc, NULL,
				(LPOLESTR*)&lpszSrcOfCopy);

			MessageBox(NULL, _bstr_t(lpszSrcOfCopy), "DisplayName", MB_OK);

			pbc.Release();//RELEASE(pbc);
			bFreeSrcOfCopy = TRUE;
		}
	}

	if (lpSizelHim)
	{
		// Use extents passed by the caller
		sizelHim = *lpSizelHim;
	}
	else if (lpViewObj2)
	{
		// Get the current extents from the object
		sc = lpViewObj2->GetExtent(dwDrawAspect, -1, NULL,
			(LPSIZEL)&sizelHim);
		if (sc != S_OK)
			sizelHim.cx = sizelHim.cy = 0;
	}
	else
	{
		sizelHim.cx = sizelHim.cy = 0;
	}

	// Get dwStatus
	sc = lpOleObj->GetMiscStatus(dwDrawAspect, &dwStatus);
	if (sc != S_OK)
		dwStatus = 0;

	// Get OBJECTDESCRIPTOR
	hObjDesc = _AfxOleGetObjectDescriptorData(clsid, dwDrawAspect, sizelHim,
		pointl, dwStatus, lpszFullUserTypeName, lpszSrcOfCopy);

	// Clean up
	CoTaskMemFree(lpszFullUserTypeName);
	if (bFreeSrcOfCopy)
		CoTaskMemFree((LPOLESTR)lpszSrcOfCopy);
	lpSrcMonikerOfCopy.Release();
	lpOleLink.Release();
	lpViewObj2.Release();

	return hObjDesc;
}
