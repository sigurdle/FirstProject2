#ifndef __PInlineBox_h__
#define __PInlineBox_h__

#include "PElementBox.h"

namespace System
{
namespace Web
{

class CHTMInlineBox : public CHTMElementBox
{
public:
	CTOR CHTMInlineBox();

	virtual double AdjustBottom();

	virtual void Draw(CHTMRenderContext* pC);
	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);
	virtual int HitTestElementBox(double x, double y, PElementBase** ppElement);
};

class CMarkupBox : public CHTMBoxItem
{
public:
	PElementBase* m_pElement;
	int m_start;

	CTOR CMarkupBox()
	{
		m_pElement = NULL;
		m_start = 0;
	}

	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);

	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);
};

}	// w3c
}

#endif // __PInlineBox_h__
