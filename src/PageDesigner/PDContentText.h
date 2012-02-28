#pragma once

#include "PDObjectTextImpl.h"
#include "PDStory.h"
#include "PDTextFrameOptionsImpl.h"
#include "PDObjectLocatableImpl.h"

class CPDDocument;
class CPDContentText;
class CBox;
class CLineBox;
class CBlockBox;
class CElementBox;
class CNode;
class CElement;

class CContentTextContext : public CTextContext
{
public:
	CPDContentText* m_pContentText;

	Gdiplus::Region* m_iregion;

	CBlockBox* m_pBlockBox;
	CLineBox* m_pCurLineBox;
	CElementBox* m_pCurBox;

	CElement* m_pElement;

	int m_textAlign;

	Gdiplus::RectF m_framebounds;
	double m_x;
	double m_y;

	double m_absx;
	double m_absy;

	double m_left;
	double m_right;

	int m_nDropCapsChars;
	int m_nDropCapsLines;
	int m_nDropCapsCharSoFar;
	double m_nDropCapsLeft;
	double m_nDropCapsBottom;

	BOOL m_bInSelection;

	BOOL PlaceInlineBox(CBox* pInlineBox);
	BOOL PlaceInlineBoxInColumn(CBox* pCBox);
	BOOL PlaceInlineBoxInDropCaps(CBox* pCBox);

	CContentTextContext()
	{
		m_pContentText = NULL;

//		m_pGraphics = NULL;

		m_pElement = NULL;
		m_pBlockBox = NULL;
		m_pCurLineBox = NULL;
		m_pCurBox = NULL;

		m_absx = 0;
		m_absy = 0;

		m_left = 0;
		m_right = 0;

		m_x = 0;
		m_y = 0;
		m_iregion = NULL;

		m_bInSelection = FALSE;

		m_textAlign = 0;

		m_nDropCapsChars = 0;
		m_nDropCapsLines = 0;

		m_nDropCapsCharSoFar = 0;
		m_nDropCapsLeft = 0;
		m_nDropCapsBottom = 20;
	}

	~CContentTextContext()
	{
	}

	virtual CTextContext* SetupElement(CElement* pElement);
	virtual void SetdownElement(CElement* pElement, CTextContext* _pC);
	virtual BOOL PlaceWord(CNode* node, int start, _bstr_t data);
	virtual BOOL PlaceObject(IPDObject* object);
};

class CBox
{
public:
	BYTE m_type;
	Gdiplus::RectF m_innerRect;
	Gdiplus::RectF m_outerRect;
	CBox* m_parent;
	CElement* m_pElement;

	CArray<CBox*,CBox*> m_children;

public:
	CBox()
	{
		m_type = 0;
		m_parent = NULL;
		m_pElement = NULL;

		m_innerRect.X = 0;
		m_innerRect.Y = 0;
		m_innerRect.Width = 0;
		m_innerRect.Height = 0;

		m_outerRect.X = 0;
		m_outerRect.Y = 0;
		m_outerRect.Width = 0;
		m_outerRect.Height = 0;
	}

	virtual ~CBox()
	{
		for (int i = 0; i < m_children.GetSize(); i++)
		{
			delete m_children[i];
		}
		m_children.RemoveAll();
	}

	Gdiplus::RectF GetAbsInnerRect();

	CBox* GetPreviousSibling()
	{
		if (m_parent)
		{
			for (int i = 0; i < m_parent->m_children.GetSize(); i++)
			{
				if (m_parent->m_children[i] == this)
				{
					if (i > 0)
						return m_parent->m_children[i-1];
					else
						return NULL;
				}
			}
			ATLASSERT(0);
		}
		return NULL;
	}

	CBox* GetNextSibling()
	{
		if (m_parent)
		{
			for (int i = 0; i < m_parent->m_children.GetSize(); i++)
			{
				if (m_parent->m_children[i] == this)
				{
					if (i < m_parent->m_children.GetSize()-1)
						return m_parent->m_children[i+1];
					else
						return NULL;
				}
			}
			ATLASSERT(0);
		}
		return NULL;
	}

	virtual void Render(CContentTextContext* pContext);
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
	virtual void RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range);

	void BuildPaths(CContentTextContext* pC, IPDDocument* pddoc, IPDObjectGroup* pdgroup, IPDPath* pdpath, HDC hDC);

	CBox* FindBox(ILDOMNode* container, long offset);
//	BOOL FindNodeFromX(IDOMNode* *containeR, long* offset);

	CLineBox* GetParentLineBox();

	CElement* GetElement()
	{
		CBox* parent = this;
		while (parent->m_pElement == NULL)
			parent = parent->m_parent;

		return parent->m_pElement;
	}
};

