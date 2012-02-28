#include "stdafx.h"
#include "LXUI2.h"
#include "UndoManager.h"

namespace System
{
namespace UI
{

UndoManager::UndoManager()
{
	m_state = 0;
	m_pOpenParent = NULL;
}

UndoManager::~UndoManager()
{
	ClearUndoList();
	ClearRedoList();
}

void UndoManager::ClearUndoList()
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

void UndoManager::ClearRedoList()
{
#if 0
	UPOSITION pos = m_redoList.GetHeadPosition();
	while (pos)
	{
		IUndoUnit* pUnit = (IUndoUnit*)m_redoList.GetNext(pos);
#if 0
		pUnit->Release();
#endif
	}
#endif

	m_redoList.clear();
}

void UndoManager::Open(IParentUndoUnit *pPUU)
{
#if 0
	pPUU->AddRef();
#endif
	m_pOpenParent = pPUU;
}

void UndoManager::Close(IParentUndoUnit *pPUU, bool fCommit)
{
	if (pPUU != m_pOpenParent)
		THROW(-1);//return E_INVALIDARG;

	if (m_pOpenParent)
	{
		m_pOpenParent = NULL;

		if (fCommit)
		{
			Add(pPUU);
		}
#if 0
		pPUU->Release();
#endif
	}
}

StringW* UndoManager::GetLastUndoDescription()
{
	if (m_undoList.size() > 0)
	{
		return m_undoList.front()->GetDescription();
	}

	return NULL;
}

StringW* UndoManager::GetLastRedoDescription()
{
	if (m_redoList.size() > 0)
	{
		return m_redoList.back()->GetDescription();
	}

	return NULL;
}

int UndoManager::GetOpenParentState(uint32 *pdwState)
{
	if (m_pOpenParent)
	{
		*pdwState = m_pOpenParent->GetParentState();
		return 0;
	}
	else
	{
		return 1;
	}
}

void UndoManager::Enable(bool fEnable)
{
	// TODO
}

void UndoManager::DiscardFrom(/* [in] */ IUndoUnit *pUU)
{
}

/*
If the undo manager is in the base state, it should put the new unit on
the undo stack and discard the entire redo stack. If the undo manager
is in the undo state, it should put new units on the redo stack.
If the undo manager is in the redo state, it should put units on the
undo stack without affecting the redo stack.
*/

void UndoManager::Add(IUndoUnit *pUU)
{
	if (m_pOpenParent)
	{
		m_pOpenParent->Add(pUU);
	}
	else
	{
#if 0
		pUU->AddRef();
#endif

		if (m_state == 0)	// base state
		{
			ClearRedoList();
			m_undoList.push_front(pUU);
		}
		else if (m_state == 1)	// undo state
		{
			m_redoList.push_front(pUU);
		}
		else if (m_state == 2)	// redo state
		{
			m_undoList.push_front(pUU);
		}

//		ASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}
}

void UndoManager::UndoTo(IUndoUnit *pUU)
{
	if (pUU == NULL && !m_undoList.empty())
	{
		pUU = m_undoList.front();
	}

	if (pUU)
	{
		list<IUndoUnit*>::iterator pos = m_undoList.find(pUU);
		if (pos == m_undoList.end())
		{
			ASSERT(0);
			THROW(-1);//return E_INVALIDARG;	// The specified undo unit is not on the undo stack.
		}

		m_state = 1;	// Undo State

		IUndoUnit* pUndo;

		while (1)
		{
			pUndo = m_undoList.front();//GetHead();

			pUndo->Do(this);

			m_undoList.pop_front();	// Remove it from the undo stack
#if 0
			pUndo->Release();
#endif

			if (pUndo == pUU) break;
		}

		m_state = 0;

//		ATLASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}

//	return S_OK;
}

void UndoManager::RedoTo(IUndoUnit *pUU)
{
	if (pUU == NULL && !m_redoList.empty())
	{
		pUU = m_redoList.front();
	}

	if (pUU)
	{
		list<IUndoUnit*>::iterator pos = m_redoList.find(pUU);
		if (pos == m_redoList.end())
		{
			ASSERT(0);
			THROW(-1);//return E_INVALIDARG;	// The specified undo unit is not on the redo stack.
		}

		m_state = 2;	// Redo state

		IUndoUnit* pUndo;

		while (1)
		{
			pUndo = m_redoList.front();

			pUndo->Do(this);

			m_redoList.pop_front();	// Remove it from the undo stack
#if 0
			pUndo->Release();
#endif

			if (pUndo == pUU) break;
		}

		m_state = 0;

		//ATLASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}
}

}	// UI
}
