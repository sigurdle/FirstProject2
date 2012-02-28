#include "stdafx.h"
#include "LXMLEditor2.h"

#include "UndoParent.h"

namespace System
{
namespace LXmlEdit
{

void CUndoParent::Add(/* [in] */ IUndoUnit *pUU)
{
#if 0
	pUU->AddRef();
#endif

	if (m_state == 0)	// undo state
	{
		m_undoList.push_front(pUU);
	}
	else if (m_state == 1)	// redo state
	{
		m_undoList.push_front(pUU);
	}
}

long CUndoParent::GetParentState()
{
	return m_flags;
}

void CUndoParent::Do(/* [in] */ IUndoManager *pUndoManager)
{
	pUndoManager->Open(this);

	m_state = !m_state;

	list<IUndoUnit*>::iterator pos = m_undoList.begin();
	while (pos != m_undoList.end())
	{
		list<IUndoUnit*>::iterator pos2 = pos;
		IUndoUnit* pUU = *pos;//(IUndoUnit*)m_undoList.GetNext(pos);
		++pos;

		pUU->Do(pUndoManager);
		m_undoList.erase(pos2);

	//	pUU->Release();
	}

	pUndoManager->Close(this, true);
}

/*
sysstring CUndoParent::GetDescription()
{
	return L"New Filter";
}
*/

void CUndoParent::Open(/* [in] */ IParentUndoUnit *pPUU)
{
}

void CUndoParent::Close(/* [in] */ IParentUndoUnit *pPUU, /* [in] */ bool fCommit)
{
}

void CUndoParent::OnNextAdd(void)
{
}

#if 0
STDMETHODIMP CUndoParent::FindUnit(/* [in] */ IOleUndoUnit *pUU)
{
	return S_OK;
}
#endif

}
}
