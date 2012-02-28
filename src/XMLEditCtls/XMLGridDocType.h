#pragma once

#include "XMLGridNode.h"

namespace System
{

class XMLGRIDEXT CGridEntity :
	public CGridItem
{
public:
	void FinalRelease()
	{
		CGridItem::FinalRelease();
	}

//	ILDTDObject* m_object;

	virtual void BuildXML(System::IO::ISequentialByteStream* stream)
	{
		ASSERT(0);
	}

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

	virtual void BuildChildren();
};


class XMLGRIDEXT CGridDTDElement :
	public CGridItem
{
public:
	void FinalRelease()
	{
		CGridItem::FinalRelease();
	}

//	ILDTDObject* m_object;

	virtual void BuildXML(System::IO::ISequentialByteStream* stream)
	{
		ASSERT(0);
	}

	virtual System::StringW* GetNodeName()
	{
		return WSTR("ELEMENT");
		/*
		BSTR bnodeName;
		m_domElement->get_nodeName(&bnodeName);
		return sysstring(bnodeName, false);
		*/
	}

	virtual void Size(MSWindows::HDC hDC, int width);

	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
};

class XMLGRIDEXT CGridDTDAttList :
	public CGridItem
{
public:
	/*
	void FinalRelease()
	{
		CGridItem::FinalRelease();
	}
	*/

	Web::CDTDObjectImpl* m_object;

	virtual void BuildXML(System::IO::ISequentialByteStream* stream)
	{
		ASSERT(0);
	}

	virtual System::StringW* GetNodeName()
	{
		return WSTR("ATTLIST");
		/*
		BSTR bnodeName;
		m_domElement->get_nodeName(&bnodeName);
		return sysstring(bnodeName, false);
		*/
	}

	virtual void Size(MSWindows::HDC hDC, int width);

	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
};

class XMLGRIDEXT CGridDocType :
	public CGridContainer
{
public:
	/*
	void FinalRelease()
	{
		CGridContainer::FinalRelease();
	}
	*/

	int m_nameHeight;

	virtual void BuildChildren();

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);
	virtual System::StringW* GetNodeName();
	virtual void Size(MSWindows::HDC hDC, int width);
	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
};

class CGridDTDDocument :
	public CGridContainer
{
public:
	Web::CDTDObjectImpl* m_object;

//	int m_nameHeight;

	virtual void BuildChildren();

	virtual void BuildXML(System::IO::ISequentialByteStream* stream);
	virtual System::StringW* GetNodeName();
	virtual void Size(MSWindows::HDC hDC, int width);
	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
};

}
