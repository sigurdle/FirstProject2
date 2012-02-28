#pragma once

#include "XMLGridNode.h"

namespace System
{

class CGridEntityReference :
	public CGridNode
{
public:
	/*
	void FinalRelease()
	{
		CGridNode::FinalRelease();
	}
	*/

	virtual void BuildXML(System::IO::ISequentialByteStream* stream);

	virtual System::StringW* GetNodeName()
	{
		return WSTR("ENTITY");
		/*
		BSTR bnodeName;
		m_domElement->get_nodeName(&bnodeName);
		return sysstring(bnodeName, false);
		*/
	}

	virtual void Size(MSWindows::HDC hDC, int width);

	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
};

}
