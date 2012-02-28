#ifndef __WEUNDOMANAGER_H_
#define __WEUNDOMANAGER_H_

#include "resource.h"       // main symbols

namespace System
{
namespace LXmlEdit
{

class CEnumOleUndoUnits /*:
	public IEnumUndoUnits*/
{
public:
	CEnumOleUndoUnits()
	{
		m_iCur = 0;
	}

	void FinalRelease()
	{
		for (int i = 0; i < m_list.GetSize(); i++)
		{
			//m_list[i]->Release();
		}
	}

	Array<IUndoUnit*> m_list;

	int m_iCur;

  virtual /* [local] */ ErrorCode Next( 
      /* [in] */ ULONG cElt,
      /* [length_is][size_is][out] */ IUndoUnit **rgElt,
      /* [out] */ ULONG *pcEltFetched)
	{
		int cElt2 = MIN((int)cElt, m_list.GetSize()-m_iCur);

		int n;
		for (n = 0; n < cElt2; n++)
		{
//			(rgElt[n] = m_list[m_iCur])->AddRef();
			m_iCur++;
		}

		if (pcEltFetched)
			*pcEltFetched = n;

		if (n > 0)
			return Success_True;
		else
			return Success_False;
	}
  
  virtual ErrorCode Skip( 
      /* [in] */ ULONG cElt)
	{
		m_iCur += cElt;
		return Success;
	}
  
	virtual ErrorCode Reset( void)
	{
		m_iCur = 0;
		return Success;
	}
  
#if 0
	virtual HRESULT STDMETHODCALLTYPE Clone( 
      /* [out] */ IEnumUndoUnits **ppEnum)
	{
		ASSERT(0);
#if 0
		CComObject<CEnumOleUndoUnits>* pEnum;
		CComObject<CEnumOleUndoUnits>::CreateInstance(&pEnum);
		if (pEnum)
		{
			pEnum->AddRef();

		// Clone state
			pEnum->m_iCur = m_iCur;

			for (int i = 0; i < m_list.GetSize(); i++)
			{
				m_list[i]->AddRef();
				pEnum->m_list.Add(m_list[i]);
			}

			*ppEnum = pEnum;
		}
		else
			*ppEnum = NULL;
#endif
		return Success;
	}
#endif
};

class CWEUndoManager : 

	public IUndoManager
{
public:
	CWEUndoManager()
	{
		m_state = 0;
		m_pOpenParent = NULL;
	}

	~CWEUndoManager()
	{
		ClearUndoList();
		ClearRedoList();
	}

	int m_state;
	IParentUndoUnit*	m_pOpenParent;

	list<IUndoUnit*> m_undoList;
	list<IUndoUnit*> m_redoList;

	void ClearUndoList()
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_undoList.GetHeadPosition();
		while (pos)
		{
			IOleUndoUnit* pUnit = (IOleUndoUnit*)m_undoList.GetNext(pos);
			pUnit->Release();
		}

		m_undoList.RemoveAll();
#endif
	}

	void ClearRedoList()
	{
		ASSERT(0);
#if 0
		UPOSITION pos = m_redoList.GetHeadPosition();
		while (pos)
		{
			IOleUndoUnit* pUnit = (IOleUndoUnit*)m_redoList.GetNext(pos);
			pUnit->Release();
		}

		m_redoList.RemoveAll();
#endif
	}

public:

	void Open(IParentUndoUnit *pPUU);
	void Close(IParentUndoUnit *pPUU, bool fCommit);
	void Add(IUndoUnit *pUU);
	int GetOpenParentState(uint *);

	void DiscardFrom(/* [in] */ IUndoUnit *pUU)
  	{
	}

	void UndoTo(IUndoUnit *pUU);
	void RedoTo(IUndoUnit *pUU);

	System::StringW* GetLastUndoDescription();
	System::StringW* GetLastRedoDescription();

#if 0
	STDMETHOD(EnumUndoable)(/* [out] */ IEnumOleUndoUnits __RPC_FAR *__RPC_FAR *ppEnum)
  	{
		if (ppEnum == NULL) return E_POINTER;

		CComObject<CEnumOleUndoUnits>* pEnum;
		CComObject<CEnumOleUndoUnits>::CreateInstance(&pEnum);
		if (pEnum)
		{
			pEnum->AddRef();

			UPOSITION pos = m_undoList.GetHeadPosition();
			while (pos)
			{
				IOleUndoUnit* pUnit = (IOleUndoUnit*)m_undoList.GetNext(pos);
				pUnit->AddRef();
				pEnum->m_list.Add(pUnit);
			}

			*ppEnum = pEnum;
		}
		else
			*ppEnum = NULL;

		return S_OK;
	}
	
	STDMETHOD(EnumRedoable)(/* [out] */ IEnumOleUndoUnits __RPC_FAR *__RPC_FAR *ppEnum)
  	{
		if (ppEnum == NULL) return E_POINTER;

		CComObject<CEnumOleUndoUnits>* pEnum;
		CComObject<CEnumOleUndoUnits>::CreateInstance(&pEnum);
		if (pEnum)
		{
			pEnum->AddRef();

			UPOSITION pos = m_redoList.GetHeadPosition();
			while (pos)
			{
				IOleUndoUnit* pUnit = (IOleUndoUnit*)m_redoList.GetNext(pos);
				pUnit->AddRef();
				pEnum->m_list.Add(pUnit);
			}

			*ppEnum = pEnum;
		}
		else
			*ppEnum = NULL;

		return S_OK;
	}
#endif
	void Enable(bool fEnable)
	{
	}
};

}	// LXmlEdit
}

#endif //__WEUNDOMANAGER_H_
