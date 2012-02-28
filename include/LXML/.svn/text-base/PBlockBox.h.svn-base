#ifndef __PBlockBox_h__
#define __PBlockBox_h__

#include "PElementBox.h"

namespace System
{
namespace Web
{

class WEBEXT CHTMBlockBox : public CHTMElementBox
{
protected:
	virtual ~CHTMBlockBox();

public:
	CTOR CHTMBlockBox();

	void Draw2(CHTMRenderContext* pC/*, LDraw::RectF& outerRect*/);

	void DrawScrollBars(CHTMRenderContext* pC);

	virtual void Draw(CHTMRenderContext* pC);
	virtual int HitTestElementBox(double x, double y, PElementBase** ppElement);
	virtual gm::PointD ParentToChild(gm::PointD point);

	uint8 m_opacity;
	ControlHost* m_scrollX;
	ControlHost* m_scrollY;

	// Testing
	vector<CHTMElementBox*, __gc_allocator> m_positioned_children;
};

}	// w3c
}

#endif // __PBlockBox_h__
