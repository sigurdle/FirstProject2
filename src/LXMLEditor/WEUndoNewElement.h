#pragma once

#include "WEUndoSourceLast.h"

namespace System
{
namespace LXmlEdit
{

class CWEUndoNewElement :
	public CWEUndoSourceLast
{
public:
	CWEUndoNewElement()
	{
		m_pStream = NULL;
	}

public:
	GUID m_guidParentNode;
	GUID m_guidBeforeNode;
	GUID m_guidNode;
	System::IO::ISequentialByteStream* m_pStream;	// != NULL when the node isn't part of the document
//	CComPtr<Web::Node> node;	// != NULL when the node is part of the document

	ErrorCode DoInitial(IUndoManager *undoManager, Web::Node* node, Web::Node* parentNode, Web::Node* beforeNode);

public:

// IOleUndoUnit
	void Do(/* [in] */ IUndoManager *pUndoManager);
	System::StringW* GetDescription();
//	long GetUnitType(/* [out] */ CLSID __RPC_FAR *pClsid);
	void OnNextAdd();
};

}	// LXmlEdit
}
