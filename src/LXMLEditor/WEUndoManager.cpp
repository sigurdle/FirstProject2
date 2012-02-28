#include "stdafx.h"
#include "LXMLEditor.h"
#include "WEUndoManager.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CWEUndoManager

void CWEUndoManager::Open(IParentUndoUnit *pPUU)
{
#if 0
	pPUU->AddRef();
#endif
	m_pOpenParent = pPUU;
}

void CWEUndoManager::Close(IParentUndoUnit *pPUU, bool fCommit)
{
	if (pPUU != m_pOpenParent)
		throw -1;//return E_INVALIDARG;

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

System::StringW* CWEUndoManager::GetLastUndoDescription()
{
	if (!m_undoList.empty())
	{
		return m_undoList.front()->GetDescription();
	}

	return NULL;
}

System::StringW* CWEUndoManager::GetLastRedoDescription()
{
	if (!m_redoList.empty())
	{
		return m_redoList.front()->GetDescription();
	}

	return NULL;
}

int CWEUndoManager::GetOpenParentState(uint *pdwState)
{
	if (m_pOpenParent)
	{
		*pdwState = m_pOpenParent->GetParentState();
		return Success_True;
	}
	else
	{
		return Success_False;
	}
}

/*
If the undo manager is in the base state, it should put the new unit on
the undo stack and discard the entire redo stack. If the undo manager
is in the undo state, it should put new units on the redo stack.
If the undo manager is in the redo state, it should put units on the
undo stack without affecting the redo stack.
*/

void CWEUndoManager::Add(IUndoUnit *pUU)
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

		ASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}
}

void CWEUndoManager::UndoTo(IUndoUnit *pUU)
{
	if (pUU == NULL && !m_undoList.empty())
	{
		pUU = m_undoList.front();
	}

	if (pUU)
	{
		list<IUndoUnit*>::iterator pos = m_undoList.find(pUU);
		if (pos == NULL)
		{
			ASSERT(0);
			throw -1;//return E_INVALIDARG;	// The specified undo unit is not on the undo stack.
		}

		m_state = 1;	// Undo State

		IUndoUnit* pUndo;

		while (1)
		{
			pUndo = m_undoList.front();

			pUndo->Do(this);

			m_undoList.erase(m_undoList.begin());	// Remove it from the undo stack
#if 0
			pUndo->Release();
#endif

			if (pUndo == pUU) break;
		}

		m_state = 0;

		ASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}

//	return S_OK;
}

void CWEUndoManager::RedoTo(IUndoUnit *pUU)
{
	if (pUU == NULL && !m_redoList.empty())
	{
		pUU = m_redoList.front();
	}

	if (pUU)
	{
		list<IUndoUnit*>::iterator pos = m_redoList.find(pUU);
		if (pos == NULL)
		{
			ASSERT(0);
			throw -1;//return E_INVALIDARG;	// The specified undo unit is not on the redo stack.
		}

		m_state = 2;	// Redo state

		IUndoUnit* pUndo;

		while (1)
		{
			pUndo = m_redoList.front();

			pUndo->Do(this);

			m_redoList.erase(m_redoList.begin());	// Remove it from the undo stack
#if 0
			pUndo->Release();
#endif

			if (pUndo == pUU) break;
		}

		m_state = 0;

		ASSERT(0);
#if 0
		Fire_OnChange();
#endif
	}
}

}	// LXmlEdit
}
