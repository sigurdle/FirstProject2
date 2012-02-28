#ifndef __PParentBox_h__
#define __PParentBox_h__

#include "PBox.h"

namespace System
{
namespace Web
{

class CHTMParentBox : public CHTMBoxItem
{
protected:
	virtual ~CHTMParentBox();

public:
	CTOR CHTMParentBox();

//	BOOL m_bAnynomous;	// TODO remove
	vector<CHTMBoxItem*> m_children;	// boxes contained within this box
	vector<CHTMBoxItem*> m_renderChildren;	// boxes contained within this box

	gm::RectF m_innerRect;	// Relative to m_outerRect
	gm::RectF m_absInnerRect;

	gm::RectF GetAbsInnerRect();

//	void PlaceRelativeOnTop();

	void AddChildBox(CHTMBoxItem* pBox);
	void RemoveChildBox(CHTMBoxItem* pBox);
	void DeleteChildBoxes();
	void DrawOutline(CHTMRenderContext* pC);	// TODO ??? Remove

// public methods
	virtual void Destroy();
	virtual gm::PointD ParentToChild(gm::PointD point);
};

}	// w3c
}

#endif // __PParentBox_h__
