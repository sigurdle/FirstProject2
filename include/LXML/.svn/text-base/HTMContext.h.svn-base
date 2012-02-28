#ifndef __HTMContext_h__
#define __HTMContext_h__

/*
class IMPORTEXPORT CHTMBaseContext
{
public:
	virtual ~CHTMBaseContext()
	{
	}
};
*/

namespace System
{
namespace Web
{

class CHTMLWindow;
//class CLHTMLDocumentView;

class CHTMBoxItem;
class CHTMParentBox;
class CHTMInlineBox;
class CHTMLineBox;
class CHTMBlockBox;

class PElementBase;
//class ILBoxHandler;	// Have this instead

class WEBEXT CHTMContext// : public CHTMBaseContext
{
public:
	CTOR CHTMContext()
	{
		m_renderContext = NULL;
	//	m_pStringFormat = Gdiplus::StringFormat::GenericTypographic();

//		m_pUI = NULL;	// TODO Remove ??
	}

	virtual ~CHTMContext()
	{
	}

	Gui::RetainedRenderContext* m_renderContext;
//	const Gdiplus::StringFormat* m_pStringFormat;

#if 0
//	CLHTMLDocumentView* m_pUI;
	void* m_pUI;	// TODO Remove ??
#endif
};

class WEBEXT CHTMCalcContext : public CHTMContext
{
public:

	/*
#ifdef 1//_DEBUG
	DWORD m_timeGetCSS;
#endif
	*/
};

class WEBEXT CHTMFlowInlineContext;

class WEBEXT CHTMFlowContext : public Object
{
public:
	CTOR CHTMFlowContext()
	{
		m_curpos.X = 0;
		m_curpos.Y = 0;

// float info
		m_floatLeft = 0;
		m_floatBottom = 0;
		m_pPrevLeftFloatBox = NULL;

		m_pPseudoFirstLineElement = NULL;

	//
		m_pCurInlineBox = NULL;
		m_pParentC = NULL;
		m_pCurLineBox = NULL;
		m_pBlockBox = NULL;
		m_pElement = NULL;
	}

	virtual ~CHTMFlowContext()
	{
	}

	int m_floatLeft;
	int m_floatBottom;
	CHTMBlockBox* m_pPrevLeftFloatBox;

	PElementBase* m_pPseudoFirstLineElement;

	short m_type;
	gm::PointF m_curpos;

	virtual void PlaceInlineBox2(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox) = 0;
	virtual int PlaceOnSame(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox) = 0;


#if 1
	CHTMInlineBox* m_pCurInlineBox;
	CHTMFlowContext* m_pParentC;
#endif

#if 1

	float m_maxx;
	gm::PointF m_linepos;
	CHTMLineBox* m_pCurLineBox;
	CHTMBlockBox* m_pBlockBox;
	PElementBase* m_pElement;

#endif

	virtual void PlaceInlineBox(CHTMBoxItem* pBox)
	{
		ASSERT(0);
	}

	virtual void done()
	{
	}
};

class WEBEXT CHTMFlowInlineContext : public CHTMFlowContext
{
public:
	CTOR CHTMFlowInlineContext();
	virtual ~CHTMFlowInlineContext();

#if 0
	CHTMInlineBox* m_pCurInlineBox;
	CHTMFlowContext* m_pParentC;
	PElementBase* m_pElement;
#endif

	bool m_bAnonymous;

	virtual void PlaceInlineBox(CHTMBoxItem* pBox);
	//void PlaceRelativeOnTop(CHTMParentBox* pThisBox);

	virtual void PlaceInlineBox2(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox);
	virtual int PlaceOnSame(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox);
};

class WEBEXT CHTMFlowBlockContext : public CHTMFlowContext
{
public:
	CTOR CHTMFlowBlockContext();
	virtual ~CHTMFlowBlockContext();

	bool m_bCanBreak;

	void done();

#if 0
	PElementBase* m_pElement;
	float m_maxx;
	LDraw::PointF m_linepos;
	CHTMLineBox* m_pCurLineBox;
	CHTMBlockBox* m_pBlockBox;
#endif

	gm::RectI m_frameClient;
	CHTMLWindow* m_pWindow;

	virtual void PlaceInlineBox2(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox);
	virtual int PlaceOnSame(CHTMFlowInlineContext* pC, CHTMBoxItem* pBox);
};

}	// Web
}

#endif // __HTMContext_h__
