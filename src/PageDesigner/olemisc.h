#pragma once

HGLOBAL AFXAPI _AfxOleGetObjectDescriptorData(
	CLSID       clsid,
	DWORD       dwDrawAspect,
	SIZEL       sizel,
	POINTL      pointl,
	DWORD       dwStatus,
	LPCOLESTR   lpszFullUserTypeName,
	LPCOLESTR   lpszSrcOfCopy);

HGLOBAL AFXAPI _AfxOleGetObjectDescriptorData(
	LPOLEOBJECT     lpOleObj,
	LPCOLESTR       lpszSrcOfCopy,
	DWORD           dwDrawAspect,
	POINTL          pointl,
	LPSIZEL         lpSizelHim);
