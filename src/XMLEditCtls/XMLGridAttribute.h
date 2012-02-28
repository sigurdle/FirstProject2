#pragma once

#include "XMLGridContainerNode.h"

namespace System
{

class XMLGRIDEXT CGridAttribute :
	public CGridContainerNode
{
public:
	CGridAttribute()
	{
		m_minWidth = 10;
	}

	UI::UIElement* m_icon;
	UI::TextEdit* m_nodeNameEdit;

	virtual void BuildChildren();

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
	virtual void OnArrange(LDraw::SizeD finalSize);

	//virtual System::StringW* BuildXML();
	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);

#if 0
	virtual void Size(HDC hDC, int width);
	virtual void SizeContent(HDC hDC, int width);
	virtual void Draw(HDC hDC, BOOL bSelected);
	virtual void DrawContent(HDC hDC, BOOL bSelected);
#endif
	virtual int Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal);
	virtual int ClickContent(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem** pVal);
//	virtual void OnEditChange(HDC hDC, CGridItem* m_pTree);

	virtual int HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal);
};

}
