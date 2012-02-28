#pragma once

#if 0
class ATL_NO_VTABLE CLXMLEditorFrame : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IEFrame
{
public:
	CLXMLEditorFrame()
	{
	}

	ILXUIMDIFrameElement* m_frame;	// TODO, have pointer to own frame object instead

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CLXMLEditorFrame)
	COM_INTERFACE_ENTRY(IEFrame)
END_COM_MAP()

public:
	STDMETHOD(GetMDIFrame)(ILXUIMDIFrameElement* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_frame;
//		if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
};

#endif