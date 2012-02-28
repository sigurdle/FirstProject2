#pragma once

#include "WEUndoSourceLast.h"

namespace System
{
namespace LXmlEdit
{

class CEXMLViewGroup;

class CWEUndoGroupObjects :
	public CWEUndoSourceLast
{
public:
	CWEUndoGroupObjects()
	{
	}

public:


	GUID m_groupGUID;
	GUID m_parentgroupGUID;
	GUID m_beforegroupGUID;

	Array<GUID> m_parentElements;
	Array<GUID> m_beforeElements;
	Array<GUID> m_targetElements;

	ErrorCode DoInitial(CEXMLViewGroup* pView, IUndoManager *pUndoManager);

public:

// IUndoUnit
	void Do(/* [in] */ IUndoManager *pUndoManager);
	System::StringW* GetDescription();
//	long GetUnitType(/* [out] */ CLSID *pClsid);
	void OnNextAdd(void);
};

}	// LXmlEdit
}
