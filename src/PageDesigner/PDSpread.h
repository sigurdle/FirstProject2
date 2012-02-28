#if 0
class CObjectMap;
class CPDDocument;

#include "PDSpreadImpl.h"

class ATL_NO_VTABLE CPDSpread : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDSpreadImpl<IPDSpread>
{
public:
	CPDSpread()
	{
		m_previousSpread = NULL;
		m_nextSpread = NULL;
	}

	CComObject<CPDSpread>* m_previousSpread;
	CComObject<CPDSpread>* m_nextSpread;
	
	HRESULT FinalConstruct();
	void FinalRelease();

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDSpread)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDSpread)
END_COM_MAP()

// IPDSpread
public:
	STDMETHOD(loadXML)(/*[in]*/ IDOMNode* node);
	STDMETHOD(saveAsXML)(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node);
};

#endif