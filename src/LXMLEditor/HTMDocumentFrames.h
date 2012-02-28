#pragma once

namespace System
{

class CHTMDesignFrameSet;
class CHTMDesignFrame;

class CHTMDesignFrameNode
{
public:
	int m_type;
	Web::Document* m_pDocument;

	CHTMDesignFrameNode* m_pParentFrame;

//	CIUIWnd*	m_pUI;

	LDraw::BBoxi	m_client;

	Web::Element*	m_pElement;

	CHTMDesignFrameNode()
	{
		m_type = -1;
	//	m_pDocument = 0;
		m_pParentFrame = NULL;
	//	m_pElement = NULL;
//		m_pUI = NULL;
	}

	CHTMDesignFrame* GetTopFrame();

	virtual ~CHTMDesignFrameNode()
	{
	}

	virtual void OnPaint(MSWindows::HDC hDC) = 0;
	virtual void PositionFrames(int spacing = -1) = 0;
	virtual bool OnButtonDown(UINT nFlags, LDraw::PointD point, int iButton, bool bDblClk, CHTMDesignFrame** pFrame) = 0;
//	virtual BOOL OnMouseMove(UINT nFlags, POINT point) = 0;
};

class CHTMDesignFrameSet : public CHTMDesignFrameNode
{
public:
#if 0
	CUPtrList m_frames;	// A list of CHTMFrameNode

	CString m_cols;
	CString m_rows;

public:
	CHTMDesignFrameSet()
	{
		m_type = 0;
	}

	virtual ~CHTMDesignFrameSet();

	CHTMDesignFrame* FindFrameByName(LPCTSTR name);

	virtual BOOL OnButtonDown(UINT nFlags, POINT point, int iButton, BOOL bDblClk, CHTMDesignFrame** pFrame);
/*	virtual BOOL OnMouseMove(UINT nFlags, POINT point)
	{
		return FALSE;
	}
*/
	virtual void OnPaint(HDC hDC);
	void CreateFrames(Web::Element* pFrameSetElement);

	virtual void PositionFrames(int spacing = -1);
#endif
};

//class CHTMPElement;

class CHTMDesignFrame : public CHTMDesignFrameNode
{
public:
	System::StringW* m_src;
	System::StringW* m_name;	// target for A href tags

	Web::Document* m_pDocument;
	// For HTML document (Both BODY and FRAMESET)

//	CJScript* m_pJScript;
//	CJSGlobal* m_pGlobal;

// url is HTML BODY document
//	CHTMPElement* m_htmTree;

// url is HTML FRAMESET document
	CHTMDesignFrameSet* m_pFrameSet;

	void BuildHTMTree();
	void OnSize();

public:
	CHTMDesignFrame();
	virtual ~CHTMDesignFrame();

	virtual bool OnButtonDown(UINT nFlags, LDraw::PointD point, int iButton, bool bDblClk, CHTMDesignFrame** pFrame);
//	virtual BOOL OnMouseMove(UINT nFlags, POINT point);
	bool OnSetCursor(UINT nHittest, UINT wMouseMsg);
	void OnContextMenu(UI::Control* hWnd, LDraw::PointD point);

	virtual void OnPaint(MSWindows::HDC hDC);

	virtual void PositionFrames(int spacing = -1);
};

}
