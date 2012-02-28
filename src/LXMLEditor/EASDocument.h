// EASDocument.h : Declaration of the CEASDocument

#ifndef __EASDOCUMENT_H_
#define __EASDOCUMENT_H_

#include "resource.h"       // main symbols

#include "..\LXFramework\WebDocumentImpl.h"

namespace System
{
namespace LXmlEdit
{

/////////////////////////////////////////////////////////////////////////////
// CEASDocument
class CEASDocument : 
	public CEDocument//Impl<CEASDocument>,
{
public:
	CTOR CEASDocument()
	{
	}

	CLXMLEditorApp* m_app;

// IEASDocument
public:
// IEDocument
	ErrorCode ShowViews(IEFrame* pFrame);
	ErrorCode Activate();
	ErrorCode CloseDocument();
};

}	// LXmlEdit
}

#endif //__EASDOCUMENT_H_
