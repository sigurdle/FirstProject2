#pragma once

#include "WEUndoSourceLast.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CWEUndoMoveObjects
class CWEUndoMoveObjects :
	public CWEUndoSourceLast
{
public:
	CWEUndoMoveObjects()
	{
	//	m_dx = 0;
	//	m_dy = 0;
	}

	Array<GUID> m_targetElements;
	Array<LDraw::PointD> m_deltas;
//	double m_dx;
//	double m_dy;

public:

// IOleUndoUnit
	void Do(/* [in] */ IUndoManager *pUndoManager);
	System::StringW* GetDescription();
//	long GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid);
	void OnNextAdd(void);
};

}	// LXmlEdit
}
