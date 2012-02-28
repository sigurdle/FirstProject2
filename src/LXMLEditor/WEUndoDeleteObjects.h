#pragma once

#include "WEUndoSourceLast.h"

namespace System
{
namespace LXmlEdit
{

class CWEUndoDeleteObjects :
	public CWEUndoSourceLast
{
public:
	CWEUndoDeleteObjects()
	{
		m_pStream = NULL;
	}

public:
	Array<GUID> m_parentElements;
	Array<GUID> m_beforeElements;
	Array<GUID> m_targetElements;
	System::IO::ISequentialByteStream* m_pStream;

public:

// IOleUndoUnit
	void Do(/* [in] */ IUndoManager * pUndoManager);
	System::StringW* GetDescription();
	//long GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid);
	void OnNextAdd();
};

}	// LXmlEdit
}
