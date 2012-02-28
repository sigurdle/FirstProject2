#pragma once

namespace System
{
namespace LXmlEdit
{

class CEXMLDocument;

/////////////////////////////////////////////////////////////////////////////
// CWEUndoSourceLastBase
class CWEUndoSourceLast : 
	public IUndoUnit
{
public:
	CWEUndoSourceLast()
	{
		m_bRedo = false;
		m_pDocument = NULL;

		m_bSourceEditLast = false;
//		m_sourceText = NULL;
	}

	bool m_bRedo;
	bool m_bSourceEditLast;
	System::StringW* m_sourceText;

	CEXMLDocument*	m_pDocument;

public:

#if 0
	void Do(/* [in] */ IUndoManager *pUndoManager);
	sysstring GetDescription();
	long GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid);
	void OnNextAdd(void);
#endif
};

}	// LXmlEdit
}
