#ifndef __PLineBox_h__
#define __PLineBox_h__

#include "PParentBox.h"

namespace System
{
namespace Web
{

class CHTMLineBox : public CHTMParentBox
{
public:
	CTOR CHTMLineBox();
	~CHTMLineBox();

//	double m_maxascent;

#if 0
	void Adjust(CPElement* pElement);
#endif
	double AdjustBottom();

	virtual void Draw(CHTMRenderContext* pC);
//	virtual void OnButtonDown(LDraw::PointD point, int nhit);
	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);
	virtual int HitTestElementBox(double x, double y, PElementBase** ppElement);
};

}	// w3c
}

#endif // __PLineBox_h__