class CElementBox : public CBox
{
public:
	CElementBox()
	{
		m_type = 3;
	}
};

class CBlockBox : public CBox
{
public:
	CBlockBox()
	{
		m_type = 1;
	}

	virtual void Render(CContentTextContext* pContext);
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
};

class CTextContentBox : public CBox
{
public:
	int m_start;
	ILDOMNode* m_node;	// DOMText
	WCHAR m_ch;

	CTextContentBox()
	{
		m_node = NULL;
	}

	void RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range, int length, double* m_charOffsets);
	virtual void CalculateDimensions(CContentTextContext* pC, double sizeFactor = 1) = 0;
	virtual double GetCharOffset(int index) = 0;
};

class CSpaceBox : public CTextContentBox
{
public:
	CSpaceBox()
	{
		m_type = 11;
	}

	virtual double GetCharOffset(int index)
	{
		double charOffsets[2] = {0, m_innerRect.Width };
		return charOffsets[index];
	}

	virtual void Render(CContentTextContext* pC);
	virtual void CalculateDimensions(CContentTextContext* pC, double sizeFactor = 1);
	virtual void RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range);
};

class CWordBox : public CTextContentBox
{
public:
	_bstr_t m_text;
	CArray<double,double> m_charOffsets;

public:
	CWordBox()
	{
		m_type = 10;
	}

	virtual double GetCharOffset(int index)
	{
		return m_charOffsets[index];
	}

	virtual void CalculateDimensions(CContentTextContext* pC, double sizeFactor = 1);

	virtual void Render(CContentTextContext* pC);
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
	virtual void RenderSelection(CContentTextContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range);
};

class CObjectBox : public CBox
{
public:
	CPDObjectImpl<IPDObject>* m_pObject;

public:
	CObjectBox()
	{
		m_type = 12;
		m_pObject = NULL;
	}

	virtual void Render(CContentTextContext* pC);
};

class CLineBox : public CBox
{
public:
	CLineBox()
	{
		m_type = 2;
	}

	double m_maxascent;

	void AdjustBottom();
	void OffsetChildren(double dx);

	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
	virtual void Render(CContentTextContext* pC);
};

class ATL_NO_VTABLE CPDContentText : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDContentText, &CLSID_PDContentText>,
	public CPDObjectTextImpl<IPDContentText>,
	public CPDTextFrameOptionsImpl<CPDContentText>,
	public CPDObjectLocatableImpl<CPDContentText, IPDObjectLocatable>,
	public CNotifySendImpl<CPDContentText>
{
public:
	CPDContentText()
	{
		m_pBox = NULL;

		m_regionRectsCount = 0L;
		m_regionRects = NULL;
	}

	int FinalConstruct();
	void FinalRelease();

	double m_topSoFar;
	double m_bottomSoFar;

	CBlockBox* m_pBox;

	int m_nColumnsSoFar;

	INT m_regionRectsCount;
	Gdiplus::RectF* m_regionRects;

	virtual CTextContext* SetupBox(CStoryFlowContext* pSC);
	virtual void SetdownBox(CTextContext* pContext);
	virtual void Clear();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* graphics, double scaleX, double scaleY);
	virtual void CalculateBounds();

	void FindThreadPts(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
	void CalculateThreadRects();

	void OnChangedTextFrameOptions();

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDCONTENTTEXT)

BEGIN_COM_MAP(CPDContentText)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectText)
	COM_INTERFACE_ENTRY(IPDContentText)
	COM_INTERFACE_ENTRY(IPDTextFrameOptions)
	COM_INTERFACE_ENTRY(IPDObjectLocatable)
	COM_INTERFACE_ENTRY(IObjectSerializable)
	COM_INTERFACE_ENTRY(INotifySend)
END_COM_MAP()

// IPDContentText
public:
	STDMETHOD(setColumns)(/*[in]*/ long ncolumns, /*[in]*/ double gutter, /*[in]*/ double width, /*[in]*/ VARIANT_BOOL fixedWidth);
	//STDMETHOD(getExpandedBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(RenderSelection)(/*[in]*/ HDC hDC, /*[in]*/ IPDMatrix* matrix, /*[in]*/ ILDOMRange* range);
	STDMETHOD(getPosUnderPoint)(/*[in]*/ double x, /*[in]*/ double y, /*[out]*/ ILDOMNode* *pNode, /*[out]*/ long *pOffset, /*[out,retval]*/ BOOL *bHit);
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal);
// IPDObjectLocatable
	STDMETHOD(Move)(/*[in]*/ double dx, /*[in]*/ double dy);
	STDMETHOD(getScreenBBox)(/*[out,retval]*/ RectD* pVal);
// IObjectSerializable
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_PDContentText;
		return S_OK;
	}
};
