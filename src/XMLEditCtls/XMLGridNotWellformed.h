#include "XMLGridNode.h"

namespace System
{

class CGridNotWellformed :
	public CGridNode
{
public:
	CGridNotWellformed()
	{
		m_minWidth = 10;
	}

	void FinalRelease()
	{
		CGridNode::FinalRelease();
	}

	System::StringW* GetValue();
	virtual void Size(MSWindows::HDC hDC, int width);
	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
	virtual int Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal);
	virtual void EndEdit();
	virtual void OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree);

	virtual int HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal);

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);
};

}
