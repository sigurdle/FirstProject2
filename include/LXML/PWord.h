#ifndef __PWord_h__
#define __PWord_h__

#include "PBox.h"

namespace System
{
namespace Web
{

class PText;
class CHTMLineBox;

class WEBEXT Char
{
public:
	inline CTOR Char(double _offset)
	{
		offset = _offset;
	}
	double offset;
};

class WEBEXT CHTMPCharacterBox : public CHTMBoxItem
{
public:
	CTOR CHTMPCharacterBox(PText* pTextNode);

	int m_start;
	int m_len;
	PText* m_pTextNode;	// The text node that this word belongs to
	vector<Char, __gc_allocator> m_chars;

//	void GetSel(CHTMRenderContext* pC, int& startChar, int& endChar, int length);

	void DrawTextDecoration(CHTMRenderContext* pC, gm::RectF& trect);

//	virtual void AdjustBottom(CHTMLineBox* pLineBox);
//	virtual double GetAscent();

	virtual void CalculateDimensions(CHTMCalcContext* pC) = 0;
};

class WEBEXT CHTMPWord : public CHTMPCharacterBox
{
public:
	CTOR CHTMPWord(PText* pTextNode) : CHTMPCharacterBox(pTextNode)
	{
		m_type = 3;
		m_bFreeText = false;
	//	m_text = NULL;
	}

	bool m_bFreeText;
	//const WCHAR* m_text;

	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);
	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);

protected:
	virtual ~CHTMPWord()
	{
		if (m_bFreeText)
		{
			ASSERT(0);
		//	SysFreeString(m_text);
		//	m_text = NULL;
		}
	}
};

class WEBEXT CHTMPSpace : public CHTMPCharacterBox
{
public:
	CTOR CHTMPSpace(PText* pTextNode) : CHTMPCharacterBox(pTextNode)
	{
		m_type = 4;
	}

	virtual bool getPosUnderPoint(double x, double y, PNode **pNode, long *pOffset);
	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);
};

}	// w3c
}

#endif // __PWord_h__
