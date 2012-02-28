// LXMTODocument.h : Declaration of the CLXMTODocument

#ifndef __LXMTODOCUMENT_H_
#define __LXMTODOCUMENT_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLXMTODocument
class ATL_NO_VTABLE CLXMTODocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLXMTODocument, &CLSID_LXMTODocument>,
	public ILXMTODocument
{
public:
	CLXMTODocument()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LXMTODOCUMENT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXMTODocument)
	COM_INTERFACE_ENTRY(ILXMTODocument)
END_COM_MAP()

// ILXMTODocument
public:
};

#endif //__LXMTODOCUMENT_H_
