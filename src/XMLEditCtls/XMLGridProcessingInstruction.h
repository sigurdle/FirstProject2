#pragma once

#include "XMLGridNode.h"

namespace System
{

class CGridProcessingInstruction :
	public CGridNode
{
public:
	/*
	void FinalRelease()
	{
		CGridNode::FinalRelease();
	}
	*/

	CGridProcessingInstruction()
	{
		m_minWidth = 10;
	}

	System::StringW* GetValue();
	virtual void Size(MSWindows::HDC hDC, int width);
	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
	virtual int Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal);
	virtual void EndEdit(/*CXMLGridCtl* pUI*/);
	virtual void OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree);

	virtual int HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal);

	//virtual sysstring BuildXML();
	virtual void BuildXML(System::StringBuilderW& stream);
};

}
