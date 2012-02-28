#ifndef __PElementBox_h__
#define __PElementBox_h__

#include "PParentBox.h"
#include "PImage.h"

namespace System
{
namespace Web
{
class PElementBase;
//class ILBoxHandler;

class WEBEXT CHTMElementBox : public CHTMParentBox
{
protected:
	virtual ~CHTMElementBox();

public:
	CTOR CHTMElementBox();

	PElementBase* m_pElement;	// The element that owns this box
//	ILBoxHandler* m_pElement;	// The element that owns this box

// non-inherited CSS properties
	double m_computedMargin[4];	// draw as transparent
	double m_computedBorderWidth[4];
	double m_computedPadding[4];
	CRGBColor m_computedBackgroundColor;
	CImage* m_pBackgroundImage;

	void AdjustOuterRect();
//
	void DrawBoxShadow(CHTMRenderContext* pC);
	void DrawBorder(CHTMRenderContext* pC);
	void DrawOutline(CHTMRenderContext* pC);
	void DrawBackground(CHTMRenderContext* pC);
	void DrawChildren(CHTMRenderContext* pC);

	gm::PointD ScreenToClient(gm::PointD point);

//	virtual bool OnButtonDown(LDraw::PointD point, CPElementBase* *pVal);
	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);

//	virtual void SetParentNULL();

// public methods
//	virtual void Destroy();

//	virtual CPElement* HitTestElementBox(double x, double y);
};

}	// w3c
}

#endif // __PElementBox_h__
