#pragma once

namespace System
{
namespace LXmlEdit
{

class CUndoParent : 
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IParentUndoUnit // IOleUndoUnit
{
public:
	CUndoParent()
	{
		m_flags = 1;//UAS_NORMAL;
		m_state = 1;
	}

	void FinalRelease()
	{
		ASSERT(0);
#if 0

		while (!m_undoList.empty())
		{
			IUndoUnit* pUU = (IUndoUnit*)m_undoList.RemoveTail();
	//		pUU->Release();
		}
#endif
	}

	ULONG m_flags;

	int m_state;
	list<IUndoUnit*> m_undoList;

	/*
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoParent)
	COM_INTERFACE_ENTRY(IOleUndoUnit)
	COM_INTERFACE_ENTRY(IOleParentUndoUnit)
END_COM_MAP()
*/

public:

// IUndoUnit
	void Do(/* [in] */ IUndoManager *pUndoManager);
//	STDMETHOD(GetDescription)(/* [out] */ BSTR __RPC_FAR *pBstr);
//	STDMETHOD(GetUnitType)(/* [out] */ CLSID __RPC_FAR *pClsid, /* [out] */ LONG __RPC_FAR *plID);
	void OnNextAdd(void);

// IParentUndoUnit
	void Open(/* [in] */ IParentUndoUnit *pPUU);
	void Close(/* [in] */ IParentUndoUnit *pPUU, /* [in] */ bool fCommit);
	void Add(/* [in] */ IUndoUnit *pUU);
	//STDMETHOD(FindUnit)(/* [in] */ IUndoUnit *pUU);
	long GetParentState();
};

}
}
