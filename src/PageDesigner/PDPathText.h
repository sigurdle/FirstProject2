#include "PDObjectTextImpl.h"
#include "PDStory.h"

class CPDObjectFrame;

class CTextContext;
class CStoryFlowContext;

class CPDDocument;
class CPDPathText;
class CPDStory;
class CBox;
class CLineBox;
class CBlockBox;
class CElement;

class CPElementBox;

class CTextPathContext : public CTextContext
{
public:

	CPDPathText* m_pPathText;

	CComPtr<IPDSubPath> m_path;

	double m_lengthSoFar;

	CPElementBox* m_pCurElementBox;

	BOOL m_bInSelection;

public:
	CTextPathContext()
	{
		m_bInSelection = FALSE;

		m_pPathText = NULL;
		m_pCurElementBox = NULL;
		m_lengthSoFar = 0;
	}

	virtual CTextContext* SetupElement(CElement* pElement);
	virtual void SetdownElement(CElement* pElement, CTextContext* _pC);
	virtual BOOL PlaceWord(CNode* node, int start, _bstr_t data);
	virtual BOOL PlaceObject(IPDObject* object);
};

class CPBox
{
public:
	CPElementBox* m_parent;
	CElement* m_pElement;

public:
	virtual void Render(CTextPathContext* pC) = 0;
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset) = 0;
	virtual void RenderSelection(CTextPathContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range) = 0;

	CPBox()
	{
		m_pElement = NULL;
		m_parent = NULL;
	}
};

class CPElementBox : public CPBox
{
public:
	CArray<CPBox*,CPBox*> m_children;

public:

	virtual void Render(CTextPathContext* pC);
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
	virtual void RenderSelection(CTextPathContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range);
};

class CPWordBox : public CPBox
{
public:
	ILDOMNode* m_node;
	CArray<double,double> m_charOffsets;
	CArray<double,double> m_charRotations;
	CArray<CDblPoint,CDblPoint&> m_charPositions;

	int m_start;
	_bstr_t m_text;
	double m_height;

public:
	CPWordBox()
	{
		m_node = NULL;
		m_start = 0;
	}

	void CalculateDimensions(CTextPathContext* pC);

	virtual void Render(CTextPathContext* pC);
	virtual BOOL getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset);
	virtual void RenderSelection(CTextPathContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range);
};

class ATL_NO_VTABLE CPDPathText : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPDObjectTextImpl<IPDPathText>
{
public:
	CPDPathText()
	{
		m_pBox = NULL;
		m_parentFrame = NULL;

		m_startOnLength = 0.0;
		m_endOnLength = 0.0;

		m_pathTextAlign = PATHTEXTALIGN_BASELINE;
		m_pathTextAlignToPath = PATHTEXTALIGNTOPATH_CENTER;
	}

	int FinalConstruct()
	{
		HRESULT hr;

		hr = CPDObjectTextImpl<IPDPathText>::FinalConstruct();
		if (FAILED(hr)) return hr;

		return S_OK;
	}

	void FinalRelease()
	{
		CPDObjectTextImpl<IPDPathText>::FinalRelease();
	}

	CPDObjectFrame* m_parentFrame;
	CPElementBox* m_pBox;

	double m_startOnLength;
	double m_endOnLength;

	PDPathTextAlign			m_pathTextAlign;
	PDPathTextAlignToPath	m_pathTextAlignToPath;

	virtual CTextContext* SetupBox(CStoryFlowContext* pSC);
	virtual void SetdownBox(CTextContext* pContext);
	virtual void Clear();

	virtual void Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY);

	virtual void CalculateBounds()
	{
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CPDPathText)
	COM_INTERFACE_ENTRY(IPDUnknown)
	COM_INTERFACE_ENTRY(IPDObjectUnknown)
	COM_INTERFACE_ENTRY(IPDObject)
	COM_INTERFACE_ENTRY(IPDObjectText)
	COM_INTERFACE_ENTRY(IPDPathText)
	COM_INTERFACE_ENTRY(IObjectSerializable)
END_COM_MAP()

// IPDPathText
public:
	STDMETHOD(getExpandedBBox)(/*[out,retval]*/ RectD* pVal);
	STDMETHOD(get_pathTextAlignToPath)(/*[out, retval]*/ PDPathTextAlignToPath *pVal);
	STDMETHOD(put_pathTextAlignToPath)(/*[in]*/ PDPathTextAlignToPath newVal);
	STDMETHOD(get_pathTextAlign)(/*[out, retval]*/ PDPathTextAlign *pVal);
	STDMETHOD(put_pathTextAlign)(/*[in]*/ PDPathTextAlign newVal);
	STDMETHOD(get_wrapPath)(/*[out, retval]*/ IPDPath* *pVal);
	STDMETHOD(put_wrapPath)(/*[in]*/ IPDPath* newVal);
	STDMETHOD(get_endOnLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_endOnLength)(/*[in]*/ double newVal);
	STDMETHOD(get_startOnLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_startOnLength)(/*[in]*/ double newVal);
	STDMETHOD(RenderSelection)(/*[in]*/ HDC hDC, /*[in]*/ IPDMatrix* matrix, /*[in]*/ ILDOMRange* range);
	STDMETHOD(getPosUnderPoint)(/*[in]*/ double x, /*[in]*/ double y, /*[out]*/ ILDOMNode* *pNode, /*[out]*/ long *pOffset, /*[out,retval]*/ BOOL *bHit);
//	STDMETHOD(saveAsXML)(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId);
//	STDMETHOD(loadXML)(/*[in]*/ IDOMNode* node);
	STDMETHOD(get_objectType)(/*[out, retval]*/ PDObjectType *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = PATH_TEXT;
		return S_OK;
	}
// IObjectSerializable
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID)
	{
		*pClassID = CLSID_NULL;//PDContentGraphic;
		return S_OK;
	}
};
