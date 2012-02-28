#pragma once

#include "XMLGridNode.h"

namespace System
{

class CGridNodeDecl :
	public System::Object//IXMLGridTableColumn
{
public:
	int m_width;
	Web::NodeType m_nodeType;
	System::StringW* m_name;

	bool m_selected;

	Array<CGridNode*> m_nodes;

	CGridNodeDecl()
	{
		m_width = 80;
		m_selected = false;
	}

	CGridNode* FindElementNode(CGridElement* pElement);
};

class CGridAttrDecl :
	public CGridNodeDecl
{
public:
	CGridAttrDecl()
	{
		m_width = 60;
		m_nodeType = Web::NODE_ATTRIBUTE;
	}
};

class CGridElementDecl :
	public CGridNodeDecl
{
public:
	CGridElementDecl()
	{
		m_nodeType = Web::NODE_ELEMENT;
	}

};

class CGridTable :
	public CGridContainer
{
public:
	CGridTable()
	{
		m_iLastRowFocus = -1;
		m_iLastColumnFocus = -1;
		m_name = NULL;
	}

	/*
	void FinalRelease()
	{
		CGridContainer::FinalRelease();
	}
	*/

	System::StringW* m_name;

	Array<CGridNodeDecl*> m_nodeDecls;

	Array<CGridAttrDecl*> m_attrDecls;

	int m_iLastRowFocus;
	int m_iLastColumnFocus;

	CGridAttrDecl* FindAttrDecl(System::StringW* name);
	void BuildAttrDecls();

	virtual System::StringW* GetNodeName()
	{
		return m_name;
	}

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildSelectedXML(System::StringBuilderW& stream);

	virtual void BuildXML(System::IO::ISequentialByteStream* stream);
	virtual void BuildSelectedXML(System::IO::ISequentialByteStream* stream);

	virtual void Size(MSWindows::HDC hDC, int width);
	virtual void RecalculateParentSize(MSWindows::HDC hDC);

	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
	virtual int Click(MSWindows::HDC hDC, LDraw::PointD point, UINT nFlags, bool bDblClk, CGridItem* *pVal);

	void DeselectRows();
	void DeselectColumns();
};

}
